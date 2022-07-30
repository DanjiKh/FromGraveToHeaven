#ifndef RAYLIB_VF2D_HEADER
#define RAYLIB_VF2D_HEADER

#include "raylib.h"
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

class vf2d {
    Vector2 _data;
public:
    vf2d(float x=0, float y=0) {_data.x = x; _data.y = y;}
    vf2d(const vf2d& v) {_data.x = v.x(); _data.y = v.y();}
    vf2d(const Vector2& v) {_data.x = v.x; _data.y = v.y;}
    vf2d& operator=(const vf2d& v) = default;
    float mag() const { return float(std::sqrt(_data.x * _data.x + _data.y * _data.y)); }
    float mag2() const { return _data.x * _data.x + _data.y * _data.y; }
    vf2d  norm() const { float r = 1 / mag(); return vf2d(_data.x * r, _data.y * r); }
    vf2d  perp() const { return vf2d(-_data.y, _data.x); }
    vf2d  floor() const { return vf2d(std::floor(_data.x), std::floor(_data.y)); }
    vf2d  ceil() const { return vf2d(std::ceil(_data.x), std::ceil(_data.y)); }
    vf2d  max(const vf2d& v) const { return vf2d(std::max(_data.x, v.x()), std::max(_data.y, v.y())); }
    vf2d  min(const vf2d& v) const { return vf2d(std::min(_data.x, v.x()), std::min(_data.y, v.y())); }
    vf2d  cart() { return { std::cos(_data.y) * _data.x, std::sin(_data.y) * _data.x }; }
    vf2d  polar() { return { mag(), std::atan2(_data.y, _data.x) }; }
    float dot(const vf2d& rhs) const { return _data.x * rhs.x() + _data.y * rhs.y(); }
    float cross(const vf2d& rhs) const { return _data.x * rhs.y() - _data.y * rhs.x(); }
    vf2d  operator +  (const vf2d& rhs) const { return vf2d(_data.x + rhs.x(), _data.y + rhs.y()); }
    vf2d  operator -  (const vf2d& rhs) const { return vf2d(_data.x - rhs.x(), _data.y - rhs.y()); }
    vf2d  operator *  (const float& rhs)           const { return vf2d(_data.x * rhs, _data.y * rhs); }
    vf2d  operator *  (const vf2d& rhs) const { return vf2d(_data.x * rhs.x(), _data.y * rhs.y()); }
    vf2d  operator /  (const float& rhs)           const { return vf2d(_data.x / rhs, _data.y / rhs); }
    vf2d  operator /  (const vf2d& rhs) const { return vf2d(_data.x / rhs.x(), _data.y / rhs.y()); }
    vf2d& operator += (const vf2d& rhs) { _data.x += rhs.x(); _data.y += rhs.y(); return *this; }
    vf2d& operator -= (const vf2d& rhs) { _data.x -= rhs.x(); _data.y -= rhs.y(); return *this; }
    vf2d& operator *= (const float& rhs) { _data.x *= rhs; _data.y *= rhs; return *this; }
    vf2d& operator /= (const float& rhs) { _data.x /= rhs; _data.y /= rhs; return *this; }
    vf2d& operator *= (const vf2d& rhs) { _data.x *= rhs.x(); _data.y *= rhs.y(); return *this; }
    vf2d& operator /= (const vf2d& rhs) { _data.x /= rhs.x(); _data.y /= rhs.y(); return *this; }
    vf2d  operator +  () const { return { +_data.x, +_data.y }; }
    vf2d  operator -  () const { return { -_data.x, -_data.y }; }
    bool operator == (const vf2d& rhs) const { return (_data.x == rhs.x() && _data.y == rhs.y()); }
    bool operator != (const vf2d& rhs) const { return (_data.x != rhs.x() || _data.y != rhs.y()); }
    const std::string str() const { return std::string("(") + std::to_string(_data.x) + "," + std::to_string(_data.y) + ")"; }
    friend std::ostream& operator << (std::ostream& os, const vf2d& rhs) { os << rhs.str(); return os; }

    const Vector2 data() const {
        return _data;
    }

    const float x() const {
        return _data.x;
    }

    const float y() const {
        return _data.y;
    }
};

inline bool operator < (const vf2d& lhs, const vf2d& rhs)
{ return lhs.y() < rhs.y() && lhs.x() < rhs.x(); }
inline bool operator > (const vf2d& lhs, const vf2d& rhs)
{ return lhs.y() > rhs.y() && lhs.x() > rhs.x(); }

#endif