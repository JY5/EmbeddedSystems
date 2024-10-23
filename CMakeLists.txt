# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

# # Set the path to pico-extras
# set(PICO_EXTRAS_PATH "C:/Users/helloWorld/.pico-sdk/pico-extras")

# # Include pico-extras in the SDK by setting PICO_SDK_POST_LIST_DIRS
# set(PICO_SDK_POST_LIST_DIRS ${PICO_EXTRAS_PATH})

# # Include the Pico SDK
# include(pico_sdk_import.cmake)

project(EmbeddedSystems C CXX ASM)

# Initialize the Pico SDK
pico_sdk_init()

# Add executable
add_executable(EmbeddedSystems
    src/main.c
    src/microphone.c
    src/led.c
    src/button.c
    src/ping.c
)

# Include directories
target_include_directories(EmbeddedSystems PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_arch/include
)

# Link libraries
target_link_libraries(EmbeddedSystems
    pico_stdlib
    hardware_adc
    # pico_cyw43_arch_lwip_nosys  # Use this for NO_SYS=1 configuration
    # pico_cyw43_arch_none
    pico_cyw43_arch_lwip_poll
    pico_lwip_mqtt
    # pico_cyw43_arch_lwip_threadsafe_background
)


# Enable USB output, disable UART output (optional)
pico_enable_stdio_usb(EmbeddedSystems 1)
pico_enable_stdio_uart(EmbeddedSystems 1)

# Add extra outputs (UF2 file etc.)
pico_add_extra_outputs(EmbeddedSystems)
