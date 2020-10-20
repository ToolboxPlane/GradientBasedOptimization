project(Tests)

enable_testing()
find_package(GTest)
if (GTest_FOUND)
    include_directories(${GTEST_INCLUDE_DIR})

    set(TEST_SOURCES
            Symbolic/Add.cpp
            Symbolic/Constant.cpp
            Symbolic/Mul.cpp
            Symbolic/Operators.cpp
            Symbolic/Variable.cpp
            Optimization/SimpleGradientDescent.cpp)

    include_directories(${CMAKE_SOURCE_DIR}/Source)

    add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${TEST_SOURCES})

    target_link_libraries(${PROJECT_NAME} ${LIBS} gmock gtest pthread)

    add_test(
            NAME ${PROJECT_NAME}
            COMMAND ${PROJECT_NAME}
    )
endif()
