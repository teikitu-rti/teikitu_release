# 015482FC-A4BD-4E1C-AE49-A30E5728D73A
CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
CMAKE_POLICY(VERSION 3.31)
SET (CMAKE_OBJECT_PATH_MAX 1024)

INCLUDE (ExternalProject)


# ========================================================================================================================================================================================================
#  FIND GIT
# ========================================================================================================================================================================================================

FIND_PACKAGE (Git) #======================================================================================================================================================================================
IF (GIT_FOUND)
    EXECUTE_PROCESS(
      COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE GIT_BRANCH
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    EXECUTE_PROCESS(
      COMMAND ${GIT_EXECUTABLE} rev-parse --show-toplevel
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE GIT_ROOT_PATH
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
ELSE ()
    MESSAGE (FATAL_ERROR "Could not discover the git. Required for the script to work")
ENDIF ()

IF (NOT GIT_ROOT_PATH)
    MESSAGE (FATAL_ERROR "Could not discover the git repo root. Required for the script to work")
ENDIF ()


# ========================================================================================================================================================================================================
#  HOST SYSTEM INFORMATION
# ========================================================================================================================================================================================================

CMAKE_HOST_SYSTEM_INFORMATION (RESULT PRETTY_NAME QUERY DISTRIB_PRETTY_NAME)
MESSAGE (VERBOSE "${PRETTY_NAME}")

CMAKE_HOST_SYSTEM_INFORMATION (RESULT DISTRO QUERY DISTRIB_INFO)

MESSAGE (VERBOSE "")
MESSAGE (VERBOSE "")
MESSAGE (VERBOSE "HOST SYSTEM INFORMATION")
MESSAGE (VERBOSE "")
FOREACH (VAR IN LISTS DISTRO)
    MESSAGE (VERBOSE "${VAR}=`${${VAR}}`")
endforeach()
MESSAGE (VERBOSE "")

CMAKE_HOST_SYSTEM_INFORMATION (RESULT CMAKE_LOGICAL_CORE_COUNT QUERY NUMBER_OF_LOGICAL_CORES)
MESSAGE (VERBOSE "CMAKE_LOGICAL_CORE_COUNT=${CMAKE_LOGICAL_CORE_COUNT}")
MESSAGE (VERBOSE "CMAKE_HOST_SYSTEM_NAME=${CMAKE_HOST_SYSTEM_NAME}")
MESSAGE (VERBOSE "")

SET (CMAKE_JOB_POOL_COMPILE ${CMAKE_LOGICAL_CORE_COUNT}-2)
SET (CMAKE_JOB_POOL_LINK ${CMAKE_LOGICAL_CORE_COUNT}-2)
SET (PARALLEL_LEVEL  ${CMAKE_LOGICAL_CORE_COUNT}-2) # UNIX Makefiles
SET (NINJA_PARALLEL_JOBS ${CMAKE_LOGICAL_CORE_COUNT}-2) # Ninja


# ========================================================================================================================================================================================================
#  Windows RC Compiler
# ========================================================================================================================================================================================================

# NOTE: If you are seeing "No CMAKE_RC_COMPILER could be found." from CMake, run from a VS Developer Terminal/Powershell window.


# ========================================================================================================================================================================================================
#  CONFIGURATION
# ========================================================================================================================================================================================================

# Base language overrides
SET (CMAKE_USER_MAKE_RULES_OVERRIDE ${GIT_ROOT_PATH}/cmake/flag_overrides.cmake)

# Project Configurations
SET (CMAKE_CONFIGURATION_TYPES DEBUG RELEASE FINAL DEBUG_TOOLS RELEASE_TOOLS)
SET (CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset the configurations to what we need" FORCE )

SET (MK_BUILD__CONFIGURATION_TYPES DEBUG RELEASE FINAL DEBUG_TOOLS RELEASE_TOOLS)
SET (MK_BUILD__EXTERNAL_CONFIGURATION_TYPES DEBUG RELEASE)

# Generation the solution name for the project
IF (CMAKE_GENERATOR MATCHES "Visual Studio.*")
    PROJECT ("Teikitu Superbuild" LANGUAGES C CXX DESCRIPTION "Teikitu Superbuild" HOMEPAGE_URL "https://github.com/aaye/teikitu_release")
ELSE ()
    PROJECT ("Teikitu Superbuild" LANGUAGES C CXX DESCRIPTION "Teikitu Superbuild" HOMEPAGE_URL "https://github.com/aaye/teikitu_release")
ENDIF ()
INCLUDE(${GIT_ROOT_PATH}/cmake/cmake_config.cmake) # =====================================================================================================================================================
INCLUDE(${GIT_ROOT_PATH}/cmake/cmake_macros.cmake) # =====================================================================================================================================================

LIST(APPEND CMAKE_MODULE_PATH ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY})
LIST(APPEND CMAKE_MODULE_PATH ${GIT_ROOT_PATH}/cmake)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules)
LIST (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

SET (MK_BUILD__SHARED_CMAKE_ARGS_DEFAULT
)

SET (MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT
    ${MK_BUILD__SHARED_CMAKE_ARGS_DEFAULT}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE_EXTERNAL}
)

SET (MK_BUILD__CMAKE_ARGS_DEFAULT
    ${MK_BUILD__SHARED_CMAKE_ARGS_DEFAULT}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)

IF (ANDROID)
    SET (MK_BUILD__SHARED_CMAKE_CACHE_ARGS_DEFAULT
        -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_ANDROID_NDK:STRING=${CMAKE_ANDROID_NDK}
        -DANDROID_TOOLCHAIN:STRING=${ANDROID_TOOLCHAIN}
        -DANDROID_ABI:STRING=${ANDROID_ABI}
        -DANDROID_PLATFORM:STRING=${ANDROID_PLATFORM}
        -DANDROID_ARM_MODE:STRING=${ANDROID_ARM_MODE}
        -DANDROID_STL:STRING=${ANDROID_STL}
        -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM:STRING=${CMAKE_FIND_ROOT_PATH_MODE_PROGRAM}
        -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY:STRING=${CMAKE_FIND_ROOT_PATH_MODE_LIBRARY}
        -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE:STRING=${CMAKE_FIND_ROOT_PATH_MODE_INCLUDE}
        -DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE:STRING=${CMAKE_FIND_ROOT_PATH_MODE_PACKAGE}
        -DCMAKE_TRY_COMPILE_TARGET_TYPE:STRING=${CMAKE_TRY_COMPILE_TARGET_TYPE}
    )

    # Toolchain file clears our the init flags from flag_overrides.cmake. Copy them back.
    STRING (APPEND CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_INIT})
    STRING (APPEND CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG_INIT})
    STRING (APPEND CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE_INIT})
    STRING (APPEND CMAKE_C_FLAGS ${CMAKE_C_FLAGS_INIT})
    STRING (APPEND CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG_INIT})
    STRING (APPEND CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE_INIT})
ELSE ()
    SET (MK_BUILD__SHARED_CMAKE_CACHE_ARGS_DEFAULT
        -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
        -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    )
ENDIF ()

SET (MK_BUILD__SHARED_CMAKE_CACHE_ARGS_DEFAULT
    ${MK_BUILD__SHARED_CMAKE_CACHE_ARGS_DEFAULT}

    -DCMAKE_INSTALL_PREFIX:STRING=${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}
    -DCMAKE_MESSAGE_LOG_LEVEL:STRING=${CMAKE_MESSAGE_LOG_LEVEL}

    -DCMAKE_C_STANDARD:STRING=${CMAKE_C_STANDARD}
    -DCMAKE_C_EXTENSIONS:BOOL=${CMAKE_C_EXTENSIONS}
    -DCMAKE_C_STANDARD_REQUIRED:BOOL=${CMAKE_C_STANDARD_REQUIRED}

    -DCMAKE_CXX_STANDARD:STRING=${CMAKE_CXX_STANDARD}
    -DCMAKE_CXX_EXTENSIONS:BOOL=${CMAKE_CXX_EXTENSIONS}
    -DCMAKE_CXX_STANDARD_REQUIRED:BOOL=${CMAKE_CXX_STANDARD_REQUIRED}

    # Note: any attempt to set the build_type <lang> flags directly (cached or set) breaks try_compile.

    -DCMAKE_C_FLAGS_DEBUG_INIT:STRING=${CMAKE_C_FLAGS_DEBUG}
    -DCMAKE_C_FLAGS_RELEASE_INIT:STRING=${CMAKE_C_FLAGS_RELEASE}

    -DCMAKE_CXX_FLAGS_DEBUG_INIT:STRING=${CMAKE_CXX_FLAGS_DEBUG}
    -DCMAKE_CXX_FLAGS_RELEASE_INIT:STRING=${CMAKE_CXX_FLAGS_RELEASE}
)

SET (MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT
    ${MK_BUILD__SHARED_CMAKE_CACHE_ARGS_DEFAULT}
    -DCMAKE_CONFIGURATION_TYPES:STRING=${MK_BUILD__EXTERNAL_CONFIGURATION_TYPES}
)

SET_APPEND_MSVC_COMPILER_OPTION (CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS CMAKE_CXX_FLAGS std:c++20 EHsc)
APPEND_GNU_COMPILER_OPTION (CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS std=c++20 D_CRT_SECURE_NO_WARNINGS)
APPEND_GNU_DISABLE_WARNING( CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS unused-function unused-command-line-argument deprecated-declarations deprecated-non-prototype strict-prototypes macro-redefined)

SET_APPEND_MSVC_COMPILER_OPTION (CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS CMAKE_C_FLAGS std:c17)
APPEND_GNU_COMPILER_OPTION (CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS std=c17 D_CRT_SECURE_NO_WARNINGS)
APPEND_GNU_DISABLE_WARNING( CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS unused-function unused-command-line-argument deprecated-declarations deprecated-non-prototype strict-prototypes macro-redefined)

IF (NOT CMAKE_CROSSCOMPILING)
    TGS_RETRIEVE_CACHE_LINE_DEFINITION ()
ELSE ()
    SET (MK_COMPILE_HARDWARE_CONSTRUCTIVE_INTERFERENCE_SIZE 64)
    SET (MK_COMPILE_HARDWARE_DESTRUCTIVE_INTERFERENCE_SIZE 64)
ENDIF ()

SET (MK_BUILD__CMAKE_CACHE_ARGS_DEFAULT
    ${MK_BUILD__SHARED_CMAKE_CACHE_ARGS_DEFAULT}

    #Note: the additional build types used by Teikitu are to modify its own compilation and should not have different compilation flags.

    -DCMAKE_CONFIGURATION_TYPES:STRING=${MK_BUILD__CONFIGURATION_TYPES}

    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_C_FLAGS_FINAL_INIT:STRING=${CMAKE_C_FLAGS_RELEASE}
    -DCMAKE_C_FLAGS_TOOLS_DEBUG_INIT:STRING=${CMAKE_C_FLAGS_DEBUG}
    -DCMAKE_C_FLAGS_TOOLS_RELEASE_INIT:STRING=${CMAKE_C_FLAGS_RELEASE}

    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_CXX_FLAGS_FINAL_INIT:STRING=${CMAKE_CXX_FLAGS_RELEASE}
    -DCMAKE_CXX_FLAGS_TOOLS_DEBUG_INIT:STRING=${CMAKE_CXX_FLAGS_DEBUG}
    -DCMAKE_CXX_FLAGS_TOOLS_RELEASE_INIT:STRING=${CMAKE_CXX_FLAGS_RELEASE}

    -DMK_BUILD__THREAD:STRING=${MK_BUILD__THREAD}
    -DMK_BUILD__UNIVERSAL:STRING=${MK_BUILD__UNIVERSAL}
    -DMK_BUILD__OS:STRING=${MK_BUILD__OS}
    -DMK_BUILD__DEVICE:STRING=${MK_BUILD__DEVICE}
    -DMK_FEATURE__GRAPHICS:STRING=${MK_FEATURE__GRAPHICS}
    -DMK_FEATURE__AUDIO:STRING=${MK_FEATURE__AUDIO}
    -DMK_BUILD__TARGET_HARDWARE:STRING=${MK_BUILD__TARGET_HARDWARE}
    -DMK_BUILD__OS_TEXT_WIDE:STRING=${MK_BUILD__OS_TEXT_WIDE}
#   -DMK_BUILD__AUTOMATION:STRING=${MK_BUILD__AUTOMATION}

    -DMK_BUILD__HARDWARE__CONSTRUCTIVE_INTERFERENCE_SIZE:STRING=${MK_COMPILE_HARDWARE_CONSTRUCTIVE_INTERFERENCE_SIZE}
    -DMK_BUILD__HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE:STRING=${MK_COMPILE_HARDWARE_DESTRUCTIVE_INTERFERENCE_SIZE}
)

# Standard report to stdout that reflects the build configuration used.
INCLUDE(${GIT_ROOT_PATH}/cmake/project_report.cmake)


# ========================================================================================================================================================================================================
#  EXTERNAL PROJECT - SINGLE PROJECTS WITH NO DEPENDENCIES
# ========================================================================================================================================================================================================

IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("DIRECTX" IN_LIST MK_BUILD__LIST) OR (("TEIKITU" IN_LIST MK_BUILD__LIST) AND ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "DX12")))
    EXTERNALPROJECT_ADD( DIRECTX_HEADERS_EXTERNAL #=======================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/directx/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}directx/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/microsoft/DirectX-Headers.git
        GIT_TAG                         v1.614.1
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

                                        -DDXHEADERS_BUILD_TEST:BOOL=OFF
                                        -DDXHEADERS_BUILD_GOOGLE_TEST:BOOL=OFF

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    # Once we have downloaded the repo, create a branch and patch it.
    ExternalProject_Add_Step(
        DIRECTX_HEADERS_EXTERNAL DIRECTX_SWITCH_AND_PATCH
        COMMAND ${CMAKE_COMMAND} -P ${GIT_ROOT_PATH}/teikitu_external/DirectX_Patch.cmake
        WORKING_DIRECTORY ${GIT_ROOT_PATH}/teikitu_external
        DEPENDEES download
        DEPENDERS configure
        INDEPENDENT TRUE
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("ZLIB" IN_LIST MK_BUILD__LIST) OR ("TIFF" IN_LIST MK_BUILD__LIST) OR ("TEIKITU" IN_LIST MK_BUILD__LIST))
    SET_APPEND_GNU_COMPILER_OPTION( CMAKE_CXX_FLAGS_FOR_ZLIB CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS D_GNU_SOURCE D__DARWIN_C_LEVEL=__DARWIN_C_FULL)
    SET_APPEND_GNU_COMPILER_OPTION( CMAKE_C_FLAGS_FOR_ZLIB CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS D_GNU_SOURCE D__DARWIN_C_LEVEL=__DARWIN_C_FULL)

    EXTERNALPROJECT_ADD( ZLIB_EXTERNAL #==================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/zlib/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}zlib/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/madler/zlib.git
        GIT_TAG                         v1.3.1
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_ZLIB}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_ZLIB}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("ZSTD" IN_LIST MK_BUILD__LIST) OR ("TIFF" IN_LIST MK_BUILD__LIST) OR ("TEIKITU" IN_LIST MK_BUILD__LIST))
    SET_APPEND_GNU_COMPILER_OPTION( CMAKE_C_FLAGS_FOR_ZSTD CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS)

    EXTERNALPROJECT_ADD( ZSTD_EXTERNAL #==================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/zstd/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}zstd/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/facebook/zstd.git
        GIT_TAG                         v1.5.6
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_ZSTD}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

        SOURCE_SUBDIR                   build/cmake
        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    # Once we have downloaded the repo, create a branch and patch it.
    ExternalProject_Add_Step(
        ZSTD_EXTERNAL ZSTD_SWITCH_AND_PATCH
        COMMAND ${CMAKE_COMMAND} -P ${GIT_ROOT_PATH}/teikitu_external/ZSTD_Patch.cmake
        WORKING_DIRECTORY ${GIT_ROOT_PATH}/teikitu_external
        DEPENDEES download
        DEPENDERS configure
        INDEPENDENT TRUE
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("LIBDEFLATE" IN_LIST MK_BUILD__LIST) OR ("TIFF" IN_LIST MK_BUILD__LIST) OR ("OPENEXR" IN_LIST MK_BUILD__LIST) OR ("TEIKITU" IN_LIST MK_BUILD__LIST))
    SET_APPEND_MSVC_COMPILER_OPTION( CMAKE_C_FLAGS_FOR_LIBDEFLATE CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS wd4113)

    EXTERNALPROJECT_ADD( LIBDEFLATE_EXTERNAL #============================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/libdeflate/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}libdeflate/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/ebiggers/libdeflate.git
        GIT_TAG                         v1.22
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_LIBDEFLATE}

                                        -DLIBDEFLATE_BUILD_SHARED_LIB:BOOL=OFF
                                        -DLIBDEFLATE_BUILD_TESTS:BOOL=OFF
                                        -DLIBDEFLATE_BUILD_GZIP:BOOL=OFF

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    # Once we have downloaded the repo, create a branch and patch it.
    ExternalProject_Add_Step(
        LIBDEFLATE_EXTERNAL LIBDEFLATE_SWITCH_AND_PATCH
        COMMAND ${CMAKE_COMMAND} -P ${GIT_ROOT_PATH}/teikitu_external/Libdeflate_Patch.cmake
        WORKING_DIRECTORY ${GIT_ROOT_PATH}/teikitu_external
        DEPENDEES download
        DEPENDERS configure
        INDEPENDENT TRUE
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("TIFF" IN_LIST MK_BUILD__LIST) OR ("TEIKITU" IN_LIST MK_BUILD__LIST))
    EXTERNALPROJECT_ADD( TIFF_EXTERNAL #==================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/tiff/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}tiff/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://gitlab.com/libtiff/libtiff.git
        GIT_TAG                         97aa7f403e35a1e2975fe38cdd0312ce5c420c3a
        GIT_SHALLOW                     FALSE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

                                        -DBUILD_SHARED_LIBS:BOOL=OFF
                                        -Dtiff-tools:BOOL=OFF
                                        -Dtiff-tests:BOOL=OFF
                                        -Dtiff-contrib:BOOL=OFF
                                        -Dtiff-docs:BOOL=OFF
                                        -Dcxx:BOOL=OFF
                                        -Dwin32-io:BOOL=OFF
                                        -Dunix-io:BOOL=OFF

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    ExternalProject_Add_StepDependencies (TIFF_EXTERNAL install LIBDEFLATE_EXTERNAL)
    ExternalProject_Add_StepDependencies (TIFF_EXTERNAL install ZLIB_EXTERNAL)
    ExternalProject_Add_StepDependencies (TIFF_EXTERNAL install ZSTD_EXTERNAL)

    # Once we have downloaded the repo, create a branch and patch it.
    ExternalProject_Add_Step(
        TIFF_EXTERNAL TIFF_SWITCH_AND_PATCH
        COMMAND ${CMAKE_COMMAND} -P ${GIT_ROOT_PATH}/teikitu_external/TIFF_Patch.cmake
        WORKING_DIRECTORY ${GIT_ROOT_PATH}/teikitu_external
        DEPENDEES download
        DEPENDERS configure
        INDEPENDENT TRUE
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("MIMALLOC" IN_LIST MK_BUILD__LIST) OR ("TEIKITU" IN_LIST MK_BUILD__LIST))
    EXTERNALPROJECT_ADD( MIMALLOC_EXTERNAL #==============================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/mimalloc/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}mimalloc/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/microsoft/mimalloc.git
        GIT_TAG                         fbd8b99c2b828428947d70fdc046bb55609be93e # branch: dev, HEAD
        GIT_SHALLOW                     FALSE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

                                        -DMI_OVERRIDE:BOOL=OFF
                                        -DMI_WIN_REDIRECT:BOOL=OFF
                                        -DMI_BUILD_SHARED:BOOL=OFF
                                        -DMI_BUILD_OBJECT:BOOL=OFF
                                        -DMI_BUILD_TESTS:BOOL=OFF
                                        -DMI_USE_CXX:BOOL=OFF
                                        -DMI_INSTALL_TOPLEVEL:BOOL=ON

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    # Once we have downloaded the repo, create a branch and patch it.
    ExternalProject_Add_Step(
        MIMALLOC_EXTERNAL MIMALLOC_SWITCH_AND_PATCH
        COMMAND ${CMAKE_COMMAND} -P ${GIT_ROOT_PATH}/teikitu_external/MiMalloc_Patch.cmake
        WORKING_DIRECTORY ${GIT_ROOT_PATH}/teikitu_external
        DEPENDEES download
        DEPENDERS configure
        INDEPENDENT TRUE
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("FLECS" IN_LIST MK_BUILD__LIST) OR ("TEIKITU" IN_LIST MK_BUILD__LIST))
    SET_APPEND_MSVC_COMPILER_OPTION( CMAKE_C_FLAGS_FOR_FLECS CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS wd4391)
    SET_APPEND_MSVC_COMPILER_OPTION( CMAKE_CXX_FLAGS_FOR_FLECS CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS wd4391)

    EXTERNALPROJECT_ADD( FLECS_EXTERNAL #=================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/flecs/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}flecs/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/SanderMertens/flecs.git
        GIT_TAG                         v4.1.1
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_FLECS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_FLECS}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


IF (("${MK_BUILD__OS_NAME}" STREQUAL "WINDOWS") AND (("ALL" IN_LIST MK_BUILD__LIST) OR ("ASSIMP" IN_LIST MK_BUILD__LIST) OR ("TEIKITU" IN_LIST MK_BUILD__LIST)))
    SET_APPEND_MSVC_COMPILER_OPTION( CMAKE_C_FLAGS_FOR_ASSIMP CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS wd4113)
    EXTERNALPROJECT_ADD( ASSIMP_EXTERNAL #================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/asset_import/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}asset_import/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/assimp/assimp.git
        GIT_TAG                         v6.0.2
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


# ========================================================================================================================================================================================================
#  EXTERNAL PROJECT - TOOLS - OPEN EXR
# ========================================================================================================================================================================================================

IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("IMATH" IN_LIST MK_BUILD__LIST) OR ("OPENEXR" IN_LIST MK_BUILD__LIST) OR ("OPENUSD" IN_LIST MK_BUILD__LIST))
    EXTERNALPROJECT_ADD( IMATH_EXTERNAL #=================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/imath/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}imath/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/AcademySoftwareFoundation/Imath.git
        GIT_TAG                         v3.1.9
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

                                        -DPYTHON:BOOL=OFF
                                        -DBUILD_DOCS:BOOL=OFF
                                        -DIMATH_INSTALL_PKG_CONFIG:BOOL=ON
                                        -DBUILD_SHARED_LIBS:BOOL=OFF
                                        -DBUILD_TESTING:BOOL=OFF

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("IMATH" IN_LIST MK_BUILD__LIST) OR ("OPENEXR" IN_LIST MK_BUILD__LIST) OR ("OPENUSD" IN_LIST MK_BUILD__LIST))
    SET_APPEND_MSVC_COMPILER_OPTION( CMAKE_CXX_FLAGS_FOR_OPENEXR CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS D_SILENCE_CXX20_OLD_SHARED_PTR_ATOMIC_SUPPORT_DEPRECATION_WARNING wd4113)
    APPEND_GNU_COMPILER_OPTION( CMAKE_CXX_FLAGS_FOR_OPENEXR D_SILENCE_CXX20_OLD_SHARED_PTR_ATOMIC_SUPPORT_DEPRECATION_WARNING)
    SET_APPEND_GNU_COMPILER_OPTION( CMAKE_C_FLAGS_FOR_OPENEXR CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS D_GNU_SOURCE )

    EXTERNALPROJECT_ADD( OPENEXR_EXTERNAL #===============================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/openexr/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}openexr/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/AcademySoftwareFoundation/openexr.git
        GIT_TAG                         release
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

                                        -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON
                                        -DOPENEXR_FORCE_INTERNAL_DEFLATE=ON # Windows does not natively support pkg_check_modules

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_OPENEXR}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_OPENEXR}

                                        -DOPENEXR_INSTALL_TOOLS:BOOL=OFF
                                        -DOPENEXR_INSTALL_EXAMPLES:BOOL=OFF
                                        -DOPENEXR_INSTALL_DOCS:BOOL=OFF
                                        -DBUILD_WEBSITE:BOOL=OFF
                                        -DOPENEXR_BUILD_PYTHON:BOOL=OFF
                                        -DBUILD_TESTING:BOOL=OFF
                                        -DOPENEXR_INSTALL_PKG_CONFIG:BOOL=ON
                                        -DOPENEXR_BUILD_TOOLS:BOOL=OFF
                                        -DBUILD_SHARED_LIBS:BOOL=OFF

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    ExternalProject_Add_StepDependencies (OPENEXR_EXTERNAL install IMATH_EXTERNAL)
    ExternalProject_Add_StepDependencies (OPENEXR_EXTERNAL install LIBDEFLATE_EXTERNAL)
ENDIF ()


# ========================================================================================================================================================================================================
#  EXTERNAL PROJECT - TOOLS - OPEN USD AND OPEN SUB DIV
# ========================================================================================================================================================================================================

IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("ONEAPI" IN_LIST MK_BUILD__LIST) OR ("OPENUSD" IN_LIST MK_BUILD__LIST))
    SET_APPEND_GNU_COMPILER_OPTION (CMAKE_CXX_FLAGS_FOR_ONEAPI CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS)
    EXTERNALPROJECT_ADD( ONEAPI_EXTERNAL #================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/oneapi/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}oneapi/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/oneapi-src/oneTBB.git
        GIT_TAG                         v2021.9.0
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_ONEAPI}

                                        -DTBB_TEST:BOOL=OFF
                                        -DTBB_EXAMPLES:BOOL=OFF
                                        -DTBBMALLOC_BUILD:BOOL=OFF
                                        -DBUILD_SHARED_LIBS:BOOL=OFF

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("BOOST" IN_LIST MK_BUILD__LIST) OR ("OPENUSD" IN_LIST MK_BUILD__LIST))
    SET_APPEND_MSVC_COMPILER_OPTION( CMAKE_CXX_FLAGS_FOR_BOOST CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS wd4245 wd4005)

    EXTERNALPROJECT_ADD( BOOST_EXTERNAL #=================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/boost/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}boost/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/boostorg/boost.git
        GIT_TAG                         boost-1.83.0
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_BOOST}

                                        -DBOOST_ENABLE_PYTHON:BOOL=ON

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("GLFW" IN_LIST MK_BUILD__LIST) OR ("OPENSUBDIV" IN_LIST MK_BUILD__LIST) OR ("OPENUSD" IN_LIST MK_BUILD__LIST))
    SET_APPEND_GNU_COMPILER_OPTION( CMAKE_C_FLAGS_FOR_GLFW CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS D_GNU_SOURCE )

    EXTERNALPROJECT_ADD( GLFW_EXTERNAL #==================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/glfw/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}glfw/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/glfw/glfw.git
        GIT_TAG                         3.3.8
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_GLFW}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("OPENSUBDIV" IN_LIST MK_BUILD__LIST) OR ("OPENUSD" IN_LIST MK_BUILD__LIST))
    EXTERNALPROJECT_ADD( OPENSUBDIV_EXTERNAL #============================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/opensubdiv/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}opensubdiv/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/PixarAnimationStudios/OpenSubdiv.git
        GIT_TAG                         release
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

                                        -DNO_EXAMPLES:BOOL=ON         # disable examples build
                                        -DNO_TUTORIALS:BOOL=ON        # disable tutorials build
                                        -DNO_REGRESSION:BOOL=ON       # disable regression tests build
                                        -DNO_PTEX:BOOL=ON             # disable PTex support
                                        -DNO_DOC:BOOL=ON              # disable documentation build
                                        -DNO_OMP:BOOL=ON              # disable OpenMP
                                        -DNO_TBB:BOOL=ON              # disable TBB
                                        -DNO_CUDA:BOOL=ON             # disable CUDA
                                        -DNO_OPENCL:BOOL=ON           # disable OpenCL
                                        -DNO_CLEW:BOOL=ON             # disable CLEW wrapper library
                                        -DNO_METAL:BOOL=ON            # disable Metal
                                        -DNO_DX:BOOL=ON               # disable DirectX

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    ExternalProject_Add_StepDependencies (OPENSUBDIV_EXTERNAL install GLFW_EXTERNAL)
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("ONEAPI" IN_LIST MK_BUILD__LIST) OR ("OPENUSD" IN_LIST MK_BUILD__LIST))
    SET_APPEND_MSVC_COMPILER_OPTION( CMAKE_CXX_FLAGS_FOR_OPENUSD CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS wd4996)
    APPEND_GNU_DISABLE_WARNING( CMAKE_CXX_FLAGS_FOR_OPENUSD self-assign-overloaded)
    SET_APPEND_GNU_COMPILER_OPTION (CMAKE_C_FLAGS_FOR_OPENUSD CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS D_GNU_SOURCE)

    EXTERNALPROJECT_ADD( OPENUSD_EXTERNAL #===============================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/openusd/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}openusd/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/PixarAnimationStudios/OpenUSD.git
        GIT_TAG                         v24.11 # 9b0c13b2efa6233c8a4a4af411833628c5435bde / release 11-23-2024
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      -DCMAKE_INSTALL_PREFIX=${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}
                                        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE_EXTERNAL}

                                        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
                                        -DCMAKE_C_STANDARD=${CMAKE_C_STANDARD}
                                        -DCMAKE_C_EXTENSIONS=${CMAKE_C_EXTENSIONS}
                                        -DCMAKE_C_STANDARD_REQUIRED=${CMAKE_C_STANDARD_REQUIRED}

                                        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
                                        -DCMAKE_CXX_STANDARD=17
                                        -DCMAKE_CXX_EXTENSIONS=OFF
                                        -DCMAKE_CXX_STANDARD_REQUIRED=ON

    #                                   -DPXR_MALLOC_LIBRARY:path=/usr/local/lib/libjemalloc.so

                                        -DTBB_INCLUDE_DIR=${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}/include/
                                        -DTBB_LIBRARY=${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}lib/

                                        -DBoost_ROOT=${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

                                        -DOPENSUBDIV_ROOT_DIR=${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_OPENUSD}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_OPENUSD}

                                        -DBoost_NO_BOOST_CMAKE:BOOL=OFF
                                        -DPXR_ENABLE_ONEAPI_TBB:BOOL=ON

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    # Once we have downloaded the repo, create a branch and patch it.
    ExternalProject_Add_Step(
        OPENUSD_EXTERNAL OPENUSD_SWITCH_AND_PATCH
        COMMAND ${CMAKE_COMMAND} -P ${GIT_ROOT_PATH}/teikitu_external/OpenUSD_Patch.cmake
        WORKING_DIRECTORY ${GIT_ROOT_PATH}/teikitu_external
        DEPENDEES download
        DEPENDERS configure
        INDEPENDENT TRUE
    )

    ExternalProject_Add_StepDependencies (OPENUSD_EXTERNAL install MIMALLOC_EXTERNAL)
    ExternalProject_Add_StepDependencies (OPENUSD_EXTERNAL install ONEAPI_EXTERNAL)
    ExternalProject_Add_StepDependencies (OPENUSD_EXTERNAL install OPENEXR_EXTERNAL)
    ExternalProject_Add_StepDependencies (OPENUSD_EXTERNAL install BOOST_EXTERNAL)
    ExternalProject_Add_StepDependencies (OPENUSD_EXTERNAL install OPENSUBDIV_EXTERNAL)
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("SLANG" IN_LIST MK_BUILD__LIST))
    IF (MK_IDE__MSVC)
        SET(SLANG_PRESET vs2022)
    ELSE ()
        SET(SLANG_PRESET default)
    ENDIF ()

    EXTERNALPROJECT_ADD( SLANG_EXTERNAL #=====================================================================================================================================================================
        SOURCE_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}slang/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}slang/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/shader-slang/slang.git
        GIT_TAG                         v2025.15.1 # 
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1

        BUILD_COMMAND                   ${CMAKE_COMMAND} --preset ${SLANG_PRESET}
        COMMAND                         ${CMAKE_COMMAND} --build --preset releaseWithDebugInfo
        INSTALL_COMMAND                 ""
        TEST_COMMAND                    ""
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("TEIKITU" IN_LIST MK_BUILD__LIST) OR ("IMGUI" IN_LIST MK_BUILD__LIST))
    EXTERNALPROJECT_ADD( IMGUI_EXTERNAL #=====================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/imgui/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}imgui/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/ocornut/imgui.git
        GIT_TAG                         v1.92.2 # 059b751e41fe508b87b43a7fa2b8a500beb709d8
        GIT_SHALLOW                     FALSE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        CONFIGURE_COMMAND               ""
        BUILD_COMMAND                   ""
        INSTALL_COMMAND                 ""
        TEST_COMMAND                    ""
        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("VULKAN" IN_LIST MK_BUILD__LIST) OR (("TEIKITU" IN_LIST MK_BUILD__LIST) AND ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "VULKAN")))
    IF (CMAKE_HOST_WIN32)
        SET (CMAKE_C_FLAGS_FOR_VOLK ${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS})
        SET (CMAKE_CXX_FLAGS_FOR_VOLK ${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS})
    ELSE ()
        SET_APPEND_GNU_COMPILER_OPTION (CMAKE_C_FLAGS_FOR_VOLK CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS "I$ENV{VULKAN_SDK}/include")
        SET_APPEND_GNU_COMPILER_OPTION (CMAKE_CXX_FLAGS_FOR_VOLK CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS "I$ENV{VULKAN_SDK}/include")
    ENDIF ()

    EXTERNALPROJECT_ADD( VOLK_EXTERNAL #==================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/volk/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}volk/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/zeux/volk.git
        GIT_TAG                         vulkan-sdk-1.4.321.0
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag
        INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}
                                        -DVOLK_INSTALL=ON

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_VOLK}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_VOLK}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1
        BUILD_ALWAYS                    0

        LOG_DOWNLOAD                    1
        LOG_UPDATE                      1
        LOG_CONFIGURE                   1
        LOG_BUILD                       1
        LOG_INSTALL                     1
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()




# ========================================================================================================================================================================================================
#  FETCH ASSETS
# ========================================================================================================================================================================================================

EXTERNALPROJECT_ADD( ASSETS_EXTERNAL #====================================================================================================================================================================
    SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_assets/
    GIT_REPOSITORY                  https://github.com/aaye/teikitu_assets.git
    GIT_TAG                         main
    GIT_SHALLOW                     TRUE
    GIT_PROGRESS                    FALSE
    GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT
    CONFIGURE_COMMAND               ""
    BUILD_COMMAND                   ""
    INSTALL_COMMAND                 ""
    TEST_COMMAND                    ""
    TEST_AFTER_INSTALL              0
    DOWNLOAD_NO_PROGRESS            1
    LOG_DOWNLOAD                    1
    LOG_UPDATE                      1
    LOG_CONFIGURE                   1
    LOG_BUILD                       1
    LOG_INSTALL                     1
    LOG_MERGED_STDOUTERR            1
    LOG_OUTPUT_ON_FAILURE           1
)

#https://github.com/AcademySoftwareFoundation/openexr-images/blob/df16e765fee28a947244657cae3251959ae63c00/TestImages/WideColorGamut.exr


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("DIRECTX" IN_LIST MK_BUILD__LIST) OR (("TEIKITU" IN_LIST MK_BUILD__LIST) AND ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "DX12")))
    EXTERNALPROJECT_ADD( DIRECTX_AGILE_EXTERNAL #=========================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/__directx_agile
        URL                             https://www.nuget.org/api/v2/package/Microsoft.Direct3D.D3D12
        CONFIGURE_COMMAND               ""
        BUILD_COMMAND                   ""
        INSTALL_COMMAND                 ""
        TEST_COMMAND                    ""
        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1
        LOG_DOWNLOAD                    1
        LOG_UPDATE                      1
        LOG_CONFIGURE                   1
        LOG_BUILD                       1
        LOG_INSTALL                     1
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("DIRECTX" IN_LIST MK_BUILD__LIST) OR (("TEIKITU" IN_LIST MK_BUILD__LIST) AND ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "DX12")))
    EXTERNALPROJECT_ADD( WIN_PIX_EXTERNAL #===============================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/__win_pix_event_runtime
        URL                             https://www.nuget.org/api/v2/package/WinPixEventRuntime
        CONFIGURE_COMMAND               ""
        BUILD_COMMAND                   ""
        INSTALL_COMMAND                 ""
        TEST_COMMAND                    ""
        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1
        LOG_DOWNLOAD                    1
        LOG_UPDATE                      1
        LOG_CONFIGURE                   1
        LOG_BUILD                       1
        LOG_INSTALL                     1
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


# ========================================================================================================================================================================================================
#  TEIKITU
# ========================================================================================================================================================================================================

IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("TEIKITU" IN_LIST MK_BUILD__LIST))
    EXTERNALPROJECT_ADD( TEIKITU_EXTERNAL #===============================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_private/
        BINARY_DIR                      ${MK_BUILD__BUILD_DIRECTORY}/teikitu/
        INSTALL_DIR                     ${MK_BUILD__INSTALL_DIRECTORY}

        DOWNLOAD_COMMAND                ""

        CMAKE_ARGS                      ${MK_BUILD__CMAKE_ARGS_DEFAULT}

                                        -DMK_BUILD__PRELOAD__MALLOC_OVERRIDE:BOOL=OFF
                                        -DMK_BUILD__MIMALLOC_ALLOCATOR:BOOL=ON
                                        -DMK_BUILD__MIMALLOC_DEFAULT:BOOL=ON

        CMAKE_CACHE_ARGS                ${MK_BUILD__CMAKE_CACHE_ARGS_DEFAULT}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    IF (("DIRECTX" IN_LIST MK_BUILD__LIST) OR ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "DX12"))
        ExternalProject_Add_StepDependencies (TEIKITU_EXTERNAL install DIRECTX_HEADERS_EXTERNAL)
        ExternalProject_Add_StepDependencies (TEIKITU_EXTERNAL install DIRECTX_AGILE_EXTERNAL)
        ExternalProject_Add_StepDependencies (TEIKITU_EXTERNAL install WIN_PIX_EXTERNAL)
    ENDIF ()
    IF (("VULKAN" IN_LIST MK_BUILD__LIST) OR ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "VULKAN"))
        ExternalProject_Add_StepDependencies (TEIKITU_EXTERNAL install VOLK_EXTERNAL)
    ENDIF ()
    ExternalProject_Add_StepDependencies (TEIKITU_EXTERNAL install TIFF_EXTERNAL)
    ExternalProject_Add_StepDependencies (TEIKITU_EXTERNAL install MIMALLOC_EXTERNAL)
    #ExternalProject_Add_StepDependencies (TEIKITU_EXTERNAL install OPENEXR_EXTERNAL)


    EXTERNALPROJECT_ADD( TEIKITU_TOOLS_EXTERNAL #=========================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_tools/
        BINARY_DIR                      ${MK_BUILD__BUILD_DIRECTORY}/teikitu_tools/
        INSTALL_DIR                     ${MK_BUILD__INSTALL_DIRECTORY}

        DOWNLOAD_COMMAND                ""

        CMAKE_ARGS                      ${MK_BUILD__CMAKE_ARGS_DEFAULT}

                                        -DMK_BUILD__PRELOAD__MALLOC_OVERRIDE:BOOL=OFF
                                        -DMK_BUILD__MIMALLOC_ALLOCATOR:BOOL=ON
                                        -DMK_BUILD__MIMALLOC_DEFAULT:BOOL=ON

        CMAKE_CACHE_ARGS                ${MK_BUILD__CMAKE_CACHE_ARGS_DEFAULT}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    ExternalProject_Add_StepDependencies (TEIKITU_TOOLS_EXTERNAL install TEIKITU_EXTERNAL)
    #ExternalProject_Add_StepDependencies (TEIKITU_TOOLS_EXTERNAL install OPENSUBDIV_EXTERNAL)
    #ExternalProject_Add_StepDependencies (TEIKITU_TOOLS_EXTERNAL install OPENUSD_EXTERNAL)


    EXTERNALPROJECT_ADD( TEIKITU_SAMPLES_EXTERNAL #=======================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_samples/
        BINARY_DIR                      ${MK_BUILD__BUILD_DIRECTORY}/teikitu_samples/
        INSTALL_DIR                     ${MK_BUILD__INSTALL_DIRECTORY}

        DOWNLOAD_COMMAND                ""

        CMAKE_ARGS                      ${MK_BUILD__CMAKE_ARGS_DEFAULT}

                                        -DMK_BUILD__PRELOAD__MALLOC_OVERRIDE:BOOL=OFF
                                        -DMK_BUILD__MIMALLOC_ALLOCATOR:BOOL=ON
                                        -DMK_BUILD__MIMALLOC_DEFAULT:BOOL=ON

        CMAKE_CACHE_ARGS                ${MK_BUILD__CMAKE_CACHE_ARGS_DEFAULT}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    ExternalProject_Add_StepDependencies (TEIKITU_SAMPLES_EXTERNAL install TEIKITU_EXTERNAL)

ENDIF ()


# ========================================================================================================================================================================================================
#  DOCUMENTATION
# ========================================================================================================================================================================================================

IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("ICONV" IN_LIST MK_BUILD__LIST) OR ("DOXYGEN" IN_LIST MK_BUILD__LIST))
    EXTERNALPROJECT_ADD( ICONV_EXTERNAL #=================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/__iconv
        URL                             https://github.com/pffang/libiconv-for-Windows/releases/download/1.18-eed6782/libiconv-for-Windows_prebuilt.zip
        CONFIGURE_COMMAND               ""
        BUILD_COMMAND                   ""
        INSTALL_COMMAND                 ""
        TEST_COMMAND                    ""
        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1
        LOG_DOWNLOAD                    1
        LOG_UPDATE                      1
        LOG_CONFIGURE                   1
        LOG_BUILD                       1
        LOG_INSTALL                     1
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )
ENDIF ()


IF (("ALL" IN_LIST MK_BUILD__LIST) OR ("DOXYGEN" IN_LIST MK_BUILD__LIST))
    SET_APPEND_MSVC_COMPILER_OPTION (CMAKE_C_FLAGS_FOR_DOXYGEN CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS wd4005 wd4333 wd4391)
    APPEND_GNU_COMPILER_OPTION (CMAKE_C_FLAGS_FOR_DOXYGEN D_GNU_SOURCE)
    SET_APPEND_MSVC_COMPILER_OPTION( CMAKE_CXX_FLAGS_FOR_DOXYGEN CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS wd4005 wd4333 wd4391)

    IF ("${MK_BUILD__OS_NAME}" STREQUAL "WINDOWS")
        SET (Iconv_INCLUDE_DIRS "${GIT_ROOT_PATH}/teikitu_external/__iconv/")
        IF (MK_BUILD__HARDWARE__X64)
            IF (${CMAKE_BUILD_TYPE_EXTERNAL} STREQUAL "DEBUG")
                SET (Iconv_LIBRARIES "${GIT_ROOT_PATH}/teikitu_external/__iconv/x64/DebugStatic/libiconvStaticD.lib")
            ELSE ()
                SET (Iconv_LIBRARIES "${GIT_ROOT_PATH}/teikitu_external/__iconv/x64/ReleaseStatic/libiconvStatic.lib")
            ENDIF ()
        ELSEIF (MK_BUILD__HARDWARE__ARM)
            IF (${CMAKE_BUILD_TYPE_EXTERNAL} STREQUAL "DEBUG")
                SET (Iconv_LIBRARIES "${GIT_ROOT_PATH}/teikitu_external/__iconv/ARM64/DebugStatic/libiconvStaticD.lib")
            ELSE ()
                SET (Iconv_LIBRARIES "${GIT_ROOT_PATH}/teikitu_external/__iconv/ARM64/ReleaseStatic/libiconvStatic.lib")
            ENDIF ()
        ELSE ()
            MESSAGE (FATAL_ERROR "Unsupported hardware type")
        ENDIF ()
    ELSE ()
        FIND_PACKAGE (Iconv REQUIRED)
    ENDIF ()

    EXTERNALPROJECT_ADD( DOXYGEN_EXTERNAL #===================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/doxygen/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}doxygen/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/doxygen/doxygen.git
        GIT_TAG                         Release_1_12_0
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE

        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}
                                        -DMK_BUILD__OS_NAME=${MK_BUILD__OS_NAME}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

                                        -DCMAKE_REQUIRED_QUIET:BOOL=OFF
                                        -DICONV_USE_STATIC_LIBS:BOOL=ON
                                        -DIconv_INCLUDE_DIRS:STRING=${Iconv_INCLUDE_DIRS}
                                        -DIconv_LIBRARIES:STRING=${Iconv_LIBRARIES}

                                        -Dbuild_app:BOOL=ON

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    # Once we have downloaded the repo, create a branch and patch it.
    ExternalProject_Add_Step(
        DOXYGEN_EXTERNAL DOXYGEN_SWITCH_AND_PATCH
        COMMAND ${CMAKE_COMMAND} -P ${GIT_ROOT_PATH}/teikitu_external/Doxygen_Patch.cmake
        WORKING_DIRECTORY ${GIT_ROOT_PATH}/teikitu_external
        DEPENDEES download
        DEPENDERS configure
        INDEPENDENT TRUE
    )

    ExternalProject_Add_StepDependencies (DOXYGEN_EXTERNAL install ICONV_EXTERNAL)
ENDIF ()




# ========================================================================================================================================================================================================
#  UTILITIES
# ========================================================================================================================================================================================================

IF ("CMAKE" IN_LIST MK_BUILD__LIST)
    EXTERNALPROJECT_ADD( CMAKE_EXTERNAL #=====================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/cmake/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}cmake/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/kitware/cmake.git
        GIT_TAG                         v4.1.1 # ba8c4a15f10e2636405106ff0dc92b79d94a616c
        GIT_SHALLOW                     TRUE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    # Once we have downloaded the repo, create a branch and patch it.
    ExternalProject_Add_Step(
        CMAKE_EXTERNAL CMAKE_SWITCH_AND_PATCH
        COMMAND ${CMAKE_COMMAND} -P ${GIT_ROOT_PATH}/teikitu_external/Cmake_Patch.cmake
        WORKING_DIRECTORY ${GIT_ROOT_PATH}/teikitu_external
        DEPENDEES download
        DEPENDERS configure
        INDEPENDENT TRUE
    )
ENDIF ()


IF ("UNCRUSTIFY" IN_LIST MK_BUILD__LIST)
    EXTERNALPROJECT_ADD( UNCRUSTIFY_EXTERNAL #================================================================================================================================================================
        SOURCE_DIR                      ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/uncrustify/
        BINARY_DIR                      ${MK_BUILD__EXTERNAL_BUILD_DIRECTORY}uncrustify/
        INSTALL_DIR                     ${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}

        GIT_REPOSITORY                  https://github.com/uncrustify/uncrustify.git
        GIT_TAG                         uncrustify-0.81.0 # 059b751e41fe508b87b43a7fa2b8a500beb709d8
        GIT_SHALLOW                     FALSE
        GIT_PROGRESS                    FALSE
        GIT_REMOTE_UPDATE_STRATEGY      REBASE_CHECKOUT

        UPDATE_COMMAND                  "" # No need to update the repo given we are pulling a specific version tag

        CMAKE_ARGS                      ${MK_BUILD__EXTERNAL_CMAKE_ARGS_DEFAULT}

        CMAKE_CACHE_ARGS                ${MK_BUILD__EXTERNAL_CMAKE_CACHE_ARGS_DEFAULT}

                                        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS_FOR_EXTERNAL_PROJECTS}
                                        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS_FOR_EXTERNAL_PROJECTS}

        TEST_AFTER_INSTALL              0
        DOWNLOAD_NO_PROGRESS            1

        LOG_DOWNLOAD                    ${MK_BUILD__LOG_TO_FILE}
        LOG_UPDATE                      ${MK_BUILD__LOG_TO_FILE}
        LOG_CONFIGURE                   ${MK_BUILD__LOG_TO_FILE}
        LOG_BUILD                       ${MK_BUILD__LOG_TO_FILE}
        LOG_INSTALL                     ${MK_BUILD__LOG_TO_FILE}
        LOG_MERGED_STDOUTERR            1
        LOG_OUTPUT_ON_FAILURE           1
    )

    # Once we have downloaded the repo, create a branch and patch it.
    ExternalProject_Add_Step(
        UNCRUSTIFY_EXTERNAL UNCRUSTIFY_SWITCH_AND_PATCH
        COMMAND ${CMAKE_COMMAND} -P ${GIT_ROOT_PATH}/teikitu_external/Uncrustify_Patch.cmake
        WORKING_DIRECTORY ${GIT_ROOT_PATH}/teikitu_external
        DEPENDEES download
        DEPENDERS configure
        INDEPENDENT TRUE
    )
ENDIF ()
