add_executable(gbuffer WIN32 "gbuffer.cpp")
target_link_libraries(gbuffer PRIVATE donut_core donut_render donut_app donut_engine)
set_target_properties(gbuffer PROPERTIES FOLDER "Examples/GBuffer")

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /MP")
endif()