#include "chromosome.h"
#include <iostream>
#include <cmath>

Chromosome::Chromosome(int num_of_bit)
{
    // 随机生成一个vector, 0 1
    for (int i = 0; i < num_of_bit; ++i)
    {
        c_data.push_back(rand() % 2);
    }

    // test
    for (int i = 0; i < num_of_bit; ++i)
    {
        std::cout << c_data[i];
    }
    std::cout << std::endl;
}


std::vector<double> Chromosome::GetValue(int popsize, double leftVal, double rightVal, int num_of_x)
{
    // 二进制转换成 

    std::vector<long> x_t(num_of_x, 0);    /* x' */
    std::vector<double> x(num_of_x, 0.0);

    int num_of_bit = c_data.size() / num_of_x;

    // std::cout << num_of_bit << std::endl;

    for (int i = 0; i < num_of_bit; ++i)
    {
        for (int j = 0; j < num_of_x; ++j)
        {
            /* j = 0即为x1, j = 1 为x2 */
            int idx = (j + 1) * num_of_bit - i - 1;
            x_t[j] += c_data[idx] * pow(2, i);
        }
    }

    for (int j = 0; j < num_of_x; ++j)
    {
        x[j] = leftVal + x_t[j] * (rightVal - leftVal) / (pow(2, num_of_bit) - 1);
    }

    return x;
}