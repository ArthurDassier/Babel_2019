/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** PortAudio.cpp
*/

#include "PortAudio.hpp"

/*!
 * \fn PortAudio::PortAudio()
 * \brief ?
 *
 * \param void
 */

PortAudio::PortAudio():
    _sample_rate(44100),
    _frame_per_buffer(512)
{
    err = Pa_Initialize();
    if (err != paNoError)
        exit(84);
}

/*!
 * \fn PortAudio::~PortAudio()
 * \brief ?
 *
 * \param void
 */

PortAudio::~PortAudio()
{
    Pa_Terminate();
    if (_data.recordedSamples)
        free(_data.recordedSamples);
}

/*!
 * \fn PortAudio::SetInputParameters()
 * \brief ?
 *
 * \param void
 */

void PortAudio::SetInputParameters()
{
    inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice) {
        std::cerr << "Error: No default input device." << std::endl;
        return;
    }
    inputParameters.channelCount = 2;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;
}

/*!
 * \fn PortAudio::SetData()
 * \brief ?
 *
 * \param int num_seconds, int sample_rate, int num_channels
 */

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
}

/*!
 * \fn PortAudio::SetOutputParameters()
 * \brief ?
 *
 * \param void
 */

void PortAudio::SetOutputParameters()
{
    outputParameters.device = Pa_GetDefaultInputDevice();
    if (outputParameters.device == paNoDevice) {
        std::cerr << "Error: No default input device." << std::endl;
        return;
    }
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
}

/*!
 * \fn PortAudio::StartStream()
 * \brief ?
 *
 * \param PaStream *stream
 */

void PortAudio::StartStream(PaStream *stream)
{
    err = Pa_StartStream(stream);
    if (err != paNoError)
        exit(84);
}

/*!
 * \fn PortAudio::CloseStream()
 * \brief ?
 *
 * \param PaStream *stream
 */

void PortAudio::CloseStream(PaStream *stream)
{
    err = Pa_CloseStream(stream);
    if (err != paNoError)
        exit(84);
}

/*!
 * \fn recordCallback()
 * \brief ?
 *
 * \param const void *inputBuffer,
                    void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData
 */

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

/*!
 * \fn PortAudio::RecordStream()
 * \brief ?
 *
 * \param void
 */

PaStream *PortAudio::RecordStream()
{
    PaStream *stream;

    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        NULL,
        44100,
        _frame_per_buffer,
        paClipOff,
        recordCallback,
        &_data);
    if (err != paNoError) {
        std::cout << err << std::endl;
        std::cout << Pa_GetErrorText(err) << std::endl;
        exit(84);
    }
    return stream;
}

/*!
 * \fn playCallback()
 * \brief ?
 *
 * \param const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo *timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData
 */

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

/*!
 * \fn PortAudio::PlayStream()
 * \brief ?
 *
 * \param PaStream *stream
 */

void PortAudio::PlayStream(PaStream *stream)
{
    err = Pa_OpenStream(
        &stream,
        NULL,
        &outputParameters,
        44100,
        _frame_per_buffer,
        paClipOff,
        playCallback,
        &_data);
    if (err != paNoError) {
        std::cout << err << std::endl;
        std::cout << Pa_GetErrorText(err) << std::endl;
        exit(84);
    }
}

/*!
 * \fn PortAudio::setSampleRate()
 * \brief ?
 *
 * \param short sample_rate
 */

void PortAudio::setSampleRate(short sample_rate)
{
    _sample_rate = sample_rate;
}

/*!
 * \fn PortAudio::setFramePerBuffer()
 * \brief ?
 *
 * \param short frame_per_buffer
 */

void PortAudio::setFramePerBuffer(short frame_per_buffer)
{
    _frame_per_buffer = frame_per_buffer;
}

/*!
 * \fn PortAudio::setDataFrameIndex()
 * \brief ?
 *
 * \param void
 */

void PortAudio::setDataFrameIndex()
{
    _data.frameIndex = 0;
}

int main()
{
    PortAudio test;
    PaStream *stream;
    test.SetInputParameters();
    std::cout << "1" << std::endl;
    test.SetData(5, 44100, 2);
    std::cout << "2" << std::endl;
    stream = test.RecordStream();
    std::cout << "3" << std::endl;
    test.StartStream(stream);
    std::cout << "4" << std::endl;
    Pa_Sleep(3000);
    std::cout << "5" << std::endl;
    test.CloseStream(stream);
    std::cout << "6" << std::endl;
    test.SetOutputParameters();
    test.setDataFrameIndex();
    std::cout << "7" << std::endl;
    test.PlayStream(stream);
    std::cout << "8" << std::endl;
    test.StartStream(stream);
    Pa_Sleep(3000);
    std::cout << "9" << std::endl;
    test.CloseStream(stream);
    std::cout << "10" << std::endl;
    return (0);
}