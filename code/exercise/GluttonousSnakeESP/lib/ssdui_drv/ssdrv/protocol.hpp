#pragma once
#include <Wire.h>

#include <cstdint>

#include "ssdrv/constant.hpp"
#include "ssdrv/create.hpp"

SSDRV_NS_BEGIN

namespace protocol {

/**
 * @brief 显示驱动协议接口
 *        事实上，Arduino提供了类似的接口，该层只是为了更好地抽象
 */
class IProtocol : public CreateToUniquePtr<IProtocol> {
 public:
  virtual ~IProtocol() = default;

  /**
   * @brief 向显示驱动发送数据
   */
  virtual void write(uint8_t data) = 0;

  void write(uint8_t data) const {
    const_cast<IProtocol*>(this)->write(data);
  }
};

/**
 * @brief 通信接口配置对象
 *
 */
struct I2CProtocolConfig {
  uint8_t address;
  uint8_t sda;
  uint8_t scl;
  TwoWire& wire;
};

/**
 * @brief I2C示例接口
 */
class I2CProtocol : public IProtocol {
 private:
  I2CProtocolConfig m_config;

 public:
  explicit I2CProtocol(I2CProtocolConfig config)
      : m_config(std::move(config)) {
    m_config.wire.begin(m_config.sda, m_config.scl);
  }
  I2CProtocol() = delete;
  ~I2CProtocol() { m_config.wire.end(); };

  /**
   * @brief 向显示驱动发送数据
   */
  void write(uint8_t data) override {
    m_config.wire.beginTransmission(m_config.address);
    m_config.wire.write(data);
    m_config.wire.endTransmission();
  };
};

}  // namespace protocol

SSDRV_NS_END
