#pragma once

#include "ssdrv/command.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace behaviors {

class InitializationBehavior : public behavior::IBehavior {
 public:
  InitializationBehavior() = default;

  InitializationBehavior(const InitializationBehavior&) = default;
  InitializationBehavior& operator=(const InitializationBehavior&) = default;
  InitializationBehavior(InitializationBehavior&&) = default;
  InitializationBehavior& operator=(InitializationBehavior&&) = default;

  ~InitializationBehavior() = default;

  void apply(std::shared_ptr<context::Context> context) override {
    using namespace command;

    log_i("==> Start initializing the display");

    auto& config = context->config();
    behavior::BehaviorBuilder()
        .add(Command::create<fundamental::CommandEnableDisplay>(false))
        .add(Command::create<clock::CommandSetDisplayClock>(
            config.get_clock_ratio(), config.get_clock_frequency()))
        .add(Command::create<hardware::CommandSetMultiplexRatio>(
            config.get_multiplex_ratio()))
        .add(Command::create<hardware::CommandSetDisplayOffset>(
            config.get_display_offset()))
        .add(Command::create<address::CommandSetAddressingMode>(
            config.get_addressing_mode()))
        .add(Command::create<hardware::CommandSetStartLine>(
            config.get_start_line()))
        .add(Command::create<hardware::CommandSetHorizontalFlip>(
            config.get_horizontal_flip()))
        .add(Command::create<hardware::CommandSetVerticalFlip>(
            config.get_vertical_flip()))
        .add(
            Command::create<hardware::CommandSetComPins>(config.get_com_pins()))
        .add(Command::create<fundamental::CommandSetContrast>(
            config.get_contrast()))
        .add(Command::create<clock::CommandSetPrechargePeriod>(
            config.get_precharge_phase1(), config.get_precharge_phase2()))
        .add(Command::create<clock::CommandSetVcomhDeselectLevel>(
            config.get_vcomh_level()))
        .add(Command::create<fundamental::CommandEnableEntireDisplayOn>(
            config.get_entire_display_on()))
        .add(Command::create<fundamental::CommandSetInverseDisplay>(
            config.get_inverse_display()))
        // set cursor
        .add(Command::create<address::CommandSetPageAddress>(
            config.get_page_start(), config.get_page_end()))
        .add(Command::create<address::CommandSetColumnAddress>(
            config.get_column_start(), config.get_column_end()))
        .add(Command::create<fundamental::CommandEnableDisplay>(
            config.get_display_on()))
        .apply(context);

    log_i("<== Finish initializing the display");
  }
};

}  // namespace behaviors

SSDRV_NS_END
