cmake_minimum_required(VERSION 3.4)
cmake_policy(VERSION 3.4)
cmake_policy(SET CMP0015 NEW)
#    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "KERNEL" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../tst/inc/TgS KERNEL" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../tst/src/TgS KERNEL" )
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()




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

SET( PCH_INCLUDE_DEFAULT "TgS Kernel [Unit Test] - Internal.h")
TGS_ADD_UNITTEST_EXECUTABLE( "Unit_Test___Ring_2___TgS_KERNEL" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Kernel [Unit Test]" ${PCH_INCLUDE_DEFAULT} exe_source_files exe_header_files )

IF ("${MK_BUILD__OS}" STREQUAL "WIN")
    IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
        IF (MK_COMPILER_FRONTEND__MSVC)
            TARGET_LINK_OPTIONS ("Unit_Test___Ring_2___TgS_KERNEL" PUBLIC /SUBSYSTEM:CONSOLE)
        ELSEIF (MK_COMPILER_FRONTEND__GNU)
            TARGET_LINK_OPTIONS ("Unit_Test___Ring_2___TgS_KERNEL" PUBLIC -Xlinker /SUBSYSTEM:CONSOLE)
        ENDIF ()
        TARGET_COMPILE_DEFINITIONS("Unit_Test___Ring_2___TgS_KERNEL" PRIVATE TgBUILD_TARGET__WINDOWS_CONSOLE)
    ELSEIF (MK_COMPILER_FRONTEND__MSVC)
        TARGET_LINK_OPTIONS ("Unit_Test___Ring_2___TgS_KERNEL" PUBLIC /SUBSYSTEM:WINDOWS)
    ENDIF ()

    IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "DX12")
        # This is left in for the GitHub builds
        SET_PROPERTY(TARGET "Unit_Test___Ring_2___TgS_KERNEL" PROPERTY VS_PACKAGE_REFERENCES "Microsoft.Direct3D.D3D12_1.606.4;WinPixEventRuntime_1.0.220810001")
        # New properties that I hacked in CMake so that I can get it done.
        SET_PROPERTY(TARGET "Unit_Test___Ring_2___TgS_KERNEL" PROPERTY VS_PACKAGE_TARGET_REFERENCES "Microsoft.Direct3D.D3D12|1.606.4|build/native;WinPixEventRuntime|1.0.220810001|build")
        SET_PROPERTY(TARGET "Unit_Test___Ring_2___TgS_KERNEL" PROPERTY VS_PACKAGE_PROPS_REFERENCES "Microsoft.Direct3D.D3D12|1.606.4|build/native")
    ENDIF ()
ENDIF ()

TARGET_LINK_LIBRARIES("Unit_Test___Ring_2___TgS_KERNEL" ${_Ring_0___LIBS} ${_Ring_2___LIBS})
