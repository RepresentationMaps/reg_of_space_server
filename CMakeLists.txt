cmake_minimum_required(VERSION 3.8)
project(reg_of_space_server)

# Global flags
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/RegOfSpace.srv"
  "srv/RemoveRegOfSpace.srv"
)

# Targets
ament_auto_add_library(${PROJECT_NAME}_lib
  src/reg_of_space_server/reg_of_space_server.cpp
)

target_link_libraries(${PROJECT_NAME}_lib)

rosidl_target_interfaces(${PROJECT_NAME}_lib
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

ament_auto_add_executable(reg_of_space_server_node
  src/reg_of_space_server_node.cpp
)

install(
  DIRECTORY include/
  DESTINATION include
)

ament_export_include_directories(
  include
)

# Testing
if(BUILD_TESTING)
  ament_auto_find_test_dependencies()
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()
