add_executable(the_aftermath WIN32 
    "the_aftermath.cpp" 
    "pass.cpp"
    "pass.h"
)
target_link_libraries(the_aftermath PRIVATE donut_core donut_render donut_app donut_engine)
set_target_properties(the_aftermath PROPERTIES FOLDER "Game/The Aftermath")

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /MP")
endif()