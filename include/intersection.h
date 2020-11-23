#pragma once

#include "maths_toolbox.h"

bool    intersect(const Vector2D& point1, const Vector2D& point2);

bool    intersect(const Vector2D& point, const Line& line);

bool    intersect(const Vector2D& point, const Segment& segment);

bool    intersect(const Vector2D& point, const Rect& box);

bool    intersect(const Line& line1, const Line& line2);

bool    intersect(const Line& line, const Segment& segment);

bool    intersect(const Segment& segment1, const Segment& segment2);

bool    intersect(const Circle& circle, const Vector2D& point);

bool    intersect(const Circle& circle, const Line& line);

bool    intersect(const Circle& circle, const Segment& segment);

bool    intersect(const Circle& circle1, const Circle& circle2);

bool    intersect(const Circle& circle, const Rect& box);

bool    intersect(const Rect& box1, const Rect& box2);

bool    intersect(const ConvexPolygon& convex, const Vector2D& point);

bool    intersect(const ConvexPolygon& convex1, const ConvexPolygon& convex2);

bool    intersect(const ConvexPolygon& convex, const Circle& cicle);

bool    intersect(const ConcavePolygon& concave1, const ConcavePolygon& concave2);

bool    intersect(const ConcavePolygon& concave, const Circle& circle);