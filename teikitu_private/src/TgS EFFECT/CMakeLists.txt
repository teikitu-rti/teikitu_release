cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
cmake_policy(SET CMP0015 NEW)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "EFFECT" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Module" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - AnimData.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Module" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - System.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Module" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Data.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Module" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Debug.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Module" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - File.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Module" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Module.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Module" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect [PCH].c")

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Render" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect -- Render.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Render" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Beam - Render.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Render" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Billboard - Render.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Render" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Decal - Render.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Render" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Emitter - Render.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Render" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - GIB - Render.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Render" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Glass - Render.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Render" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Liquid - Render.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Render" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Trail - Render.c")

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect -- Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Beam - Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Billboard - Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Decal - Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Emitter - Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - GIB - Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Glass - Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Light - Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Liquid - Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Post - Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Scene" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Trail - Scene.c")

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect -- Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Beam - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Billboard - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Decal - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Emitter - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Emitter - Update - Particle.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - GIB - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Glass - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Group - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Light - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Liquid - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Post - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Sound - Update.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Update" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Trail - Update.c")

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Client" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect -- Client.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Effect Client" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Client - Effect.c")



TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Effect - Effect [INC].h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Effect - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Effect - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Effect - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Effect.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 4 - Type.h")

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Internal - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Internal.h")

TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "SDK/Inline Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Internal.inl")
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "SDK/Inline Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Effect - Render.inl")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
ADD_LIBRARY(_Ring_4___TgS_EFFECT STATIC ${lib_source_files} ${lib_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET (PCH_INCLUDE_DEFAULT "TgS Effect - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES (_Ring_4___TgS_EFFECT "${MK_BUILD_MODULE__SRC_DIR}" "TgS Effect [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files lib_sdk_header_files)
TARGET_LINK_LIBRARIES (_Ring_4___TgS_EFFECT PUBLIC 
    _Ring_0___TgS_COMMON
    _Ring_0___TgS_COLLISION
    _Ring_3___TgS_ANIMATION
    _Ring_3___TgS_RENDER
    _Ring_3___TgS_SOUND
    _Ring_4___TgS_SET
    _Ring_U___TgS_UTILITY
)

#IF (NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
#    ADD_LIBRARY(_Ring_4___TgS_EFFECT__GPU STATIC ${lib_gpu_source_files} ${lib_gpu_header_files})
#    TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__GPU")
#    SET( PCH_GPU_INCLUDE_DEFAULT "TgS Effect - Internal [GPU].h")
#    TGS_SET_STANDARD_LIBRARY_PROPERTIES( _Ring_4___TgS_EFFECT__GPU "${MK_BUILD_MODULE__SRC_DIR}" "TgS Effect [GPU] [PCH]" ${PCH_GPU_INCLUDE_DEFAULT} lib_gpu_source_files lib_gpu_header_files )##
#
#    SET(MK_BUILD__GRAPHICS_IMPL_LIB _Ring_4___TgS_EFFECT__GPU__${MK_BUILD__GRAPHICS_NAME})
#    ADD_LIBRARY(${MK_BUILD__GRAPHICS_IMPL_LIB} STATIC ${lib_api_gpu_source_files} ${lib_api_gpu_header_files})
#    TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__GPU__${MK_BUILD__GRAPHICS_NAME}")
#    SET( PCH_GPU_INCLUDE_DEFAULT "TgS (${MK_BUILD__GRAPHICS_NAME}) Effect - Internal [GPU].h")
#    TGS_SET_STANDARD_LIBRARY_PROPERTIES( ${MK_BUILD__GRAPHICS_IMPL_LIB} "${MK_BUILD_MODULE__SRC_DIR}" "TgS (${MK_BUILD__GRAPHICS_NAME}) Effect [GPU] [PCH]" ${PCH_GPU_INCLUDE_DEFAULT} lib_api_gpu_source_files lib_api_gpu_header_files )
#ENDIF()
