cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "KERNEL" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )

# Special case for "headless" graphics/rendering: NONE
SET (MK_BUILD__GRAPHICS_GENEREIC "NO_IMPL")
IF (NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
    SET (MK_BUILD__GRAPHICS_GENEREIC ${MK_BUILD__GRAPHICS_NAME})
ENDIF ()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# build library

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Data.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Module.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - System.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [PCH].c")

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/File" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - File System.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/File" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - File Job.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/File" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - File IO.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/File" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - File System - HDD.c")

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Internal - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Internal.h")

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Errors.TgS")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 2 - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Kernel.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# library platform specific files

FOREACH (MK_LIST_ITEM__OS_NAME IN LISTS MK_GENERATE_LIST__OS_NAMES)
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Data.c" )
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Module.c" )
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Configuration.c")
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Link Test.c")
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - System.c")
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Unit Test.c")
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel [PCH].c")

    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Internal - Data.h")
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Internal - Type.h")
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Internal.h")

    TGS_ADD_HEADER_FILE( lib_os_source_files lib_sdk_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Constants.h")
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_sdk_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Type.h")
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_sdk_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel.h")

ENDFOREACH ()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Constants.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Data.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Debug [Console].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Debug [Geom-Text-UI].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Debug.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Module.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [DEVC].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [EXEC].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [HOST].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [SWAP].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Unit Test.c")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Common].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Font] [ROM].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Shader].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Cube].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Image].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Volume].c")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [BMP].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [DDS].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [GIF].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [JPG].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [PNG].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [TGA].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [TIF].c")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "${MK_BUILD__GRAPHICS_GENEREIC}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource LIB" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource LIB [Common].c")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] [PCH].c")

TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal [EXT].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal.h")

TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Constants.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [INC].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [HLSL] [Constants].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [HLSL] [Data].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [HLSL] [Vertex].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Type.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] [EXT].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Kernel [GPU].h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - Specialization Generic

FOREACH (MK_LIST_ITEM__GRAPHICS_NAME IN LISTS MK_GENERATE_LIST__GRAPHICS_NAMES)
    TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "${MK_LIST_ITEM__GRAPHICS_NAME}" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__GRAPHICS_NAME}) Kernel [GPU] - Internal.h")
ENDFOREACH ()

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (API) Kernel [GPU] [PCH].c")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - Specialization DX12

TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Constants.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Debug.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Type.h")

TGS_ADD_INCSRC_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Inline Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal.inl")

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Link Test.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Constants.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Debug [Geom-Text-UI].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Debug.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Data.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Module.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Context] [DEVC].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Context] [EXEC].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Context] [HOST].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Context] [SWAP].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Enumeration].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Select].c")

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Resource [Data Buffer].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Resource [Pipeline].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Resource [Texture].c")

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12-WINDOWS" "${MK_BUILD__GRAPHICS_NAME}-${MK_BUILD__OS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12-WINDOWS) Kernel [GPU] - Module.c")

TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_sdk_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (DX12) Kernel [GPU] - Constants.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_sdk_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (DX12) Kernel [GPU] - Type.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_sdk_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "Public" "${MK_BUILD_MODULE__INC_DIR}/TgS (DX12) Kernel [GPU].h")

TGS_SOURCE_APPEND_GNU_COMPILER_OPTION( "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Context] [HOST].c" "Wno-invalid-token-paste")


# DX12 HLSL Files

TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Particle_00_PS_FX.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Particle_01_PS_FX.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Geom_00_PS_P.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Geom_01_PS_PC.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Geom_02_PS_PNC.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Geom_02I_PS_PNC.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Geom_03_PS_PNC.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Line_PS_PC.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_UI_PS_UI.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_UI_Text_PS_UIT.vs.hlsl")

TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_FX.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_UI.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_UIG.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_UIT.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_P.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_PN.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_PC.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_PCG.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_PNC.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Test_PNC.ps.hlsl")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Common.hlsli")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - Specialization Vulkan (VLKN)


TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "VULKAN-WINDOWS" "${MK_BUILD__GRAPHICS_NAME}-${MK_BUILD__OS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (VULKAN-WINDOWS) Kernel [GPU] - Module.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "VULKAN" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (VULKAN) Kernel [GPU] [API].c")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "VULKAN" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (VULKAN) Kernel [GPU] - Internal.h")

TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_sdk_api_gpu_header_files "VULKAN" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (VULKAN) Kernel [GPU] - Constants.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - Specialization Vulkan (METAL)


TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "METAL" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (METAL) Kernel [GPU] [API].c")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "METAL" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (METAL) Kernel [GPU] - Internal.h")

TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_sdk_api_gpu_header_files "METAL" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (METAL) Kernel [GPU] - Constants.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - Reference

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (REF) Kernel [GPU] [API].c")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_sdk_api_gpu_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (REF) Kernel [GPU] - Constants.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - DirectX Headers

FILE(GLOB_RECURSE children "${GIT_ROOT_PATH}/teikitu_external/__directx_agile/build/native/include/*")
FOREACH(child ${children})
    TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/DirectX" "${child}")
ENDFOREACH()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #

# KERNEL GPU (GRAPHICS AND COMPUTE) API SPECIALIZATION

SET(MK_BUILD__GRAPHICS_IMPL_LIB _Ring_2___TgS_KERNEL__GPU__${MK_BUILD__GRAPHICS_NAME})
ADD_LIBRARY (${MK_BUILD__GRAPHICS_IMPL_LIB} STATIC ${lib_api_gpu_source_files} ${lib_api_gpu_header_files} ${lib_sdk_api_gpu_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY ("__GPU__${MK_BUILD__GRAPHICS_NAME}")
SET (PCH_GPU_INCLUDE_DEFAULT "TgS (${MK_BUILD__GRAPHICS_NAME}) Kernel [GPU] - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES (${MK_BUILD__GRAPHICS_IMPL_LIB} "${MK_BUILD_MODULE__SRC_DIR}" "TgS (API) Kernel [GPU] [PCH]" ${PCH_GPU_INCLUDE_DEFAULT} lib_api_gpu_source_files lib_api_gpu_header_files lib_sdk_api_gpu_header_files)
IF (NOT EXISTS "${MK_BUILD_MODULE__SRC_DIR}/${MK_COMPILE__TYPE}")
    FILE (MAKE_DIRECTORY "${MK_BUILD_MODULE__SRC_DIR}/${MK_COMPILE__TYPE}")
    MESSAGE( STATUS "Created directory: ${MK_BUILD_MODULE__SRC_DIR}/${MK_COMPILE__TYPE}")
ENDIF ()
TARGET_INCLUDE_DIRECTORIES (${MK_BUILD__GRAPHICS_IMPL_LIB} PRIVATE "${MK_BUILD_MODULE__SRC_DIR}/${MK_COMPILE__TYPE}")

IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "DX12")
    # DirectX Headers
    TARGET_LINK_LIBRARIES (${MK_BUILD__GRAPHICS_IMPL_LIB} PUBLIC Microsoft::DirectX-Headers)
    TARGET_LINK_LIBRARIES (${MK_BUILD__GRAPHICS_IMPL_LIB} PUBLIC Microsoft::DirectX-Guids)
    TARGET_COMPILE_DEFINITIONS (${MK_BUILD__GRAPHICS_IMPL_LIB} PUBLIC USING_DIRECTX_HEADERS)

    # DirectX Agile SDK
    TARGET_INCLUDE_DIRECTORIES(${MK_BUILD__GRAPHICS_IMPL_LIB} BEFORE PUBLIC "${GIT_ROOT_PATH}/teikitu_external/__directx_agile/build/native/include")

    # DirectX Agile SDK - D3D12Core
    TGS_ADD_DLL_NO_LIB ("D3D12Core")
    SET_PROPERTY (TARGET "D3D12Core" PROPERTY IMPORTED_LOCATION "${GIT_ROOT_PATH}/teikitu_external/__directx_agile/build/native/bin/x64/D3D12Core.dll")
    TARGET_LINK_LIBRARIES (${MK_BUILD__GRAPHICS_IMPL_LIB} PRIVATE "D3D12Core")
    SET_PROPERTY(TARGET "D3D12CoreLIB" PROPERTY PROJECT_LABEL "DX12-DLL Core")
    SET_TARGET_PROPERTIES("D3D12CoreLIB" PROPERTIES FOLDER "External Dependencies")

    # DirectX Agile SDK - D3D12SDKLayers
    TGS_ADD_DLL_NO_LIB ("d3d12SDKLayers")
    SET_PROPERTY (TARGET "d3d12SDKLayers" PROPERTY IMPORTED_LOCATION "${GIT_ROOT_PATH}/teikitu_external/__directx_agile/build/native/bin/x64/d3d12SDKLayers.dll")
    TARGET_LINK_LIBRARIES (${MK_BUILD__GRAPHICS_IMPL_LIB} PRIVATE "d3d12SDKLayers")
    SET_PROPERTY(TARGET "d3d12SDKLayersLIB" PROPERTY PROJECT_LABEL "DX12-DLL SDK Layers")
    SET_TARGET_PROPERTIES("d3d12SDKLayersLIB" PROPERTIES FOLDER "External Dependencies")

    # DirectX Agile SDK - D3D12SDKLayers
    TGS_ADD_DLL_NO_LIB ("WinPixEventRuntime")
    SET_PROPERTY (TARGET "WinPixEventRuntime" PROPERTY IMPORTED_LOCATION "${GIT_ROOT_PATH}/teikitu_external/__win_pix_event_runtime/bin/x64/WinPixEventRuntime.dll")
    TARGET_LINK_LIBRARIES (${MK_BUILD__GRAPHICS_IMPL_LIB} PRIVATE "WinPixEventRuntime")
    SET_PROPERTY(TARGET "WinPixEventRuntimeLIB" PROPERTY PROJECT_LABEL "Windows PIX")
    SET_TARGET_PROPERTIES("WinPixEventRuntimeLIB" PROPERTIES FOLDER "External Dependencies")
ENDIF ()


# KERNEL GPU

SET(MK_BUILD__MODULE_GPU_LIB _Ring_2___TgS_KERNEL__GPU)
ADD_LIBRARY (${MK_BUILD__MODULE_GPU_LIB} STATIC ${lib_gpu_source_files} ${lib_gpu_header_files} ${lib_sdk_gpu_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY ("__GPU")
SET (PCH_GPU_INCLUDE_DEFAULT "TgS Kernel [GPU] - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES (${MK_BUILD__MODULE_GPU_LIB} "${MK_BUILD_MODULE__SRC_DIR}" "TgS Kernel [GPU] [PCH]" ${PCH_GPU_INCLUDE_DEFAULT} lib_gpu_source_files lib_gpu_header_files lib_sdk_gpu_header_files)
TARGET_INCLUDE_DIRECTORIES (${MK_BUILD__MODULE_GPU_LIB} PUBLIC "${TIFF_INCLUDE_DIRS}")


# KERNEL OS SPECIALIZATION

ADD_LIBRARY (_Ring_2___TgS_KERNEL__OS STATIC ${lib_os_source_files} ${lib_os_header_files} ${lib_sdk_os_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY ("__OS")
SET (PCH_OS_INCLUDE_DEFAULT "TgS (${MK_BUILD__OS_NAME}) Kernel - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES (_Ring_2___TgS_KERNEL__OS "${MK_BUILD_MODULE__SRC_DIR}" "TgS (${MK_BUILD__OS_NAME}) Kernel [PCH]" ${PCH_OS_INCLUDE_DEFAULT} lib_os_source_files lib_os_header_files lib_sdk_os_header_files)


# KERNEL BASE

ADD_LIBRARY (_Ring_2___TgS_KERNEL STATIC ${lib_source_files} ${lib_header_files} ${lib_sdk_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY ()
SET (PCH_INCLUDE_DEFAULT "TgS Kernel - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES (_Ring_2___TgS_KERNEL "${MK_BUILD_MODULE__SRC_DIR}" "TgS Kernel [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files lib_sdk_header_files)
TARGET_INCLUDE_DIRECTORIES (_Ring_2___TgS_KERNEL PRIVATE ${TIFF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES (_Ring_2___TgS_KERNEL PUBLIC
    ${TIFF_LIBRARIES}
    _Ring_0___TgS_COMMON
    _Ring_2___TgS_KERNEL__OS
    _Ring_2___TgS_KERNEL__GPU
    _Ring_2___TgS_KERNEL__GPU__${MK_BUILD__GRAPHICS_NAME}
)



#ADD_LIBRARY(_Ring_X___TgS_KERNEL__FILE_TEST__ STATIC ${lib_api_gpu_source_files} ${lib_api_gpu_header_files} ${lib_gpu_source_files} ${lib_gpu_header_files} ${lib_os_source_files} ${lib_os_header_files} ${lib_source_files} ${lib_header_files})
