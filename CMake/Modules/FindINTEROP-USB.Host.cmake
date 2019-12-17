#
# Copyright(c) 2018 The nanoFramework project contributors
# See LICENSE file in the project root for full license information.
#


#################################################################################################
# make sure that a valid path is set bellow                                                     #
# if this is for a class library it's OK to leave it as it is                                   #
# if this is an Interop module the path has to be set where the build can find the source files #
#################################################################################################

# native code directory
set(BASE_PATH_FOR_THIS_MODULE "${PROJECT_SOURCE_DIR}/InteropAssemblies/USB.Host")


# set include directories
list(APPEND USB.Host_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/CLR/Core")
list(APPEND USB.Host_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/CLR/Include")
list(APPEND USB.Host_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/HAL/Include")
list(APPEND USB.Host_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/PAL/Include")
list(APPEND USB.Host_INCLUDE_DIRS "${BASE_PATH_FOR_THIS_MODULE}")

# source files
set(USB.Host_SRCS

    USB_Host.cpp
    USB_Host_USB_Host_Info_mshl.cpp
    USB_Host_USB_Host_Info.cpp

)

foreach(SRC_FILE ${USB.Host_SRCS})
    set(USB.Host_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(USB.Host_SRC_FILE ${SRC_FILE}
	    PATHS
	        "${BASE_PATH_FOR_THIS_MODULE}"
	        "${TARGET_BASE_LOCATION}"

	    CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${USB.Host_SRC_FILE}") # debug helper
list(APPEND USB.Host_SOURCES ${USB.Host_SRC_FILE})
endforeach()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(USB.Host DEFAULT_MSG USB.Host_INCLUDE_DIRS USB.Host_SOURCES)

