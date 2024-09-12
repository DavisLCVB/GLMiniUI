#pragma once
#include <GL/glut.h>
#include <ft2build.h>
#include <array>
#include <map>
#include "utils.hpp"
#include FT_FREETYPE_H
#include <memory>

namespace arch {
template <typename T, int i>
using array = std::array<T, i>;

class Label {
 public:
  Label() = default;
  Label(const Label&);
  Label& operator=(const Label&);
  auto text() const -> std::string;
  auto text(const std::string& text) -> Label&;
  auto pos() const -> array<int, 2>;
  auto pos(const array<int, 2>& pos) -> Label&;
  auto color() const -> Color;
  auto color(const Color& color) -> Label&;
  auto font() const -> std::pair<std::string, uint16_t>;
  auto font(const std::string& fontPath, uint16_t fontSize) -> Label&;
  auto draw() const -> void;
  auto empty() const -> bool;
  auto width() const -> int;

 private:
  std::string _text{""};
  array<int, 2> _pos{0, 0};
  Color _color{.0, .0, 1.0, 1.0};
  std::string _fontPath{"Arial"};
  uint16_t _fontSize{48};
};

struct Character {
  uint32_t texture;
  array<uint32_t, 2> size;
  array<int, 2> bearing;
  int64_t advance;
};

class FontLoader {
 public:
  void loadFont(const std::string& path, uint32_t fontSize);
  static FontLoader& getInstance();

 private:
  FontLoader() = default;
  static std::unique_ptr<FontLoader> _instance;
  FT_Library _ft;
  FT_Face _face;
  std::map<std::pair<std::string, uint16_t>, std::map<char, Character>> _fonts;
  friend class Label;
};

}  // namespace arch
