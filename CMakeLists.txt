cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(threadmcdatahao)

#For find module path
set(CMAKE_MODULE_PATH "${MODULE_EXTRA_PATH}" ${CMAKE_MODULE_PATH})

#For definitions
add_definitions(${COMPILER_EXTRA_DEF})

#For c++ flag
set(CMAKE_CXX_FLAGS "${COMPILER_EXTRA_FLAG}" ${CMAKE_CXX_FLAGS})

# For lapackblas library
find_package(acml)
find_package(mkl)
if(ACML_FOUND)
  add_definitions(-DUSE_ACML)
  include_directories(${acml_include_dirs})
  set(lapackblas_libraries "${acml_libraries}")
elseif(MKL_FOUND)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -m64")
  add_definitions(-DUSE_MKL)
  include_directories(${mkl_include_dirs})
  set(lapackblas_libraries "${mkl_libraries}")
endif()

if(USE_MAGMA)
  add_definitions(-DUSE_MAGMA)
  # Use standard FindCUD
  find_package(CUDA REQUIRED)
  include_directories(${CUDA_INCLUDE_DIRS})
  find_package(magma REQUIRED)
  include_directories(${magma_include_dirs})
  set(magma_libraries "${magma_libraries}" "${CUDA_LIBRARIES}" "${CUDA_CUBLAS_LIBRARIES}")
else()
  MESSAGE("-- MAGMA support was disabled.")
endif()


#For libaray hao:matrix, kahanerr, and mpi
find_package(matrixhao REQUIRED)
include_directories(${matrixhao_include_dirs})
find_package(kahanerrhao REQUIRED)
include_directories(${kahanerrhao_include_dirs})
find_package(mpihao REQUIRED)
include_directories(${mpihao_include_dirs})

include_directories(inc)

add_subdirectory(inc)

add_subdirectory(src)

add_subdirectory(test)
