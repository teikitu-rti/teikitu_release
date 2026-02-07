# 015482FC-A4BD-4E1C-AE49-A30E5728D73A
CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
CMAKE_POLICY(VERSION 3.31)

# SHA fbd8b99c2b828428947d70fdc046bb55609be93e

# ========================================================================================================================================================================================================
#  FIND GIT
# ========================================================================================================================================================================================================

FIND_PACKAGE (Git) #======================================================================================================================================================================================
IF (GIT_FOUND)
    # WARNING: This must run in the root teikitu git repo for the pathing to work.
    EXECUTE_PROCESS(
        COMMAND ${GIT_EXECUTABLE} rev-parse --show-toplevel
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_ROOT_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE GIT_COMMAND_RESULT
    )
ELSE ()
    MESSAGE (FATAL_ERROR "Could not discover the git. Required for the script to work")
ENDIF ()

IF (NOT GIT_ROOT_PATH)
    MESSAGE (FATAL_ERROR "Could not discover the git repo root. Required for the script to work")
ENDIF ()

SET (WORKING_DIR ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/mimalloc/)



##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(GIT_PATCH patch_file description)
    EXECUTE_PROCESS(
        COMMAND ${GIT_EXECUTABLE} apply "${GIT_ROOT_PATH}/teikitu_external/${patch_file}"
        WORKING_DIRECTORY ${WORKING_DIR}
    )

    EXECUTE_PROCESS(
        COMMAND ${GIT_EXECUTABLE} add -A
        WORKING_DIRECTORY ${WORKING_DIR}
        OUTPUT_VARIABLE GIT_COMMAND_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    EXECUTE_PROCESS(
        COMMAND ${GIT_EXECUTABLE} commit -a -u --no-edit -m ${description}
        WORKING_DIRECTORY ${WORKING_DIR}
        OUTPUT_VARIABLE GIT_COMMAND_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    MESSAGE (STATUS "GIT commit with result: ${GIT_COMMAND_RESULT}")

ENDMACRO ()




# ========================================================================================================================================================================================================
# Eliminate all uses of #ifdef __cplusplus (We compile under C rules even with a C++ compiler)
# Eliminate the redirector process/thread hooks (This is moved into Teikitu DLL)
# ========================================================================================================================================================================================================

# GIT Switch or Create the branch to apply the patch =====================================================================================================================================================

EXECUTE_PROCESS(
    COMMAND git tag -l
    WORKING_DIRECTORY ${WORKING_DIR}
    OUTPUT_VARIABLE GIT_TAG_LIST
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Switch to the patch branch, or create it.
IF (NOT GIT_TAG_LIST OR NOT ${GIT_TAG_LIST} MATCHES "teikitu")

    GIT_PATCH( "Patch #0001 MiMalloc Fixes.patch" "Redirector Updates and Removals 32bit.")
    GIT_PATCH( "Patch #0002 MiMalloc Fixes.patch" "Removal of ifdef __cplusplus blocks.")
    GIT_PATCH( "Patch #0003 MiMalloc Fixes.patch" "Update CMakeLists.")
    GIT_PATCH( "Patch #0004 MiMalloc Fixes.patch" "Removal of Redirector code path.")
    GIT_PATCH( "Patch #0005 MiMalloc Fixes.patch" "Implement deferred DLL function loading.")

    EXECUTE_PROCESS(
        COMMAND ${GIT_EXECUTABLE} tag -a teikitu -m "teikitu patch"
        WORKING_DIRECTORY ${WORKING_DIR}
        OUTPUT_VARIABLE GIT_COMMAND_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

ELSE ()

    EXECUTE_PROCESS(
        COMMAND ${GIT_EXECUTABLE} checkout teikitu
        WORKING_DIRECTORY ${WORKING_DIR}
        OUTPUT_VARIABLE GIT_COMMAND_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

ENDIF ()
