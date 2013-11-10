#ifndef _MATRIX_64F_
#define _MATRIX_64F_

#include "dll_macros.h"
#include <string.h>

namespace funopt {
    class Vector64f;

    class DLL_EXPORT Matrix64f {
    private:
        int nrows, ncols;
        double* data;

    public:
        // �R���X�g���N�^
        Matrix64f();
        Matrix64f(int rows, int cols);
        Matrix64f(const Matrix64f& m);

        // �f�X�g���N�^
        ~Matrix64f();

        Matrix64f& operator=(const Matrix64f& m);

        double& operator()(int i, int j);
        double  operator()(int i, int j) const;

        Vector64f operator*(const Vector64f& v);

        int rows() const;
        int cols() const;

        // ���`��������
        Vector64f solve(Vector64f& b, int decomp_type);
    };
}

#endif
