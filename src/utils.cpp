#include "utils.h"
#include "maths_toolbox.h"

#include <raylib.h>

std::string stringConcatenateInt(std::string string, int value)
{
	return string + " " + std::to_string(value);
}

void DrawAlignedText(const char* text, float offset, int x, int y, float fontSize, Color color)
{
	DrawText(text, x - MeasureText(text, fontSize) * offset, y, fontSize, color);
}

void Rect::drawDebug() const
{
    // Draw Rect and AABB
    DrawRectangleLines(pt.x - halfWidth,
        pt.y - halfHeight,
        halfWidth * 2.f,
        halfHeight * 2.f,
        collide ? RED : BLUE);
}

void ConvexPolygon::drawDebug() const
{
    // Draw each segment of the polygon and its AABB
    Rect  convexAABB = getAABB();

    convexAABB.drawDebug();

    for (int i = 0; i < pts.size(); i++)
    {
        int j = (i + 1) % pts.size();

        Vector2D point0 = pts[i];
        Vector2D point1 = pts[j];

        DrawLine(point0.x, point0.y, point1.x, point1.y, ORANGE);
        DrawCircle(point0.x, point0.y, 2, BLACK);
    }
}