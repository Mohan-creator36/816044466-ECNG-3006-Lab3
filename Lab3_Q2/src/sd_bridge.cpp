// ECNG3006 Lab 3 Q2 — Mohan Latchman — ID: 816044466
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "nv_bridge.h"

extern "C" bool sd_bridge_init(void)
{
    // Tested on this MKR Zero using the board's default SD chip select.
    return SD.begin();
}

extern "C" bool sd_bridge_write(const char *name,
                                 const uint8_t *data,
                                 size_t length)
{
    if (name == nullptr || data == nullptr || length == 0U) {
        return false;
    }

    // FILE_WRITE appends. Delete the previous test file to replace it.
    if (SD.exists(name) && !SD.remove(name)) {
        return false;
    }

    File file = SD.open(name, FILE_WRITE);
    if (!file) {
        return false;
    }

    size_t written = file.write(data, length);
    file.flush();   // Include completion of buffered writes.
    file.close();
    return written == length;
}

extern "C" size_t sd_bridge_read(const char *name,
                                  uint8_t *data,
                                  size_t capacity)
{
    if (name == nullptr || data == nullptr || capacity == 0U) {
        return 0U;
    }

    File file = SD.open(name, FILE_READ);
    if (!file) {
        return 0U;
    }

    // Require an exact file length, rather than accepting stale extra data.
    if (file.size() != capacity) {
        file.close();
        return 0U;
    }

    size_t total = 0U;
    while (total < capacity && file.available()) {
        int value = file.read();
        if (value < 0) {
            break;
        }
        data[total++] = static_cast<uint8_t>(value);
    }
    file.close();
    return total;
}
