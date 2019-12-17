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
set(BASE_PATH_FOR_THIS_MODULE "${PROJECT_SOURCE_DIR}/InteropAssemblies/Oberon.NaCl")


# set include directories
list(APPEND Oberon.NaCl_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/CLR/Core")
list(APPEND Oberon.NaCl_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/CLR/Include")
list(APPEND Oberon.NaCl_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/HAL/Include")
list(APPEND Oberon.NaCl_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/PAL/Include")
list(APPEND Oberon.NaCl_INCLUDE_DIRS "${BASE_PATH_FOR_THIS_MODULE}")
list(APPEND Oberon.NaCl_INCLUDE_DIRS "${BASE_PATH_FOR_THIS_MODULE}/include")

# source files
set(Oberon.NaCl_SRCS

    Oberon_NaCl.cpp
    Oberon_NaCl_Oberon_NaCl_Native_mshl.cpp
    Oberon_NaCl_Oberon_NaCl_Native.cpp
	interop.c
	bigint.c
	#from curve25519
	base.c
	smult.c
	#from ed25519
	ed25519.c
	fe25519.c
	ge25519.c
	sc25519.c
	sign_keywrapper.c
	#from hsalsa20
	core.c
	#from poly1305
	auth.c
	verify.c
	#from sha512
	blocks.c
	hash.c
	#from xsalsa20
	stream.c
	xor.c
	#from xsalsa20poly1305
	box.c
)
# from chacha20
set(Oberon.NaCl_chacha20_SRCS
	core.c
	stream.c
	xor.c
)
#from curve25519xsalsa20poly1305
set(Oberon.NaCl_curve25519xsalsa_SRCS
	after.c
	before.c
	box.c
	box_keywrapper.c
	keypair.c
)
# from salsa20
set(Oberon.NaCl_salsa20_SRCS
	core.c
	stream.c
	xor.c
)
# from verify16
set(Oberon.NaCl_verify16_SRCS
	verify.c
)
# from verify32
set(Oberon.NaCl_verify32_SRCS
	verify.c
)

foreach(SRC_FILE ${Oberon.NaCl_SRCS})
    set(Oberon.NaCl_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(Oberon.NaCl_SRC_FILE ${SRC_FILE}
	    PATHS
	        "${BASE_PATH_FOR_THIS_MODULE}"
	        "${TARGET_BASE_LOCATION}"
			"${BASE_PATH_FOR_THIS_MODULE}/bigint"
			"${BASE_PATH_FOR_THIS_MODULE}/curve25519"
			"${BASE_PATH_FOR_THIS_MODULE}/ed25519"
			"${BASE_PATH_FOR_THIS_MODULE}/hsalsa20"
			"${BASE_PATH_FOR_THIS_MODULE}/poly1305"
			"${BASE_PATH_FOR_THIS_MODULE}/sha512"
			"${BASE_PATH_FOR_THIS_MODULE}/xsalsa20"
			"${BASE_PATH_FOR_THIS_MODULE}/xsalsa20poly1305"

	    CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${Oberon.NaCl_SRC_FILE}") # debug helper
list(APPEND Oberon.NaCl_SOURCES ${Oberon.NaCl_SRC_FILE})
endforeach()

foreach(SRC_FILE ${Oberon.NaCl_chacha20_SRCS})
    set(Oberon.NaCl_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(Oberon.NaCl_SRC_FILE ${SRC_FILE}
	    PATHS
			"${BASE_PATH_FOR_THIS_MODULE}/chacha20"
			
		CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${Oberon.NaCl_SRC_FILE}") # debug helper
list(APPEND Oberon.NaCl_SOURCES ${Oberon.NaCl_SRC_FILE})
endforeach()

foreach(SRC_FILE ${Oberon.NaCl_curve25519xsalsa_SRCS})
    set(Oberon.NaCl_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(Oberon.NaCl_SRC_FILE ${SRC_FILE}
	    PATHS
			"${BASE_PATH_FOR_THIS_MODULE}/curve25519xsalsa20poly1305"
			
		CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${Oberon.NaCl_SRC_FILE}") # debug helper
list(APPEND Oberon.NaCl_SOURCES ${Oberon.NaCl_SRC_FILE})
endforeach()

foreach(SRC_FILE ${Oberon.NaCl_salsa20_SRCS})
    set(Oberon.NaCl_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(Oberon.NaCl_SRC_FILE ${SRC_FILE}
	    PATHS
			"${BASE_PATH_FOR_THIS_MODULE}/salsa20"
			
		CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${Oberon.NaCl_SRC_FILE}") # debug helper
list(APPEND Oberon.NaCl_SOURCES ${Oberon.NaCl_SRC_FILE})
endforeach()

foreach(SRC_FILE ${Oberon.NaCl_verify16_SRCS})
    set(Oberon.NaCl_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(Oberon.NaCl_SRC_FILE ${SRC_FILE}
	    PATHS
			"${BASE_PATH_FOR_THIS_MODULE}/verify_16"
			
		CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${Oberon.NaCl_SRC_FILE}") # debug helper
list(APPEND Oberon.NaCl_SOURCES ${Oberon.NaCl_SRC_FILE})
endforeach()

foreach(SRC_FILE ${Oberon.NaCl_verify32_SRCS})
    set(Oberon.NaCl_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(Oberon.NaCl_SRC_FILE ${SRC_FILE}
	    PATHS
			"${BASE_PATH_FOR_THIS_MODULE}/verify_32"
			
		CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${Oberon.NaCl_SRC_FILE}") # debug helper
list(APPEND Oberon.NaCl_SOURCES ${Oberon.NaCl_SRC_FILE})
endforeach()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Oberon.NaCl DEFAULT_MSG Oberon.NaCl_INCLUDE_DIRS Oberon.NaCl_SOURCES)

