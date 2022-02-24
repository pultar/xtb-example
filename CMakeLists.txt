cmake_minimum_required(VERSION 3.21)

# set the project name
project(xtb-example)

# specify the C++ standard
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# include directory
set(PROGRAM_INCLUDES ${PROJECT_SOURCE_DIR}/../xtb/include)

# linking
link_directories(${PROJECT_SOURCE_DIR}/../xtb/build)

# add the executable
add_executable(xtb-example example.cc)

target_include_directories(xtb-example PUBLIC ${PROGRAM_INCLUDES})

target_link_libraries(xtb-example xtb)

