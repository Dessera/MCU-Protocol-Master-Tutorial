#pragma once

#include <memory>

#include "protocol.hpp"
#include "ssdrv/constant.hpp"

SSDRV_NS_BEGIN

namespace context {

/**
 * @brief OLED显示驱动上下文配置对象
 *
 */
struct Config {
  std::unique_ptr<protocol::IProtocol> protocol;
  uint8_t width;
  // * Instead of height
  uint8_t page;
};

/**
 * @brief OLED显示驱动上下文，需要配合Behavior类使用
 * 
 */
class Context : public CreateToSharedPtr<Context> {
 private:
  Config m_config;

 public:
  explicit Context(Config config)
      : m_config(std::move(config)) {
    // TODO: wait for implementation
  }

  inline const Config& config() const { return m_config; }
  inline const protocol::IProtocol& protocol() const {
    return *m_config.protocol;
  }
};

};  // namespace context

SSDRV_NS_END
