include_directories(${PROJECT_SORCE_DIR})

add_executable(Escape_From_Collapse
                display.c
                file_loading.c
                game.c
                main.c
                registration_system.c
              )

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()