cmake_minimum_required(VERSION 3.6.2)
project(FMFI_rozvrh___projekt)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

set(SOURCE_FILES

        Subject.cpp
        Professor.cpp
        Schedule.cpp
        Student.cpp
        StudyProgram.cpp

        Subject_testy.cpp
        Professor_testy.cpp
        Schedule_testy.cpp
        Student_testy.cpp
        StudyProgram_testy.cpp

        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc
        )

include_directories(GoogleTest)
add_executable(FMFI_rozvrh___projekt ${SOURCE_FILES})
target_link_libraries(FMFI_rozvrh___projekt ${CMAKE_THREAD_LIBS_INIT})
