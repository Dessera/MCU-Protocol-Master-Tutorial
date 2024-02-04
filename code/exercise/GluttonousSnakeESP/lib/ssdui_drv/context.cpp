#include "ssdrv/context.hpp"

#include "ssdrv/behaviors/initialize.hpp"

SSDRV_NS_BEGIN

namespace context {

Context::Context(std::unique_ptr<protocol::IProtocol> protocol, Config config)
    : m_protocol(std::move(protocol)), m_config(std::move(config)) {}

void Context::initialize() {
  behaviors::InitializationBehavior().apply(shared_from_this());
}

}  // namespace context

SSDRV_NS_END
