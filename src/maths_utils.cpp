#include "maths_toolbox.h"

#include "maths_utils.h"

float min(float value1, float value2)
{
    return value1 <= value2 ? value1 : value2;
}

float max(float value1, float value2)
{
    return value1 <= value2 ? value2 : value1;
}

float clamp(float value, float a, float b)
{
    float minimum = min(a, b), maximum = max(a, b);
    return value < minimum ? minimum : value > maximum ? maximum : value;
}

// Return -1 or 1
float randomSign()
{
    return ((rand() % 2) * 2.f - 1.f);
}

// Return a random float in a range
float randomNumber(float min, float max)
{
    // Get a random number between two floats by getting a range between 0 and 1 and remapping the bounds
    return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

int sign(float value)
{
    // Get the sign of a float by substracting the boolean comparaisons
    return (value > 0.f) - (value < 0.f);
}

float radToDeg()
{
    return 180.f / M_PI;
}

float degToRad()
{
    return M_PI / 180.f;
}

// Return a line made of a segment (not used)
Line::Line(const Segment& segment)
    : pt(segment.pt1), dir((segment.pt2 - segment.pt1).normalized())
{ }

Rect ConvexPolygon::getAABB() const
{
    // Get AABB of a convex by comparing each coordinate of each point
    float xMin = FLT_MAX, yMin = FLT_MAX, xMax = FLT_MIN, yMax = FLT_MIN;
    for (const Vector2D& point : pts)
    {
        xMin = min(xMin, point.x);
        yMin = min(yMin, point.y);
        xMax = max(xMax, point.x);
        yMax = max(yMax, point.y);
    }

    // Getting the center
    Vector2D center((xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f);

    // Returning the center and the bounds
    return { center, (xMax - xMin) * 0.5f, (yMax - yMin) * 0.5f};
}

Rect ConcavePolygon::getAABB()
{
    // Get AABB of a convex by comparing each AABB of each polygon
    float xMin = FLT_MAX, yMin = FLT_MAX, xMax = FLT_MIN, yMax = FLT_MIN;
    for (const ConvexPolygon& polygon : polygon)
    {
        Rect AABB = polygon.getAABB();
        xMin = min(xMin, AABB.pt.x - AABB.halfWidth);
        yMin = min(yMin, AABB.pt.y - AABB.halfHeight);
        xMax = max(xMax, AABB.pt.x + AABB.halfWidth);
        yMax = max(yMax, AABB.pt.y + AABB.halfHeight);
    }

    // Getting the center
    Vector2D center((xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f);

    // Setting the AABB in the polygon (to avoid more calculations) with the center and the bounds
    m_AABB = { center, (xMax - xMin) * 0.5f, (yMax - yMin) * 0.5f };

    // Returning the result
    return m_AABB;
}

Vector2D randomVector()
{
    return { randomNumber(-1.f, 1.f), randomNumber(-1.f, 1.f) };
}