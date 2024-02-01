#include <Arduino.h>

#include <ssdui/behavior.hpp>
#include <ssdui/context.hpp>

class SSDrvBehaviorTest : public SSDrvBehavior {
 public:
  void apply(std::shared_ptr<SSDrvContext> context) override {
    Serial.println("SSDrvBehaviorTest::apply");
  }
};

class SSDrvBehaviorPrintWH : public SSDrvBehavior {
 public:
  void apply(std::shared_ptr<SSDrvContext> context) override {
    Serial.println("SSDrvBehaviorPrintWH::WH");
    Serial.print("width: ");
    Serial.println(context->config().width);
    Serial.print("height: ");
    Serial.println(context->config().height);
  }
};

void setup() {
  Serial.begin(115200);

  auto protocol = std::unique_ptr<ISSDrvProtocol>(
      new SSDrvI2CProtocol(SSDrvI2CProtocolConfig{0x3c, 4, 5, Wire}));
  auto context = std::make_shared<SSDrvContext>(
      SSDrvContextConfig(std::move(protocol), 128, 64));

  SSDrvBehaviorBuilder(context)
      .add(std::unique_ptr<SSDrvBehavior>(new SSDrvBehaviorTest()))
      .add(std::unique_ptr<SSDrvBehavior>(new SSDrvBehaviorPrintWH()))
      .apply();
}

void loop() {
  delay(1000);
}
