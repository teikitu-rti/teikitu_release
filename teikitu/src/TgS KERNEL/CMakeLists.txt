cmake_minimum_required(VERSION 3.4)
cmake_policy(VERSION 3.4)
cmake_policy(SET CMP0015 NEW)
#    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "KERNEL" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../inc" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../inc/TgS KERNEL" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../src/TgS KERNEL" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library

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

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Errors.TgS")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 2 - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Kernel.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files

TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Kernel - Data.c" )
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Kernel - Module.c" )
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Kernel - Configuration.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Kernel - Link Test.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Kernel - System.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Kernel [PCH].c")

TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Kernel - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Kernel - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Kernel - Internal.h")

TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (WIN) Kernel - Constants.h")
TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (WIN) Kernel - Type.h")
TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" ${MK_BUILD__OS_NAME} "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (WIN) Kernel.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library

TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal [EXT].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal.h")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Constants.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Data.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Debug [Console].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Debug [Geom-Text-UI].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Debug.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Module.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [DEVC].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [EXEC].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [HOST].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [SWAP].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] [PCH].c")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Common].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Font] [ROM].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Shader].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Cube].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Image].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Volume].c")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [BMP].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [DDS].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [GIF].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [JPG].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [PNG].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [TGA].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [TIF].c")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource LIB" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource LIB [Common].c")

TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Constants.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [INC].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [HLSL] [Constants].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [HLSL] [Data].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [HLSL] [Vertex].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Type.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] [EXT].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Kernel [GPU].h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - Specialization DX12

TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Constants.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Debug.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal.h")

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
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] [PCH].c")

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Resource [Data Buffer].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Resource [Pipeline].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Resource [Texture].c")

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12-WIN" "${MK_BUILD__GRAPHICS_NAME}-${MK_BUILD__OS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12-WIN) Kernel [GPU] - Module.c")

TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (DX12) Kernel [GPU] - Constants.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (DX12) Kernel [GPU] - Type.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "Public" "${MK_BUILD_MODULE__INC_DIR}/TgS (DX12) Kernel [GPU].h")




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
# GPU Library - Reference STUB

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (REF) Kernel [GPU] [API].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (REF) Kernel [GPU] [PCH].c")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (REF) Kernel [GPU] - Internal.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (REF) Kernel [GPU] - Constants.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - DirectX Headers

FILE(GLOB_RECURSE children "${MK_BUILD_MODULE__SRC_DIR}/DirectX-Headers/*")
FOREACH(child ${children})
    TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/DirectX-Headers" "${child}")
ENDFOREACH()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - LibTIFF

CMAKE_PATH ( SET MK_BUILD_EXTERNAL__LIBTIFF NORMALIZE "${PROJECT_SOURCE_DIR}/../../external/libtiff" )

TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public/Header Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tiff.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public/Header Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tiffio.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public/Header Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tiffvers.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "Public/Header Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tiffconf.h")

TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/t4.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_dir.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_predict.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tiffiop.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/uvcode.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_config.h")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_aux.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_close.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_codec.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_color.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_compress.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_dir.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_dirinfo.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_dirread.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_dirwrite.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_dumpmode.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_error.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_extension.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_fax3.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_fax3sm.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_flush.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_getimage.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_jbig.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_jpeg.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_jpeg_12.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_lerc.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_luv.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_lzma.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_lzw.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_next.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_ojpeg.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_open.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_packbits.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_pixarlog.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_predict.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_print.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_read.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_strip.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_swab.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_thunder.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_tile.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_version.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_warning.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_webp.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_write.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_zip.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/LibTIFF" "${MK_BUILD_EXTERNAL__LIBTIFF}/tif_zstd.c")

FILE(GLOB_RECURSE children "${MK_BUILD_EXTERNAL__LIBTIFF}/*")
FOREACH(child ${children})
    IF (CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "gnu")
        SET_PROPERTY(SOURCE "${child}" APPEND_STRING PROPERTY COMPILE_FLAGS [=[ -w]=])
    ELSE()
        SET_PROPERTY(SOURCE "${child}" APPEND_STRING PROPERTY COMPILE_FLAGS [=[ /W0 /Y- /TC]=])
    ENDIF ()
ENDFOREACH()





# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
ADD_LIBRARY("_Ring_2___TgS_KERNEL" STATIC ${lib_source_files} ${lib_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Kernel - Internal.h")
TGS_SET_STANDARD_PROPERTIES( "_Ring_2___TgS_KERNEL" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Kernel [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files )

ADD_LIBRARY("_Ring_2___TgS_KERNEL__OS" STATIC ${lib_os_source_files} ${lib_os_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__OS")
SET( PCH_OS_INCLUDE_DEFAULT "TgS (${MK_BUILD__OS_NAME}) Kernel - Internal.h")
TGS_SET_STANDARD_PROPERTIES( "_Ring_2___TgS_KERNEL__OS" "${MK_BUILD_MODULE__SRC_DIR}" "TgS (${MK_BUILD__OS_NAME}) Kernel [PCH]" ${PCH_OS_INCLUDE_DEFAULT} lib_os_source_files lib_os_header_files )

SET(MK_BUILD__MODULE_GPU_LIB "_Ring_2___TgS_KERNEL__GPU")
IF (NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
    ADD_LIBRARY(${MK_BUILD__MODULE_GPU_LIB} STATIC ${lib_gpu_source_files} ${lib_gpu_header_files})
    TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__GPU")
    SET( PCH_GPU_INCLUDE_DEFAULT "TgS Kernel [GPU] - Internal.h")
    TGS_SET_STANDARD_PROPERTIES( ${MK_BUILD__MODULE_GPU_LIB} "${MK_BUILD_MODULE__SRC_DIR}" "TgS Kernel [GPU] [PCH]" ${PCH_GPU_INCLUDE_DEFAULT} lib_gpu_source_files lib_gpu_header_files )
ELSE ()
    ADD_CUSTOM_TARGET( ${MK_BUILD__MODULE_GPU_LIB} SOURCES ${lib_gpu_source_files} ${lib_gpu_header_files})
    SET_PROPERTY(TARGET ${MK_BUILD__MODULE_GPU_LIB} PROPERTY PROJECT_LABEL "${MK_BUILD__MODULE_GPU_LIB} (Inactive)")
ENDIF ()

SET(MK_BUILD__GRAPHICS_IMPL_LIB "_Ring_2___TgS_KERNEL__GPU__${MK_BUILD__GRAPHICS_NAME}")
IF (NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
    ADD_LIBRARY(${MK_BUILD__GRAPHICS_IMPL_LIB} STATIC ${lib_api_gpu_source_files} ${lib_api_gpu_header_files})
    TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__GPU__${MK_BUILD__GRAPHICS_NAME}")
    SET( PCH_GPU_INCLUDE_DEFAULT "TgS (${MK_BUILD__GRAPHICS_NAME}) Kernel [GPU] - Internal.h")
    TGS_SET_STANDARD_PROPERTIES( ${MK_BUILD__GRAPHICS_IMPL_LIB} "${MK_BUILD_MODULE__SRC_DIR}" "TgS (${MK_BUILD__GRAPHICS_NAME}) Kernel [GPU] [PCH]" ${PCH_GPU_INCLUDE_DEFAULT} lib_api_gpu_source_files lib_api_gpu_header_files )
ELSE ()
    ADD_CUSTOM_TARGET(${MK_BUILD__GRAPHICS_IMPL_LIB} SOURCES ${lib_api_gpu_source_files} ${lib_api_gpu_header_files})
    SET_PROPERTY(TARGET ${MK_BUILD__GRAPHICS_IMPL_LIB} PROPERTY PROJECT_LABEL "${MK_BUILD__GRAPHICS_IMPL_LIB} (Inactive)")
ENDIF()

IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "DX12")
    # This is left in for the GitHub builds
    SET_PROPERTY(TARGET ${MK_BUILD__GRAPHICS_IMPL_LIB} PROPERTY VS_PACKAGE_REFERENCES "Microsoft.Direct3D.D3D12_1.606.4;WinPixEventRuntime_1.0.220810001")
    # New properties that I hacked in CMake so that I can get it done.
    SET_PROPERTY(TARGET ${MK_BUILD__GRAPHICS_IMPL_LIB} PROPERTY VS_PACKAGE_TARGET_REFERENCES "Microsoft.Direct3D.D3D12|1.606.4|build/native;WinPixEventRuntime|1.0.220810001|build")
    SET_PROPERTY(TARGET ${MK_BUILD__GRAPHICS_IMPL_LIB} PROPERTY VS_PACKAGE_PROPS_REFERENCES "Microsoft.Direct3D.D3D12|1.606.4|build/native")
ENDIF ()
#ADD_LIBRARY("_Ring_X___TgS_KERNEL__FILE_TEST__" STATIC ${lib_api_gpu_source_files} ${lib_api_gpu_header_files} ${lib_gpu_source_files} ${lib_gpu_header_files} ${lib_os_source_files} ${lib_os_header_files} ${lib_source_files} ${lib_header_files})
