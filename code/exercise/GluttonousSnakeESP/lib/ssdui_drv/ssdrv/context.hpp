#pragma once

#include <memory>

#include "ssdrv/protocol.hpp"
#include "ssdrv/utils/namesapce.hpp"

SSDRV_NS_BEGIN

namespace context {

/**
 * @brief 内存寻址模式
 */
enum class AddressingMode : uint8_t {
  HORIZONTAL = 0x00,
  VERTICAL = 0x01,
  PAGE = 0x02,
};

enum class ComPinsConfig : uint8_t {
  SEQUENTIAL = 0x02,
  SEQUENTIAL_REMAPPED = 0x22,
  ALTERNATIVE = 0x12,
  ALTERNATIVE_REMAPPED = 0x32,
};

/**
 * @brief OLED显示驱动上下文配置对象
 */
class Config {
 public:
  static constexpr uint8_t DEFAULT_WIDTH = 128;
  static constexpr uint8_t DEFAULT_PAGE = 8;
  static constexpr uint8_t DEFAULT_PAGE_SIZE = 8;
  static constexpr AddressingMode DEFAULT_ADDRESSING_MODE =
      AddressingMode::PAGE;
  static constexpr uint8_t DEFAULT_RATIO = 0x00;
  static constexpr uint8_t DEFAULT_FREQUENCY = 0x08;
  static constexpr uint8_t DEFAULT_PRECHARGE_PHASE1 = 0x02;
  static constexpr uint8_t DEFAULT_PRECHARGE_PHASE2 = 0x02;
  static constexpr uint8_t DEFAULT_VCOMH_LEVEL = 0x20;
  static constexpr uint8_t DEFAULT_CONTRAST = 0x7F;
  static constexpr uint8_t DEFAULT_INIT_PAGE_START = 0;
  static constexpr ComPinsConfig DEFAULT_COM_PINS = ComPinsConfig::ALTERNATIVE;

 private:
  /**
   * @brief OLED显示驱动显示宽度
   * @note 可以自定义，该条目实际上是软件限制
   */
  uint8_t width{DEFAULT_WIDTH};

  /**
   * @brief OLED显示驱动显示页数
   * @note 可以自定义，该条目实际上是软件限制
   */
  uint8_t page{DEFAULT_PAGE};

  /**
   * @brief OLED显示驱动寻址模式
   */
  AddressingMode addressing_mode{DEFAULT_ADDRESSING_MODE};

  /**
   * @brief 初始化显示的起始页
   */
  uint8_t init_page_start{0};

  /**
   * @brief 初始化显示的结束页
   * @note 在页寻址模式下，该条目无效
   */
  uint8_t init_page_end{DEFAULT_PAGE - 1};

  /**
   * @brief 初始化显示的起始列
   */
  uint8_t init_column_start{0};

  /**
   * @brief 初始化显示的结束列
   * @note 在页寻址模式下，该条目无效
   */
  uint8_t init_column_end{DEFAULT_WIDTH - 1};

  /**
   * @brief 时钟分频
   */
  uint8_t clock_ratio{DEFAULT_RATIO};

  /**
   * @brief 振荡频率
   */
  uint8_t clock_frequency{DEFAULT_FREQUENCY};

  /**
   * @brief 预充电周期1
   */
  uint8_t precharge_phase1{DEFAULT_PRECHARGE_PHASE1};

  /**
   * @brief 预充电周期2
   */
  uint8_t precharge_phase2{DEFAULT_PRECHARGE_PHASE2};

  /**
   * @brief VCOMH电压
   */
  uint8_t vcomh_level{DEFAULT_VCOMH_LEVEL};

  /**
   * @brief 对比度
   */
  uint8_t contrast{DEFAULT_CONTRAST};

  /**
   * @brief 显示全亮
   */
  bool entire_display_on{false};

  /**
   * @brief 显示反色
   */
  bool inverse_display{false};

  /**
   * @brief 显示开关
   */
  bool display_on{true};

  /**
   * @brief 初始显示行
   */
  uint8_t start_line{0};

  /**
   * @brief 左右翻转
   */
  bool horizontal_flip{false};

  /**
   * @brief 上下翻转
   */
  bool vertical_flip{false};

  /**
   * @brief 启用通道数
   * @note
   * OLED命令中，输入的ratio会被+1,这里自动处理的该情况，请填写正确的通道数。
   * 另外，该条目是硬件限制
   */
  uint8_t multiplex_ratio{DEFAULT_PAGE_SIZE * DEFAULT_PAGE};

  /**
   * @brief 显示偏移
   */
  uint8_t display_offset{0};

  /**
   * @brief COM引脚配置
   */
  ComPinsConfig com_pins{DEFAULT_COM_PINS};

 public:
  // ! Config is immutable(for now), so just provide getters
  inline uint8_t get_width() const { return width; }
  inline uint8_t get_page() const { return page; }
  inline uint8_t get_height() const { return page * DEFAULT_PAGE_SIZE; }
  inline AddressingMode get_addressing_mode() const { return addressing_mode; }
  inline uint8_t get_init_page_start() const { return init_page_start; }
  inline uint8_t get_init_page_end() const { return init_page_end; }
  inline uint8_t get_init_column_start() const { return init_column_start; }
  inline uint8_t get_init_column_end() const { return init_column_end; }
  inline uint8_t get_clock_ratio() const { return clock_ratio; }
  inline uint8_t get_clock_frequency() const { return clock_frequency; }
  inline uint8_t get_precharge_phase1() const { return precharge_phase1; }
  inline uint8_t get_precharge_phase2() const { return precharge_phase2; }
  inline uint8_t get_vcomh_level() const { return vcomh_level; }
  inline uint8_t get_contrast() const { return contrast; }
  inline bool get_entire_display_on() const { return entire_display_on; }
  inline bool get_inverse_display() const { return inverse_display; }
  inline bool get_display_on() const { return display_on; }
  inline uint8_t get_start_line() const { return start_line; }
  inline bool get_horizontal_flip() const { return horizontal_flip; }
  inline bool get_vertical_flip() const { return vertical_flip; }
  inline uint8_t get_multiplex_ratio() const { return multiplex_ratio; }
  inline uint8_t get_display_offset() const { return display_offset; }
  inline ComPinsConfig get_com_pins() const { return com_pins; }
};

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
