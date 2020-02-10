#
# Copyright (c) 2017 The nanoFramework project contributors
# See LICENSE file in the project root for full license information.
#

cmake_minimum_required(VERSION 3.0)
ENABLE_LANGUAGE(ASM)

# add header files with common OS definitions and board definitions specific for each image
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/nanoBooter/target_board.h.in"
                "${CMAKE_CURRENT_BINARY_DIR}/nanoBooter/target_board.h" @ONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/nanoCLR/target_board.h.in"
                "${CMAKE_CURRENT_BINARY_DIR}/nanoCLR/target_board.h" @ONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/target_common.h.in"
                "${CMAKE_CURRENT_BINARY_DIR}/target_common.h" @ONLY)

set(NANOBOOTER_PROJECT_NAME "nanoBooter")
set(NANOCLR_PROJECT_NAME "nanoCLR")

find_package(BuildUtils REQUIRED)
find_package(CHIBIOS REQUIRED)
find_package(ChibiOSnfOverlay REQUIRED)
find_package(WireProtocol REQUIRED)

# packages for nanoFramework libraries
#######################################
# mandatory 
find_package(NF_CoreCLR REQUIRED)

#######################################
# optional

# ChibiOS contrib repo
if(CHIBIOS_CONTRIB_REQUIRED)
    find_package(ChibiOS-Contrib REQUIRED)
endif()

# nF feature: debugger
if(NF_FEATURE_DEBUGGER)
    find_package(NF_Debugger REQUIRED)
    find_package(NF_Diagnostics REQUIRED)
endif()

# nF feature: networking
if(USE_NETWORKING_OPTION)
    find_package(CHIBIOS_LWIP REQUIRED)
    find_package(NF_NETWORKING REQUIRED)
endif()

# nF feature: filesystem
if(USE_FILESYSTEM_OPTION)
    find_package(CHIBIOS_FATFS REQUIRED)
endif()

# security provider is mbedTLS
if(USE_SECURITY_MBEDTLS_OPTION)
    find_package(mbedTLS REQUIRED)
endif()

# SPIFFS
if(NF_FEATURE_USE_SPIFFS)
    find_package(STM32F4_CubePackage REQUIRED)
    find_package(SPIFFS REQUIRED)
endif()

#######################################

add_subdirectory("common")
add_subdirectory("Drivers")
add_subdirectory("nanoBooter")
add_subdirectory("nanoCLR")

#######################
# nanoBooter executable

add_executable(
    # executables for project, project sources
    ${NANOBOOTER_PROJECT_NAME}.elf

    "${CMAKE_CURRENT_SOURCE_DIR}/target_common.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/target_BlockStorage.c"

    # the next one is required is the target implements and it's using external memory
	"${CMAKE_CURRENT_SOURCE_DIR}/target_external_memory.c"

    # need to add configuration manager to allow get/store configuration blocks
    "${PROJECT_SOURCE_DIR}/src/HAL/nanoHAL_ConfigurationManager.c"
	"${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/nanoCLR/Windows.Devices.I2c/win_dev_i2c_native_Windows_Devices_I2C_I2cDevice.cpp"
	"${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/2G_M4-MCU/target_windows_devices_i2c_config.cpp"

    ${COMMON_PROJECT_SOURCES}
    ${NANOBOOTER_PROJECT_SOURCES}

    ${TARGET_CMSIS_COMMON_SOURCES}
    ${TARGET_CMSIS_NANOBOOTER_SOURCES}
    
    ${TARGET_CHIBIOS_COMMON_SOURCES}
    ${TARGET_CHIBIOS_NANOBOOTER_SOURCES}

    ${CHIBIOS_SOURCES}
    ${ChibiOSnfOverlay_SOURCES}

    ${WireProtocol_SOURCES}
    
    #MFUpdate
    "${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/2G_M4-MCU/nanoBooter/NanoBooterEntry.cpp"
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFupdateFlag/UpdateFlashConfig.cpp"
    
    "${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/2G_M4-MCU/MicroBooter/MicroBooter.cpp"
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdate/Storage/BlockStorageUpdate.cpp"
    #"${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/nanoCLR/targetHAL.cpp"

    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdate/Support/Compression.cpp"
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdate/Validation/CRC/CrcUpdateValidation.cpp"
)

#######################
# nanoCLR executable

add_executable(
    # executables for project, project sources
    ${NANOCLR_PROJECT_NAME}.elf

    "${CMAKE_CURRENT_SOURCE_DIR}/target_common.c"
	
    # the next one is required is the target implements and it's using external memory
	"${CMAKE_CURRENT_SOURCE_DIR}/target_external_memory.c"

    ${COMMON_PROJECT_SOURCES}
    ${NANOCLR_PROJECT_SOURCES}

    ${TARGET_CMSIS_COMMON_SOURCES}
    ${TARGET_CMSIS_NANOCLR_SOURCES}
    
    ${TARGET_CHIBIOS_COMMON_SOURCES}
    ${TARGET_CHIBIOS_NANOCLR_SOURCES}

    ${CHIBIOS_SOURCES}
    ${CHIBIOS_CONTRIB_SOURCES}
    ${ChibiOSnfOverlay_SOURCES}
    ${STM32F4_CubePackage_SOURCES}
    ${WireProtocol_SOURCES}

    # sources for nanoFramework libraries
    ${NF_CoreCLR_SOURCES}
    ${NF_Debugger_SOURCES}
    ${NF_Diagnostics_SOURCES}

    # sources for ChibiOS FatFS
    ${CHIBIOS_FATFS_SOURCES}
    
    # sources for nanoFramework Network LWIP, Sockets and TLS
    ${CHIBIOS_LWIP_SOURCES}
    ${NF_Networking_SOURCES}
    ${mbedTLS_SOURCES}

    # sources for SPIFFS
    ${SPIFFS_SOURCES}

    # sources for nanoFramework APIs
    ${TARGET_NANO_APIS_SOURCES}
    
    "${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/2G_M4-MCU/netmf_signature_compat.s"
	
    # MFUpdate: Implementations (and stubs)
    "${PROJECT_SOURCE_DIR}/src/PAL/MFUpdate/MFUpdate.cpp"
    #"${PROJECT_SOURCE_DIR}/src/PAL/MFUpdate/stubs/MFUpdate_stub.cpp"

    "${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/2G_M4-MCU/MFUpdate_config_PAL/MFUpdate_config_M4MCU.cpp"
    #"${PROJECT_SOURCE_DIR}/src/PAL/MFUpdate/stubs/Config/MFUpdate_config_stub.cpp"

    #MFUpdate Storage
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdate/Storage/BlockStorageUpdate.cpp"

    #MFUpdate Validation
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFupdate/Validation/CRC/CrcUpdateValidation.cpp"

    #MFUpdate Flag
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFupdateFlag/MicroBooterFlashUpdate.cpp"
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFupdateFlag/UpdateFlashConfig.cpp"
)

# add dependency from ChibiOS (this is required to make sure the ChibiOS repo is downloaded before the build starts)
add_dependencies(${NANOBOOTER_PROJECT_NAME}.elf ChibiOS)
add_dependencies(${NANOCLR_PROJECT_NAME}.elf ChibiOS)

# add dependencies from CHIBIOS_NETWORK_COMPONENTS (this is required to make sure that ChibiOS network components are unzip at the proper locations before the build starts)
# only required if networking is ON
if(USE_NETWORKING_OPTION)
    add_dependencies(${NANOBOOTER_PROJECT_NAME}.elf CHIBIOS_NETWORK_COMPONENTS)
    add_dependencies(${NANOCLR_PROJECT_NAME}.elf CHIBIOS_NETWORK_COMPONENTS)

    # add dependency for security provider mbedTLS
    if(USE_SECURITY_MBEDTLS_OPTION)
        add_dependencies(${NANOCLR_PROJECT_NAME}.elf mbedTLS)
    endif()
endif()

# add dependencies from CHIBIOS_FILESYSTEM_COMPONENTS (this is required to make sure that ChibiOS filesystem components are unzip at the proper locations before the build starts)
# only required if filesystem is ON
if(USE_FILESYSTEM_OPTION)
    add_dependencies(${NANOBOOTER_PROJECT_NAME}.elf CHIBIOS_FILESYSTEM_COMPONENTS)
    add_dependencies(${NANOCLR_PROJECT_NAME}.elf CHIBIOS_FILESYSTEM_COMPONENTS)
endif()

# include common directories
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${PROJECT_SOURCE_DIR}/src/CLR/Core
    ${PROJECT_SOURCE_DIR}/src/CLR/Include
    ${PROJECT_SOURCE_DIR}/src/HAL/Include
    ${PROJECT_SOURCE_DIR}/src/PAL/Include

    ${WireProtocol_INCLUDE_DIRS}
    ${CHIBIOS_INCLUDE_DIRS}
    ${ChibiOSnfOverlay_INCLUDE_DIRS}
    ${CHIBIOS_CONTRIB_INCLUDE_DIRS}
    ${STM32F4_CubePackage_INCLUDE_DIRS}

    ${TARGET_CMSIS_COMMON_INCLUDE_DIRS}
    ${TARGET_CHIBIOS_COMMON_INCLUDE_DIRS}
	
	# #includes for i2c
	# ${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/nanoCLR/Windows.Devices.I2c
	# ${PROJECT_SOURCE_DIR}/src/Windows.Devices.I2c
)

# include directories for nanoBooter
target_include_directories(${NANOBOOTER_PROJECT_NAME}.elf PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/nanoBooter
     ${CMAKE_CURRENT_SOURCE_DIR}/nanoBooter

     ${TARGET_CMSIS_NANOBOOTER_INCLUDE_DIRS}
     ${TARGET_CHIBIOS_NANOBOOTER_INCLUDE_DIRS}

    # includes for ChibiOS LwIP
    ${CHIBIOS_LWIP_INCLUDE_DIRS}

    #includes for i2c
    ${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/nanoCLR/Windows.Devices.I2c
    ${PROJECT_SOURCE_DIR}/src/Windows.Devices.I2c

    #MFUpdate
    "${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/2G_M4-MCU/nanoBooter/"
    "${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/2G_M4-MCU/MicroBooter/"

    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdate/Storage/"
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdate/Validation/CRC/"
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdateFlag/"
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdate/Support/"

    "${PROJECT_SOURCE_DIR}/InteropAssemblies/SPOT.MFUpdate/include"
    "${PROJECT_SOURCE_DIR}/src/HAL/Include/"
    #"${PROJECT_SOURCE_DIR}/build/targets/CMSIS-OS/ChibiOS/nanoCLR/"

    #"${PROJECT_SOURCE_DIR}/build/ChibiOS_Source/os/common/ext/ARM/CMSIS/Core/Include"

    "${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/nf-overlay/os/hal/ports/STM32/LLD/FSMCv1/"
    "${PROJECT_SOURCE_DIR}/targets/CMSIS-OS/ChibiOS/nf-overlay/os/hal/include/stm32_fsmc/"
)

# include directories for nanoCLR
target_include_directories(${NANOCLR_PROJECT_NAME}.elf PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/nanoCLR
     ${CMAKE_CURRENT_SOURCE_DIR}/nanoCLR

     ${TARGET_CMSIS_NANOCLR_INCLUDE_DIRS}
     ${TARGET_CHIBIOS_NANOCLR_INCLUDE_DIRS}

    # directories for nanoFramework libraries
    ${NF_CoreCLR_INCLUDE_DIRS}
    ${NF_Debugger_INCLUDE_DIRS}
    ${NF_Diagnostics_INCLUDE_DIRS}
    
    # includes for nanoFramework APIs
    ${TARGET_NANO_APIS_INCLUDES}

    # includes for ChibiOS FatFS
    ${CHIBIOS_FATFS_INCLUDE_DIRS}

    # includes for ChibiOS LwIP
    ${CHIBIOS_LWIP_INCLUDE_DIRS}

    # incudes for Networking and TLS
    ${NF_Networking_INCLUDE_DIRS}
    ${mbedTLS_INCLUDE_DIRS}

    # includes for SPIFFS
    ${SPIFFS_INCLUDE_DIRS}

    #MFUpdate
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdate/Storage/"
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdate/Validation/CRC/"
    "${PROJECT_SOURCE_DIR}/src/Drivers/MFUpdateFlag/"
)

# set compiler options
nf_set_compiler_options(${NANOBOOTER_PROJECT_NAME}.elf)
nf_set_compiler_options(${NANOCLR_PROJECT_NAME}.elf)

# mbed TLS requires a config file
if(USE_SECURITY_MBEDTLS_OPTION)
    # this seems to be only option to properly set a compiler define through the command line that needs to be a string literal
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DMBEDTLS_CONFIG_FILE=\"<${PROJECT_SOURCE_DIR}/src/PAL/COM/sockets/ssl/mbedTLS/nf_mbedtls_config.h>\"")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMBEDTLS_CONFIG_FILE=\"<${PROJECT_SOURCE_DIR}/src/PAL/COM/sockets/ssl/mbedTLS/nf_mbedtls_config.h>\"")
endif()

# set compiler definitions
nf_set_compiler_definitions(${NANOBOOTER_PROJECT_NAME}.elf)
nf_set_compiler_definitions(${NANOCLR_PROJECT_NAME}.elf)

if(USE_M4MCU_V3)
	# set linker files
	if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
		nf_set_linker_file(${NANOBOOTER_PROJECT_NAME}.elf ${CMAKE_CURRENT_SOURCE_DIR}/nanoBooter/STM32F427xI_booter-DEBUG.ld)
		nf_set_linker_file(${NANOCLR_PROJECT_NAME}.elf ${CMAKE_CURRENT_SOURCE_DIR}/nanoCLR/STM32F427xI_CLR-DEBUG.ld)
	else()
		nf_set_linker_file(${NANOBOOTER_PROJECT_NAME}.elf ${CMAKE_CURRENT_SOURCE_DIR}/nanoBooter/STM32F427xI_booter.ld)
		nf_set_linker_file(${NANOCLR_PROJECT_NAME}.elf ${CMAKE_CURRENT_SOURCE_DIR}/nanoCLR/STM32F427xI_CLR.ld)
	endif()
else()
	# set linker files
	if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
		nf_set_linker_file(${NANOBOOTER_PROJECT_NAME}.elf ${CMAKE_CURRENT_SOURCE_DIR}/nanoBooter/STM32F407xI_booter-DEBUG.ld)
		nf_set_linker_file(${NANOCLR_PROJECT_NAME}.elf ${CMAKE_CURRENT_SOURCE_DIR}/nanoCLR/STM32F407xI_CLR-DEBUG.ld)
	else()
		nf_set_linker_file(${NANOBOOTER_PROJECT_NAME}.elf ${CMAKE_CURRENT_SOURCE_DIR}/nanoBooter/STM32F407xI_booter.ld)
		nf_set_linker_file(${NANOCLR_PROJECT_NAME}.elf ${CMAKE_CURRENT_SOURCE_DIR}/nanoCLR/STM32F407xI_CLR.ld)
	endif()
endif()

# set linker options
nf_set_linker_options(${NANOBOOTER_PROJECT_NAME}.elf)
nf_set_linker_options(${NANOCLR_PROJECT_NAME}.elf)

# add other linker flags
###########################################################
# the sizes of CRT heap and ChibiOS stacks are defined here
set_property(TARGET ${NANOBOOTER_PROJECT_NAME}.elf APPEND_STRING PROPERTY LINK_FLAGS ",--defsym=__main_stack_size__=0x400,--defsym=__process_stack_size__=0x800,--defsym=__crt_heap_size__=0x2000")
set_property(TARGET ${NANOCLR_PROJECT_NAME}.elf APPEND_STRING PROPERTY LINK_FLAGS ",--defsym=__main_stack_size__=0x400,--defsym=__process_stack_size__=0x800,--defsym=__crt_heap_size__=0x60000")

# generate output files
nf_generate_build_output_files(${NANOBOOTER_PROJECT_NAME}.elf)
nf_generate_build_output_files(${NANOCLR_PROJECT_NAME}.elf)
