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
set(BASE_PATH_FOR_THIS_MODULE "${PROJECT_SOURCE_DIR}/InteropAssemblies/SPOT.MFUpdate")


# set include directories
list(APPEND SPOT.MFUpdate_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/CLR/Core")
list(APPEND SPOT.MFUpdate_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/CLR/Include")
list(APPEND SPOT.MFUpdate_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/HAL/Include")
list(APPEND SPOT.MFUpdate_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/PAL/Include")
list(APPEND SPOT.MFUpdate_INCLUDE_DIRS "${BASE_PATH_FOR_THIS_MODULE}")
list(APPEND SPOT.MFUpdate_INCLUDE_DIRS "${BASE_PATH_FOR_THIS_MODULE}/include")

# source files
set(SPOT.MFUpdate_SRCS

    SPOT_MFUpdate.cpp
    SPOT_MFUpdate_SPOT_MFUpdate_MFNativeUpdate_mshl.cpp
    SPOT_MFUpdate_SPOT_MFUpdate_MFNativeUpdate.cpp

)

foreach(SRC_FILE ${SPOT.MFUpdate_SRCS})
    set(SPOT.MFUpdate_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(SPOT.MFUpdate_SRC_FILE ${SRC_FILE}
	    PATHS
	        "${BASE_PATH_FOR_THIS_MODULE}"
	        "${TARGET_BASE_LOCATION}"

	    CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${SPOT.MFUpdate_SRC_FILE}") # debug helper
list(APPEND SPOT.MFUpdate_SOURCES ${SPOT.MFUpdate_SRC_FILE})
endforeach()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SPOT.MFUpdate DEFAULT_MSG SPOT.MFUpdate_INCLUDE_DIRS SPOT.MFUpdate_SOURCES)

