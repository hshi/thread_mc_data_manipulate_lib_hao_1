#include "mpi_fun.h"
#include "thread_mc_data_manipulate.h"

using namespace std;
using namespace tensor_hao;

void write_sum_complex_test()
{
    string filename="out.dat";
    int flag=0;

    //Set input and exact values
    int rank = MPIRank();
    int size = MPISize();
    complex<double> data( rank, 2.0*rank );
    complex<double> exact(0,0);
    for(int i=0; i<size; i++) exact += complex<double>(i, 2.0*i); 

    write_sum(data, filename);

    if(MPIRank()==0)
    {
        double a,b;
        ifstream in_file;
        in_file.open(filename, ios::in);
        in_file>>a>>b;
        in_file.close();

        if(abs( a-exact.real() )>1e-12) flag++;
        if(abs( b-exact.imag() )>1e-12) flag++;
        if(flag==0)  cout<<"PASSED! Write_sum_complex passed the test! "<<endl;
        else         cout<<"Warning!!!! Write_sum_complex failed the test! "<<endl;

        remove( filename.c_str() );
   }
}

void write_sum_complex_array_test()
{
    string filename="out.dat";
    int flag=0;

    complex<double> data[3]={ complex<double>(2.0, 3.0),  complex<double>(1.0, 3.0), complex<double>(1.0, 1.0) } ;
    double size = MPISize();
    complex<double> exact[3] = { size*data[0], size*data[1], size*data[2] };

    write_sum(3, data, filename);

    if(MPIRank()==0)
    {
        complex<double> sum[3];
        double a, b;
        ifstream in_file;
        in_file.open(filename, ios::in);
        for(int i=0; i<3; i++)
        {
           in_file>>a>>b;
           sum[i] = complex<double>(a,b);
        }
        in_file.close();

        for(int i=0; i<3; i++)
        {
           if( abs( sum[i]-exact[i] ) > 1e-12 ) flag++;
        }

        if(flag==0)  cout<<"PASSED! Write_sum_complex_array passed the test! "<<endl;
        else         cout<<"Warning!!!! Write_sum_complex_array failed the test! "<<endl;

        remove( filename.c_str() );
    }

}


void write_sum_kahan_complex_array_test()
{
    string filename="out.dat";
    int flag=0;

    KahanData< complex<double> > data[3]={ complex<double>(2.0, 3.0),  complex<double>(1.0, 3.0), complex<double>(1.0, 1.0) } ;
    double size = MPISize();
    complex<double> exact[3] = { size*(data[0].sum), size*(data[1].sum), size*(data[2].sum) };

    write_sum(3, data, filename);

    if(MPIRank()==0)
    {
        complex<double> sum[3];
        double a, b;
        ifstream in_file;
        in_file.open(filename, ios::in);
        for(int i=0; i<3; i++)
        {
           in_file>>a>>b;
           sum[i] = complex<double>(a,b);
        }
        in_file.close();

        for(int i=0; i<3; i++)
        {
           if( abs( sum[i]-exact[i] ) > 1e-12 ) flag++;
        }

        if(flag==0)  cout<<"PASSED! Write_sum_kahan_complex_array passed the test! "<<endl;
        else         cout<<"Warning!!!! Write_sum_kahan_complex_array failed the test! "<<endl;

        remove( filename.c_str() );
    }

}


void thread_mc_data_manipulate_test()
{
    write_sum_complex_test();
    write_sum_complex_array_test();
    write_sum_kahan_complex_array_test();
}
