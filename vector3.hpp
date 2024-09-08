#ifndef VECTOR_3_HPP
#define VECTOR_3_HPP

#include <cmath>
#include <stdio.h>

struct vector3 {
    float x, y, z;

    // vector3() 
    //     : x(0), y(0), z(0)
    // {
    // }

    // vector3(float x, float y, float z) 
    //     : x(x), y(y), z(z)
    // {
    // }
    
    // addop. doesn't modify object. therefore const.
    vector3 operator+(const vector3& a) const
    {
        return vector3{a.x+x, a.y+y, a.z+z};
    } 

    vector3 operator-(const vector3& a) const
    {
        return vector3{x-a.x, y-a.y, z-a.z};
    }

    vector3 operator*(const vector3& a) const
    {
        return vector3{a.x*x, a.y*y, a.z*z};
    } 

    vector3 operator/(const vector3& a) const
    {
        return vector3{a.x/x, a.y/y, a.z/z};
    } 

    vector3 operator*(const float a) const
    {
        return vector3{a*x, a*y, a*z};
    } 

    vector3 operator/(const float a) const
    {
        return vector3{x/a, y/a, z/a};
    } 

    void operator+=(const vector3& a)
    {
        x = a.x+x;
        y = a.y+y;
        z = a.z+z;
    } 

    void operator-=(const vector3& a)
    {
        x = x-a.x;
        y = y-a.y;
        z = z-a.z;
    }

    void operator*= (const vector3& a)
    {
        x = a.x*x;
        y = a.y*y;
        z = a.z*z;
    }

    float dot(const vector3& a) const
    {
        return x*a.x + y*a.y + z*a.z;
    }

    vector3 cross(const vector3& a) const
    {
        return vector3{y*a.z - z*a.y,z*a.x - x*a.z,x*a.y - y*a.x};
    }

    vector3 norm () const
    {
        float mag = sqrt(x*x + y*y + z*z);
        return vector3{x/mag,y/mag,z/mag};
    }

    void print()
    {
        printf("{%.3f, %.3f, %.3f}",x,y,z);
    }

    void println()
    {
        printf("{%.3f, %.3f, %.3f}\n",x,y,z);
    }

    float mag() const
    {
        return sqrt(x*x + y*y + z*z);
    }

    float mag2() const
    {
        return x*x + y*y + z*z;
    }

    vector3 rotate(vector3 axis, float rad) const
    {
        vector3 result = {x, y, z};
        result = result * cos(rad) + axis.norm().cross(result)*sin(rad) + axis.norm() * (axis.norm().dot(result)) * (1 - cos(rad));
        return result;
    }
};

#endif