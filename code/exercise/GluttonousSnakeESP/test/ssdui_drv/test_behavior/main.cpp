#include <Arduino.h>

#include <ssdrv/behavior.hpp>
#include <ssdrv/context.hpp>

void setup() {
  using ssdrv::protocol::I2CProtocol;
  using ssdrv::protocol::I2CProtocolConfig;
  using SSDrvContext = ssdrv::context::Context;
  Serial.begin(115200);

  auto protocol =
      I2CProtocol::create<I2CProtocol>(I2CProtocolConfig{0x3C, 4, 5, Wire});
  auto context = SSDrvContext::create(protocol);
}

void loop() { delay(1000); }
