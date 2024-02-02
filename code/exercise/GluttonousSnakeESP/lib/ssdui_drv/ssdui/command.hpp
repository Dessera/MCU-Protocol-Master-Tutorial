#pragma once

#include "behavior.hpp"

class SSDrvCommand : public SSDrvBehavior {
 public:
  inline static constexpr uint8_t COMMAND_SIGNAL = 0x00;

  virtual void apply(std::shared_ptr<SSDrvContext> context) override {
    context->protocol().write(COMMAND_SIGNAL);
  };
};

class SSDrvSetContrastCommand : public SSDrvCommand {
 public:
  inline static constexpr uint8_t COMMAND_PREFIX = 0x81;
  inline static constexpr uint8_t DEFAULT_CONTRAST = 0x7F;

 private:
  uint8_t m_contrast{DEFAULT_CONTRAST};

 public:
  SSDrvSetContrastCommand(uint8_t contrast) : m_contrast(contrast) {}
  SSDrvSetContrastCommand() = default;

  void apply(std::shared_ptr<SSDrvContext> context) final {
    // call super method to write command signal
    SSDrvCommand::apply(context);
    context->protocol().write(COMMAND_PREFIX);
    SSDrvCommand::apply(context);
    context->protocol().write(m_contrast);
  };
};

class SSDrvSetDisplayAllOnCommand : public SSDrvCommand {
 public:
  inline static constexpr uint8_t DISPLAY_ALL_ON = 0xA5;
  inline static constexpr uint8_t DISPLAY_NORMAL = 0xA4;

 private:
  bool m_state{false};

 public:
  SSDrvSetDisplayAllOnCommand(bool state) : m_state(state) {}
  SSDrvSetDisplayAllOnCommand() = default;

  inline uint8_t state() const {
    return m_state ? DISPLAY_ALL_ON : DISPLAY_NORMAL;
  }

  void apply(std::shared_ptr<SSDrvContext> context) final {
    // call super method to write command signal
    SSDrvCommand::apply(context);
    context->protocol().write(state());
  };
};

class SSDrvSetInverseColorCommand : public SSDrvCommand {
 public:
  inline static constexpr uint8_t DISPLAY_INVERSE = 0xA7;
  inline static constexpr uint8_t DISPLAY_NORMAL = 0xA6;

 private:
  bool m_state{false};

 public:
  SSDrvSetInverseColorCommand(bool state) : m_state(state) {}
  SSDrvSetInverseColorCommand() = default;

  inline uint8_t state() const {
    return m_state ? DISPLAY_INVERSE : DISPLAY_NORMAL;
  }

  void apply(std::shared_ptr<SSDrvContext> context) final {
    // call super method to write command signal
    SSDrvCommand::apply(context);
    context->protocol().write(state());
  };
};

class SSDrvSetDisplayOnCommand : public SSDrvCommand {
 public:
  inline static constexpr uint8_t DISPLAY_ON = 0xAF;
  inline static constexpr uint8_t DISPLAY_OFF = 0xAE;

 private:
  bool m_state{false};

 public:
  SSDrvSetDisplayOnCommand(bool state) : m_state(state) {}
  SSDrvSetDisplayOnCommand() = default;

  inline uint8_t state() const {
    return m_state ? DISPLAY_ON : DISPLAY_OFF;
  }

  void apply(std::shared_ptr<SSDrvContext> context) final {
    // call super method to write command signal
    SSDrvCommand::apply(context);
    context->protocol().write(state());
  };
};



