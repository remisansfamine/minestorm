#pragma once


#include <string>
#include <raylib.h>

std::string stringConcatenateInt(std::string string, int value);

void DrawAlignedText(const char* text, float offset, int x, int y, float fontSize, Color color);