cmake_minimum_required (VERSION 2.8.11)
project (emp-ag2pc)
set(NAME "emp-ag2pc")

find_path(CMAKE_FOLDER NAMES cmake/emp-tool-config.cmake)

include(${CMAKE_FOLDER}/cmake/common.cmake)
include(${CMAKE_FOLDER}/cmake/enable_rdseed.cmake)
include(${CMAKE_FOLDER}/cmake/enable_float.cmake)

FIND_PACKAGE(emp-ot REQUIRED)
INCLUDE_DIRECTORIES(${EMP-OT_INCLUDE_DIRS})

FIND_PACKAGE(Boost REQUIRED COMPONENTS program_options)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
set(EMP-AG2PC_LIBRARIES ${EMP-AG2PC_LIBRARIES} ${Boost_LIBRARIES})
set(EMP-AG2PC_INCLUDE_DIRS ${EMP-AG2PC_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

install(DIRECTORY emp-ag2pc DESTINATION include)
install(DIRECTORY cmake/ DESTINATION cmake)

# Test cases
macro (add_test _name)
	add_test_with_lib(${_name} ${EMP-OT_LIBRARIES})
endmacro()

#add_test(aes)
#add_test(sha1)
#add_test(sha256)
#add_test(simple_circuit)
#add_test(abit)
#add_test(triple)
#add_test(amortized_2pc)
add_test(command_line_run)

TARGET_LINK_LIBRARIES(command_line_run ${Boost_LIBRARIES})

