
cmake_minimum_required(VERSION 3.10) 


find_package(LLVM REQUIRED CONFIG)
find_package(Polly)
# Needed to use support library 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -std=c++17") 

include_directories(${LLVM_INCLUDE_DIRS}) 
add_definitions(${LLVM_DEFINITIONS}) 

include_directories(${Polly_INCLUDE_DIRS})
add_definitions(${Polly_DEFINITIONS})

aux_source_directory(. DIR_HI_Polly_Info_SRCS)
add_library(HI_Polly_Info ${DIR_HI_Polly_Info_SRCS})


# set(llvm_libs "")

