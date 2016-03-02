#ifndef THREAD_MC_DATA_MANIPULATE_H
#define THREAD_MC_DATA_MANIPULATE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <complex>
#include "kahan.h"
#include "matrix_all.h"

//Write mean and error for: complex<double>
void write_mean_error(std::complex<double> num, 
                      std::complex<double> den, std::complex<double> den_thread_sum, std::ofstream& file);

//Write mean and error for KahanData< complex<double> >*
void write_mean_error(size_t L, const KahanData< std::complex<double> >* num_base_array,
                      std::complex<double> den, std::complex<double> den_thread_sum, std::ofstream& file);

//Write mean and error for Matrix< KahanData<complex<double> >, D>
template <int D>
void write_mean_error(const matrix_hao_lib::Matrix< KahanData< std::complex<double> >,D>& num,
                      std::complex<double> den, std::complex<double> den_thread_sum, std::ofstream& file)
{
    size_t L=num.L_f();
    write_mean_error(L, num.base_array, den, den_thread_sum, file);
}

#endif
