/*
** EPITECH PROJECT, 2019
** OpusE.cpp
** File description:
** OpusE.cpp
*/

#include "OpusE.hpp"

EncoderSystem::EncoderSystem()
{
}

EncoderSystem::~EncoderSystem()
{
    opus_encoder_destroy(_encode);
    opus_decoder_destroy(_decode);
}

bool EncoderSystem::encoderCreate()
{
    int error;

    if ((_encode = opus_encoder_create(SAMPLE_RATE,
                                        CHANNELS,
                                        OPUS_APPLICATION_VOIP,
                                        &error)) == NULL) {
        std::cerr << "Can't create encode" << std::endl;
        return (false);
    }
    return (true);
}

bool EncoderSystem::decoderCreate()
{
    int error;

    if ((_decode = opus_decoder_create(SAMPLE_RATE, CHANNELS, &error)) == NULL) {
        std::cerr << "Can't create decoder" << std::endl;
        return (false);
    }
    return (true);
}

unsigned char* EncoderSystem::encode(unsigned char *data, int size)
{
    unsigned char *c_bits = new unsigned char [size];

    memcpy(_in, data, size);
    _nbBytes = opus_encode(_encode, _in, FRAME_SIZE, c_bits, size);
    if (_nbBytes < 0) {
        std::cerr << "Can't decode" << std::endl;
        return NULL;
    }
    return (c_bits);
}
unsigned char* EncoderSystem::decode(unsigned char *data, int size)
{

    int frame_size = opus_decode(_decode, data, size, _out,
                                    MAX_FRAME_SIZE * CHANNELS * 2, 0);
    unsigned char *pcm_bytes = new unsigned char [MAX_FRAME_SIZE * CHANNELS * 2];

    if (frame_size < 0) {
        std::cerr << "Can't decode" << std::endl;
        return (NULL);
    }
    memcpy(pcm_bytes, _out, size);
    return (pcm_bytes);
}

int EncoderSystem::getEncodeLen() const
{
    return (this->_nbBytes);
}

int main()
{
    return 0;
}