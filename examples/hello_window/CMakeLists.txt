add_executable(hello_window WIN32 "hello_window.cpp")
target_link_libraries(hello_window PRIVATE donut_core donut_render donut_app donut_engine)
set_target_properties(hello_window PROPERTIES FOLDER "Examples/Hello Window")

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /MP")
endif()