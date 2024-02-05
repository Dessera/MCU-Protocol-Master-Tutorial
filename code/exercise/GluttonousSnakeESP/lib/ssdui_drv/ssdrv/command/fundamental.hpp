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
  static constexpr uint8_t COMMAND_PREFIX = 0x81;

 private:
  uint8_t m_contrast;

 public:
  CommandSetContrast(uint8_t contrast) : m_contrast(contrast) {}
  CommandSetContrast() = delete;

  CommandSetContrast(const CommandSetContrast &) = default;
  CommandSetContrast(CommandSetContrast &&) noexcept = default;
  CommandSetContrast &operator=(const CommandSetContrast &) = default;
  CommandSetContrast &operator=(CommandSetContrast &&) noexcept = default;

  ~CommandSetContrast() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    log_i("==> Set contrast: %d", m_contrast);
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, m_contrast);
  };
};

/**
 * @brief 设置显示全亮
 */
class CommandEnableEntireDisplayOn : public Command {
 public:
  static constexpr uint8_t DISPLAY_ALL_ON = 0xA5;
  static constexpr uint8_t DISPLAY_NORMAL = 0xA4;

 private:
  bool m_state;

 public:
  CommandEnableEntireDisplayOn(bool state) : m_state(state) {}
  CommandEnableEntireDisplayOn() = delete;

  CommandEnableEntireDisplayOn(const CommandEnableEntireDisplayOn &) = default;
  CommandEnableEntireDisplayOn(CommandEnableEntireDisplayOn &&) noexcept =
      default;
  CommandEnableEntireDisplayOn &operator=(
      const CommandEnableEntireDisplayOn &) = default;
  CommandEnableEntireDisplayOn &operator=(
      CommandEnableEntireDisplayOn &&) noexcept = default;

  ~CommandEnableEntireDisplayOn() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    log_i("==> Set entire display to %s", m_state ? "ON" : "OFF");
    Command::apply(context, m_state ? DISPLAY_ALL_ON : DISPLAY_NORMAL);
  };
};

/**
 * @brief 设置显示反色
 */
class CommandSetInverseDisplay : public Command {
 public:
  static constexpr uint8_t DISPLAY_INVERSE = 0xA7;
  static constexpr uint8_t DISPLAY_NORMAL = 0xA6;

 private:
  bool m_state;

 public:
  CommandSetInverseDisplay(bool state) : m_state(state) {}
  CommandSetInverseDisplay() = delete;

  CommandSetInverseDisplay(const CommandSetInverseDisplay &) = default;
  CommandSetInverseDisplay(CommandSetInverseDisplay &&) noexcept = default;
  CommandSetInverseDisplay &operator=(const CommandSetInverseDisplay &) =
      default;
  CommandSetInverseDisplay &operator=(CommandSetInverseDisplay &&) noexcept =
      default;

  ~CommandSetInverseDisplay() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    log_i("==> Set inverse display to %s", m_state ? "ON" : "OFF");
    Command::apply(context, m_state ? DISPLAY_INVERSE : DISPLAY_NORMAL);
  };
};

/**
 * @brief 显示开关
 */
class CommandEnableDisplay : public Command {
 public:
  static constexpr uint8_t DISPLAY_ON = 0xAF;
  static constexpr uint8_t DISPLAY_OFF = 0xAE;

 private:
  bool m_state;

 public:
  CommandEnableDisplay(bool state) : m_state(state) {}
  CommandEnableDisplay() = delete;

  CommandEnableDisplay(const CommandEnableDisplay &) = default;
  CommandEnableDisplay(CommandEnableDisplay &&) noexcept = default;
  CommandEnableDisplay &operator=(const CommandEnableDisplay &) = default;
  CommandEnableDisplay &operator=(CommandEnableDisplay &&) noexcept = default;

  ~CommandEnableDisplay() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    log_i("==> Set display to %s", m_state ? "ON" : "OFF");
    Command::apply(context, m_state ? DISPLAY_ON : DISPLAY_OFF);
  };
};

}  // namespace command::fundamental

SSDRV_NS_END
