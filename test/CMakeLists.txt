set(threadmcdata_test_srcs mc_data_manipulate_test.cpp test_all.cpp)

add_executable(threadmcdatatest ${threadmcdata_test_srcs})
target_link_libraries(threadmcdatatest threadmcdatahao)
target_link_libraries(threadmcdatatest ${lib_all})

install(TARGETS threadmcdatatest DESTINATION test)
