cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "UNIT_TEST__INPUT" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${CMAKE_CURRENT_SOURCE_DIR}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library unit test

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.c" )
TGS_ADD_HEADER_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] [Boot].c")


TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input [Unit Test] - Internal.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input [Unit Test].c" )




#INPUT
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input [Unit Test] - GamePad.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input [Unit Test] - Keyboard.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input [Unit Test] - Module.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Input [Unit Test] - Mouse.c")


# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library unit test
ADD_EXECUTABLE ("Unit_Test___Ring_3___TgS_INPUT" ${APP_TYPE} ${exe_source_files} ${exe_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Input [Unit Test] - Internal.h")
TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES( "Unit_Test___Ring_3___TgS_INPUT" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Input [Unit Test]" ${PCH_INCLUDE_DEFAULT} exe_source_files exe_header_files )
TARGET_LINK_LIBRARIES("Unit_Test___Ring_3___TgS_INPUT" PRIVATE ${_Ring_0___COMMON_LIBS} ${_Ring_2___COMMON_LIBS} _Ring_3___TgS_INPUT _Ring_3___TgS_INPUT__OS)

IF ("${MK_BUILD__OS}" STREQUAL "WINDOWS")
    IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
        IF (MK_COMPILER_FRONTEND__MSVC)
            TARGET_LINK_OPTIONS ("Unit_Test___Ring_3___TgS_INPUT" PUBLIC /SUBSYSTEM:CONSOLE)
        ELSEIF (MK_COMPILER_FRONTEND__GNU)
            TARGET_LINK_OPTIONS ("Unit_Test___Ring_3___TgS_INPUT" PUBLIC -Xlinker /SUBSYSTEM:CONSOLE)
        ENDIF ()
        TARGET_COMPILE_DEFINITIONS("Unit_Test___Ring_3___TgS_INPUT" PRIVATE TgBUILD_TARGET__WINDOWS_CONSOLE)
    ELSEIF (MK_COMPILER_FRONTEND__MSVC)
        TARGET_LINK_OPTIONS ("Unit_Test___Ring_3___TgS_INPUT" PUBLIC /SUBSYSTEM:WINDOWS)
    ENDIF ()
ENDIF ()
