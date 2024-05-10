#include "palette.hpp"

Palette::Palette(Color *colours, int size) : m_colours(colours), m_size(size)
{
}

Color Palette::operator[](int index) const
{
  return m_colours[index];
}

int Palette::next(int index, int limit) const
{
  if (index + 1 >= m_size || index + 1 >= limit) {
    return 0;
  }
  return index + 1;
}

int Palette::size() const
{
  return m_size;
}
