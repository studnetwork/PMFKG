#ifndef VECTOR4D_H
#define VECTOR4D_H


#include "vector3d.h"

class Vector4D
{
public:
    double m_x, m_y, m_z, m_w;
public:
    Vector4D(){}
    Vector4D(double x, double y, double z, double w);
    Vector4D(const Vector4D &a);
    Vector4D(const Vector3D &a);

    void set(double x, double y, double z, double w){ m_x = x; m_y = y; m_z = z; m_w = w; }
    void zero(){ m_x = m_y = m_z = m_w = 0.0; }

    Vector4D& operator =(const Vector4D &A);

    inline double& operator[](int i);
    inline double operator[](int i) const;

    Vector4D operator+(const Vector4D& A);
    Vector4D operator+();
    void operator+=(const Vector4D& A);
    Vector4D operator-(const Vector4D& A);
    Vector4D operator-();
    void operator-=(const Vector4D& A);
    Vector4D operator*(double k);
    void operator*=(double k);

    double squared();
    double length();

    void normalize();

    double X(){ return m_x; }
    double Y(){ return m_y; }
    double Z(){ return m_z; }
    double W(){ return m_w; }

    friend class Vector3D;
};

inline double& Vector4D::operator[](int i)
{
  assert(i>=0 && i<4);
  return((&m_x)[i]);
}

inline double Vector4D::operator[](int i) const
 {
   assert(i>=0 && i<4);
   return((&m_x)[i]);
 }

#endif // VECTOR4D_H