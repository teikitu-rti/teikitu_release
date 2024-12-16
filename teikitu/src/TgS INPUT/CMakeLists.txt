cmake_minimum_required(VERSION 3.4)
cmake_policy(VERSION 3.4)
cmake_policy(SET CMP0015 NEW)

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "INPUT" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../inc" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../inc/TgS INPUT" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../src/TgS INPUT" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library
SOURCE_GROUP ("" REGULAR_EXPRESSION .*)

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input [PCH].c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input - Module.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input - System.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input - Data.c")

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input - Internal.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input - Internal - Data.h")

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Input - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Input - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Input.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 3 - Type.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files

TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input [PCH].cpp")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input - Fcn Bind.cpp")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (XInput) Input - GamePad.cpp")

TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input [PCH].c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input - Data.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input - Module.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input - GUI Keyboard.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input - GUI Mouse.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input - Keyboard.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input - Mouse.c")

TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Header Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Header Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Input - Internal.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific modifications

IF (MK_PLATFORM_WIN)
    FOREACH (MK_LIST_ITEM__FILE_NAME IN ITEMS ${${SOURCE_FILES}} )
        GET_FILENAME_COMPONENT( FILE_EXTENSION "${MK_LIST_ITEM__FILE_NAME}" EXT )
        IF (${FILE_EXTENSION} STREQUAL ".cpp")
            SET_SOURCE_FILES_PROPERTIES("${MK_LIST_ITEM__FILE_NAME}" PROPERTIES DISABLE_LANGUAGE_EXTENSIONS 0)
        ENDIF ()
    ENDFOREACH ()
ENDIF (MK_PLATFORM_WIN)




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
ADD_LIBRARY("_Ring_3___TgS_INPUT" STATIC ${lib_source_files} ${lib_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Input - Internal.h")
TGS_SET_STANDARD_PROPERTIES( "_Ring_3___TgS_INPUT" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Input [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files )

ADD_LIBRARY("_Ring_3___TgS_INPUT__OS" STATIC ${lib_os_source_files} ${lib_os_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__OS")
SET( PCH_OS_INCLUDE_DEFAULT "TgS (${MK_BUILD__OS_NAME}) Input - Internal.h")
TGS_SET_STANDARD_PROPERTIES( "_Ring_3___TgS_INPUT__OS" "${MK_BUILD_MODULE__SRC_DIR}" "TgS (${MK_BUILD__OS_NAME}) Input [PCH]" ${PCH_OS_INCLUDE_DEFAULT} lib_os_source_files lib_os_header_files )
