#ifndef MC_DATA_MANIPULATE_H
#define MC_DATA_MANIPULATE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <complex>
#include "kahan.h"
#include "tensor_all.h"

//Write mean for: complex<double> on main thread
void write_mean(std::complex<double> num, std::complex<double> den, std::ofstream& file);

//Write mean for KahanData< complex<double> >* on main thread
void write_mean(size_t L, const KahanData< std::complex<double> >* num_base_array,
                      std::complex<double> den, std::ofstream& file);

//Write mean for Matrix< KahanData<complex<double> >, D> on main thread
template <int D>
void write_mean(const tensor_hao::Tensor_core< KahanData< std::complex<double> >,D>& num,
                      std::complex<double> den, std::ofstream& file)
{
    size_t L=num.size();
    write_mean(L, num.data(), den, file);
}

#endif
