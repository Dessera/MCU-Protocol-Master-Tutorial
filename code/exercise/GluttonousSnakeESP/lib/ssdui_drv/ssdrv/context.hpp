#pragma once

#include <memory>

#include "ssdrv/config.hpp"
#include "ssdrv/protocol.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace context {

/**
 * @brief OLED显示驱动上下文，需要配合Behavior类使用
 */
class Context : public CreateToSharedPtr<Context>,
                public std::enable_shared_from_this<Context> {
 private:
  std::unique_ptr<protocol::IProtocol> m_protocol;
  Config m_config;

 public:
  explicit Context(std::unique_ptr<protocol::IProtocol> protocol,
                   Config config = Config());

  // I really don't like explicit initialize method, but I have to do this
  void initialize();

  inline Config& config() { return m_config; }
  inline protocol::IProtocol& protocol() { return *m_protocol; }
};

};  // namespace context

SSDRV_NS_END
