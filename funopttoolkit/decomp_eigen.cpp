#define __MAT64F_EXPORT__
#include "funopt_macros.h"
#include "Matrix64f.h"
using namespace funopt;

// �s��A���O�d�Ίp�s��T�Ƒ����ϊ�V�ɕ���
static void tridiag(const Matrix64f& A, Matrix64f& T, Matrix64f& V)
{
	massert(A.rows() == A.cols(), "matrix is not square");

	int n = A.rows();
    T = A;
    V = Matrix64f::eye(n);
	double nx = 0.0;
	for(int k=0; k<n-1; k++) {
		double a = 0.0;
		for(int i=k+1; i<n; i++) {
			a += T(i, k) * T(i, k);
		}

		double sgn = T(k+1, k) > 0.0 ? 1.0 : -1.0;
		a = -sgn * sqrt(a);
		double r = sqrt(0.5 * a * (a - T(k+1, k)));

		Matrix64f v(n, 1);
		v(k, 0) = 0.0;
		v(k+1, 0) = (T(k+1, k) - a) / (2.0 * r);

		for(int i=2; i<n-k; i++) {
			v(k+i, 0) = T(k+i, k) / (2.0 * r);
		}

		Matrix64f P = Matrix64f::eye(n) - (v * v.trans()) * 2.0;

        T = P * T * P;
        V = V * P;
	}
}

void Matrix64f::eig(Matrix64f& val, Matrix64f& vec) const
{
	massert(nrows == ncols, "Matrix is not square.");
    double tol = 1.0e-20;
    int n = nrows;

    Matrix64f Q, R, I;
    I = Matrix64f::eye(n);

    Matrix64f T, V;
	tridiag(*this, T, V);

    val = T;
    vec = I;
    for(int i=0; i<100; i++) {
        double a11 = val(n-2,n-2);
        double a12 = val(n-2,n-1);
        double a21 = val(n-1,n-2);
        double a22 = val(n-1,n-1);
        double a = a11 + a22;
        double b = a11 * a22 - a12 * a21;
        double x1 = (a + sqrt(a * a - 4.0 * b)) / 2.0;
        double x2 = (a - sqrt(a * a - 4.0 * b)) / 2.0;
        double mu = abs(x1 - a22) < abs(x2 - a22) ? x1 : x2;
        val = val - I * mu;
        val.factor_qr(Q, R);
        val = R * Q + I * mu;

        bool is_end = true;
        for(int i=0; i<n-1; i++) {
            if(abs(val(i, i+1)) > tol || abs(val(i, i+1)) > tol) {
                is_end = false;
                break;
            }
        }
        if(is_end) break;
    }

    // �O�d�Ίp�s�񂩂�ŗL�x�N�g�������߂�
    vec = Matrix64f(n, n);
    for(int j=0; j<n; j++) {
        double l = val(j, j);
        printf("l = %f\n", l);

        vec(0, j) = 1.0;
        vec(1, j) = -(T(0, 0) - l) / T(0, 1);
        for(int k=2; k<n; k++) {
            vec(k, j) = - (vec(k-2, j) * T(k-1, k-2) + vec(k-1, j) * (T(k-1, k-1) - l)) / T(k-1, k); 
        }
    }
    vec = V * vec;

    for(int j=0; j<n; j++) {
        double nv = 0.0;
        for(int i=0; i<n; i++) {
            nv += vec(i, j) * vec(i, j);
        }
        nv = sqrt(nv);
        for(int i=0; i<n; i++) {
            vec(i, j) /= nv;
        }
    }
}