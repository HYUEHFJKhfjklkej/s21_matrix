cmake_minimum_required(VERSION 3.10)
project(CPP1_s21_matrixplus-1)
set(CMAKE_CXX_STANDARD 17)

# Добавьте s21matrix.cpp и s21matrix.h в ваш проект
# add_executable(CPP1_s21_matrixplus-1 main.cpp s21_matrix_oop.h)

find_package(GTest REQUIRED)

# Включите поддержку тестирования для вашего проекта
enable_testing()

# Используйте найденные заголовки и библиотеки Google Test
include_directories(${GTEST_INCLUDE_DIRS})

# Создайте исполняемый файл для вашего теста
add_executable(tests test.cpp s21_matrix_oop.h main.cpp)

# Свяжите исполняемый файл с библиотеками Google Test
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

# Добавьте тест в набор тестов вашего проекта
add_test(NAME tests COMMAND tests)
include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

# Create a custom target for generating code coverage report
add_custom_target(coverage
  COMMAND gcovr -r ${CMAKE_CURRENT_SOURCE_DIR} --html --html-details -o coverage.html
  DEPENDS tests
)

add_dependencies(coverage tests)
# target_compile_options(tests PRIVATE --coverage)
# target_link_libraries(tests PRIVATE --coverage)