namespace Drawing {

  class Window {
    private:
      int m_screen_width;
      int m_screen_height;
    public:
      Window(int width, int height, const char *title);
      ~Window();
  };
}
