cmake_minimum_required (VERSION 2.6)

set (MULT_SOURCES dense_mia_mult_test.cpp)
add_executable(DenseMIAMultTests ${MULT_SOURCES})
set (SOLVE_SOURCES dense_mia_solve_test.cpp)
add_executable(DenseMIASolveTests ${SOLVE_SOURCES})
set (ADD_SUB_SOURCES dense_mia_add_subtract_test.cpp)
add_executable(DenseMIAAddSubtractTests ${ADD_SUB_SOURCES})
set (FUNCTION_SOURCES dense_mia_functions.cpp)
add_executable(DenseMIAFunctionTests ${FUNCTION_SOURCES})
if(NOT MIA_USE_HEADER_ONLY_TESTS)
	target_link_libraries(DenseMIAMultTests ${Boost_LIBRARIES})
	target_link_libraries(DenseMIASolveTests ${Boost_LIBRARIES})
	target_link_libraries(DenseMIAAddSubtractTests ${Boost_LIBRARIES})
	target_link_libraries(DenseMIAFunctionTests ${Boost_LIBRARIES})
endif()
ADD_TEST(DenseMIAMultTests ${CMAKE_CURRENT_BINARY_DIR}/DenseMIAMultTests)
ADD_TEST(DenseMIASolveTests ${CMAKE_CURRENT_BINARY_DIR}/DenseMIASolveTests)
ADD_TEST(DenseMIAAddSubtractTests ${CMAKE_CURRENT_BINARY_DIR}/DenseMIAAddSubtractTests)
ADD_TEST(DenseMIAFunctionTests ${CMAKE_CURRENT_BINARY_DIR}/DenseMIAFunctionTests)


