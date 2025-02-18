#include "Color.h"

Color::Color(Colors colorCode)
    : r(0), g(0), b(0), a(1.0f)
{
    switch (colorCode)
    {
    case WHITE:
        r = 1.0f; g = 1.0f; b = 1.0f; break;
    case BLACK:
        r = 0.0f; g = 0.0f; b = 0.0f; break;
    case RED:
        r = 1.0f; g = 0.0f; b = 0.0f; break;
    case GREEN:
        r = 0.0f; g = 1.0f; b = 0.0f; break;
    case BLUE:
        r = 0.0f; g = 0.0f; b = 1.0f; break;
    case YELLOW:
        r = 1.0f; g = 1.0f; b = 0.0f; break;
    case CYAN:
        r = 0.0f; g = 1.0f; b = 1.0f; break;
    case MAGENTA:
        r = 1.0f; g = 0.0f; b = 1.0f; break;
    case ORANGE:
        r = 1.0f; g = 0.5f; b = 0.0f; break;
    case PURPLE:
        r = 0.5f; g = 0.0f; b = 0.5f; break;
    case PINK:
        r = 1.0f; g = 0.75f; b = 0.8f; break;
    case GRAY:
        r = 0.5f; g = 0.5f; b = 0.5f; break;
    case LIGHT_GRAY:
        r = 0.75f; g = 0.75f; b = 0.75f; break;
    case DARK_GRAY:
        r = 0.25f; g = 0.25f; b = 0.25f; break;
    case BROWN:
        r = 0.6f; g = 0.4f; b = 0.2f; break;
    case LIME:
        r = 0.75f; g = 1.0f; b = 0.0f; break;
    case TEAL:
        r = 0.0f; g = 0.5f; b = 0.5f; break;
    case INDIGO:
        r = 0.29f; g = 0.0f; b = 0.51f; break;
    case VIOLET:
        r = 0.93f; g = 0.51f; b = 0.93f; break;
    default:
        break;
    }
}

Color::Color(float r, float g, float b, float a)
    : r(r/255), g(g/255), b(b/255), a(a/255)
{
}