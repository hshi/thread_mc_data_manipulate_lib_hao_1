set(threadmcdata_test_srcs mc_data_manipulate_test.cpp test_all.cpp)

add_executable(threadmcdatatest ${threadmcdata_test_srcs})
target_link_libraries(threadmcdatatest threadmcdatahao)
target_link_libraries(threadmcdatatest ${matrixhao_libraries})
target_link_libraries(threadmcdatatest ${kahanerrhao_libraries})
target_link_libraries(threadmcdatatest ${mpihao_libraries})
target_link_libraries(threadmcdatatest ${magma_libraries})
target_link_libraries(threadmcdatatest ${lapackblas_libraries})

install(TARGETS threadmcdatatest DESTINATION test)
