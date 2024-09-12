#include <GL/glut.h>
#include <GLMiniUI>
#include <cmath>
#include <cstdint>
#include <iostream>
arch::Color black = {34, 40, 49, 255};
arch::Color white = {238, 238, 238, 255};
arch::Color gray = {57, 62, 70, 255};
arch::Color smoke = {200, 200, 200, 255};
arch::Color cyan = {0, 173, 181, 255};
arch::Label text{};
arch::Color bgColor = white;

namespace arch {
void updatePos(int val);

class Selector {
 public:
  void draw() {
    glColor4f(_lnColor.r, _lnColor.g, _lnColor.b, _lnColor.a);
    glLineWidth(_thick);
    glBegin(GL_LINE_LOOP);
    glVertex2f(_pos[0], _pos[1]);
    glVertex2f(_pos[0] + 1, _pos[1] + 2);
    glVertex2f(_pos[0] + 1, _pos[1] + _size[1] - 2);
    glVertex2f(_pos[0], _pos[1] + _size[1]);
    glVertex2f(_pos[0] - 1, _pos[1] + _size[1] - 2);
    glVertex2f(_pos[0] - 1, _pos[1] + 2);
    glEnd();
  }

  void changePos(const std::array<int, 2>& pos) {
    _targetPos = pos;
    _dx = _targetPos[0] - _pos[0];
    _dy = _targetPos[1] - _pos[1];
  }

  void animate() {
    _isAnimating = true;
    glutTimerFunc(16, updatePos, 0);
  }

  Selector() = default;

 private:
  std::array<int, 2> _pos{45, 700};
  std::array<int, 2> _size{2, 40};
  std::array<int, 2> _targetPos{50, 550};
  uint8_t _thick{2};
  uint8_t _radius{10};
  Color _lnColor{black};
  float _dx{0};
  float _dy{0};
  bool _isAnimating{false};
  int _counter{0};
  int _maxCounter{10};
  friend void updatePos(int val);
};
}  // namespace arch

arch::Selector selector;

void arch::updatePos([[maybe_unused]] int val) {
  if (selector._isAnimating) {
    if (selector._counter < selector._maxCounter) {
      auto xAdvance = selector._dx / selector._maxCounter;
      auto yAdvance = selector._dy / selector._maxCounter;
      auto down = selector._dy < 0;
      auto right = selector._dx > 0;
      if (right && selector._pos[0] + xAdvance < selector._targetPos[0]) {
        selector._pos[0] += xAdvance;
      } else if (!right &&
                 selector._pos[0] + xAdvance > selector._targetPos[0]) {
        selector._pos[0] += xAdvance;
      } else {
        selector._pos[0] = selector._targetPos[0];
      }
      if (down && selector._pos[1] + yAdvance > selector._targetPos[1]) {
        selector._pos[1] += yAdvance;
      } else if (!down &&
                 selector._pos[1] + yAdvance < selector._targetPos[1]) {
        selector._pos[1] += yAdvance;
      } else {
        selector._pos[1] = selector._targetPos[1];
      }
      selector._counter++;
      glutPostRedisplay();
      glutTimerFunc(16, updatePos, 0);
    } else {
      selector._isAnimating = false;
      selector._counter = 0;
      selector._dx = 0;
      selector._dy = 0;
      selector._pos = selector._targetPos;
      glutPostRedisplay();
    }
  }
}

void mouseEnter(const std::string& name, [[maybe_unused]] int x,
                [[maybe_unused]] int y) {
  auto& button = arch::ButtonManager::getInstance().getButton(name);
  button.bgColor(smoke.darken());
}

void mouseLeave(const std::string& name, [[maybe_unused]] int x,
                [[maybe_unused]] int y) {
  auto& button = arch::ButtonManager::getInstance().getButton(name);
  button.bgColor(white);
}

void mousePress(const std::string& name, [[maybe_unused]] int x,
                [[maybe_unused]] int y) {
  auto& button = arch::ButtonManager::getInstance().getButton(name);
  button.bgColor(cyan.darken(0.1));
  auto [posX, posY] = button.pos();
  selector.changePos({posX - 10, posY});
  selector.animate();
}

void mouseRelease(const std::string& name, [[maybe_unused]] int x,
                  [[maybe_unused]] int y) {
  auto& button = arch::ButtonManager::getInstance().getButton(name);
  button.bgColor(smoke.darken());
}

void click(const std::string& name) {
  text.text("Button " + name + " clicked");
}

void init() {
  using namespace arch;
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, Window::width(), 0, Window::height(), -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  auto fontPath = "../fonts/SUSE/static/SUSE-Medium.ttf";
  Window::bgColor(white);
  auto& btnM = ButtonManager::getInstance();
  auto btn1 =
      Button()
          .pos({55, 400})
          .size({120, 40})
          .bgColor(white)
          .lnColor(smoke)
          .radius(10)
          .thick(2)
          .label(Label().text("Button 1").color(black).font(fontPath, 24));
  auto btn2 = Button(btn1).pos({55, 325}).label(
      Label().text("Button 2").color(black).font(fontPath, 24));
  auto btn3 = Button(btn1).pos({55, 250}).label(
      Label().text("Button 3").color(black).font(fontPath, 24));
  text = Label(text)
             .text("Nothing clicked")
             .color(black)
             .pos({350, 330})
             .font(fontPath, 30);
  btnM.addButton("1", btn1);
  btnM.addButton("2", btn2);
  btnM.addButton("3", btn3);
  btnM.mouseEnterFunc(mouseEnter);
  btnM.mouseLeaveFunc(mouseLeave);
  btnM.mousePressFunc(mousePress);
  btnM.mouseReleaseFunc(mouseRelease);
  btnM.clickFunc(click);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
  glPushMatrix();
  arch::ButtonManager::getInstance().drawButtons();
  text.draw();
  selector.draw();
  glPopMatrix();
  glFlush();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, (GLdouble)w, 0, (GLdouble)h, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void passiveMouse(int x, int y) {
  int invertedY = arch::Window::height() - y;
  arch::ButtonManager::getInstance().mouseEnter(x, invertedY);
  arch::ButtonManager::getInstance().mouseLeave(x, invertedY);
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    auto invertedY = arch::Window::height() - y;
    arch::ButtonManager::getInstance().mousePress(x, invertedY);
    glutPostRedisplay();
    int16_t _y = invertedY;
    int16_t _x = x;
    int32_t coord = (_y << 16) | (_x & 0xFFFF);
    glutTimerFunc(
        50,
        [](int val) {
          int16_t invertedY = (val >> 16) & 0xFFFF;
          int16_t x = val & 0xFFFF;
          arch::ButtonManager::getInstance().mouseRelease(x, invertedY);
          glutPostRedisplay();
        },
        coord);
  }
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(arch::Window::width(), arch::Window::height());
  uint16_t screenWidth = glutGet(GLUT_SCREEN_WIDTH);
  uint16_t screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
  glutInitWindowPosition((screenWidth - arch::Window::width()) / 2,
                         (screenHeight - arch::Window::height()) / 2);
  glutCreateWindow("Graphics");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutPassiveMotionFunc(passiveMouse);
  glutMouseFunc(mouse);
  glutMainLoop();
}
