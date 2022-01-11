#include "vector3d.h"
#include "vector4d.h"
#include <assert.h>

using namespace std;


const Vector3D Vector3D::AxisX(1.0, 0.0, 0.0);
const Vector3D Vector3D::AxisY(0.0, 1.0, 0.0);
const Vector3D Vector3D::AxisZ(0.0, 0.0, 1.0);

Vector3D::Vector3D(const Vector3D& A)
{
    m_x = A.m_x;
    m_y = A.m_y;
    m_z = A.m_z;
}

Vector3D::Vector3D(const Vector4D &A)
{
    m_x = A.m_x;
    m_y = A.m_y;
    m_z = A.m_z;
}

void Vector3D::zero()
{
    m_x = 0.0;
    m_y = 0.0;
    m_z = 0.0;
}

Vector3D Vector3D::operator+(const Vector3D& A) const
{
  return(Vector3D(m_x+A.m_x, m_y+A.m_y, m_z+A.m_z));
}

Vector3D Vector3D::operator+() const
{
  return(*this);
}

void Vector3D::operator+=(const Vector3D& A)
{
  m_x+=A.m_x;
  m_y+=A.m_y;
  m_z+=A.m_z;
}

Vector3D Vector3D::operator-(const Vector3D& A) const
{
  return(Vector3D(m_x-A.m_x, m_y-A.m_y, m_z-A.m_z));
}

Vector3D Vector3D::operator-() const
{
  return(Vector3D(-m_x,-m_y,-m_z));
}

void Vector3D::operator-=(const Vector3D& A)
{
  m_x-=A.m_x;
  m_y-=A.m_y;
  m_z-=A.m_z;
}

Vector3D Vector3D::operator*(double k) const
{
  return(Vector3D(m_x*k, m_y*k, m_z*k));
}

void Vector3D::operator*=(double k)
{
  m_x*=k;
  m_y*=k;
  m_z*=k;
}

void Vector3D::Normalize()
{
    double norm = Norm();
    if (norm <= EPSILON)
        zero();
    else
    {
        m_x /= norm;
        m_y /= norm;
        m_z /= norm;
    }
}

void Vector3D::add(const Vector3D& A, const Vector3D& B)
{
  m_x=A.m_x + B.m_x;
  m_y=A.m_y + B.m_y;
  m_z=A.m_z + B.m_z;
}

void Vector3D::sub(const Vector3D& A, const Vector3D& B)
{
  m_x=A.m_x - B.m_x;
  m_y=A.m_y - B.m_y;
  m_z=A.m_z - B.m_z;
}

void Vector3D::scalar(double k)
{
  m_x*=k;
  m_y*=k;
  m_z*=k;
}

void Vector3D::cross(const Vector3D& A, const Vector3D& B)
{
  m_x=A.m_y*B.m_z - A.m_z*B.m_y;
  m_y=A.m_z*B.m_x - A.m_x*B.m_z;
  m_z=A.m_x*B.m_y - A.m_y*B.m_x;
}

void Vector3D::normal(const Vector3D& A, const Vector3D& B, const Vector3D& C)
{
  Vector3D P,Q;

  P.sub(C,B);
  Q.sub(A,B);
  cross(P,Q);
  Normalize();
}

double Vector3D::operator*(const Vector3D& A) const
{
  return(m_x*A.m_x + m_y*A.m_y + m_z*A.m_z);
}

bool Vector3D::operator==(const Vector3D& A) const
{
  return(cmp(A));
}

bool Vector3D::operator!=(const Vector3D& A) const
{
  return(!cmp(A));
}

double Vector3D::dot(const Vector3D& A) const
{
  return(m_x*A.m_x + m_y*A.m_y + m_z*A.m_z);
}

bool Vector3D::cmp(const Vector3D& A, double epsilon) const
{
  return(
    (fabs(m_x-A.m_x)<epsilon) &&
    (fabs(m_y-A.m_y)<epsilon) &&
    (fabs(m_z-A.m_z)<epsilon)
  );
}

void Vector3D::toString()
{
	cout << "x= " << m_x << ", y=" << m_y << ", z=" << m_z << "\n";
}

void Vector3D::toString(char s[])
{
	cout << s  << "  x= " << m_x << ", y=" << m_y << ", z=" << m_z << "\n";
}



double Vector3D::AngleBetween(const Vector3D &v)
{
    Vector3D a(m_x,m_y,m_z);

    double kosFi = (a * v) / (a.Norm() * v.Norm());
    double sinFi = (a.Cross(v)).Norm() / (a.Norm() * v.Norm());

    double fi = atan2(sinFi,kosFi);

    return fi;
}