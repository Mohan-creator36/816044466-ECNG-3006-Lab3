#ifndef NV_BRIDGE_H
#define NV_BRIDGE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// C-compatible hardware bridge implemented in sd_bridge.cpp.
bool sd_bridge_init(void);
bool sd_bridge_write(const char *name, const uint8_t *data, size_t length);
size_t sd_bridge_read(const char *name, uint8_t *data, size_t capacity);

#ifdef __cplusplus
}
#endif

#endif
