#pragma once

#include "ssdrv/command/base.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace command::clock {

/**
 * @brief 设置时钟分频 和 振荡频率
 */
class CommandSetDisplayClock : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0xD5;

 private:
  uint8_t m_ratio;
  uint8_t m_frequency;

 public:
  CommandSetDisplayClock(uint8_t ratio, uint8_t frequency)
      : m_ratio(ratio), m_frequency(frequency) {}
  CommandSetDisplayClock() = delete;

  CommandSetDisplayClock(const CommandSetDisplayClock &) = default;
  CommandSetDisplayClock(CommandSetDisplayClock &&) noexcept = default;
  CommandSetDisplayClock &operator=(const CommandSetDisplayClock &) = default;
  CommandSetDisplayClock &operator=(CommandSetDisplayClock &&) noexcept =
      default;

  ~CommandSetDisplayClock() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, (m_frequency << 4) | m_ratio);
  };
};

/**
 * @brief 设置预充电周期
 */
class CommandSetPrechargePeriod : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0xD9;

 private:
  uint8_t m_phase1;
  uint8_t m_phase2;

 public:
  CommandSetPrechargePeriod(uint8_t phase1, uint8_t phase2)
      : m_phase1(phase1), m_phase2(phase2) {}
  CommandSetPrechargePeriod() = delete;

  CommandSetPrechargePeriod(const CommandSetPrechargePeriod &) = default;
  CommandSetPrechargePeriod(CommandSetPrechargePeriod &&) noexcept = default;
  CommandSetPrechargePeriod &operator=(const CommandSetPrechargePeriod &) =
      default;
  CommandSetPrechargePeriod &operator=(CommandSetPrechargePeriod &&) noexcept =
      default;

  ~CommandSetPrechargePeriod() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, (m_phase1 << 4) | m_phase2);
  };
};

/**
 * @brief 设置VCOMH电压
 */
class CommandSetVcomhDeselectLevel : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0xDB;

 private:
  uint8_t m_level;

 public:
  CommandSetVcomhDeselectLevel(uint8_t level) : m_level(level) {}
  CommandSetVcomhDeselectLevel() = delete;

  CommandSetVcomhDeselectLevel(const CommandSetVcomhDeselectLevel &) = default;
  CommandSetVcomhDeselectLevel(CommandSetVcomhDeselectLevel &&) noexcept =
      default;
  CommandSetVcomhDeselectLevel &operator=(
      const CommandSetVcomhDeselectLevel &) = default;
  CommandSetVcomhDeselectLevel &operator=(
      CommandSetVcomhDeselectLevel &&) noexcept = default;

  ~CommandSetVcomhDeselectLevel() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, m_level);
  };
};

/**
 * @brief 什么都不做
 */
class CommandNop : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0xE3;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, COMMAND_PREFIX);
  };
};

}  // namespace command::clock

SSDRV_NS_END