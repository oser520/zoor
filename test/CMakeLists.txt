include_directories(../src)
include_directories(SYSTEM $ENV{GTEST_INC_DIR} $ENV{GMOCK_INC_DIR})
link_directories($ENV{GMOCK_LIB_DIR})
set(TZOOR_LIBS tzoor gmock_main pthread)
set(TEST_SRC
    tbasicboard.cc
    tbasictypes.cc
    tboard.cc
    tboardinfo.cc
    tfenrecord.cc
    tiofen.cc
    tpiececount.cc
    tpiecemove.cc
    tsquare.cc
)
add_library(tzoor STATIC ${TEST_SRC})
target_link_libraries(tzoor zoor)

# One executable for all unit tests.
add_executable(test_all ${TEST_SRC})

# One executable per unit test module.
# TODO: handle this in loop
add_executable(tbasicboard tbasicboard.cc)
add_executable(tbasictypes tbasictypes.cc)
add_executable(tboard tboard.cc)
add_executable(tboardinfo tboardinfo.cc)
add_executable(tfenrecord tfenrecord.cc)
add_executable(tiofen tiofen.cc)
add_executable(tpiececount tpiececount.cc)
add_executable(tpiecemove tpiecemove.cc)
add_executable(tsquare tsquare.cc)

target_link_libraries(test_all ${TZOOR_LIBS})

# TODO: handle this in loop
target_link_libraries(tbasicboard ${TZOOR_LIBS})
target_link_libraries(tbasictypes ${TZOOR_LIBS})
target_link_libraries(tboard ${TZOOR_LIBS})
target_link_libraries(tboardinfo ${TZOOR_LIBS})
target_link_libraries(tfenrecord ${TZOOR_LIBS})
target_link_libraries(tiofen ${TZOOR_LIBS})
target_link_libraries(tpiececount ${TZOOR_LIBS})
target_link_libraries(tpiecemove ${TZOOR_LIBS})
target_link_libraries(tsquare ${TZOOR_LIBS})

file(COPY fen DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
