# 015482FC-A4BD-4E1C-AE49-A30E5728D73A
# ===================================================================================================================================================================================
# Clear out all the default flags - if I don't SET it up, it should not be SET
# ===================================================================================================================================================================================

SET (CMAKE_C_FLAGS_INIT                         "")
SET (CMAKE_C_FLAGS_DEBUG_INIT                   "")
SET (CMAKE_C_FLAGS_RELEASE_INIT                 "")
SET (CMAKE_C_FLAGS_FINAL_INIT                   "")
SET (CMAKE_C_FLAGS_TOOLS_INIT                   "")
SET (CMAKE_C_FLAGS_MINSIZEREL                   "")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO               "")
SET (CMAKE_C_STANDARD_LIBRARIES_INIT            "")

SET (CMAKE_CXX_FLAGS_INIT                       "")
SET (CMAKE_CXX_FLAGS_DEBUG_INIT                 "")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT               "")
SET (CMAKE_CXX_FLAGS_FINAL_INIT                 "")
SET (CMAKE_CXX_FLAGS_TOOLS_INIT                 "")
SET (CMAKE_CXX_FLAGS_MINSIZEREL                 "")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO             "")
SET (CMAKE_CXX_STANDARD_LIBRARIES_INIT          "")

SET (CMAKE_EXE_LINKER_FLAGS_INIT                "")
SET (CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT          "")
SET (CMAKE_EXE_LINKER_FLAGS_RELEASE_INIT        "")
SET (CMAKE_EXE_LINKER_FLAGS_FINAL_INIT          "")
SET (CMAKE_EXE_LINKER_FLAGS_TOOLS_INIT          "")
SET (CMAKE_EXE_LINKER_FLAGS_MINSIZEREL          "")
SET (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO      "")

SET (CMAKE_STATIC_LINKER_FLAGS_INIT             "")
SET (CMAKE_STATIC_LINKER_FLAGS_DEBUG_INIT       "")
SET (CMAKE_STATIC_LINKER_FLAGS_RELEASE_INIT     "")
SET (CMAKE_STATIC_LINKER_FLAGS_FINAL_INIT       "")
SET (CMAKE_STATIC_LINKER_FLAGS_TOOLS_INIT       "")
SET (CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL       "")
SET (CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO   "")

SET (CMAKE_MODULE_LINKER_FLAGS_INIT             "")
SET (CMAKE_MODULE_LINKER_FLAGS_DEBUG_INIT       "")
SET (CMAKE_MODULE_LINKER_FLAGS_RELEASE_INIT     "")
SET (CMAKE_MODULE_LINKER_FLAGS_FINAL_INIT       "")
SET (CMAKE_MODULE_LINKER_FLAGS_TOOLS_INIT       "")
SET (CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL       "")
SET (CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO   "")

SET (CMAKE_SHARED_LINKER_FLAGS_INIT             "")
SET (CMAKE_SHARED_LINKER_FLAGS_DEBUG_INIT       "")
SET (CMAKE_SHARED_LINKER_FLAGS_RELEASE_INIT     "")
SET (CMAKE_SHARED_LINKER_FLAGS_FINAL_INIT       "")
SET (CMAKE_SHARED_LINKER_FLAGS_TOOLS_INIT       "")
SET (CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL       "")
SET (CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO   "")

# Mark the new configurations as advanced

MARK_AS_ADVANCED( CMAKE_C_FLAGS_FINAL_INIT )
MARK_AS_ADVANCED( CMAKE_CXX_FLAGS_FINAL_INIT )
MARK_AS_ADVANCED( CMAKE_EXE_LINKER_FLAGS_FINAL_INIT )
MARK_AS_ADVANCED( CMAKE_STATIC_LINKER_FLAGS_FINAL_INIT )
MARK_AS_ADVANCED( CMAKE_MODULE_LINKER_FLAGS_FINAL_INIT )
MARK_AS_ADVANCED( CMAKE_SHARED_LINKER_FLAGS_FINAL_INIT )

MARK_AS_ADVANCED( CMAKE_C_FLAGS_TOOLS_INIT )
MARK_AS_ADVANCED( CMAKE_CXX_FLAGS_TOOLS_INIT )
MARK_AS_ADVANCED( CMAKE_EXE_LINKER_FLAGS_TOOLS_INIT )
MARK_AS_ADVANCED( CMAKE_STATIC_LINKER_FLAGS_TOOLS_INIT )
MARK_AS_ADVANCED( CMAKE_MODULE_LINKER_FLAGS_TOOLS_INIT )
MARK_AS_ADVANCED( CMAKE_SHARED_LINKER_FLAGS_TOOLS_INIT )




# ===================================================================================================================================================================================
#  Setting IDE (Project Build System)
# ===================================================================================================================================================================================

SET (MK_IDE__UNIX_MAKEFILES                     0 CACHE BOOL "")
SET (MK_IDE__MSVC                               0 CACHE BOOL "")
SET (MK_IDE__XCODE                              0 CACHE BOOL "")
SET (MK_IDE__NINJA                              0 CACHE BOOL "")

IF (CMAKE_GENERATOR MATCHES "Visual Studio.*")
    SET (MK_IDE__MSVC                               1 )
ELSEIF (CMAKE_GENERATOR MATCHES "Xcode")
    SET (MK_IDE__XCODE                              1 )
ELSEIF (CMAKE_GENERATOR MATCHES "Unix Makefiles")
    SET (MK_IDE__UNIX_MAKEFILES                     1 )
ELSEIF (CMAKE_GENERATOR MATCHES "Ninja")
    SET (MK_IDE__NINJA                              1 )
ELSE()
    MESSAGE(FATAL_ERROR "UNKNOWN IDE: " ${CMAKE_GENERATOR})
ENDIF ()




# ===================================================================================================================================================================================
#  Setting Compiler
# ===================================================================================================================================================================================

SET (MK_COMPILER__CLANG                         0 CACHE BOOL "")
SET (MK_COMPILER__MSVC                          0 CACHE BOOL "")

SET (MK_COMPILER_FRONTEND__GNU                  0 CACHE BOOL "")
SET (MK_COMPILER_FRONTEND__MSVC                 0 CACHE BOOL "")
SET (MK_COMPILER_FRONTEND__APPLE                0 CACHE BOOL "")

# VALIDATION C == CXX || !C || !CXX
IF (DEFINED CMAKE_CXX_COMPILER_ID)
    IF (DEFINED CMAKE_C_COMPILER_ID)
        IF (CMAKE_C_COMPILER_ID MATCHES CMAKE_CXX_COMPILER_ID)
            MESSAGE(FATAL_ERROR "MISMATCHED C AND CXX COMPILERS: " ${CMAKE_C_COMPILER_ID} ", " ${CMAKE_CXX_COMPILER_ID})
        ENDIF ()
        IF (CMAKE_C_COMPILER_FRONTEND_VARIANT MATCHES CMAKE_CXX_COMPILER_FRONTEND_VARIANT)
            MESSAGE(FATAL_ERROR "MISMATCHED C AND CXX COMPILER FRONTENDS: " ${CMAKE_C_COMPILER_FRONTEND_VARIANT} ", " ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})
        ENDIF ()
    ENDIF ()
ENDIF ()

# C COMPILER
IF (DEFINED CMAKE_C_COMPILER_ID AND NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "")
    STRING (TOLOWER ${CMAKE_C_COMPILER_ID}          CMAKE_C_COMPILER_ID_LOWER )
    IF (CMAKE_C_COMPILER_ID_LOWER MATCHES "clang")
        SET (MK_COMPILER__CLANG                         1 )
    ELSEIF (CMAKE_C_COMPILER_ID_LOWER MATCHES "msvc")
        SET (MK_COMPILER__MSVC                          1 )
    ELSE()
        MESSAGE(FATAL_ERROR "UNSUPPORTED C COMPILER: " ${CMAKE_C_COMPILER_ID})
    ENDIF ()

    IF (NOT DEFINED CMAKE_C_COMPILER_FRONTEND_VARIANT OR "${CMAKE_C_COMPILER_FRONTEND_VARIANT}" STREQUAL "")
        STRING (TOLOWER ${CMAKE_C_COMPILER_ID} CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER )
    ELSE ()
        STRING (TOLOWER ${CMAKE_C_COMPILER_FRONTEND_VARIANT} CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER )
    ENDIF ()

    IF (CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "gnu")
        SET (MK_COMPILER_FRONTEND__GNU                  1 )
    ELSEIF (CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "msvc")
        SET (MK_COMPILER_FRONTEND__MSVC                 1 )
    ELSE()
        MESSAGE(FATAL_ERROR "UNSUPPORTED C FRONTEND: " ${CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER})
    ENDIF ()

# CXX COMPILER
ELSEIF (DEFINED CMAKE_CXX_COMPILER_ID AND NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "")
    STRING (TOLOWER ${CMAKE_CXX_COMPILER_ID}        CMAKE_CXX_COMPILER_ID_LOWER )
    IF (CMAKE_CXX_COMPILER_ID_LOWER MATCHES "clang")
        SET (MK_COMPILER__CLANG                         1 )
    ELSEIF (CMAKE_CXX_COMPILER_ID_LOWER MATCHES "msvc")
        SET (MK_COMPILER__MSVC                          1 )
    ELSE()
        MESSAGE(FATAL_ERROR "UNSUPPORTED CXX COMPILER: " ${CMAKE_CXX_COMPILER_ID})
    ENDIF ()

    IF (NOT DEFINED CMAKE_CXX_COMPILER_FRONTEND_VARIANT OR "${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "")
        STRING (TOLOWER ${CMAKE_CXX_COMPILER_ID} CMAKE_CXX_COMPILER_FRONTEND_VARIANT_LOWER )
    ELSE ()
        STRING (TOLOWER ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT} CMAKE_CXX_COMPILER_FRONTEND_VARIANT_LOWER )
    ENDIF ()

    IF (CMAKE_CXX_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "gnu")
        SET (MK_COMPILER_FRONTEND__GNU                  1 )
    ELSEIF (CMAKE_CXX_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "msvc")
        SET (MK_COMPILER_FRONTEND__MSVC                 1 )
    ELSE()
        MESSAGE(FATAL_ERROR "UNSUPPORTED CXX FRONTEND: " ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})
    ENDIF ()

# NO C/CXX COMPILER
ELSE()
    MESSAGE(SEND_ERROR "UNSUPPORTED C COMPILER: " ${CMAKE_C_COMPILER_ID})
    MESSAGE(SEND_ERROR "UNSUPPORTED CXX COMPILER: " ${CMAKE_CXX_COMPILER_ID})
    MESSAGE(FATAL_ERROR "MISSING COMPILER DEFINITIONS")
ENDIF ()




# ===================================================================================================================================================================================
#  Compilation Configuration
# ===================================================================================================================================================================================

IF (MK_COMPILER_FRONTEND__MSVC)

    SET (MSVC_COMPILE_FLAGS                                               "/arch:AVX")                              # Minimum hardware architecture requirement
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /fp:precise")                            # Floating-point behaviour
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /fp:except-")                            # Floating-point behaviour
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /GF")                                    # Eliminate duplicate strings
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /GR-")                                   # Disable Run-Time Type Information
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Gv")                                    # Vectorcall by default
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Gy-")                                   # Do not put each function in its own section (default)
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Ob2")                                   # Inline functions as deemed beneficial by the compiler
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Oi")                                    # Enable use of builtin functions
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /openmp-")                               # Disable OpenMP Support
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Ot")                                    # Optimize for speed
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Oy-")                                   # Omit Frame Pointers
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Wall")                                  # Enable -Weverything
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /wd4007")                                # Disable warnings for simple project compiles
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /WX")                                    # Treat warnings as errors
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /MP")                                    # Build with Multiple Processes
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /permissive-")                           # Make sure to enforce conformance
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Zc:inline")                             # Conformance
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Zc:rvalueCast")                         # Conformance
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /std:c17")                               # C standard
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /std:c++20")                             # C++ standard - C++20 needed for unicode literals
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /GT")                                    # Support fiber-safe thread-local storage
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /GS")                                    # Enable Security Checks
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /utf-8")                                 # Use UTF8
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Zc:char8_t")                            # Enable char8_t from C++2a
#    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /JMC")                                   # Just My Code debugging

    IF (MK_COMPILER__MSVC)
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /J")                                     # Default char type is unsigned
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Zc:strictStrings")                      # Treat string literals as const
    ENDIF ()

    SET (CMAKE_C_FLAGS_INIT                         "${CMAKE_C_FLAGS_INIT} ${MSVC_COMPILE_FLAGS}")

    SET (CMAKE_C_FLAGS_DEBUG_INIT                   "${CMAKE_C_FLAGS_DEBUG_INIT} /Od /RTC1")
    SET (CMAKE_C_FLAGS_RELEASE_INIT                 "${CMAKE_C_FLAGS_RELEASE_INIT} /Ox /GS-")
    SET (CMAKE_C_FLAGS_FINAL_INIT                   "${CMAKE_C_FLAGS_FINAL_INIT} /Ox /GS-")
    #SET (CMAKE_C_FLAGS_TOOLS_INIT                   "${CMAKE_C_FLAGS_TOOLS_INIT} /Ox /GS-")

    SET (CMAKE_EXE_LINKER_FLAGS_FINAL_INIT          "${CMAKE_EXE_LINKER_FLAGS_FINAL_INIT} /INCREMENTAL:NO")

    SET (CMAKE_CXX_FLAGS_INIT                       "${CMAKE_CXX_FLAGS_INIT} ${MSVC_COMPILE_FLAGS} /DTgCOMPILE_FILE__CXX")

    SET (CMAKE_CXX_FLAGS_DEBUG_INIT                 "${CMAKE_CXX_FLAGS_DEBUG_INIT} /Od /RTC1")
    SET (CMAKE_CXX_FLAGS_RELEASE_INIT               "${CMAKE_CXX_FLAGS_RELEASE_INIT} /Ox /GS-")
    SET (CMAKE_CXX_FLAGS_FINAL_INIT                 "${CMAKE_CXX_FLAGS_FINAL_INIT} /Ox /GS-")
    #SET (CMAKE_CXX_FLAGS_TOOLS_INIT                 "${CMAKE_CXX_FLAGS_TOOLS_INIT} /Ox /GS-")

    SET (CMAKE_EXE_LINKER_FLAGS_TOOLS_INIT          "${CMAKE_EXE_LINKER_FLAGS_TOOLS_INIT}")

ELSEIF (MK_COMPILER__CLANG)

    SET (CLANG_COMPILE_FLAGS                                               "-Weverything")                          # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -Werror")                               # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fstack-protector-all")                 # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fstrict-aliasing")                     # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -ffunction-sections")                   # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fomit-frame-pointer")                  # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fdata-sections")                       # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fchar8_t")                             # Include support for UTF8 character type and literals
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fno-short-enums")                      # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fno-exceptions")                       # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fno-rtti")                             # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -finline-functions")                    # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fdebug-macro")                         # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fms-compatibility")                    # MSFT extension support - compatability
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fstandalone-debug")                    # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -mms-bitfields")                        # MSFT extension support - bitfields
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -mstackrealign")                        # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -mcx16")                                # Include support for 16B compare exchange
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -msse4")                                # SSE4 Support, Released in CPUs from 2007/2008
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -g")                                    # Generate source-level debug information

    SET (CMAKE_C_FLAGS_INIT                         "${CMAKE_C_FLAGS_INIT} ${CLANG_COMPILE_FLAGS} -std=c17")

    SET (CMAKE_C_FLAGS_DEBUG_INIT                   "${CMAKE_C_FLAGS_DEBUG_INIT} -O0")
    SET (CMAKE_C_FLAGS_RELEASE_INIT                 "${CMAKE_C_FLAGS_RELEASE_INIT} -O3 -Wno-unused-parameter")
    SET (CMAKE_C_FLAGS_FINAL_INIT                   "${CMAKE_C_FLAGS_FINAL_INIT} -O3 -Wno-unused-parameter")
    SET (CMAKE_C_FLAGS_TOOLS_INIT                   "${CMAKE_C_FLAGS_TOOLS_INIT} -O3")

    SET (CMAKE_CXX_FLAGS_INIT                       "${CMAKE_CXX_FLAGS_INIT} ${CLANG_COMPILE_FLAGS} -std=c++20 -DTgCOMPILE_FILE__CXX")

    SET (CMAKE_CXX_FLAGS_DEBUG_INIT                 "${CMAKE_CXX_FLAGS_DEBUG_INIT} -O0")
    SET (CMAKE_CXX_FLAGS_RELEASE_INIT               "${CMAKE_CXX_FLAGS_RELEASE_INIT} -O3 -Wno-unused-parameter")
    SET (CMAKE_CXX_FLAGS_FINAL_INIT                 "${CMAKE_CXX_FLAGS_FINAL_INIT} -O3 -Wno-unused-parameter")
    SET (CMAKE_CXX_FLAGS_TOOLS_INIT                 "${CMAKE_CXX_FLAGS_TOOLS_INIT} -O3")

ELSE()
    MESSAGE(FATAL_ERROR "UNSUPPORTED COMPILER AT THIS TIME")
ENDIF ()




# ===================================================================================================================================================================================
#  Final and Tools Configuration
# ===================================================================================================================================================================================

# Setup the Final flags
SET (CMAKE_C_FLAGS_FINAL                        "${CMAKE_C_FLAGS_FINAL_INIT}"             CACHE STRING "")
SET (CMAKE_CXX_FLAGS_FINAL                      "${CMAKE_CXX_FLAGS_FINAL_INIT}"           CACHE STRING "")
SET (CMAKE_EXE_LINKER_FLAGS_FINAL               "${CMAKE_EXE_LINKER_FLAGS_FINAL_INIT}"    CACHE STRING "")
SET (CMAKE_STATIC_LINKER_FLAGS_FINAL            "${CMAKE_STATIC_LINKER_FLAGS_FINAL_INIT}" CACHE STRING "")
SET (CMAKE_MODULE_LINKER_FLAGS_FINAL            "${CMAKE_MODULE_LINKER_FLAGS_FINAL_INIT}" CACHE STRING "")
SET (CMAKE_SHARED_LINKER_FLAGS_FINAL            "${CMAKE_SHARED_LINKER_FLAGS_FINAL_INIT}" CACHE STRING "")

MARK_AS_ADVANCED(                               CMAKE_C_FLAGS_FINAL )
MARK_AS_ADVANCED(                               CMAKE_CXX_FLAGS_FINAL )
MARK_AS_ADVANCED(                               CMAKE_EXE_LINKER_FLAGS_FINAL )
MARK_AS_ADVANCED(                               CMAKE_STATIC_LINKER_FLAGS_FINAL )
MARK_AS_ADVANCED(                               CMAKE_MODULE_LINKER_FLAGS_FINAL )
MARK_AS_ADVANCED(                               CMAKE_SHARED_LINKER_FLAGS_FINAL )

# Setup the Tools flags
SET (CMAKE_C_FLAGS_TOOLS                        "${CMAKE_C_FLAGS_TOOLS_INIT}"             CACHE STRING "")
SET (CMAKE_CXX_FLAGS_TOOLS                      "${CMAKE_CXX_FLAGS_TOOLS_INIT}"           CACHE STRING "")
SET (CMAKE_EXE_LINKER_FLAGS_TOOLS               "${CMAKE_EXE_LINKER_FLAGS_TOOLS_INIT}"    CACHE STRING "")
SET (CMAKE_STATIC_LINKER_FLAGS_TOOLS            "${CMAKE_STATIC_LINKER_FLAGS_TOOLS_INIT}" CACHE STRING "")
SET (CMAKE_MODULE_LINKER_FLAGS_TOOLS            "${CMAKE_MODULE_LINKER_FLAGS_TOOLS_INIT}" CACHE STRING "")
SET (CMAKE_SHARED_LINKER_FLAGS_TOOLS            "${CMAKE_SHARED_LINKER_FLAGS_TOOLS_INIT}" CACHE STRING "")

MARK_AS_ADVANCED(                               CMAKE_C_FLAGS_TOOLS )
MARK_AS_ADVANCED(                               CMAKE_CXX_FLAGS_TOOLS )
MARK_AS_ADVANCED(                               CMAKE_EXE_LINKER_FLAGS_TOOLS )
MARK_AS_ADVANCED(                               CMAKE_STATIC_LINKER_FLAGS_TOOLS )
MARK_AS_ADVANCED(                               CMAKE_MODULE_LINKER_FLAGS_TOOLS )
MARK_AS_ADVANCED(                               CMAKE_SHARED_LINKER_FLAGS_TOOLS )

