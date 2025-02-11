#pragma once

enum Colors
{
    WHITE,
    BLACK,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    ORANGE,
    PURPLE,
    PINK,
    GRAY,
    LIGHT_GRAY,
    DARK_GRAY,
    BROWN,
    LIME,
    TEAL,
    INDIGO,
    VIOLET
};

struct Color {
	float r;
	float g;
	float b;
	float a;
	Color(Colors colorCode);
	Color(float r, float g, float b, float a);
};