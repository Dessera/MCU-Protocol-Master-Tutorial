#pragma once

#include <memory>

/**
 * @brief Unique 指针的创建器
 *
 * @tparam T 创建类型
 */
template <typename T>
class CreateToUniquePtr {
 public:
  template <typename D = T, typename... Args>
  static std::unique_ptr<T> create(Args&&... args) {
    return std::unique_ptr<T>(new D(std::forward<Args>(args)...));
  }
};

/**
 * @brief Shared 指针的创建器
 *
 * @tparam T 创建类型
 */
template <typename T>
class CreateToSharedPtr {
 public:
  template <typename D = T, typename... Args>
  static std::shared_ptr<T> create(Args&&... args) {
    return std::shared_ptr<T>(new D(std::forward<Args>(args)...));
  }
};
