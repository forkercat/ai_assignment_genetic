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
    // g_iteration_time = 100; /* testing */
    for (int i = 0; i < g_iteration_time; ++i)
    {
        /* 问题一用轮盘策略, 问题二用锦标赛策略 */
        SelectStrategy(i, g_problem_type);

        /* 杂交 变异 */
        Cross(i);
        Mutate(i);

        /* 从父代和所有子代中选出最优的规模大小的个体 */
        std::vector<Chromosome> best_of_all = Cull(i);

        if (i < g_iteration_time - 1)
        {
            /* 交给下一次迭代 */
            g_chromoData.push_back(best_of_all);
        }
        else
        {
            /* 最后一次了 */
            for (unsigned int j = 0; j < best_of_all.size(); ++j)
            {
                std::vector<double> param = best_of_all[j].GetValue(g_popsize, g_leftVal, g_rightVal, GetNumberOfX());
                double val = Function(param, g_j, g_n);
                std::cout << val << std::endl;
            }
        }
    }
}

void Genetic::SelectStrategy(int iter, int select_type)
{
    // 计算适应值
    std::vector<double> adaptiveData;
    double total_adaptive = 0.0;  /* 为了计算相对适应值 */
    for (int j = 0; j < g_popsize; ++j)
    {
        // 从data获取染色体并转换相应的x1 x2变量作为参数给目标函数
        std::vector<double> param = g_chromoData[iter][j].GetValue(g_popsize, g_leftVal, g_rightVal, GetNumberOfX());

        double val = Function(param, g_j, g_n);
        adaptiveData.push_back(val);

        total_adaptive += val;
        // std::cout<<"----适应值------"<<val<<std::endl;
    }
    g_adaptiveData.push_back(adaptiveData);

    if (select_type == 0)
    {
        /* 轮盘策略 */
        Wheel_Strategy(iter, total_adaptive);
    }
    else
    {
        /* 锦标赛选择法 */
        Tournament_Strategy(iter, g_percentage);
    }
    std::cout<<"繁殖池个体数: "<<g_pool[iter].size()<<std::endl;
}

void Genetic::Wheel_Strategy(int iter, double total_adaptive)
{
    // 计算相对适应值和繁殖量
    std::vector<double> rel_adaptiveData;
    std::vector<int> N_data;
    for (int j = 0; j < g_popsize; ++j)
    {
        double rel = g_adaptiveData[iter][j] / total_adaptive;
        int n = round(rel * g_popsize);
        rel_adaptiveData.push_back(rel);
        N_data.push_back(n);

        std::cout<<"个体#"<<j<<": "<<g_adaptiveData[iter][j]<<"  "<<rel <<"  "<<n<<std::endl;
    }
    g_rel_adaptiveData.push_back(rel_adaptiveData);
    g_N.push_back(N_data);

    // 形成繁殖池
    std::vector<Chromosome> poolData;
    for (int j = 0; j < g_popsize; ++j)
    {
        for (int k = 0; k < g_N[iter][j]; ++k)
        {
            /* g_N[i][j]是该个体多少个进入繁殖池 */
            Chromosome c = g_chromoData[iter][j];
            poolData.push_back(c);
        }
    }
    g_pool.push_back(poolData);
}

void Genetic::Tournament_Strategy(int iter, double percentage)
{
    int match_num = round(g_popsize * percentage);

    std::vector<Chromosome> poolData;

    // 不断随机选来比赛
    while ((int)poolData.size() < g_popsize)
    {
        std::vector<Chromosome> randomData;
        randomData = g_chromoData[iter];

        std::random_shuffle(randomData.begin(), randomData.end());

        int bestIndex = 0;
        std::vector<double>param = randomData[0].GetValue(g_popsize, g_leftVal, g_rightVal, GetNumberOfX());
        double bestVal = Function(param, g_j, g_n);

        /* 选前match_num个 */
        for (int j = 1; j < match_num; ++j)
        {
            std::vector<double>t_param = randomData[j].GetValue(g_popsize, g_leftVal, g_rightVal, GetNumberOfX());
            double val = Function(t_param, g_j, g_n);

            if (val < bestVal)
            {
                bestVal = val;
                bestIndex = j;
            }
        }

        Chromosome bestChromo = randomData[bestIndex];
        poolData.push_back(bestChromo);

        std::cout << "个体#" << poolData.size() << ": "<<bestVal << std::endl;
    }

    // 添加进繁殖池
    g_pool.push_back(poolData);
}

void Genetic::Cross(int iter)
{
    std::vector<Chromosome> crossData;
    for (unsigned int i = 1; i < g_pool[iter].size(); ++i)
    {
        /* 杂交概率 */
        int rnd = (rand() % 100) + 1; /* 1-100 */
        if (rnd < (g_p_cross * 100))
        {
            Chromosome c_1 = g_pool[iter][i - 1];
            Chromosome c_2 = g_pool[iter][i];
            std::vector<Chromosome> result = c_1.Cross(c_2);
            crossData.push_back(result[0]);
            crossData.push_back(result[1]);
        }
    }
    g_crossData.push_back(crossData);
    // std::cout<< "杂交生成新的个数: "<< crossData.size() << std::endl;
}

void Genetic::Mutate(int iter)
{
    /* 将要变异的位数 */
    int num_of_mutation = g_p_mutate * g_pool[iter].size() * g_num_of_bit;
    // std::cout<< "总共: "<< g_pool[iter].size() * g_num_of_bit<< "位"<< "  将变异: "<< num_of_mutation<< "位"<< std::endl;

    std::vector<Chromosome> mutateData;
    for (int i = 0; i < num_of_mutation; ++i)
    {
        int selected = rand() % g_pool.size();   /* 从繁殖池随机选择个体 */

        Chromosome c = g_pool[iter][selected].Mutate();

        mutateData.push_back(c);
    }
    g_mutateData.push_back(mutateData);
    std::cout<< "变异生成新的个数: "<< mutateData.size() << std::endl;
}


std::vector<Chromosome> Genetic::Cull(int iter)
{
    std::vector<Chromosome> totalData;
    std::vector<double> totalValue;

    // 父代
    std::vector<Chromosome> parentData = g_chromoData[iter];
    // 子代
    std::vector<Chromosome> childCrossData = g_crossData[iter];
    std::vector<Chromosome> childMutateData = g_mutateData[iter];

    /* 计算所有子代的适应值 */
    std::vector<double> crossVal;
    std::vector<double> mutateVal;
    for (unsigned int i = 0; i < childCrossData.size(); ++i)
    {
        std::vector<double>param = childCrossData[i].GetValue(g_popsize, g_leftVal, g_rightVal, GetNumberOfX());
        double val = Function(param, g_j, g_n);
        crossVal.push_back(val);
    }
    for (unsigned int i = 0; i < childMutateData.size(); ++i)
    {
        std::vector<double>param = childMutateData[i].GetValue(g_popsize, g_leftVal, g_rightVal, GetNumberOfX());
        double val = Function(param, g_j, g_n);
        mutateVal.push_back(val);
    }

    // 插入
    totalData.insert(totalData.end(), parentData.begin(), parentData.end());
    totalData.insert(totalData.end(), childCrossData.begin(), childCrossData.end());
    totalData.insert(totalData.end(), childMutateData.begin(), childMutateData.end());

    totalValue.insert(totalValue.end(), g_adaptiveData[iter].begin(), g_adaptiveData[iter].end());
    totalValue.insert(totalValue.end(), crossVal.begin(), crossVal.end());
    totalValue.insert(totalValue.end(), mutateVal.begin(), mutateVal.end());

    std::vector<Chromosome> best_of_all;
    /* 选取TOP popsize个 */
    for (int i = 0; i < g_popsize; ++i)
    {
        int bestIndex = 0;
        double bestVal = totalValue[0];
        for (unsigned int j = 0; j < totalData.size(); ++j)
        {
            /* 遍历挑出最小的 */
            double val = totalValue[j];
            if (val < bestVal)
            {
                bestVal = val;
                bestIndex = j;
            }
        }
        best_of_all.push_back(totalData[bestIndex]);
        /* 移除这个个体 */
        std::vector<Chromosome>::iterator iter1 = totalData.begin() + bestIndex;
        std::vector<double>::iterator iter2 = totalValue.begin() + bestIndex;
        totalData.erase(iter1);
        totalValue.erase(iter2);
    }

    return best_of_all;
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
        return F_2(param, n);
}

double Genetic::F_1(double x1, double x2, double j)
{
    return 3 - pow(sin(j * x1), 2) - pow(sin(j * x2), 2);
}

double Genetic::F_2(const std::vector<double> x_vec, int n)
{
    double ret = 1.0;
    for (int i = 0; i < n; ++i)
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