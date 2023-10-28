#include "doctest/doctest.h"

#include "spdlog/spdlog.h"

#include "../src/a54ecsd.h"

/*
 * Test Data has been pulled from "3GPP TS 55.217 V6.1.0 (2002-12)".
 */

TEST_CASE("Testing the A54ECSD class with (4.7) Test Set 5") {
    spdlog::set_level(spdlog::level::info);
    uint8_t t_kc[16] = {0xD3, 0xC5, 0xD5, 0x92, 0x32, 0x7F, 0xB1, 0x1C, 0x40, 0x35, 0xC6, 0x68, 0x0A, 0xF8, 0xC6, 0xD1};
    uint8_t t_klen = 128;
    uint32_t t_count = 0x0A59B4;

    kneedeepbts::crypto::A54ECSD dut_a54ecsd(t_kc, t_klen, t_count);
    dut_a54ecsd.run();

    uint8_t expected_block1[44] = {
            0x98, 0x87, 0x36, 0x8E, 0x48, 0x25, 0x7E, 0x17, 0x2E, 0xFF, 0x14, 0xBA,
            0xBC, 0x11, 0x4D, 0xB5, 0x15, 0x9C, 0x2E, 0x3D, 0x05, 0x21, 0xAF, 0xCD,
            0x04, 0x48, 0x79, 0x95, 0x98, 0x9C, 0x35, 0xF8, 0xF2, 0x6C, 0x00, 0x5D,
            0x4C, 0xBD, 0xE2, 0xE3, 0x9F, 0x18, 0x57, 0x20
    };
    uint8_t expected_block2[44] = {
            0xD6, 0xDD, 0x0D, 0x2F, 0xA8, 0x5C, 0xF7, 0xC5, 0xFF, 0x04, 0xCD, 0xEC,
            0x12, 0x31, 0x8F, 0x01, 0xD4, 0x18, 0xF4, 0xBB, 0xBF, 0x5F, 0xAF, 0xF8,
            0xDF, 0xEA, 0x66, 0xC9, 0x24, 0x7A, 0x8F, 0x64, 0xDE, 0xBF, 0x71, 0xA3,
            0x64, 0xFB, 0xB3, 0x6F, 0x39, 0x16, 0x1E, 0xC0
    };

    for (int i = 0; i < 44; i++) {
        CHECK(expected_block1[i] == dut_a54ecsd.m_block1[i]);
        CHECK(expected_block2[i] == dut_a54ecsd.m_block2[i]);
    }
}
