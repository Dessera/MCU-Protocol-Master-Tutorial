#include <Arduino.h>

#include <ssdrv/behavior.hpp>
#include <ssdrv/context.hpp>



void setup() {
  using ssdrv::protocol::I2CProtocol;
  using ssdrv::protocol::I2CProtocolConfig;
  using ssdrv::protocol::IProtocol;
  using SSDrvContext = ssdrv::context::Context;
  Serial.begin(115200);

  auto protocol =
      IProtocol::create<I2CProtocol>(I2CProtocolConfig{0x3C, 4, 5, Wire});
  auto context = SSDrvContext::create(std::move(protocol));

  context->initialize();
}

void loop() { delay(1000); }
