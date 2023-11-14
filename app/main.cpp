#include <fstream>
#include <iostream>
#include "CrumpleTree.hpp"

int main()
{
    CrumpleTree<unsigned, unsigned> k1;
    k1.insert(1,1);
    const CrumpleTree<unsigned, unsigned> k1Cpy;
    std::cout << k1Cpy.find(1) << std::endl; 
    return 0;
}

