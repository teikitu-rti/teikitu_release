# VerifyShaderOutput.cmake
# Verifies that shader compilation produced a valid output file

if(NOT DEFINED CMAKE_ARGV3)
    message(FATAL_ERROR "Usage: cmake -P VerifyShaderOutput.cmake <output_file>")
endif()

set(OUTPUT_FILE "${CMAKE_ARGV3}")

# Check if output file exists
if(NOT EXISTS "${OUTPUT_FILE}")
    message(FATAL_ERROR "Shader compilation failed: Output file does not exist: ${OUTPUT_FILE}")
endif()

# Check if output file has content
file(SIZE "${OUTPUT_FILE}" FILE_SIZE)
if(FILE_SIZE EQUAL 0)
    message(FATAL_ERROR "Shader compilation failed: Output file is empty: ${OUTPUT_FILE}")
endif()

# Check if it's a valid C header file by looking for basic structure
file(READ "${OUTPUT_FILE}" FILE_CONTENTS)
if(NOT FILE_CONTENTS MATCHES "const uint32_t.*=.*\\{.*\\}")
    message(FATAL_ERROR "Shader compilation failed: Output file does not appear to be a valid C header: ${OUTPUT_FILE}")
endif()

message(STATUS "Shader compilation verification passed: ${OUTPUT_FILE} (${FILE_SIZE} bytes)")