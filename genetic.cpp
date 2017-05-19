#include "genetic.h"
#include "constant.h"
#include <iostream>


Genetic::Genetic()
{
    g_popsize = POPSIZE;
    g_precision = PRECISION;
    g_p_cross = P_CROSS;
    g_p_mutate = P_MUTATE;
    g_leftVal = LEFT_VAL_1;
    g_rightVal = RIGHT_VAL_1;
    g_iteration_time = ITERATION_TIME;

    g_j = J;

    g_n = N_2;

    g_problem_type = 0;   /* 默认为问题一 */

    g_percentage = PERCENTAGE;

    std::cout << "初始化成功!" << std::endl;
}


void Genetic::Train(int type)
{
    DisplayInfo();   /* 打印下参数信息 */

    g_problem_type = type;

    // Reset
    Reset();

    // 初始化原始值
    CreatePrimitive();

    // 迭代
    g_iteration_time = 1; /* testing */
    for (int i = 0; i < g_iteration_time; ++i)
    {
        /* 问题一用轮盘策略, 问题二用锦标赛策略 */
        SelectStrategy(i, g_problem_type);
    }
}

void Genetic::SelectStrategy(int i, int select_type)
{
    // 计算适应值
    std::vector<double> adaptiveData;
    double total_adaptive = 0.0;  /* 为了计算相对适应值 */
    for (int j = 0; j < g_popsize; ++j)
    {
        // 从data获取染色体并转换相应的x1 x2变量作为参数给目标函数
        std::vector<double> param = g_chromoData[i][j].GetValue(g_popsize, g_leftVal, g_rightVal, GetNumberOfX());

        double val = Function(param, g_j, g_n);
        adaptiveData.push_back(val);

        total_adaptive += val;
        // std::cout<<"----适应值------"<<val<<std::endl;
    }
    g_adaptiveData.push_back(adaptiveData);

    if (select_type == 0)
    {
        /* 轮盘策略 */
        Wheel_Strategy(i, total_adaptive);
    }
    else
    {
        /* 锦标赛选择法 */
        Tournament_Strategy(i, g_percentage);
    }
    std::cout<<"繁殖池个体数: "<<g_pool[i].size()<<std::endl;
}

void Genetic::Wheel_Strategy(int i, double total_adaptive)
{
    // 计算相对适应值和繁殖量
    std::vector<double> rel_adaptiveData;
    std::vector<int> N_data;
    for (int j = 0; j < g_popsize; ++j)
    {
        double rel = g_adaptiveData[i][j] / total_adaptive;
        int n = round(rel * g_popsize);
        rel_adaptiveData.push_back(rel);
        N_data.push_back(n);

        std::cout<<"规模#"<<j<<": "<<rel <<"  "<<n<<std::endl;
    }
    g_rel_adaptiveData.push_back(rel_adaptiveData);
    g_N.push_back(N_data);

    // 形成繁殖池
    std::vector<Chromosome> poolData;
    for (int j = 0; j < g_popsize; ++j)
    {
        for (int k = 0; k < g_N[i][j]; ++k)
        {
            /* g_N[i][j]是该个体多少个进入繁殖池 */
            Chromosome c = g_chromoData[i][j];
            poolData.push_back(c);
        }
    }
    g_pool.push_back(poolData);
}

void Genetic::Tournament_Strategy(int i, double percentage)
{
    
}


void Genetic::Reset()
{
    g_chromoData.clear();
    g_adaptiveData.clear();
    g_rel_adaptiveData.clear();
    g_N.clear();
    g_pool.clear();
}

void Genetic::CreatePrimitive()
{
    // 群体vector
    std::vector<Chromosome> population;

    GetNumberOfBit();       /* g_num_of_bit */

    // 生成原始染色体
    for (int i = 0; i < g_popsize; ++i)
    {
        Chromosome chromo(g_num_of_bit);
        population.push_back(chromo);

        std::vector<double> t = chromo.GetValue(g_popsize, g_leftVal, g_rightVal, 2);
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
    /* 要乘以相应的变量数 */
    g_num_of_bit = num_of_bit * GetNumberOfX();
}


double Genetic::Function(const std::vector<double> param, double j, int n)
{
    if (g_problem_type == 0)
        return F_1(param[0], param[1], j);
    else
        return F_2(param, j, n);
}

double Genetic::F_1(double x1, double x2, double j)
{
    return 3 - pow(sin(j * x1), 2) - pow(sin(j * x2), 2);
}

double Genetic::F_2(const std::vector<double> x_vec, double j, int n)
{
    double ret = 1.0;
    for (int i = 0; i < g_n; ++i)
    {
        double sum = 0.0;
        for (int j = 1; j <= 5; ++j)  /* 5是题目固定的 */
        {
            sum += j * cos((j + 1) * x_vec[i] + j);
        }
        ret *= sum;
    }

    return ret;
}


int Genetic::GetNumberOfX()
{
    /* 问题一固定两个变量, 问题二由n来决定 */
    return (g_problem_type == 0) ? 2 : g_n;
}




void Genetic::DisplayInfo()
{
    std::cout <<  std::endl <<
    "问题: " << g_problem_type << std::endl <<
    "规模: " << g_popsize << std::endl <<
    "精度: " << g_precision << std::endl << 
    "杂交概率: " << g_p_cross << std::endl <<
    "变异概率: " << g_p_mutate << std::endl << 
    "左区间值: " << g_leftVal << std::endl <<
    "右区间值: " << g_rightVal << std::endl <<
    "迭代次数: " << g_iteration_time << std::endl <<
    "锦标比例 : " << g_percentage << std::endl <<
    "j = " << g_j << std::endl <<
    "n = " << g_n << std::endl << std::endl;
}