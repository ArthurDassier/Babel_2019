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
        return nullptr;
    }
    return (c_bits);
}
unsigned char* EncoderSystem::decode(unsigned char *data, int size)
{
    int frame_size = opus_decode(_decode, data, size, _out,
                                    MAX_FRAME_SIZE * CHANNELS * 2, 0);
    unsigned char *pcm_bytes = new unsigned char [MAX_FRAME_SIZE * CHANNELS * 2];

    std::cout << frame_size << std::endl;
    std::cout << _out << std::endl;
    if (frame_size < 0) {
        std::cout << "Can't decode" << std::endl;
        return (nullptr);
    }
    for(int i=0;i<CHANNELS*frame_size;i++)
      {
         pcm_bytes[2*i]=_out[i]&0xFF;
         pcm_bytes[2*i+1]=(_out[i]>>8)&0xFF;
      }
      std::cout << pcm_bytes << std::endl;
    //memcpy(pcm_bytes, _out, size);
    return (pcm_bytes);
}

int EncoderSystem::getEncodeLen() const
{
    return (this->_nbBytes);
}

int main()
{
    EncoderSystem test;
    unsigned char *mapi = (unsigned char *)malloc(sizeof(unsigned char) * 5);

    mapi[0] = 't';
    mapi[1] = 'e';
    mapi[2] = 's';
    mapi[3] = 't';
    mapi[4] = '\0';
    test.encoderCreate();
    test.decoderCreate();
    std::cout << mapi << std::endl;
    unsigned char *mapi2 = test.encode(mapi, 5);
    std::cout << mapi2 << std::endl;
    unsigned char *mapi3 = test.decode(mapi2, test.getEncodeLen());
    std::cout << mapi3 << std::endl;
}