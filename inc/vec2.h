#ifndef VEC2_H
#define VEC2_H

#include <SFML/Graphics.hpp>

template <typename T>
struct Vec2
{
    T x;
    T y;

    Vec2() : x(0) , y(0)
    {}
    Vec2(T _x, T _y) : x(_x) , y(_y)
    {}

    template <typename U>
    Vec2(const Vec2<U>& v)
    {
        x = (U)v.x;
        y = (U)v.y;
    }

    Vec2<int> floor();
};

typedef Vec2<int> Vec2i;
typedef Vec2<double> Vec2f;

template <>
inline Vec2<int> Vec2<double>::floor()
{
    return Vec2i((int)x, (int)y);
}


template <typename T>
inline Vec2<T> operator + (Vec2<T> u, Vec2<T> v)
{
    Vec2<T> result;
    result.x = u.x + v.x;
    result.y = u.y + v.y;

    return result;
}

template <typename T>
inline Vec2<T> operator - (Vec2<T> u, Vec2<T> v)
{
    Vec2<T> result;
    result.x = u.x - v.x;
    result.y = u.y - v.y;

    return result;
}

template <typename T>
inline Vec2<T> operator += (Vec2<T> &u, Vec2<T> v)
{
    u.x += v.x;
    u.y += v.y;

    return u;
}

template <typename T, typename S>
inline Vec2<T> operator * (Vec2<T> u, S s)
{
    Vec2<T> result;
    result.x = u.x * s;
    result.y = u.y * s;

    return result;
}

template <typename T, typename S>
inline Vec2<T> operator *= (Vec2<T> &u, S s)
{
    u.x *= s;
    u.y *= s;

    return u;
}

template <typename T, typename S>
inline Vec2<T> operator / (Vec2<T> u, S s)
{
    Vec2<T> result;
    result.x = u.x / s;
    result.y = u.y / s;

    return result;
}

template <typename T, typename S>
inline Vec2<T> operator /= (Vec2<T> &u, S s)
{
    u.x /= s;
    u.y /= s;

    return u;
}

template <typename T>
inline bool operator < (const Vec2<T> &u, const Vec2<T> &v)
{
    if (u.x < v.x)
        return true;
    else if (u.x > v.x)
        return false;
    else
    {
        if (u.y < v.y)
            return true;
        else
            return false;
    }
}

template <typename T>
inline bool operator == (const Vec2<T> &u, const Vec2<T> &v)
{
    return (u.x == v.x && u.y == v.y);
}

#endif // VEC2_H
