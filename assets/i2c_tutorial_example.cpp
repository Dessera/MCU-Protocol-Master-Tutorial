#include <Arduino.h>
#include <Wire.h>

#include <cstddef>
#include <cstdint>
#include <glut_root.hh>
#include <memory>
#include <mutex>
#include <ssd1306.hh>
#include <ssd1306_command.hh>
#include <ssd1306_config.hh>
#include <ssd1306_renderer.hh>
#include <ssd1306_ticker.hh>

#include "glut_platform.hh"

class MPMTRenderer {
 private:
  std::mutex mtx_{};

  // 需要实现的函数：发送一段指令
  size_t _command_impl(uint8_t* data, size_t size) {
    size_t bytes_sent = 0;

    while (bytes_sent < size) {
      Wire.beginTransmission(0x3C);
      Wire.write(0x00);

      auto bytes_send_once_round =
          Wire.write(data + bytes_sent, size - bytes_sent);

      if (Wire.endTransmission() != 0) {
        break;
      }
      bytes_sent += bytes_send_once_round;
    }

    return bytes_sent;
  }

  // 需要实现的函数：发送一段数据
  size_t _data_impl(uint8_t* data, size_t size) {
    size_t bytes_sent = 0;

    while (bytes_sent < size) {
      Wire.beginTransmission(0x3C);
      Wire.write(0x40);

      auto bytes_send_once_round =
          Wire.write(data + bytes_sent, size - bytes_sent);

      if (Wire.endTransmission() != 0) {
        break;
      }
      bytes_sent += bytes_send_once_round;
    }

    return bytes_sent;
  }

 public:
  MPMTRenderer() {
    Wire.setClock(400000);
    Wire.begin();
  }

  ~MPMTRenderer() { Wire.end(); }

  std::size_t command(std::span<uint8_t> data) {
    std::lock_guard<std::mutex> lock{mtx_};
    return _command_impl(data.data(), data.size());
  }
  std::size_t data(std::span<uint8_t> data) {
    std::lock_guard<std::mutex> lock{mtx_};
    return _data_impl(data.data(), data.size());
  }
};

class MPMTPlatform {
 public:
  using Renderer = MPMTRenderer;
  using Config = SSD1306::Config;
  using Event = GlutEvent;

  using Store = GlutStore;
};

std::unique_ptr<SSD1306::Ticker<MPMTPlatform>> ticker{nullptr};

void setup() {
  namespace Context = SSDUI::Context;

  Serial.begin(115200);

  auto opt =
      Context::Builder<MPMTPlatform>()
          .set_config(SSD1306::Config{
              .horizontal_flip = true, .vertical_flip = true, .fps = 30})
          //  .set_renderer(std::make_unique<SSD1306::Renderer>(&Wire, 0x3C))
          .set_renderer(std::make_unique<MPMTRenderer>())
          .set_root(std::make_unique<GlutRoot<MPMTPlatform>>())
          .build();

  if (!opt.has_value()) {
    Serial.println("Failed to create context");
    return;
  }

  auto context = std::move(opt.value());

  context->enable_event_manager();

  SSD1306::Initializer<MPMTPlatform>()(context.get());

  ticker =
      Context::Context<MPMTPlatform>::to_ticker<SSD1306::Ticker<MPMTPlatform>>(
          std::move(context));
}

void loop() { delay(100); }
