#pragma once

#include "ssdrv/behavior.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace command {

/**
 * @brief 命令基类，所有命令都继承自此类
 *
 */
class Command : public behavior::IBehavior {
 public:
  inline static constexpr uint8_t COMMAND_SIGNAL = 0x00;

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
