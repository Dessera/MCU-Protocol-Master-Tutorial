#pragma once
#include <Wire.h>

#include <cstdint>

/**
 * @brief 显示驱动协议接口
 *        事实上，Arduino提供了类似的接口，该层只是为了更好地抽象
 */
class ISSDrvProtocol {
 public:
  virtual ~ISSDrvProtocol() = default;

  /**
   * @brief 向显示驱动发送数据
   */
  virtual void write(uint8_t data) = 0;
};

struct SSDrvI2CProtocolConfig {
  uint8_t address;
  uint8_t sda;
  uint8_t scl;
  TwoWire& wire;
};

/**
 * @brief I2C示例接口
 */
class SSDrvI2CProtocol : public ISSDrvProtocol {
 private:
  SSDrvI2CProtocolConfig m_config;

 public:
  explicit SSDrvI2CProtocol(SSDrvI2CProtocolConfig config)
      : m_config(std::move(config)) {
    m_config.wire.begin(m_config.sda, m_config.scl);
  }
  SSDrvI2CProtocol() = delete;
  ~SSDrvI2CProtocol() { m_config.wire.end(); };

  /**
   * @brief 向显示驱动发送数据
   */
  void write(uint8_t data) override {
    m_config.wire.beginTransmission(m_config.address);
    m_config.wire.write(data);
    m_config.wire.endTransmission();
  };
};
