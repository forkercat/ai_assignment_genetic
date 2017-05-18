#include "genetic.h"
#include "constant.h"
#include <iostream>


Genetic::Genetic()
{
    g_popsize = POPSIZE;
    g_precision = (int)log10(1.0 / PRECISION);
    g_precision_decimal = PRECISION;
    g_p_cross = P_CROSS;
    g_p_mutate = P_MUTATE;
    g_leftVal = LEFT_VAL;
    g_rightVal = RIGHT_VAL;
    g_iteration_time = ITERATION_TIME;

    std::cout << "初始化成功!" << std::endl;
}


void Genetic::Train()
{
    // 初始化原始值
    CreatePrimitive();



    // 迭代
    // for (int i = 0; i < g_iteration_time; ++i)
    // {

    // }
}

void Genetic::CreatePrimitive()
{
    g_chromoData.clear();

    // 群体vector
    std::vector<Chromosome> population;

    GetNumberOfBit();       /* g_num_of_bit */

    // 生成原始染色体
    for (int i = 0; i < g_popsize; ++i)
    {
        Chromosome chromo(g_num_of_bit);
        population.push_back(chromo);
    }
    g_chromoData.push_back(population);
}

void Genetic::GetNumberOfBit()
{
    // 6 x 10^6
    long total = (int)(g_rightVal - g_leftVal) * (int)pow(10, (int)g_precision);

    int num_of_bit = 0;
    while (pow(2, num_of_bit) < total)
    {
        ++num_of_bit;
    }

    // 获取需要的位数
    /* 要乘以2 因为函数是双变量的 */
    g_num_of_bit = num_of_bit * 2;
}


double Genetic::FX(double x1, double x2, double j)
{
    return 3 - pow(sin(j * x1), 2) - pow(sin(j * x2), 2);
}