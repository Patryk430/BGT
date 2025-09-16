#include <iostream>
#include <string>
#include <random>
#include <algorithm>


main()
{  
    int SUM = 0;
    std::string INPUT;
    std::cin>>INPUT;

    for (char character : INPUT)
    {
        SUM+=character;
    };
    
    std::cout<<SUM<<" ";

    int OUTPUT [64];
    std::fill_n(OUTPUT, 64, 15);

    std::mt19937 gen(SUM);
    std::uniform_int_distribution<> distr(0, 15);

    for (int num : OUTPUT)
    {
        std::cout<<std::hex<<num-distr(gen);
    };

    return 0;
}