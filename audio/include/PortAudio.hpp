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

#define CHANNELS 2
#define BUFFER_SIZE 480
#define SAMPLE_RATE 48000

class testAudio
{
    public:
        testAudio();
        ~testAudio();

        PaStream *openStream();
        void startStream(PaStream* stream);
        std::vector<unsigned short> readStream(PaStream* stream);
        std::vector<unsigned char> encode(std::vector<unsigned short> captured);
        std::vector<unsigned short> decode(std::vector<unsigned char> encoded);
        void writeStream(PaStream* stream, std::vector<unsigned short> decoded);
        void stopStream(PaStream* stream);
        void closeStream(PaStream* stream);

        OpusEncoder *getEncoder();
        OpusDecoder *getDecoder();

    private:
        OpusEncoder *_enc;
        OpusDecoder* _dec;
};
