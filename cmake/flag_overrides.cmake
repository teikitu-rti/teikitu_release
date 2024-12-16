# 015482FC-A4BD-4E1C-AE49-A30E5728D73A
# ===================================================================================================================================================================================
# Clear out all the default flags - if I don't SET it up, it should not be SET
# ===================================================================================================================================================================================

SET (CMAKE_C_FLAGS_INIT                         "")
SET (CMAKE_C_FLAGS_DEBUG_INIT                   "")
SET (CMAKE_C_FLAGS_RELEASE_INIT                 "")
SET (CMAKE_C_STANDARD_LIBRARIES_INIT            "")

SET (CMAKE_CXX_FLAGS_INIT                       "")
SET (CMAKE_CXX_FLAGS_DEBUG_INIT                 "")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT               "")
SET (CMAKE_CXX_STANDARD_LIBRARIES_INIT          "")

SET (CMAKE_EXE_LINKER_FLAGS_INIT                "")
SET (CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT          "")
SET (CMAKE_EXE_LINKER_FLAGS_RELEASE_INIT        "")
SET (CMAKE_EXE_LINKER_FLAGS_MINSIZEREL          "")
SET (CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO      "")

SET (CMAKE_STATIC_LINKER_FLAGS_INIT             "")
SET (CMAKE_STATIC_LINKER_FLAGS_DEBUG_INIT       "")
SET (CMAKE_STATIC_LINKER_FLAGS_RELEASE_INIT     "")
SET (CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL       "")
SET (CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO   "")

SET (CMAKE_MODULE_LINKER_FLAGS_INIT             "")
SET (CMAKE_MODULE_LINKER_FLAGS_DEBUG_INIT       "")
SET (CMAKE_MODULE_LINKER_FLAGS_RELEASE_INIT     "")
SET (CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL       "")
SET (CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO   "")

SET (CMAKE_SHARED_LINKER_FLAGS_INIT             "")
SET (CMAKE_SHARED_LINKER_FLAGS_DEBUG_INIT       "")
SET (CMAKE_SHARED_LINKER_FLAGS_RELEASE_INIT     "")
SET (CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL       "")
SET (CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO   "")




# ===================================================================================================================================================================================
#  Setting Compiler
# ===================================================================================================================================================================================

#SET (MK_COMPILER__CLANG                         0 CACHE BOOL "")
#SET (MK_COMPILER__MSVC                          0 CACHE BOOL "")
#SET (MK_COMPILER__APPLE                         0 CACHE BOOL "")

#SET (MK_COMPILER_FRONTEND__GNU                  0 CACHE BOOL "")
#SET (MK_COMPILER_FRONTEND__MSVC                 0 CACHE BOOL "")
#SET (MK_COMPILER_FRONTEND__APPLE                0 CACHE BOOL "")

# MESSAGE( STATUS "C AND CXX COMPILERS: " ${CMAKE_C_COMPILER_ID} ", " ${CMAKE_CXX_COMPILER_ID})
# MESSAGE( STATUS "C AND CXX COMPILER FRONTENDS: " ${CMAKE_C_COMPILER_FRONTEND_VARIANT} ", " ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})

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
    STRING (TOLOWER ${CMAKE_C_COMPILER_ID} CMAKE_C_COMPILER_ID_LOWER )
    IF (CMAKE_C_COMPILER_ID_LOWER MATCHES "appleclang")
        SET (MK_COMPILER__APPLE 1 )
    ELSEIF (CMAKE_C_COMPILER_ID_LOWER MATCHES "msvc")
        SET (MK_COMPILER__MSVC 1 )
    ELSEIF (CMAKE_C_COMPILER_ID_LOWER MATCHES "clang")
        SET (MK_COMPILER__CLANG 1 )
    ELSE()
        MESSAGE(FATAL_ERROR "UNSUPPORTED C COMPILER: " ${CMAKE_C_COMPILER_ID})
    ENDIF ()

    IF (NOT DEFINED CMAKE_C_COMPILER_FRONTEND_VARIANT OR "${CMAKE_C_COMPILER_FRONTEND_VARIANT}" STREQUAL "")
        STRING (TOLOWER ${CMAKE_C_COMPILER_ID} CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER )
    ELSE ()
        STRING (TOLOWER ${CMAKE_C_COMPILER_FRONTEND_VARIANT} CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER )
    ENDIF ()

    IF (CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "gnu")
        SET (MK_COMPILER_FRONTEND__GNU 1 )
    ELSEIF (CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "msvc")
        SET (MK_COMPILER_FRONTEND__MSVC 1 )
    ELSEIF (CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "appleclang")
        SET (MK_COMPILER_FRONTEND__APPLE 1 ) 
    ELSE()
        MESSAGE(FATAL_ERROR "UNSUPPORTED C FRONTEND: " ${CMAKE_C_COMPILER_FRONTEND_VARIANT_LOWER})
    ENDIF ()

# CXX COMPILER
ELSEIF (DEFINED CMAKE_CXX_COMPILER_ID AND NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "")
    STRING (TOLOWER ${CMAKE_CXX_COMPILER_ID} CMAKE_CXX_COMPILER_ID_LOWER )
    IF (CMAKE_CXX_COMPILER_ID_LOWER MATCHES "appleclang")
        SET (MK_COMPILER__APPLE 1 )
    ELSEIF (CMAKE_CXX_COMPILER_ID_LOWER MATCHES "msvc")
        SET (MK_COMPILER__MSVC 1 )
    ELSEIF (CMAKE_CXX_COMPILER_ID_LOWER MATCHES "clang")
        SET (MK_COMPILER__CLANG 1 )
    ELSE()
        MESSAGE(FATAL_ERROR "UNSUPPORTED CXX COMPILER: " ${CMAKE_CXX_COMPILER_ID})
    ENDIF ()

    IF (NOT DEFINED CMAKE_CXX_COMPILER_FRONTEND_VARIANT OR "${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "")
        STRING (TOLOWER ${CMAKE_CXX_COMPILER_ID} CMAKE_CXX_COMPILER_FRONTEND_VARIANT_LOWER )
    ELSE ()
        STRING (TOLOWER ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT} CMAKE_CXX_COMPILER_FRONTEND_VARIANT_LOWER )
    ENDIF ()

    IF (CMAKE_CXX_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "gnu")
        SET (MK_COMPILER_FRONTEND__GNU 1 )
    ELSEIF (CMAKE_CXX_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "msvc")
        SET (MK_COMPILER_FRONTEND__MSVC 1 )
    ELSEIF (CMAKE_CXX_COMPILER_FRONTEND_VARIANT_LOWER MATCHES "appleclang")
        SET (MK_COMPILER_FRONTEND__APPLE 1 )
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
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Gy-")                                   # Do not put each function in its own section (default)
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Ob2")                                   # Inline functions as deemed beneficial by the compiler
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Oi")                                    # Enable use of builtin functions
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /openmp-")                               # Disable OpenMP Support
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Ot")                                    # Optimize for speed
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Oy-")                                   # Omit Frame Pointers
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /wd4007")                                # Disable warnings for simple project compiles
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /WX")                                    # Treat warnings as errors
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /MP")                                    # Build with Multiple Processes
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /GT")                                    # Support fiber-safe thread-local storage
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /GS")                                    # Enable Security Checks
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Zi")                                    # Debug information format (PDB)
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Zf")                                    # Enable faster PDB generation in parallel builds by minimizing RPC calls to mspdbsrv.exe
    
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /permissive-")                           # Make sure to enforce conformance
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Zc:char8_t")                            # Enable char8_t from C++2a
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Zc:inline")                             # Conformance
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Zc:preprocessor")                       # Conformance
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /Zc:__cplusplus")                        # Conformance

    IF (MK_COMPILER__MSVC)
    SET (MSVC_COMPILE_FLAGS                         "${MSVC_COMPILE_FLAGS} /J")                                     # Default char type is unsigned
    ENDIF ()

    SET (CMAKE_C_FLAGS_INIT                         "${CMAKE_C_FLAGS_INIT} ${MSVC_COMPILE_FLAGS}")
    SET (CMAKE_C_FLAGS_DEBUG_INIT                   "${CMAKE_C_FLAGS_DEBUG_INIT} /Od /RTC1")
    SET (CMAKE_C_FLAGS_RELEASE_INIT                 "${CMAKE_C_FLAGS_RELEASE_INIT} /Zo /Ox /GS-")

    SET (CMAKE_CXX_FLAGS_INIT                       "${CMAKE_CXX_FLAGS_INIT} ${MSVC_COMPILE_FLAGS}")
    SET (CMAKE_CXX_FLAGS_DEBUG_INIT                 "${CMAKE_CXX_FLAGS_DEBUG_INIT} /Od /RTC1")
    SET (CMAKE_CXX_FLAGS_RELEASE_INIT               "${CMAKE_CXX_FLAGS_RELEASE_INIT} /Ox /GS-")

ELSEIF (MK_COMPILER__CLANG OR MK_COMPILER__APPLE)

    SET (CLANG_COMPILE_FLAGS                                               "-fstack-protector-all")                 # Enable stack protectors for all functions
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fstrict-aliasing")                     # Enable optimizations based on strict aliasing rules
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -ffunction-sections")                   # Place each function in its own section
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fomit-frame-pointer")                  # Omit the frame pointer from functions that don't need it. On many targets, -O1 and higher omit the frame pointer by default.
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fdata-sections")                       # Place each data in its own section
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fchar8_t")                             # Include support for UTF8 character type and literals
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fno-short-enums")                      # 
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -finline-functions")                    # Inline suitable functions
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fstandalone-debug")                    # Emit full debug info for all types used by the program
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -mstackrealign")                        # Force realign the stack at entry to every function
    SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -g")                                    # Generate source-level debug information

#   SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -fms-compatibility")                    # MSFT extension support - compatability
#   SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -mms-bitfields")                        # MSFT extension support - bitfield
#   SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -nostdinc")                             # 
#   SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -nostdinc++")                           # 
#   SET (CLANG_COMPILE_FLAGS                        "${CLANG_COMPILE_FLAGS} -Xclang -ibuiltininc")                  # 

    SET (CMAKE_C_FLAGS_INIT                         "${CMAKE_C_FLAGS_INIT} ${CLANG_COMPILE_FLAGS}")
    SET (CMAKE_C_FLAGS_DEBUG_INIT                   "${CMAKE_C_FLAGS_DEBUG_INIT} -O0")                              # Optimization Flag
    SET (CMAKE_C_FLAGS_RELEASE_INIT                 "${CMAKE_C_FLAGS_RELEASE_INIT} -O3")                            # Optimization Flag

    SET (CMAKE_CXX_FLAGS_INIT                       "${CMAKE_CXX_FLAGS_INIT} ${CLANG_COMPILE_FLAGS}")
    SET (CMAKE_CXX_FLAGS_DEBUG_INIT                 "${CMAKE_CXX_FLAGS_DEBUG_INIT} -O0")                            # Optimization Flag
    SET (CMAKE_CXX_FLAGS_RELEASE_INIT               "${CMAKE_CXX_FLAGS_RELEASE_INIT} -O3")                          # Optimization Flag

ELSE()
    MESSAGE(FATAL_ERROR "UNSUPPORTED COMPILER AT THIS TIME")
ENDIF ()
