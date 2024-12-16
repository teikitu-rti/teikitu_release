# 015482FC-A4BD-4E1C-AE49-A30E5728D73A

# ========================================================================================================================================================================================================
#  OPTIONS
#  Feature Enable / Disable and Default Compilation Configuration
#    - Include the list of primary configuration variables for legibility
# ========================================================================================================================================================================================================

SET (MK_CMAKE_BUILD_VERSION                     1.0.0.0) # major[.minor[.patch[.tweak]]]

INCLUDE(${GIT_ROOT_PATH}/cmake/cmake_options.cmake)




# ========================================================================================================================================================================================================
#  Language
# ========================================================================================================================================================================================================

SET (CMAKE_C_STANDARD                           17) # For atomic operations
SET (CMAKE_C_EXTENSIONS                        OFF)
SET (CMAKE_C_STANDARD_REQUIRED                  ON)
SET (CMAKE_CXX_STANDARD                         20) # For unicode literals
SET (CMAKE_CXX_EXTENSIONS                      OFF)
SET (CMAKE_CXX_STANDARD_REQUIRED                ON)




# ========================================================================================================================================================================================================
#  Default root directories for the binaries, library, and object files
# ========================================================================================================================================================================================================

CMAKE_PATH ( SET CMAKE_ARCHIVE_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_BINARY_DIR}/lib/)
CMAKE_PATH ( SET CMAKE_LIBRARY_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_BINARY_DIR}/lib/)
CMAKE_PATH ( SET CMAKE_RUNTIME_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_BINARY_DIR}/bin/)
CMAKE_PATH ( SET CMAKE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_BINARY_DIR}/obj/)




# ========================================================================================================================================================================================================
#  Determine the host system
# ========================================================================================================================================================================================================

SET (MK_BUILD__HOST_NAME "")

IF (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    SET (MK_BUILD__HOST_LINUX 0)
    SET (MK_BUILD__HOST_MACOS 0)
    SET (MK_BUILD__HOST_WINDOWS 1)
    SET (MK_BUILD__HOST_NAME "HWIN")
ELSEIF (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    SET (MK_BUILD__HOST_LINUX 0)
    SET (MK_BUILD__HOST_MACOS 1)
    SET (MK_BUILD__HOST_WINDOWS 0)
    SET (MK_BUILD__HOST_NAME "HMAC")
ELSEIF (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    SET (MK_BUILD__HOST_LINUX 1)
    SET (MK_BUILD__HOST_MACOS 0)
    SET (MK_BUILD__HOST_WINDOWS 0)
    SET (MK_BUILD__HOST_NAME "HLNX")
ELSE ()
    MESSAGE(FATAL_ERROR "UNKNOWN BUILD HOST: " ${CMAKE_HOST_SYSTEM_NAME})
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgBUILD_HOST_SYSTEM__${MK_BUILD__HOST_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_HOST_SYSTEM=${MK_BUILD__HOST_NAME})

STRING (TOLOWER ${MK_BUILD__HOST_NAME}           MK_BUILD__HOST_PATH)
SET (MK_BUILD__TARGET_DIRECTORY                  ${MK_BUILD__HOST_PATH})



# ========================================================================================================================================================================================================
#  Determine the IDE (from the cmake generator)
# ========================================================================================================================================================================================================

SET (MK_BUILD__IDE_NAME "")

IF (CMAKE_GENERATOR MATCHES "Visual Studio.*")
    SET (MK_IDE__MSVC 1 )
    SET (MK_BUILD__IDE_NAME "MSVC")
ELSEIF (CMAKE_GENERATOR MATCHES "Xcode")
    SET (MK_IDE__XCODE 1 )
    SET (MK_BUILD__IDE_NAME "XCODE")
ELSEIF (CMAKE_GENERATOR MATCHES "Unix Makefiles")
    SET (MK_IDE__UNIX_MAKEFILES 1 )
    SET (MK_BUILD__IDE_NAME "MAKE")
ELSEIF (CMAKE_GENERATOR MATCHES "Ninja")
    SET (MK_IDE__NINJA 1 )
    SET (MK_BUILD__IDE_NAME "NINJA")
ELSE ()
    MESSAGE(FATAL_ERROR "UNKNOWN IDE: " ${CMAKE_GENERATOR})
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgIDE__${MK_BUILD__IDE_NAME})
ADD_COMPILE_DEFINITIONS (TgIDE=${MK_BUILD__IDE_NAME})

STRING (TOLOWER ${MK_BUILD__IDE_NAME}           MK_BUILD__IDE_PATH)
SET (MK_BUILD__TARGET_DIRECTORY                 "${MK_BUILD__TARGET_DIRECTORY}_${MK_BUILD__IDE_PATH}")



# ========================================================================================================================================================================================================
#  Build path configuration based on compiler
# ========================================================================================================================================================================================================

# Compiler Flags for Compiler Frontend

SET (MK_BUILD__COMPILER_FRONTEND_NAME "")

IF (MK_COMPILER_FRONTEND__APPLE)
    SET (MK_BUILD__COMPILER_FRONTEND_NAME "APPLE")

ELSEIF (MK_COMPILER_FRONTEND__GNU)
    SET (MK_BUILD__COMPILER_FRONTEND_NAME "GNU")

ELSEIF (MK_COMPILER_FRONTEND__MSVC)
    SET (MK_BUILD__COMPILER_FRONTEND_NAME "MSVC")

ENDIF ()

IF ("${MK_BUILD__COMPILER_FRONTEND_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "UNKNOWN OR UNSUPPORTED COMPILER FRONTEND")
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgBUILD_COMPILER_FRONTEND__${MK_BUILD__COMPILER_FRONTEND_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_COMPILER_FRONTEND=${MK_BUILD__COMPILER_FRONTEND_NAME})

# Compiler Flags for Compiler

SET (MK_BUILD__COMPILER_NAME "")

IF (MK_COMPILER__APPLE)
    SET (MK_BUILD__COMPILER_NAME "APPLE")

ELSEIF (MK_COMPILER__CLANG)
    SET (MK_BUILD__COMPILER_NAME "CLANG")

ELSEIF (MK_COMPILER__MSVC)
    SET (MK_BUILD__COMPILER_NAME "MSVC")

ENDIF ()

IF ("${MK_BUILD__COMPILER_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "UNKNOWN OR UNSUPPORTED COMPILER")
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgBUILD_COMPILER__${MK_BUILD__COMPILER_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_COMPILER=${MK_BUILD__COMPILER_NAME})


SET (MK_PROJECT_NAME "${MK_PROJECT_NAME} [${MK_BUILD__COMPILER_FRONTEND_NAME}-${MK_BUILD__COMPILER_NAME}]")
STRING (TOLOWER ${MK_BUILD__COMPILER_FRONTEND_NAME} MK_BUILD__COMPILER_FRONTEND_PATH)
STRING (TOLOWER ${MK_BUILD__COMPILER_NAME}          MK_BUILD__COMPILER_PATH)
SET (MK_BUILD__TARGET_DIRECTORY                     "${MK_BUILD__TARGET_DIRECTORY}_${MK_BUILD__COMPILER_FRONTEND_PATH}")
SET (MK_BUILD__TARGET_DIRECTORY                     "${MK_BUILD__TARGET_DIRECTORY}_${MK_BUILD__COMPILER_PATH}")




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

ELSEIF ("${MK_BUILD__THREAD}" STREQUAL "WINDOWS")
    SET (MK_BUILD__THREAD_NAME                      "WINDOWS")

ELSEIF ("${MK_BUILD__THREAD}" STREQUAL "POSIX")
    SET (MK_BUILD__THREAD_NAME                      "POSIX" )

ENDIF ()

IF ("${MK_BUILD__THREAD_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "MUST SELECT A SUPPORTING THREADING LIBRARY")
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgCOMPILE_THREAD_SUPPORT__${MK_BUILD__THREAD_NAME})
ADD_COMPILE_DEFINITIONS (TgCOMPILE_THREAD_SUPPORT=${MK_BUILD__THREAD_NAME})

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} [${MK_BUILD__THREAD_NAME}")
STRING (TOLOWER ${MK_BUILD__THREAD_NAME}        MK_BUILD__THREAD_PATH)
SET (MK_BUILD__TARGET_DIRECTORY                 "${MK_BUILD__TARGET_DIRECTORY}_${MK_BUILD__THREAD_PATH}")


# Operating System
IF ("${MK_BUILD__OS}" STREQUAL "WINDOWS")
    SET (MK_BUILD__OS_NAME                          "WINDOWS")
    SET (APP_TYPE                                   "WIN32")
#   SET (CMAKE_SYSTEM_VERSION                       "10.0.14393.0")
    SET (MK_BUILD_OS__MAX_FILE_PATH                 32768)
    SET (MK_BUILD_OS__WINDOWS                       1)
    SET (MK_BUILD__OS_TEXT_WIDE                     1)

ELSEIF ("${MK_BUILD__OS}" STREQUAL "POSIX")
    SET (MK_BUILD__OS_NAME                          "POSIX")
    SET (MK_BUILD_OS__MAX_FILE_PATH                 240)
    SET (MK_BUILD_OS__POSIX                         1)
    SET (MK_BUILD__OS_TEXT_WIDE                     0)

ELSEIF ("${MK_BUILD__OS}" STREQUAL "ANDROID")
    SET (MK_BUILD__OS_NAME                          "ANDROID")
    SET (MK_BUILD_OS__MAX_FILE_PATH                 240)
    SET (MK_BUILD_OS__ANDROID                       1)
    SET (MK_BUILD__OS_TEXT_WIDE                     0)

ENDIF ()

IF ("${MK_BUILD__OS_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "MUST SELECT AN OPERATING SYSTEM INTERFACE")
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgBUILD_OS__${MK_BUILD__OS_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_OS=${MK_BUILD__OS_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_OS__MAX_FILE_PATH=${MK_BUILD_OS__MAX_FILE_PATH})

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} ${MK_BUILD__OS_NAME}")
STRING (TOLOWER ${MK_BUILD__OS_NAME}            MK_BUILD__OS_PATH)
SET (MK_BUILD__TARGET_DIRECTORY                 "${MK_BUILD__TARGET_DIRECTORY}_${MK_BUILD__OS_PATH}")

# Universal Package
IF ("${MK_BUILD__UNIVERSAL}" STREQUAL "UWP")
    IF (NOT WINDOWS_STORE)
        MESSAGE(FATAL_ERROR "PLATFORM UWP SELECTED BUT WINDOWS_STORE NOT ENABLED")
    ENDIF ()
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
    SET (MK_BUILD__TARGET_DIRECTORY                 "${MK_BUILD__TARGET_DIRECTORY}_${MK_BUILD__UNIVERSAL_PATH}")
ELSE ()
    SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} -")
ENDIF ()


# Target Device
IF ("${MK_BUILD__DEVICE}" STREQUAL "DESKTOP")
    SET (MK_BUILD__DEVICE_NAME                      "DESKTOP")

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

ADD_COMPILE_DEFINITIONS (TgBUILD_DEVICE__${MK_BUILD__DEVICE_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_DEVICE=${MK_BUILD__DEVICE_NAME})

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} ${MK_BUILD__DEVICE_NAME}")
STRING (TOLOWER ${MK_BUILD__DEVICE_NAME}        MK_BUILD__DEVICE_PATH)
SET (MK_BUILD__TARGET_DIRECTORY                 "${MK_BUILD__TARGET_DIRECTORY}_${MK_BUILD__DEVICE_PATH}")

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
    SET (MK_BUILD__GRAPHICS_NAME                    "OGES")
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

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} [${MK_BUILD__GRAPHICS_NAME}]")
STRING (TOLOWER ${MK_BUILD__GRAPHICS_NAME}      MK_BUILD__GRAPHICS_PATH)
SET (MK_BUILD__TARGET_DIRECTORY                 "${MK_BUILD__TARGET_DIRECTORY}_${MK_BUILD__GRAPHICS_PATH}")



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

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} [${MK_BUILD__AUDIO_NAME}]")
STRING (TOLOWER ${MK_BUILD__AUDIO_NAME}         MK_BUILD__AUDIO_PATH)
SET (MK_BUILD__TARGET_DIRECTORY                 "${MK_BUILD__TARGET_DIRECTORY}_${MK_BUILD__AUDIO_PATH}")




# ========================================================================================================================================================================================================
#  Configuration for Hardware
# ========================================================================================================================================================================================================

SET (MK_BUILD__HARDWARE_NAME                    "")
SET (MK_BUILD__HARDWARE__IMPLEMENTATION         0)
SET (MK_BUILD__HARDWARE__POINTER_SIZE           0)
SET (MK_BUILD__HARDWARE__WORDSIZE               0)

IF ("${MK_BUILD__TARGET_HARDWARE}" STREQUAL "C17_A64")
    SET (MK_BUILD__HARDWARE_NAME                    "C17_A64")
    SET (MK_BUILD__HARDWARE__POINTER_SIZE           8)
    SET (MK_BUILD__HARDWARE__WORDSIZE               8)
    SET (MK_BUILD__HARDWARE__X64                    FALSE)
    SET (MK_BUILD__HARDWARE__A64                    TRUE)
ELSEIF ("${MK_BUILD__TARGET_HARDWARE}" STREQUAL "C17_X64")
    SET (MK_BUILD__HARDWARE_NAME                    "C17_X64")
    SET (MK_BUILD__HARDWARE__POINTER_SIZE           8)
    SET (MK_BUILD__HARDWARE__WORDSIZE               8)
    SET (MK_BUILD__HARDWARE__X64                    TRUE)
    SET (MK_BUILD__HARDWARE__A64                    FALSE)
ENDIF ()

IF ("${MK_BUILD__HARDWARE_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "MUST HAVE A TARGET HARDWARE ARCHITECTURE (${MK_BUILD__TARGET_HARDWARE})")
ENDIF ()

ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE__${MK_BUILD__HARDWARE_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE=${MK_BUILD__HARDWARE_NAME})
ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE__POINTER_SIZE=${MK_BUILD__HARDWARE__POINTER_SIZE})
ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE__WORDSIZE=${MK_BUILD__HARDWARE__WORDSIZE})
ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE__CONSTRUCTIVE_INTERFERENCE_SIZE=${MK_BUILD__HARDWARE__CONSTRUCTIVE_INTERFERENCE_SIZE})
ADD_COMPILE_DEFINITIONS (TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE=${MK_BUILD__HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE})

SET (MK_PROJECT_NAME                            "${MK_PROJECT_NAME} [${MK_BUILD__HARDWARE_NAME}]")
STRING (TOLOWER ${MK_BUILD__HARDWARE_NAME}      MK_BUILD__HARDWARE_PATH)
SET (MK_BUILD__TARGET_DIRECTORY                 "${MK_BUILD__TARGET_DIRECTORY}_${MK_BUILD__HARDWARE_PATH}")



# ========================================================================================================================================================================================================
# Text Literal Format
# ========================================================================================================================================================================================================

IF (MK_BUILD__OS_TEXT_WIDE)
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

    CONFIGURE_FILE( ${GIT_ROOT_PATH}/cmake/directory.build.props ${CMAKE_BINARY_DIR}/directory.build.props COPYONLY )

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

    SET(CMAKE_XCODE_ATTRIBUTE_GCC_C_LANGUAGE_STANDARD                       C17 )
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
        ${GIT_ROOT_PATH}/teikitu_ide/WorkspaceSettings.xcsettings
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.xcodeproj/project.xcworkspace/xcuserdata/$ENV{USER}.xcuserdatad/WorkspaceSettings.xcsettings
        COPYONLY
    )

ELSEIF (MK_IDE__UNIX_MAKEFILES)
    SET (MK_IDE_NAME                                UNIX_MAKEFILES)

ELSEIF (MK_IDE__NINJA)
    SET (MK_IDE_NAME                                NINJA)
ENDIF ()

IF ("${MK_IDE_NAME}" STREQUAL "")
    MESSAGE(FATAL_ERROR "UNSUPPORTED IDE: " ${CMAKE_GENERATOR})
ENDIF ()

# Turn on folder usage
set_property(GLOBAL PROPERTY USE_FOLDERS ON)




# ========================================================================================================================================================================================================
#  Configuration Types
# ========================================================================================================================================================================================================

SET (MK_COMPILE__TYPE                         "")

STRING (TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_LOWER)

IF ("${CMAKE_BUILD_TYPE_LOWER}" STREQUAL "release")
    SET (MK_COMPILE__TYPE                         "RELEASE")
ELSEIF ("${CMAKE_BUILD_TYPE_LOWER}" STREQUAL "final")
    SET (MK_COMPILE__TYPE                         "FINAL")
ELSEIF ("${CMAKE_BUILD_TYPE_LOWER}" STREQUAL "tools_debug")
    SET (MK_COMPILE__TYPE                         "TOOLS_DEBUG")
ELSEIF ("${CMAKE_BUILD_TYPE_LOWER}" STREQUAL "tools_release")
    SET (MK_COMPILE__TYPE                         "TOOLS_RELEASE")
ELSEIF ("${CMAKE_BUILD_TYPE_LOWER}" STREQUAL "debug")
    SET (MK_COMPILE__TYPE                         "DEBUG")
ELSE ()
    MESSAGE(FATAL_ERROR "UNKNOWN BUILD TYPE: " ${CMAKE_BUILD_TYPE})
ENDIF ()

SET (CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
SET (MK_COMPILE__TYPE__${MK_COMPILE__TYPE} 1)

# Compiler Flags for Configuration

ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Debug>:TGS_DEBUG>)
ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Release>:TGS_RELEASE>)
ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Final>:TGS_FINAL>)
ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Tools_Debug>:TGS_TOOLS>)
ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Tools_Debug>:TGS_TOOLS_DEBUG>)
ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Tools_Release>:TGS_TOOLS>)
ADD_COMPILE_DEFINITIONS ($<$<CONFIG:Tools_Release>:TGS_TOOLS_RELEASE>)
ADD_COMPILE_DEFINITIONS (TgBUILD_CONFIG=${MK_COMPILE__TYPE})

# Teikitu does not use the standard cmake configuration builds. This will map our configurations to a couple of the standard configurations that should be present in each external project.

IF (${CMAKE_BUILD_TYPE_LOWER} STREQUAL "debug")
    SET (CMAKE_BUILD_TYPE_EXTERNAL "DEBUG")
ELSE ()
    SET (CMAKE_BUILD_TYPE_EXTERNAL "RELEASE")
ENDIF ()

# Add the install directory to the prefix path, and for non multi config store add the build type to the path

GET_PROPERTY (isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
IF (NOT isMultiConfig)
    STRING (TOLOWER ${CMAKE_BUILD_TYPE_EXTERNAL}    CMAKE_BUILD_TYPE_EXTERNAL_PATH)
    SET (MK_BUILD__EXTERNAL_TARGET_DIRECTORY        "${MK_BUILD__TARGET_DIRECTORY}_${CMAKE_BUILD_TYPE_EXTERNAL_PATH}")
    SET (MK_BUILD__EXTERNAL_BUILD_DIRECTORY         "${GIT_ROOT_PATH}/teikitu_external/_build/${MK_BUILD__EXTERNAL_TARGET_DIRECTORY}/")
    SET (MK_BUILD__EXTERNAL_INSTALL_DIRECTORY       "${GIT_ROOT_PATH}/teikitu_external/_install/${MK_BUILD__EXTERNAL_TARGET_DIRECTORY}/")
    LIST (APPEND CMAKE_PREFIX_PATH                  "${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}")

    STRING (TOLOWER ${MK_COMPILE__TYPE}             MK_COMPILE__TYPE_PATH)
    SET (MK_BUILD__TARGET_DIRECTORY                 "${MK_BUILD__TARGET_DIRECTORY}_${MK_COMPILE__TYPE_PATH}")
    SET (MK_BUILD__BUILD_DIRECTORY                  "${GIT_ROOT_PATH}/teikitu_external/_build/${MK_BUILD__TARGET_DIRECTORY}/")
    SET (MK_BUILD__INSTALL_DIRECTORY                "${GIT_ROOT_PATH}/teikitu_external/_install/${MK_BUILD__TARGET_DIRECTORY}/")
    LIST (APPEND CMAKE_PREFIX_PATH                  "${MK_BUILD__INSTALL_DIRECTORY}")

    SET (MK_BUILD__RUNTIME_DIRECTORY                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
ELSE ()
    SET (MK_BUILD__EXTERNAL_BUILD_DIRECTORY         "${GIT_ROOT_PATH}/teikitu_external/_build/${MK_BUILD__TARGET_DIRECTORY}/")
    SET (MK_BUILD__EXTERNAL_INSTALL_DIRECTORY       "${GIT_ROOT_PATH}/teikitu_external/_install/${MK_BUILD__TARGET_DIRECTORY}/")
    SET (MK_BUILD__BUILD_DIRECTORY                  "${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}")
    SET (MK_BUILD__INSTALL_DIRECTORY                "${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}")
    LIST (APPEND CMAKE_PREFIX_PATH                  "${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}")
    SET (MK_BUILD__RUNTIME_DIRECTORY                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE_EXTERNAL}")
ENDIF ()




# ========================================================================================================================================================================================================
#  Compiler Flags
# ========================================================================================================================================================================================================

IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
    IF (MK_BUILD__HARDWARE__X64)
        ADD_COMPILE_OPTIONS (-march=x86-64-v2)
        ADD_COMPILE_OPTIONS (-mcx16) # Include support for 16B compare exchange
        ADD_COMPILE_OPTIONS (-msse4) # SSE4 Support, Released in CPUs from 2007/2008
    ELSEIF (MK_BUILD__HARDWARE__A64)
        IF (MK_BUILD_OS__ANDROID)
            SET (NDK_SYSROOT "${ANDROID_NDK}/toolchains/llvm/prebuilt/${ANDROID_HOST_TAG}/sysroot")
            SET (NDK_STL_INCLUDE "${ANDROID_NDK}/sources/cxx-stl/llvm-libc++/include")
            ADD_COMPILE_OPTIONS ("SHELL:-isystem \"${NDK_SYSROOT}/usr/include\"")
            ADD_COMPILE_OPTIONS ("SHELL:-isystem \"${NDK_SYSROOT}/usr/include/${CMAKE_LIBRARY_ARCHITECTURE}\"")
            ADD_COMPILE_OPTIONS ("$<$<COMPILE_LANGUAGE:CXX>:SHELL:-isystem \"${NDK_STL_INCLUDE}\">")
        ELSEIF (MK_BUILD_OS__POSIX)
            IF ("${MK_BUILD__DEVICE_NAME}" STREQUAL "DESKTOP")
                ADD_COMPILE_OPTIONS (--target=aarch64-apple-darwin)
            ELSEIF ("${MK_BUILD__DEVICE_NAME}" STREQUAL "APPLE_IPHONE")
                ADD_COMPILE_OPTIONS (--target=aarch64-apple-ios)
            ENDIF ()
        ELSEIF (MK_BUILD_OS__WINDOWS)
        ELSE ()
            MESSAGE (FATAL_ERROR "Unknown operating system")
        ENDIF ()
    ELSE ()
        MESSAGE (FATAL_ERROR "Unknown compile hardware target")
    ENDIF ()
ENDIF ()
