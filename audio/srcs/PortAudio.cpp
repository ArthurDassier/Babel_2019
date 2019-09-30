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

void PortAudio::RecordStream()
{
    paTestData data;

    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        NULL,
        _sample_rate,
        _frame_per_buffer,
        paClipOff,
        nullptr,
        &data
    );
    if (err < 0)
        goto done;
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