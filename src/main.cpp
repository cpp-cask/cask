#include <iostream>

// ///////

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

enum class ColorId
{
    red,
    green,
    cyan,
};

enum class ColorFont
{
    regular,
    bold,
};

std::string color(ColorId color_id, const std::string& line, ColorFont font = ColorFont::regular)
{

#ifdef _WIN32

    HANDLE h_console{GetStdHandle(STD_OUTPUT_HANDLE)};
    CONSOLE_SCREEN_BUFFER_INFO console_info;
    WORD saved_attributes;
    
    // Save current console attributes
    GetConsoleScreenBufferInfo(h_console, &console_info);
    saved_attributes = console_info.wAttributes;

    WORD color_code{saved_attributes};

    switch (color_id) {
        case ColorId::red:   color_code = FOREGROUND_RED; break;
        case ColorId::green: color_code = FOREGROUND_GREEN; break;
        case ColorId::cyan:  color_code = FOREGROUND_GREEN | FOREGROUND_BLUE; break;
    }

    SetConsoleTextAttribute(h_console, color_code);

    std::cout << line;

    SetConsoleTextAttribute(h_console, saved_attributes);

#else
    std::string color_code = "\033[";

    std::string color_font = "0";

    if (font == ColorFont::bold) {
        color_font = "1";
    }

    color_code += color_font;
    color_code += ';';

    switch (color_id) {
        case ColorId::red:    color_code += "31"; break;
        case ColorId::green:  color_code += "32"; break;
        case ColorId::cyan:   color_code += "36"; break;
        default:              color_code += "0"; break;
    }

    color_code += "m";

    std::cout << color_code << line << "\033[0m";
    
#endif

    return "";
}

// //////

// void show_help()
// {
//     std::cout << "C++'s package manager\n\n";

//     std::cout << color(ColorId::green, "Usage:", ColorFont::bold) << color(ColorId::cyan, " cask [COMMAND]", ColorFont::bold) << "\n\n";

//     std::cout << color(ColorId::green, "Commands:", ColorFont::bold) << "\n";
//     std::cout << color(ColorId::cyan, "    new", ColorFont::bold) << "  Create a new cask package\n";
// }

int main(int ac, char *av[])
{
    // if (ac < 2)
    // {
    //     show_help();
    //     return 1;
    // }

    std::cout << "C++'s package manager\n\n";

    return 0;
}