#ifndef NOISE_HPP
#define NOISE_HPP

#include "platform/types.hpp"
#include "core/math/linear.hpp"
#include "core/assert.hpp"
#include "math.h"
#include "random_plot.hpp"

using namespace StraitX;

template <size_t s_Size>
struct NoiseGenerator2D{
    RandomPlot2D<s_Size> SeedArray;

    NoiseGenerator2D(u64 seed):
        SeedArray(seed)
    {}

    float Get(size_t x, size_t y, size_t octaves){
        Assert(pow(2, octaves) < s_Size);
        float reverse = 0.0;
        float value = 0;

        float scale = 1.0f;
        for(int o = 0; o<octaves; o++){
            int pitch = 256 >> o;

            int sample_x1 = (x / pitch) * pitch;
            int sample_y1 = (y / pitch) * pitch;

            int sample_x2 = (sample_x1 + pitch) % s_Size;
            int sample_y2 = (sample_y1 + pitch) % s_Size;

            float first = Lerp(SeedArray[sample_y1][sample_x1], SeedArray[sample_y1][sample_x2], float(x-sample_x1)/pitch);
            float second = Lerp(SeedArray[sample_y2][sample_x1], SeedArray[sample_y2][sample_x2], float(x-sample_x1)/pitch);

            value += scale * Lerp(first, second, float(y-sample_y1)/pitch);

            reverse += scale;
            scale /= 2.0f;
        }
        return value / reverse;
    }

    float GetWrapped(s64 x, s64 y, size_t octaves){
        return Get(std::abs(x) % Size(), std::abs(y) % Size(), octaves);
    }

    size_t Size(){
        return s_Size;
    }
};


template <size_t s_Size>
struct NoiseGenerator3D{
    RandomPlot3D<s_Size> SeedArray;

    NoiseGenerator3D(u64 seed):
        SeedArray(seed)
    {}

    float Get(size_t x, size_t y, size_t z, size_t octaves){
        Assert(pow(2, octaves) < s_Size);
        float reverse = 0.0;
        float value = 0;

        float scale = 1.0f;
        for(int o = 0; o<octaves; o++){
            int pitch = 256 >> o;

            int sample_x1 = (x / pitch) * pitch;
            int sample_y1 = (y / pitch) * pitch;
            int sample_z1 = (z / pitch) * pitch;

            int sample_x2 = (sample_x1 + pitch) % s_Size;
            int sample_y2 = (sample_y1 + pitch) % s_Size;
            int sample_z2 = (sample_z1 + pitch) % s_Size;

            float first_z1 = Lerp(SeedArray.SeedArray[sample_z1][sample_y1][sample_x1], SeedArray.SeedArray[sample_z1][sample_y1][sample_x2], float(x-sample_x1)/pitch);
            float second_z1 = Lerp(SeedArray.SeedArray[sample_z1][sample_y2][sample_x1], SeedArray.SeedArray[sample_z1][sample_y2][sample_x2], float(x-sample_x1)/pitch);

            float bottom = Lerp(first_z1, second_z1, float(y-sample_y1)/pitch);

            float first_z2 = Lerp(SeedArray.SeedArray[sample_z2][sample_y1][sample_x1], SeedArray.SeedArray[sample_z2][sample_y1][sample_x2], float(x-sample_x1)/pitch);
            float second_z2 = Lerp(SeedArray.SeedArray[sample_z2][sample_y2][sample_x1], SeedArray.SeedArray[sample_z2][sample_y2][sample_x2], float(x-sample_x1)/pitch);
            
            float top = Lerp(first_z2, second_z2, float(y-sample_y1)/pitch);

            value += scale * Lerp(bottom, top, float(z-sample_z1)/pitch);

            reverse += scale;
            scale /= 2.0f;
        }
        return value / reverse;
    }

    float GetWrapped(s64 x, s64 y, s64 z, size_t octaves){
        return Get(std::abs(x) % Size(), std::abs(y) % Size(), std::abs(z) % Size(), octaves);
    }

    size_t Size(){
        return s_Size;
    }
};


#endif //NOISE_HPP