#include "maths_toolbox.h"
#include "maths_utils.h"

#include "range.h"

Range::Range(float val1, float val2)
    : m_min(min(val1, val2)), m_max(max(val1, val2)) { }

// Range of a point in an axis
// (used to get the range of a Convex Polygon, and the range of a Rect 
// and to check collisions between two Convex Polygons, or a Convex Polygon and a Circle)
Range::Range(const Vector2D& point, const Vector2D& axis)
{
    float dotProduct = dot(point, axis.normalized());
    m_min = m_max = dotProduct;
}

// Not used
Range::Range(const Range& range1, const Range& range2)
{
    m_min = min(range1.m_min, range2.m_min);
    m_max = max(range1.m_max, range2.m_max);
}

// Not used
Range::Range(const Segment& segment, const Vector2D& axis)
    : Range(Range(segment.pt1, axis.normalized()), Range(segment.pt2, axis.normalized())) { }

// Range of a rect in an axis (used to check collisions between Rects)
Range::Range(const Rect& rect, const Vector2D& axis)
{
    Vector2D points[4] =
    {
        {rect.pt.x - rect.halfWidth, rect.pt.y - rect.halfHeight },
        {rect.pt.x - rect.halfWidth, rect.pt.y + rect.halfHeight },
        {rect.pt.x + rect.halfWidth, rect.pt.y + rect.halfHeight },
        {rect.pt.x + rect.halfWidth, rect.pt.y - rect.halfHeight }
    };

    axis.normalized();

    this->Range::Range(Range(Range(points[0], axis), Range(points[1], axis)),
        Range(Range(points[2], axis), Range(points[3], axis)));
}

// Range of a circle in an axis (used to check collisions between a Circle and a Convex Polygon)
Range::Range(const Circle& circle, const Vector2D& axis)
{
    Vector2D radius = axis * circle.radius;
    Segment diameter = { circle.center - radius, circle.center + radius };
    this->Range::Range(diameter, axis.normalized());
}

// Range of a convex polygon in an axis (used to check collisions between a Circle and a Convex Polygon, or two Convex Polygons)
Range::Range(const ConvexPolygon& polygon, const Vector2D& axis)
    : Range(polygon.pts[0], axis)
{
    for (int i = 1; i < polygon.pts.size(); i++)
        merge(Range(polygon.pts[i], axis));
}

float Range::minimum(const Range& other) const
{
    return min(m_min, other.m_min);
}

float Range::maximum(const Range& other) const
{
    return max(m_max, other.m_max);
}

Range& Range::merge(const Range& other)
{
    m_min = minimum(other);
    m_max = maximum(other);
    return *this;
}

Range& Range::merge(float value)
{
    // Merging the ranges by setting the extreme bounds of each range
    m_min = min(m_min, value);
    m_max = max(m_max, value);
    return *this;
}

bool Range::interfere(const Range& other) const
{
    // Checking if ranges interfere by comparing their bounds
    return m_min <= other.m_max && other.m_min <= m_max;
}