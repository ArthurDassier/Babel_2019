/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** PortAudio.cpp
*/

#include "PortAudio.hpp"

testAudio::testAudio()
{
    // initialize opus
    int opusErr;

    _enc = opus_encoder_create(
        SAMPLE_RATE, CHANNELS, OPUS_APPLICATION_AUDIO, &opusErr);
    if (opusErr != OPUS_OK) {
        std::cout << "opus_encoder_create failed: " << opusErr << std::endl;
        exit(84);
    }
    _dec = opus_decoder_create(
        SAMPLE_RATE, CHANNELS, &opusErr);
    if (opusErr != OPUS_OK) {
        std::cout << "opus_decoder_create failed: " << opusErr << std::endl;
        exit(84);
    }

    // initialize portaudio
    PaError paErr;

    if ((paErr = Pa_Initialize()) != paNoError) {
        std::cout << "Pa_Initialize failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
}

testAudio::~testAudio()
{
    PaError paErr;

    if ((paErr = Pa_Terminate()) != paNoError)  {
        std::cout << "Pa_Terminate failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
    opus_encoder_destroy(_enc);
    opus_decoder_destroy(_dec);
}

PaStream *testAudio::openStream()
{
    PaError paErr;
    PaStream *new_stream;

    if ((paErr = Pa_OpenDefaultStream(&new_stream,
        CHANNELS, CHANNELS, paInt16, SAMPLE_RATE,
        BUFFER_SIZE, nullptr, nullptr)) != paNoError) {
        std::cout << "Pa_OpenDefaultStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
    return new_stream;
}

void testAudio::startStream(PaStream *stream)
{
    PaError paErr;

    if ((paErr = Pa_StartStream(stream)) != paNoError) {
        std::cout << "Pa_StartStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
}

std::vector<unsigned short> testAudio::readStream(PaStream* stream)
{
    PaError paErr;
    std::vector<unsigned short> captured(BUFFER_SIZE * CHANNELS);

    if ((paErr = Pa_ReadStream(stream, 
        captured.data(), BUFFER_SIZE)) != paNoError) {
        std::cout << "Pa_ReadStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
    return captured;
}

std::vector<unsigned char> testAudio::encode(std::vector<unsigned short> captured)
{
    std::vector<unsigned char> encoded(BUFFER_SIZE * CHANNELS * 2);
    opus_int32 enc_bytes;

    if ((enc_bytes = opus_encode(_enc, reinterpret_cast<opus_int16 const*>(
        captured.data()), 480, encoded.data(), encoded.size())) < 0) {
        std::cout << "opus_encode failed: " << enc_bytes << std::endl;
        exit(84);
    }
    std::cout << "~~~~~ENCODE: " << enc_bytes << std::endl;
    return encoded;
}

std::vector<unsigned short> testAudio::decode(std::vector<unsigned char> encoded)
{
    std::vector<unsigned short> decoded(BUFFER_SIZE * CHANNELS);
    opus_int32 dec_bytes;
    opus_int32 enc_bytes = 150; //128 de base...

    if ((dec_bytes = opus_decode(_dec, encoded.data(), enc_bytes,
        reinterpret_cast<opus_int16*>(decoded.data()), 480, 0)) < 0) {
        std::cout << "opus_decode failed: " << dec_bytes << std::endl;
        exit(84);
    }
    return decoded;
}

void testAudio::writeStream(PaStream* stream, std::vector<unsigned short> decoded)
{
    PaError paErr;

    if ((paErr = Pa_WriteStream(stream, decoded.data(), BUFFER_SIZE)) != paNoError) {
        std::cout << "Pa_WriteStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        // exit(84);
    }
}

void testAudio::stopStream(PaStream* stream)
{
    PaError paErr;

    if ((paErr = Pa_StopStream(stream)) != paNoError) {
        std::cout << "Pa_StopStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
}

void testAudio::closeStream(PaStream* stream)
{
    PaError paErr;

    if ((paErr = Pa_CloseStream(stream)) != paNoError) {
        std::cout << "Pa_CloseStream failed: " << Pa_GetErrorText(paErr) << std::endl;
        exit(84);
    }
}

OpusEncoder *testAudio::getEncoder()
{
    return _enc;
}

OpusDecoder *testAudio::getDecoder()
{
    return _dec;
}

