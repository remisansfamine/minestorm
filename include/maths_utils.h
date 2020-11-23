#pragma once

#include "maths_toolbox.h"

float min(float value1, float value2);
float max(float value1, float value2);
float clamp(float value, float min, float max);

float randomNumber(float Min, float Max);

int sign(float value);

float radToDeg();
float degToRad();