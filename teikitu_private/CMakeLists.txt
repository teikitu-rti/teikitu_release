# 015482FC-A4BD-4E1C-AE49-A30E5728D73A
CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
CMAKE_POLICY(VERSION 3.31)
CMAKE_POLICY(SET CMP0057 NEW)
CMAKE_POLICY(SET CMP0015 NEW)
CMAKE_POLICY(SET CMP0072 NEW)
CMAKE_POLICY(SET CMP0091 NEW)
SET (CMAKE_OBJECT_PATH_MAX 1024)

INCLUDE (ExternalProject)


# ========================================================================================================================================================================================================
#  OPTIONS
# ========================================================================================================================================================================================================




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
#  CONFIGURATION
# ========================================================================================================================================================================================================

# Base language overrides
SET (CMAKE_USER_MAKE_RULES_OVERRIDE ${GIT_ROOT_PATH}/cmake/flag_overrides.cmake)

# Project Configurations
SET (CMAKE_CONFIGURATION_TYPES DEBUG RELEASE FINAL TOOLS_DEBUG TOOLS_RELEASE)
SET (CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset the configurations to what we need" FORCE )

# Generate the root project name with a declaration of the git branch that was used.
SET (MK_PROJECT_NAME "Teikitu Gaming System")
IF (GIT_FOUND)
    SET (MK_PROJECT_NAME "${MK_PROJECT_NAME} (${GIT_BRANCH})")
ELSE ()
    SET (MK_PROJECT_NAME "${MK_PROJECT_NAME} (Unknown)")
ENDIF ()
SET(STREAM_FILE_CONTENTS "SET (MK_PROJECT_NAME \"${MK_PROJECT_NAME}\")\n")

# Generation the solution name for the project
PROJECT (${MK_PROJECT_NAME} LANGUAGES C CXX DESCRIPTION "Teikitu Compile Test")
INCLUDE(${GIT_ROOT_PATH}/cmake/cmake_config.cmake) # =====================================================================================================================================================
SET (MK_TEIKITU_PROJECT_NAME "${MK_PROJECT_NAME}")
IF (CMAKE_GENERATOR MATCHES "Visual Studio.*")
    PROJECT (${MK_TEIKITU_PROJECT_NAME} LANGUAGES CXX DESCRIPTION "Teikitu Realtime Interactive Engine Platform" HOMEPAGE_URL "https://github.com/aaye/teikitu_release" VERSION 5.22.0)
ELSE ()
    PROJECT (${MK_TEIKITU_PROJECT_NAME} LANGUAGES C DESCRIPTION "Teikitu Realtime Interactive Engine Platform" HOMEPAGE_URL "https://github.com/aaye/teikitu_release" VERSION 5.22.0)
ENDIF ()


# Teikitu Config #========================================================================================================================================================================================
INCLUDE(${GIT_ROOT_PATH}/cmake/teikitu_config.cmake) # ===================================================================================================================================================
INCLUDE(${GIT_ROOT_PATH}/cmake/cmake_macros.cmake) # =====================================================================================================================================================
SET (MK_BUILD_PACKAGE_PROJECT_NAME "teikitu")


# ========================================================================================================================================================================================================
#  Build Teikitu, Teikitu SDK, Teikitu Samples, Teikitu Tools - can include your project in here as well to have a single solution
# ========================================================================================================================================================================================================

# Disable Vulkan and Metal
IF ("${MK_FEATURE__GRAPHICS}" STREQUAL "METAL")
    SET (MK_FEATURE__GRAPHICS "REF")
ENDIF ()

# Libraries and Executables
SET (PROJECT_FOLDER_NAME_LIST "teikitu_private/src" "teikitu_private/tests")
FOREACH ( PROJECT_FOLDER_NAME IN ITEMS ${PROJECT_FOLDER_NAME_LIST} )
    #MESSAGE("SEARCHING DIRECTORY: ${GIT_ROOT_PATH}/${PROJECT_FOLDER_NAME}/*")
    FILE(GLOB FOLDER_LIST LIST_DIRECTORIES true "${GIT_ROOT_PATH}/${PROJECT_FOLDER_NAME}/*" )
    FOREACH ( FOLDER_NAME IN ITEMS ${FOLDER_LIST} )
        IF (IS_DIRECTORY ${FOLDER_NAME} AND EXISTS ${FOLDER_NAME}/CMakeLists.txt)
            #MESSAGE("ADDING PROJECT: " ${FOLDER_NAME})
            CMAKE_PATH ( SET FOLDER_NAME_NORMALIZED NORMALIZE "${FOLDER_NAME}" )
            ADD_SUBDIRECTORY ("${FOLDER_NAME_NORMALIZED}")
        ENDIF ()
    ENDFOREACH ()
ENDFOREACH ()

# Cmake files in the project tree
TGS_ADD_CMAKE_FILE( build_files__cmake build_files__cmake "-" "-" "" "${GIT_ROOT_PATH}/cmake/cmake_config.cmake" )
TGS_ADD_CMAKE_FILE( build_files__cmake build_files__cmake "-" "-" "" "${GIT_ROOT_PATH}/cmake/cmake_macros.cmake" )
TGS_ADD_CMAKE_FILE( build_files__cmake build_files__cmake "-" "-" "" "${GIT_ROOT_PATH}/cmake/cmake_options.cmake" )
TGS_ADD_CMAKE_FILE( build_files__cmake build_files__cmake "-" "-" "" "${GIT_ROOT_PATH}/cmake/flag_overrides.cmake" )
TGS_ADD_CMAKE_FILE( build_files__cmake build_files__cmake "-" "-" "" "${GIT_ROOT_PATH}/cmake/project_report.cmake" )

ADD_CUSTOM_TARGET( CMakeFiles SOURCES ${build_files__cmake})


# ========================================================================================================================================================================================================
#  BUILD REPORT
# ========================================================================================================================================================================================================

# Standard report to stdout that reflects the build configuration used.
INCLUDE(${GIT_ROOT_PATH}/cmake/project_report.cmake)
