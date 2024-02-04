#pragma once

#include "ssdrv/behavior.hpp"
#include "ssdrv/context.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace command {

class Command : public behavior::IBehavior {
 public:
  static constexpr uint8_t COMMAND_SIGNAL = 0x00;

  void apply(std::shared_ptr<context::Context> context) override {
    context->protocol().write(COMMAND_SIGNAL);
  };

  void apply(std::shared_ptr<context::Context> context, uint8_t data) {
    context->protocol().write(COMMAND_SIGNAL);
    context->protocol().write(data);
  };
};

}  // namespace command

SSDRV_NS_END
