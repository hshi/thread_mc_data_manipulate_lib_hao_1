#For num_array_den_error_analysis
add_executable(num_array_den_error_analysis num_array_den_error_analysis.cpp)

target_link_libraries(num_array_den_error_analysis threadmcdatahao)

target_link_libraries(num_array_den_error_analysis ${lib_all})

install(TARGETS num_array_den_error_analysis DESTINATION bin)

#For num_den_error_analysis
add_executable(num_den_error_analysis num_den_error_analysis.cpp)

target_link_libraries(num_den_error_analysis threadmcdatahao)

target_link_libraries(num_den_error_analysis ${lib_all})

install(TARGETS num_den_error_analysis DESTINATION bin)

#For complex_double_array_error_analysis
add_executable(complex_double_array_error_analysis complex_double_array_error_analysis.cpp)

target_link_libraries(complex_double_array_error_analysis threadmcdatahao)

target_link_libraries(complex_double_array_error_analysis ${lib_all})

install(TARGETS complex_double_array_error_analysis DESTINATION bin)
