#include <iomanip>
#include "mpi_fun.h"
#include "thread_error_analysis.h"
#include "thread_mc_data_manipulate.h"

using namespace std;
using namespace matrix_hao_lib;


//input: num and den are in each thread; den_thread_sum is sum of den about all threads
//den_thread_sum can be only in master thread.
//Calculated global average, thread averge and thread error bar.
void write_mean_error(complex<double> num, complex<double> den, complex<double> den_thread_sum, ofstream& file)
{
    complex<double> mean_global,mean; double err;
    mean_global = MPISum(num)/den_thread_sum;
    calculate_mean_err_between_thread(num/den,mean,err);
    if(MPIRank()==0)
    {
        file<<setprecision(16)<<scientific;
        file<<setw(26)<<mean_global.real()<<setw(26)<<mean_global.imag()
            <<setw(26)<<mean.real()<<setw(26)<<mean.imag()<<setw(26)<<err<<"\n";
    }
}



//Same with the last function, the difference is that we are deal with array and KahanData
//We chunk the array to save memory.
void write_mean_error(size_t L, const KahanData< complex<double> >* num_base_array,
                      complex<double> den, complex<double> den_thread_sum, ofstream& file)
{
    if(L==0) {return;}

    int M=10000;    //the chunk size 
    int N=(L-1)/M;  //number of chunk (count from 0 ~ N)
    const KahanData< complex<double> >* numbasearray = num_base_array;
    Matrix<complex<double>,1> mean_global(M), mean(M), send(M); Matrix<double,1> err(M);
    for (int i_chunk=0; i_chunk<=N; i_chunk++)
    {
        int L_chunk=M; if(i_chunk==N) L_chunk=L-M*N;   //0~N-1, passed M*N, left L-M*N

        for(int i=0; i<L_chunk; i++) send(i)=numbasearray[i].sum;

        MPISum(L_chunk,send.base_array,mean_global.base_array); mean_global/=den_thread_sum;

        send=send/den;
        calculate_mean_err_between_thread(L_chunk, send.base_array, mean.base_array, err.base_array);

        if(MPIRank()==0)
        {
           file<<setprecision(16)<<scientific;
           for(int i=0; i<L_chunk; i++)
           {
               file<<setw(26)<<mean_global(i).real()<<setw(26)<<mean_global(i).imag()
                   <<setw(26)<<mean(i).real()<<setw(26)<<mean(i).imag()<<setw(26)<<err(i)<<"\n";
           }
        }

        MPIBarrier();

        numbasearray+=L_chunk;
    }

}
