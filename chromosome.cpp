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

    for (int i = 0; i < num_of_bit; ++i)
    {
        std::cout << c_data[i];
    }
    std::cout << std::endl;
}

double Chromosome::GetValue(int popsize, double leftVal, double rightVal)
{
    // 二进制转换成
    long x_t = 0;   /* x' */

    int num_of_bit = c_data.size();

    for (unsigned int i = 0; i < num_of_bit; ++i)
    {
        x_t += c_data[num_of_bit - i - 1] * pow(2, i);
    }

    double x = leftVal + x_t * (rightVal - leftVal) / (pow(2, num_of_bit) - 1);

    return x;
}