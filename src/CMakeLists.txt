set(threadmcdata_srcs mc_data_manipulate.cpp  thread_mc_data_manipulate.cpp)

add_library(threadmcdatahao STATIC ${threadmcdata_srcs})

install(TARGETS threadmcdatahao  DESTINATION lib)
