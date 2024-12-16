cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "UNIT_TEST__COLLISION" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${CMAKE_CURRENT_SOURCE_DIR}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library unit test

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.c" )
TGS_ADD_HEADER_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] [Boot].c")


TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - Internal.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test].c" )




#COLLISION
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Box AA.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Box.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Capsule.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Circle.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Mesh.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Cylinder.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Ellipse.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Line.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Parallelogram.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Plane.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Ray.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Rectangle.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Segment.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Sphere.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Triangle.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Torus.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F - Tube.c_inc")
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Test/Source Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [Unit Test] - F [Set].c_inc")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library unit test
ADD_EXECUTABLE ("Unit_Test___Ring_0___TgS_COLLISION" ${APP_TYPE} ${exe_source_files} ${exe_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Collision [Unit Test] - Internal.h")
TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES( "Unit_Test___Ring_0___TgS_COLLISION" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Collision [Unit Test]" ${PCH_INCLUDE_DEFAULT} exe_source_files exe_header_files )

TARGET_LINK_LIBRARIES("Unit_Test___Ring_0___TgS_COLLISION" PRIVATE _Ring_0___TgS_COMMON _Ring_0___TgS_COMMON__OS _Ring_0___TgS_COLLISION)

IF ("${MK_BUILD__OS}" STREQUAL "WINDOWS")
    SET_TARGET_PROPERTIES( "Unit_Test___Ring_0___TgS_COLLISION" PROPERTIES WIN32_EXECUTABLE 0)
    TARGET_COMPILE_DEFINITIONS("Unit_Test___Ring_0___TgS_COLLISION" PRIVATE TgBUILD_TARGET__WINDOWS_CONSOLE)
ENDIF ()

#    IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
#        SET_TARGET_PROPERTIES( ${TARGET} PROPERTIES WIN32_EXECUTABLE 0)
#        TARGET_COMPILE_DEFINITIONS("Unit_Test___Ring_0___TgS_COLLISION" PRIVATE TgBUILD_TARGET__WINDOWS_CONSOLE)
#        IF (MK_COMPILER_FRONTEND__MSVC)
#            TARGET_LINK_OPTIONS ("Unit_Test___Ring_0___TgS_COLLISION" PUBLIC /SUBSYSTEM:CONSOLE)
#        ELSEIF (MK_COMPILER_FRONTEND__GNU)
#            TARGET_LINK_OPTIONS ("Unit_Test___Ring_0___TgS_COLLISION" PUBLIC -Xlinker /SUBSYSTEM:CONSOLE)
#        ENDIF ()
#    ELSEIF (MK_COMPILER_FRONTEND__MSVC)
#        TARGET_LINK_OPTIONS ("Unit_Test___Ring_0___TgS_COLLISION" PUBLIC /SUBSYSTEM:WINDOWS)
#    ENDIF ()
#ENDIF ()
