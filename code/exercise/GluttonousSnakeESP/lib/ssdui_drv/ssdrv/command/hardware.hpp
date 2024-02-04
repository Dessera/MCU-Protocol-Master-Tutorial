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
  inline static constexpr uint8_t COMMAND_PREFIX = 0x40;

 private:
  uint8_t m_line{0};

 public:
  CommandSetStartLine(uint8_t line) : m_line(line) {}
  CommandSetStartLine() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    if (m_line >= context->height()) {
      m_line = context->height() - 1;
    }
    Command::apply(context, COMMAND_PREFIX | m_line);
  };
};

/**
 * @brief 设置映射方向（左右翻转）
 */
class CommandSetSegmentRemap : public Command {
 public:
  inline static constexpr uint8_t NORMAL = 0xA0;
  inline static constexpr uint8_t REMAP = 0xA1;

 private:
  bool m_remap{false};

 public:
  CommandSetSegmentRemap(bool remap) : m_remap(remap) {}
  CommandSetSegmentRemap() = default;

  inline uint8_t state() const { return m_remap ? REMAP : NORMAL; }

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, state());
  };
};

// * Alias for CommandSetSegmentRemap
using CommandSetHorizontalFlip = CommandSetSegmentRemap;

/**
 * @brief 设置通道数（可显示的行数）
 */
class CommandSetMultiplexRatio : public Command {
 public:
  inline static constexpr uint8_t COMMAND_PREFIX = 0xA8;
  inline static constexpr uint8_t DEFAULT_RATIO = 63;

 private:
  uint8_t m_ratio{DEFAULT_RATIO};

 public:
  CommandSetMultiplexRatio(uint8_t ratio) : m_ratio(ratio) {}
  CommandSetMultiplexRatio() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    if (m_ratio >= context->width()) {
      m_ratio = context->width() - 1;
    }
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, m_ratio);
  };
};

/**
 * @brief 设置扫描方向 (上下翻转)
 */
class CommandSetScanDirection : public Command {
 public:
  inline static constexpr uint8_t NORMAL = 0xC0;
  inline static constexpr uint8_t REVERSE = 0xC8;

 private:
  bool m_reverse{false};

 public:
  CommandSetScanDirection(bool reverse) : m_reverse(reverse) {}
  CommandSetScanDirection() = default;

  inline uint8_t state() const { return m_reverse ? REVERSE : NORMAL; }

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, state());
  };
};

// * Alias for CommandSetScanDirection
using CommandSetVerticalFlip = CommandSetScanDirection;

/**
 * @brief 设置显示偏移
 */
class CommandSetDisplayOffset : public Command {
 public:
  inline static constexpr uint8_t COMMAND_PREFIX = 0xD3;
  inline static constexpr uint8_t DEFAULT_OFFSET = 0x00;

 private:
  uint8_t m_offset{DEFAULT_OFFSET};

 public:
  CommandSetDisplayOffset(uint8_t offset) : m_offset(offset) {}
  CommandSetDisplayOffset() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    if (m_offset >= context->config().page) {
      m_offset = context->config().page - 1;
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
  inline static constexpr uint8_t COMMAND_PREFIX = 0xDA;

 private:
  context::ComPinConfiguration m_config{
      context::ComPinConfiguration::ALTERNATIVE};

 public:
  CommandSetComPins(context::ComPinConfiguration config) : m_config(config) {}
  CommandSetComPins() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, COMMAND_PREFIX);
    Command::apply(context, static_cast<uint8_t>(m_config));
  };
};

}  // namespace command::hardware

SSDRV_NS_END