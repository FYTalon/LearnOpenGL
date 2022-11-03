add_subdirectory(${CMAKE_SOURCE_DIR}/external/assimp)

set(ASSIMP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/assimp/include)

set_target_properties(assimp PROPERTIES FOLDER external)

set(ASSIMP_LIBARARIES ${ASSIMP_LIBARARIES} assimp)