#ifndef MC_DATA_MANIPULATE_H
#define MC_DATA_MANIPULATE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <complex>
#include "kahan.h"
#include "tensor_all.h"

//Write mean
void write_mean(std::complex<double> num, std::complex<double> den, const std::string& filename);

void write_mean(size_t L, const std::complex<double>* num, std::complex<double> den, const std::string& filename);

template <int D>
void write_mean(const tensor_hao::Tensor_core<std::complex<double> >& num,
                      std::complex<double> den, const std::string& filename)
{
    write_mean( num.size(), num.data(), den, filename );
}

void write_mean(size_t L, const KahanData< std::complex<double> >* num_base_array,
                      std::complex<double> den, const std::string& filename);

template <int D>
void write_mean(const tensor_hao::Tensor_core< KahanData< std::complex<double> >,D>& num,
                      std::complex<double> den, const std::string& filename)
{
    write_mean( num.size(), num.data(), den, filename );
}

#endif
