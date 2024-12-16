cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "RENDER" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )

# HEADLESS Module Support
SET (MK_BUILD__GRAPHICS_GENEREIC "NO_IMPL")
IF (NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
    SET (MK_BUILD__GRAPHICS_GENEREIC ${MK_BUILD__GRAPHICS_NAME})
ENDIF ()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# Minimal Module (Used in headless mode)

TGS_ADD_SOURCE_FILE( lib_none_source_files lib_none_header_files "NO_IMPL" "${MK_BUILD__GRAPHICS_GENEREIC}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (NONE) Render - Data.c")
TGS_ADD_SOURCE_FILE( lib_none_source_files lib_none_header_files "NO_IMPL" "${MK_BUILD__GRAPHICS_GENEREIC}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (NONE) Render - Module.c")
TGS_ADD_SOURCE_FILE( lib_none_source_files lib_none_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Render [PCH].c")

TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_header_files "NO_IMPL" "${MK_BUILD__GRAPHICS_GENEREIC}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (NONE) Render - Internal.h")

TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Render - Constants.h")
TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Render - Data.h")
TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Render - Type.h")

TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_sdk_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Render.h")
TGS_ADD_HEADER_FILE( lib_none_source_files lib_none_sdk_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 3 - Type.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Render - Data.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Render - Module.c")

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Render - Debug - Console.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Render [Util].c")

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Render - Internal - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Render - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Render - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Render - Internal.h")

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Render - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Render - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Render - Type.h")

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Render.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 3 - Type.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# Specialization DX12

FOREACH (MK_LIST_ITEM__GRAPHICS_NAME IN LISTS MK_GENERATE_LIST__GRAPHICS_NAMES)
    TGS_ADD_HEADER_FILE( lib_api_source_files lib_api_header_files "${MK_LIST_ITEM__GRAPHICS_NAME}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__GRAPHICS_NAME}) Render - Internal.h")
ENDFOREACH ()

TGS_ADD_SOURCE_FILE (lib_none_api_source_files lib_none_api_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (API) Render [PCH].c")



# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# Specialization DX12

TGS_ADD_SOURCE_FILE( lib_api_source_files lib_api_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Render - Data.c")





# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #

# Headless (server) builds have a "NONE" Render Module. The minimum required set of files to maintain the build are used.

IF (NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
    SET (lib_none_api_source_files ${lib_none_api_source_files} ${lib_api_source_files})
    SET (lib_none_api_header_files ${lib_none_api_header_files} ${lib_api_header_files})
    SET (lib_none_sdk_api_header_files ${lib_none_sdk_api_header_files} ${lib_sdk_api_header_files})
    SET (lib_none_source_files ${lib_none_source_files} ${lib_source_files})
    SET (lib_none_header_files ${lib_none_header_files} ${lib_header_files})
    SET (lib_none_sdk_header_files ${lib_none_sdk_header_files} ${lib_sdk_header_files})

    SET (MK_BUILD__MODULE_API_LIB _Ring_3___TgS_RENDER__${MK_BUILD__GRAPHICS_NAME})
    SET (PCH_API_INCLUDE_DEFAULT "TgS (${MK_BUILD__GRAPHICS_NAME}) Render - Internal.h")
    ADD_LIBRARY (${MK_BUILD__MODULE_API_LIB} STATIC ${lib_none_api_source_files} ${lib_none_api_header_files} ${lib_none_sdk_api_header_files})
    TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY ("__${MK_BUILD__GRAPHICS_NAME}")
    TGS_SET_STANDARD_LIBRARY_PROPERTIES (${MK_BUILD__MODULE_API_LIB} "${MK_BUILD_MODULE__SRC_DIR}" "TgS (API) Render [PCH]" ${PCH_API_INCLUDE_DEFAULT} lib_none_api_source_files lib_none_api_header_files lib_none_sdk_api_header_files)

ELSE ()
    SET (MK_BUILD__MODULE_API_LIB "")
ENDIF ()

SET (MK_BUILD__MODULE_LIB _Ring_3___TgS_RENDER)
SET (PCH_INCLUDE_DEFAULT "TgS Render - Internal.h")
ADD_LIBRARY (${MK_BUILD__MODULE_LIB} STATIC ${lib_none_source_files} ${lib_none_header_files} ${lib_none_sdk_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY ()
TGS_SET_STANDARD_LIBRARY_PROPERTIES (${MK_BUILD__MODULE_LIB} "${MK_BUILD_MODULE__SRC_DIR}" "TgS Render [PCH]" ${PCH_INCLUDE_DEFAULT} lib_none_source_files lib_none_header_files lib_none_sdk_header_files)
TARGET_LINK_LIBRARIES(${MK_BUILD__MODULE_LIB} PUBLIC
    _Ring_0___TgS_COMMON
    _Ring_2___TgS_KERNEL
    ${MK_BUILD__MODULE_API_LIB}
)
