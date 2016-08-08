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
    return i/L;
}

void read_file(Tensor_hao<complex<double>, 1>& data, ifstream& file)
{
    double re, im; 
    int L=data.size();
    for(int i=0; i<L; i++)
    {
        file >> re >> im;
        data(i) = complex<double>(re, im);
    }
}

void read_file(complex<double>& data, ifstream& file)
{
    double re, im;
    file >> re >> im;
    data = complex<double>(re, im);
}


int main(int argc, char** argv)
{
    if( argc<6 ) { cout<<"Error!!!!! Need input/output file name, array size, and block size!"<<endl; }
    string num_filename = argv[1];    //numerator filename
    string den_filename = argv[2];    //denominator filename
    string out_filename = argv[3];    //output filename
    int L          = atoi( argv[4] ); //Each array size
    int block_size = atoi( argv[5] ); //Block size

    int num_sample_size = file_line_number(num_filename, L); 
    int den_sample_size = file_line_number(den_filename);
    int sample_size = (num_sample_size > den_sample_size) ? den_sample_size : num_sample_size; 
    int block_num = sample_size / block_size;
    if( sample_size%block_size !=0 ) 
    {
        cout<<"ERROR!!!!! Total sample size can not be devided by block size! "<<sample_size<<" "<<block_size<<endl;
        exit(1);
    }
    cout<<"Effective sample points is "<<sample_size<<endl;
    cout<<"Use reblock to calculate error bar, block number is "<<block_num<<endl;

    ifstream num_file;
    num_file.open(num_filename, ios::in);
    if ( ! num_file.is_open() ) {cout << "Error opening num file in num_den_error_analysis.cpp!!!"<<endl; exit(1);}

    ifstream den_file;
    den_file.open(den_filename, ios::in);
    if ( ! den_file.is_open() ) {cout << "Error opening den file in num_den_error_analysis.cpp!!!"<<endl; exit(1);}
 
    Tensor_hao<complex<double>, 1> num_tmp(L), num_sum(L);
    complex<double> den_tmp, den_sum, zero(0,0);    
    Tensor_hao<complex<double>, 1> mean(L), error(L);

    //Calculate mean valule
    num_sum = zero; den_sum = zero;
    for(int i=0; i<sample_size; i++)
    {
        read_file(num_tmp, num_file); 
        read_file(den_tmp, den_file); 
        num_sum += num_tmp;
        den_sum += den_tmp;
    }
    mean= num_sum / den_sum;

    //Clear the file and calculate error bar
    num_file.clear();            den_file.clear();
    num_file.seekg(0, ios::beg); den_file.seekg(0, ios::beg);
    for(int i=0; i<block_num; i++)
    {
        num_sum = zero; den_sum = zero; 
        for(int j=0; j<block_size; j++)
        {
            read_file(num_tmp, num_file); 
            read_file(den_tmp, den_file);
            num_sum += num_tmp; 
            den_sum += den_tmp; 
        }
        error += norm( num_sum/den_sum - mean );
    }
    error /= complex<double>( block_num*(block_num-1), 0.0 );
    error = sqrt(error);
    
    num_file.close();
    den_file.close();

    //Write to output file
    ofstream out_file;
    out_file.open(out_filename, ios::out|ios::trunc);
    out_file<<setprecision(16)<<scientific;
    for (int i=0; i<L; i++)
    {
        out_file<<setw(26)<<mean(i).real()<<setw(26)<<mean(i).imag()<<setw(26)<<error(i).real()<<"\n";
    }
    out_file.close();

    return 0;
}

