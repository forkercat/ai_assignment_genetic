#ifndef GENETIC_H
#define GENETIC_H

#include "chromosome.h"
#include <vector>
#include <cmath>

class Genetic
{

public:
    int g_popsize;
    int g_precision;
    double g_p_cross;
    double g_p_mutate;
    double g_leftVal;
    double g_rightVal;
    int g_iteration_time;
    double g_j;
    int g_n;

    /* 规模, 精度, 杂率, 变率, 左区间值, 右区间值 */

    Genetic();

    // Setter
    void SetPopsize(int popsize) { g_popsize = popsize; }
    void SetPrecision(int precision) { g_precision = precision; }
    void SetPcross(double p_c) { g_p_cross = p_c; }
    void SetPmutate(double p_m) { g_p_mutate = p_m; }
    void SetLeftVal(double left) { g_leftVal = left; }
    void SetRightVal(double right) { g_rightVal = right; }
    void SetIterationTime(int iteration) { g_iteration_time = iteration; }
    void SetJ(double j) { g_j = j; }
    void SetN(int n) { g_n = n; }


    void Train(int type);



private:

    int g_problem_type;  /* 问题类型 */
    
    /* 染色体数据 */
    std::vector< std::vector<Chromosome> > g_chromoData;
    std::vector< std::vector<double> > g_adaptiveData;
    std::vector< std::vector<double> > g_rel_adaptiveData;
    std::vector< std::vector<int> > g_N;       /* 繁殖量 */

    int g_num_of_bit;
    

    /* 私有方法 */
    void Reset();  /* 重置 */
    void CreatePrimitive();     /* 生成原始染色体 */
    void GetNumberOfBit();      /* 获取Bit的个数 动态 */
    void SelectStrategy(int i);      /* 选择策略(适应值, 相对适应值, 繁殖量)  i表示当前迭代次数 */


    /* 目标函数, 适应值函数 */
    double Function(const std::vector<double> param, double j, int n);
    /* 问题一 */
    double F_1(double x1, double x2, double j);
    /* 问题二 */
    double F_2(const std::vector<double> x_p, double j, int n);

    /* 获取对应问题的变量个数 */
    int GetNumberOfX();
};



#endif