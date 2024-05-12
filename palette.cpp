#include "palette.hpp"
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

namespace Palette
{
  Palette::Palette(std::vector<Color> colours) : m_colours(colours)
  {
  }

  Color Palette::operator[](int index) const
  {
    return m_colours[index];
  }

  int Palette::next(int index, int limit) const
  {
    if (index + 1 >= size() || index + 1 >= limit) {
      return 0;
    }
    return index + 1;
  }

  int Palette::size() const
  {
    return m_colours.size();
  } 

  Color color_from_hex(unsigned int hex)
  {
    unsigned int red = (0x00FF0000 & hex) >> 16;
    unsigned int green = (0x0000FF00 & hex) >> 8;
    unsigned int blue = 0x000000FF & hex;

    return { (unsigned char) red, (unsigned char) green, (unsigned char) blue, 255 };
  }

  Color parse_color(std::string input)
  {
    std::stringstream ss(input);
    std::string color_name;
    std::string hex_string;

    ss >> color_name >> hex_string;

    int hex = std::stoi(hex_string, nullptr, 16);

    return color_from_hex(hex);
  }

  Palette parse_palette(std::string file_name)
  {
    std::string line;
    std::fstream file(file_name);
    std::vector<Color> colours;

    if (file.is_open()) {
      while (std::getline(file, line)) {
        auto colour = parse_color(line);        
        colours.push_back(colour);
      }
      file.close();
    }
    return Palette(colours);
  }

  Palette default_palette(void)
  {
    std::vector<Color> colours = {
      RAYWHITE,
      BLACK,
      DARKPURPLE,
      VIOLET,
      PURPLE,
      DARKBLUE,
      BLUE,
      SKYBLUE,
      DARKGREEN,
      LIME,
      GREEN,
      MAROON,
      PINK,
      ORANGE,
      GOLD,
      YELLOW
    };
    return Palette(colours);
  }
}
