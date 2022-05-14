typedef unsigned short t_color;
using Color = std::vector<int>;
// Chromakey
Color COLOR_BLACK = { 0, 0, 0, 255 };
Color COLOR_WHITE = { 255, 255, 255, 255 };
Color COLOR_LIGHT_GREY = { 128, 128, 128, 255 };
Color COLOR_DARK_GREY = { 63, 63, 63, 255 };
Color grey = { 14, 14, 14, 255 };
// Primary
Color COLOR_RED = { 255, 0, 0, 255 };
Color COLOR_GREEN = { 0, 255, 0, 255 };
Color COLOR_BLUE = { 0, 0, 255, 255 };
// Secondary
Color COLOR_YELLOW = { 255, 255, 0, 255 };
Color COLOR_CYAN = { 0, 255, 255, 255 };
Color COLOR_MAGENTA = { 255, 0, 255, 255 };
// Tertiary
Color COLOR_ORANGE = { 255, 128, 0, 255 };
Color COLOR_CHARTREUSE = { 128, 255, 0, 255 };
Color COLOR_SPRING_GREEN = { 0, 255, 128, 255 };
Color COLOR_AZURE = { 0, 128, 255, 255 };
Color COLOR_VIOLET = { 128, 0, 255, 255 };
Color COLOR_ROSE = { 255, 0, 128, 255 };

// Soft Primary
Color COLOR_SOFT_RED = { 255, 50, 50, 255 };
Color COLOR_SOFT_GREEN = { 50, 255, 50, 255 };
Color COLOR_SOFT_BLUE = { 50, 50, 255, 255 };
// Soft Secondary
Color COLOR_SOFT_YELLOW = { 255, 255, 50, 255 };
Color COLOR_SOFT_CYAN = { 50, 255, 255, 255 };
Color COLOR_SOFT_MAGENTA = { 255, 50, 255, 255 };
// Soft Tertiary
Color COLOR_SOFT_ORANGE = { 255, 128, 50, 255 };
Color COLOR_SOFT_CHARTREUSE = { 128, 255, 50, 255 };
Color COLOR_SOFT_SPRING_GREEN = { 50, 255, 128, 255 };
Color COLOR_SOFT_AZURE = { 50, 128, 255, 255 };
Color COLOR_SOFT_VIOLET = { 128, 50, 255, 255 };
Color COLOR_SOFT_ROSE = { 255, 50, 128, 255 };

// Miscellaneous
Color COLOR_DISCORD = { 54, 57, 63, 255 };
Color COLOR_SIMPLE = { 0, 159, 141, 255 };