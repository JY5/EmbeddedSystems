# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
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

set(PICO_BOARD pico_w)

# Minimum CMake version requirement
cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK
include(pico_sdk_import.cmake)

# Name the project
project(EmbeddedSystems)

# Initialize the Pico SDK
pico_sdk_init()

# Add executable for your project
add_executable(EmbeddedSystems
    src/main.c           # Main control logic
    src/button.c         # Button handler
    src/led.c            # LED control
    # src/microphone.c     # Microphone input handler
    # src/mqtt.c           # Wi-Fi & MQTT communication
)

# Add include directories
target_include_directories(EmbeddedSystems PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    # ${CMAKE_CURRENT_LIST_DIR}/lib/paho.mqtt.c/src
)

# Link with necessary Pico libraries
target_link_libraries(EmbeddedSystems
    pico_stdlib          # Standard Pico libraries
    hardware_adc         # For ADC input (microphone)
    hardware_pwm         # For LED control
    hardware_i2c         # For I2C peripherals (if used)
    hardware_spi         # For SPI peripherals (if used)
    pico_cyw43_arch_lwip_threadsafe_background  # For Wi-Fi support
    # ${CMAKE_CURRENT_LIST_DIR}/lib/paho.mqtt.c/build/src/Release/paho-mqtt3c.lib  # Path to Paho MQTT C library
)

# Enable USB and UART output for debugging
pico_enable_stdio_usb(EmbeddedSystems 1)    # Enable USB output
pico_enable_stdio_uart(EmbeddedSystems 1)   # Enable UART output

# Create the output files (e.g., .uf2, .bin, etc.)
pico_add_extra_outputs(EmbeddedSystems)
