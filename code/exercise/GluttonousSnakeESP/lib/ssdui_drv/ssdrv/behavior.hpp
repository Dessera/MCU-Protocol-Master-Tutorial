#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "context.hpp"
#include "ssdrv/constant.hpp"
#include "ssdrv/create.hpp"

SSDRV_NS_BEGIN

namespace behavior {

/**
 * @brief 行为接口，表示一种操作
 *
 */
class IBehavior : public CreateToUniquePtr<IBehavior> {
 public:
  virtual ~IBehavior() = default;

  /**
   * @brief 应用行为
   */
  virtual void apply(std::shared_ptr<context::Context> context) = 0;
};

/**
 * @brief 行为构建器，用于构建行为链
 *
 */
class BehaviorBuilder {
 private:
  // ! Self is just a name, there is only ONE instance during the add chain
  using Self = BehaviorBuilder;
  std::vector<std::unique_ptr<IBehavior>> m_behaviors{};
  std::shared_ptr<context::Context> m_context{nullptr};

 public:
  BehaviorBuilder() = default;
  explicit BehaviorBuilder(std::shared_ptr<context::Context> context)
      : m_context(std::move(context)) {}
  explicit BehaviorBuilder(std::size_t size) : m_behaviors(size) {}
  ~BehaviorBuilder() = default;

  inline Self& add(std::unique_ptr<IBehavior> behavior) {
    m_behaviors.push_back(std::move(behavior));
    return *this;
  }

  inline Self& context(std::shared_ptr<context::Context> context) {
    m_context = std::move(context);
    return *this;
  }

  inline void apply() {
    if (m_context == nullptr) {
      // ! In normal case, should throw an exception
      // ! But may mcu compiler does not support exception
      // ? Thinking to use an Result Type
      return;
    }
    std::for_each(m_behaviors.begin(), m_behaviors.end(),
                  [this](std::unique_ptr<IBehavior>& behavior) {
                    behavior->apply(m_context);
                  });
  }
};

}  // namespace behavior

SSDRV_NS_END
