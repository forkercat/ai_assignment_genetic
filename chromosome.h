#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>


class Chromosome
{

public:
    Chromosome(int num_of_bit);
    ~Chromosome() {};

    std::vector<int> GetData() { return c_data; }
    double GetValue(int popsize, double leftVal, double rightVal);  /* 参数: 规模, 左区间, 右区间 */

private:
    std::vector<int> c_data;
    

};


#endif