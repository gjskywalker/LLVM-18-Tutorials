
cmake_minimum_required(VERSION 3.10) 


find_package(LLVM REQUIRED CONFIG) 
# Needed to use support library 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -std=c++17") 

include_directories(${LLVM_INCLUDE_DIRS}) 
add_definitions(${LLVM_DEFINITIONS}) 

aux_source_directory(. DIR_HI_InstructionMoveBackward_SRCS)
add_library(HI_InstructionMoveBackward ${DIR_HI_InstructionMoveBackward_SRCS})


# set(llvm_libs "")

