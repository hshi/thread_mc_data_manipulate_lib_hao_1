#include <iostream>
#include "mpi_fun.h"

#ifdef USE_MAGMA
#include "magma.h"
#endif

#include "thread_mc_data_manipulate.h"

using namespace std;

void mc_data_manipulate_test();
void thread_mc_data_manipulate_test();

int main(int argc, char** argv)
{
    MPIInitFunnel(argc,argv);

    #ifdef USE_MAGMA
    magma_init();
    #endif

    if( MPIRank()==0 ) cout<<"\n\n\n=======Testing======="<<endl;
    mc_data_manipulate_test();
    thread_mc_data_manipulate_test();

    #ifdef USE_MAGMA
    magma_finalize();
    #endif

    MPIFinalize();

    return 0;
}
