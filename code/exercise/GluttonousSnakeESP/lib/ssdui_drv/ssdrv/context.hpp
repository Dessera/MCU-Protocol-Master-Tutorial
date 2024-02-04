#pragma once

#include <memory>

#include "ssdrv/protocol.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace context {

enum class AddressingMode : uint8_t {
  HORIZONTAL = 0x00,
  VERTICAL = 0x01,
  PAGE = 0x02,
};

enum class ComPinConfiguration : uint8_t {
  SEQUENTIAL = 0x02,
  SEQUENTIAL_REMAPPED = 0x22,
  ALTERNATIVE = 0x12,
  ALTERNATIVE_REMAPPED = 0x32,
};

/**
 * @brief OLED显示驱动上下文配置对象
 *
 */
struct Config {
  std::unique_ptr<protocol::IProtocol> protocol;
  uint8_t width;
  // * Instead of height
  uint8_t page;
  AddressingMode addressing_mode;
};

/**
 * @brief OLED显示驱动上下文，需要配合Behavior类使用
 *
 */
class Context : public CreateToSharedPtr<Context> {
 private:
  Config m_config;

 public:
  explicit Context(Config config) : m_config(std::move(config)) {
    // TODO: wait for implementation
  }

  inline const Config& config() const { return m_config; }
  inline uint8_t width() const { return m_config.width; }
  inline uint8_t page() const { return m_config.page; }
  inline uint8_t height() const { return m_config.page * 8; }
  inline const protocol::IProtocol& protocol() const {
    return *m_config.protocol;
  }
};

};  // namespace context

SSDRV_NS_END
