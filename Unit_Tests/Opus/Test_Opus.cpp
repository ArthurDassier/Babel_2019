/*
** EPITECH PROJECT, 2019
** tests_Opus.cpp
** File description:
** tests_4001
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "OpusE.hpp"

Test(tests_Opus, test_encoderCreate)
{
    EncoderSystem test;

    cr_assert_eq(test.encoderCreate(), true);
}

Test(tests_Opus, test_decoderCreate)
{
    EncoderSystem test;

    cr_assert_eq(test.decoderCreate(), true);
}

Test(tests_Opus, test_encode)
{
    EncoderSystem test;
    unsigned char *mapi = (unsigned char *)malloc(sizeof(unsigned char) * 5);

    mapi[0] = 't';
    mapi[1] = 'e';
    mapi[2] = 's';
    mapi[3] = 't';
    mapi[4] = '\0';
    cr_assert(test.encode(mapi, 4) != nullptr);
}

// Test(tests_Opus, test_decode)
// {
//     EncoderSystem test;

//     cr_assert(test.decode("test", 4) != nullptr);
// }
