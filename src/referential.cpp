#include "math_toolbox.h"

#define M_PI 3.14159265358979323846f

Referential2D::Referential2D(const Vector2D& origin, const Vector2D& i)
    : m_origin(origin), m_i(i.normalized()), m_j(i.normal()), m_angle(angle(i, {1.f, 0.f})) {}

void Referential2D::rotate(float angle)
{
    m_angle = fmod(m_angle + angle, 360.f);

    float radAngle = angle * M_PI / 180.f;

    m_i.rotate(radAngle);
    m_j.rotate(radAngle);
}

Vector2D Referential2D::pointLocalToGlobal(const Vector2D& pointLocal) const
{
    return m_origin + m_i * pointLocal.x + m_j * pointLocal.y;
}

Vector2D Referential2D::pointGlobalToLocal(const Vector2D& pointGlobal) const
{
    Vector2D OP = pointGlobal - m_origin;
    return { dot(OP, m_i), dot(OP, m_j) };
}

Vector2D Referential2D::vectorLocalToGlobal(const Vector2D& vectLocal) const
{
    return m_i * vectLocal.x + m_j * vectLocal.y;
}

Vector2D Referential2D::vectorGlobalToLocal(const Vector2D& vectGlobal) const
{
    return { dot(vectGlobal, m_i), dot(vectGlobal, m_j) };
}