#include "math_toolbox.h"

#define M_PI 3.14159265358979323846f

#include <iostream>

Referential2D::Referential2D(const Vector2D& origin, const Vector2D& i)
    : m_origin(origin), m_i(i.normalized()), m_j(i.normal())
{
    // Does not make any sens
    m_angle = -angle(i, { 1.f, 0.f });
}

void Referential2D::rotate(float angle)
{
    m_angle += angle;
    m_i.rotate(angle);
    m_j.rotate(angle);
}

Vector2D Referential2D::pointLocalToGlobal(const Vector2D& pointLocal) const
{
    return m_origin + m_i * pointLocal.x + m_j * pointLocal.y;
}

Vector2D Referential2D::pointGlobalToLocal(const Vector2D& pointGlobal) const
{
    Vector2D pos = pointGlobal - m_origin;
    return { dot(pos, m_i), dot(pos, m_j) };
}

Vector2D Referential2D::vectorLocalToGlobal(const Vector2D& vectLocal) const
{
    return m_i * vectLocal.x + m_j * vectLocal.y;
}

Vector2D Referential2D::vectorGlobalToLocal(const Vector2D& vectGlobal) const
{
    return { dot(vectGlobal, m_i), dot(vectGlobal, m_j) };
}

ConvexPolygon Referential2D::convexToGlobal(const ConvexPolygon& polygonLocal) const
{
    std::vector<Vector2D> points;
    for (const Vector2D& pointLocal : polygonLocal.pts)
        points.push_back(pointLocalToGlobal(pointLocal));

    return { points };
}

ConvexPolygon Referential2D::convexToLocal(const ConvexPolygon& polygonGlobal) const
{
    std::vector<Vector2D> points;
    for (const Vector2D& pointGlobal : polygonGlobal.pts)
        points.push_back(pointGlobalToLocal(pointGlobal));

    return { points };
}

ConcavePolygon Referential2D::concaveToGlobal(const ConcavePolygon& polygonLocal) const
{
    std::vector<ConvexPolygon> polygon;
    for (const ConvexPolygon& convexLocal : polygonLocal.polygon)
        polygon.push_back(convexToGlobal(convexLocal));

    return { polygon };
}

ConcavePolygon Referential2D::concaveToLocal(const ConcavePolygon& polygonGlobal) const
{
    std::vector<ConvexPolygon> polygon;
    for (const ConvexPolygon& convexGlobal : polygonGlobal.polygon)
        polygon.push_back(convexToLocal(convexGlobal));

    return { polygon };
}