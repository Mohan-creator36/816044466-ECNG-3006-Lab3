// ECNG3006 Lab 3 Q2 — Mohan Latchman — ID: 816044466
#include <Arduino.h>
#include "nv_storage.h"
#include "nv_test.h"

static void print_test_results(size_t bytes, uint32_t runs)
{
    nv_test_result_t results;
    bool success = nv_test_run(bytes, runs, &results);

    Serial.print(bytes);
    Serial.print(" byte test: ");
    Serial.print(results.passed);
    Serial.print("/");
    Serial.print(results.attempts);
    Serial.println(success ? " PASSED" : " FAILED");

    Serial.print("  Write failures: ");
    Serial.println(results.write_failures);
    Serial.print("  Read failures: ");
    Serial.println(results.read_failures);
    Serial.print("  Verification failures: ");
    Serial.println(results.verify_failures);
}

void setup()
{
    Serial.begin(115200);
    unsigned long start = millis();
    while (!Serial && millis() - start < 5000UL) {
        delay(10);
    }

    Serial.println("=== ECNG3006 LAB 3 Q2 ===");
    if (!nv_init()) {
        Serial.println("SD initialization FAILED.");
        return;
    }

    Serial.println("SD initialization successful.");
    print_test_results(64U, 10U);
    print_test_results(512U, 10U);
    Serial.println("Tests complete; NVTEST.DAT remains on the card.");
}

void loop()
{
    // Test runs once after boot/reset.
}
