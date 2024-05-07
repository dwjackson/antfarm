extern "C" {
  #include "raylib.h"
}

#include "drawing.hpp"

namespace Drawing {

  Window::Window(int width, int height, const char *title)
  {
    InitWindow(width, height, title);
    m_screen_width = width;
    m_screen_height = height;
  }

  Window::~Window()
  {
    CloseWindow();
  }
} 
