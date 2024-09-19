#include "label.hpp"
#include <iostream>
#include <stdexcept>
#include "utils.hpp"

namespace arch
{

  Label::Label(const Label &label)
  {
    _text = label._text;
    _pos = label._pos;
    _color = label._color;
    _fontPath = label._fontPath;
    _fontSize = label._fontSize;
  }

  Label &Label::operator=(const Label &label)
  {
    _text = label._text;
    _pos = label._pos;
    _color = label._color;
    _fontPath = label._fontPath;
    _fontSize = label._fontSize;
    return *this;
  }

  Label &Label::text(const std::string &text)
  {
    _text = text;
    return *this;
  }

  std::string Label::text() const
  {
    return _text;
  }

  Label &Label::pos(const array<int, 2> &pos)
  {
    _pos = pos;
    return *this;
  }

  array<int, 2> Label::pos() const
  {
    return _pos;
  }

  Label &Label::color(const Color &color)
  {
    _color = color;
    return *this;
  }

  Color Label::color() const
  {
    return _color;
  }

  Label &Label::font(const std::string &fontPath, uint16_t fontSize)
  {
    _fontPath = fontPath;
    _fontSize = fontSize;
    auto &fl = FontLoader::getInstance();
    if (fl._fonts.find(std::pair(fontPath, fontSize)) == fl._fonts.end())
    {
      fl.loadFont(fontPath, fontSize);
    }
    return *this;
  }

  std::pair<std::string, uint16_t> Label::font() const
  {
    return std::pair(_fontPath, _fontSize);
  }

  void Label::draw() const
  {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(_color.r, _color.g, _color.b, _color.a);

    auto &fontLoader = FontLoader::getInstance();
    auto x = _pos[0];
    for (const char &c : _text)
    {
      Character ch = fontLoader._fonts[std::pair(_fontPath, _fontSize)][c];
      float xpos = x + ch.bearing[0];
      float ypos = _pos[1] - (ch.size[1] - ch.bearing[1]);
      float w = ch.size[0];
      float h = ch.size[1];
      glBindTexture(GL_TEXTURE_2D, ch.texture);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex2f(xpos, ypos);
      glTexCoord2f(1.0f, 1.0f);
      glVertex2f(xpos + w, ypos);
      glTexCoord2f(1.0f, 0.0f);
      glVertex2f(xpos + w, ypos + h);
      glTexCoord2f(0.0f, 0.0f);
      glVertex2f(xpos, ypos + h);
      glEnd();

      x += (ch.advance >> 6);
    }
    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
  }

  bool Label::empty() const
  {
    return _text.empty();
  }

  int Label::width() const
  {
    auto &fontLoader = FontLoader::getInstance();
    int width = 0;
    if (_text.empty())
      return width;
    if (fontLoader._fonts.find(std::pair(_fontPath, _fontSize)) ==
        fontLoader._fonts.end())
    {
      fontLoader.loadFont(_fontPath, _fontSize);
    }
    for (const char &c : _text)
    {
      Character ch = fontLoader._fonts[std::pair(_fontPath, _fontSize)][c];
      width += (ch.advance >> 6);
    }
    return width;
  }

  std::unique_ptr<FontLoader> FontLoader::_instance = nullptr;

  FontLoader &FontLoader::getInstance()
  {
    if (!_instance)
    {
      _instance.reset(new FontLoader());
    }
    return *_instance;
  }

  void FontLoader::loadFont(const std::string &path, uint32_t fontSize)
  {
    if (FT_Init_FreeType(&_ft))
    {
      throw std::runtime_error("Error: Could not init freetype library");
    }
    if (FT_New_Face(_ft, path.c_str(), 0, &_face))
    {
      throw std::runtime_error("Error: Could not open font file " + path);
    }
    FT_Set_Pixel_Sizes(_face, 0, fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char c = 0; c < 128; c++)
    {
      if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
      {
        std::cerr << "Error: Failed to load glyph" << std::endl;
        continue;
      }
      uint32_t texture;
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, _face->glyph->bitmap.width,
                   _face->glyph->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE,
                   _face->glyph->bitmap.buffer);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      Character character = {
          texture,
          {_face->glyph->bitmap.width, _face->glyph->bitmap.rows},
          {_face->glyph->bitmap_left, _face->glyph->bitmap_top},
          _face->glyph->advance.x};
      _fonts[std::pair(path, fontSize)].insert(
          std::pair<char, Character>(c, character));
    }
    FT_Done_Face(_face);
    FT_Done_FreeType(_ft);
  }

} // namespace arch
