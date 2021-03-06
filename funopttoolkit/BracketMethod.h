#ifndef _BRACKET_METHOD_H_
#define _BRACKET_METHOD_H_

#include "NonlinFunc.h"

#ifdef __BRACKET_EXPORT__
#define BRACKET_EXPORT __declspec(dllexport)
#else
#define BRACKET_EXPORT __declspec(dllimport)
#endif

namespace funopt {
    namespace nonlin {
        class BRACKET_EXPORT BracketMethod {
        private:
            static const double GOLD;
            static const double GLIMIT;
            static const double TINY;
            double lower, mid, upper;

        public:
            BracketMethod();
            void bracket(const double a, const double b, const func1d& func);
            virtual double get_lower() const;
            virtual double get_mid() const;
            virtual double get_upper() const;
            

        protected:
            virtual void   shift2(double &a, double &b, const double c);
            virtual void   shift3(double &a, double &b, double &c, const double d);
            virtual void   mov3(double &a, double &b, double &c, const double d, const double e, const double f);
            virtual double sgn(double d);
        };        
    }
}

#endif
