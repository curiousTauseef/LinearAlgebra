#ifndef _NELDER_SIMPLEX_H_
#define _NELDER_SIMPLEX_H_

#include "NonlinSolverBase.h"

namespace funopt {
    namespace nonlin {
        class NelderSimplex : public SolverBase {
        public:
            NelderSimplex();
            explicit NelderSimplex(funcNd* func_ptr);
            NelderSimplex(const NelderSimplex& ns);
            ~NelderSimplex();

            NelderSimplex& operator=(const NelderSimplex& ns);

            void solve(const Vector64f& x0, Vector64f& x_opt, const int maxiter, const double tol);

        private:
            // ����(�O��)��t�ɏ]���ē_���A�b�v�f�[�g
            void update(Vector64f* xs, double* fs, int ihi, double t);
        };
    }
}

#endif
