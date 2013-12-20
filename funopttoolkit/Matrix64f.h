#ifndef _MATRIX_64F_
#define _MATRIX_64F_

#ifdef __MAT64F_EXPORT__
#define MAT64F_DLL_EXPORT __declspec(dllexport)
#else
#define MAT64F_DLL_EXPORT __declspec(dllimport)
#endif

#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>

#include "funopt_enum.h"
#include "matrix_enums.h"

namespace funopt {
    class Vector64f;

    class MAT64F_DLL_EXPORT Matrix64f {
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

		// �����s��
		static Matrix64f rand(int rows, int cols);

        // �Ίp�s��
        static Matrix64f diag(std::vector<double>& v);

        // �f�X�g���N�^
        ~Matrix64f();

        Matrix64f& operator=(const Matrix64f& m);

        double& operator()(int i, int j);
        double  operator()(int i, int j) const;
        Matrix64f& operator+=(const Matrix64f& A);
        Matrix64f& operator-=(const Matrix64f& A);
        
        int rows() const;
        int cols() const;

        Vector64f row(int i) const;
        Vector64f col(int j) const;

        // �����s��̎��o��
        Matrix64f submat(int i, int j, int rows, int cols) const;

		// �s��̓]�u
		Matrix64f trans() const;

		// �s�񎮂����߂�
		double det() const;

		// �s��m����
        double norm(MatrixNormType type = MAT_NORM_FROBENIUS) const;

		// �t�s������߂�
		Matrix64f inv() const;

        // ���`��������
		Matrix64f solve(const Matrix64f& b, SolverType solver_type=SOLVER_LU);

        // �ŗL�l�����߂�
        void eig(Matrix64f& val, Matrix64f& vec) const;

	private:
		// LU����
		void factor_lu(Matrix64f& LU, int* order) const;

		// LU�����ɂ����`��������
		void solve_lu(const Matrix64f& b, Matrix64f& x) const;

		// QR����
		void factor_qr(Matrix64f& Q, Matrix64f& R) const;

		// QR�����ɂ����`��������
		void solve_qr(const Matrix64f& b, Matrix64f& x) const;

        // CG�@�ɂ����`��������
        void solve_cg(const Matrix64f& b, Matrix64f& x) const;
    };
}

MAT64F_DLL_EXPORT std::ostream& operator<<(std::ostream& os, const funopt::Matrix64f& m);


// ���Z�q��`

MAT64F_DLL_EXPORT funopt::Matrix64f operator+(const funopt::Matrix64f& A, const funopt::Matrix64f& B);
MAT64F_DLL_EXPORT funopt::Matrix64f operator-(const funopt::Matrix64f& A, const funopt::Matrix64f& B);
MAT64F_DLL_EXPORT funopt::Matrix64f operator*(const funopt::Matrix64f& A, const funopt::Matrix64f& B);
MAT64F_DLL_EXPORT funopt::Vector64f operator*(const funopt::Matrix64f& A, const funopt::Vector64f& v);
MAT64F_DLL_EXPORT funopt::Matrix64f operator*(const funopt::Matrix64f& A, double d);
MAT64F_DLL_EXPORT funopt::Matrix64f operator*(double d, const funopt::Matrix64f& A);
MAT64F_DLL_EXPORT funopt::Matrix64f operator/(const funopt::Matrix64f& A, double d);

#endif
