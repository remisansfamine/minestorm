#include "math_toolbox.h"

float min(float value1, float value2)
{
    return value1 <= value2 ? value1 : value2;
}

float max(float value1, float value2)
{
    return value1 <= value2 ? value2 : value1;
}

Line::Line(const Segment& segment)
    : pt(segment.pt1), dir((segment.pt2 - segment.pt1).normalized())
{ }

float clamp(float value, float a, float b)
{
    float minimum = min(a, b), maximum = max(a, b);
    return value < minimum ? minimum : value > maximum ? maximum : value;
}

float sign(float value)
{
    return (value > 0.f) - (value < 0.f);
}