#pragma once

#include "maths_toolbox.h"

struct Referential2D
{
    Vector2D    m_origin = { 0.f, 0.f };
    Vector2D    m_i = { 1.f, 0.f };
    Vector2D    m_j = { 0.f, 1.f };
    float       m_angle = 0.f;

    Referential2D() = default;
    Referential2D(const Vector2D& origin, const Vector2D& i = { 1.f, 0.f });

    // Rotate a referential by rotating its vectors and by updating its angle (used to rotate an entity)
    void rotate(float angle);

    // Convert a local point to a global point (used to get a global convex polygon and to get an AABB)
    Vector2D pointLocalToGlobal(const Vector2D& pointLocal) const;
    // Not used
    Vector2D pointGlobalToLocal(const Vector2D& pointGlobal) const;

    // Not used
    Vector2D vectorLocalToGlobal(const Vector2D& vectLocal) const;
    // Not used
    Vector2D vectorGlobalToLocal(const Vector2D& vectGlobal) const;

    // Convert a local convex to a global convex (used to get a global concave polygon)
    ConvexPolygon convexToGlobal(const ConvexPolygon& polygonLocal) const;
    // Not used
    ConvexPolygon convexToLocal(const ConvexPolygon& polygonGlobal) const;

    // Convert a local concave to a global concave (used to check collisions)
    ConcavePolygon concaveToGlobal(const ConcavePolygon& polygonLocal) const;
    // Not used
    ConcavePolygon concaveToLocal(const ConcavePolygon& polygonGlobal) const;
};