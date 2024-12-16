cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "SOUND" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )

# RELEASE - STUB Out Incomplete Modules
SET (MK_BUILD__RELEASE_MODULE_NAME "NO_IMPL")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# Minimal Module (Used in headless mode)

TGS_ADD_SOURCE_FILE( lib_none_source_files lib_none_header_files "NO_IMPL" "${MK_BUILD__RELEASE_MODULE_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (NONE) Sound - Data.c")
TGS_ADD_SOURCE_FILE( lib_none_source_files lib_none_header_files "NO_IMPL" "${MK_BUILD__RELEASE_MODULE_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (NONE) Sound - Module.c")
TGS_ADD_SOURCE_FILE( lib_none_source_files lib_none_header_files "NO_IMPL" "${MK_BUILD__RELEASE_MODULE_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (NONE) Sound - System.c")
TGS_ADD_SOURCE_FILE( lib_none_source_files lib_none_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Sound [PCH].c")

TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_header_files "NO_IMPL" "${MK_BUILD__RELEASE_MODULE_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (NONE) Sound - Internal.h")

TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Sound - Constants.h")
TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Sound - Data.h")
TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Sound - Type.h")

TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_sdk_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Sound.h")
TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_sdk_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 3 - Type.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# build library

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "${MK_BUILD__RELEASE_MODULE_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Sound - Data.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "${MK_BUILD__RELEASE_MODULE_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Sound - Module.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "${MK_BUILD__RELEASE_MODULE_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Sound - System.c")

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "${MK_BUILD__RELEASE_MODULE_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Sound - Internal.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #

# Headless (server) builds have a "NONE" Render Module. The minimum required set of files to maintain the build are used.

IF ("${MK_BUILD__RELEASE_MODULE_NAME}" STREQUAL "-")
    SET (lib_none_source_files ${lib_none_source_files} ${lib_source_files})
    SET (lib_none_header_files ${lib_none_header_files} ${lib_header_files})
    SET (lib_none_sdk_header_files ${lib_none_sdk_header_files} ${lib_sdk_header_files})
ENDIF()

SET (MK_BUILD__MODULE_LIB _Ring_3___TgS_SOUND)
ADD_LIBRARY (${MK_BUILD__MODULE_LIB} STATIC ${lib_none_source_files} ${lib_none_header_files} ${lib_none_sdk_header_files})
SET (PCH_INCLUDE_DEFAULT "TgS Sound - Internal.h")
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY ()
TGS_SET_STANDARD_LIBRARY_PROPERTIES (${MK_BUILD__MODULE_LIB} "${MK_BUILD_MODULE__SRC_DIR}" "TgS Sound [PCH]" ${PCH_INCLUDE_DEFAULT} lib_none_source_files lib_none_header_files lib_none_sdk_header_files)
TARGET_LINK_LIBRARIES(${MK_BUILD__MODULE_LIB} PUBLIC
    _Ring_0___TgS_COMMON
)
