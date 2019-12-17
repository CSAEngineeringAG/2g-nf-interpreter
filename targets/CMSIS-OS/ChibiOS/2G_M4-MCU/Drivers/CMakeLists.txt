#
# Copyright (c) 2017 The nanoFramework project contributors
# See LICENSE file in the project root for full license information.
#

# append common source files
list(APPEND COMMON_PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/MX29_FlashDriver_v2.c")
list(APPEND COMMON_PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/platform_BlockStorage_M4MCU.c")

# make var global
set(COMMON_PROJECT_SOURCES ${COMMON_PROJECT_SOURCES} CACHE INTERNAL "make global")
