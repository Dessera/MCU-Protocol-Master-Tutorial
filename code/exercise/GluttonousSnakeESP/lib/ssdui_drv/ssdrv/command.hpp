#pragma once

#include "behavior.hpp"
#include "ssdrv/constant.hpp"

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

class CommandInverseColor : public Command {
 public:
  inline static constexpr uint8_t DISPLAY_INVERSE = 0xA7;
  inline static constexpr uint8_t DISPLAY_NORMAL = 0xA6;

 private:
  bool m_state{false};

 public:
  CommandInverseColor(bool state) : m_state(state) {}
  CommandInverseColor() = default;

  inline uint8_t state() const {
    return m_state ? DISPLAY_INVERSE : DISPLAY_NORMAL;
  }

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, state());
  };
};

class CommandEnableDisplay : public Command {
 public:
  inline static constexpr uint8_t DISPLAY_ON = 0xAF;
  inline static constexpr uint8_t DISPLAY_OFF = 0xAE;

 private:
  bool m_state{false};

 public:
  CommandEnableDisplay(bool state) : m_state(state) {}
  CommandEnableDisplay() = default;

  inline uint8_t state() const { return m_state ? DISPLAY_ON : DISPLAY_OFF; }

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, state());
  };
};

class CommandSetAddressingMode : public Command {
 public:
  // TODO: move out of class
  enum class Mode : uint8_t {
    HORIZONTAL = 0x00,
    VERTICAL = 0x01,
    PAGE = 0x02,
  };

  inline static constexpr uint8_t COMMAND_PREFIX = 0x20;

 private:
  Mode m_mode{Mode::HORIZONTAL};

  inline uint8_t mode() const {
    return static_cast<uint8_t>(m_mode) | COMMAND_PREFIX;
  }

 public:
  CommandSetAddressingMode(Mode mode) : m_mode(mode) {}
  CommandSetAddressingMode() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, mode());
  };
};

class CommandSetStartPage : public Command {
 public:
  // TODO: move out of class
  enum class Page : uint8_t {
    PAGE0 = 0,
    PAGE1 = 1,
    PAGE2 = 2,
    PAGE3 = 3,
    PAGE4 = 4,
    PAGE5 = 5,
    PAGE6 = 6,
    PAGE7 = 7,
  };

  inline static constexpr uint8_t COMMAND_PREFIX = 0xB0;

 private:
  Page m_page{Page::PAGE0};

  inline uint8_t page() const {
    return static_cast<uint8_t>(m_page) | COMMAND_PREFIX;
  }

 public:
  CommandSetStartPage(Page page) : m_page(page) {}
  CommandSetStartPage() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    Command::apply(context, page());
  };
};

class CommandSetStartColumn : public Command {
 public:
  inline static constexpr uint8_t LOW_COMMAND_PREFIX = 0x00;
  inline static constexpr uint8_t HIGH_COMMAND_PREFIX = 0x10;

 private:
  uint8_t m_column{0};

 public:
  CommandSetStartColumn(uint8_t column) : m_column(column) {}
  CommandSetStartColumn() = default;

  void apply(std::shared_ptr<context::Context> context) final {
    if (m_column >= context->config().width) {
      m_column = context->config().width - 1;
    }
    Command::apply(context, LOW_COMMAND_PREFIX | (m_column & 0x0F));
    Command::apply(context, HIGH_COMMAND_PREFIX | (m_column >> 4));
  };
};

// class SSDrvSetPageAddressCommand : public Command {
//  public:
//   inline static constexpr uint8_t COMMAND_PREFIX = 0x22;

//  private:
//   uint8_t m_start_page{0};
//   uint8_t m_end_page{0};
// };

}  // namespace command

SSDRV_NS_END
