#include "mpi_fun.h"
#include "mc_data_manipulate.h"

using namespace std;
using namespace tensor_hao;

void write_mean_complex_test()
{
    ofstream out_file; 
    string filename="out.dat";
    int flag=0;
    complex<double> num(2.0,3.0), den(1.0,1.0);

    if(MPIRank()==0) out_file.open(filename, ios::out|ios::trunc);
    write_mean(num, den, out_file);
    if(MPIRank()==0) out_file.close();

    double a,b;
    ifstream in_file;
    if(MPIRank()==0)
    { 
        in_file.open(filename, ios::in);
        in_file>>a>>b;
        in_file.close();
    }

   if(abs(a-2.5)>1e-12) flag++;
   if(abs(b-0.5)>1e-12) flag++;
   if(MPIRank()==0)
   {
       if(flag==0)  cout<<"PASSED! Write_mean_complex passed the test! "<<endl;
       else         cout<<"Warning!!!! Write_mean_complex failed the test! "<<endl;
   }
   
   if(MPIRank()==0) remove( filename.c_str() ); 
}


void write_mean_complex_array_test()
{
    ofstream out_file;
    string filename="out.dat";
    int flag=0;
    KahanData< complex<double> > num[3]={complex<double>(2.0, 3.0),  complex<double>(1.0, 3.0), complex<double>(1.0, 1.0)} ;
    complex<double> den(1.0,1.0);
    double a_exact[3]={2.5, 2.0, 1.0};
    double b_exact[3]={0.5, 1.0, 0.0};

    if(MPIRank()==0) out_file.open(filename, ios::out|ios::trunc);
    write_mean(3, num, den, out_file);
    if(MPIRank()==0) out_file.close();

    double a[3],b[3];
    ifstream in_file;
    if(MPIRank()==0)
    {   
        in_file.open(filename, ios::in);
        for(int i=0; i<3; i++)
        {
           in_file>>a[i]>>b[i];
        }
        in_file.close();
    }

    for(int i=0; i<3; i++)
    {
       if(abs(a[i]-a_exact[i])>1e-12) flag++;
       if(abs(b[i]-b_exact[i])>1e-12) flag++;
    }

    if(MPIRank()==0)
    {
        if(flag==0)  cout<<"PASSED! Write_mean_complex_array passed the test! "<<endl;
        else         cout<<"Warning!!!! Write_mean_complex_array failed the test! "<<endl;
    }

    if(MPIRank()==0) remove( filename.c_str() );
}

void mc_data_manipulate_test()
{
    write_mean_complex_test();
    write_mean_complex_array_test();
}
