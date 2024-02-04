#pragma once

#include "ssdrv/command/base.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace command::hardware {

/**
 * @brief 设置显示起始行
 */
class CommandSetStartLine : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0x40;

 private:
  uint8_t m_line;

 public:
  CommandSetStartLine(uint8_t line) : m_line(line) {}
  CommandSetStartLine() = delete;

  CommandSetStartLine(const CommandSetStartLine &) = default;
  CommandSetStartLine(CommandSetStartLine &&) noexcept = default;
  CommandSetStartLine &operator=(const CommandSetStartLine &) = default;
  CommandSetStartLine &operator=(CommandSetStartLine &&) noexcept = default;

  ~CommandSetStartLine() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    if (m_line >= context->config().get_height()) {
      m_line = context->config().get_height() - 1;
    }
    Command::apply(context, COMMAND_PREFIX | m_line);
  };
};

/**
 * @brief 设置映射方向（左右翻转）
 */
class CommandSetSegmentRemap : public Command {
 public:
  static constexpr uint8_t NORMAL = 0xA0;
  static constexpr uint8_t REMAP = 0xA1;

 private:
  bool m_remap;

 public:
  CommandSetSegmentRemap(bool remap) : m_remap(remap) {}
  CommandSetSegmentRemap() = delete;

  CommandSetSegmentRemap(const CommandSetSegmentRemap &) = default;
  CommandSetSegmentRemap(CommandSetSegmentRemap &&) noexcept = default;
  CommandSetSegmentRemap &operator=(const CommandSetSegmentRemap &) = default;
  CommandSetSegmentRemap &operator=(CommandSetSegmentRemap &&) noexcept =
      default;

  ~CommandSetSegmentRemap() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, m_remap ? REMAP : NORMAL);
  };
};

// * Alias for CommandSetSegmentRemap
using CommandSetHorizontalFlip = CommandSetSegmentRemap;

/**
 * @brief 设置通道数（可显示的行数）
 */
class CommandSetMultiplexRatio : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0xA8;

 private:
  uint8_t m_ratio;

 public:
  CommandSetMultiplexRatio(uint8_t ratio) : m_ratio(ratio) {}
  CommandSetMultiplexRatio() = delete;

  CommandSetMultiplexRatio(const CommandSetMultiplexRatio &) = default;
  CommandSetMultiplexRatio(CommandSetMultiplexRatio &&) noexcept = default;
  CommandSetMultiplexRatio &operator=(const CommandSetMultiplexRatio &) =
      default;
  CommandSetMultiplexRatio &operator=(CommandSetMultiplexRatio &&) noexcept =
      default;

  ~CommandSetMultiplexRatio() = default;

  // ! Auto handle the +1 issue
  void apply(std::shared_ptr<context::Context> context) final {
    if (m_ratio > context->config().get_width()) {
      m_ratio = context->config().get_width();
    }
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, m_ratio - 1);
  };
};

/**
 * @brief 设置扫描方向 (上下翻转)
 */
class CommandSetScanDirection : public Command {
 public:
  static constexpr uint8_t NORMAL = 0xC0;
  static constexpr uint8_t REVERSE = 0xC8;

 private:
  bool m_reverse;

 public:
  CommandSetScanDirection(bool reverse) : m_reverse(reverse) {}
  CommandSetScanDirection() = delete;

  CommandSetScanDirection(const CommandSetScanDirection &) = default;
  CommandSetScanDirection(CommandSetScanDirection &&) noexcept = default;
  CommandSetScanDirection &operator=(const CommandSetScanDirection &) = default;
  CommandSetScanDirection &operator=(CommandSetScanDirection &&) noexcept =
      default;

  ~CommandSetScanDirection() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, m_reverse ? REVERSE : NORMAL);
  };
};

// * Alias for CommandSetScanDirection
using CommandSetVerticalFlip = CommandSetScanDirection;

/**
 * @brief 设置显示偏移
 */
class CommandSetDisplayOffset : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0xD3;

 private:
  uint8_t m_offset;

 public:
  CommandSetDisplayOffset(uint8_t offset) : m_offset(offset) {}
  CommandSetDisplayOffset() = delete;

  CommandSetDisplayOffset(const CommandSetDisplayOffset &) = default;
  CommandSetDisplayOffset(CommandSetDisplayOffset &&) noexcept = default;
  CommandSetDisplayOffset &operator=(const CommandSetDisplayOffset &) = default;
  CommandSetDisplayOffset &operator=(CommandSetDisplayOffset &&) noexcept =
      default;

  ~CommandSetDisplayOffset() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    if (m_offset >= context->config().get_page()) {
      m_offset = context->config().get_page() - 1;
    }
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, m_offset);
  };
};

/**
 * @brief 设置COM硬件配置
 */
class CommandSetComPins : public Command {
 public:
  static constexpr uint8_t COMMAND_PREFIX = 0xDA;

 private:
  context::ComPinsConfig m_config;

 public:
  CommandSetComPins(context::ComPinsConfig config) : m_config(config) {}
  CommandSetComPins() = delete;

  CommandSetComPins(const CommandSetComPins &) = default;
  CommandSetComPins(CommandSetComPins &&) noexcept = default;
  CommandSetComPins &operator=(const CommandSetComPins &) = default;
  CommandSetComPins &operator=(CommandSetComPins &&) noexcept = default;

  ~CommandSetComPins() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, static_cast<uint8_t>(m_config));
  };
};

}  // namespace command::hardware

SSDRV_NS_END