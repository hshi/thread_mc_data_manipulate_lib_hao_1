set(test_exe threadmcdatatest)

file(GLOB test_srcs "*.cpp")

add_executable(${test_exe} ${test_srcs})

target_link_libraries(${test_exe} threadmcdatahao)

target_link_libraries(${test_exe} ${lib_all})

install(TARGETS ${test_exe}  DESTINATION test)
