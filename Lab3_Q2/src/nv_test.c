// ECNG3006 Lab 3 Q2 — Mohan Latchman — ID: 816044466
#include "nv_test.h"
#include "nv_storage.h"

#define MAX_TEST_BYTES 512U
#define TEST_FILE "NVTEST.DAT"

bool nv_test_run(size_t data_length, uint32_t repetitions,
                 nv_test_result_t *result)
{
    static uint8_t expected[MAX_TEST_BYTES];
    static uint8_t received[MAX_TEST_BYTES];

    if (result == NULL || data_length == 0U ||
        data_length > MAX_TEST_BYTES || repetitions == 0U) {
        return false;
    }

    *result = (nv_test_result_t){0};
    if (!nv_is_ready()) {
        return false;
    }

    for (uint32_t run = 0U; run < repetitions; ++run) {
        result->attempts++;

        // Each run uses different bytes to detect stale data.
        for (size_t i = 0U; i < data_length; ++i) {
            expected[i] = (uint8_t)((i * 17U + run) & 0xFFU);
            received[i] = 0U;
        }

        if (!nv_write(TEST_FILE, expected, data_length)) {
            result->write_failures++;
            continue;
        }

        if (nv_read(TEST_FILE, received, data_length) != data_length) {
            result->read_failures++;
            continue;
        }

        if (!nv_verify(expected, received, data_length)) {
            result->verify_failures++;
            continue;
        }

        result->passed++;
    }

    return result->passed == repetitions;
}
