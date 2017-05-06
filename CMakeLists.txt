# Force minimum CMake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Set default values for cmd arguments
if (NOT MIRAGE_PLATFORM)
	set(MIRAGE_PLATFORM "windows")
endif()

if (NOT MIRAGE_ARCH)
	set(MIRAGE_ARCH "x86")
endif()

# Create and initialize the project
project(MirageENGiNE CXX)
set(MIRAGE_ENGINE_DIR "${PROJECT_SOURCE_DIR}/MirageENGiNE_Engine")
set(MIRAGE_ENGINE_DIR_SRC "${MIRAGE_ENGINE_DIR}/src")
set(MIRAGE_ENGINE_DIR_INC "${MIRAGE_ENGINE_DIR}/inc")
set(MIRAGE_ENGINE_DIR_LIB "${MIRAGE_ENGINE_DIR}/lib/${MIRAGE_PLATFORM}/${MIRAGE_ARCH}")
set(MIRAGE_ENGINE_DIR_DTA "${MIRAGE_ENGINE_DIR}/data")
set(MIRAGE_ENGINE_DIR_BIN "${PROJECT_BINARY_DIR}/bin")

# Print all build process related variables
message(STATUS "Target platform: ${MIRAGE_PLATFORM}")
message(STATUS "Target architecture: ${MIRAGE_ARCH}")
message(STATUS "Source directory: ${MIRAGE_ENGINE_DIR_SRC}")
message(STATUS "Include directory: ${MIRAGE_ENGINE_DIR_INC}")
message(STATUS "Library directory: ${MIRAGE_ENGINE_DIR_LIB}")
message(STATUS "Data directory: ${MIRAGE_ENGINE_DIR_DTA}")
message(STATUS "Binary directory: ${MIRAGE_ENGINE_DIR_BIN}")

# Fetch all build process related files
file(GLOB_RECURSE SOURCES "${MIRAGE_ENGINE_DIR_SRC}/*.cpp" "${MIRAGE_ENGINE_DIR_SRC}/*.c")
file(GLOB_RECURSE SOURCES_ALL "${MIRAGE_ENGINE_DIR_SRC}/*.cpp" "${MIRAGE_ENGINE_DIR_SRC}/*.c" "${MIRAGE_ENGINE_DIR_SRC}/*.h" "${MIRAGE_ENGINE_DIR_SRC}/*.hpp")
file(GLOB_RECURSE INCLUDES "${MIRAGE_ENGINE_DIR_SRC}/*.h" "${MIRAGE_ENGINE_DIR_SRC}/*.hpp" "${MIRAGE_ENGINE_DIR_INC}/*.h" "${MIRAGE_ENGINE_DIR_INC}/*.hpp")
file(GLOB_RECURSE LIBRARIES "${MIRAGE_ENGINE_DIR_LIB}/*")
file(GLOB_RECURSE RESOURCES "${MIRAGE_ENGINE_DIR_DTA}/*")

# Force CXX compiler/linker for all source files
set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE CXX)

# Setup source file grouping for project files
source_group ("src" FILES ${SOURCES_ALL})

# Add to be linked executables / libraries to project
if (MIRAGE_PLATFORM STREQUAL "windows")
	add_executable(MirageENGiNE ${SOURCES_ALL})
else()
	add_executable(MirageENGiNE ${SOURCES_ALL})
endif()

# Setup compiler / linker flags
target_compile_options(MirageENGiNE PUBLIC -std=c++11)

# Find external dependencies
find_package(OpenGL REQUIRED)
set(GLFW_LIBRARY "${MIRAGE_ENGINE_DIR_LIB}/glfw3.*")

# Setup project include directoires
target_include_directories(MirageENGiNE PUBLIC "${MIRAGE_ENGINE_DIR_SRC}")
target_include_directories(MirageENGiNE PUBLIC "${MIRAGE_ENGINE_DIR_INC}")

# Setup project libraries to link against
target_link_libraries(MirageENGiNE PUBLIC
	${OPENGL_LIBRARY}
	${GLFW_LIBRARY}
)

# Setup project install configuration
install(TARGETS MirageENGiNE DESTINATION ${MIRAGE_ENGINE_DIR_BIN})
install(DIRECTORY ${MIRAGE_ENGINE_DIR_DTA} DESTINATION ${MIRAGE_ENGINE_DIR_BIN})

# Setup project package(s)
set(CPACK_PACKAGE_NAME "MirageENGiNE")
set(CPACK_MONOLITHIC_INSTALL 1)
include(CPack)