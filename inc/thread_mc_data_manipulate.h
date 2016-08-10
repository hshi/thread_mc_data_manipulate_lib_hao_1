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

void write_mean_error(size_t L, const std::complex<double>* num,
                      std::complex<double> den, std::complex<double> den_thread_sum, const std::string& filename);

template <int D>
void write_mean_error(const tensor_hao::Tensor_core< std::complex<double>, D >& num,
                      std::complex<double> den, std::complex<double> den_thread_sum, const std::string& filename)
{
    write_mean_error( num.size(), num.data(), den, den_thread_sum, filename );
}

void write_mean_error(size_t L, const KahanData< std::complex<double> >* num_base_array,
                      std::complex<double> den, std::complex<double> den_thread_sum, const std::string& filename);

template <int D>
void write_mean_error(const tensor_hao::Tensor_core< KahanData< std::complex<double> >,D>& num,
                      std::complex<double> den, std::complex<double> den_thread_sum, const std::string& filename)
{
    write_mean_error( num.size(), num.data(), den, den_thread_sum, filename );
}




//Write sum
void write_sum(std::complex<double> data, const std::string& filename);

void write_sum(size_t L, const std::complex<double>* data, const std::string& filename);

template <int D>
void write_sum(const tensor_hao::Tensor_core< std::complex<double>, D >& data, const std::string& filename)
{
    write_sum( data.size(), data.data(), filename );
}

void write_sum(size_t L, const KahanData< std::complex<double> >* data, const std::string& filename);

template <int D>
void write_sum(const tensor_hao::Tensor_core< KahanData< std::complex<double> >,D>& data, const std::string& filename)
{
    write_sum( data.size(), data.data(), filename );
}

#endif
