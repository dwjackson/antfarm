#include "rules.hpp"
#include "palette.hpp"
#include <cstring>
#include <cstdlib>

bool rules_validate(const char *rules, const Palette &palette)
{
  size_t len = strlen(rules);
  if ((size_t) palette.size() <= len) {
    return false;
  }
  for (size_t i = 0; i < len; i++) {
    if (rules[i] != 'L' && rules[i] != 'R') {
      return false;
    }
  }
  return true;
}
