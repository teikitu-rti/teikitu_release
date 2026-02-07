# filter_line_directives_and_add_header.cmake
# Filters out #line directives from preprocessed GLSL files

message(STATUS "CMAKE_ARGC: ${CMAKE_ARGC}")

# Print each argument individually
if(DEFINED CMAKE_ARGC)
    math(EXPR LAST_ARG "${CMAKE_ARGC} - 1")
    foreach(i RANGE 0 ${LAST_ARG})
        message(STATUS "CMAKE_ARGV${i}: ${CMAKE_ARGV${i}}")
    endforeach()
endif()

# In script mode with cmake -P, arguments start at CMAKE_ARGV3
# CMAKE_ARGV0 = cmake
# CMAKE_ARGV1 = --log-level=ERROR
# CMAKE_ARGV2 = -P
# CMAKE_ARGV3 = script_name.cmake
# CMAKE_ARGV4 = first user argument
# CMAKE_ARGV5 = second user argument

if(NOT DEFINED CMAKE_ARGV4 OR NOT DEFINED CMAKE_ARGV5)
    message(FATAL_ERROR "Usage: cmake -P filter_line_directives_and_add_header.cmake <input_file> <output_file>")
endif()

set(INPUT_FILE "${CMAKE_ARGV4}")
set(OUTPUT_FILE "${CMAKE_ARGV5}")

if(NOT EXISTS "${INPUT_FILE}")
    message(FATAL_ERROR "Input file does not exist: ${INPUT_FILE}")
endif()

# Read the input file
file(READ "${INPUT_FILE}" FILE_CONTENTS)

# Remove #line directives and empty lines
string(REGEX REPLACE "#line[^\r\n]*[\r\n]+" "" FILTERED_CONTENTS "${FILE_CONTENTS}")
string(REGEX REPLACE "[\r\n][\r\n]+" "\n" FILTERED_CONTENTS "${FILTERED_CONTENTS}")

# Extract all ##extension directives
string(REGEX MATCHALL "##extension[^\r\n]*[\r\n]*" EXTENSION_LINES "${FILTERED_CONTENTS}")

# Remove ##extension directives from the content
string(REGEX REPLACE "##extension[^\r\n]*[\r\n]*" "" FILTERED_CONTENTS "${FILTERED_CONTENTS}")

# Prepend extracted ##extension directives to the beginning, converting to #extension
if(EXTENSION_LINES)
    # Remove the extra # from ##extension to make it #extension
    string(REPLACE "##extension" "#extension" EXTENSION_BLOCK "${EXTENSION_LINES}")
    string(REPLACE ";" "" EXTENSION_BLOCK "${EXTENSION_BLOCK}")
    set(FILTERED_CONTENTS "${EXTENSION_BLOCK}${FILTERED_CONTENTS}")
endif()

# Check if there's no #version line
if(NOT FILTERED_CONTENTS MATCHES "#version")
    set(FILTERED_CONTENTS "#version 460\n${FILTERED_CONTENTS}")
endif()

# Write the filtered content to the output file
file(WRITE "${OUTPUT_FILE}" "${FILTERED_CONTENTS}")

message(STATUS "Filtered line directives from ${INPUT_FILE} -> ${OUTPUT_FILE}")
