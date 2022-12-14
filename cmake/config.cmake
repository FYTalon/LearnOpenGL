if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose build type: Debug  Release" FORCE)
endif ()

macro(make_project_)
    if (NOT DEFINED PROJECT)
        get_filename_component(PROJECT ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    endif ()

    project(${PROJECT} CXX)

    if(MSVC)
        # Ignore 4055 for glad
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /IGNORE:4055")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++14 -w -fopenmp ")
        
    endif ()

    if(MSVC)
        add_definitions(
            -D_USE_MATH_DEFINES
            )
    endif()
    
    if (NOT DEFINED HEADERS)
        file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
    endif ()

    if (NOT DEFINED SOURCES)
        file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
        file(GLOB_RECURSE CSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
    endif ()

    source_group("Header Files" FILES ${HEADERS})
    source_group("Source Files" FILES ${SOURCES} ${CSOURCES})
endmacro ()

macro(make_executable)
    make_project_()
    
    add_executable(${PROJECT} ${HEADERS} ${SOURCES})

    add_definitions(${GLFW_DEFINITIONS})
    
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/bundle/${PROJECT}")
    install(
        TARGETS ${PROJECT}
        DESTINATION ${CMAKE_INSTALL_PREFIX})
endmacro()

macro(make_library)
    make_project_()
    add_library(${PROJECT} STATIC ${HEADERS} ${SOURCES})
    target_include_directories(${PROJECT} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

    set_target_properties(${PROJECT} PROPERTIES FOLDER Libraries)

    include_directories(
        ${GLM_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR})

    if (NOT SOURCES)
        set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)
    endif ()
endmacro()

function(add_all_subdirectories)
    file(GLOB CHILDREN RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

    foreach(CHILD ${CHILDREN})
        if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CHILD})
            add_subdirectory(${CHILD})
        endif ()
    endforeach ()
endfunction()


macro(make_cuda_project_)
    if (NOT DEFINED PROJECT)
        get_filename_component(PROJECT ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    endif ()

    project(${PROJECT} CXX)

    if(MSVC)
        # Ignore 4055 for glad
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /IGNORE:4055")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++14 -w -fopenmp ")
        
    endif ()

    if(MSVC)
        add_definitions(
            -D_USE_MATH_DEFINES
            )
    endif()
    
    if (NOT DEFINED HEADERS)
        file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
    endif ()

    if (NOT DEFINED SOURCES)
        file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
        file(GLOB_RECURSE CSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
    endif ()

    if (NOT DEFINED CUDASOURCES)
        file(GLOB_RECURSE CUDASOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cu)
    endif ()

    source_group("Header Files" FILES ${HEADERS})
    source_group("Source Files" FILES ${SOURCES} ${CSOURCES})
    source_group("CUDA FILEs" FILES ${CUDASOURCES})

endmacro ()


macro(make_cuda_executable)
    make_cuda_project_()
    
    cuda_add_executable(${PROJECT} ${HEADERS}
                                      ${SOURCES}
                                      ${CUDASOURCES})

    #add_executable(${PROJECT} ${HEADERS} ${SOURCES})

    add_definitions(${GLFW_DEFINITIONS})
    
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/bundle/${PROJECT}")
    install(
        TARGETS ${PROJECT}
        DESTINATION ${CMAKE_INSTALL_PREFIX})
endmacro()