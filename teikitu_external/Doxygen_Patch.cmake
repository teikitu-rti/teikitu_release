# 015482FC-A4BD-4E1C-AE49-A30E5728D73A
CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
CMAKE_POLICY(VERSION 3.31)


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

SET (WORKING_DIR ${GIT_ROOT_PATH}/teikitu_external/_repo_clone/doxygen/)



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
#  Prepare the OpenUSD branch to allow for OneAPI TBB
# ========================================================================================================================================================================================================

# GIT Switch or Create the branch to apply the patch =====================================================================================================================================================

EXECUTE_PROCESS(
    COMMAND git tag -l
    WORKING_DIRECTORY ${WORKING_DIR}
    OUTPUT_VARIABLE GIT_TAG_LIST
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# MESSAGE (STATUS "BRANCH LIST: ${GIT_TAG_LIST}")

IF (NOT GIT_TAG_LIST)
    MESSAGE (FATAL_ERROR "Could not get a tag list for the repo")
ENDIF ()

# Switch to the patch branch, or create it.
IF (NOT ${GIT_TAG_LIST} MATCHES "teikitu")

    GIT_PATCH( "Patch #0001 Doxygen Fixes.patch" "Build Fixes.")

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
