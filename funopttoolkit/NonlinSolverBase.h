#ifndef _NONLIN_SOLVER_BASE_H_
#define _NONLIN_SOLVER_BASE_H_

#include "funopt_macros.h"

namespace funopt {
    class Vector64f;

    namespace nonlin {
        // �\���o�̎��
        enum SolverType {
            SOLVER_NELDER_SIMPLEX
        };
        
        // �֐��N���X (�p�����Ďg��)
        class func1d {
        public:
            // �֐��̕]��
            virtual double operator()(double x) = 0;

            // �֐��̔���
            virtual double df(double x) {
                massert(false, "derivative not defined");
            }
        };

        // �֐��N���X (�p�����Ďg��)
        class funcNd {
        public:
            // �֐��̕]��
            virtual double operator()(const Vector64f& x) = 0;
            // �֐��̌��z
            virtual double grad(const Vector64f& x) {
                massert(false, "gradient not defined");
            }
        };

        // �\���o���N���X
        class SolverBase {
        protected:
            funcNd* f_ptr;

        public:
            SolverBase();
            explicit SolverBase(funcNd* func_ptr);
            SolverBase(const SolverBase& sb);
            ~SolverBase();

            SolverBase& operator=(const SolverBase& sb);

            Vector64f solve(const Vector64f& x0, const int maxiter, const double tol);
            virtual void solve(const Vector64f& x0, Vector64f& x_opt, const int maxiter, const double tol) = 0;
        };
    };
};

#endif
