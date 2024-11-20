#if !defined(HELP_H)
#define HELP_H

#include <stdint.h>
#include <iostream>
#include <fstream>

namespace tool
{
    int32_t floor(double num);
    void print_array(int32_t *arr, int32_t n);
    void read_input(const char* filename, int32_t*& arr, int32_t& n);
} // namespace tool



#endif // HELP_H
