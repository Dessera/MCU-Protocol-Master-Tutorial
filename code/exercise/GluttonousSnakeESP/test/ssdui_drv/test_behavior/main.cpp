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
    Serial.println("SSDrvBehaviorPrintWH::apply");
    Serial.print("width: ");
    Serial.println(context->config().width);
    Serial.print("height: ");
    Serial.println(context->config().height);
  }
};

class SSDrvBehaviorWithParam : public SSDrvBehavior {
 private:
  int m_param{0};

 public:
  explicit SSDrvBehaviorWithParam(int param) : m_param(param) {}
  void apply(std::shared_ptr<SSDrvContext> context) override {
    Serial.println("SSDrvBehaviorWithParam::apply");
    Serial.print("param: ");
    Serial.println(m_param);
  }
};

void setup() {
  Serial.begin(115200);

  auto context = SSDrvContext::create(
      SSDrvContextConfig(ISSDrvProtocol::create<SSDrvI2CProtocol>(
                             SSDrvI2CProtocolConfig{0x3c, 4, 5, Wire}),
                         128, 64));

  SSDrvBehaviorBuilder(context)
      .add(SSDrvBehavior::create<SSDrvBehaviorTest>())
      .add(SSDrvBehavior::create<SSDrvBehaviorPrintWH>())
      .add(SSDrvBehavior::create<SSDrvBehaviorWithParam>(123))
      .apply();
}

void loop() { delay(1000); }
