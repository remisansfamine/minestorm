#pragma once

#include "maths_toolbox.h"

struct Range
{
    float m_min = FLT_MIN;
    float m_max = FLT_MAX;

    Range() = default;
    Range(float val1, float val2);
    Range(Vector2D point, Vector2D axis);
    Range(Segment segment, Vector2D axis);
    Range(Range range1, Range range2);
    Range(Rect rect, Vector2D axis);
    Range(Circle circle, Vector2D axis);
    Range(ConvexPolygon polygon, Vector2D axis);

    float minimum(const Range&) const;
    float maximum(const Range&) const;

    Range& merge(const Range&);
    Range& merge(float);

    bool interfere(const Range&) const;
};