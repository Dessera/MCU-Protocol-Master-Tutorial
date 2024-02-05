#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "ssdrv/context.hpp"
#include "ssdrv/create.hpp"
#include "ssdrv/utils/namesapce.hpp"

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
class BehaviorBuilder : public IBehavior {
 private:
  // ! Self is just a name, there is only ONE instance during the add chain
  using Self = BehaviorBuilder;
  std::vector<std::unique_ptr<IBehavior>> m_behaviors{};

 public:
  BehaviorBuilder() = default;
  explicit BehaviorBuilder(std::size_t size) : m_behaviors(size) {}
  ~BehaviorBuilder() = default;

  inline Self& add(std::unique_ptr<IBehavior> behavior) {
    m_behaviors.push_back(std::move(behavior));
    return *this;
  }

  void apply(std::shared_ptr<context::Context> context) override {
    std::for_each(m_behaviors.begin(), m_behaviors.end(),
                  [&context](std::unique_ptr<IBehavior>& behavior) {
                    behavior->apply(context);
                  });
  }
};

}  // namespace behavior

SSDRV_NS_END
