/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** PortAudio.hpp
*/

#ifndef PORTAUDIO_HPP_
#define PORTAUDIO_HPP_

#include "portaudio.h"

class PortAudio {
    public:
        PortAudio();
        ~PortAudio();

        void SetInputParameters();
        void SetOutputParameters();

        void CloseStream();
        void RecordStream();
        void PlayStream();

        void setSampleRate(short) const;
        void setFramePerBuffer(short) const;

    private:
        PaError err;
        PaStream *stream;
        PaStreamParameters inputParameters;
        PaStreamParameters outputParameters;
        paTestData data;

        short _sample_rate;
        short _frame_per_buffer;
};

#endif /* !PORTAUDIO_HPP_ */
