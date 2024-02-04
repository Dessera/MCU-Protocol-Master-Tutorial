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
  inline static constexpr uint8_t COMMAND_PREFIX = 0xD5;
  inline static constexpr uint8_t DEFAULT_RATIO = 0x00;
  inline static constexpr uint8_t DEFAULT_FREQUENCY = 0x08;

 private:
  uint8_t m_ratio{DEFAULT_RATIO};
  uint8_t m_frequency{DEFAULT_FREQUENCY};

 public:
  CommandSetDisplayClock(uint8_t ratio, uint8_t frequency)
      : m_ratio(ratio), m_frequency(frequency) {}
  CommandSetDisplayClock() = default;

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
  inline static constexpr uint8_t COMMAND_PREFIX = 0xD9;
  inline static constexpr uint8_t DEFAULT_PHASE1 = 0x02;
  inline static constexpr uint8_t DEFAULT_PHASE2 = 0x02;

 private:
  uint8_t m_phase1{DEFAULT_PHASE1};
  uint8_t m_phase2{DEFAULT_PHASE2};

 public:
  CommandSetPrechargePeriod(uint8_t phase1, uint8_t phase2)
      : m_phase1(phase1), m_phase2(phase2) {}
  CommandSetPrechargePeriod() = default;

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
  inline static constexpr uint8_t COMMAND_PREFIX = 0xDB;
  inline static constexpr uint8_t DEFAULT_LEVEL = 0x20;

 private:
  uint8_t m_level{DEFAULT_LEVEL};

 public:
  CommandSetVcomhDeselectLevel(uint8_t level) : m_level(level) {}
  CommandSetVcomhDeselectLevel() = default;

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
  inline static constexpr uint8_t COMMAND_PREFIX = 0xE3;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, COMMAND_PREFIX);
  };
};

}  // namespace command::clock

SSDRV_NS_END