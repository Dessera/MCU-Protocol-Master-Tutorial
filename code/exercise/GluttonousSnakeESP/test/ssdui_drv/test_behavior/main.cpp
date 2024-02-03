#include <Arduino.h>

#include <ssdrv/behavior.hpp>
#include <ssdrv/context.hpp>

void setup() {
  Serial.begin(115200);

  // auto context = SSDrvContext::create(
  //     SSDrvContextConfig(ISSDrvProtocol::create<SSDrvI2CProtocol>(
  //                            SSDrvI2CProtocolConfig{0x3c, 4, 5, Wire}),
  //                        128, 64));

  // SSDrvBehaviorBuilder(context)
  //     .add(SSDrvBehavior::create<SSDrvBehaviorTest>())
  //     .add(SSDrvBehavior::create<SSDrvBehaviorPrintWH>())
  //     .add(SSDrvBehavior::create<SSDrvBehaviorWithParam>(123))
  //     .apply();
}

void loop() { delay(1000); }
