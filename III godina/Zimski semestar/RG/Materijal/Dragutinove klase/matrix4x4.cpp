#include "matrix4x4.h"
#include <string.h>
#include <math.h>

#define MM_PI 3.14

Matrix4x4::Matrix4x4(Matrix4x4& A)
{
    memcpy(m_d, A.m_d, sizeof(m_d));
}

Matrix4x4& Matrix4x4::operator =(Matrix4x4& A)
{
    memcpy(m_d, A.m_d, sizeof(m_d));
    return(*this);
}

void Matrix4x4::operator =(const Matrix4x4& A)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_d[i][j] = A[i][j];
}

void Matrix4x4::zero()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_d[i][j] = 0.0;
}

void Matrix4x4::identity()
{
    zero();
    for(int i = 0; i < 4; i++)
        m_d[i][i] = 1.0;
}

Matrix4x4 Matrix4x4::operator +(const Matrix4x4 &A)
{
    Matrix4x4 M;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            M[i][j] = m_d[i][j] + A[i][j];

    return(M);
}

Matrix4x4 Matrix4x4::operator +()
{
    return(*this);
}

void Matrix4x4::operator +=(const Matrix4x4 &A)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_d[i][j] += A[i][j];
}

Matrix4x4 Matrix4x4::operator -(const Matrix4x4 &A)
{
    Matrix4x4 M;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            M[i][j] = m_d[i][j] - A[i][j];

    return(M);
}

Matrix4x4 Matrix4x4::operator -()
{
    Matrix4x4 M;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            M[i][j] = -m_d[i][j];

    return(M);
}

void Matrix4x4::operator -=(const Matrix4x4 &A)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_d[i][j] -= A[i][j];
}

Matrix4x4 Matrix4x4::operator *(const Matrix4x4 &A)
{
    Matrix4x4 M;
    double ab;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ab = 0.0;
            for (int k = 0; k < 4; k++)
                ab += m_d[i][k]*A[k][j];
            M[i][j] = ab;
        }
    }
    return(M);
}

void Matrix4x4::operator *=(const Matrix4x4 &A)
{
    double mm[4][4];
    double ab;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ab = 0.0;
            for (int k = 0; k < 4; k++)
                ab += m_d[i][k]*A[k][j];
            mm[i][j] = ab;
        }
    }
    memcpy(m_d, mm ,sizeof(m_d));
}

Matrix4x4 Matrix4x4::operator *(double k)
{
    Matrix4x4 M;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            M[i][j] = m_d[i][j] * k;

    return(M);
}

void Matrix4x4::operator *=(double k)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_d[i][j] *= k;
}

void Matrix4x4::neg()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_d[i][j] = -m_d[i][j];
}

void Matrix4x4::abs()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_d[i][j] = fabs(m_d[i][j]);
}

void Matrix4x4::transpose()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            double t = m_d[i][j];
            m_d[i][j] = m_d[j][i];
            m_d[j][i] = t;
        }
}

static inline double det2x2( double a, double b,
                             double c, double d)
{
  return((a*d)-(b*c));
}


static double det3x3(double a1, double a2, double a3,
                     double b1, double b2, double b3,
                     double c1, double c2, double c3)
{
  return(a1*det2x2(b2,b3,c2,c3)-
         b1*det2x2(a2,a3,c2,c3)+
         c1*det2x2(a2,a3,b2,b3)
         );
}

double Matrix4x4::det()
{
  double a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4;

  a1 = m_d[0][0];
  b1 = m_d[1][0];
  c1 = m_d[2][0];
  d1 = m_d[3][0];
  a2 = m_d[0][1];
  b2 = m_d[1][1];
  c2 = m_d[2][1];
  d2 = m_d[3][1];
  a3 = m_d[0][2];
  b3 = m_d[1][2];
  c3 = m_d[2][2];
  d3 = m_d[3][2];
  a4 = m_d[0][3];
  b4 = m_d[1][3];
  c4 = m_d[2][3];
  d4 = m_d[3][3];
  return( a1 * det3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4)-
          b1 * det3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4)+
          c1 * det3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4)-
          d1 * det3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4)
        );
}

void Matrix4x4::adjoint()
{
    double a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4;

    a1 = m_d[0][0];
    b1 = m_d[1][0];
    c1 = m_d[2][0];
    d1 = m_d[3][0];
    a2 = m_d[0][1];
    b2 = m_d[1][1];
    c2 = m_d[2][1];
    d2 = m_d[3][1];
    a3 = m_d[0][2];
    b3 = m_d[1][2];
    c3 = m_d[2][2];
    d3 = m_d[3][2];
    a4 = m_d[0][3];
    b4 = m_d[1][3];
    c4 = m_d[2][3];
    d4 = m_d[3][3];
    m_d[0][0]=  det3x3 (b2, b3, b4, c2, c3, c4, d2, d3, d4);
    m_d[0][1]= -det3x3 (a2, a3, a4, c2, c3, c4, d2, d3, d4);
    m_d[0][2]=  det3x3 (a2, a3, a4, b2, b3, b4, d2, d3, d4);
    m_d[0][3]= -det3x3 (a2, a3, a4, b2, b3, b4, c2, c3, c4);
    m_d[1][0]= -det3x3 (b1, b3, b4, c1, c3, c4, d1, d3, d4);
    m_d[1][1]=  det3x3 (a1, a3, a4, c1, c3, c4, d1, d3, d4);
    m_d[1][2]= -det3x3 (a1, a3, a4, b1, b3, b4, d1, d3, d4);
    m_d[1][3]=  det3x3 (a1, a3, a4, b1, b3, b4, c1, c3, c4);
    m_d[2][0]=  det3x3 (b1, b2, b4, c1, c2, c4, d1, d2, d4);
    m_d[2][1]= -det3x3 (a1, a2, a4, c1, c2, c4, d1, d2, d4);
    m_d[2][2]=  det3x3 (a1, a2, a4, b1, b2, b4, d1, d2, d4);
    m_d[2][3]= -det3x3 (a1, a2, a4, b1, b2, b4, c1, c2, c4);
    m_d[3][0]= -det3x3 (b1, b2, b3, c1, c2, c3, d1, d2, d3);
    m_d[3][1]=  det3x3 (a1, a2, a3, c1, c2, c3, d1, d2, d3);
    m_d[3][2]= -det3x3 (a1, a2, a3, b1, b2, b3, d1, d2, d3);
    m_d[3][3]=  det3x3 (a1, a2, a3, b1, b2, b3, c1, c2, c3);
}

void Matrix4x4::copy(const Matrix4x4 &A)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_d[i][j] = A[i][j];
}

bool Matrix4x4::inv()
{
    double determinant = det();

    if(determinant < EPSILON)
        return false;

    Matrix4x4 A(*this);

    A.adjoint();
    A *= determinant;

    copy(A);

    return true;
}

void Matrix4x4::loadTranslate(double tx, double ty, double tz)
{
    identity();
    m_d[0][3] = tx;
    m_d[1][3] = ty;
    m_d[2][3] = tz;
}

void Matrix4x4::loadTranslate(Vector3D tv)
{
	loadTranslate(tv.X(), tv.Y(), tv.Z());
}

void Matrix4x4::loadScale(double sx, double sy, double sz)
{
    identity();
    m_d[0][0] = sx;
    m_d[1][1] = sy;
    m_d[2][2] = sz;
}

void Matrix4x4::loadRotateX(double phi)
{
    double sinPhi = sin(phi);
    double cosPhi = cos(phi);

    zero();
    m_d[0][0] = 1.0;
    m_d[1][1] = cosPhi;
    m_d[2][2] = cosPhi;
    m_d[1][2] = -sinPhi;
    m_d[2][1] = sinPhi;
    m_d[3][3] = 1.0;
}

void Matrix4x4::loadRotateY(double phi)
{
    double sinPhi = sin(phi);
    double cosPhi = cos(phi);

    zero();
    m_d[0][0] = cosPhi;
    m_d[1][1] = 1.0;
    m_d[2][2] = cosPhi;
    m_d[0][2] = sinPhi;
    m_d[2][0] = -sinPhi;
    m_d[3][3] = 1.0;
}

void Matrix4x4::loadRotateZ(double phi)
{
    double sinPhi = sin(phi);
    double cosPhi = cos(phi);

    zero();
    m_d[0][0] = cosPhi;
    m_d[1][1] = cosPhi;
    m_d[2][2] = 1.0;
    m_d[0][1] = -sinPhi;
    m_d[1][0] = sinPhi;
    m_d[3][3] = 1.0;
}

Vector3D Matrix4x4::Translate(Vector3D & v, Vector3D & vTranslate)
{
	return Translate(v, vTranslate.X(), vTranslate.Y(), vTranslate.Z());
}

Vector3D Matrix4x4::Translate(Vector3D & v, double tx, double ty, double tz)
{
	Matrix4x4 m;
	m.loadTranslate(tx, ty, tz);
	return m.Transform(v);
}

vector<Vector3D> Matrix4x4::Translate(vector<Vector3D>& shape, Vector3D & vTranslate)
{
	vector<Vector3D> newShape;
	for (int i = 0; i < shape.size(); i++)
	{
		newShape.push_back(Translate(shape[i], vTranslate));
	}
	return newShape;
}

vector<Vector3D> Matrix4x4::Translate(vector<Vector3D>& shape, double tx, double ty, double tz)
{
	Vector3D vTranslate(tx, ty, tz);
	return Translate(shape, vTranslate);
}



vector<vector<Vector3D>> Matrix4x4::Translate(vector<vector<Vector3D>> &body, Vector3D &vTranslate)
{
	vector<vector<Vector3D>> newBody;
	for (int i = 0; i < body.size(); i++)
	{
		newBody.push_back(Translate(body[i], vTranslate));
	}
	return newBody;
}


vector<vector<Vector3D>> Matrix4x4::Translate(vector<vector<Vector3D>> &body, double tx, double ty, double tz)
{
	Vector3D vTranslate(tx, ty, tz);
	return Translate(body, vTranslate);
}

Vector3D Matrix4x4::Rotate(Vector3D & v, Vector3D & centerOfRotation, int axis, double phi)
{
	if(axis<1 && axis > 3)
		return Vector3D();


	Matrix4x4 m,m_r, m_moveToCentre, m_back;

	m_moveToCentre.loadTranslate(-centerOfRotation.X(), -centerOfRotation.Y(), -centerOfRotation.Z());
	m_back.loadTranslate(centerOfRotation.X(), centerOfRotation.Y(), centerOfRotation.Z());

	if (axis == 1)
	{
		m_r.loadRotateX(phi);
	}
	else
		if (axis == 2)
		{
			m_r.loadRotateY(phi);
		}
		else
		{
			m_r.loadRotateZ(phi);
		}

	m = m_back * m_r * m_moveToCentre;

	return m.Transform(v);
}

vector<Vector3D> Matrix4x4::Rotate(vector<Vector3D>& shape, Vector3D & centerOfRotation, int axis, double phi)
{
	if (axis<1 && axis > 3)
		return vector<Vector3D>();

	Matrix4x4 m, m_r, m_moveToCentre, m_back;

	m_moveToCentre.loadTranslate(-centerOfRotation.X(), -centerOfRotation.Y(), -centerOfRotation.Z());
	m_back.loadTranslate(centerOfRotation.X(), centerOfRotation.Y(), centerOfRotation.Z());

	if (axis == 1)
	{
		m_r.loadRotateX(phi);
	}
	else
		if (axis == 2)
		{
			m_r.loadRotateY(phi);
		}
		else
		{
			m_r.loadRotateZ(phi);
		}

	m = m_back * m_r * m_moveToCentre;

	return m.Transform(shape);
}


vector<vector<Vector3D>>Matrix4x4::Rotate(vector<vector<Vector3D>> &body, Vector3D &centerOfRotation, int axis, double phi)
{

	if (axis<1 && axis > 3)
		return vector<vector<Vector3D>>();

	Matrix4x4 m, m_r, m_moveToCentre, m_back;

	m_moveToCentre.loadTranslate(-centerOfRotation.X(), -centerOfRotation.Y(), -centerOfRotation.Z());
	m_back.loadTranslate(centerOfRotation.X(), centerOfRotation.Y(), centerOfRotation.Z());

	if (axis == 1)
	{
		m_r.loadRotateX(phi);
	}
	else
		if (axis == 2)
		{
			m_r.loadRotateY(phi);
		}
		else
		{
			m_r.loadRotateZ(phi);
		}

	m = m_back * m_r * m_moveToCentre;

	return m.Transform(body);

}




Matrix4x4 Matrix4x4::CreateRotationMatrix(Vector3D & P, Vector3D & axis, double alpha)

{
	Matrix4x4 MR, MTranslationP, MRotationYteta_minus, MRotationXfi,
		MRotationZalpha, MRotationXfi_minus, MRotationYteta,
		MTranslationPminus;

	double teta, fi;

	if (axis.Z() != 0)
	{
		teta = atan(axis.m_x / axis.m_z);
	}
	else
	{
		if (axis.X() > 0)
		{
			teta = MM_PI / 2.0;
		}
		else
		{
			if (axis.X() < 0 )
			{
				teta = - MM_PI / 2.0;
			}
			else
			{
				teta = 0;
			}
		}
	}

	double d = sqrt((axis.X() *axis.X()) + (axis.Z() *axis.Z()) );
	if (d!=0)
	{
		fi = atan(axis.Y() / d);
	}
	else
	{
		if (axis.Y() > 0 )
		{
			fi = MM_PI / 2.0;
		}
		else 
			if (axis.Y() < 0)
			{
				fi = -MM_PI / 2.0;
			}
			else
			{
				fi = 0;
			}

	}
//	fi = atan(axis.m_y / sqrt(axis.m_x*axis.m_x + axis.m_z*axis.m_z));
	
	MTranslationP.loadTranslate(P.m_x, P.m_y, P.m_z);
	MTranslationPminus.loadTranslate(-P.m_x, -P.m_y, -P.m_z);
	MRotationXfi.loadRotateX(fi);
	MRotationXfi_minus.loadRotateX(-fi);
	MRotationZalpha.loadRotateZ(alpha);
	MRotationYteta.loadRotateY(teta);
	MRotationYteta_minus.loadRotateY(-teta);

	MR = MTranslationP  * MRotationYteta * MRotationXfi_minus *
		MRotationZalpha * MRotationXfi * MRotationYteta_minus *
		MTranslationPminus;

	
	return MR;
}


Vector3D Matrix4x4::operator *(const Vector3D &A)
{
    Vector3D v;

    v.m_x = m_d[0][0]*A.m_x + m_d[0][1]*A.m_y + m_d[0][2]*A.m_z + m_d[0][3];
    v.m_y = m_d[1][0]*A.m_x + m_d[1][1]*A.m_y + m_d[1][2]*A.m_z + m_d[1][3];
    v.m_z = m_d[2][0]*A.m_x + m_d[2][1]*A.m_y + m_d[2][2]*A.m_z + m_d[2][3];

    return v;
}

Vector3D Matrix4x4::Transform(const Vector3D &A)
{
    Vector3D v;

    double x = A.m_x;
    double y = A.m_y;
    double z = A.m_z;

    v.m_x = m_d[0][0]*x + m_d[0][1]*y + m_d[0][2]*z + m_d[0][3];
    v.m_y = m_d[1][0]*x + m_d[1][1]*y + m_d[1][2]*z + m_d[1][3];
    v.m_z = m_d[2][0]*x + m_d[2][1]*y + m_d[2][2]*z + m_d[2][3];

    return(v);
}

vector<Vector3D> Matrix4x4::Transform(const vector<Vector3D>& shape)
{
	vector<Vector3D> newShape;
	for (int i = 0; i < shape.size(); i++)
	{
		newShape.push_back(Transform(shape[i]));
	}
	return newShape;

}

vector<vector<Vector3D>>Matrix4x4::Transform(const vector<vector<Vector3D>> &body)
{
	vector<vector<Vector3D>> newBody;
	for (int i = 0; i < body.size(); i++)
	{
		newBody.push_back(Transform(body[i]));
	}
	return newBody;
}



Vector4D Matrix4x4::operator *(const Vector4D &A)
{
    Vector4D v;

    v.m_x = m_d[0][0]*A.m_x + m_d[0][1]*A.m_y + m_d[0][2]*A.m_z + m_d[0][3]*A.m_w;
    v.m_y = m_d[1][0]*A.m_x + m_d[1][1]*A.m_y + m_d[1][2]*A.m_z + m_d[1][3]*A.m_w;
    v.m_z = m_d[2][0]*A.m_x + m_d[2][1]*A.m_y + m_d[2][2]*A.m_z + m_d[2][3]*A.m_w;
    v.m_w = m_d[3][0]*A.m_x + m_d[3][1]*A.m_y + m_d[3][2]*A.m_z + m_d[3][3]*A.m_w;

    return v;
}

Vector4D Matrix4x4::Transform(const Vector4D &A)
{
    Vector4D v;

    double x = A.m_x;
    double y = A.m_y;
    double z = A.m_z;
    double w = A.m_w;

    v.m_x = m_d[0][0]*x + m_d[0][1]*y + m_d[0][2]*z + m_d[0][3]*w;
    v.m_y = m_d[1][0]*x + m_d[1][1]*y + m_d[1][2]*z + m_d[1][3]*w;
    v.m_z = m_d[2][0]*x + m_d[2][1]*y + m_d[2][2]*z + m_d[2][3]*w;
    v.m_w = m_d[3][0]*x + m_d[3][1]*y + m_d[3][2]*z + m_d[3][3]*w;

    return(v);
}

bool Matrix4x4::cmp(Matrix4x4 &A)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(fabs(m_d[i][j] - A[i][j]) < EPSILON)
                return false;

    return true;
}

bool Matrix4x4::operator ==(Matrix4x4 &A)
{
    return cmp(A);
}

bool Matrix4x4::operator !=(Matrix4x4 &A)
{
    return (!cmp(A));
}