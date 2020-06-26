cmake_minimum_required (VERSION 2.8.11)
project (emp-ag2pc)
set(NAME "emp-ag2pc")

find_path(CMAKE_FOLDER NAMES cmake/emp-tool-config.cmake)

include(${CMAKE_FOLDER}/cmake/common.cmake)
include(${CMAKE_FOLDER}/cmake/source_of_randomness.cmake)
include(${CMAKE_FOLDER}/cmake/threading.cmake)



FIND_PACKAGE(emp-ot REQUIRED)
INCLUDE_DIRECTORIES(${EMP-OT_INCLUDE_DIRS})


find_package(Boost REQUIRED COMPONENTS program_options)
set(EMP-AG2PC_LIBRARIES ${EMP-AG2PC_LIBRARIES} ${Boost_LIBRARIES})
set(EMP-AG2PC_INCLUDE_DIRS ${EMP-AG2PC_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

install(DIRECTORY emp-ag2pc DESTINATION include)
install(DIRECTORY cmake/ DESTINATION cmake)

# Test cases
macro (add_test _name)
	add_test_with_lib(${_name} ${EMP-AG2PC_LIBRARIES})
endmacro()

add_test(aes)
add_test(sha1)
add_test(sha256)
add_test(single_execution_run)
add_test (simple_circuit)
#add_test (abit)
#add_test (amortized_2pc)

