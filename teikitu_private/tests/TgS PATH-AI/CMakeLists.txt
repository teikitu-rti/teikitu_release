cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "UNIT_TEST__PATH-AI" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${CMAKE_CURRENT_SOURCE_DIR}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library unit test

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.c" )
TGS_ADD_HEADER_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] [Boot].c")


TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Path-AI [Unit Test] - Internal.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Path-AI [Unit Test].c" )




#PATH-AI




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library unit test
ADD_EXECUTABLE ("Unit_Test___Ring_0___TgS_PATH-AI" ${APP_TYPE} ${exe_source_files} ${exe_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Path-AI [Unit Test] - Internal.h")
TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES( "Unit_Test___Ring_0___TgS_PATH-AI" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Path-AI [Unit Test]" ${PCH_INCLUDE_DEFAULT} exe_source_files exe_header_files )

IF ("${MK_BUILD__OS}" STREQUAL "WINDOWS")
    IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
        IF (MK_COMPILER_FRONTEND__MSVC)
            TARGET_LINK_OPTIONS ("Unit_Test___Ring_0___TgS_PATH-AI" PUBLIC /SUBSYSTEM:CONSOLE)
        ELSEIF (MK_COMPILER_FRONTEND__GNU)
            TARGET_LINK_OPTIONS ("Unit_Test___Ring_0___TgS_PATH-AI" PUBLIC -Xlinker /SUBSYSTEM:CONSOLE)
        ENDIF ()
        TARGET_COMPILE_DEFINITIONS("Unit_Test___Ring_0___TgS_PATH-AI" PRIVATE TgBUILD_TARGET__WINDOWS_CONSOLE)
    ELSEIF (MK_COMPILER_FRONTEND__MSVC)
        TARGET_LINK_OPTIONS ("Unit_Test___Ring_0___TgS_PATH-AI" PUBLIC /SUBSYSTEM:WINDOWS)
    ENDIF ()
ENDIF ()
TARGET_LINK_LIBRARIES("Unit_Test___Ring_0___TgS_PATH-AI" PRIVATE ${_Ring_0___COMMON_LIBS})
