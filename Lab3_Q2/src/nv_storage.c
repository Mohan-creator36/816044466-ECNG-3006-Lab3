// ECNG3006 Lab 3 Q2 — Mohan Latchman — ID: 816044466
#include "nv_storage.h"
#include "nv_bridge.h"

static bool storage_ready = false;

bool nv_init(void)
{
    storage_ready = sd_bridge_init();
    return storage_ready;
}

bool nv_is_ready(void)
{
    return storage_ready;
}

bool nv_write(const char *name, const uint8_t *data, size_t length)
{
    if (!storage_ready || name == NULL || data == NULL || length == 0U) {
        return false;
    }
    return sd_bridge_write(name, data, length);
}

size_t nv_read(const char *name, uint8_t *data, size_t capacity)
{
    if (!storage_ready || name == NULL || data == NULL || capacity == 0U) {
        return 0U;
    }
    return sd_bridge_read(name, data, capacity);
}

bool nv_verify(const uint8_t *expected, const uint8_t *actual, size_t length)
{
    if (expected == NULL || actual == NULL || length == 0U) {
        return false;
    }
    for (size_t i = 0U; i < length; ++i) {
        if (expected[i] != actual[i]) {
            return false;
        }
    }
    return true;
}
