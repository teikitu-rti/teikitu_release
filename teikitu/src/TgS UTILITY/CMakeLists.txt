cmake_minimum_required(VERSION 3.4)
cmake_policy(VERSION 3.4)
cmake_policy(SET CMP0015 NEW)

CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../inc" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../inc/TgS UTILITY" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../src/TgS UTILITY" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Utility [PCH].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Utility - Data.c" )

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Utility - Constants.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Utility - Type.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Utility - Data.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Utility.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 3 - Type.h" )

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Utility - Internal.h" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
ADD_LIBRARY("_Ring_U___TgS_UTILITY" STATIC ${lib_source_files} ${lib_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Utility - Internal.h")
TGS_SET_STANDARD_PROPERTIES( "_Ring_U___TgS_UTILITY" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Utility [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files )
