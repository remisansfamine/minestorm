#include "maths_toolbox.h"
#include "maths_utils.h"
#include "range.h"
#include "intersection.h"

#include <cfloat>
#include <cmath>

// Not used
bool intersect(const Vector2D& point1, const Vector2D& point2)
{
    return (point1 - point2).sqrMagnitude() <= FLT_EPSILON;
}

// Not used
bool intersect(const Vector2D& point, const Line& line)
{
    return sqrDistance(point, line) <= FLT_EPSILON;
}

// Not used
bool intersect(const Vector2D& point, const Segment& segment)
{
    Line line(segment);

    if (!intersect(point, line))
        return false;

    return Range(segment, line.dir).interfere(Range(point, line.dir));
}

// Not used
bool    intersect(const Vector2D& point, const Rect& rect)
{
    return point.x >= rect.pt.x - rect.halfWidth  &&
           point.x <= rect.pt.x + rect.halfWidth  &&
           point.y >= rect.pt.y - rect.halfHeight &&
           point.y <= rect.pt.y + rect.halfHeight;
}

// Not used
bool    intersect(const Line& line1, const Line& line2)
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

// Not used
bool    intersect(const Line& line, const Segment& segment)
{
    Vector2D normal = line.dir.normal();

    // Checking if the points of the segment are in the same side of the line
    if (dot(segment.pt1 - line.pt, normal) * dot(segment.pt2 - line.pt, normal) > 0)
        return false;

    // Checking if the line (made by the segment) intersect with the real line
    return intersect(line, Line(segment));
}

// Not used
bool    intersect(const Segment& segment1, const Segment& segment2)
{
    Line line(segment1);

    if (!intersect(line, segment2))
        return false;

    // Checking if the segments ranges interfere
    return Range(segment1, line.dir).interfere(Range(segment2, line.dir));
}

// Not used
bool    intersect(const Circle& circle, const Vector2D& point)
{
    return (point - circle.center).sqrMagnitude() <= circle.radius * circle.radius;
}

// Not used
bool    intersect(const Circle& circle, const Line& line)
{
    return sqrDistance(circle.center, line) <= circle.radius * circle.radius;
}

// Not used
bool    intersect(const Circle& circle, const Segment& segment)
{
    Line line(segment);

    if (!intersect(circle, line))
        return false;

    if (intersect(circle, segment.pt1) || intersect(circle, segment.pt2))
        return true;

    return Range(circle, line.dir).interfere(Range(segment, line.dir));
}

// Intersection Circle/Circle (used for collisions between projectiles)
bool    intersect(const Circle& circle1, const Circle& circle2)
{
    // Checking if the squared distance between the centers of the circles is smaller than their squared radius
    return sqrDistance(circle1.center, circle2.center) <=
           (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);
}

// Intersection Rect/Rect (used for collisions between polygon AABBs and projectiles)
bool    intersect(const Circle& circle, const Rect& rect)
{
    // Checking if the center of the point is in the rect
    if (intersect(circle.center, rect))
        return true;

    Vector2D height =
    {
        clamp(circle.center.x, rect.pt.x - rect.halfWidth, rect.pt.x + rect.halfWidth),
        clamp(circle.center.y, rect.pt.y - rect.halfHeight, rect.pt.y + rect.halfHeight)
    };

    // Checking if the squared distance between the circle and the rect is smaller than the squared radius
    return sqrDistance(height, circle.center) <= circle.radius * circle.radius;
}

// Intersection Rect/Rect (used for collisions between AABBs)
bool    intersect(const Rect& rect1, const Rect& rect2)
{
    // Comparing the ranges of the rects on the x and the y axis

    Range range1(rect1, Vector2D(1.f, 0.f));
    Range range2(rect2, Vector2D(1.f, 0.f));

    if (!range1.interfere(range2))
        return false;

    range1 = Range(rect1, Vector2D(0.f, 1.f));
    range2 = Range(rect2, Vector2D(0.f, 1.f));

    return range1.interfere(range2);
}

// Not used
bool    intersect(const ConvexPolygon& convex, const Vector2D& point)
{
    size_t count = convex.pts.size();

    // Checking if there is a separating axis between the point and each segment of the convex

    for (int i = 0; i < count; i++)
    {
        Segment segment = { convex.pts[i], convex.pts[(i + 1) % count] };
        Vector2D normal = segment.normal();

        Range range(convex, normal);

        if (!range.interfere(Range(point, normal)))
            return false;
    }
    return true;
}

// Intersection Convex Polygon/Convex Polygon (used for collisions between players and mines)
bool    intersect(const ConvexPolygon& convex1, const ConvexPolygon& convex2)
{
    size_t count1 = convex1.pts.size();
    size_t count2 = convex2.pts.size();

    // For each convex, checking if there is a separating axis by comparing the ranges of the each segment of each polygon

    for (int i = 0; i < count1; i++)
    {
        Segment segment = { convex1.pts[i], convex1.pts[(i + 1) % count1] };
        Vector2D normal = segment.normal();

        Range range1(convex1, normal);
        Range range2(convex2, normal);

        if (!range1.interfere(range2))
            return false;
    }

    for (int i = 0; i < count2; i++)
    {
        Segment segment = { convex2.pts[i], convex2.pts[(i + 1) % count2] };
        Vector2D normal = segment.normal();

        Range range1(convex1, normal);
        Range range2(convex2, normal);

        if (!range1.interfere(range2))
            return false;
    }

    return true;
}

// Intersection Concave Polygon/Concave Polygon (used for collisions between players and mines)
bool intersect(const ConcavePolygon& concave1, const ConcavePolygon& concave2)
{
    // Checking if concave AABBs intersect
    if (intersect(concave1.m_AABB, concave2.m_AABB))
    {
        for (const ConvexPolygon& convex1 : concave1.polygon)
        {
            Rect AABB1 = convex1.getAABB();

            // Checking if convexe AABBs intersect
            for (const ConvexPolygon& convex2 : concave2.polygon)
            {
                Rect AABB2 = convex2.getAABB();

                // Checking if concave polygons intersect
                if (intersect(AABB1, AABB2))
                {
                    if (intersect(convex1, convex2))
                        return true;
                }
            }
        }
    }

    return false;
}

// Intersection Convex Polygon/Circle (used for projectiles and mines, minelayer and players)
bool    intersect(const ConvexPolygon& convex, const Circle& circle)
{
    size_t count = convex.pts.size();

    // Checking if there is a separating axis by comparing the ranges 
    // of the circle and the convex made with each segment of the polygon

    for (int i = 0; i < count; i++)
    {
        Segment segment = { convex.pts[i], convex.pts[(i + 1) % count] };
        Vector2D normal = segment.normal();

        Range range(convex, normal);

        if (!range.interfere(Range(circle, normal)))
            return false;
    }
    
    // Get nearest point to get a new axis for range
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

    Range range(convex, dir);
    
    return range.interfere(Range(circle, dir));
}

// Intersection Concave Polygon/Circle (used for projectiles and mines or minelayer)
bool intersect(const ConcavePolygon& concave, const Circle& circle)
{
    // Checking if concave AABB and circle intersect

    if (intersect(circle, concave.m_AABB))
    {
        for (const ConvexPolygon& polygon : concave.polygon)
        {
            Rect AABB = polygon.getAABB();

            // Checking if concave polygon and circle intersect
            if (intersect(circle, AABB))
            {
                if (intersect(polygon, circle))
                    return true;
            }
        }
    }

    return false;
}