#ifndef RANDOM_PLOT_HPP
#define RANDOM_PLOT_HPP

#include "platform/types.hpp"
#include <random>

using namespace StraitX;

template <size_t s_Size>
struct RandomPlot2D{
    float SeedArray[s_Size][s_Size];
    u64 Seed;

    RandomPlot2D(u64 seed):
        Seed(seed)
    {
        srand(Seed);

        for(auto &row: SeedArray)
            for(auto &e: row)
                e = rand() / float(RAND_MAX);
    }

    float (&operator[](size_t index))[s_Size]{
        return SeedArray[index];
    }

    float GetWrapped(int x, int y){
        return SeedArray[abs(y) % Size()][abs(x) % Size()];
    }

    size_t Size(){
        return s_Size;
    }
};

template <size_t s_Size>
struct RandomPlot3D{
    float SeedArray[s_Size][s_Size][s_Size];
    u64 Seed;

    RandomPlot3D(u64 seed):
        Seed(seed)
    {
        srand(Seed);

        for(int i = 0; i<s_Size; i++)
        for(int j = 0; j<s_Size; j++)
        for(int k = 0; k<s_Size; k++)
            SeedArray[i][j][k] = rand() / float(RAND_MAX);
    }

    float GetWrapped(int x, int y, int z){
        return SeedArray[abs(z) % Size()][abs(y) % Size()][abs(x) % Size()];
    }

    size_t Size(){
        return s_Size;
    }
};

#endif//RANDOM_PLOT_HPP