/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** PortAudio.cpp
*/

#include "PortAudio.hpp"

PortAudio::PortAudio():
    sample_rate(44100)
{
    err = Pa_Initialize();
    if (err != paNoError)
        goto done;
}

PortAudio::~PortAudio()
{
}

void PortAudio::SetInputParameters()
{
    inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice) {
        std::cer << "Error: No default input device." << std::endl;
        return;
    }
    inputParameters.channelCount = 2;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;
}

void PortAudio::SetData(int num_seconds, int sample_rate, int num_channels)
{
    int numSamples;
    int numBytes;

    data.maxFrameIndex = num_seconds * sample_rate; /* Record for a few seconds. */
    data.frameIndex = 0;
    numSamples = data.maxFrameIndex * num_channels;
    numBytes = numSamples * sizeof(float);
    data.recordedSamples = (float *)malloc(numBytes);

    for (i = 0; i < numSamples; i++)
        data.recordedSamples[i] = 0;
}

void PortAudio::SetOutputParameters()
{
    outputParameters.device = Pa_GetDefaultInputDevice();
    if (outputParameters.device == paNoDevice) {
        std::cer << "Error: No default input device." << std::endl;
        return;
    }
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
}

void PortAudio::CloseStream()//PaStream *stream)
{
    err = Pa_CloseStream(stream);
    if (err != paNoError)
        goto done;
}

// int recordCallback(const void *inputBuffer,
//                     void *outputBuffer,
//                     unsigned long framesPerBuffer,
//                     const PaStreamCallbackTimeInfo *timeInfo,
//                     PaStreamCallbackFlags statusFlags,
//                     void *userData)
// {
//     paTestData *data = (paTestData *)userData;
//     const float *rptr = (const float *)inputBuffer;
//     float *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
//     long framesToCalc = 0;
//     long i = 0;
//     int finished = 0;
//     unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

//     if (framesLeft < framesPerBuffer) {
//         framesToCalc = framesLeft;
//         finished = paComplete;
//     } else {
//         framesToCalc = framesPerBuffer;
//         finished = paContinue;
//     }

//     if (inputBuffer == NULL) {
//         for (i = 0; i < framesToCalc; i++) {
//             *wptr++ = SAMPLE_SILENCE; /* left */
//             if (NUM_CHANNELS == 2)
//                 *wptr++ = SAMPLE_SILENCE; /* right */
//         }
//     } else {
//         for (i = 0; i < framesToCalc; i++) {
//             *wptr++ = *rptr++; /* left */
//             if (NUM_CHANNELS == 2)
//                 *wptr++ = *rptr++; /* right */
//         }
//     }
//     data->frameIndex += framesToCalc;
//     return finished;
// }

void PortAudio::RecordStream()
{
    // paTestData data; // a remplir

    // data.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
    // data.frameIndex = 0;
    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        NULL,
        _sample_rate,
        _frame_per_buffer,
        paClipOff,
        recordCallback,
        &data);
    if (err < 0)
        return;
}

void PortAudio::PlayStream()
{

}

void PortAudio::setSampleRate(short sample_rate) const
{
    _sample_rate = sample_rate;
}

void PortAudio::setFramePerBuffer(short frame_per_buffer) const
{
    _frame_per_buffer = frame_per_buffer;
}