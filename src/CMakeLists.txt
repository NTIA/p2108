# Define the library/target name
set(LIB_NAME "P2108")

# Create the library. Include header files so IDEs find them.
add_library(
    ${LIB_NAME} SHARED
    "AeronauticalStatisticalModel.cpp"
    "HeightGainTerminalCorrectionModel.cpp"
    "InverseComplementaryCumulativeDistribution.cpp"
    "TerrestrialStatisticalModel.cpp"
    "${P2108_INCLUDE_DIR}/Consts.h"
    "${P2108_INCLUDE_DIR}/Errors.h"
    "${P2108_INCLUDE_DIR}/P2108.h"
)

# Add the include directory
target_include_directories(${LIB_NAME} PRIVATE ${P2108_INCLUDE_DIR})

# Set minimum C++ version to C++11
target_compile_features(${LIB_NAME} PUBLIC cxx_std_11)

# Platform-specific configurations
if (WIN32)
    set_target_properties(${LIB_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
# elseif (UNIX)
# todo
endif()

# Set some target metadata
set_target_properties(
    ${LIB_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR} # Include version in .so output filenames
    # ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    # LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    # RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    # todo more properties?
)

# Todo maybe needed for Linux compile
# include(GNUInstallDirs)

# Todo compiler-specific configuration for builds? 