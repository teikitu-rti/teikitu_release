# 015482FC-A4BD-4E1C-AE49-A30E5728D73A

# ========================================================================================================================================================================================================
#  CONFIGURATION
# ========================================================================================================================================================================================================

# Supported Platforms, Hardware, and Compilers - Used to include inactive files into supported IDEs #=====================================================================================================

SET (MK_GENERATE_LIST__COMPILER_NAMES "APPLE" "CLANG" "MSVC")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__COMPILER_NAMES)

SET (MK_GENERATE_LIST__HARDWARE_NAMES "C17_X64" "C17_A64")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__HARDWARE_NAMES)

SET (MK_GENERATE_LIST__THREAD_NAMES "POSIX" "WINDOWS")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__THREAD_NAMES)

SET (MK_GENERATE_LIST__UNIVERSAL_NAMES "APPLE")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__UNIVERSAL_NAMES)

SET (MK_GENERATE_LIST__OS_NAMES "WINDOWS" "POSIX" "ANDROID" "MAC" "IOS")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__OS_NAMES)

SET (MK_GENERATE_LIST__DEVICE_NAMES "DESKTOP" "APPLE_MAC" "APPLE_IPHONE" "APPLE_TV" "APPLE_WATCH" "XB4" "PS5")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__DEVICE_NAMES)

SET (MK_GENERATE_LIST__GRAPHICS_NAMES "NONE" "REF" "VULKAN")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__GRAPHICS_NAMES)

SET (MK_GENERATE_LIST__AUDIO_NAMES "NONE" "XAUDIO2")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__AUDIO_NAMES)

# LIBRARAY DEPENDENCY GROUPS =============================================================================================================================================================================

SET (_Ring_0___COMMON_LIBS _Ring_0___TgS_COMMON _Ring_0___TgS_COLLISION _Ring_0___TgS_PARTITION)
SET (_Ring_2___COMMON_LIBS _Ring_2___TgS_KERNEL _Ring_U___TgS_UTILITY)
SET (_Ring_3___COMMON_LIBS _Ring_3___TgS_ANIMATION _Ring_3___TgS_INPUT _Ring_3___TgS_RENDER _Ring_3___TgS_SOUND)
SET (_Ring_4___COMMON_LIBS _Ring_4___TgS_OBJECT _Ring_4___TgS_SCRIPT _Ring_4___TgS_SET)

SET (_TEIKITU_LIB__MP_SERVER    ${_Ring_0___COMMON_LIBS}            _Ring_0___TgS_PATH-AI             ${_Ring_2___COMMON_LIBS}            _Ring_3___TgS_PHYSICS_MP_SERVER   ${_Ring_4___COMMON_LIBS}
                                _Ring_5___TgS_EXECUTE_MP_SERVER)

SET (_TEIKITU_LIB__MP_CLIENT    ${_Ring_0___COMMON_LIBS}            ${_Ring_2___COMMON_LIBS}            ${_Ring_3___COMMON_LIBS}            ${_Ring_4___COMMON_LIBS}            _Ring_3___TgS_PHYSICS_MP_CLIENT
                                _Ring_4___TgS_EFFECT              _Ring_5___TgS_EXECUTE_MP_CLIENT   )

SET (_TEIKITU_LIB__SP           ${_Ring_0___COMMON_LIBS}            ${_Ring_2___COMMON_LIBS}            ${_Ring_3___COMMON_LIBS}            _Ring_3___TgS_PHYSICS_SP          _Ring_4___TgS_EFFECT
                                ${_Ring_4___COMMON_LIBS}            _Ring_5___TgS_EXECUTE_SP          )


# ========================================================================================================================================================================================================
#  PACKAGES
# ========================================================================================================================================================================================================

MESSAGE(DEBUG "MK_BUILD__EXTERNAL_INSTALL_DIRECTORY: ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}")

LIST (APPEND CMAKE_MODULE_PATH "${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}")
LIST (APPEND CMAKE_MODULE_PATH "${GIT_ROOT_PATH}/cmake")
LIST (APPEND CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules")
LIST (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

#FOREACH (entry IN LISTS CMAKE_MODULE_PATH)
#    MESSAGE ("CMAKE_MODULE_PATH: ${entry}")
#ENDFOREACH ()

LIST (APPEND CMAKE_PREFIX_PATH "${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}")
LIST (REMOVE_DUPLICATES CMAKE_PREFIX_PATH)

#FOREACH (entry IN LISTS CMAKE_PREFIX_PATH)
#    MESSAGE ("CMAKE_PREFIX_PATH: ${entry}")
#ENDFOREACH ()

LIST (APPEND CMAKE_FIND_ROOT_PATH "${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}")
LIST (REMOVE_DUPLICATES CMAKE_FIND_ROOT_PATH)

#FOREACH (entry IN LISTS CMAKE_FIND_ROOT_PATH)
#    MESSAGE ("CMAKE_FIND_ROOT_PATH: ${entry}")
#ENDFOREACH ()


FIND_PACKAGE (MIMALLOC CONFIG REQUIRED GLOBAL)
IF (MIMALLOC_FOUND)
    MESSAGE(VERBOSE "MIMALLOC_FOUND: ${MIMALLOC_FOUND}")
ELSE ()
    MESSAGE(SEND_ERROR "MIMALLOC_FOUND: ${MIMALLOC_FOUND}")
ENDIF ()

FIND_PATH (TIFF_INCLUDE_DIRS NAMES tiff.h REQUIRED GLOBAL)
MESSAGE (STATUS "TIFF_INCLUDE_DIRS: ${TIFF_INCLUDE_DIRS}")
IF (MK_COMPILER_FRONTEND__MSVC AND CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    FIND_LIBRARY (TIFF_LIBRARIES NAMES tiffd REQUIRED GLOBAL)
ELSE ()
    FIND_LIBRARY (TIFF_LIBRARIES NAMES tiff REQUIRED GLOBAL)
ENDIF ()
MESSAGE (STATUS "TIFF_LIBRARIES: ${TIFF_LIBRARIES}")

IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "DX12")
    FIND_PACKAGE (directx-headers CONFIG REQUIRED QUIET)
ENDIF ()

MESSAGE (STATUS "MK_BUILD__GRAPHICS_NAME: ${MK_BUILD__GRAPHICS_NAME}")
IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "VULKAN")
    set(VULKAN_COMPONENTS
        "glslc"
        "glslangValidator"
        "glslang"
        "shaderc_combined"
        "SPIRV-Tools"
    )
    FIND_PACKAGE (Vulkan COMPONENTS ${VULKAN_COMPONENTS} REQUIRED QUIET)
    IF (Vulkan_FOUND)
        MESSAGE(VERBOSE "Vulkan_FOUND: ${Vulkan_FOUND}")
    ELSE ()
        MESSAGE(SEND_ERROR "Vulkan_FOUND: ${Vulkan_FOUND}")
    ENDIF ()
    MESSAGE (STATUS "Vulkan_INCLUDE_DIRS: ${Vulkan_INCLUDE_DIRS}")
    FIND_PACKAGE (volk CONFIG REQUIRED)
ENDIF ()


IF (MK_BUILD_OS__MAC OR MK_BUILD_OS__IOS)
    ENABLE_LANGUAGE (OBJC OBJCXX)
    FIND_LIBRARY (FOUNDATION_LIBRARY Foundation)
    FIND_LIBRARY (APPKIT_LIBRARY AppKit)
    FIND_LIBRARY (COREGRAPHICS_LIBRARY CoreGraphics)
    FIND_LIBRARY (COCOA_LIBRARY Cocoa)
    FIND_LIBRARY (IOSURFACE_LIBRARY IOSurface)
    FIND_LIBRARY (METAL_LIBRARY Metal)
    FIND_LIBRARY (METALKIT_LIBRARY MetalKit)
    FIND_LIBRARY (QUARTZCORE_LIBRARY QuartzCore)
    FIND_LIBRARY (AVFOUNDATION_LIBRARY AVFoundation)
    FIND_LIBRARY (COREMEDIA_LIBRARY CoreMedia)
    FIND_LIBRARY (COREAUDIO_LIBRARY CoreAudio)
    FIND_LIBRARY (AUDIOUNIT_LIBRARY AudioUnit)
    FIND_LIBRARY (CORESERVICES_LIBRARY CoreServices)
    FIND_LIBRARY (SECURITY_LIBRARY Security)
    FIND_LIBRARY (SYSTEMCONFIGURATION_LIBRARY SystemConfiguration)
ENDIF ()
