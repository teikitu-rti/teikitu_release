cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "UTILITY" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Utility [PCH].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Utility - Data.c" )

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Utility - Constants.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Utility - Type.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Utility - Data.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Utility.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 3 - Type.h" )

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Utility - Internal.h" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
ADD_LIBRARY(_Ring_U___TgS_UTILITY STATIC ${lib_source_files} ${lib_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Utility - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES( _Ring_U___TgS_UTILITY "${MK_BUILD_MODULE__SRC_DIR}" "TgS Utility [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files lib_sdk_header_files)
TARGET_LINK_LIBRARIES (_Ring_U___TgS_UTILITY PUBLIC
    _Ring_0___TgS_COMMON
)
