#pragma once
#include <GL/glut.h>
#include <functional>
#include <memory>
#include <mutex>
#include "label.hpp"
#include "utils.hpp"

namespace arch {
class ButtonManager;

class Button {
 public:
  Button() = default;
  Button(const Button&);
  auto operator=(const Button&) -> Button&;
  auto lnColor() const -> Color;
  auto lnColor(const Color& lnColor) -> Button&;
  auto bgColor() const -> Color;
  auto bgColor(const Color& bgColor) -> Button&;
  auto pos() const -> std::array<int, 2>;
  auto pos(const std::array<int, 2>& pos) -> Button&;
  auto size() const -> std::array<int, 2>;
  auto size(const std::array<int, 2>& size) -> Button&;
  auto thick() const -> uint8_t;
  auto thick(uint8_t thick) -> Button&;
  auto radius() const -> uint8_t;
  auto radius(uint8_t radius) -> Button&;
  auto label() const -> Label;
  auto label(const Label& label) -> Button&;
  auto draw() const -> void;

 private:
  Color _lnColor{0.0, 0.0, 0.0, 1.0};
  Color _bgColor{1.0, 1.0, 1.0, 1.0};
  std::array<int, 2> _pos{0, 0};
  std::array<int, 2> _size{1, 1};
  uint8_t _thick{1};
  uint8_t _radius{0};
  Label _label{};
  auto _drawRectButton() const -> void;
  auto _drawRoundButton() const -> void;
  auto _drawText() const -> void;
  friend class ButtonManager;
};

class ButtonManager {
 public:
  static auto getInstance() -> ButtonManager&;
  auto addButton(const std::string& name, const Button& button) -> void;
  auto getButton(const std::string& name) -> Button&;
  auto removeButton(const std::string& name) -> void;
  auto mouseEnterFunc(
      std::function<void(const std::string&, int x, int y)> func) -> void;
  auto mouseLeaveFunc(
      std::function<void(const std::string&, int x, int y)> func) -> void;
  auto mousePressFunc(
      std::function<void(const std::string&, int x, int y)> func) -> void;
  auto mouseReleaseFunc(
      std::function<void(const std::string&, int x, int y)> func) -> void;
  auto clickFunc(std::function<void(const std::string&)> func) -> void;
  auto drawButtons() -> void;
  auto mouseEnter(int x, int y) -> void;
  auto mouseLeave(int x, int y) -> void;
  auto mousePress(int x, int y) -> bool;
  auto mouseRelease(int x, int y) -> void;

 private:
  std::function<void(const std::string&, int x, int y)> _mouseEnterFunc{
      [](const std::string&, int, int) {
      }};
  std::function<void(const std::string&, int x, int y)> _mouseLeaveFunc{
      [](const std::string&, int, int) {
      }};
  std::function<void(const std::string&, int x, int y)> _mousePressFunc{
      [](const std::string&, int, int) {
        return false;
      }};
  std::function<void(const std::string&, int x, int y)> _mouseReleaseFunc{
      [](const std::string&, int, int) {
      }};
  std::function<void(const std::string&)> _clickFunc{[](const std::string&) {
  }};
  ButtonManager() = default;
  std::multimap<std::string, Button> _buttons{};
};

}  // namespace arch
