#include <fmt/color.h>

#include <iostream>

void show_help() {
  constexpr fmt::color green{fmt::color::light_green};
  constexpr fmt::color blue{fmt::color::deep_sky_blue};

  std::cout << "C++'s package manager\n\n";

  fmt::print(fg(green) | fmt::emphasis::bold, "Usage: ");
  fmt::print(fg(blue) | fmt::emphasis::bold, "cask [COMMAND]\n\n");

  fmt::print(fg(green) | fmt::emphasis::bold, "Commands:\n");
  fmt::print(fg(blue) | fmt::emphasis::bold, "    new  ");
  std::cout << "Create a new cask package\n";
}

int main(int ac, char *av[]) {
  if (ac < 2) {
    show_help();
    return 1;
  }

  show_help();

  return 0;
}