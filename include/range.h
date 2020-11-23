#pragma once

#include "maths_toolbox.h"

struct Range
{
    float m_min = FLT_MIN;
    float m_max = FLT_MAX;

    Range() = default;
    Range(float val1, float val2);
    Range(const Vector2D& point, const Vector2D& axis);
    Range(const Segment& segment, const Vector2D& axis);
    Range(const Range& range1, const Range& range2);
    Range(const Rect& rect, const Vector2D& axis);
    Range(const Circle& circle, const Vector2D& axis);
    Range(const ConvexPolygon& polygonconst, const Vector2D& axis);

    float minimum(const Range&) const;
    float maximum(const Range&) const;

    Range& merge(const Range&);
    Range& merge(float);

    bool interfere(const Range&) const;
};