#
# Copyright(c) 2020 The nanoFramework project contributors
# See LICENSE file in the project root for full license information.
#

########################################################################################
# make sure that a valid path is set bellow                                            #
# this is an Interop module so this file should be placed in the CMakes module folder  #
# usually CMake\Modules                                                                #
########################################################################################

# native code directory
set(BASE_PATH_FOR_THIS_MODULE ${PROJECT_SOURCE_DIR}/InteropAssemblies/Process.Watchdog)


# set include directories
list(APPEND Process.Watchdog_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/CLR/Core)
list(APPEND Process.Watchdog_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/CLR/Include)
list(APPEND Process.Watchdog_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/HAL/Include)
list(APPEND Process.Watchdog_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/PAL/Include)
list(APPEND Process.Watchdog_INCLUDE_DIRS ${BASE_PATH_FOR_THIS_MODULE})


# source files
set(Process.Watchdog_SRCS

    Process_Watchdog.cpp


    Process_Watchdog_Process_Watchdog_Watchdog_mshl.cpp
    Process_Watchdog_Process_Watchdog_Watchdog.cpp

)

foreach(SRC_FILE ${Process.Watchdog_SRCS})

    set(Process.Watchdog_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(Process.Watchdog_SRC_FILE ${SRC_FILE}
        PATHS
	        "${BASE_PATH_FOR_THIS_MODULE}"
	        "${TARGET_BASE_LOCATION}"

	    CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${Process.Watchdog_SRC_FILE}") # debug helper
list(APPEND Process.Watchdog_SOURCES ${Process.Watchdog_SRC_FILE})
endforeach()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Process.Watchdog DEFAULT_MSG Process.Watchdog_INCLUDE_DIRS Process.Watchdog_SOURCES)
