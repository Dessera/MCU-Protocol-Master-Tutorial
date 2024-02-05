#include <Arduino.h>
#include <Wire.h>

#include <ssdrv/behavior.hpp>
#include <ssdrv/command.hpp>
#include <ssdrv/context.hpp>

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
  using SSDrvConfig = ssdrv::context::Config;
  using ssdrv::context::AddressingMode;
  Serial.begin(115200);

  auto config = SSDrvConfig();
  config.set_addressing_mode(AddressingMode::VERTICAL);
  config.set_horizontal_flip(true);
  config.set_vertical_flip(true);


  auto protocol =
      IProtocol::create<I2CProtocol>(Wire, I2CProtocolConfig{0x3C, 4, 5});
  auto context = SSDrvContext::create(std::move(protocol), std::move(config));

  context->initialize();

  // clear screen
  for (int i = 0; i < 128 * 8; i++) {
    write_data(0x00);
  }

  for (int i = 0; i < 128 * 8; i++) {
    write_data(0xFF);
    delay(50);
  }
}

void loop() { delay(1000); }
