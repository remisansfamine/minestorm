#pragma once

#include <cfloat>

#include <vector>

#define M_PI 3.14159265358979323846f

#define _USE_MATH_DEFINES
#include <cmath>

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

    Vector2D operator-() const;
    Vector2D operator+(const Vector2D&) const;
    Vector2D& operator+=(const Vector2D&);
    Vector2D operator-(const Vector2D&) const;
    Vector2D& operator-=(const Vector2D&);
    Vector2D operator*(float) const;
    Vector2D& operator*=(float);
    Vector2D operator/(float) const;
    Vector2D& operator/=(float);
    bool operator==(const Vector2D&) const;

    operator Vector2();

    Vector2D& rotate(float angle);
    Vector2D& rotate90();
    Vector2D& rotateAround(const Vector2D& center, float angle);

    Vector2D normal() const;
};

// Struct of segment that starts at pt1 and ends at pt2
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

// Struct of point, or vector of coordinates (x; y)
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

    float minimum(const Range&) const;
    float maximum(const Range&) const;

    Range& merge(const Range&);
    Range& merge(float);

    bool interfere(const Range&) const;
};

float angle(const Vector2D& vect1, const Vector2D& vect2);

float dot(const Vector2D& vect1, const Vector2D& vect2);

float distance(const Vector2D& point1, const Vector2D& point2);
float distance(const Vector2D& point, const Line& line);
float sqrDistance(const Vector2D& point1, const Vector2D& point2);
float sqrDistance(const Vector2D& point, const Line& line);

float min(float value1, float value2);
float max(float value1, float value2);
float randomNumber(float Min, float Max);
float clamp(float value, float min, float max);
int sign(float value);

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