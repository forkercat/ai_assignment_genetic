#ifndef GENETIC_H
#define GENETIC_H


#include <vector>
#include "chromosome.h"
#include <cmath>

class Genetic
{

public:
    int g_popsize;
    int g_precision;
    double g_precision_decimal;
    double g_p_cross;
    double g_p_mutate;
    double g_leftVal;
    double g_rightVal;
    int g_iteration_time;


    /* 规模, 精度, 杂率, 变率, 左区间值, 右区间值 */

    Genetic();

    // Setter
    void SetPopsize(int popsize) { g_popsize = popsize; }
    void SetPrecision(double precision)
    { 
        g_precision = (int)log10(1.0 / precision);
        g_precision_decimal = precision;
    }
    void SetPcross(double p_c) { g_p_cross = p_c; }
    void SetPmutate(double p_m) { g_p_mutate = p_m; }
    void SetLeftVal(double left) { g_leftVal = left; }
    void SetRightVal(double right) { g_rightVal = right; }
    void SetIterationTime(int iteration) { g_iteration_time = iteration; }


    void Train();



private:
    
    /* 染色体数据 */
    std::vector< std::vector<Chromosome> > g_chromoData;

    int g_num_of_bit;
    

    /* 私有方法 */
    void CreatePrimitive();
    void GetNumberOfBit();

    /* 目标函数, 适应值函数 */
    double FX(double x1, double x2, double j);
};



#endif