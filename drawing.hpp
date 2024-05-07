#include <memory>

namespace Drawing {

  class Rectangle {
    private:
      const int m_width;
      const int m_height;
    public:
      Rectangle(int width, int height);
      int width() const;
      int height() const;
  };

  class Point {
    private:
      int m_x;
      int m_y;
    public:
      Point(int x, int y);
      int x() const;
      int y() const;
  };

  class Context {
    public:
      Context();
      ~Context();
      void clear_background();
      void rectangle(const Point &pos, const Rectangle &rect);
  };

  class Window {
    private:
      int m_screen_width;
      int m_screen_height;
    public:
      Window(int width, int height, const char *title);
      ~Window();
      std::unique_ptr<Context> draw();
      bool should_close();
      Point center(const Rectangle &rect);
  };

}
