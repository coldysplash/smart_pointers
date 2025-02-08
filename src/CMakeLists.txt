set(target_name smart_pointers)

add_library(${target_name} INTERFACE
  smart_pointers.hpp
)

include(CompileOptions)
set_compile_options(${target_name} INTERFACE)

target_include_directories(
    ${target_name}
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

add_executable(app main.cpp)

target_link_libraries(app smart_pointers)
