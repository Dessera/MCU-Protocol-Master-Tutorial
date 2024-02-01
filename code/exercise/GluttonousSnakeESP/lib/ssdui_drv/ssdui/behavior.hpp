#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "core.hpp"

class SSDrvBehavior {
 public:
  virtual ~SSDrvBehavior() = default;

  /**
   * @brief 应用行为
   */
  virtual void apply(std::shared_ptr<SSDrvContext> context) = 0;
};

class SSDrvBehaviorBuilder {
 private:
  using Self = SSDrvBehaviorBuilder;
  std::vector<std::unique_ptr<SSDrvBehavior>> m_behaviors{};
  std::shared_ptr<SSDrvContext> m_context{nullptr};

 public:
  SSDrvBehaviorBuilder() = default;
  explicit SSDrvBehaviorBuilder(std::shared_ptr<SSDrvContext> context)
      : m_context(std::move(context)) {}
  ~SSDrvBehaviorBuilder() = default;

  inline Self add(std::unique_ptr<SSDrvBehavior> behavior) {
    m_behaviors.push_back(std::move(behavior));
    return *this;
  }

  inline Self context(std::shared_ptr<SSDrvContext> context) {
    m_context = std::move(context);
    return *this;
  }

  inline void apply() {
    std::for_each(m_behaviors.begin(), m_behaviors.end(),
                  [this](std::unique_ptr<SSDrvBehavior>& behavior) {
                    behavior->apply(m_context);
                  });
  }
};
