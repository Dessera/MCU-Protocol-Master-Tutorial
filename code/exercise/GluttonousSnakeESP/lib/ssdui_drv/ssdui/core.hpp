#pragma once

#include <memory>

#include "ssdui/protocol.hpp"

struct SSDrvContextConfig {
  std::unique_ptr<ISSDrvProtocol> protocol;
  uint8_t width;
  uint8_t height;
};

class SSDrvContext {
 private:
  SSDrvContextConfig m_config;

 public:
  explicit SSDrvContext(SSDrvContextConfig config);
};
