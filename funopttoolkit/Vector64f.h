#ifndef _VECTOR_64F_
#define _VECTOR_64F_

#ifdef __VEC64F_EXPORT__
#define VEC64F_DLL_EXPORT __declspec(dllexport)
#else
#define VEC64F_DLL_EXPORT __declspec(dllimport)
#endif

#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

namespace funopt {
    class Matrix64f;

    class VEC64F_DLL_EXPORT Vector64f {
        friend class Matrix64f;

    private:
        int ndim;
        double* data;

    public:
        Vector64f();
        explicit Vector64f(int dim);
        Vector64f(double* data, int dim);
        Vector64f(const Vector64f& v);
        ~Vector64f();

        Vector64f& operator=(const Vector64f& v);

        double& operator()(int i);
        double  operator()(int i) const;
        
        Vector64f operator+(const Vector64f& v) const;
        Vector64f operator-(const Vector64f& v) const;

        // �����x�N�g���̐���
        static Vector64f rand(int dim);

        int dim() const;
        double norm() const;
        double norm2() const;
        double dot(const Vector64f& v) const;
    };
}

VEC64F_DLL_EXPORT funopt::Vector64f operator*(const funopt::Vector64f& v, double s);
VEC64F_DLL_EXPORT funopt::Vector64f operator*(double s, const funopt::Vector64f& v);
VEC64F_DLL_EXPORT funopt::Vector64f operator/(const funopt::Vector64f& v, double s);

VEC64F_DLL_EXPORT ostream& operator<<(ostream& os, const funopt::Vector64f& v);

#endif
