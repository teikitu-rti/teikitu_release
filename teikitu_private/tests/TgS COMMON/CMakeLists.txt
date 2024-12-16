cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "UNIT_TEST__COMMON" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${CMAKE_CURRENT_SOURCE_DIR}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library unit test

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.c" )
TGS_ADD_HEADER_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] [Boot].c")


TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Internal.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test].c" )




# BASE

TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Base/Tests/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Base - API [Text].c_inc" )
TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "Base/Tests/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Base - API [Math].c_inc" )

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Base - API [Math].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Base - API [Platform].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Base - API [Text].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Base - API.c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Base - Type [Constants].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Base - Type [File].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Base - Type [IO].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Base - Type [MP].c" )

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base"       "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Case] - Base - API.c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base"       "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Case] - Base - Type.c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Base"       "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Set] - Base.c" )




# MATH

    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Matrix" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Matrix] [API].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Matrix" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Matrix] [S] [F] [34].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Matrix" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Matrix] [S] [F] [44].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Matrix" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Matrix] [S] [F].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Matrix" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Matrix] [F] [34].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Matrix" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Matrix] [F] [44].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Matrix" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Matrix] [F].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Matrix" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Matrix] [S].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Matrix" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Matrix].c")

    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Vector" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Vector] [API].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Vector" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Vector] [S] [FXX_04].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Vector" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Vector] [S] [F].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Vector" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Vector] [S] [I].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Vector" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Vector] [FXX_04].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Vector" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Vector] [F].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Vector" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Vector] [I].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Vector" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Vector].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Vector" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Vector] [S].c")

    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Scalar" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Constants].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math/Tests/Scalar" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Math [Scalar] [F].c")

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Case] - Math [Matrix].c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Case] - Math [Vector].c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Math" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Set] - Math.c")




# GEOMETRY

    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 2D - Rectangle.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Box - Axis Aligned.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Box.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Capsule.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Circle.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Cylinder.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Ellipse.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Line.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Mesh [BA].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Mesh [BVT].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Mesh [Simple].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Parallelogram.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Particle.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Plane.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Ray.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Rectangle.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Segment.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Sphere.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Torus.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Triangle [Collision].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Triangle [Edge].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Triangle [Point].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Triangle [Space].c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry 3D - Tube.c")
    TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry - Type.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Geometry.c")




# UTILITY

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util MT - Hash Table.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util MT - LA Ring Buffer SRSW.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util MT - Profile Sample.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util MT - Reader Writer Lock.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util MT - Spin Lock.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util MT - Stack.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util ST - Array.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util ST - Colour.c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util ST - List.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util ST - Queue.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Util ST - String.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Utility" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Util.c")




# COMMON

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Common/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Console.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Common/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Event MGR.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Common/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Global.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Common/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Job MGR.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Common/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Mem MGR.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Common/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - Profile.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Common/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - String MGR.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Common/Tests" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] [Test] - SysInfo.c")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [Unit Test] - Common.c")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "UWP" ${MK_BUILD__UNIVERSAL_NAME} "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/TgS (UWP) Common [Unit Test].cpp" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library unit test
ADD_EXECUTABLE ("Unit_Test___Ring_0___TgS_COMMON" ${APP_TYPE} ${exe_source_files} ${exe_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Common [Unit Test] - Internal.h")
TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES( "Unit_Test___Ring_0___TgS_COMMON" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Common [Unit Test]" ${PCH_INCLUDE_DEFAULT} exe_source_files exe_header_files )
TARGET_LINK_LIBRARIES("Unit_Test___Ring_0___TgS_COMMON" PRIVATE _Ring_0___TgS_COMMON)

IF ("${MK_BUILD__OS}" STREQUAL "WINDOWS")
    SET_TARGET_PROPERTIES( "Unit_Test___Ring_0___TgS_COMMON" PROPERTIES WIN32_EXECUTABLE 0)
    TARGET_COMPILE_DEFINITIONS("Unit_Test___Ring_0___TgS_COMMON" PRIVATE TgBUILD_TARGET__WINDOWS_CONSOLE)
ENDIF ()

#IF ("${MK_BUILD__OS}" STREQUAL "WINDOWS")
#    SET_TARGET_PROPERTIES( ${TARGET} PROPERTIES WIN32_EXECUTABLE 0)
#    TARGET_COMPILE_DEFINITIONS("Unit_Test___Ring_0___TgS_COMMON" PRIVATE TgBUILD_TARGET__WINDOWS_CONSOLE)
#    IF (MK_COMPILER_FRONTEND__MSVC)
#        TARGET_LINK_OPTIONS ("Unit_Test___Ring_0___TgS_COMMON" PUBLIC /SUBSYSTEM:CONSOLE)
#    ELSEIF (MK_COMPILER_FRONTEND__GNU)
#        TARGET_LINK_OPTIONS ("Unit_Test___Ring_0___TgS_COMMON" PUBLIC -Xlinker /SUBSYSTEM:CONSOLE)
#    ENDIF ()
#ENDIF ()
