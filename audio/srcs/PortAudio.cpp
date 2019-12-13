/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** PortAudio.cpp
*/

#include "PortAudio.hpp"

PortAudio::PortAudio():
    _sample_rate(44100),
    _frame_per_buffer(512),
    _isFreeable(false)
{
    _err = Pa_Initialize();
    if (_err != paNoError) {
        std::cout << "Can't use PortAudio" << std::endl;
        exit(84);
    }
}

PortAudio::~PortAudio()
{
    Pa_Terminate();
    if (_isFreeable == true)
        free(_data.recordedSamples);
}

void PortAudio::SetInputParameters()
{
    _inputParameters.device = Pa_GetDefaultInputDevice();
    if (_inputParameters.device == paNoDevice) {
        std::cerr << "Error: No default input device." << std::endl;
        return;
    }
    _inputParameters.channelCount = 2;
    _inputParameters.sampleFormat = paFloat32;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultLowInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = NULL;
}

void PortAudio::SetData(int num_seconds, int sample_rate, int num_channels)
{
    int numSamples;
    int numBytes;

    _data.maxFrameIndex = num_seconds * sample_rate;
    _data.frameIndex = 0;
    numSamples = _data.maxFrameIndex * num_channels;
    numBytes = numSamples * sizeof(float);
    _data.recordedSamples = static_cast<float *>(malloc(numBytes));

    for (int i = 0; i < numSamples; ++i)
        _data.recordedSamples[i] = 0;

    _isFreeable = true;
}

void PortAudio::SetOutputParameters()
{
    _outputParameters.device = Pa_GetDefaultInputDevice();
    if (_outputParameters.device == paNoDevice) {
        std::cerr << "error: No default input device." << std::endl;
        return;
    }
    _outputParameters.channelCount = 2;
    _outputParameters.sampleFormat = paFloat32;
    _outputParameters.suggestedLatency = Pa_GetDeviceInfo(_outputParameters.device)->defaultLowOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = NULL;
}

void PortAudio::StartStream(PaStream *stream)
{
    _err = Pa_StartStream(stream);
    if (_err != paNoError)
        exit(84);
}

void PortAudio::CloseStream(PaStream *stream)
{
    _err = Pa_CloseStream(stream);
    if (_err != paNoError)
        exit(84);
}

int recordCallback(const void *inputBuffer,
                    void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData)
{
    paTestData *data = static_cast<paTestData *>(userData);
    const float *rptr = static_cast<const float *>(inputBuffer);
    float *wptr = &data->recordedSamples[data->frameIndex * 2];
    long framesToCalc = 0;
    long i = 0;
    int finished = 0;
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

    if (framesLeft < framesPerBuffer) {
        framesToCalc = framesLeft;
        finished = paComplete;
    } else {
        framesToCalc = framesPerBuffer;
        finished = paContinue;
    }

    if (inputBuffer == NULL) {
        for (i = 0; i < framesToCalc; ++i) {
            *wptr++ = SAMPLE_SILENCE; /* left */
            *wptr++ = SAMPLE_SILENCE; /* right */
        }
    } else {
        for (i = 0; i < framesToCalc; ++i) {
            *wptr++ = *rptr++; /* left */
            *wptr++ = *rptr++; /* right */
        }
    }
    data->frameIndex += framesToCalc;
    return finished;
}

std::vector<unsigned short> PortAudio::readStream(PaStream *stream)
{
    unsigned long bufferSize = 480;
    std::vector<unsigned short> captured(bufferSize * 2);
    PaError _err = Pa_ReadStream(stream, captured.data(), bufferSize);
    if (_err != paNoError)
        std::cerr << "Pa_ReadStream failed: " << Pa_GetErrorText(_err) << std::endl;
    return captured;
}

PaStream *PortAudio::RecordStream()
{
    PaStream *stream;

    // _err = Pa_OpenStream(
    //     &stream,
    //     &_inputParameters,
    //     NULL,
    //     44100,
    //     _frame_per_buffer,
    //     paClipOff,
    //     recordCallback,
    //     &_data);
    _err = Pa_OpenDefaultStream(&stream,
      2, 2, paInt16, 48000,
      480, nullptr, nullptr);
    if (_err != paNoError) {
        std::cout << _err << std::endl;
        std::cout << Pa_GetErrorText(_err) << std::endl;
        exit(84);
    }
    return stream;
}

PaStream *PortAudio::writeStream(std::vector<unsigned short> decoded)
{
    PaStream *stream;

    Pa_WriteStream(stream, decoded.data(), 480);
    return stream;
}

static int playCallback(const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo *timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData)
{
    paTestData *data = static_cast<paTestData *>(userData);
    float *rptr = &data->recordedSamples[data->frameIndex * 2];
    float *wptr = static_cast<float *>(outputBuffer);
    unsigned int i;
    int finished;
    unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

    if (framesLeft < framesPerBuffer) {
        /* final buffer... */
        for (i = 0; i < framesLeft; ++i) {
            *wptr++ = *rptr++; /* left */
            *wptr++ = *rptr++; /* right */
        }
        for (; i < framesPerBuffer; ++i) {
            *wptr++ = 0; /* left */
            *wptr++ = 0; /* right */
        }
        data->frameIndex += framesLeft;
        finished = paComplete;
    } else {
        for (i = 0; i < framesPerBuffer; ++i) {
            *wptr++ = *rptr++; /* left */
            *wptr++ = *rptr++; /* right */
        }
        data->frameIndex += framesPerBuffer;
        finished = paContinue;
    }
    return finished;
}

void PortAudio::PlayStream(PaStream *stream)
{
    _err = Pa_OpenStream(
        &stream,
        NULL,
        &_outputParameters,
        44100,
        _frame_per_buffer,
        paClipOff,
        playCallback,
        &_data);
    if (_err != paNoError) {
        std::cout << _err << std::endl;
        std::cout << Pa_GetErrorText(_err) << std::endl;
        exit(84);
    }
}


void PortAudio::setSampleRate(short sample_rate)
{
    _sample_rate = sample_rate;
}

void PortAudio::setFramePerBuffer(short frame_per_buffer)
{
    _frame_per_buffer = frame_per_buffer;
}

void PortAudio::setDataFrameIndex()
{
    _data.frameIndex = 0;
}

// int main()
// {
//     PortAudio test;
//     PaStream *stream;
//     test.SetInputParameters();
//     std::cout << "1" << std::endl;
//     test.SetData(5, 44100, 2);
//     std::cout << "2" << std::endl;
//     stream = test.RecordStream();
//     std::cout << "3" << std::endl;
//     test.StartStream(stream);
//     std::cout << "4" << std::endl;
//     Pa_Sleep(3000);
//     std::cout << "5" << std::endl;
//     test.CloseStream(stream);
//     std::cout << "6" << std::endl;
//     test.SetOutputParameters();
//     test.setDataFrameIndex();
//     std::cout << "7" << std::endl;
//     test.PlayStream(stream);
//     std::cout << "8" << std::endl;
//     test.StartStream(stream);
//     Pa_Sleep(3000);
//     std::cout << "9" << std::endl;
//     test.CloseStream(stream);
//     std::cout << "10" << std::endl;
//     return (0);
// }

testAudio::testAudio()
{
    // initialize opus
    int opusErr;

    _enc = opus_encoder_create(
        SAMPLE_RATE, CHANNELS, OPUS_APPLICATION_AUDIO, &opusErr);
    if (opusErr != OPUS_OK) {
        std::cout << "opus_encoder_create failed: " << opusErr << std::endl;
        exit(84);
    }
    _dec = opus_decoder_create(
        SAMPLE_RATE, CHANNELS, &opusErr);
    if (opusErr != OPUS_OK) {
        std::cout << "opus_decoder_create failed: " << opusErr << std::endl;
        exit(84);
    }

    // initialize portaudio
    PaError paErr;

    if ((paErr = Pa_Initialize()) != paNoError) {
        std::cout << "Pa_Initialize failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
}

testAudio::~testAudio()
{
    PaError paErr;

    if ((paErr = Pa_Terminate()) != paNoError)  {
        std::cout << "Pa_Terminate failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
    opus_encoder_destroy(_enc);
    opus_decoder_destroy(_dec);
}

void testAudio::initOutputInfo()
{
    // _outputInfo.device = Pa_GetDefaultOutputDevice();
    // if (_outputInfo.device == paNoDevice) {
    //     std::cout << "error: No default output device." << std::endl;
    //     exit(84);
    // }
    // _outputInfo.channelCount = 2; //2 ?
    // _outputInfo.sampleFormat = paFloat32;
    // _outputInfo.suggestedLatency = Pa_GetDeviceInfo(_outputInfo.device)->defaultLowOutputLatency;
    // _outputInfo.hostApiSpecificStreamInfo = NULL;

    _outputInfo.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (_outputInfo.device == paNoDevice) {
        std::cout << "Error: No default output device." << std::endl;
        exit(84);
    }
    _outputInfo.channelCount = 2;       /* stereo output */
    _outputInfo.sampleFormat = paFloat32; /* 32 bit floating point output */
    _outputInfo.suggestedLatency = 0.050; // Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    _outputInfo.hostApiSpecificStreamInfo = NULL;
}

void testAudio::initData(int num_seconds, int sample_rate, int num_channels)
{
    int numSamples;
    int numBytes;

    _data.maxFrameIndex = num_seconds * sample_rate;
    _data.frameIndex = 0;
    numSamples = _data.maxFrameIndex * num_channels;
    numBytes = numSamples * sizeof(float);
    _data.recordedSamples = static_cast<float *>(malloc(numBytes));

    for (int i = 0; i < numSamples; ++i)
        _data.recordedSamples[i] = 0;
}

PaStream *testAudio::openStream()
{
    PaError paErr;
    PaStream *new_stream;

    if ((paErr = Pa_OpenDefaultStream(&new_stream,
        CHANNELS, CHANNELS, paInt16, SAMPLE_RATE,
        BUFFER_SIZE, nullptr, nullptr)) != paNoError) {
        std::cout << "Pa_OpenDefaultStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
    return new_stream;
}

void testAudio::startStream(PaStream *stream)
{
    PaError paErr;

    if ((paErr = Pa_StartStream(stream)) != paNoError) {
        std::cout << "Pa_StartStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
}

std::vector<unsigned short> testAudio::readStream(PaStream* stream)
{
    PaError paErr;
    std::vector<unsigned short> captured(BUFFER_SIZE * CHANNELS);

    if ((paErr = Pa_ReadStream(stream, 
        captured.data(), BUFFER_SIZE)) != paNoError) {
        std::cout << "Pa_ReadStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
    return captured;
}

std::vector<unsigned char> testAudio::encode(std::vector<unsigned short> captured)
{
    std::vector<unsigned char> encoded(BUFFER_SIZE * CHANNELS * 2);
    opus_int32 enc_bytes;

    if ((enc_bytes = opus_encode(_enc, reinterpret_cast<opus_int16 const*>(
        captured.data()), 480, encoded.data(), encoded.size())) < 0) {
        std::cout << "opus_encode failed: " << enc_bytes << std::endl;
        exit(84);
    }
    std::cout << "~~~~~ENCODE: " << enc_bytes << std::endl;
    return encoded;
}

std::vector<unsigned short> testAudio::decode(std::vector<unsigned char> encoded, opus_int32 &dec_bytes)
{
    std::vector<unsigned short> decoded(BUFFER_SIZE * CHANNELS);
    // opus_int32 dec_bytes;
    opus_int32 enc_bytes = 150; //128 de base...

    if ((dec_bytes = opus_decode(_dec, encoded.data(), enc_bytes,
        reinterpret_cast<opus_int16*>(decoded.data()), 480, 0)) < 0) {
        std::cout << "opus_decode failed: " << dec_bytes << std::endl;
        exit(84);
    }
    return decoded;
}

void testAudio::writeStream(PaStream* stream, std::vector<unsigned short> decoded)
{
    PaError paErr;

    if ((paErr = Pa_WriteStream(stream, decoded.data(), BUFFER_SIZE)) != paNoError) {
        std::cout << "Pa_WriteStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
}

void testAudio::stopStream(PaStream* stream)
{
    PaError paErr;

    if ((paErr = Pa_StopStream(stream)) != paNoError) {
        std::cout << "Pa_StopStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
}

void testAudio::closeStream(PaStream* stream)
{
    PaError paErr;

    if ((paErr = Pa_CloseStream(stream)) != paNoError) {
        std::cout << "Pa_CloseStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
}

OpusEncoder *testAudio::getEncoder()
{
    return _enc;
}

OpusDecoder *testAudio::getDecoder()
{
    return _dec;
}


static int patestCallback(const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo *timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData)
{
    paTestData *data = static_cast<paTestData *>(userData);
    float *rptr = &data->recordedSamples[data->frameIndex * 2];
    float *wptr = static_cast<float *>(outputBuffer);
    unsigned int i;
    int finished;
    unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

    if (framesLeft < framesPerBuffer) {
        /* final buffer... */
        for (i = 0; i < framesLeft; ++i) {
            *wptr++ = *rptr++; /* left */
            *wptr++ = *rptr++; /* right */
        }
        for (; i < framesPerBuffer; ++i) {
            *wptr++ = 0; /* left */
            *wptr++ = 0; /* right */
        }
        data->frameIndex += framesLeft;
        finished = paComplete;
    } else {
        for (i = 0; i < framesPerBuffer; ++i) {
            *wptr++ = *rptr++; /* left */
            *wptr++ = *rptr++; /* right */
        }
        data->frameIndex += framesPerBuffer;
        finished = paContinue;
    }
    return finished;
}

PaStream *testAudio::playStream()
{
    // PaError paErr;

    // paErr = Pa_OpenStream(
    //     &stream,
    //     NULL,
    //     &_outputInfo,
    //     44100,
    //     512, //frame_per_buffer
    //     paClipOff,
    //     patestCallback,
    //     &_data);
    // if (paErr != paNoError) {
    //     std::cout << paErr << std::endl;
    //     std::cout << Pa_GetErrorText(paErr) << std::endl;
    //     exit(84);
    // }
    PaError paErr;
    PaStream *stream;

    paErr = Pa_OpenStream(
            &stream,
            NULL, /* no input */
            &_outputInfo,
            44100,
            1024,
            paClipOff,      /* we won't output out of range samples so don't bother clipping them */
            patestCallback, /* no callback, use blocking API */
            &_data ); /* no callback, so no callback userData */
    if (paErr != paNoError) {
        std::cout << paErr << std::endl;
        std::cout << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
    return stream;
}