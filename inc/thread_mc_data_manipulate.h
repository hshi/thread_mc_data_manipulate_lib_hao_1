#ifndef THREAD_MC_DATA_MANIPULATE_H
#define THREAD_MC_DATA_MANIPULATE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <complex>
#include "kahan.h"
#include "tensor_all.h"

//Write mean and error for: complex<double>
void write_mean_error(std::complex<double> num, 
                      std::complex<double> den, std::complex<double> den_thread_sum, const std::string& filename);

//Write mean and error for KahanData< complex<double> >*
void write_mean_error(size_t L, const KahanData< std::complex<double> >* num_base_array,
                      std::complex<double> den, std::complex<double> den_thread_sum, const std::string& filename);

//Write mean and error for Tensor_core< KahanData<complex<double> >, D>
template <int D>
void write_mean_error(const tensor_hao::Tensor_core< KahanData< std::complex<double> >,D>& num,
                      std::complex<double> den, std::complex<double> den_thread_sum, const std::string& filename)
{
    size_t L=num.size();
    write_mean_error(L, num.data(), den, den_thread_sum, filename);
}


//Write sum
void write_sum(std::complex<double> data, const std::string& filename);

//Write sum for KahanData< complex<double> >*
void write_sum(size_t L, const KahanData< std::complex<double> >* data, const std::string& filename);

//Write sum for Tensor_core< KahanData<complex<double> >, D>
template <int D>
void write_sum(const tensor_hao::Tensor_core< KahanData< std::complex<double> >,D>& data, const std::string& filename)
{
    size_t L=data.size();
    write_sum(L, data.data(), filename);
}

#endif
