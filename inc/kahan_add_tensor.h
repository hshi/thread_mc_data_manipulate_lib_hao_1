#ifndef KAHAN_ADD_TENSOR_H
#define KAHAN_ADD_TENSOR_H

#include "kahan.h"
#include "tensor_all.h"

//Add equal A+=B
template <class T, int D>
void kahan_add_equal(tensor_hao::Tensor_core< KahanData<T>, D>& A, const tensor_hao::Tensor_core<T, D>& B)
{
    int L=A.size(); if( L!=B.size() ) {std::cout<<"Size if not consistent for add_equal input."<<std::endl; std::exit(1);}
    KahanData<T>* A_p = A.data(); const T* B_p = B.data();
    for(int i=0; i<L; i++) A_p[i]+=B_p[i];
}

#endif

