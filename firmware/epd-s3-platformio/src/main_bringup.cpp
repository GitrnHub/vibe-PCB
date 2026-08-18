#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "board_pins.h"

SPIClass epdSPI(FSPI);

static void epdWriteCommand(uint8_t c) {
  digitalWrite(PIN_EPD_DC, LOW);
  digitalWrite(PIN_EPD_CS, LOW);
  epdSPI.transfer(c);
  digitalWrite(PIN_EPD_CS, HIGH);
}

static void epdWriteData(uint8_t d) {
  digitalWrite(PIN_EPD_DC, HIGH);
  digitalWrite(PIN_EPD_CS, LOW);
  epdSPI.transfer(d);
  digitalWrite(PIN_EPD_CS, HIGH);
}

static bool epdWaitReady(uint32_t timeout_ms = 30000) {
  const uint32_t start = millis();
  while (digitalRead(PIN_EPD_BUSY) == LOW) {
    if (millis() - start > timeout_ms) return false;
    delay(5);
  }
  return true;
}

static void epdHardwareReset() {
  digitalWrite(PIN_EPD_RST, LOW);
  delay(10);
  digitalWrite(PIN_EPD_RST, HIGH);
  delay(10);
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_EPD_CS, OUTPUT);
  pinMode(PIN_EPD_DC, OUTPUT);
  pinMode(PIN_EPD_RST, OUTPUT);
  pinMode(PIN_EPD_BUSY, INPUT);
  digitalWrite(PIN_EPD_CS, HIGH);
  epdSPI.begin(PIN_EPD_SCLK, -1, PIN_EPD_MOSI, PIN_EPD_CS);
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  epdHardwareReset();
  Serial.println("EPD-S3-Universal board bring-up.");
  Serial.println("Load the exact panel controller init/LUT before sending display data.");
  (void)epdWriteCommand; (void)epdWriteData; (void)epdWaitReady;
}

void loop() { delay(1000); }
