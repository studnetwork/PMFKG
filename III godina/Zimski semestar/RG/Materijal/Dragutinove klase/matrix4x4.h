#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include <assert.h>
#include "vector4d.h"
#include <vector>


using namespace std;
#define EPSILON 1.0e-10

enum ProjectionType{ORTHOGRAPHIC_PROJECTION, PERSPECTIVE_PROJECTION};

class Matrix4x4
{
public:
    double m_d[4][4];
public:
    Matrix4x4(){}
    Matrix4x4(Matrix4x4& A);
    Matrix4x4& operator=(Matrix4x4& A);

    void zero();
    void identity();

    void copy(const Matrix4x4& A);

    inline void set(int row, int col, double value);

    inline double* operator[](int index);
    inline const double* operator[](int index) const;

    void operator=(const Matrix4x4& A);
    Matrix4x4 operator+(const Matrix4x4& A);
    Matrix4x4 operator+();
    void operator+=(const Matrix4x4& A);
    Matrix4x4 operator-();
    Matrix4x4 operator-(const Matrix4x4& A);
    void operator-=(const Matrix4x4& A);
    Matrix4x4 operator*(const Matrix4x4& A);
    void operator*=(const Matrix4x4& A);
    Matrix4x4 operator*(double k);
    void operator*=(double k);

    void neg();
    void abs();
    void transpose();

    double det();
    void adjoint();
    bool inv();

    bool cmp(Matrix4x4 &A);
    bool operator ==(Matrix4x4 &A);
    bool operator !=(Matrix4x4 &A);

    void loadTranslate(double tx, double ty, double tz);
	void loadTranslate(Vector3D tv);
    void loadScale(double sx, double sy, double sz);
    void loadRotateX(double phi);
    void loadRotateY(double phi);
    void loadRotateZ(double phi);

	//--------------------

	/*
		Vektor v se translira za vrednost vektora vTranslate
	*/
 	static Vector3D Translate(Vector3D &v, Vector3D &vTranslate);

	/*
		Vektor v se translira za vrednosti tx, ty, tz
	*/
	static Vector3D Translate(Vector3D &v, double tx, double ty, double tz);

	/*
		Oblik (lista vektora) se translira za vrednost vektora vTranslate
	*/
	static vector<Vector3D> Translate(vector<Vector3D> &shape, Vector3D &vTranslate);
	
	/*
		Oblik (lista vektora) se translira za vrednosti tx, ty, tz
	*/
	static vector<Vector3D> Translate(vector<Vector3D> &shape, double tx, double ty, double tz);

	/*
	    Telo (lista liste vektora) se translira za vrednost vektora vTranslate
	*/
	static vector<vector<Vector3D>> Translate(vector<vector<Vector3D>> &body, Vector3D &vTranslate);
	
	/*
		Telo (lista liste vektora) se translira za vrednosti tx, ty, tz
	*/
	static vector<vector<Vector3D>> Translate(vector<vector<Vector3D>> &body, double tx, double ty, double tz);


	//-----------------

	/*
		Rotiraj vektor u odnosu na tacku centerOfRotation za ugao phi, axis 1 x, 2 y, 3z
	*/
	static Vector3D Rotate(Vector3D &v, Vector3D &centerOfRotation, int axis, double phi);


	/*
		Rotiraj oblik u odnosu na tacku centerOfRotation za ugao phi, axis 1 x, 2 y, 3z
	*/
	static vector<Vector3D> Rotate(vector<Vector3D> &shape, Vector3D &centerOfRotation, int axis, double phi);

	/*
		Rotiraj telo u odnosu na tacku centerOfRotation za ugao phi, axis 1 x, 2 y, 3z
	*/
	static vector<vector<Vector3D>> Rotate(vector<vector<Vector3D>> &body, Vector3D &centerOfRotation, int axis, double phi);

	/*
		Kreiraj rotacionu matricu za rotaciju tacke p u odnosu na osu axis za ugao alpha
	*/
	static Matrix4x4 CreateRotationMatrix(Vector3D &P, Vector3D &axis, double alpha);

    Vector3D operator*(const Vector3D &A);
   
	/*
		Izvrsi transformaciju 3D vektora
	*/
	Vector3D Transform(const Vector3D &A);
	
	/*
		Izvrsi transformaciju oblika ( lista 3D vektora)
	*/
	vector<Vector3D> Transform(const vector<Vector3D> &shape);
	
	/*
		Izvrsi transformaciju Tela ( lista liste 3D vektora)
	*/
	vector<vector<Vector3D>> Transform(const vector<vector<Vector3D>> &body);


    Vector4D operator*(const Vector4D &A);
	
	/*
	Izvrsi transformaciju 4D vektora
	*/
	Vector4D Transform(const Vector4D &A);

};

inline const double* Matrix4x4::operator[](int index) const
{
  assert(index>=0 && index<4);
  return((double*)&m_d[index]);
}

inline double* Matrix4x4::operator[](int index)
{
  assert(index>=0 && index<4);
  return((double*)&m_d[index]);
}

inline void Matrix4x4::set(int row, int col, double value)
{
  assert(row>=0 && row<4 && col>=0 && col<4);
  m_d[row][col]=value;
}

#endif // MATRIX4X4_H