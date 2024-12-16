cmake_minimum_required(VERSION 3.4)
cmake_policy(VERSION 3.4)
#    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "COMMON" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../inc" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../inc/TgS COMMON" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${PROJECT_SOURCE_DIR}/../src/TgS COMMON" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 0 - Type.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Common.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Common -- VERSION.h" )

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Common.inl" )




# BASE

    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base/Template" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Defines [Template] [Math].h_inc" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base/Template" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Defines [Template] [Text].h_inc" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base/Template" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Type [Template] [Vector].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - API [Compiler].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - API [Math].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - API [Thread].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - API [Text].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - API.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Defines [Code].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Defines [Configuration].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Defines [Hardware].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Defines [Text].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Defines.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Include.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Type [Constants].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Type [File].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Type [IO].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Type [Limits].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Type [MT].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Type [Vector].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Type.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common -- BASE.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Errors.TgS" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Literals.TgS" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - API [Math].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - API [Text].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - API.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Type [IO].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Base - Type.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Base" "${MK_BUILD_MODULE__INC_DIR}/TgS Common -- BASE.inl" )

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Internal.h" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Base - API [Math].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Base - API [Text].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Base - API.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Base - Data.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Base - Type [Constants].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Base - Type [File] [Data].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Base - Type [File].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Base - Type [IO].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [PCH].c" )




# MATH

    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [API].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [S] [F] [34].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [S] [F] [44].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [S] [F].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [S].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [F] [34].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [F] [44].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [F].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix].h" )

    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [API].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [S] [FXX_04].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [S] [F].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [S] [I].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [S].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [FXX_04].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [F].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [I].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector].h" )
    
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math/Template Files/Scalar" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Scalar] [F].h" )

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS Common -- MATH.h" )

    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [API].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [S] [F] [34].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [S] [F] [44].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [S] [F].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [S].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [F] [34].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [F] [44].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix] [F].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Matrix" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Matrix].inl" )

    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [API].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [S] [FXX_04].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [S] [F].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [S] [I].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [S].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [FXX_04].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [F].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector] [I].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math/Template Files/Vector" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Math [Vector].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS Common -- MATH.inl" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Math" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Math [Scalar] [F].c" )




# GEOMETRY

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 2D - Rectangle.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Box - Axis Aligned.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Box.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Capsule.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Circle.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Cylinder.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Ellipse.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Line.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Mesh [BA].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Mesh [BVT].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Mesh [Simple].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Parallelogram.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Particle.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Plane.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Ray.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Rectangle.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Segment.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Sphere.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Torus.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Triangle [Collision].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Triangle [Edge].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Triangle [Point].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Triangle [Space].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Tube.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry - Type.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry - Constants.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common -- GEOMETRY.h" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 2D - Rectangle.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Box - Axis Aligned.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Box.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Capsule.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Circle.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Cylinder.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Ellipse.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Mesh [BA].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Mesh [BVT].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Mesh [Simple].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Mesh [Utility].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Parallelogram.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Particle.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Plane.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Rectangle.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Segment.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Sphere.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Torus.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Triangle [Collision].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Triangle [Edge].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Triangle [Point].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Triangle [Space].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry 3D - Tube.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Geometry - Type.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Geometry" "${MK_BUILD_MODULE__INC_DIR}/TgS Common -- GEOMETRY.inl" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Circle.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Cylinder.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Ellipse.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Mesh [BA].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Mesh [Simple].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Mesh [Utility].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Particle.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Torus.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Triangle [Collision].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Triangle [Edge].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry 3D - Triangle [Point].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Geometry" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Geometry.c" )





# UTILITY

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - Hash Table.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - LA Ring Buffer SRSW.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - Profile Sample.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - Reader Writer Lock.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - Spin Lock.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - Stack.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - Array.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - Colour.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - Job.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - List.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - Queue.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - String.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common -- UTIL.h" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - Hash Table.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - LA Ring Buffer SRSW.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - Profile Sample.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - Reader Writer Lock.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - Spin Lock.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util MT - Stack.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - Array.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - Colour.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - List.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - Queue.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Util ST - String.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "Public/Inline Files/Utility" "${MK_BUILD_MODULE__INC_DIR}/TgS Common -- UTIL.inl" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Utility" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Util MT - Hash Table.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Utility" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Util MT - Reader Writer Lock.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Utility" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Util ST - Array.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Utility" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Util ST - Colour.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Utility" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Util ST - String.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Utility" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Util.c" )




# COMMON

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Common" "${MK_BUILD_MODULE__INC_DIR}/TgS Common -- COMMON.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Common" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Console.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Common" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Console [Var].h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Common" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Event MGR.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Common" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Job MGR.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Common" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Global.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Common" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Mem MGR.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Common" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - Profile.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "Public/Header Files/Common" "${MK_BUILD_MODULE__INC_DIR}/TgS Common - String MGR.h" )

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Event MGR - Internal.h" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Event MGR.inl" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Console - Internal.h" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Console.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Common/Template" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Profile.c_inc" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Console [Var].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Console.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Event MGR [Time Event].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Event MGR.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Job MGR.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Global.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Mem MGR.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Profile.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common - String MGR.c" )





# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific files

FOREACH (MK_LIST_ITEM__COMPILER_NAME IN LISTS MK_GENERATE_LIST__COMPILER_NAMES)
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__COMPILER_NAME}" "${MK_COMPILER_NAME}" "Public/Header Files/@Specialization/Compiler" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__COMPILER_NAME}) Common - Base - Defines.h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__COMPILER_NAME}" "${MK_COMPILER_NAME}" "Public/Header Files/@Specialization/Compiler" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__COMPILER_NAME}) Common - Base - API.h" )

    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__COMPILER_NAME}" "${MK_COMPILER_NAME}" "Public/Inline Files/@Specialization/Compiler" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__COMPILER_NAME}) Common - Base - API.inl" )

    TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__COMPILER_NAME}" "${MK_COMPILER_NAME}" "SDK/Source Files/@Specialization/Compiler" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__COMPILER_NAME}) Common - Base - API.c" )

ENDFOREACH ()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library hardware specific files

FOREACH (MK_LIST_ITEM__HARDWARE_NAME IN LISTS MK_GENERATE_LIST__HARDWARE_NAMES)
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__HARDWARE_NAME}" "${MK_HARDWARE_NAME}" "Public/Header Files/@Specialization/Hardware" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__HARDWARE_NAME}) Common - Base - Defines [Hardware].h" )
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__HARDWARE_NAME}" "${MK_HARDWARE_NAME}" "Public/Header Files/@Specialization/Hardware" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__HARDWARE_NAME}) Common - Base - Include.h" )

ENDFOREACH ()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# threading library - source files are included as part of the operating system library in case of matching configuration (thread == operating system)

FOREACH (MK_LIST_ITEM__THREAD_NAME IN LISTS MK_GENERATE_LIST__THREAD_NAMES)
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__THREAD_NAME}" "${MK_BUILD__THREAD_NAME}" "Public/Header Files/@Specialization/Thread Support" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__THREAD_NAME}) Common - Base - Type [MT].h" )

ENDFOREACH ()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# operating system - put into a separate library due to issues with ninja and overriding PCH files at a source level

FOREACH (MK_LIST_ITEM__OS_NAME IN LISTS MK_GENERATE_LIST__OS_NAMES)
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "Public/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Common - Base - Defines.h" )

ENDFOREACH ()

FOREACH (MK_LIST_ITEM__THREAD_NAME IN LISTS MK_GENERATE_LIST__THREAD_NAMES)
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__THREAD_NAME}" "${MK_BUILD__THREAD_NAME}" "SDK/Source Files/@Specialization/Thread Support" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__THREAD_NAME}) Common - Base - API [Thread].c" )
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__THREAD_NAME}" "${MK_BUILD__THREAD_NAME}" "SDK/Source Files/@Specialization/Thread Support" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__THREAD_NAME}) Common - STg1_MT_MX.c" )
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__THREAD_NAME}" "${MK_BUILD__THREAD_NAME}" "SDK/Source Files/@Specialization/Thread Support" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__THREAD_NAME}) Common - STg1_MT_SM.c" )

ENDFOREACH ()

FOREACH (MK_LIST_ITEM__OS_NAME IN LISTS MK_GENERATE_LIST__OS_NAMES)
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "Public/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Common - Base - Include.h" )
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "Public/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Common - Base - Type.h" )
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "Public/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Common - Global.h" )

    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Common - Base - API.c" )
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Common - Global.c" )
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Common - Mem MGR.c" )
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Common [PCH].c" )
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Source Files/Common" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Common - Console.c" )

    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" "${MK_BUILD__OS_NAME}" "SDK/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Common - Internal.h" )

ENDFOREACH ()

TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Common - Link Test.c" )
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Source Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Common - SysInfo.c" )

TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Common - Internal - Type.h" )
TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "SDK/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__SRC_DIR}/TgS (WIN) Common - Global - Data.h" )

TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "WIN" "${MK_BUILD__OS_NAME}" "Public/Header Files/@Specialization/Operating System" "${MK_BUILD_MODULE__INC_DIR}/TgS (WIN) Common - SysInfo.h" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# universal package

FOREACH (MK_LIST_ITEM__UNIVERSAL_NAME IN LISTS MK_GENERATE_LIST__UNIVERSAL_NAMES)

ENDFOREACH ()

TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "UWP" "${MK_BUILD__UNIVERSAL_NAME}" "SDK/Source Files/@Specialization/Universal" "${MK_BUILD_MODULE__SRC_DIR}/TgS Common [PCH].cpp" )
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "UWP" "${MK_BUILD__UNIVERSAL_NAME}" "SDK/Source Files/@Specialization/Universal" "${MK_BUILD_MODULE__SRC_DIR}/TgS (UWP) Common - Base - API [Universal].cpp" )
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "UWP" "${MK_BUILD__UNIVERSAL_NAME}" "SDK/Source Files/@Specialization/Universal" "${MK_BUILD_MODULE__SRC_DIR}/TgS (UWP) Common - Global.cpp" )
TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "UWP" "${MK_BUILD__UNIVERSAL_NAME}" "SDK/Source Files/@Specialization/Universal" "${MK_BUILD_MODULE__SRC_DIR}/TgS (UWP) Common - Base - API [Universal].cpp" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# math interface and implementation

SET( MK_GENERATE_LIST__MATH_INTERFACE_LIST_0    CLANG               INTEL               APPLE)
SET( MK_GENERATE_LIST__MATH_INTERFACE_LIST_1    ${MK_COMPILER_NAME} ${MK_HARDWARE_NAME} ${MK_BUILD__UNIVERSAL_NAME})
SET( MK_GENERATE_LIST__MATH_IMPLEMENTATION_0    INTEL               APPLE)
SET( MK_GENERATE_LIST__MATH_IMPLEMENTATION_1    ${MK_HARDWARE_NAME} ${MK_BUILD__UNIVERSAL_NAME})

FOREACH (MK_LIST_ITEM__NAME_0 MK_LIST_ITEM__NAME_1 IN ZIP_LISTS MK_GENERATE_LIST__MATH_INTERFACE_LIST_0 MK_GENERATE_LIST__MATH_INTERFACE_LIST_1)
    TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Header Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Vector].h" )

ENDFOREACH ()

FOREACH (MK_LIST_ITEM__NAME_0 MK_LIST_ITEM__NAME_1 IN ZIP_LISTS MK_GENERATE_LIST__MATH_IMPLEMENTATION_0 MK_GENERATE_LIST__MATH_IMPLEMENTATION_1)
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Matrix] [F32] [34].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Matrix] [F32] [44].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Matrix].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Vector] [F32_04].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Vector] [F32].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Vector].inl" )

    IF (NOT MK_LIST_ITEM__NAME_0 MATCHES "APPLE")
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Vector] [S08].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Vector] [S16].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Vector] [S32].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Vector] [U08].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Vector] [U16].inl" )
    TGS_ADD_INCSRC_FILE( lib_source_files lib_header_files "${MK_LIST_ITEM__NAME_0}" "${MK_LIST_ITEM__NAME_1}" "Public/Inline Files/@Specialization/Math" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__NAME_0}) Common - Math [Vector] [U32].inl" )
    ENDIF ()

ENDFOREACH ()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
ADD_LIBRARY("_Ring_0___TgS_COMMON" STATIC ${lib_source_files} ${lib_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Common - Internal.h")
TGS_SET_STANDARD_PROPERTIES( "_Ring_0___TgS_COMMON" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Common [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files )

ADD_LIBRARY("_Ring_0___TgS_COMMON__OS" STATIC ${lib_os_source_files} ${lib_os_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__OS")
SET( PCH_OS_INCLUDE_DEFAULT "TgS (${MK_BUILD__OS_NAME}) Common - Internal.h")
TGS_SET_STANDARD_PROPERTIES( "_Ring_0___TgS_COMMON__OS" "${MK_BUILD_MODULE__SRC_DIR}" "TgS (${MK_BUILD__OS_NAME}) Common [PCH]" ${PCH_OS_INCLUDE_DEFAULT} lib_os_source_files lib_os_header_files )


IF (MK_PLATFORM_UWP)
    #TGS_ADD_CXX_PRECOMPILED_HEADER("${MK_BUILD_MODULE__SRC_DIR}/TgS Common [PCH].cpp" "CXX" ${PCH_INCLUDE_DEFAULT} )
    #TGS_USE_PRECOMPILED_HEADER("${MK_BUILD_MODULE__SRC_DIR}/TgS Common - Base - API - Platform.cpp" "CXX" ${PCH_INCLUDE_DEFAULT} )
ENDIF ()

#ADD_LIBRARY("_Ring_X___TgS_COMMON__FILE_TEST__" STATIC ${lib_os_source_files} ${lib_os_header_files} ${lib_source_files} ${lib_header_files})
