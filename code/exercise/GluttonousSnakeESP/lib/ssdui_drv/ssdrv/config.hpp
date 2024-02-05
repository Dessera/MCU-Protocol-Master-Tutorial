#pragma once

#include <cstdint>

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
  /**
   * @brief 默认显示宽度
   */
  static constexpr uint8_t DEFAULT_WIDTH = 128;

  /**
   * @brief 默认显示页数
   */
  static constexpr uint8_t DEFAULT_PAGE = 8;

  /**
   * @brief 默认页大小
   */
  static constexpr uint8_t DEFAULT_PAGE_SIZE = 8;

  /**
   * @brief 默认初始化起始页
   */
  static constexpr uint8_t DEFAULT_INIT_PAGE_START = 0;

  /**
   * @brief 默认初始化结束页
   */
  static constexpr uint8_t DEFAULT_INIT_PAGE_END = DEFAULT_PAGE - 1;

  /**
   * @brief 默认初始化起始列
   */
  static constexpr uint8_t DEFAULT_INIT_COLUMN_START = 0;

  /**
   * @brief 默认初始化结束列
   */
  static constexpr uint8_t DEFAULT_INIT_COLUMN_END = DEFAULT_WIDTH - 1;

  /**
   * @brief 默认寻址模式
   */
  static constexpr AddressingMode DEFAULT_ADDRESSING_MODE =
      AddressingMode::PAGE;

  /**
   * @brief 默认时钟分频
   */
  static constexpr uint8_t DEFAULT_RATIO = 0x00;

  /**
   * @brief 默认振荡频率
   */
  static constexpr uint8_t DEFAULT_FREQUENCY = 0x08;

  /**
   * @brief 默认预充电周期1
   */
  static constexpr uint8_t DEFAULT_PRECHARGE_PHASE1 = 0x01;

  /**
   * @brief 默认预充电周期2
   */
  static constexpr uint8_t DEFAULT_PRECHARGE_PHASE2 = 0x0F;

  /**
   * @brief 默认VCOMH电压
   * TODO: Maybe refactor this to an enum
   */
  static constexpr uint8_t DEFAULT_VCOMH_LEVEL = 0x40;

  /**
   * @brief 默认对比度
   */
  static constexpr uint8_t DEFAULT_CONTRAST = 0x7F;

  /**
   * @brief 默认Com引脚配置
   */
  static constexpr ComPinsConfig DEFAULT_COM_PINS = ComPinsConfig::ALTERNATIVE;

  /**
   * @brief 默认显示全亮
   */
  static constexpr bool DEFAULT_ENTIRE_DISPLAY_ON = false;

  /**
   * @brief 默认显示反色
   */
  static constexpr bool DEFAULT_INVERSE_DISPLAY = false;

  /**
   * @brief 默认显示开关
   */
  static constexpr bool DEFAULT_DISPLAY_ON = true;

  /**
   * @brief 默认显示行
   */
  static constexpr uint8_t DEFAULT_START_LINE = 0;

  /**
   * @brief 默认左右翻转
   */
  static constexpr bool DEFAULT_HORIZONTAL_FLIP = false;

  /**
   * @brief 默认上下翻转
   */
  static constexpr bool DEFAULT_VERTICAL_FLIP = false;

  /**
   * @brief 默认显示偏移
   */
  static constexpr uint8_t DEFAULT_DISPLAY_OFFSET = 0;

  /**
   * @brief 默认通道数
   */
  static constexpr uint8_t DEFAULT_MULTIPLEX_RATIO =
      DEFAULT_PAGE_SIZE * DEFAULT_PAGE;

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
   * @brief 显示的起始页
   */
  uint8_t page_start{DEFAULT_INIT_PAGE_START};

  /**
   * @brief 初始化显示的结束页
   * @note 在页寻址模式下，该条目无效
   */
  uint8_t page_end{DEFAULT_INIT_PAGE_END};

  /**
   * @brief 初始化显示的起始列
   */
  uint8_t column_start{DEFAULT_INIT_COLUMN_START};

  /**
   * @brief 初始化显示的结束列
   * @note 在页寻址模式下，该条目无效
   */
  uint8_t column_end{DEFAULT_INIT_COLUMN_END};

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
  bool entire_display_on{DEFAULT_ENTIRE_DISPLAY_ON};

  /**
   * @brief 显示反色
   */
  bool inverse_display{DEFAULT_INVERSE_DISPLAY};

  /**
   * @brief 显示开关
   */
  bool display_on{DEFAULT_DISPLAY_ON};

  /**
   * @brief 初始显示行
   */
  uint8_t start_line{DEFAULT_START_LINE};

  /**
   * @brief 左右翻转
   */
  bool horizontal_flip{DEFAULT_HORIZONTAL_FLIP};

  /**
   * @brief 上下翻转
   */
  bool vertical_flip{DEFAULT_VERTICAL_FLIP};

  /**
   * @brief 启用通道数
   * @note
   * OLED命令中，输入的ratio会被+1,这里自动处理的该情况，请填写正确的通道数。
   * 另外，该条目是硬件限制
   */
  uint8_t multiplex_ratio{DEFAULT_MULTIPLEX_RATIO};

  /**
   * @brief 显示偏移
   */
  uint8_t display_offset{DEFAULT_DISPLAY_OFFSET};

  /**
   * @brief COM引脚配置
   */
  ComPinsConfig com_pins{DEFAULT_COM_PINS};

 public:
  [[nodiscard]] inline uint8_t get_width() const { return width; }
  [[nodiscard]] inline uint8_t get_page() const { return page; }
  [[nodiscard]] inline uint8_t get_height() const {
    return page * DEFAULT_PAGE_SIZE;
  }
  [[nodiscard]] inline AddressingMode get_addressing_mode() const {
    return addressing_mode;
  }
  [[nodiscard]] inline uint8_t get_page_start() const { return page_start; }
  [[nodiscard]] inline uint8_t get_page_end() const { return page_end; }
  [[nodiscard]] inline uint8_t get_column_start() const { return column_start; }
  [[nodiscard]] inline uint8_t get_column_end() const { return column_end; }
  [[nodiscard]] inline uint8_t get_clock_ratio() const { return clock_ratio; }
  [[nodiscard]] inline uint8_t get_clock_frequency() const {
    return clock_frequency;
  }
  [[nodiscard]] inline uint8_t get_precharge_phase1() const {
    return precharge_phase1;
  }
  [[nodiscard]] inline uint8_t get_precharge_phase2() const {
    return precharge_phase2;
  }
  [[nodiscard]] inline uint8_t get_vcomh_level() const { return vcomh_level; }
  [[nodiscard]] inline uint8_t get_contrast() const { return contrast; }
  [[nodiscard]] inline bool get_entire_display_on() const {
    return entire_display_on;
  }
  [[nodiscard]] inline bool get_inverse_display() const {
    return inverse_display;
  }
  [[nodiscard]] inline bool get_display_on() const { return display_on; }
  [[nodiscard]] inline uint8_t get_start_line() const { return start_line; }
  [[nodiscard]] inline bool get_horizontal_flip() const {
    return horizontal_flip;
  }
  [[nodiscard]] inline bool get_vertical_flip() const { return vertical_flip; }
  [[nodiscard]] inline uint8_t get_multiplex_ratio() const {
    return multiplex_ratio;
  }
  [[nodiscard]] inline uint8_t get_display_offset() const {
    return display_offset;
  }
  [[nodiscard]] inline ComPinsConfig get_com_pins() const { return com_pins; }

  // ! Methods below just mutate the object, not really take effect
  // TODO: Methods below should have a boundary check
  // width & page is immutable
  inline void set_addressing_mode(AddressingMode mode) {
    addressing_mode = mode;
  }
  inline void set_page_start(uint8_t start) { page_start = start; }
  inline void set_page_end(uint8_t end) { page_end = end; }
  inline void set_column_start(uint8_t start) { column_start = start; }
  inline void set_column_end(uint8_t end) { column_end = end; }
  // did not provide some hw & clock related methods
  inline void set_contrast(uint8_t contrast) { this->contrast = contrast; }
  inline void set_entire_display_on(bool entire_display_on) {
    this->entire_display_on = entire_display_on;
  }
  inline void set_inverse_display(bool inverse_display) {
    this->inverse_display = inverse_display;
  }
  inline void set_display_on(bool display_on) { this->display_on = display_on; }
  inline void set_start_line(uint8_t start_line) {
    this->start_line = start_line;
  }
  inline void set_horizontal_flip(bool horizontal_flip) {
    this->horizontal_flip = horizontal_flip;
  }
  inline void set_vertical_flip(bool vertical_flip) {
    this->vertical_flip = vertical_flip;
  }
  inline void set_display_offset(uint8_t display_offset) {
    this->display_offset = display_offset;
  }
};

}  // namespace context

SSDRV_NS_END
