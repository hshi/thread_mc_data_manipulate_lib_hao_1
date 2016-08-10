#ifndef READ_WRITE_FILE_H
#define READ_WRITE_FILE_H

#include <complex>
#include "tensor_all.h"

//Check sample size from a file
int file_sample_size(std::string filename, int L=1);



//Read data from file
void read_file(std::complex<double>& data, std::ifstream& file);

void read_file(int L, std::complex<double>* data, std::ifstream& file);

template<int D>
void read_file(tensor_hao::Tensor_core<std::complex<double>, D>& data, std::ifstream& file)
{
    read_file( data.size(), data.data(), file );
}



//Read data from file ( Use filename )
void read_file(std::complex<double>& data, std::string filename);

void read_file(int L, std::complex<double>* data, std::string filename);

template<int D>
void read_file(tensor_hao::Tensor_core<std::complex<double>, D>& data, std::string filename)
{
    read_file( data.size(), data.data(), filename );
}




//Write data to file
void write_file(std::complex<double> data, std::string filename);

void write_file(int L, const std::complex<double>* data, std::string filename);

template<int D>
void write_file(const tensor_hao::Tensor_core<std::complex<double>, D>& data, std::string filename)
{
    write_file( data.size(), data.data(), filename );
}

#endif
