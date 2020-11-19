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

Rect ConvexPolygon::getAABB() const
{
    float xMin = FLT_MAX, yMin = FLT_MAX, xMax = FLT_MIN, yMax = FLT_MIN;
    for (const Vector2D& point : pts)
    {
        xMin = min(xMin, point.x);
        yMin = min(yMin, point.y);
        xMax = max(xMax, point.x);
        yMax = max(yMax, point.y);
    }

    Vector2D center((xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f);

    return { center, (xMax - xMin) * 0.5f, (yMax - yMin) * 0.5f};
}

Rect ConcavePolygon::getAABB()
{
    float xMin = FLT_MAX, yMin = FLT_MAX, xMax = FLT_MIN, yMax = FLT_MIN;
    for (const ConvexPolygon& polygon : polygon)
    {
        Rect AABB = polygon.getAABB();
        xMin = min(xMin, AABB.pt.x - AABB.halfWidth);
        yMin = min(yMin, AABB.pt.y - AABB.halfHeight);
        xMax = max(xMax, AABB.pt.x + AABB.halfWidth);
        yMax = max(yMax, AABB.pt.y + AABB.halfHeight);
    }

    Vector2D center((xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f);

    m_AABB = { center, (xMax - xMin) * 0.5f, (yMax - yMin) * 0.5f };

    return m_AABB;
}

float randomNumber(float min, float max)
{
    return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

float clamp(float value, float a, float b)
{
    float minimum = min(a, b), maximum = max(a, b);
    return value < minimum ? minimum : value > maximum ? maximum : value;
}

int sign(float value)
{
    return (value > 0.f) - (value < 0.f);
}