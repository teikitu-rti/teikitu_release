# 015482FC-A4BD-4E1C-AE49-A30E5728D73A

# ========================================================================================================================================================================================================
#  OPTIONS
#  Feature Enable / Disable and Default Compilation Configuration
#    - Include the list of primary configuration variables for legibility
# ========================================================================================================================================================================================================

SET (MK_BUILD__THREAD                           "" CACHE STRING "Select the threading API/model.")
SET (MK_BUILD__OS                               "" CACHE STRING "Select the compilation target operating system. ")
SET (MK_BUILD__OS_TEXT_WIDE                     "" CACHE STRING "Select whether the operating system API will expect 8bit or 16bit text.")
SET (MK_BUILD__UNIVERSAL                        "" CACHE STRING "Select the target universal build.")
SET (MK_BUILD__DEVICE                           "" CACHE STRING "Select the target device for a build.")
SET (MK_BUILD__TARGET_HARDWARE                  "" CACHE STRING "Select the target hardware architecture.")

SET (MK_FEATURE__GRAPHICS                       "" CACHE STRING "Select the target graphics API.")
SET (MK_FEATURE__AUDIO                          "" CACHE STRING "Select the target audio API.")

# These options are set in the command line through the root cmakelist.txt file

OPTION (MK_BUILD__PRELOAD__MALLOC_OVERRIDE      "Override malloc and associated functions..")
OPTION (MK_BUILD__MIMALLOC_ALLOCATOR            "Build a memory allocator backed by mimalloc.")
OPTION (MK_BUILD__MIMALLOC_DEFAULT              "Use the mimalloc allocator by default.")

# MK_IDE - Cache variable is set in flag_overrides.cmake
# MK_COMPILER - Cache variable is set in flag_overrides.cmake
