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
#include "opus.h"

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

        bool _isFreeable;
};

#define CHANNELS 2
#define BUFFER_SIZE 480
#define SAMPLE_RATE 48000

class testAudio
{
    public:
        testAudio();
        ~testAudio();

        void initOutputInfo();
        void initData(int, int, int);
        PaStream *openStream();
        void startStream(PaStream* stream);
        std::vector<unsigned short> readStream(PaStream* stream);
        std::vector<unsigned char> encode(std::vector<unsigned short> captured);
        std::vector<unsigned short> decode(std::vector<unsigned char> encoded, opus_int32 &dec_bytes);
        void writeStream(PaStream* stream, std::vector<unsigned short> decoded);
        void playStream(PaStream *stream);
        void stopStream(PaStream* stream);
        void closeStream(PaStream* stream);

        OpusEncoder *getEncoder();
        OpusDecoder *getDecoder();

    private:
        OpusEncoder *_enc;
        OpusDecoder* _dec;
        PaStreamParameters _outputInfo;
        paTestData _data;
};
