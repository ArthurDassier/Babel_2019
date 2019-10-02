/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** PortAudio.hpp
*/

#pragma once

#include <stdio.h>
#include <iostream>

#include "portaudio.h"

#define SAMPLE_SILENCE (0.0f)


typedef struct {
    int frameIndex;
    int maxFrameIndex;
    float *recordedSamples;
} paTestData;

class PortAudio {
    public:
        PortAudio();
        ~PortAudio();

        void SetInputParameters();
        void SetOutputParameters();
        void SetData(int, int, int);

        void StartStream(PaStream *);
        void CloseStream(PaStream *);
        PaStream *RecordStream();

        void PlayStream(PaStream *);

        void setSampleRate(short);
        void setFramePerBuffer(short);
        void setDataFrameIndex();

    private:
        PaError err;
        PaStreamParameters inputParameters;
        PaStreamParameters outputParameters;
        paTestData _data;

        short _sample_rate;
        short _frame_per_buffer;
};
