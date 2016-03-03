#include <iomanip>
#include "mpi_fun.h"
#include "mc_data_manipulate.h"

using namespace std;
using namespace matrix_hao_lib;


//input: num and den in main thread
//Output: write num/den to file
void write_mean(complex<double> num, complex<double> den, ofstream& file)
{
    if(MPIRank()==0)
    {
        complex<double> mean = num/den;
        file<<setprecision(16)<<scientific;
        file<<setw(26)<<mean.real()<<setw(26)<<mean.imag()<<"\n";
    }
}



//Same with the last function, the difference is that we are dealing with array and KahanData
void write_mean(size_t L, const KahanData< complex<double> >* num_base_array, complex<double> den, ofstream& file)
{
    if(L==0) return;

    if(MPIRank()==0)
    {
        complex<double> mean;
        file<<setprecision(16)<<scientific;
        for (size_t i=0; i<L; i++)
        {
            mean=num_base_array[i].sum/den;
            file<<setw(26)<<mean.real()<<setw(26)<<mean.imag()<<"\n";
        }
    }

    MPIBarrier();
}
