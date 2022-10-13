set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR "OpenGL not found!")
endif()

find_package(OpenMP REQUIRED)
if(NOT OPENMP_FOUND)
    message(ERROR "OpenMP not found!")
endif()

find_package(CUDA REQUIRED)

set(CUDA_SEPARABLE_COMPILATION ON)
set(CUDA_PROPAGATE_HOWT_FLAGS OFF)

include(cmake/glad.cmake)
include(cmake/glfw.cmake)