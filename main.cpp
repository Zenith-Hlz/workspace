#include <iostream>
#include <cmath>
#include <limits>

bool testExpression(double d, float f)
{
    return ((d + f) - d) == f;
}

int main()
{
    bool allTrue = true;

    // Test a range of values for d and f
    double testDoubles[] = {0.0, 1.0, -1.0, std::numeric_limits<double>::max(), std::numeric_limits<double>::min(), std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), std::nan("")};
    float testFloats[] = {0.0f, 1.0f, -1.0f, std::numeric_limits<float>::max(), std::numeric_limits<float>::min(), std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), std::nanf("")};

    for (double d : testDoubles)
    {
        for (float f : testFloats)
        {
            if (!testExpression(d, f))
            {
                allTrue = false;
                std::cout << "Expression failed for d = " << d << ", f = " << f << std::endl;
            } 
        }
    }

    if (allTrue)
    {
        std::cout << "The expression holds true for all tested double and float values." << std::endl;
    }
    else
    {
        std::cout << "The expression does not hold true for all tested double and float values." << std::endl;
    }

    return 0;
}