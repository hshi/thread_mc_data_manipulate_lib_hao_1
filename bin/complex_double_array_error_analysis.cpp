#include <math.h>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <complex>
#include "error_analysis.h"
#include "kahan.h"
#include "tensor_all.h"
#include "read_write_file.h"

using namespace std;
using namespace tensor_hao;

int main(int argc, char** argv)
{
    if( argc<5 ) 
    { 
        cout<<"Error!!!!! Need input/output file name, array size, and block size!"<<endl; 
        cout<<"Example: ./complex_double_array_error_analysis data.dat out.dat array_size block_size!"<<endl;
        exit(1);
    }
    string data_filename = argv[1];    //data filename
    string out_filename = argv[2];    //output filename
    int L          = atoi( argv[3] ); //Each array size
    int block_size = atoi( argv[4] ); //Block size

    int sample_size = file_sample_size(data_filename, L); 
    int block_num = sample_size / block_size;
    if( ( sample_size-block_num*block_size ) !=0 ) 
    {
        cout<<"ERROR!!!!! Total sample size can not be devided by block size! "<<sample_size<<" "<<block_size<<endl;
        exit(1);
    }
    cout<<"Effective sample points is "<<sample_size<<endl;
    cout<<"Use reblock to calculate error bar, block number is "<<block_num<<endl;

    //Open files
    ifstream data_file;
    data_file.open(data_filename, ios::in);
    if ( ! data_file.is_open() ) {cout << "Error opening data file in complex_double_array_error_analysis.cpp!!! "<<data_filename<<endl; exit(1);}
 
    Tensor_hao<complex<double>, 1> data_tmp(L), data_sum(L);
    Tensor_hao<complex<double>, 1> mean(L), error(L);
    complex<double> zero(0,0);    

    //Calculate mean valule
    data_sum = zero;
    for(int i=0; i<sample_size; i++)
    {
        read_file(data_tmp, data_file); 
        data_sum += data_tmp;
    }
    mean= data_sum / complex<double>(sample_size, 0);

    //Clear the file and calculate error bar
    if( block_num>1 )
    {
        data_file.clear();
        data_file.seekg(0, ios::beg);
        for(int i=0; i<block_num; i++)
        {
            data_sum = zero; 
            for(int j=0; j<block_size; j++)
            {
                read_file(data_tmp, data_file); 
                data_sum += data_tmp; 
            }
            error += norm( data_sum/complex<double>(block_size, 0.0) - mean );
        }
        error /= complex<double>( block_num*(block_num-1), 0.0 );
        error = sqrt(error);
    }
    else
    {
        error = zero;
    }
   
    //Close files 
    data_file.close();

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

