#include "math_toolbox.h"

#include <cfloat>
#include <cmath>

bool intersect(Vector2D point1, Vector2D point2)
{
    return (point1 - point2).sqrMagnitude() <= FLT_EPSILON;
}

bool intersect(Vector2D point, Line line)
{
    return sqrDistance(point, line) <= FLT_EPSILON;
}

bool intersect(Vector2D point, Segment segment)
{
    Line line(segment);

    if (!intersect(point, line))
        return false;

    return Range(segment, line.dir).interfere(Range(point, line.dir));
}

bool    intersect(Vector2D point, Rect rect)
{
    return point.x >= rect.pt.x - rect.halfWidth && point.x <= rect.pt.x + rect.halfWidth && point.y >= rect.pt.y - rect.halfHeight && point.y <= rect.pt.y + rect.halfHeight;
}

bool    intersect(Line line1, Line line2)
{
    // Intersect
    if (dot(line1.dir.normal(), line2.dir) != 0)
        return true;

    // Merged
    if (intersect(line1.pt, line2))
        return true;
    
    // Parallel
    return false;
}

bool    intersect(Line line, Segment segment)
{
    Vector2D normal = line.dir.normal();

    if (dot(segment.pt1 - line.pt, normal) * dot(segment.pt2 - line.pt, normal) > 0)
        return false;

    return intersect(line, Line(segment));
}

bool    intersect(Segment segment1, Segment segment2)
{
    Line line(segment1);

    if (!intersect(line, segment2))
        return false;

    return Range(segment1, line.dir).interfere(Range(segment2, line.dir));
}

bool    intersect(Circle circle, Vector2D point)
{
    return (point - circle.center).sqrMagnitude() <= circle.radius * circle.radius;
}

bool    intersect(Circle circle, Line line)
{
    return sqrDistance(circle.center, line) <= circle.radius * circle.radius;
}

bool    intersect(Circle circle, Segment segment)
{
    Line line(segment);

    if (!intersect(circle, line))
        return false;

    if (intersect(circle, segment.pt1) || intersect(circle, segment.pt2))
        return true;

    return Range(circle, line.dir).interfere(Range(segment, line.dir));
}

bool    intersect(Circle circle1, Circle circle2)
{
    return sqrDistance(circle1.center, circle2.center) <= (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);
}

bool    intersect(Circle circle, Rect rect)
{
    if (intersect(circle.center, rect))
        return true;

    Vector2D height;
    height.x = clamp(circle.center.x, rect.pt.x - rect.halfWidth, rect.pt.x + rect.halfWidth);
    height.y = clamp(circle.center.y, rect.pt.y - rect.halfHeight, rect.pt.y + rect.halfHeight);

    return sqrDistance(height, circle.center) <= circle.radius * circle.radius;
}

bool    intersect(Rect rect1, Rect rect2)
{
    return rect1.pt.x + rect1.halfWidth * 2.f > rect2.pt.x &&
           rect1.pt.x < rect2.pt.x + rect2.halfWidth * 2.f &&
           rect1.pt.y + rect1.halfHeight * 2.f > rect2.pt.y &&
           rect1.pt.y < rect2.pt.y + rect2.halfHeight * 2.f;
}

bool    intersect(ConvexPolygon convex, Vector2D point)
{
    int count = convex.pts.size();

    for (int i = 0; i < count; i++)
    {
        Segment segment = { convex.pts[i], convex.pts[(i + 1) % count] };
        Vector2D normal = segment.normal();

        Range range(convex.pts[0], normal);
        for (int i = 1; i < count; i++)
            range.merge(Range(convex.pts[i], normal));

        if (!range.interfere(Range(point, normal)))
            return false;
    }
    return true;
}

bool    intersect(ConvexPolygon convex1, ConvexPolygon convex2)
{
    int count1 = convex1.pts.size();
    int count2 = convex2.pts.size();

    for (int i = 0; i < count1; i++)
    {
        Segment segment = { convex1.pts[i], convex1.pts[(i + 1) % count1] };
        Vector2D normal = segment.normal();

        Range range1(convex1.pts[0], normal);
        for (int i = 1; i < count1; i++)
            range1.merge(Range(convex1.pts[i], normal));

        Range range2(convex2.pts[0], normal);
        for (int i = 1; i < count2; i++)
            range2.merge(Range(convex2.pts[i], normal));

        if (!range1.interfere(range2))
            return false;
    }

    for (int i = 0; i < count2; i++)
    {
        Segment segment = { convex2.pts[i], convex2.pts[(i + 1) % count2] };
        Vector2D normal = segment.normal();

        Range range1(convex1.pts[0], normal);
        for (int i = 0; i < count1; i++)
            range1.merge(Range(convex1.pts[i], normal));

        Range range2(convex2.pts[0], normal);
        for (int i = 0; i < count2; i++)
            range2.merge(Range(convex2.pts[i], normal));

        if (!range1.interfere(range2))
            return false;
    }

    return true;
}

bool    intersect(ConvexPolygon convex, Circle circle)
{
    int count = convex.pts.size();

    for (int i = 0; i < count; i++)
    {
        Segment segment = { convex.pts[i], convex.pts[(i + 1) % count] };
        Vector2D normal = segment.normal();

        Range range(convex.pts[0], normal);
        for (int i = 1; i < count; i++)
            range.merge(Range(convex.pts[i], normal));

        if (!range.interfere(Range(circle, normal)))
            return false;
    }
    
    // Get nearest point
    Vector2D nearestPoint = convex.pts[0];
    float currentDistance = sqrDistance(nearestPoint, circle.center);
    for (int i = 1; i < count; i++)
    {
        if (sqrDistance(convex.pts[i], circle.center) < currentDistance)
        {
            nearestPoint = convex.pts[i];
            currentDistance = sqrDistance(nearestPoint, circle.center);
        }
    }

    Vector2D dir = (circle.center - nearestPoint).normalized();

    Range range(convex.pts[0], dir);
        for (int i = 1; i < count; i++)
            range.merge(Range(convex.pts[i], dir));
    
    if (!range.interfere(Range(circle, dir)))
            return false;

    return true;
}