#pragma once
#include <Arduino.h>
#include <Wire.h>

#include <cstdint>
#include <numeric>
#include <vector>

#include "ssdrv/create.hpp"
#include "ssdrv/utils/namesapce.hpp"

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
  // virtual std::size_t write(uint8_t data) = 0;
  virtual std::size_t write(const std::vector<uint8_t>& data) = 0;
};

/**
 * @brief 通信接口配置对象
 *
 */
struct I2CProtocolConfig {
  uint8_t address;
  uint8_t sda;
  uint8_t scl;
};

/**
 * @brief I2C示例接口
 */
class I2CProtocol : public IProtocol {
 private:
  TwoWire& m_wire;
  I2CProtocolConfig m_config;

 public:
  explicit I2CProtocol(TwoWire& wire, I2CProtocolConfig config)
      : m_wire(wire), m_config(std::move(config)) {
    m_wire.setPins(m_config.sda, m_config.scl);
    m_wire.begin();
  }
  I2CProtocol() = delete;
  ~I2CProtocol() { m_wire.end(); };

  /**
   * @brief 向显示驱动发送数据
   */
  std::size_t write(const std::vector<uint8_t>& data) override {
    m_wire.beginTransmission(m_config.address);

    std::size_t send = std::accumulate(
        data.begin(), data.end(), 0,
        [&](std::size_t acc, uint8_t d) { return acc + m_wire.write(d); });

    m_wire.endTransmission();

    return send;
  };
};

}  // namespace protocol

SSDRV_NS_END
