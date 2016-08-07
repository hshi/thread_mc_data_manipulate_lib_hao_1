#include <iomanip>
#include "mpi_fun.h"
#include "thread_error_analysis.h"
#include "thread_mc_data_manipulate.h"

using namespace std;
using namespace tensor_hao;


//input: num and den are in each thread; den_thread_sum is sum of den about all threads
//den_thread_sum can be only in master thread.
//Calculated global average, thread averge and thread error bar.
void write_mean_error(complex<double> num, complex<double> den, complex<double> den_thread_sum, const string& filename)
{
    complex<double> mean_global,mean; double err;
    mean_global = MPISum(num)/den_thread_sum;
    calculate_mean_err_between_thread(num/den,mean,err);
    if(MPIRank()==0)
    {
        ofstream file;
        file.open(filename, ios::out|ios::app);
        file<<setprecision(16)<<scientific;
        file<<setw(26)<<mean_global.real()<<setw(26)<<mean_global.imag()
            <<setw(26)<<mean.real()<<setw(26)<<mean.imag()<<setw(26)<<err<<"\n";
        file.close();
    }
}



//Same with the last function, the difference is that we are deal with array and KahanData
//We chunk the array to save memory.
void write_mean_error(size_t L, const KahanData< complex<double> >* num_base_array,
                      complex<double> den, complex<double> den_thread_sum, const string& filename)
{
    if(L==0) {return;}

    int M=10000;    //the chunk size 
    int N=(L-1)/M;  //number of chunk (count from 0 ~ N)
    const KahanData< complex<double> >* numbasearray = num_base_array;
    Tensor_hao<complex<double>,1> mean_global(M), mean(M), send(M); Tensor_hao<double,1> err(M);

    ofstream file;
    if(MPIRank()==0)
    {
        file.open(filename, ios::out|ios::app);
        file<<setprecision(16)<<scientific;
    }
    for (int i_chunk=0; i_chunk<=N; i_chunk++)
    {
        int L_chunk=M; if(i_chunk==N) L_chunk=L-M*N;   //0~N-1, passed M*N, left L-M*N

        for(int i=0; i<L_chunk; i++) send(i)=numbasearray[i].sum;

        MPISum(L_chunk,send.data(),mean_global.data()); mean_global/=den_thread_sum;

        send=send/den;
        calculate_mean_err_between_thread(L_chunk, send.data(), mean.data(), err.data());

        if(MPIRank()==0)
        {
           for(int i=0; i<L_chunk; i++)
           {
               file<<setw(26)<<mean_global(i).real()<<setw(26)<<mean_global(i).imag()
                   <<setw(26)<<mean(i).real()<<setw(26)<<mean(i).imag()<<setw(26)<<err(i)<<"\n";
           }
        }

        MPIBarrier();

        numbasearray+=L_chunk;
    }
    if(MPIRank()==0) file.close();

}




//Input: data is in each thread
//Calculated global sum between thread
void write_sum(complex<double> data, const string& filename)
{
    complex<double> data_global = MPISum(data);
    if(MPIRank()==0)
    {
        ofstream file;
        file.open(filename, ios::out|ios::app);
        file<<setprecision(16)<<scientific;
        file<<setw(26)<<data_global.real()<<setw(26)<<data_global.imag()<<"\n";
        file.close();
    }
}

//Same with the last function, the difference is that we are deal with array and KahanData
//We chunk the array to save memory.
void write_sum(size_t L, const KahanData< complex<double> >* data, const string& filename)
{
    if(L==0) {return;}

    int M=10000;    //the chunk size 
    int N=(L-1)/M;  //number of chunk (count from 0 ~ N)
    const KahanData< complex<double> >* data_chunk = data;
    Tensor_hao<complex<double>,1> data_global(M), data_complexdouble(M);

    ofstream file;
    if(MPIRank()==0)
    {
        file.open(filename, ios::out|ios::app);
        file<<setprecision(16)<<scientific;
    }
    for (int i_chunk=0; i_chunk<=N; i_chunk++)
    {
        int L_chunk=M; if(i_chunk==N) L_chunk=L-M*N;   //0~N-1, passed M*N, left L-M*N

        for(int i=0; i<L_chunk; i++) data_complexdouble(i)=data_chunk[i].sum;

        MPISum( L_chunk, data_complexdouble.data(), data_global.data() );

        if(MPIRank()==0)
        {
           for(int i=0; i<L_chunk; i++)
           {
               file<<setw(26)<<data_global(i).real()<<setw(26)<<data_global(i).imag()<<"\n";
           }
        }

        MPIBarrier();

        data_chunk += L_chunk;
    }
    if(MPIRank()==0) file.close();
}
