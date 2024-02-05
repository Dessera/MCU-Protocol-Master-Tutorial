#pragma once

#include "ssdrv/behavior.hpp"
#include "ssdrv/context.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace command {

class Command : public behavior::IBehavior {
 public:
  static constexpr uint8_t COMMAND_SIGNAL = 0x00;

  void apply(std::shared_ptr<context::Context> context) override{
      // context->protocol().write(COMMAND_SIGNAL);
  };

  void apply(std::shared_ptr<context::Context> context, uint8_t data) {
    std::size_t send = context->protocol().write({COMMAND_SIGNAL, data});
    if (send != 2) {
      log_e("==> Failed to send command data require 2 bytes, but send %d",
            send);
      return;
    }
    log_d("==> Send command data: 0x%02X", data);
  };
};

}  // namespace command

SSDRV_NS_END
