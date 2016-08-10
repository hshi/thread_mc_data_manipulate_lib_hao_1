#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <complex>
#include <iomanip>
#include "error_analysis.h"
#include "kahan.h"
#include "tensor_all.h"

using namespace std;
using namespace tensor_hao;

int file_line_number(string filename, int L=1)
{
    ifstream file(filename);
    string line;
    int i=0;
    while( getline(file, line) ) i++;
    file.close();
    return i/L;
}

void read_file(Tensor_hao<complex<double>, 1>& data, string filename)
{
    int L = data.size();
    double re, im;
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in num_den_error_analysis.cpp!!!"<<endl; exit(1);}
    for(int i=0; i<L; i++)
    {
        file >> re >> im;
        data(i) = complex<double>(re, im);
    }
    file.close();
}

int main(int argc, char** argv)
{
    if( argc<4 ) { cout<<"Error!!!!! Need input/output file name, example: ./num_den_error_analysis num.dat den.dat out.dat!"<<endl; exit(1); }
    string num_filename = argv[1];    //numerator filename
    string den_filename = argv[2];    //denominator filename
    string out_filename = argv[3];    //output filename

    int num_sample_size = file_line_number(num_filename); 
    int den_sample_size = file_line_number(den_filename);
    int sample_size = (num_sample_size > den_sample_size) ? den_sample_size : num_sample_size; 
    cout<<"Effective sample points is "<<sample_size<<endl;

    //Read num and den data
    Tensor_hao<complex<double>, 1> num(sample_size), den(sample_size);
    read_file(num, num_filename);
    read_file(den, den_filename);

    //Get all factors of sample_size
    vector<size_t> fact;
    get_factors(sample_size,fact);

    //Open output file
    ofstream out_file;
    out_file.open(out_filename, ios::out|ios::trunc);
    out_file<<setprecision(16)<<scientific;

    //Calculate mean and error bar
    Tensor_hao<complex<double>, 1> array(sample_size);
    complex<double> mean; double error; 
    complex<double> num_tmp, den_tmp;
    complex<double> zero(0,0);
    for (int block_size : fact)
    {
        int block_num = sample_size / block_size;

        for(int i=0; i<block_num; i++)
        {
            num_tmp = zero;
            den_tmp = zero;
            for(int j=0; j<block_size; j++)
            {
                 num_tmp += num(j+i*block_size); 
                 den_tmp += den(j+i*block_size); 
            }
            array(i) = num_tmp/den_tmp;
        }
        error_analysis(block_num, array.data(), mean, error);
        out_file<<setw(26)<<block_size<<setw(26)<<mean.real()<<setw(26)<<mean.imag()<<setw(26)<<error<<"\n";
    }

    //Close file
    out_file.close();

    return 0;
}

