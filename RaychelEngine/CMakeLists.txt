cmake_minimum_required(VERSION 3.10)

project(RaychelCPU_test VERSION 0.0.1)

set(RAYCHEL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/Raychel)

set(SOURCES 
    ${RAYCHEL_SOURCE_DIR}/Engine/Objects/Interface.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Objects/sdObjects.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/Pipeline/Shading.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/Renderer.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Interface/Camera.cpp
    ${RAYCHEL_SOURCE_DIR}/Types.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/RenderTarget/ImageTarget.cpp
)

add_executable(RaychelCPU_test 
    ${PROJECT_SOURCE_DIR}/src/test/main.cpp
    ${SOURCES}
)

configure_file( ${PROJECT_SOURCE_DIR}/include/CMakeSettings.h.in
                ${PROJECT_SOURCE_DIR}/include/CMakeSettings.h
)

target_include_directories(RaychelCPU_test PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(RaychelCPU_test PRIVATE
    RaychelLogger
    tbb
    png
)

if(${USE_ASAN})
    if(MSVC)
        target_compile_options(RaychelCPU_test PUBLIC /fsanitize=address /fno-omit-frame-pointer)
        target_link_options(RaychelCPU_test PUBLIC /fsanitize=address)
    else()
        target_compile_options(RaychelCPU_test PUBLIC -fsanitize=address -fno-omit-frame-pointer)
        target_link_options(RaychelCPU_test PUBLIC -fsanitize=address)
    endif()
endif()

if(${USE_UBSAN})

    if(MSVC)
        target_compile_options(RaychelCPU_test PUBLIC /fsanitize=undefined /fno-omit-frame-pointer)
        target_link_options(RaychelCPU_test PUBLIC /fsanitize=undefined)
    else()
        target_compile_options(RaychelCPU_test PUBLIC -fsanitize=undefined -fno-sanitize-recover -fno-omit-frame-pointer)
        target_link_options(RaychelCPU_test PUBLIC -fsanitize=undefined)
    endif()

endif()

if(MSVC)
    target_compile_options(RaychelCPU_test PUBLIC /Wall /Wextra /pedantic /Wno-unknown-pragmas)
else()
    target_compile_options(RaychelCPU_test PUBLIC -Wall -Wextra -pedantic -Wno-unknown-pragmas)
endif()

target_compile_features(RaychelCPU_test PUBLIC cxx_std_17)