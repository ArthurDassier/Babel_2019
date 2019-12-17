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
        std::cout << "captured: ";
        for (auto const& c : captured)
            std::cout << c << ' ';
        encoded = _test.encode(captured);
        decoded = _test.decode(encoded);
        std::cout << "decoded: ";
        for (auto const& c : decoded)
            std::cout << c << ' ';
        _test.writeStream(test, decoded);
        i += BUFFER_SIZE;
    }
    _test.stopStream(stream);
    _test.closeStream(stream);

    return 0;
}