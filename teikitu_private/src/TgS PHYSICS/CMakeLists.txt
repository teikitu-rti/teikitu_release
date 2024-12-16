cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "PHYSICS" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library
SOURCE_GROUP ("" REGULAR_EXPRESSION .*)

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics [PCH].c")

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Scene.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - System [Solver].c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - System.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Body.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Constraints [Contact].c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Constraints [Fixed].c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Constraints.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Data [Accessors].c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Data.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Debug.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Form.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Mass.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Material.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Module.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Motors.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Ragdoll.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Generic Functions.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Visualize.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - World.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - World [Collide].c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - World [Problem Set].c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - World [Simulation].c")

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Internal - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Internal - Macro.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Internal.h")

TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "SDK/Inline Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics - Internal.inl")

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Physics - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Physics - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Physics - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Physics - Macro.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Physics - Object [INC].h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Physics.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 3 - Type.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
SET( PCH_INCLUDE_DEFAULT "TgS Physics - Internal.h")

ADD_LIBRARY(_Ring_3___TgS_PHYSICS_MP_SERVER STATIC ${lib_source_files} ${lib_header_files} ${lib_sdk_header_files})
TARGET_COMPILE_DEFINITIONS( _Ring_3___TgS_PHYSICS_MP_SERVER PRIVATE TgBUILD_FEATURE__SERVER)
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("_MP_SERVER")
TGS_SET_STANDARD_LIBRARY_PROPERTIES( _Ring_3___TgS_PHYSICS_MP_SERVER "${MK_BUILD_MODULE__SRC_DIR}" "TgS Physics [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files lib_sdk_header_files)
TARGET_LINK_LIBRARIES(_Ring_3___TgS_PHYSICS_MP_SERVER PUBLIC
    _Ring_0___TgS_COMMON
    _Ring_0___TgS_COLLISION
    _Ring_0___TgS_PARTITION
)

ADD_LIBRARY(_Ring_3___TgS_PHYSICS_MP_CLIENT STATIC ${lib_source_files} ${lib_header_files} ${lib_sdk_header_files})
TARGET_COMPILE_DEFINITIONS( _Ring_3___TgS_PHYSICS_MP_CLIENT PRIVATE TgBUILD_FEATURE__CLIENT)
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("_MP_CLIENT")
TGS_SET_STANDARD_LIBRARY_PROPERTIES( _Ring_3___TgS_PHYSICS_MP_CLIENT "${MK_BUILD_MODULE__SRC_DIR}" "TgS Physics [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files lib_sdk_header_files)
TARGET_LINK_LIBRARIES(_Ring_3___TgS_PHYSICS_MP_CLIENT PUBLIC
    _Ring_0___TgS_COMMON
    _Ring_0___TgS_COLLISION
    _Ring_0___TgS_PARTITION
)

ADD_LIBRARY(_Ring_3___TgS_PHYSICS_SP STATIC ${lib_source_files} ${lib_header_files} ${lib_sdk_header_files})
TARGET_COMPILE_DEFINITIONS( _Ring_3___TgS_PHYSICS_SP PRIVATE TgBUILD_FEATURE__SERVER)
TARGET_COMPILE_DEFINITIONS( _Ring_3___TgS_PHYSICS_SP PRIVATE TgBUILD_FEATURE__CLIENT)
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("_SP")
TGS_SET_STANDARD_LIBRARY_PROPERTIES( _Ring_3___TgS_PHYSICS_SP "${MK_BUILD_MODULE__SRC_DIR}" "TgS Physics [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files lib_sdk_header_files)
TARGET_LINK_LIBRARIES(_Ring_3___TgS_PHYSICS_SP PUBLIC
    _Ring_0___TgS_COMMON
    _Ring_0___TgS_COLLISION
    _Ring_0___TgS_PARTITION
)
