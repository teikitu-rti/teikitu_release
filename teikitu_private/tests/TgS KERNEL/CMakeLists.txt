cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "UNIT_TEST__KERNEL" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${CMAKE_CURRENT_SOURCE_DIR}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library unit test

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.c" )
TGS_ADD_HEADER_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] [Boot].c")


TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [Unit Test] - Internal.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [Unit Test].c" )



# KERNEL
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Module [Unit Test].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "GPU" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - GPU [Unit Test].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "OS" "${MK_BUILD_MODULE__SRC_DIR}/TgS (OS) Kernel - Module [Unit Test].c" )

TGS_ADD_HEADER_FILE( exe_source_files exe_header_files "-" "-" "GPU/Content Files" "${MK_BUILD_MODULE__SRC_DIR}/UnitTest_Common.hlsli")

# KERNEL DX12
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "GPU" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel - GPU [Unit Test].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "METAL" "${MK_BUILD__GRAPHICS_NAME}" "GPU" "${MK_BUILD_MODULE__SRC_DIR}/TgS (METAL) Kernel - GPU [Unit Test].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "GPU" "${MK_BUILD_MODULE__SRC_DIR}/TgS (REF) Kernel - GPU [Unit Test].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "VULKAN" "${MK_BUILD__GRAPHICS_NAME}" "GPU" "${MK_BUILD_MODULE__SRC_DIR}/TgS (VULKAN) Kernel - GPU [Unit Test].c" )

TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "GPU/Content Files" "${MK_BUILD_MODULE__SRC_DIR}/UnitTest_001.vs.hlsl")
TGS_ADD_HLSL_FILE( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "GPU/Content Files" "${MK_BUILD_MODULE__SRC_DIR}/UnitTest_003.vs.hlsl")
TGS_ADD_HLSL_FILE( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "GPU/Content Files" "${MK_BUILD_MODULE__SRC_DIR}/UnitTest_004.vs.hlsl")

TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "GPU/Content Files" "${MK_BUILD_MODULE__SRC_DIR}/UnitTest_001.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "GPU/Content Files" "${MK_BUILD_MODULE__SRC_DIR}/UnitTest_002.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "GPU/Content Files" "${MK_BUILD_MODULE__SRC_DIR}/UnitTest_003.ps.hlsl")
TGS_ADD_HLSL_FILE( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "GPU/Content Files" "${MK_BUILD_MODULE__SRC_DIR}/UnitTest_004.ps.hlsl")
TGS_ADD_HLSL_FILE( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "GPU/Content Files" "${MK_BUILD_MODULE__SRC_DIR}/UnitTest_004.ps.hlsl")
TGS_ADD_HLSL_FILE( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "GPU/Content Files" "${MK_BUILD_MODULE__SRC_DIR}/UnitTest_005.ps.hlsl")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific modifications




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library unit test
SET(MK_BUILD__KERNEL_UNIT_TEST "Unit_Test___Ring_2___TgS_KERNEL")
ADD_EXECUTABLE ("Unit_Test___Ring_2___TgS_KERNEL" ${APP_TYPE} ${exe_source_files} ${exe_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Kernel [Unit Test] - Internal.h")
TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES( "Unit_Test___Ring_2___TgS_KERNEL" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Kernel [Unit Test]" ${PCH_INCLUDE_DEFAULT} exe_source_files exe_header_files )
TARGET_LINK_LIBRARIES("Unit_Test___Ring_2___TgS_KERNEL" PRIVATE ${_Ring_0___COMMON_LIBS} ${_Ring_2___COMMON_LIBS})

IF ("${MK_BUILD__OS}" STREQUAL "WINDOWS")
    IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
        SET_TARGET_PROPERTIES( "Unit_Test___Ring_2___TgS_KERNEL" PROPERTIES WIN32_EXECUTABLE 0)
        TARGET_COMPILE_DEFINITIONS("Unit_Test___Ring_2___TgS_KERNEL" PRIVATE TgBUILD_TARGET__WINDOWS_CONSOLE)
#        IF (MK_COMPILER_FRONTEND__MSVC)
#            TARGET_LINK_OPTIONS ("Unit_Test___Ring_2___TgS_KERNEL" PUBLIC /SUBSYSTEM:CONSOLE)
#        ELSEIF (MK_COMPILER_FRONTEND__GNU)
#            TARGET_LINK_OPTIONS ("Unit_Test___Ring_2___TgS_KERNEL" PUBLIC -Xlinker /SUBSYSTEM:CONSOLE)
#        ENDIF ()
#        TARGET_COMPILE_DEFINITIONS("Unit_Test___Ring_2___TgS_KERNEL" PRIVATE TgBUILD_TARGET__WINDOWS_CONSOLE)
#    ELSEIF (MK_COMPILER_FRONTEND__MSVC)
#        TARGET_LINK_OPTIONS ("Unit_Test___Ring_2___TgS_KERNEL" PUBLIC /SUBSYSTEM:WINDOWS)
    ENDIF ()
ENDIF ()
