#pragma once

#include "maths_toolbox.h"

// Not used
bool    intersect(const Vector2D& point1, const Vector2D& point2);

// Not used
bool    intersect(const Vector2D& point, const Line& line);

// Not used
bool    intersect(const Vector2D& point, const Segment& segment);

// Not used
bool    intersect(const Vector2D& point, const Rect& box);

// Not used
bool    intersect(const Line& line1, const Line& line2);

// Not used
bool    intersect(const Line& line, const Segment& segment);

// Not used
bool    intersect(const Segment& segment1, const Segment& segment2);

// Not used
bool    intersect(const Circle& circle, const Vector2D& point);

// Not used
bool    intersect(const Circle& circle, const Line& line);

// Not used
bool    intersect(const Circle& circle, const Segment& segment);

// Intersection Circle/Circle (used for collisions between projectiles)
bool    intersect(const Circle& circle1, const Circle& circle2);

// Intersection Rect/Rect (used for collisions between polygon AABBs and projectiles)
bool    intersect(const Circle& circle, const Rect& box);

// Intersection Rect/Rect (used for collisions between AABBs)
bool    intersect(const Rect& box1, const Rect& box2);

// Not used
bool    intersect(const ConvexPolygon& convex, const Vector2D& point);

// Intersection Convex Polygon/Convex Polygon (used for collisions between players and mines)
bool    intersect(const ConvexPolygon& convex1, const ConvexPolygon& convex2);

// Intersection Convex Polygon/Circle (used for projectiles and mines, minelayer and players)
bool    intersect(const ConvexPolygon& convex, const Circle& cicle);

// Intersection Concave Polygon/Concave Polygon (used for collisions between players and mines)
bool    intersect(const ConcavePolygon& concave1, const ConcavePolygon& concave2);

// Intersection Concave Polygon/Circle (used for projectiles and mines or minelayer)
bool    intersect(const ConcavePolygon& concave, const Circle& circle);