#pragma once

#include <memory>

#include "protocol.hpp"

struct SSDrvContextConfig {
  std::unique_ptr<ISSDrvProtocol> protocol;
  uint8_t width;
  uint8_t height;

  SSDrvContextConfig() = delete;
  SSDrvContextConfig(std::unique_ptr<ISSDrvProtocol> protocol, uint8_t width,
                     uint8_t height)
      : protocol(std::move(protocol)), width(width), height(height) {}
};

class SSDrvContext {
 private:
  SSDrvContextConfig m_config;

 public:
  explicit SSDrvContext(SSDrvContextConfig config)
      : m_config(std::move(config)) {
    // TODO: wait for implementation
  }

  inline const SSDrvContextConfig& config() const { return m_config; }
};
