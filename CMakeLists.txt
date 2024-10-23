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
    src/microphone.c     # Microphone input handler
    src/mqtt.c           # Wi-Fi & MQTT communication
)

# Add include directories
target_include_directories(EmbeddedSystems PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Link with necessary Pico libraries
target_link_libraries(EmbeddedSystems
    pico_stdlib          # Standard Pico libraries
    hardware_adc         # For ADC input (microphone)
    hardware_pwm         # For LED control (if using PWM)
    hardware_i2c         # If I2C peripherals are used (optional)
    hardware_spi         # If SPI peripherals are used (optional)
    pico_cyw43_arch_none # For Wi-Fi communication
)

# Enable USB and UART output for debugging
pico_enable_stdio_usb(EmbeddedSystems 1)    # Enable USB output
pico_enable_stdio_uart(EmbeddedSystems 1)   # Disable UART (optional)

# Create the output files (e.g., .uf2, .bin, etc.)
pico_add_extra_outputs(EmbeddedSystems)
