#pragma once

#include "ssdrv/command/base.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace command::address {

/**
 * @brief 设置起始列
 */
class CommandSetStartColumn : public Command {
 public:
  static constexpr uint8_t LOW_COMMAND_PREFIX = 0x00;
  static constexpr uint8_t HIGH_COMMAND_PREFIX = 0x10;

 private:
  uint8_t m_column;

 public:
  CommandSetStartColumn(uint8_t column) : m_column(column) {}
  CommandSetStartColumn() = delete;

  CommandSetStartColumn(const CommandSetStartColumn &) = default;
  CommandSetStartColumn(CommandSetStartColumn &&) noexcept = default;
  CommandSetStartColumn &operator=(const CommandSetStartColumn &) = default;
  CommandSetStartColumn &operator=(CommandSetStartColumn &&) noexcept = default;

  ~CommandSetStartColumn() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    if (context->config().get_addressing_mode() !=
        context::AddressingMode::PAGE) {
      return;
    }
    if (m_column >= context->config().get_width()) {
      m_column = context->config().get_width() - 1;
    }
    Command::apply(context, LOW_COMMAND_PREFIX | (m_column & 0x0F));
    Command::apply(context, HIGH_COMMAND_PREFIX | (m_column >> 4));
  };
};

/**
 * @brief 设置内存寻址模式
 */
class CommandSetAddressingMode : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0x20;

 private:
  context::AddressingMode m_mode;

 public:
  CommandSetAddressingMode(context::AddressingMode mode) : m_mode(mode) {}
  CommandSetAddressingMode() = delete;

  CommandSetAddressingMode(const CommandSetAddressingMode &) = default;
  CommandSetAddressingMode(CommandSetAddressingMode &&) noexcept = default;
  CommandSetAddressingMode &operator=(const CommandSetAddressingMode &) =
      default;
  CommandSetAddressingMode &operator=(CommandSetAddressingMode &&) noexcept =
      default;

  ~CommandSetAddressingMode() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, COMMAND_PREFIX | static_cast<uint8_t>(m_mode));
  };
};

/**
 * @brief 设置列地址范围
 */
class CommandSetColumnAddress : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0x21;

 private:
  uint8_t m_start_column;
  uint8_t m_end_column;

 public:
  CommandSetColumnAddress(uint8_t start_column, uint8_t end_column)
      : m_start_column(start_column), m_end_column(end_column) {}
  CommandSetColumnAddress() = delete;

  CommandSetColumnAddress(const CommandSetColumnAddress &) = default;
  CommandSetColumnAddress(CommandSetColumnAddress &&) noexcept = default;
  CommandSetColumnAddress &operator=(const CommandSetColumnAddress &) = default;
  CommandSetColumnAddress &operator=(CommandSetColumnAddress &&) noexcept =
      default;

  ~CommandSetColumnAddress() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    if (context->config().get_addressing_mode() ==
        context::AddressingMode::PAGE) {
      return;
    }
    if (m_start_column >= context->config().get_width()) {
      m_start_column = context->config().get_width() - 1;
    }
    if (m_end_column >= context->config().get_width()) {
      m_end_column = context->config().get_width() - 1;
    }
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, m_start_column);
    Command::apply(context, m_end_column);
  };
};

/**
 * @brief 设置页地址范围
 */
class CommandSetPageAddress : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0x22;

 private:
  uint8_t m_start_page;
  uint8_t m_end_page;

 public:
  CommandSetPageAddress(uint8_t start_page, uint8_t end_page)
      : m_start_page(start_page), m_end_page(end_page) {}
  CommandSetPageAddress() = delete;

  CommandSetPageAddress(const CommandSetPageAddress &) = default;
  CommandSetPageAddress(CommandSetPageAddress &&) noexcept = default;
  CommandSetPageAddress &operator=(const CommandSetPageAddress &) = default;
  CommandSetPageAddress &operator=(CommandSetPageAddress &&) noexcept = default;

  ~CommandSetPageAddress() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    if (context->config().get_addressing_mode() ==
        context::AddressingMode::PAGE) {
      return;
    }
    if (m_start_page >= context->config().get_page()) {
      m_start_page = context->config().get_page() - 1;
    }
    if (m_end_page >= context->config().get_page()) {
      m_end_page = context->config().get_page() - 1;
    }
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, m_start_page);
    Command::apply(context, m_end_page);
  };
};

/**
 * @brief 设置页地址
 * @details 10.1.13 Set Page Start Address for Page Addressing Mode (B0h~B7h)
 */
class CommandSetStartPage : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0xB0;

 private:
  uint8_t m_page;

 public:
  CommandSetStartPage(uint8_t page) : m_page(page) {}
  CommandSetStartPage() = delete;

  CommandSetStartPage(const CommandSetStartPage &) = default;
  CommandSetStartPage(CommandSetStartPage &&) noexcept = default;
  CommandSetStartPage &operator=(const CommandSetStartPage &) = default;
  CommandSetStartPage &operator=(CommandSetStartPage &&) noexcept = default;

  ~CommandSetStartPage() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    if (context->config().get_addressing_mode() !=
        context::AddressingMode::PAGE) {
      return;
    }
    if (m_page >= context->config().get_page()) {
      m_page = context->config().get_page() - 1;
    }
    Command::apply(context, m_page | COMMAND_PREFIX);
  };
};

}  // namespace command::address

SSDRV_NS_END