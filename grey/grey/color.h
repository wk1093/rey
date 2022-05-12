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

// Custom
Color COLOR_DISCORD = { 54, 57, 63, 255 };