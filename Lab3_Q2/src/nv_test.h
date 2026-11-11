#ifndef NV_TEST_H
#define NV_TEST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t attempts;
    uint32_t passed;
    uint32_t write_failures;
    uint32_t read_failures;
    uint32_t verify_failures;
} nv_test_result_t;

// Runs repeated write -> read -> compare tests using C code.
bool nv_test_run(size_t data_length, uint32_t repetitions,
                 nv_test_result_t *result);

#ifdef __cplusplus
}
#endif

#endif
