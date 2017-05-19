#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>


class Chromosome
{

public:
    Chromosome(int num_of_bit);
    ~Chromosome() {};

    std::vector<int> GetData() { return c_data; }

    /* 适用于多元变量 */
    std::vector<double> GetValue(int popsize, double leftVal, double rightVal, int num_of_x);

private:
    std::vector<int> c_data;
    

};


#endif