/*
** EPITECH PROJECT, 2019
** OpusE.hpp
** File description:
** OpusE.hpp
*/

#pragma once

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

#include "/home/adassier/.conan/data/opus/1.3.1/bincrafters/stable/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/include/opus/opus.h"

#define FRAME_SIZE (960)
#define SAMPLE_RATE (48000)
#define CHANNELS (2)
#define APPLICATION OPUS_APPLICATION_VOIP

#define MAX_FRAME_SIZE (6*960)

class EncoderSystem
{
    private:
        OpusEncoder *_encode;
        OpusDecoder *_decode;

        opus_int16 _in[FRAME_SIZE*CHANNELS];
        opus_int16 _out[MAX_FRAME_SIZE*CHANNELS];
        int _nbBytes;


    public:
        EncoderSystem();
        ~EncoderSystem();

        bool encoderCreate();
        bool decoderCreate();

        unsigned char* encode(unsigned char *, int);
        unsigned char* decode(unsigned char *, int);

        int getEncodeLen() const;
};