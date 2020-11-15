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
};

struct ConcavePolygon
{
    std::vector<ConvexPolygon> polygon;

    Rect getAABB() const;
};

struct Referential2D
{
    Vector2D m_origin;
    Vector2D m_i = { 1.f, 0.f };
    Vector2D m_j = { 0.f, 1.f };
    float    m_angle = 0.f;

    Referential2D(const Vector2D& origin, const Vector2D& i);

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
float clamp(float value, float min, float max);
float sign(float value);

bool    intersect(Vector2D point1, Vector2D point2);

bool    intersect(Vector2D point, Line line);

bool    intersect(Vector2D point, Segment segment);

bool    intersect(Vector2D point, Rect box);

bool    intersect(Line line1, Line line2);

bool    intersect(Line line, Segment segment);

bool    intersect(Segment segment1, Segment segment2);

bool    intersect(Circle circle, Vector2D point);

bool    intersect(Circle circle, Line line);

bool    intersect(Circle circle, Segment segment);

bool    intersect(Circle circle1, Circle circle2);

bool    intersect(Circle circle, Rect box);

bool    intersect(Rect box1, Rect box2);

bool    intersect(ConvexPolygon convex, Vector2D point);

bool    intersect(ConvexPolygon convex1, ConvexPolygon convex2);

bool    intersect(ConvexPolygon convex, Circle cicle);
