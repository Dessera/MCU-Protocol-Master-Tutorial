#include <Arduino.h>
#include <Wire.h>

#include <ssdrv/behavior.hpp>
#include <ssdrv/command.hpp>
#include <ssdrv/context.hpp>

void write_command(uint8_t command) {
  Wire.beginTransmission(0x3C);
  Wire.write(0x00);  // command mode
  Wire.write(command);
  auto res = Wire.endTransmission();
}

void write_data(uint8_t data) {
  Wire.beginTransmission(0x3C);
  Wire.write(0x40);  // data mode
  Wire.write(data);
  auto res = Wire.endTransmission();
}

void setup() {
  using namespace ssdrv::command;
  using ssdrv::protocol::I2CProtocol;
  using ssdrv::protocol::I2CProtocolConfig;
  using ssdrv::protocol::IProtocol;
  using SSDrvContext = ssdrv::context::Context;
  Serial.begin(115200);

  // delay(100);

  auto protocol =
      IProtocol::create<I2CProtocol>(Wire, I2CProtocolConfig{0x3C, 4, 5});
  auto context = SSDrvContext::create(std::move(protocol));

  context->initialize();
}

void loop() { delay(1000); }
