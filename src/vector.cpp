#include "math_toolbox.h"

#include <cmath>

Vector2D::Vector2D(float x, float y)
    : x(x), y(y) {}

Vector2D::Vector2D(Vector2 vect)
    : x(vect.x), y(vect.y) {}

float   Vector2D::magnitude() const
{
    // Return the square root of the square magnitude
    return sqrt(sqrMagnitude());
}

float Vector2D::sqrMagnitude() const
{
    return dot(*this, *this);
}

float dot(const Vector2D& vect1, const Vector2D& vect2)
{
    return vect1.x * vect2.x + vect1.y * vect2.y;
}

Vector2D Vector2D::normalized() const
{
    float magn = magnitude();

    if (!magn)
        return *this;

    return { x / magn, y / magn };
}

Vector2D& Vector2D::normalize()
{
    *this = normalized();

    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    // Return the addition of the two vectors
    return {x + other.x, y + other.y};
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    *this = *this + other;
    return *this;
}

Vector2D Vector2D::operator-() const
{
    // Return the opposite of the vector
    return {-x, -y};
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    // Return the substraction of the two vectors
    return { x + -other.x, y + -other.y };
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
    *this = *this - other;
    return *this;
}

Vector2D Vector2D::operator*(float scale) const
{
    // Return the multiplication with the scalar
    return { x * scale, y * scale };
}

Vector2D& Vector2D::operator*=(float scale)
{
    *this = *this * scale;
    return *this;
}

Vector2D Vector2D::operator/(float scale) const
{
    // Return the division with the scalar
    return { x / scale, y / scale };
}

Vector2D& Vector2D::operator/=(float scale)
{
    *this = *this / scale;
    return *this;
}

bool Vector2D::operator==(const Vector2D& vect) const
{
    // Check if the substaction of the vectors is smaller than epsilon
    return abs(x - vect.x) <= FLT_EPSILON && abs(y - vect.y <= FLT_EPSILON);
}

Vector2D::operator Vector2()
{
    return { x, y };
}

float distance(const Vector2D& point1, const Vector2D& point2)
{
    return (point1 - point2).magnitude();
}

float distance(const Vector2D& point, const Line& line)
{
    Vector2D AP = point - line.pt;
    return (AP - line.dir * dot(AP, line.dir)).magnitude();
}

float sqrDistance(const Vector2D& point1, const Vector2D& point2)
{
    return (point1 - point2).sqrMagnitude();
}

float sqrDistance(const Vector2D& point, const Line& line)
{
    Vector2D dir = line.dir.normalized();
    Vector2D AP = point - line.pt;
    return (AP - dir * dot(AP, dir)).sqrMagnitude();
}

float angle(const Vector2D& vect1, const Vector2D& vect2)
{
    /*float magn = vect1.magnitude() * vect2.magnitude();

    if (magn == 0)
        return 0.f;

    float crossProd = vect1.x * vect2.y - vect1.y * vect2.x;

    return (crossProd < 0.f) ? (2.f * M_PI - acos(dot(vect1, vect2) / magn)) : (acos(dot(vect1, vect2) / magn));*/

    float dotProd = dot(vect1, vect2);
    float crossProd = (vect1.x * vect2.y) - (vect1.y * vect2.x);
    return atan2f(crossProd, dotProd);
}

Vector2D& Vector2D::rotate(float angle)
{
    Vector2D temp_vect = *this;

    float cos = cosf(angle), sin = sinf(angle);

    x = cos * temp_vect.x - sin * temp_vect.y;
    y = sin * temp_vect.x + cos * temp_vect.y;

    // Keep the vector with a correct magnitude
    *this = normalized() * temp_vect.magnitude();

    return *this;
}

Vector2D& Vector2D::rotate90()
{
    *this = normal();

    return *this;
}

Vector2D Vector2D::normal() const
{
    return Vector2D(-y, x).normalized();
}

Vector2D& Vector2D::rotateAround(const Vector2D& center, float angle)
{
    // Get the vector between the origin and the point
    Vector2D direction = *this - center;

    // Rotate this vector
    direction.rotate(angle);

    // Get the point at the end of the vector
    *this = center + direction;

    return *this;
}

Vector2D Segment::normal()
{
    return (pt2 - pt1).normal();
}