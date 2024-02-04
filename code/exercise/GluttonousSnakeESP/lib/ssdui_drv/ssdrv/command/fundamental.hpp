#pragma once

#include "ssdrv/command/base.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace command::fundamental {

/**
 * @brief 设置对比度
 */
class CommandSetContrast : public Command {
 public:
  inline static constexpr uint8_t COMMAND_PREFIX = 0x81;
  inline static constexpr uint8_t DEFAULT_CONTRAST = 0x7F;

 private:
  uint8_t m_contrast{DEFAULT_CONTRAST};

 public:
  CommandSetContrast(uint8_t contrast) : m_contrast(contrast) {}
  CommandSetContrast() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, m_contrast);
  };
};



/**
 * @brief 设置显示全亮
 */
class CommandEnableEntireDisplayOn : public Command {
 public:
  inline static constexpr uint8_t DISPLAY_ALL_ON = 0xA5;
  inline static constexpr uint8_t DISPLAY_NORMAL = 0xA4;

 private:
  bool m_state{false};

 public:
  CommandEnableEntireDisplayOn(bool state) : m_state(state) {}
  CommandEnableEntireDisplayOn() = default;

  inline uint8_t state() const {
    return m_state ? DISPLAY_ALL_ON : DISPLAY_NORMAL;
  }

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, state());
  };
};

/**
 * @brief 设置显示反色
 */
class CommandSetInverseDisplay : public Command {
 public:
  inline static constexpr uint8_t DISPLAY_INVERSE = 0xA7;
  inline static constexpr uint8_t DISPLAY_NORMAL = 0xA6;

 private:
  bool m_state{false};

 public:
  CommandSetInverseDisplay(bool state) : m_state(state) {}
  CommandSetInverseDisplay() = default;

  inline uint8_t state() const {
    return m_state ? DISPLAY_INVERSE : DISPLAY_NORMAL;
  }

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, state());
  };
};



/**
 * @brief 显示开关
 */
class CommandEnableDisplay : public Command {
 public:
  inline static constexpr uint8_t DISPLAY_ON = 0xAF;
  inline static constexpr uint8_t DISPLAY_OFF = 0xAE;

 private:
  bool m_state{true};

 public:
  CommandEnableDisplay(bool state) : m_state(state) {}
  CommandEnableDisplay() = default;

  inline uint8_t state() const { return m_state ? DISPLAY_ON : DISPLAY_OFF; }

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, state());
  };
};

}  // namespace command::fundamental

SSDRV_NS_END
