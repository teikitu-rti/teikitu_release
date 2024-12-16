cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
cmake_policy(SET CMP0015 NEW)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "PATH-AI" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library
SOURCE_GROUP ("" REGULAR_EXPRESSION .*)

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Path-AI [PCH].c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Path-AI - Data.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Path-AI - Module.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Path-AI - System.c")

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Path-AI - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Path-AI - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Path-AI - Data.h")

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Path-AI.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 0 - Type.h")

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Path-AI - Internal.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
ADD_LIBRARY(_Ring_0___TgS_PATH-AI STATIC ${lib_source_files} ${lib_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Path-AI - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES( _Ring_0___TgS_PATH-AI "${MK_BUILD_MODULE__SRC_DIR}" "TgS Path-AI [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files lib_sdk_header_files)
TARGET_LINK_LIBRARIES (_Ring_0___TgS_PATH-AI PUBLIC
    _Ring_0___TgS_COMMON
)
