#ifndef _MATRIX_64F_
#define _MATRIX_64F_

#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

#include "funopt_enum.h"
#include "dll_macros.h"
#include "matrix_enums.h"

namespace funopt {
    class Vector64f;

    class DLL_EXPORT Matrix64f {
        friend ostream& operator<<(ostream& os, const Matrix64f& m);


    private:
        int nrows, ncols;
        double* data;

    public:
        // �R���X�g���N�^
        Matrix64f();
        Matrix64f(int rows, int cols);
        Matrix64f(double* data, int rows, int cols);
        Matrix64f(const Matrix64f& m);
		Matrix64f(const Vector64f& v);

		// �P�ʍs��
		static Matrix64f eye(int n);

		// ��s��
		static Matrix64f zeros(int rows, int cols);

        // �f�X�g���N�^
        ~Matrix64f();

        Matrix64f& operator=(const Matrix64f& m);

        double& operator()(int i, int j);
        double  operator()(int i, int j) const;

		Matrix64f operator+(const Matrix64f& m) const;
		Matrix64f operator-(const Matrix64f& m) const;

        Vector64f operator*(const Vector64f& v) const;
		Matrix64f operator*(const Matrix64f& m) const;
		Matrix64f operator*(const double d) const;
		Matrix64f operator/(const double d) const;

        int rows() const;
        int cols() const;

		// �s��̓]�u
		Matrix64f trans() const;

		// �s�񎮂����߂�
		double det() const;

		// �s��m����
        double norm(MatrixNormType type = MAT_NORM_FROBENIUS) const;

		// �t�s������߂�
		Matrix64f inv() const;

        // ���`��������
		Matrix64f solve(Matrix64f& b, int decomp_type=FUNOPT_FACTOR_LU);

        // �ŗL�l�����߂�
        void eig(Matrix64f& eval, Matrix64f& evec) const;

	private:
		// LU����
		void factor_lu(Matrix64f& LU, int* order) const;

		// LU�����ɂ����`��������
		void solve_lu(Matrix64f& b, Matrix64f& x) const;

		// QR����
		void factor_qr(Matrix64f& Q, Matrix64f& R) const;

		// QR�����ɂ����`��������
		void solve_qr(Matrix64f& b, Matrix64f& x) const;
    };

    inline ostream& operator<<(ostream& os, const Matrix64f& m)
    {
        for(int i=0; i<m.rows(); i++) {
            os << (i == 0 ? "[" : " ");
            os << "[ ";
            for(int j=0; j<m.cols(); j++) {
                os << m(i, j) << (j == m.cols()-1 ? " ]" : ", ");
            }
            os << (i == m.rows()-1 ? "]" : "\n");
        }
        return os;
    }
}

#endif
