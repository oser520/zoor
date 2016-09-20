include_directories(../src)
include_directories(SYSTEM $ENV{GTEST_INC_DIR} $ENV{GMOCK_INC_DIR})
link_directories($ENV{GMOCK_LIB_DIR})
set(test_src
    tbasicboard.cc
    tbasictypes.cc
    tboard.cc
    tboardinfo.cc
    tfenrecord.cc
    tiofen.cc
    tpiececount.cc
    tpiecemove.cc
    tsquare.cc
    tpawnmove.cc
)
add_library(tzoor STATIC ${test_src})
target_link_libraries(tzoor zoor)
set(tzoor_libs tzoor gmock_main pthread)

# One executable for all unit tests.
add_executable(test_all ${test_src})
target_link_libraries(test_all ${tzoor_libs})

# One executable per unit test module.
foreach(srcfile ${test_src})
    get_filename_component(testname ${srcfile} NAME_WE)
    add_executable(${testname} ${srcfile})
    target_link_libraries(${testname} ${tzoor_libs})
endforeach()

file(COPY fen DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
