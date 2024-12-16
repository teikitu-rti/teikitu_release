cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "INPUT" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )




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

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Input - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Input - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Input.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 3 - Type.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# operating system - put into a separate library due to issues with ninja and overriding PCH files at a source level

FOREACH (MK_LIST_ITEM__OS_NAME IN LISTS MK_GENERATE_LIST__OS_NAMES)

    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Input [PCH].c")
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Input - Data.c")
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Input - Module.c")

    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Input - Internal - Data.h")
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Input - Internal - Type.h")
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Input - Internal.h")

ENDFOREACH ()

TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WINDOWS" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WINDOWS) Input - Fcn Bind.cpp")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WINDOWS" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (XINPUT) Input - GamePad.cpp")

TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WINDOWS" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WINDOWS) Input - GUI Keyboard.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WINDOWS" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WINDOWS) Input - GUI Mouse.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WINDOWS" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WINDOWS) Input - Keyboard.c")
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WINDOWS" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WINDOWS) Input - Mouse.c")




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
ADD_LIBRARY(_Ring_3___TgS_INPUT__OS STATIC ${lib_os_source_files} ${lib_os_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__OS")
SET( PCH_OS_INCLUDE_DEFAULT "TgS (${MK_BUILD__OS_NAME}) Input - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES( _Ring_3___TgS_INPUT__OS "${MK_BUILD_MODULE__SRC_DIR}" "TgS (${MK_BUILD__OS_NAME}) Input [PCH]" ${PCH_OS_INCLUDE_DEFAULT} lib_os_source_files lib_os_header_files lib_sdk_os_header_files)
TARGET_LINK_LIBRARIES (_Ring_3___TgS_INPUT__OS PUBLIC _Ring_0___TgS_COMMON)


ADD_LIBRARY(_Ring_3___TgS_INPUT STATIC ${lib_source_files} ${lib_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Input - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES( _Ring_3___TgS_INPUT "${MK_BUILD_MODULE__SRC_DIR}" "TgS Input [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files lib_sdk_header_files)
TARGET_LINK_LIBRARIES (_Ring_3___TgS_INPUT PUBLIC 
    _Ring_0___TgS_COMMON
    _Ring_3___TgS_INPUT__OS
)

