cmake_minimum_required(VERSION 3.31)
cmake_policy(VERSION 3.31)
cmake_policy(SET CMP0015 NEW)
#    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "COLLISION" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library
SOURCE_GROUP ("" REGULAR_EXPRESSION .*)

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/_System" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Data.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/_System" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Module.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/_System" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision [PCH].c" )

# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# Public Header / Inline / Source File List

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Constants.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Request.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Type.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Errors.TgS" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Collision.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 0 - Type.h" )

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box AA.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Circle.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Cylinder.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Ellipse.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Line.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Ray.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Segment.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Mesh.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Parallelogram.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Plane.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Primitive.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Ray.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Rectangle.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Segment.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Sphere.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Torus.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Triangle.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files/Primitives" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Tube.h" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/_System" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - System.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/_System" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box AA" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box AA-Box AA.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box AA" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box AA-Plane.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box AA" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box AA-Point.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box AA" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box AA-Sphere.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box AA" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box AA-Triangle.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box [Util].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box-Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box-Linear.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box-Plane.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box-Point.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box-Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box-Segment.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box-Sphere.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Box" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Box-Triangle.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Capsule" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule [Util].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Capsule" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule-Capsule.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Capsule" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule-Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Capsule" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule-Linear.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Capsule" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule-Plane.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Capsule" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule-Point.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Capsule" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule-Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Capsule" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule-Segment.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Capsule" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule-Sphere.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Capsule" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Capsule-Triangle.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Circle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Circle-Circle.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Circle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Circle-Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Circle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Circle-Point.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Circle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Circle-Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Circle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Circle-Segment.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Cylinder" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Cylinder-Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Cylinder" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Cylinder-Linear.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Cylinder" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Cylinder-Plane.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Cylinder" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Cylinder-Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Cylinder" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Cylinder-Segment.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Linear" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Linear" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Linear" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Segment.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Parallelogram" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Parallelogram-Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Parallelogram" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Parallelogram-Linear.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Parallelogram" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Parallelogram-Parallelogram.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Parallelogram" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Parallelogram-Point.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Parallelogram" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Parallelogram-Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Parallelogram" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Parallelogram-Rectangle.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Parallelogram" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Parallelogram-Segment.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Parallelogram" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Parallelogram-Triangle.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Plane" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Plane-Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Plane" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Plane-Linear.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Plane" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Plane-Point.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Plane" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Plane-Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Plane" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Plane-Segment.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Mesh" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Ray.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Rectangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Rectangle-Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Rectangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Rectangle-Linear.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Rectangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Rectangle-Point.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Rectangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Rectangle-Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Rectangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Rectangle-Rectangle.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Rectangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Rectangle-Segment.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Rectangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Rectangle-Triangle.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Mesh" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Segment.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Sphere" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Sphere-Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Sphere" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Sphere-Linear.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Sphere" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Sphere-Plane.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Sphere" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Sphere-Point.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Sphere" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Sphere-Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Sphere" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Sphere-Segment.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Sphere" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Sphere-Sphere.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Sphere" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Sphere-Triangle.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Triangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Triangle [Util].inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Triangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Triangle-Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Triangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Triangle-Point.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Triangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Triangle-Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Triangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Triangle-Segment.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Triangle" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Triangle-Triangle.inl" )

TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Tube" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Tube-Line.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Tube" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Tube-Linear.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Tube" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Tube-Ray.inl" )
TGS_ADD_INCSRC_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Inline Files/Tube" "${MK_BUILD_MODULE__INC_DIR}/TgS Collision - Tube-Segment.inl" )


# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# SDK Header / Inline / Source File List

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Internal.h" )
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files/Template Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Internal.h" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/_System" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Axis Projection.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/_System" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Clip [Template].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/_System" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Primitive-Primitive.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/_System" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - System.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/_System" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Utility.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box AA" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box AA-Box AA.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box AA" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box AA-Linear.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box AA" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box AA-Plane.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box AA" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box AA-Sphere.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box [Axis Separation].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box-Box.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box-Linear.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box-Plane.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box-Point.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box-Sphere.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Box" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Box-Triangle.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Capsule" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Capsule-Capsule.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Capsule" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Capsule-Linear.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Capsule" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Capsule-Plane.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Capsule" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Capsule-Point.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Capsule" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Capsule-Sphere.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Capsule" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Capsule-Triangle.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Circle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Circle-Circle.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Circle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Circle-Linear.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Circle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Circle-Point.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Circle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Circle-Triangle.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Convex" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Convex-Box.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Convex" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Convex-Capsule.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Convex" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Convex-Cylinder.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Convex" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Convex-Plane.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Convex" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Convex-Sphere.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Convex" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Convex-Triangle.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Cylinder" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Cylinder-Box.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Cylinder" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Cylinder-Capsule.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Cylinder" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Cylinder-Cylinder.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Cylinder" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Cylinder-Linear.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Cylinder" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Cylinder-Plane.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Cylinder" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Cylinder-Sphere.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Cylinder" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Cylinder-Triangle.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Ellipse" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Ellipse-Ellipse.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Linear" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Linear-Linear.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Parallelogram" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Parallelogram [Util].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Parallelogram" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Parallelogram-Linear.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Parallelogram" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Parallelogram-Parallelogram.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Parallelogram" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Parallelogram-Point.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Parallelogram" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Parallelogram-Rectangle.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Parallelogram" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Parallelogram-Triangle.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Rectangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Rectangle [Util].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Rectangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Rectangle-Linear.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Rectangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Rectangle-Point.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Rectangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Rectangle-Rectangle.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Rectangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Rectangle-Triangle.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Sphere" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Sphere-Linear.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Sphere" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Sphere-Plane.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Sphere" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Sphere-Point.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Sphere" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Sphere-Sphere.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Sphere" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Sphere-Triangle.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Triangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Triangle [Axis Separation].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Triangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Triangle [Util].c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Triangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Triangle-Linear.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Triangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Triangle-Particle.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Triangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Triangle-Point.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Triangle" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Triangle-Triangle.c" )

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Tube" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Tube-Linear.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Tube" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Tube-Sphere.c" )
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Tube" "${MK_BUILD_MODULE__SRC_DIR}/TgS Collision - Tube-Tube.c" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library compiler specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
ADD_LIBRARY(_Ring_0___TgS_COLLISION STATIC ${lib_source_files} ${lib_header_files} ${lib_sdk_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Collision - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES( _Ring_0___TgS_COLLISION "${MK_BUILD_MODULE__SRC_DIR}" "TgS Collision [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files lib_sdk_header_files)
TARGET_LINK_LIBRARIES(_Ring_0___TgS_COLLISION PUBLIC _Ring_0___TgS_COMMON)
