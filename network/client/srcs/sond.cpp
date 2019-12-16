#include "Client.hpp"

int main()
{
    testAudio _test;
    PaStream *stream;
    PaStream *test;
    std::vector<unsigned short> captured(BUFFER_SIZE * CHANNELS);
    std::vector<unsigned short> decoded(BUFFER_SIZE * CHANNELS);
    std::vector<unsigned char> encoded(BUFFER_SIZE * CHANNELS * 2);
    opus_int32 dec_bytes;
    int i = 0;

    stream = _test.openStream();
    _test.startStream(stream);
    test = _test.openStream();
    _test.startStream(test);

    while (i < SAMPLE_RATE * 5) { //5-> les secondes que ca dure
        captured = _test.readStream(stream);
        encoded = _test.encode(captured);
        /* envoyer */
        // send = reinterpret_cast<char*>(encoded.data());
        // socket->writeDatagram(send, _add, _port);
        decoded = _test.decode(encoded, dec_bytes);
        _test.writeStream(test, decoded);
        i += BUFFER_SIZE;
    }
    _test.stopStream(stream);
    _test.closeStream(stream);

    return 0;
}