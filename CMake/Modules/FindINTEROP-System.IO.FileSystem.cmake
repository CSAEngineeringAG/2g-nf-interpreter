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
set(BASE_PATH_FOR_THIS_MODULE "${PROJECT_SOURCE_DIR}/InteropAssemblies/System.IO.FileSystem")


# set include directories
list(APPEND System.IO.FileSystem_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/CLR/Core")
list(APPEND System.IO.FileSystem_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/CLR/Include")
list(APPEND System.IO.FileSystem_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/HAL/Include")
list(APPEND System.IO.FileSystem_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/PAL/Include")
list(APPEND System.IO.FileSystem_INCLUDE_DIRS "${BASE_PATH_FOR_THIS_MODULE}")

# source files
set(System.IO.FileSystem_SRCS

    System_IO_FileSystem.cpp
    System_IO_FileSystem_System_IO_NativeFile_mshl.cpp
    System_IO_FileSystem_System_IO_NativeFile.cpp
    System_IO_FileSystem_System_IO_NativeFileStream_mshl.cpp
    System_IO_FileSystem_System_IO_NativeFileStream.cpp

)

foreach(SRC_FILE ${System.IO.FileSystem_SRCS})
    set(System.IO.FileSystem_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(System.IO.FileSystem_SRC_FILE ${SRC_FILE}
	    PATHS
	        "${BASE_PATH_FOR_THIS_MODULE}"
	        "${TARGET_BASE_LOCATION}"

	    CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${System.IO.FileSystem_SRC_FILE}") # debug helper
list(APPEND System.IO.FileSystem_SOURCES ${System.IO.FileSystem_SRC_FILE})
endforeach()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(System.IO.FileSystem DEFAULT_MSG System.IO.FileSystem_INCLUDE_DIRS System.IO.FileSystem_SOURCES)

