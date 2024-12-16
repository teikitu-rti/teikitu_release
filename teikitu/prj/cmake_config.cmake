# 015482FC-A4BD-4E1C-AE49-A30E5728D73A
# ========================================================================================================================================================================================================
#  Utility Functions
# ========================================================================================================================================================================================================
INCLUDE (CMakeParseArguments)

##########################################################################################################################################################################################################
# Determine the appropriate object (intermediate) directory for the current module (CMakeFile)
MACRO(TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY) 
        CMAKE_PATH ( GET CMAKE_SOURCE_DIR PARENT_PATH PROJECT_ROOT_DIR )
        CMAKE_PATH ( GET CMAKE_CURRENT_LIST_DIR PARENT_PATH MODULE_PATH_ROOT )
        CMAKE_PATH ( GET MODULE_PATH_ROOT PARENT_PATH MODULE_TEST_PATH )

        #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${PROJECT_ROOT_DIR} -- ${MODULE_PATH_ROOT} -- ${MODULE_TEST_PATH}" )
        FILE ( RELATIVE_PATH MODULE_NAME ${MODULE_PATH_ROOT} ${CMAKE_CURRENT_LIST_DIR} )
        #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${MODULE_NAME}" )

        CMAKE_PATH ( SET CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_OBJECT_OUTPUT_DIRECTORY})
        #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}" )
        IF ( NOT PROJECT_ROOT_DIR STREQUAL MODULE_TEST_PATH )
            FILE ( RELATIVE_PATH EXTRA_PATH_SEGMENT ${PROJECT_ROOT_DIR} ${MODULE_TEST_PATH} )
            SET ( CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}${EXTRA_PATH_SEGMENT}/ )
        ENDIF ()
        #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}" )
        SET ( CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}${MODULE_NAME}${ARGN}/ )
        #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}" )

        IF (NOT EXISTS ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY})
            FILE (MAKE_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY})
            MESSAGE( STATUS "Created directory: ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}")
        ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_FILE_TO_IDE source_files header_files test_assigned test_current file)
    CMAKE_PARSE_ARGUMENTS (TGS_ADD_FILE_TO_IDE "" "IDE_PATH" "" ${ARGN} )
    #MESSAGE("${source_files}")
    #MESSAGE("${TGS_ADD_FILE_TO_IDE_IDE_PATH}")
    #MESSAGE("${file}")
    #MESSAGE(TEST: ${test_current} ${test_assigned})

    # Add the file to the correct list for compilation
    IF ((${test_current} STREQUAL ${test_assigned}))
        SET (${source_files} ${${source_files}} "${file}")

    ELSEIF (MK_IDE__INCLUDE_NON_SOURCE_FILES)
        SET (${header_files} ${${header_files}} "${file}")
        SET_PROPERTY(SOURCE ${file} PROPERTY  HEADER_FILE_ONLY TRUE)

    ENDIF ()

    # Assign an IDE path (folder structure)
    IF (TGS_ADD_FILE_TO_IDE_IDE_PATH AND NOT ${TGS_ADD_FILE_TO_IDE_IDE_PATH} STREQUAL "")
        STRING (REPLACE "/" "\\" IDE_PATH_FIXED ${TGS_ADD_FILE_TO_IDE_IDE_PATH})
        #MESSAGE("${IDE_PATH_FIXED}")

        IF (MK_IDE__INCLUDE_NON_SOURCE_FILES AND NOT (${test_current} STREQUAL ${test_assigned}))
            SET (IDE_PATH_FIXED "${IDE_PATH_FIXED}\\${test_assigned} (Inactive)")
        ENDIF ()
        #MESSAGE("${IDE_PATH_FIXED}")

        SOURCE_GROUP ("${IDE_PATH_FIXED}" FILES "${file}")

    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_SOURCE_FILE source_files header_files test_assigned test_current ide_path file)
    IF (EXISTS ${file})
        TGS_ADD_FILE_TO_IDE(${source_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
        IF ((${test_current} STREQUAL ${test_assigned}))
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.c)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.c)
        ELSE ()
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
        ENDIF ()
    ELSE ()
        MESSAGE("FILE DOES NOT EXIST: " ${file})
    ENDIF ()
ENDMACRO ()

##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_INCSRC_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY HEADER_FILE_ONLY TRUE)
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()

##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_HEADER_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY  HEADER_FILE_ONLY TRUE)
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()

##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_CMAKE_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO()

##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            GET_FILENAME_COMPONENT( FILE_NAME_E "${file}" NAME_WLE )
            GET_FILENAME_COMPONENT( HLSL_CHECK "${file}" LAST_EXT )
            IF (${HLSL_CHECK} STREQUAL ".hlsl")
                GET_FILENAME_COMPONENT( FILE_NAME "${FILE_NAME_E}" NAME_WE )
                GET_FILENAME_COMPONENT( SHADER_TYPE "${FILE_NAME_E}" LAST_EXT )
                IF (${SHADER_TYPE} STREQUAL ".vs")
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_TYPE Vertex)
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_VARIABLE_NAME "g_ui${FILE_NAME}_VS_Compiled")
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_OUTPUT_HEADER_FILE "%(RelativeDir)${FILE_NAME}_vs.hlsl.h")
                    CMAKE_PATH ( SET IDE_HEADER_PATH NORMALIZE "${ide_path}/../Header Files")
                    IF (NOT EXISTS "${MK_BUILD_MODULE__SRC_DIR}/${FILE_NAME}_vs.hlsl.h")
                        FILE (WRITE "${MK_BUILD_MODULE__SRC_DIR}/${FILE_NAME}_vs.hlsl.h" "")
                        MESSAGE( STATUS "Created file: ${MK_BUILD_MODULE__SRC_DIR}/${FILE_NAME}_vs.hlsl.h")
                    ENDIF ()
                    TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} "${MK_BUILD_MODULE__SRC_DIR}/${FILE_NAME}_vs.hlsl.h" IDE_PATH ${IDE_HEADER_PATH})
                    SET_PROPERTY(SOURCE "${MK_BUILD_MODULE__SRC_DIR}/${FILE_NAME}_vs.hlsl.h" PROPERTY  HEADER_FILE_ONLY TRUE)
                ELSEIF (${SHADER_TYPE} STREQUAL ".ps")
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_TYPE Pixel)
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_VARIABLE_NAME "g_ui${FILE_NAME}_PS_Compiled")
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_OUTPUT_HEADER_FILE "%(RelativeDir)${FILE_NAME}_ps.hlsl.h")
                    CMAKE_PATH ( SET IDE_HEADER_PATH NORMALIZE "${ide_path}/../Header Files")
                    IF (NOT EXISTS "${MK_BUILD_MODULE__SRC_DIR}/${FILE_NAME}_ps.hlsl.h")
                        FILE (WRITE "${MK_BUILD_MODULE__SRC_DIR}/${FILE_NAME}_ps.hlsl.h" "")
                        MESSAGE( STATUS "Created file: ${MK_BUILD_MODULE__SRC_DIR}/${FILE_NAME}_ps.hlsl.h")
                    ENDIF ()
                    TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} "${MK_BUILD_MODULE__SRC_DIR}/${FILE_NAME}_ps.hlsl.h" IDE_PATH ${IDE_HEADER_PATH})
                    SET_PROPERTY(SOURCE "${MK_BUILD_MODULE__SRC_DIR}/${FILE_NAME}_ps.hlsl.h" PROPERTY  HEADER_FILE_ONLY TRUE)
                ELSE ()
                    MESSAGE("UNKNOWN HLSL SHADER FILE TYPE: " ${SHADER_TYPE} " - " ${file})
                ENDIF ()
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_MODEL 6.2)
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_ENTRYPOINT main)
                #SET_PROPERTY(SOURCE ${file} PROPERTY VS_SETTINGS "ExcludedFromBuild=true")
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_FLAGS [=[-HV 2021 -Zpc -Fd "$(OutDir)%(Filename).debug" -Frs "$(OutDir)%(Filename).root_sig" -Fre "$(OutDir)%(Filename).reflection" -Fsh "$(OutDir)%(Filename).hash" -Zsb -Zi]=])
            ELSE ()
                MESSAGE("FILE NAME DOES NOT TERMINATE WITH HLSL: " ${HLSL_CHECK} " - " ${file})
            ENDIF ()
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()

##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_HLSL_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            GET_FILENAME_COMPONENT( FILE_NAME_E "${file}" NAME_WLE )
            GET_FILENAME_COMPONENT( HLSL_CHECK "${file}" LAST_EXT )
            IF (${HLSL_CHECK} STREQUAL ".hlsl")
                GET_FILENAME_COMPONENT( FILE_NAME "${FILE_NAME_E}" NAME_WE )
                GET_FILENAME_COMPONENT( SHADER_TYPE "${FILE_NAME_E}" LAST_EXT )
                IF (${SHADER_TYPE} STREQUAL ".vs")
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_TYPE Vertex)
                ELSEIF (${SHADER_TYPE} STREQUAL ".ps")
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_TYPE Pixel)
                ELSE ()
                    MESSAGE("UNKNOWN HLSL SHADER FILE TYPE: " ${SHADER_TYPE} " - " ${file})
                ENDIF ()
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_MODEL 6.2)
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_ENTRYPOINT main)
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_OBJECT_FILE_NAME [=[$(LOCALAPPDATA)\Teikitu\%(Filename).cso]=])
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_FLAGS [=[-HV 2021 -Zpc -Fd "$(OutDir)%(Filename).debug" -Frs "$(OutDir)%(Filename).root_sig" -Fre "$(OutDir)%(Filename).reflection" -Fsh "$(OutDir)%(Filename).hash" -Zsb -Zi]=])
            ELSE ()
                MESSAGE("FILE NAME DOES NOT TERMINATE WITH HLSL: " ${HLSL_CHECK} " - " ${file})
            ENDIF ()
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()




# ========================================================================================================================================================================================================
#  Feature Enable / Disable and Default Compilation Configuration
#    - Include the list of primary configuration variables for legibility
# ========================================================================================================================================================================================================

SET (MK_CMAKE_BUILD_VERSION                     1.0.0.0) # major[.minor[.patch[.tweak]]]

SET (MK_BUILD__THREAD                           "" CACHE STRING "")
SET (MK_BUILD__UNIVERSAL                        "" CACHE STRING "")
SET (MK_BUILD__OS                               "" CACHE STRING "")
SET (MK_BUILD__DEVICE                           "" CACHE STRING "")




# ========================================================================================================================================================================================================
#  Default root directories for the binaries, library, and object files
# ========================================================================================================================================================================================================

CMAKE_PATH ( SET CMAKE_ARCHIVE_OUTPUT_DIRECTORY NORMALIZE ${PROJECT_SOURCE_DIR}/../lib/)
CMAKE_PATH ( SET CMAKE_LIBRARY_OUTPUT_DIRECTORY NORMALIZE ${PROJECT_SOURCE_DIR}/../lib/)
CMAKE_PATH ( SET CMAKE_RUNTIME_OUTPUT_DIRECTORY NORMALIZE ${PROJECT_SOURCE_DIR}/../bin/)
CMAKE_PATH ( SET CMAKE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${PROJECT_SOURCE_DIR}/../obj/)




# ========================================================================================================================================================================================================
#  Build path configuration based on compiler
# ========================================================================================================================================================================================================

# Compiler Flags for Compiler

SET (MK_COMPILER_NAME                         "")

IF (MK_COMPILER__CLANG)
    SET (MK_COMPILER_NAME                           "CLANG")

ELSEIF (MK_COMPILER__MSVC)
    SET (MK_COMPILER_NAME                           "MSVC")
ENDIF ()

IF ("${MK_COMPILER_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "UNKNOWN OR UNSUPPORTED COMPILER")
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgBUILD_COMPILER__${MK_COMPILER_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_COMPILER=${MK_COMPILER_NAME})

STRING (TOLOWER ${MK_COMPILER_NAME}             MK_COMPILER_PATH)

CMAKE_PATH (SET CMAKE_ARCHIVE_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}${MK_COMPILER_PATH}/)
CMAKE_PATH (SET CMAKE_LIBRARY_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}${MK_COMPILER_PATH}/)
CMAKE_PATH (SET CMAKE_RUNTIME_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${MK_COMPILER_PATH}/)
CMAKE_PATH (SET CMAKE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_OBJECT_OUTPUT_DIRECTORY}${MK_COMPILER_PATH}/)


# Compiler Flags for Compiler Frontend

SET (MK_COMPILER_FRONTEND_NAME                   "")

IF (MK_COMPILER_FRONTEND__GNU)
    SET (MK_COMPILER_FRONTEND_NAME                  "GNU")

ELSEIF (MK_COMPILER_FRONTEND__MSVC)
    SET (MK_COMPILER_FRONTEND_NAME                  "MSVC")

ELSEIF (MK_COMPILER_FRONTEND__APPLE)
    SET (MK_COMPILER_FRONTEND_NAME                  "APPLE")

ENDIF ()

IF ("${MK_COMPILER_FRONTEND_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "UNKNOWN OR UNSUPPORTED COMPILER FRONTEND")
ENDIF ()

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} [${MK_COMPILER_NAME}-${MK_COMPILER_FRONTEND_NAME}]")

ADD_COMPILE_DEFINITIONS (TgBUILD_COMPILER_FRONTEND__${MK_COMPILER_FRONTEND_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_COMPILER_FRONTEND=${MK_COMPILER_FRONTEND_NAME})

STRING (TOLOWER ${MK_COMPILER_FRONTEND_NAME}     MK_COMPILER_FRONTEND_PATH)
CMAKE_PATH (SET CMAKE_ARCHIVE_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}${MK_COMPILER_FRONTEND_PATH}/)
CMAKE_PATH (SET CMAKE_LIBRARY_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}${MK_COMPILER_FRONTEND_PATH}/)
CMAKE_PATH (SET CMAKE_RUNTIME_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${MK_COMPILER_FRONTEND_PATH}/)
CMAKE_PATH (SET CMAKE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_OBJECT_OUTPUT_DIRECTORY}${MK_COMPILER_FRONTEND_PATH}/)




# ========================================================================================================================================================================================================
#  Build path configuration based on configuration for Thread, Universal, OS, Device
# ========================================================================================================================================================================================================

SET (MK_BUILD__THREAD_NAME                      "" )
SET (MK_BUILD__UNIVERSAL_NAME                   "" )
SET (MK_BUILD__OS_NAME                          "" )
SET (MK_BUILD__DEVICE_NAME                      "" )

# Threading Library
IF ("${MK_BUILD__THREAD}" STREQUAL "DISPATCH")
    SET (MK_BUILD__THREAD_NAME                      "DISPATCH" )

ELSEIF ("${MK_BUILD__THREAD}" STREQUAL "WIN")
    SET (MK_BUILD__THREAD_NAME                      "WIN")

ELSEIF ("${MK_BUILD__THREAD}" STREQUAL "POSIX")
    SET (MK_BUILD__THREAD_NAME                      "POSIX" )

ENDIF ()

IF ("${MK_BUILD__THREAD_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "MUST SELECT A SUPPORTING THREADING LIBRARY")
ENDIF ()

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} [${MK_BUILD__THREAD_NAME}")

ADD_COMPILE_DEFINITIONS (TgCOMPILE_THREAD_SUPPORT__${MK_BUILD__THREAD_NAME})
ADD_COMPILE_DEFINITIONS (TgCOMPILE_THREAD_SUPPORT=${MK_BUILD__THREAD_NAME})

STRING (TOLOWER ${MK_BUILD__THREAD_NAME}        MK_BUILD__THREAD_PATH)
CMAKE_PATH (SET CMAKE_ARCHIVE_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}${MK_BUILD__THREAD_PATH}/)
CMAKE_PATH (SET CMAKE_LIBRARY_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}${MK_BUILD__THREAD_PATH}/)
CMAKE_PATH (SET CMAKE_RUNTIME_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${MK_BUILD__THREAD_PATH}/)
CMAKE_PATH (SET CMAKE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_OBJECT_OUTPUT_DIRECTORY}${MK_BUILD__THREAD_PATH}/)


# Operating System
IF ("${MK_BUILD__OS}" STREQUAL "WIN")
    SET (MK_BUILD__OS_NAME                          "WIN")
    SET (APP_TYPE                                   "WIN32")
#   SET (CMAKE_SYSTEM_VERSION                       "10.0.14393.0")
    SET (MK_BUILD_OS__MAX_FILE_PATH                 32768)

ELSEIF ("${MK_BUILD__OS}" STREQUAL "POSIX")
    SET (MK_BUILD__OS_NAME                          "POSIX")
    SET (MK_BUILD_OS__MAX_FILE_PATH                 240)

ENDIF ()

IF ("${MK_BUILD__OS_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "MUST SELECT AN OPERATING SYSTEM INTERFACE")
ENDIF ()

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} ${MK_BUILD__OS_NAME}")

ADD_COMPILE_DEFINITIONS (TgBUILD_OS__${MK_BUILD__OS_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_OS=${MK_BUILD__OS_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_OS__MAX_FILE_PATH=${MK_BUILD_OS__MAX_FILE_PATH})

IF (MK_COMPILE_PLATFORM_TEXT__WIDE)
    STRING (TOLOWER ${MK_BUILD__OS_NAME}_WC         MK_BUILD__OS_PATH)
ELSE ()
    STRING (TOLOWER ${MK_BUILD__OS_NAME}            MK_BUILD__OS_PATH)
ENDIF ()

CMAKE_PATH (SET CMAKE_ARCHIVE_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}${MK_BUILD__OS_PATH}/)
CMAKE_PATH (SET CMAKE_LIBRARY_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}${MK_BUILD__OS_PATH}/)
CMAKE_PATH (SET CMAKE_RUNTIME_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${MK_BUILD__OS_PATH}/)
CMAKE_PATH (SET CMAKE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_OBJECT_OUTPUT_DIRECTORY}${MK_BUILD__OS_PATH}/)


# Universal Package
IF ("${MK_BUILD__UNIVERSAL}" STREQUAL "UWP")
    IF (NOT WINDOWS_STORE)
        MESSAGE(FATAL_ERROR "PLATFORM UWP SELECTED BUT WINDOWS_STORE NOT ENABLED")
    ENDIF ()
    SET (MK_COMPILE_PLATFORM_TEXT__WIDE             1)
    SET (MK_BUILD__UNIVERSAL_NAME                   "UWP")
    SET (CMAKE_C_STANDARD_LIBRARIES                 "${CMAKE_C_STANDARD_LIBRARIES} WindowsApp.lib")
    SET (CMAKE_CXX_STANDARD_LIBRARIES               "${CMAKE_CXX_STANDARD_LIBRARIES} WindowsApp.lib")

ELSEIF ("${MK_BUILD__UNIVERSAL}" STREQUAL "APPLE")
    SET (MK_BUILD__UNIVERSAL_NAME                   "APPLE")

    #IF (NOT MK_IDE__XCODE)
    #    MESSAGE(FATAL_ERROR "XCODE MUST BE USED FOR APPLE UNIVERSAL BUILDS")
    #ENDIF ()

ELSE ()
    SET (MK_BUILD__UNIVERSAL_NAME                   "NONE")

ENDIF ()

IF (NOT "${MK_BUILD__UNIVERSAL_NAME}" STREQUAL "NONE")
    SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} ${MK_BUILD__UNIVERSAL_NAME}")

    ADD_COMPILE_DEFINITIONS (TgBUILD_UNIVERSAL__${MK_BUILD__UNIVERSAL_NAME})
    ADD_COMPILE_DEFINITIONS (TgBUILD_UNIVERSAL=${MK_BUILD__UNIVERSAL_NAME})

    STRING (TOLOWER ${MK_BUILD__UNIVERSAL_NAME}     MK_BUILD__UNIVERSAL_PATH)
    CMAKE_PATH (SET CMAKE_ARCHIVE_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}${MK_BUILD__UNIVERSAL_PATH}/)
    CMAKE_PATH (SET CMAKE_LIBRARY_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}${MK_BUILD__UNIVERSAL_PATH}/)
    CMAKE_PATH (SET CMAKE_RUNTIME_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${MK_BUILD__UNIVERSAL_PATH}/)
    CMAKE_PATH (SET CMAKE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_OBJECT_OUTPUT_DIRECTORY}${MK_BUILD__UNIVERSAL_PATH}/)
ENDIF ()


# Target Device
IF ("${MK_BUILD__DEVICE}" STREQUAL "DESKTOP_X86")
    SET (MK_BUILD__DEVICE_NAME                      "DESKTOP_X86")

ELSEIF ("${MK_BUILD__DEVICE}" STREQUAL "APPLE_MAC")
    SET (MK_BUILD__DEVICE_NAME                      "APPLE_MAC")

ELSEIF ("${MK_BUILD__DEVICE}" STREQUAL "APPLE_IPHONE")
    SET (MK_BUILD__DEVICE_NAME                      "APPLE_IPHONE")

ELSEIF ("${MK_BUILD__DEVICE}" STREQUAL "APPLE_IPAD")
    SET (MK_BUILD__DEVICE_NAME                      "APPLE_IPAD")

ELSEIF ("${MK_BUILD__DEVICE}" STREQUAL "APPLE_TV")
    SET (MK_BUILD__DEVICE_NAME                      "APPLE_TV")

ELSEIF ("${MK_BUILD__DEVICE}" STREQUAL "APPLE_WATCH")
    SET (MK_BUILD__DEVICE_NAME                      "APPLE_WATCH")

ENDIF ()

IF ("${MK_BUILD__DEVICE_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "MUST SELECT A TARGET DEVICE")
ENDIF ()

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} ${MK_BUILD__DEVICE_NAME}")

ADD_COMPILE_DEFINITIONS (TgBUILD_DEVICE__${MK_BUILD__DEVICE_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_DEVICE=${MK_BUILD__DEVICE_NAME})

STRING (TOLOWER ${MK_BUILD__DEVICE_NAME}        MK_BUILD__DEVICE_PATH)
CMAKE_PATH (SET CMAKE_ARCHIVE_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}${MK_BUILD__DEVICE_PATH}/)
CMAKE_PATH (SET CMAKE_LIBRARY_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}${MK_BUILD__DEVICE_PATH}/)
CMAKE_PATH (SET CMAKE_RUNTIME_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${MK_BUILD__DEVICE_PATH}/)
CMAKE_PATH (SET CMAKE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_OBJECT_OUTPUT_DIRECTORY}${MK_BUILD__DEVICE_PATH}/)

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME}]")




# ========================================================================================================================================================================================================
#  CMake Configuration for Module Features
# ========================================================================================================================================================================================================

SET (MK_BUILD__GRAPHICS_NAME                    "")

IF ("${MK_FEATURE__GRAPHICS}" STREQUAL "DX12")
    SET (MK_BUILD__GRAPHICS_NAME                    "DX12")
ELSEIF ("${MK_FEATURE__GRAPHICS}" STREQUAL "OGL")
    SET (MK_BUILD__GRAPHICS_NAME                    "OGL")
ELSEIF ("${MK_FEATURE__GRAPHICS}" STREQUAL "OGLES")
    SET (MK_BUILD__GRAPHICS_NAME                    "OGLES")
ELSEIF ("${MK_FEATURE__GRAPHICS}" STREQUAL "METAL")
    SET (MK_BUILD__GRAPHICS_NAME                    "METAL")
ELSEIF ("${MK_FEATURE__GRAPHICS}" STREQUAL "VULKAN")
    SET (MK_BUILD__GRAPHICS_NAME                    "VULKAN")
ELSEIF ("${MK_FEATURE__GRAPHICS}" STREQUAL "REF")
    SET (MK_BUILD__GRAPHICS_NAME                    "REF")
ELSE ()
    SET (MK_BUILD__GRAPHICS_NAME                    "NONE")
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgFEATURE_GRAPHICS__${MK_BUILD__GRAPHICS_NAME})
ADD_COMPILE_DEFINITIONS (TgFEATURE_GRAPHICS=${MK_BUILD__GRAPHICS_NAME})

IF (NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
    ADD_COMPILE_DEFINITIONS (TgBUILD_FEATURE__GRAPHICS)
ENDIF ()



SET (MK_BUILD__AUDIO_NAME                       "")

IF ("${MK_FEATURE__AUDIO}" STREQUAL "XAUDIO2")
    SET (MK_BUILD__AUDIO_NAME                       "XAUDIO2")
ELSEIF ("${MK_FEATURE__AUDIO}" STREQUAL "REF")
    SET (MK_BUILD__AUDIO_NAME                       "REF")
ELSE ()
    SET (MK_BUILD__AUDIO_NAME                       "NONE")
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgFEATURE_AUDIO__${MK_BUILD__AUDIO_NAME})
ADD_COMPILE_DEFINITIONS (TgFEATURE_AUDIO=${MK_BUILD__AUDIO_NAME})

IF (NOT "${MK_BUILD__AUDIO_NAME}" STREQUAL "NONE")
    ADD_COMPILE_DEFINITIONS (TgBUILD_FEATURE__AUDIO)
ENDIF ()




# ========================================================================================================================================================================================================
#  Configuration for Hardware
# ========================================================================================================================================================================================================

SET (MK_HARDWARE_NAME                           "")
SET (MK_HARDWARE__IMPLEMENTATION                0)
SET (MK_HARDWARE__POINTER_SIZE                  0)
SET (MK_HARDWARE__WORDSIZE                      0)
SET (MK_HARDWARE__CPU_CACHE_LINE_SIZE           0)

IF ("${MK_BUILD__HW}" STREQUAL "ARM_64")
    SET (MK_HARDWARE_NAME                           "ARM")
    SET (MK_HARDWARE__POINTER_SIZE                  8)
    SET (MK_HARDWARE__WORDSIZE                      8)      # 4 for 32bit
    SET (MK_HARDWARE__CPU_CACHE_LINE_SIZE           64)     # 32 for 32bit
ELSEIF ("${MK_BUILD__HW}" STREQUAL "PPC")
    SET (MK_HARDWARE_NAME                           "PPC")
    SET (MK_HARDWARE__POINTER_SIZE                  4)
    SET (MK_HARDWARE__WORDSIZE                      8)
    SET (MK_HARDWARE__CPU_CACHE_LINE_SIZE           64)
ELSEIF ("${MK_BUILD__HW}" STREQUAL "INTEL_X64")
    SET (MK_HARDWARE_NAME                           "INTEL")
    SET (MK_HARDWARE__POINTER_SIZE                  8)      # 4 for 32bit
    SET (MK_HARDWARE__WORDSIZE                      8)      # 4 for 32bit
    SET (MK_HARDWARE__CPU_CACHE_LINE_SIZE           64)     # 32 for 32bit
ELSEIF ("${MK_BUILD__HW}" STREQUAL "C11_X64")
    SET (MK_HARDWARE_NAME                           "C11")
    SET (MK_HARDWARE__POINTER_SIZE                  8)      # 4 for 32bit
    SET (MK_HARDWARE__WORDSIZE                      8)      # 4 for 32bit
    SET (MK_HARDWARE__CPU_CACHE_LINE_SIZE           64)     # 32 for 32bit
ENDIF ()

IF ("${MK_HARDWARE_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "MUST HAVE A TARGET HARDWARE ARCHITECTURE (${MK_BUILD__HW})")
ENDIF ()

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} [${MK_HARDWARE_NAME}]")

ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE__${MK_HARDWARE_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE=${MK_HARDWARE_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE__POINTER_SIZE=${MK_HARDWARE__POINTER_SIZE})
ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE__WORDSIZE=${MK_HARDWARE__WORDSIZE})
ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE__CPU_CACHE_LINE_SIZE=${MK_HARDWARE__CPU_CACHE_LINE_SIZE})




# ========================================================================================================================================================================================================
# Text Literal Format
# ========================================================================================================================================================================================================

IF (MK_COMPILE_PLATFORM_TEXT__WIDE)
    ADD_COMPILE_DEFINITIONS (TgCOMPILE_OS_TEXT__WIDE)

ELSE ()
    ADD_COMPILE_DEFINITIONS (TgCOMPILE_OS_TEXT__UTF8)

ENDIF ()




# ========================================================================================================================================================================================================
#  Configuration for IDE
# ========================================================================================================================================================================================================

IF (MK_IDE__MSVC)
    SET (MK_IDE__INCLUDE_NON_SOURCE_FILES           1) # Add the non-source files to the project
    SET (MK_IDE_NAME                                MSVC)

    CONFIGURE_FILE( Directory.build.props ${CMAKE_BINARY_DIR}/Directory.build.props COPYONLY )

ELSEIF (MK_IDE__XCODE)
    SET (MK_IDE__INCLUDE_NON_SOURCE_FILES           1) # Add the non-source files to the project
    SET (MK_IDE_NAME                                XCODE)

    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_ANALYZER_DEADCODE_DEADSTORES            YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_ANALYZER_GCD                            YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_ANALYZER_MEMORY_MANAGEMENT              YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_ANALYZER_NONNULL                        YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_ANALYZER_SECURITY_FLOATLOOPCOUNTER      YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_WARN_BOOL_CONVERSION                    YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_WARN_CONSTANT_CONVERSION                YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_WARN_EMPTY_BODY                         YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_WARN_ENUM_CONVERSION                    YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_WARN_IMPLICIT_SIGN_CONVERSION           YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_WARN_INFINITE_RECURSION                 YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_WARN_INT_CONVERSION                     YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_WARN_NULLABLE_TO_NONNULL_CONVERSION     YES )
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_WARN_UNREACHABLE_CODE                   YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_C_LANGUAGE_STANDARD                       C11 )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_ENABLE_BUILTIN_FUNCTIONS                  YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_STRICT_ALIASING                           YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_THREADSAFE_STATICS                        YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_64_TO_32_BIT_CONVERSION              YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_ABOUT_MISSING_FIELD_INITIALIZERS     YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_ABOUT_MISSING_PROTOTYPES             YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_ABOUT_POINTER_SIGNEDNESS             YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_ABOUT_RETURN_TYPE                    YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_CHECK_SWITCH_STATEMENTS              YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_INITIALIZER_NOT_FULLY_BRACKETED      YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_MISSING_PARENTHESES                  YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_PEDANTIC                             YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_SHADOW                               YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_SIGN_COMPARE                         YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_TYPECHECK_CALLS_TO_PRINTF            YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_UNKNOWN_PRAGMAS                      YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_UNUSED_FUNCTION                      YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_UNUSED_LABEL                         YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_UNUSED_PARAMETER                     YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_UNUSED_VALUE                         YES )
    SET(CMAKE_XCODE_ATTRIBUTE_GCC_WARN_UNUSED_VARIABLE                      YES )

    # Copy the Workspace settings file from the current directory to the given location
    CONFIGURE_FILE(
        WorkspaceSettings.xcsettings
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.xcodeproj/project.xcworkspace/xcuserdata/$ENV{USER}.xcuserdatad/WorkspaceSettings.xcsettings
        COPYONLY
    )

ELSEIF (MK_IDE__UNIX_MAKEFILES)
    SET (MK_IDE_NAME                                UNIX_MAKEFILES)

ELSEIF (MK_IDE__NINJA)
    SET (MK_IDE_NAME                                NINJA)

#    IF (CMAKE_VS_PLATFORM_TOOLSET STREQUAL "ClangCL")
#        SET (ENV CC CLANG-CL)
#        SET (ENV CXX CLANG-CL)
#    ENDIF ()
ENDIF ()

IF ("${MK_IDE_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "UNSUPPORTED IDE: " ${CMAKE_GENERATOR})
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgIDE__${MK_IDE_NAME})
ADD_COMPILE_DEFINITIONS (TgIDE=${MK_IDE_NAME})




# ========================================================================================================================================================================================================
#  Configuration Types
# ========================================================================================================================================================================================================

SET (MK_COMPILE__TYPE                         "")

IF (CMAKE_BUILD_TYPE MATCHES RELEASE)
    SET (MK_COMPILE__TYPE                         "RELEASE")
    SET (MK_COMPILE__TYPE__RELEASE                1)
    SET (CMAKE_MSVC_RUNTIME_LIBRARY               MultiThreaded)

ELSEIF (CMAKE_BUILD_TYPE MATCHES FINAL)
    SET (MK_COMPILE__TYPE                         "FINAL")
    SET (MK_COMPILE__TYPE__FINAL                  1)
    SET (CMAKE_MSVC_RUNTIME_LIBRARY               MultiThreaded)

ELSEIF (CMAKE_BUILD_TYPE MATCHES TOOLS)
    SET (MK_COMPILE__TYPE                         "TOOLS")
    SET (MK_COMPILE__TYPE__TOOLS                  1)
    SET (CMAKE_MSVC_RUNTIME_LIBRARY               MultiThreaded)

ELSEIF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    SET (MK_COMPILE__TYPE                         "DEBUG")
    SET (MK_COMPILE__TYPE__DEBUG                  1)
    SET (CMAKE_MSVC_RUNTIME_LIBRARY               MultiThreadedDebug)

ELSE ()

    MESSAGE(FATAL_ERROR "UNKNOWN BUILD TYPE: " ${CMAKE_BUILD_TYPE})

ENDIF ()

# Compiler Flags for Configuration

ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Debug>:TGS_DEBUG>)
ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Release>:TGS_RELEASE>)
ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Final>:TGS_FINAL>)
ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Tools>:TGS_TOOLS>)




# ========================================================================================================================================================================================================
# Validation and Reporting
# ========================================================================================================================================================================================================

# Validate project name

IF (NOT ${__CMAKE_PROJECT_NAME} STREQUAL ${MK_PROJECT_NAME})
    MESSAGE("Solution name has changed - remake the cmake project directory.")
    MESSAGE("[${MK_PROJECT_NAME}] vs [${__CMAKE_PROJECT_NAME}]")
    MESSAGE(FATAL_ERROR "Terminating Execution")
ENDIF ()




# ========================================================================================================================================================================================================
#  Function: TGS_SET_STANDARD_PROPERTIES
# ========================================================================================================================================================================================================

FUNCTION (TGS_SET_STANDARD_PROPERTIES TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES)

    # Add standard include paths
    CMAKE_PATH ( SET PCH_SOURCE_PATH NORMALIZE      "${PCH_SOURCE_DIR}")
    TARGET_INCLUDE_DIRECTORIES(${TARGET}            BEFORE PRIVATE "${PCH_SOURCE_PATH}")
    CMAKE_PATH ( SET PROJECT_SOURCE_PATH NORMALIZE  "${PROJECT_SOURCE_DIR}/../inc")
    TARGET_INCLUDE_DIRECTORIES(${TARGET}            BEFORE PRIVATE "${PROJECT_SOURCE_PATH}")
    CMAKE_PATH ( SET EXTERNAL_PATH NORMALIZE        "${PROJECT_SOURCE_DIR}/../../external")
    TARGET_INCLUDE_DIRECTORIES(${TARGET}            BEFORE PRIVATE "${EXTERNAL_PATH}")

    # -- COMPILATION GENERATOR SETTINGS ----

    IF (MK_IDE__NINJA)
        TARGET_PRECOMPILE_HEADERS(${TARGET}             PRIVATE ${PCH_INCLUDE})
    ENDIF ()


    # -- COMPILER FRONTEND SETTINGS ----

    IF (MK_COMPILER_FRONTEND__MSVC)

        TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE /Yu\"${PCH_INCLUDE}\" ) # Use PCH
        TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE /Zi) # Debug information format (PDB)
        TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE /Fp$(IntDir)$(TargetName)_C.pch ) # Default the project to use the C PCH

    ENDIF ()


    # -- COMPILER SETTINGS ----

    SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES LTCG_GLOBAL_OPT_FINAL 1) # Enable LTCG for final and tool builds
    SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES LTCG_GLOBAL_OPT_TOOLS 1) # Enable LTCG for final and tool builds
    SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES DISABLE_LANGUAGE_EXTENSIONS 1)

    SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES INTERMEDIATE_OUTPUT_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}) # Custom properties used in our version of CMake to set the intermediate directory

    TARGET_COMPILE_DEFINITIONS(${TARGET}            PRIVATE TgCOMPILE_DEFAULT_PCH=${PCH_INCLUDE})
    TARGET_COMPILE_DEFINITIONS(${TARGET}            PRIVATE __MODULE__=${MK_BUILD_ROOT__MODULE_NAME})

    IF (MK_COMPILER__CLANG)
        TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE -Wno-reserved-macro-identifier)
#       TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE --analyze)
    ENDIF ()

    IF (MK_COMPILER__MSVC)

        TARGET_COMPILE_DEFINITIONS(${TARGET}            PRIVATE D_ANALYSIS)

        TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE /Zc:preprocessor )
        TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE /Fp$(IntDir)$(TargetName)_CXX.pch) # Default the project to use the C++ PCH.
        TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE /EHs) # Enable C++ exception handling for all files

        # Mark the C File source file for PCH creation.
        IF (EXISTS "${PCH_SOURCE_DIR}/${PCH_SOURCE}.c")
            SET_PROPERTY(SOURCE "${PCH_SOURCE_DIR}/${PCH_SOURCE}.c" APPEND_STRING PROPERTY COMPILE_FLAGS " /Yc")
        ENDIF ()

    ENDIF ()

    IF ("${MK_BUILD__OS}" STREQUAL "WIN")
        ADD_COMPILE_DEFINITIONS (TgCOMPILE__PLATFORM_TIME)
        IF (MK_COMPILE_PLATFORM_TEXT__WIDE)
            TARGET_COMPILE_DEFINITIONS(${TARGET}            PRIVATE _UNICODE)
            TARGET_COMPILE_DEFINITIONS(${TARGET}            PRIVATE UNICODE)
        ENDIF ()
    ENDIF ()


    # -- COMPILER SETTINGS: PER-FILE SETTINGS (PRECOMPILED HEADER FILES) ----

    # NOTE: This marks the file, independent of the target (i.e. source file properties are retained within an instance of an invocation.
    FOREACH (MK_LIST_ITEM__FILE_NAME IN ITEMS ${${SOURCE_FILES}} )
        GET_FILENAME_COMPONENT( FILE_EXTENSION "${MK_LIST_ITEM__FILE_NAME}" EXT )
        # stdatomic is not supported in MSVC 2022. Compile everything as a C++ project
        IF (MK_COMPILER__MSVC OR ${FILE_EXTENSION} STREQUAL ".cpp")
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" PROPERTY LANGUAGE CXX)
        ELSE ()
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" PROPERTY LANGUAGE C)
        ENDIF ()
    ENDFOREACH ()

    IF (MK_COMPILER_FRONTEND__MSVC)

        # NOTE: This marks the file, independent of the target (i.e. source file properties are retained within an instance of an invocation.
        CMAKE_PATH ( GET CMAKE_SOURCE_DIR PARENT_PATH PROJECT_ROOT_DIR )
        FOREACH (MK_LIST_ITEM__FILE_NAME IN ITEMS ${${SOURCE_FILES}} )

            FILE ( RELATIVE_PATH MK_LIST_ITEM__RELATIVE_PATH ${PROJECT_ROOT_DIR} ${MK_LIST_ITEM__FILE_NAME} )
            GET_FILENAME_COMPONENT( FILE_DIRECTORY "${MK_LIST_ITEM__RELATIVE_PATH}" DIRECTORY )
            STRING(FIND ${FILE_DIRECTORY} external IS_EXTERNAL_PATH)
            IF(${IS_EXTERNAL_PATH} LESS 0)
                SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" APPEND_STRING PROPERTY COMPILE_FLAGS " /FI \"${PCH_INCLUDE}\"") # Force include
            ENDIF ()

            GET_FILENAME_COMPONENT( FILE_EXTENSION "${MK_LIST_ITEM__FILE_NAME}" EXT )
            IF (${FILE_EXTENSION} STREQUAL ".cpp")
                SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" APPEND_STRING PROPERTY COMPILE_FLAGS [=[ /Fp"$(IntDir)$(TargetName)_CXX.pch"]=])
            ELSE ()
                SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" APPEND_STRING PROPERTY COMPILE_FLAGS [=[ /Fp"$(IntDir)$(TargetName)_C.pch"]=])
            ENDIF ()
        ENDFOREACH ()

        # Mark the C File source file for PCH creation.
        IF (EXISTS "${PCH_SOURCE_DIR}/${PCH_SOURCE}.cpp")
            SET_PROPERTY(SOURCE "${PCH_SOURCE_DIR}/${PCH_SOURCE}.cpp" APPEND_STRING PROPERTY COMPILE_FLAGS " /Yc")
        ENDIF ()

        # Mark the C File source file for PCH creation.
        IF (EXISTS "${PCH_SOURCE_DIR}/${PCH_SOURCE}.c")
            SET_PROPERTY(SOURCE "${PCH_SOURCE_DIR}/${PCH_SOURCE}.c" APPEND_STRING PROPERTY COMPILE_FLAGS " /Yc")
        ENDIF ()

    ENDIF ()



    # -- PLATFORM SETTINGS ----

    IF (MK_COMPILER_FRONTEND__MSVC)

        IF (MK_BUILD__UNIVERSAL__UWP)

            MESSAGE(FATAL_ERROR "UNSUPPORTED UNIVERSAL BUILD")

            SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES USE_DEBUG_LIB_DEBUG 1)
            SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES USE_DOT_NET_NATIVE_RELEASE 1)
            SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES USE_DOT_NET_NATIVE_FINAL 1)
            SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES VS_DESKTOP_EXTENSIONS_VERSION "10.0.14393.0" )

            TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE /MD$<$<CONFIG:Debug>:d>)
            TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE $<$<COMPILE_LANGUAGE:CXX>:/ZW>)
            TARGET_COMPILE_DEFINITIONS(${TARGET}            PRIVATE _HAS_EXCEPTIONS=$<IF:$<COMPILE_LANGUAGE:CXX>,1,0>)
        ELSE ()
            SET_TARGET_PROPERTIES( ${TARGET}                PROPERTIES WIN32 1)
            TARGET_COMPILE_OPTIONS (${TARGET}               PRIVATE /MT$<$<CONFIG:Debug>:d>)
        ENDIF ()

    ENDIF ()




    # -- STATIC LIBRARY SETTINGS ----

    GET_TARGET_PROPERTY (TARGET_TYPE ${TARGET} TYPE)
    IF (TARGET_TYPE STREQUAL "STATIC_LIBRARY")
        IF (MK_COMPILER_FRONTEND__MSVC)
            SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES STATIC_LIBRARY_OPTIONS /MACHINE:X64)
        ENDIF ()
    ENDIF ()



    # -- LINKER (EXE) SETTINGS ----

    GET_TARGET_PROPERTY (TARGET_TYPE ${TARGET} TYPE)
    IF (TARGET_TYPE STREQUAL "EXECUTABLE")
        IF (MK_COMPILER__MSVC)
        ENDIF ()

        IF (MK_COMPILER__CLANG AND MK_COMPILER_FRONTEND__MSVC)
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE /errorlimit:0)
        ENDIF ()

        IF (MK_COMPILER_FRONTEND__MSVC)

            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE /DEBUG)
            #TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE /NODEFAULTLIB)
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE /MACHINE:X64)

            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:/defaultlib:KERNEL32.LIB")
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:/defaultlib:UUID.LIB")
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:/defaultlib:libucrt$<$<CONFIG:Debug>:d>.lib")
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:/defaultlib:libvcruntime$<$<CONFIG:Debug>:d>.lib")
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:/defaultlib:libcmt$<$<CONFIG:Debug>:d>.lib")
        ENDIF ()

        IF (MK_PLATFORM__MAC)
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:-framework AudioToolbox")
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:-framework CoreGraphics")
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:-framework QuartzCore")
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:-framework UIKit")
            TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:-framework Foundation")
        ENDIF ()
    ENDIF ()


ENDFUNCTION (TGS_SET_STANDARD_PROPERTIES)




# ========================================================================================================================================================================================================
#  Function: TGS_SET_STANDARD_EXECUTABLE
# ========================================================================================================================================================================================================

FUNCTION (TGS_ADD_STANDARD_EXECUTABLE TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES)

    ADD_EXECUTABLE (${TARGET}                       ${APP_TYPE} ${${SOURCE_FILES}})

    #SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer: Andrew Aye")
    TGS_SET_STANDARD_PROPERTIES ( ${TARGET}         ${PCH_SOURCE_DIR} ${PCH_SOURCE} ${PCH_INCLUDE} ${SOURCE_FILES} ${HEADER_FILES})

ENDFUNCTION (TGS_ADD_STANDARD_EXECUTABLE)




# ========================================================================================================================================================================================================
#  Function: TGS_ADD_UNITTEST_EXECUTABLE
# ========================================================================================================================================================================================================

FUNCTION (TGS_ADD_UNITTEST_EXECUTABLE TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES)

    # Include the UWP standard runtime files
    IF (MK_BUILD__UNIVERSAL__UWP)
        SET (${SOURCE_FILES} ${${SOURCE_FILES}} "${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/UnitTestApp.xaml.cpp")
        SOURCE_GROUP ("Resource Files" FILES "${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/UnitTestApp.xaml.cpp")
        SET (${SOURCE_FILES} ${${SOURCE_FILES}} "${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/UnitTestApp.xaml")
        SOURCE_GROUP ("Resource Files" FILES "${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/UnitTestApp.xaml")
        SET_SOURCE_FILES_PROPERTIES("${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/UnitTestApp.xaml" PROPERTIES VS_XAML_TYPE "ApplicationDefinition" )

        IF (INCLUDE_NON_SOURCE_FILES)
            SET (${SOURCE_FILES} ${${SOURCE_FILES}} "${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/UnitTestApp.xaml.h")
            SOURCE_GROUP ("Resource Files" FILES "${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/UnitTestApp.xaml.h")
            SET (${SOURCE_FILES} ${${SOURCE_FILES}} "${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/pch.h")
            SOURCE_GROUP ("Resource Files" FILES "${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/pch.h")
            SET (${SOURCE_FILES} ${${SOURCE_FILES}} "${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/UnitTestApp.rd.xml")
            SOURCE_GROUP ("Resource Files" FILES "${PROJECT_SOURCE_DIR}/../src/TgS UNIT TEST/UnitTestApp.rd.xml")
        ENDIF (INCLUDE_NON_SOURCE_FILES)
    ENDIF ()

    ADD_EXECUTABLE (${TARGET}                       ${APP_TYPE} ${${SOURCE_FILES}} ${${HEADER_FILES}})

    # Add Unit Test paths for compilation
    TARGET_INCLUDE_DIRECTORIES(${TARGET}            PRIVATE "${PROJECT_SOURCE_DIR}/../tst/src/TgS UNIT TEST")
    TARGET_INCLUDE_DIRECTORIES(${TARGET}            PRIVATE "${PROJECT_SOURCE_DIR}/../tst/inc")

    IF (MK_BUILD__UNIVERSAL__UWP)
        TARGET_INCLUDE_DIRECTORIES(${TARGET}            PRIVATE "$(VCInstallDir)UnitTest/include/UWP")
        TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE /LIBPATH:"$(VCInstallDir)UnitTest/lib/UWP")
    ELSEIF (MK_BUILD__OS__WIN)
        TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE /LIBPATH:"$(VCInstallDir)UnitTest/lib/W64")
        TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:/defaultlib:kernel32.lib")
    ENDIF ()

    # Set UWP Unit Test configuration / references
    IF (MK_BUILD__UNIVERSAL__UWP)
        SET_TARGET_PROPERTIES(${TARGET}                 PROPERTIES VS_CPPUNITTESTFRAMEWORK_EXTENSIONS_VERSION "14.0" )
        SET_TARGET_PROPERTIES(${TARGET}                 PROPERTIES VS_TESTPLATFORM_EXTENSIONS_VERSION "14.0" )
        SET_TARGET_PROPERTIES(${TARGET}                 PROPERTIES UWP_APPLICATION_ID "vstest.executionengine.universal.App")
    ENDIF ()

    # SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Sign to Run Locally")
    TGS_SET_STANDARD_PROPERTIES ( ${TARGET}         ${PCH_SOURCE_DIR} ${PCH_SOURCE} ${PCH_INCLUDE} ${SOURCE_FILES} ${HEADER_FILES})

ENDFUNCTION (TGS_ADD_UNITTEST_EXECUTABLE)


# ========================================================================================================================================================================================================
# ========================================================================================================================================================================================================
 