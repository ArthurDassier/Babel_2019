/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** PortAudio.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <stdio.h>
#include <vector>

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

        // readStream(void)

        void SetInputParameters();
        void SetOutputParameters();
        void SetData(int, int, int);

        void StartStream(PaStream *);
        void CloseStream(PaStream *);

        std::vector<unsigned short> readStream(PaStream *);
        PaStream *RecordStream();

        PaStream *writeStream(std::vector<unsigned short>);

        void PlayStream(PaStream *);

        void setSampleRate(short);
        void setFramePerBuffer(short);
        void setDataFrameIndex();

    private:
        PaError _err;
        PaStreamParameters _inputParameters;
        PaStreamParameters _outputParameters;
        paTestData _data;

        short _sample_rate;
        short _frame_per_buffer;
};
