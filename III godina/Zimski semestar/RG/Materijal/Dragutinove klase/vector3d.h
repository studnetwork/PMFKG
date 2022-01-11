#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <fstream>
#include <iostream>
#include <assert.h>
#include <math.h>


#define EPSILON 1.0e-10

class Vector4D;

class Vector3D
{
public:
    Vector3D(){}
    Vector3D(double x, double y, double z){Set(x,y,z);}
    Vector3D(const Vector3D &A);
    Vector3D(const Vector4D &A);

    void Set(double x, double y, double z){ m_x = x; m_y = y; m_z = z; }
    void Init(double x, double y, double z){Set(x,y,z);}
    void Copy(Vector3D& A){m_x = A.m_x; m_y = A.m_y; m_z = A.m_z; }

    void zero();

    double DistSqr(const Vector3D& A) const
    {
        return (m_x - A.m_x)*(m_x - A.m_x) + (m_y - A.m_y)*(m_y - A.m_y) + (m_z - A.m_z)*(m_z - A.m_z);
    }

    double Dist(const Vector3D& A) const
    {
        return sqrt(DistSqr(A));
    }

    double Norm() const {return sqrt(NormSqr());}
    double NormSqr() const {return m_x*m_x + m_y*m_y + m_z*m_z;}
    void Normalize();

    const Vector3D Cross(const Vector3D &v) const
    {
        return Vector3D(
            m_y*v.m_z - m_z*v.m_y,
            m_z*v.m_x - m_x*v.m_z,
            m_x*v.m_y - m_y*v.m_x);
    }

    Vector3D operator+(const Vector3D& A) const;
    Vector3D operator+() const;
    void operator+=(const Vector3D& A);
    Vector3D operator-(const Vector3D& A) const;
    Vector3D operator-() const;
    void operator-=(const Vector3D& A);
    Vector3D operator*(double k) const;
    void operator*=(double k);

    void add(const Vector3D& A, const Vector3D& B);
    void sub(const Vector3D& A, const Vector3D& B);
    void scalar(double k);
    void cross(const Vector3D& A, const Vector3D& B);
    void normal(const Vector3D& A, const Vector3D& B, const Vector3D& C);

    double& X() {return(m_x);}
    double& Y() {return(m_y);}
    double& Z() {return(m_z);}

    double operator*(const Vector3D& A)  const;  //dot product!
    bool operator==(const Vector3D& A) const;
    bool operator!=(const Vector3D& A) const;
    double dot(const Vector3D& A) const;
    bool cmp(const Vector3D& A, double epsilon=EPSILON) const;


	void toString();
	void toString(char s[]);

    inline double operator[](int i) const;
    inline double& operator[](int i);

    double AngleBetween(const Vector3D &v);

    friend class Vector4D;

public:
    double m_x, m_y, m_z;

    const static Vector3D AxisX;
    const static Vector3D AxisY;
    const static Vector3D AxisZ;

};

inline double Vector3D::operator[](int i) const
{
    assert(i >= 0 && i < 3);
    return((&m_x)[i]);
}

inline double& Vector3D::operator[](int i)
{
    assert(i >= 0 && i < 3);
    return((&m_x)[i]);
}


#endif // VECTOR3D_H