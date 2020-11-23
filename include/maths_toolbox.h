#pragma once

#include <cfloat>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include <raylib.h>

struct Vector2D
{
    Vector2D(float x = 0.f, float y = 0.f);
    Vector2D(Vector2 vect);

    float x = 0.f;
    float y = 0.f;

    float magnitude() const;
    float sqrMagnitude() const;

    Vector2D normalized() const;
    Vector2D& normalize();

    Vector2D    operator-() const;
    Vector2D    operator+(const Vector2D&) const;
    Vector2D&   operator+=(const Vector2D&);
    Vector2D    operator-(const Vector2D&) const;
    Vector2D&   operator-=(const Vector2D&);
    Vector2D    operator*(float) const;
    Vector2D&   operator*=(float);
    Vector2D    operator/(float) const;
    Vector2D&   operator/=(float);
    bool        operator==(const Vector2D&) const;

    operator Vector2();

    Vector2D& rotate(float angle);
    Vector2D& rotate90();
    Vector2D& rotateAround(const Vector2D& center, float angle);

    Vector2D normal() const;
};

struct Segment
{
    Vector2D pt1;
    Vector2D pt2;

    Vector2D normal();
};

struct Line
{
    Vector2D pt;
    Vector2D dir;

    Line(const Segment&);
};

struct Circle
{
    Vector2D center;
    float radius;
};


struct Rect
{
    Vector2D pt;
    float halfWidth;
    float halfHeight;

    bool collide = false;

    void drawDebug() const;
};

struct OrientedRect
{
    Rect rect;
    float angle;
};

struct ConvexPolygon 
{
    std::vector<Vector2D> pts;

    Rect getAABB() const;

    void drawDebug() const;
};

struct ConcavePolygon
{
    std::vector<ConvexPolygon> polygon;
    Rect m_AABB;

    Rect getAABB();
};

struct Referential2D
{
    Vector2D m_origin = { 0.f, 0.f };
    Vector2D m_i = { 1.f, 0.f };
    Vector2D m_j = { 0.f, 1.f };
    float    m_angle = 0.f;

    Referential2D() = default;
    Referential2D(const Vector2D& origin, const Vector2D& i = {1.f, 0.f});

    void rotate(float angle);

    Vector2D pointLocalToGlobal(const Vector2D& pointLocal) const;
    Vector2D pointGlobalToLocal(const Vector2D& pointGlobal) const;

    Vector2D vectorLocalToGlobal(const Vector2D& vectLocal) const;
    Vector2D vectorGlobalToLocal(const Vector2D& vectGlobal) const;

    ConvexPolygon convexToGlobal(const ConvexPolygon& polygonLocal) const;
    ConvexPolygon convexToLocal(const ConvexPolygon& polygonGlobal) const;

    ConcavePolygon concaveToGlobal(const ConcavePolygon& polygonLocal) const;
    ConcavePolygon concaveToLocal(const ConcavePolygon& polygonGlobal) const;
};

float angle(const Vector2D& vect1, const Vector2D& vect2);

float dot(const Vector2D& vect1, const Vector2D& vect2);

float distance(const Vector2D& point1, const Vector2D& point2);
float distance(const Vector2D& point, const Line& line);
float sqrDistance(const Vector2D& point1, const Vector2D& point2);
float sqrDistance(const Vector2D& point, const Line& line);