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