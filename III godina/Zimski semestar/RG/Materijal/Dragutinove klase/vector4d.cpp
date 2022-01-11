#include "vector4d.h"

Vector4D::Vector4D(double x, double y, double z, double w)
{
    set(x,y,z,w);
}

Vector4D::Vector4D(const Vector4D &a)
{
    m_x = a.m_x;
    m_y = a.m_y;
    m_z = a.m_z;
    m_w = a.m_w;
}

Vector4D::Vector4D(const Vector3D &a)
{
    m_x = a.m_x;
    m_y = a.m_y;
    m_z = a.m_z;
    m_w = 1.0;
}

Vector4D& Vector4D::operator =(const Vector4D &A)
{
    m_x = A.m_x;
    m_y = A.m_y;
    m_z = A.m_z;
    m_w = A.m_w;

    return(*this);
}

Vector4D Vector4D::operator +(const Vector4D &A)
{
    Vector4D B(m_x + A.m_x, m_y + A.m_y, m_z + A.m_z, m_w + A.m_w);
    return (B);
}

Vector4D Vector4D::operator +()
{
    return(*this);
}

void Vector4D::operator +=(const Vector4D &A)
{
    m_x += A.m_x;
    m_y += A.m_y;
    m_z += A.m_z;
    m_w += A.m_w;
}

Vector4D Vector4D::operator -(const Vector4D &A)
{
    Vector4D B(m_x - A.m_x, m_y -A.m_y, m_z - A.m_z, m_w - A.m_w);
    return (B);
}

Vector4D Vector4D::operator -()
{
    Vector4D A(-m_x, -m_y, -m_z, -m_w);
    return (A);
}

void Vector4D::operator -=(const Vector4D &A)
{
    m_x -= A.m_x;
    m_y -= A.m_y;
    m_z -= A.m_z;
    m_w -= A.m_w;
}

Vector4D Vector4D::operator*(double k)
{
	return(Vector4D(m_x*k, m_y*k, m_z*k, m_w*k));
}

void Vector4D::operator*=(double k)
{
	m_x *= k;
	m_y *= k;
	m_z *= k;
	m_w *= k;

}

double Vector4D::squared()
{
    return(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
}

double Vector4D::length()
{
    return(sqrt(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w));
}

void Vector4D::normalize()
{
    double l = length();
    if(l < EPSILON)
        m_x = m_y = m_z = m_w = 0.0;
    else
    {
        double c = 1.0/l;
        m_x *= c;
        m_y *= c;
        m_z *= c;
        m_w *= c;
    }

}