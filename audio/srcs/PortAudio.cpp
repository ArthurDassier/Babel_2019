/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** PortAudio.cpp
*/

#include "PortAudio.hpp"

PortAudio::PortAudio():
    _sample_rate(44100)
{
    err = Pa_Initialize();
    if (err != paNoError)
        exit(84);
}

PortAudio::~PortAudio()
{
    Pa_Terminate();
    if (_data.recordedSamples)
        free(_data.recordedSamples);
}

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

void PortAudio::SetData(int num_seconds, int sample_rate, int num_channels)
{
    int numSamples;
    int numBytes;

    _data.maxFrameIndex = num_seconds * sample_rate;
    _data.frameIndex = 0;
    numSamples = _data.maxFrameIndex * num_channels;
    numBytes = numSamples * sizeof(float);
    _data.recordedSamples = (float *)malloc(numBytes);

    for (int i = 0; i < numSamples; ++i)
        _data.recordedSamples[i] = 0;
}

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

void PortAudio::StartStream()
{
    err = Pa_StartStream(stream);
    if (err != paNoError)
        exit(84);
}

void PortAudio::CloseStream()//PaStream *stream)
{
    err = Pa_CloseStream(stream);
    if (err != paNoError)
        exit(84);
}

int recordCallback(const void *inputBuffer,
                    void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData)
{
    paTestData *data = (paTestData *)userData;
    const float *rptr = (const float *)inputBuffer;
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

void PortAudio::RecordStream()
{
    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        NULL,
        _sample_rate,
        _frame_per_buffer,
        paClipOff,
        recordCallback,
        &_data);
    if (err < 0)
        exit(84);
}

static int playCallback(const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo *timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData)
{
    paTestData *data = (paTestData *)userData;
    float *rptr = &data->recordedSamples[data->frameIndex * 2];
    float *wptr = (float *)outputBuffer;
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


void PortAudio::PlayStream()
{
    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        NULL,
        _sample_rate,
        _frame_per_buffer,
        paClipOff,
        playCallback,
        &_data);
    if (err < 0)
        exit(84);
}

void PortAudio::setSampleRate(short sample_rate)
{
    _sample_rate = sample_rate;
}

void PortAudio::setFramePerBuffer(short frame_per_buffer)
{
    _frame_per_buffer = frame_per_buffer;
}

int main()
{
    PortAudio test;
    test.SetInputParameters();
    std::cout << "1" << std::endl;
    test.SetData(5, 44100, 2);
    std::cout << "2" << std::endl;
    test.RecordStream();
    std::cout << "3" << std::endl;
    test.StartStream();
    std::cout << "4" << std::endl;
    Pa_Sleep(1000);
    std::cout << "5" << std::endl;
    test.CloseStream();
    std::cout << "6" << std::endl;
    test.SetOutputParameters();
    std::cout << "7" << std::endl;
    test.PlayStream();
    std::cout << "8" << std::endl;
    test.StartStream();
    std::cout << "9" << std::endl;
    test.CloseStream();
    std::cout << "10" << std::endl;
    return (1);
}