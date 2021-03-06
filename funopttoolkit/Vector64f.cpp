#include <cstring>

#define __VEC64F_EXPORT__
#include "Vector64f.h"
using namespace funopt;

#include "Matrix64f.h"
#include "MTRand.h"
#include "funopt_macros.h"

Vector64f::Vector64f() :
    data(0)
{
}

Vector64f::Vector64f(int dim) :
    ndim(dim),
    data(0)
{
    data = new double[dim];
}

Vector64f::Vector64f(double* data_, int dim) :
    ndim(dim),
    data(0)
{
    data = new double[ndim];
    memcpy(data, data_, sizeof(double) * dim);
}

Vector64f::Vector64f(const Vector64f& v) :
    ndim(v.ndim),
    data(0)
{
    data = new double[ndim];
    memcpy(data, v.data, sizeof(double) * ndim);
}

Vector64f::~Vector64f()
{
    delete[] data;
}

Vector64f& Vector64f::operator=(const Vector64f& v)
{
	delete[] data;

    ndim = v.ndim;
    data = new double[ndim];
    memcpy(data, v.data, sizeof(double) * ndim);

    return *this;
}

inline double& Vector64f::operator()(int i) {
    return data[i];
}

inline double Vector64f::operator()(int i) const {
    return data[i];
}

Vector64f& Vector64f::operator-()
{
    for(int i=0; i<ndim; i++) {
        data[i] = -data[i];
    }
    return *this;
}

Vector64f& Vector64f::operator+=(const Vector64f& v)
{
    for(int i=0; i<ndim; i++) {
        data[i] += v.data[i];
    }
    return *this;
}

Vector64f& Vector64f::operator-=(const Vector64f& v)
{
    for(int i=0; i<ndim; i++) {
        data[i] -= v.data[i];
    }
    return *this;
}

Vector64f operator+(const Vector64f& v, const Vector64f& u)
{
    Vector64f w = v;
    w += u;
    return w;
}

Vector64f operator-(const Vector64f& v, const Vector64f& u)
{
    Vector64f w = v;
    w -= u;
    return w;
}

Vector64f& Vector64f::operator*=(double s)
{
    for(int i=0; i<ndim; i++) {
        data[i] *= s;
    }
    return *this;
}

Vector64f operator*(const Vector64f& v, double s)
{
    Vector64f ret = v;
    ret *= s;
    return ret;
}

Vector64f operator*(double s, const Vector64f& v)
{
	return v * s;
}

Vector64f operator*(const Vector64f& v, const Vector64f& u)
{
    massert(v.dim() == u.dim(), "dimension is different");

    const int n = v.dim();
    Vector64f ret(n);
    for(int i=0; i<n; i++) {
        ret(i) = v(i) * u(i);
    }
    return ret;
}

Vector64f& Vector64f::operator/=(double s)
{
    massert(s != 0.0, "zero division !");
    for(int i=0; i<ndim; i++) {
        data[i] /= s;
    }
    return *this;
}

Vector64f operator/(const Vector64f& v, double s)
{
    Vector64f ret = v;
    ret /= s;
    return ret;
}

Vector64f operator/(double s, const Vector64f& v)
{
    const int n = v.dim();
    Vector64f ret(n);
    for(int i=0; i<n; i++) {
        ret(i) = s / v(i);
    }
    return ret;
}


Vector64f operator/(const Vector64f& v, const Vector64f& u)
{
    massert(v.dim() == u.dim(), "dimension is different");

    const int n = v.dim();
    Vector64f ret(n);
    for(int i=0; i<n; i++) {
        ret(i) = v(i) / u(i);
    }
    return ret;
}

Vector64f Vector64f::rand(int dim)
{
    Vector64f v(dim);
    MTRand rand;
    for(int i=0; i<dim; i++) {
        v(i) = rand.randReal();
    }
    return v;
}

Vector64f Vector64f::zeros(int dim)
{
    Vector64f v(dim);
    for(int i=0; i<dim; i++) {
        v(i) = 0.0;
    }
    return v;
}

Vector64f Vector64f::ones(int dim)
{
    Vector64f v(dim);
    for(int i=0; i<dim; i++) {
        v(i) = 1.0;
    }
    return v;
}

Matrix64f Vector64f::asDiag() const
{
    Matrix64f D = Matrix64f::zeros(ndim, ndim);
    for(int i=0; i<ndim; i++) {
        D(i, i) = data[i];
    }
    return D;
}

int Vector64f::dim() const {
    return ndim;
}

double Vector64f::norm() const {
    return sqrt(dot(*this));
}

double Vector64f::dot(const Vector64f& v) const
{
    massert(ndim == v.ndim, "vector dimension is different !");

    double ret = 0.0;
    for(int i=0; i<ndim; i++) {
        ret += data[i] * v.data[i];
    }
    return ret;
}

Matrix64f Vector64f::tensor(const Vector64f& v) const
{
    int n = ndim;
    int m = v.ndim;
    Matrix64f ret(n, m);
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            ret(i, j) = data[i] * v.data[j];
        }
    }
    return ret;
}

std::ostream& operator<<(std::ostream& os, const Vector64f& v)
{
	os << "[ ";
    for(int i=0; i<v.dim(); i++) {
        os << v(i);
        if(i != v.dim()-1) os << ", ";
    }
    os << " ]";
    return os;
}

