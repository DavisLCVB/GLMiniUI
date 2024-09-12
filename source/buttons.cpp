#include "buttons.hpp"
#include <cmath>
#include <iostream>
#include "constants.hpp"

namespace arch {

Button::Button(const Button& button) {
  _pos = button._pos;
  _size = button._size;
  _radius = button._radius;
  _thick = button._thick;
  _bgColor = button._bgColor;
  _lnColor = button._lnColor;
  _label = button._label;
}

Button& Button::operator=(const Button& button) {
  _pos = button._pos;
  _size = button._size;
  _radius = button._radius;
  _thick = button._thick;
  _bgColor = button._bgColor;
  _lnColor = button._lnColor;
  _label = button._label;
  return *this;
}

Color Button::lnColor() const {
  return _lnColor;
}

Button& Button::lnColor(const Color& lnColor) {
  _lnColor = lnColor;
  return *this;
}

Color Button::bgColor() const {
  return _bgColor;
}

Button& Button::bgColor(const Color& bgColor) {
  _bgColor = bgColor;
  return *this;
}

std::array<int, 2> Button::pos() const {
  return _pos;
}

Button& Button::pos(const std::array<int, 2>& pos) {
  _pos = pos;
  return *this;
}

std::array<int, 2> Button::size() const {
  return _size;
}

Button& Button::size(const std::array<int, 2>& size) {
  _size = size;
  return *this;
}

uint8_t Button::thick() const {
  return _thick;
}

Button& Button::thick(uint8_t thick) {
  _thick = thick;
  return *this;
}

uint8_t Button::radius() const {
  return _radius;
}

Button& Button::radius(uint8_t radius) {
  _radius = radius;
  return *this;
}

Label Button::label() const {
  return _label;
}

Button& Button::label(const Label& label) {
  _label = label;
  return *this;
}

void Button::draw() const {
  if (_radius <= 0) {
    _drawRectButton();
  } else {
    _drawRoundButton();
  }
  if (!_label.empty()) {
    _drawText();
  }
}

void Button::_drawRectButton() const {
  glColor4f(_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
  glBegin(GL_QUADS);
  glVertex2i(_pos[0], _pos[1]);
  glVertex2i(_pos[0] + _size[0], _pos[1]);
  glVertex2i(_pos[0] + _size[0], _pos[1] + _size[1]);
  glVertex2i(_pos[0], _pos[1] + _size[1]);
  glEnd();
  glColor4f(_lnColor.r, _lnColor.g, _lnColor.b, _lnColor.a);
  glLineWidth(_thick);
  auto halfThick = _thick / 2;
  glBegin(GL_LINES);
  // Bottom
  glVertex2i(_pos[0], _pos[1] + halfThick);
  glVertex2i(_pos[0] + _size[0], _pos[1] + halfThick);
  // Right
  glVertex2i(_pos[0] + _size[0] - halfThick, _pos[1]);
  glVertex2i(_pos[0] + _size[0] - halfThick, _pos[1] + _size[1]);
  // Top
  glVertex2i(_pos[0], _pos[1] + _size[1] - halfThick);
  glVertex2i(_pos[0] + _size[0], _pos[1] + _size[1] - halfThick);
  // Left
  glVertex2i(_pos[0] + halfThick, _pos[1]);
  glVertex2i(_pos[0] + halfThick, _pos[1] + _size[1]);
  glEnd();
}

void Button::_drawRoundButton() const {
  auto line{true};
  for (uint8_t i{0}; i < 2; i++) {
    if (line) {
      glColor4f(_lnColor.r, _lnColor.g, _lnColor.b, _lnColor.a);
    } else {
      glColor4f(_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
    }
    auto offset = _radius + _thick;
    auto rad = _radius;
    if (line) {
      offset -= _thick;
      rad += _thick;
    }
    auto theta = constants::PI / (constants::CURVE_MAX_SEGMENTS * 2);
    glBegin(GL_POLYGON);
    // Bottom left corner
    for (uint16_t i = 0; i <= constants::CURVE_MAX_SEGMENTS; i++) {
      auto angle = constants::PI + theta * i;
      auto x = _pos[0] + rad * cos(angle) + offset;
      auto y = _pos[1] + rad * sin(angle) + offset;
      glVertex2f(x, y);
    }
    // Bottom right corner
    for (uint16_t i = 0; i <= constants::CURVE_MAX_SEGMENTS; i++) {
      auto angle = (3 * constants::PI) / 2 + theta * i;
      auto x = _pos[0] + _size[0] + rad * cos(angle) - offset;
      auto y = _pos[1] + rad * sin(angle) + offset;
      glVertex2f(x, y);
    }
    // Top right corner
    for (uint16_t i = 0; i <= constants::CURVE_MAX_SEGMENTS; i++) {
      auto angle = theta * i;
      auto x = _pos[0] + _size[0] + rad * cos(angle) - offset;
      auto y = _pos[1] + _size[1] + rad * sin(angle) - offset;
      glVertex2f(x, y);
    }
    // Top left corner
    for (uint16_t i = 0; i <= constants::CURVE_MAX_SEGMENTS; i++) {
      auto angle = constants::PI / 2 + theta * i;
      auto x = _pos[0] + rad * cos(angle) + offset;
      auto y = _pos[1] + _size[1] + rad * sin(angle) - offset;
      glVertex2f(x, y);
    }
    glEnd();
    line = !line;
  }
}

void Button::_drawText() const {
  int32_t dx = (_size[0] - _label.width()) / 2;
  dx = dx < 0 ? 0 : dx;
  auto [fontPath, fontSize] = _label.font();
  int32_t dy = (_size[1] - fontSize * constants::TEXT_OFFSET) / 2;
  dy = dy < 0 ? 0 : dy;
  int32_t posX = _pos[0] + dx;
  int32_t posY = _pos[1] + dy;
  auto label_ = Label(_label).pos({posX, posY});
  label_.draw();
}

std::unique_ptr<ButtonManager> ButtonManager::_instance = nullptr;

ButtonManager& ButtonManager::getInstance() {
  if (!_instance) {
    _instance.reset(new ButtonManager());
  }
  return *_instance;
}

void ButtonManager::addButton(const std::string& name, const Button& button) {
  _buttons.insert(std::pair(name, button));
}

Button& ButtonManager::getButton(const std::string& name) {
  auto it = _buttons.find(name);
  if (it != _buttons.end()) {
    return it->second;
  }
  throw std::out_of_range("Button not found");
}

void ButtonManager::removeButton(const std::string& name) {
  _buttons.erase(name);
}

void ButtonManager::mouseEnterFunc(
    std::function<void(const std::string&, int x, int y)> func) {
  _mouseEnterFunc = func;
}

void ButtonManager::mouseLeaveFunc(
    std::function<void(const std::string&, int x, int y)> func) {
  _mouseLeaveFunc = func;
}

void ButtonManager::mousePressFunc(
    std::function<void(const std::string&, int x, int y)> func) {
  _mousePressFunc = func;
}

void ButtonManager::mouseReleaseFunc(
    std::function<void(const std::string&, int x, int y)> func) {
  _mouseReleaseFunc = func;
}

void ButtonManager::clickFunc(std::function<void(const std::string&)> func) {
  _clickFunc = func;
}

void ButtonManager::drawButtons() {
  for (auto& [name, button] : _buttons) {
    button.draw();
  }
}

void ButtonManager::mouseEnter(int x, int y) {
  for (auto& [name, button] : _buttons) {
    auto [posX, posY] = button.pos();
    auto [sizeX, sizeY] = button.size();
    if (x >= posX && x <= posX + sizeX && y >= posY && y <= posY + sizeY) {
      _mouseEnterFunc(name, x, y);
    }
  }
}

void ButtonManager::mouseLeave(int x, int y) {
  for (auto& [name, button] : _buttons) {
    auto [posX, posY] = button.pos();
    auto [sizeX, sizeY] = button.size();
    if (x < posX || x > posX + sizeX || y < posY || y > posY + sizeY) {
      _mouseLeaveFunc(name, x, y);
    }
  }
}

bool ButtonManager::mousePress(int x, int y) {
  for (auto& [name, button] : _buttons) {
    auto [posX, posY] = button.pos();
    auto [sizeX, sizeY] = button.size();
    if (x >= posX && x <= posX + sizeX && y >= posY && y <= posY + sizeY) {
      _mousePressFunc(name, x, y);
      return true;
    }
  }
  return false;
}

void ButtonManager::mouseRelease(int x, int y) {
  for (auto& [name, button] : _buttons) {
    auto [posX, posY] = button.pos();
    auto [sizeX, sizeY] = button.size();
    if (x >= posX && x <= posX + sizeX && y >= posY && y <= posY + sizeY) {
      _mouseReleaseFunc(name, x, y);
      _clickFunc(name);
    }
  }
}

}  // namespace arch
