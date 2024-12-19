cmake_minimum_required(VERSION 3.13)

#Set the toolchain file path here

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialize environment setup
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

# Set board type to Pico W
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Include the Pico SDK
include(pico_sdk_import.cmake)

project(Trash_bin C CXX ASM)



# Initialize the Pico SDK
pico_sdk_init()

# Add your source files
add_executable(Trash_bin
    ${CMAKE_CURRENT_LIST_DIR}/Trash_bin.c
    ${CMAKE_CURRENT_LIST_DIR}/led.c
    ${CMAKE_CURRENT_LIST_DIR}/Ultrasonic.c
    ${CMAKE_CURRENT_LIST_DIR}/IRSensor.c
    ${CMAKE_CURRENT_LIST_DIR}/servomotor.c
    ${CMAKE_CURRENT_LIST_DIR}/notification.c
)

# Set program name and version
pico_set_program_name(Trash_bin "Trash_bin")
pico_set_program_version(Trash_bin "0.1")

# Configure stdio output
pico_enable_stdio_uart(Trash_bin 0)
pico_enable_stdio_usb(Trash_bin 1)

# WiFi credentials - these should be passed during build
if(NOT DEFINED WIFI_SSID)
    message(WARNING "WIFI_SSID not defined")
    set(WIFI_SSID "MIGO 1")
endif()

if(NOT DEFINED WIFI_PASSWORD)
    message(WARNING "WIFI_PASSWORD not defined")
    set(WIFI_PASSWORD "01005423000")
endif()

# Add compile definitions
target_compile_definitions(Trash_bin PRIVATE
    WIFI_SSID=\"${WIFI_SSID}\"
    WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
    CYW43_HOST_NAME=\"picow\"
    PICO_CYW43_ARCH_POLL=1
)

# Include directories
target_include_directories(Trash_bin PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}  # Your project directory
    C:/Users/Administrator/mbedtls/include    # MbedTLS headers
    ${PICO_SDK_PATH}/lib/lwip/src/include
    ${PICO_SDK_PATH}/lib/lwip/contrib/ports/unix/port/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_lwip/include
    ${PICO_SDK_PATH}/src/rp2_common/cmsis/stub/CMSIS/Device/RaspberryPi/RP2040/Include
    ${PICO_SDK_PATH}/src/rp2_common/cmsis/stub/CMSIS/Core/Include
    C:/Users/Administrator/pico-http-client/include
    C:/Users/Administrator/Trash_bin/build/pico-sdk/lib/lwip/src/include/compat/posix
)

# Link libraries
target_link_libraries(Trash_bin PRIVATE
    pico_stdlib
    pico_cyw43_arch_lwip_poll
    pico_lwip
    hardware_gpio
    hardware_adc
    hardware_pwm
)

add_compile_definitions(PICO_CYW43_ARCH_POLL)
add_compile_definitions(PICO_LWIP_UDP)
add_compile_definitions(PICO_LWIP_TCP)
add_compile_definitions(PICO_LWIP_DHCP)

# Exclude pico_mbedtls.c to avoid multiple definitions
set_source_files_properties(${PICO_SDK_PATH}/src/rp2_common/pico_mbedtls/pico_mbedtls.c PROPERTIES HEADER_FILE_ONLY TRUE)

# Generate additional outputs (.uf2, etc)
pico_add_extra_outputs(Trash_bin)