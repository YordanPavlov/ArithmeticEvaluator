#include <boost/algorithm/string/replace.hpp>

#include <iostream>
#include <string>
#include <cfloat>


namespace parser
{

double safeMul(double a, double b)
{
    if(0 == a || 0 == b)
    {
        return 0;
    }

    double tempA = a;
    if( tempA < 0)
    {
        tempA *= -1;
    }

    double tempB = b;
    if( tempB < 0)
    {
        tempB *= -1;
    }

    if(tempB > DBL_MAX / tempA)
    {
        throw std::runtime_error("Too big values. Integer overflow.");
    }

    // OK. No overflow
    return a * b;
}

double safeAdd(double a, double b)
{
    if(a < 0)
    {
        if(b < 0 )
        {
            if(a < -DBL_MAX)
            {
                throw std::runtime_error("Too big values. Integer overflow.");
            }
        }
    }
    else
    {
        if(b > 0)
        {
            if(a > DBL_MAX - b)
            {
                throw std::runtime_error("Too big values. Integer overflow.");
            }
        }
    }

    // OK. No overflow
    return a + b;
}

double safeSubtract(double a, double b)
{
    if(a < 0)
    {
        if(b > 0 )
        {
            if(a < -DBL_MAX + b)
            {
                throw std::runtime_error("Too big values. Integer overflow.");
            }
        }
    }
    else
    {
        if(b < 0)
        {
            if(a > DBL_MAX + b)
            {
                throw std::runtime_error("Too big values. Integer overflow.");
            }
        }
    }

    // OK. No overflow
    return a - b;
}

} // namespace parser
