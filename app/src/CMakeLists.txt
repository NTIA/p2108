###########################################
## BUILD THE DRIVER
###########################################
# Driver name set in CMakeLists.txt one level above this one.
add_executable(
    ${DRIVER_NAME}
    "AeronauticalStatisticalModel.cpp"
    "CommaSeparatedIterator.cpp"
    "Driver.cpp"
    "DriverUtils.cpp"
    "HeightGainTerminalCorrectionModel.cpp"
    "Reporting.cpp"
    "ReturnCodes.cpp"
    "TerrestrialStatisticalModel.cpp"
    "${DRIVER_HEADERS}/CommaSeparatedIterator.h"
    "${DRIVER_HEADERS}/Driver.h"
    "${DRIVER_HEADERS}/ReturnCodes.h"
    "${DRIVER_HEADERS}/Structs.h"
)

# Add the include directory
target_include_directories(${DRIVER_NAME} PUBLIC "${DRIVER_HEADERS}")

# Link the library to the executable
target_link_libraries(${DRIVER_NAME} ${LIB_NAME})

# Set PropLib compiler option defaults
configure_proplib_target(${DRIVER_NAME})

# Add definitions to enable version identification inside the driver
add_compile_definitions(
    LIBRARY_VERSION="${PROJECT_VERSION}"
    DRIVER_VERSION="${DRIVER_VERSION}"
    LIBRARY_NAME="${LIB_NAME}"
    DRIVER_NAME="${DRIVER_NAME}"
)

# Set some target metadata
set_target_properties(
    ${DRIVER_NAME} PROPERTIES
    OUTPUT_NAME ${DRIVER_NAME}-${DRIVER_VERSION}-${CMAKE_SYSTEM_NAME}-
    DEBUG_POSTFIX ${ARCH_SUFFIX}
    RELEASE_POSTFIX ${ARCH_SUFFIX}
)