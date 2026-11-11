#ifndef NV_STORAGE_H
#define NV_STORAGE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Storage functions do not expose SPI, SD-library, or board-specific types.
bool nv_init(void);
bool nv_is_ready(void);
bool nv_write(const char *name, const uint8_t *data, size_t length);
size_t nv_read(const char *name, uint8_t *data, size_t capacity);
bool nv_verify(const uint8_t *expected, const uint8_t *actual, size_t length);

#ifdef __cplusplus
}
#endif

#endif
