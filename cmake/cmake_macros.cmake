# 015482FC-A4BD-4E1C-AE49-A30E5728D73A

INCLUDE (CMakeParseArguments)
INCLUDE (CMakePrintHelpers)
INCLUDE (GNUInstallDirs) # Introduce variables: CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_BINDIR, CMAKE_INSTALL_INCLUDEDIR
INCLUDE (CMakePackageConfigHelpers)
INCLUDE (GenerateExportHeader)

##########################################################################################################################################################################################################
GET_PROPERTY (isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
IF (isMultiConfig)
    SET (MK_INSTALL__LIBRARY_DESTINATION "${CMAKE_INSTALL_LIBDIR}/${CMAKE_BUILD_TYPE}")
    SET (MK_INSTALL__ARCHIVE_DESTINATION "${CMAKE_INSTALL_LIBDIR}/${CMAKE_BUILD_TYPE}")
    SET (MK_INSTALL__RUNTIME_DESTINATION "${CMAKE_INSTALL_BINDIR}/${CMAKE_BUILD_TYPE}")
ELSE ()
    SET (MK_INSTALL__LIBRARY_DESTINATION "${CMAKE_INSTALL_LIBDIR}")
    SET (MK_INSTALL__ARCHIVE_DESTINATION "${CMAKE_INSTALL_LIBDIR}")
    SET (MK_INSTALL__RUNTIME_DESTINATION "${CMAKE_INSTALL_BINDIR}")
ENDIF ()


##########################################################################################################################################################################################################
MACRO(SET_APPEND_GNU_COMPILER_OPTION existing_flags initization_values) 
    SET (${existing_flags} ${${initization_values}})
    IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " -${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(APPEND_GNU_COMPILER_OPTION existing_flags) 
    IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " -${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(APPEND_GNU_DISABLE_WARNING existing_flags) 
    IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " -Wno-${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(SET_APPEND_MSVC_COMPILER_OPTION existing_flags initization_values) 
    SET (${existing_flags} ${${initization_values}})
    IF (MK_COMPILER_FRONTEND__MSVC)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " /${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(APPEND_MSVC_COMPILER_OPTION existing_flags) 
    IF (MK_COMPILER_FRONTEND__MSVC)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " /${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(APPEND_MSVC_DISABLE_WARNING existing_flags) 
    IF (MK_COMPILER_FRONTEND__MSVC)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " /Wd${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(TGS_SOURCE_APPEND_GNU_COMPILER_OPTION source_file) 
    IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                SET_PROPERTY(SOURCE ${source_file} APPEND_STRING PROPERTY COMPILE_FLAGS " -${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION source_file) 
    IF (MK_COMPILER_FRONTEND__MSVC)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                SET_PROPERTY(SOURCE ${source_file} APPEND_STRING PROPERTY COMPILE_FLAGS " /${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(TGS_INSTALL target)

    SET (MK_BUILD_TARGETS_EXPORT_NAME "${MK_BUILD_PACKAGE_PROJECT_NAME}Targets")
        
    SET_TARGET_PROPERTIES (${target} PROPERTIES VERSION ${CMAKE_PROJECT_VERSION})
    SET_TARGET_PROPERTIES (${target} PROPERTIES SOVERSION 0)
    SET_TARGET_PROPERTIES (${target} PROPERTIES INTERFACE_${target}_MAJOR_VERSION ${CMAKE_PROJECT_VERSION_MAJOR})
    SET_PROPERTY (TARGET ${target} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${target}_MAJOR_VERSION )

    IF ("${MK_BUILD_AUTOMATION}" STREQUAL "CICD_BUILD")
        INSTALL (TARGETS ${target}
            RUNTIME_DEPENDENCY_SET UNUSED
            DESTINATION ${CMAKE_INSTALL_PREFIX}
            EXPORT "${MK_BUILD_TARGETS_EXPORT_NAME}"
            CONFIGURATIONS ${CMAKE_BUILD_TYPE}
            LIBRARY DESTINATION "${MK_INSTALL__LIBRARY_DESTINATION}"
            ARCHIVE DESTINATION "${MK_INSTALL__ARCHIVE_DESTINATION}"
            RUNTIME DESTINATION "${MK_INSTALL__RUNTIME_DESTINATION}"
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )
    ELSE ()
        INSTALL (TARGETS ${target}
            DESTINATION ${CMAKE_INSTALL_PREFIX}
            EXPORT "${MK_BUILD_TARGETS_EXPORT_NAME}"
            CONFIGURATIONS ${CMAKE_BUILD_TYPE}
            LIBRARY DESTINATION "${MK_INSTALL__LIBRARY_DESTINATION}"
            ARCHIVE DESTINATION "${MK_INSTALL__ARCHIVE_DESTINATION}"
            RUNTIME DESTINATION "${MK_INSTALL__RUNTIME_DESTINATION}"
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(TGS_ADD_DLL_NO_LIB dllname)
    SET (MK_BUILD__LIBRARY_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    GET_PROPERTY (isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    IF (isMultiConfig)
        SET (MK_BUILD__LIBRARY_OUTPUT_DIRECTORY ${MK_BUILD__LIBRARY_OUTPUT_DIRECTORY}${CMAKE_BUILD_TYPE}/)
    ENDIF ()

    SET (TGS_ADD_DLL_NO_LIB__DEF_FILE "${CMAKE_BINARY_DIR}/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}/${dllname}.def")
    SET (TGS_ADD_DLL_NO_LIB__LIB_FILE "${MK_BUILD__LIBRARY_OUTPUT_DIRECTORY}${dllname}.lib")

    FILE (WRITE "${TGS_ADD_DLL_NO_LIB__DEF_FILE}" "LIBRARY ${dllname}\r\nEXPORTS\r\n")

    GET_FILENAME_COMPONENT(COMPILER_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    IF (MK_COMPILER_FRONTEND__MSVC)
        FIND_PROGRAM(LIB_EXE NAMES lib.exe PATHS "${COMPILER_BIN_DIR}" NO_DEFAULT_PATH)
    ELSEIF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        FIND_PROGRAM(LIB_EXE NAMES llvm-lib.exe PATHS "${COMPILER_BIN_DIR}" NO_DEFAULT_PATH)
    ELSE ()
        MESSAGE (FATAL_ERROR "COMPILER FRONTEND is UNKNOWN or UNSUPPORTED")
    ENDIF ()

    ADD_CUSTOM_COMMAND (
        OUTPUT "${TGS_ADD_DLL_NO_LIB__LIB_FILE}"
        COMMAND ${CMAKE_COMMAND} -E echo ${LIB_EXE} /machine:X64 /def:"${TGS_ADD_DLL_NO_LIB__DEF_FILE}" /out:"${TGS_ADD_DLL_NO_LIB__LIB_FILE}"
        COMMAND ${LIB_EXE} /machine:X64 /def:"${TGS_ADD_DLL_NO_LIB__DEF_FILE}" /out:"${TGS_ADD_DLL_NO_LIB__LIB_FILE}"
        DEPENDS "${TGS_ADD_DLL_NO_LIB__DEF_FILE}")
     
    ADD_CUSTOM_TARGET(${dllname}LIB ALL
        DEPENDS "${TGS_ADD_DLL_NO_LIB__LIB_FILE}")

    ADD_LIBRARY (${dllname} SHARED IMPORTED GLOBAL)
    SET_PROPERTY (TARGET ${dllname} PROPERTY IMPORTED_IMPLIB "${TGS_ADD_DLL_NO_LIB__LIB_FILE}")
    INSTALL (FILES "${TGS_ADD_DLL_NO_LIB__LIB_FILE}" DESTINATION "${MK_INSTALL__LIBRARY_DESTINATION}")

    IF (NOT "${MK_BUILD_AUTOMATION}" STREQUAL "CICD_BUILD")
        INSTALL (IMPORTED_RUNTIME_ARTIFACTS  ${dllname}
            DESTINATION ${CMAKE_INSTALL_PREFIX}
            CONFIGURATIONS ${CMAKE_BUILD_TYPE}
            LIBRARY DESTINATION "${MK_INSTALL__LIBRARY_DESTINATION}"
            RUNTIME DESTINATION "${MK_INSTALL__RUNTIME_DESTINATION}"
        )
    ENDIF ()

ENDMACRO ()


##########################################################################################################################################################################################################
# Dump out all cmake variables that match a regex
function(dump_cmake_variables)
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        if (ARGV0)
            unset(MATCHED)

            #case sensitive match
            # string(REGEX MATCH ${ARGV0} MATCHED ${_variableName})
            #
            #case insenstitive match
            string( TOLOWER "${ARGV0}" ARGV0_lower )
            string( TOLOWER "${_variableName}" _variableName_lower )
            string(REGEX MATCH ${ARGV0_lower} MATCHED ${_variableName_lower})

            if (NOT MATCHED)
                continue()
            endif()
        endif()
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endfunction()


##########################################################################################################################################################################################################
# Determine the appropriate object (intermediate) directory for the current module (CMakeFile)
MACRO(TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY) 
    #CMAKE_PATH ( GET CMAKE_SOURCE_DIR PARENT_PATH PROJECT_ROOT_DIR )
    #CMAKE_PATH ( GET MODULE_PATH_ROOT PARENT_PATH MODULE_TEST_PATH )

    #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${PROJECT_ROOT_DIR} -- ${MODULE_PATH_ROOT} -- ${MODULE_TEST_PATH}" )

    # Assuming that the directory containing the cmakelists.txt is the module name, determine the folder name and use it for the module name
    CMAKE_PATH ( GET CMAKE_CURRENT_LIST_DIR PARENT_PATH MODULE_PATH_ROOT ) # Used to determine the module name
    FILE ( RELATIVE_PATH MODULE_NAME ${MODULE_PATH_ROOT} ${CMAKE_CURRENT_LIST_DIR} )
    #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${MODULE_NAME}" )

    # Add the relative path from project root this cmakelist for the object directory.
    CMAKE_PATH ( SET CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_OBJECT_OUTPUT_DIRECTORY})
    #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}" )
    FILE ( RELATIVE_PATH EXTRA_PATH_SEGMENT ${GIT_ROOT_PATH} ${CMAKE_CURRENT_LIST_DIR} )
    #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${EXTRA_PATH_SEGMENT}" )
    SET ( CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}${EXTRA_PATH_SEGMENT}${ARGN}/ )
    #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}" )

    IF (NOT EXISTS ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY})
        FILE (MAKE_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY})
        MESSAGE( STATUS "Created directory: ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}")
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_FILE_TO_IDE source_files header_files test_assigned test_current file)
    CMAKE_PARSE_ARGUMENTS (TGS_ADD_FILE_TO_IDE "" "IDE_PATH" "" ${ARGN} )
    #MESSAGE("${source_files}")
    #MESSAGE("${TGS_ADD_FILE_TO_IDE_IDE_PATH}")
    #MESSAGE("${file}")
    #MESSAGE(TEST: ${test_current} ${test_assigned})

    # Add the file to the correct list for compilation
    IF ((${test_current} STREQUAL ${test_assigned}))
        SET (${source_files} ${${source_files}} "${file}")

    ELSEIF (MK_IDE__INCLUDE_NON_SOURCE_FILES)
        SET (${header_files} ${${header_files}} "${file}")
        SET_PROPERTY(SOURCE ${file} PROPERTY HEADER_FILE_ONLY TRUE)

    ENDIF ()

    # Assign an IDE path (folder structure)
    IF (TGS_ADD_FILE_TO_IDE_IDE_PATH AND NOT ${TGS_ADD_FILE_TO_IDE_IDE_PATH} STREQUAL "")
        STRING (REPLACE "/" "\\" IDE_PATH_FIXED ${TGS_ADD_FILE_TO_IDE_IDE_PATH})
        #MESSAGE("${IDE_PATH_FIXED}")

        IF (MK_IDE__INCLUDE_NON_SOURCE_FILES AND NOT (${test_current} STREQUAL ${test_assigned}))
            SET (IDE_PATH_FIXED "${IDE_PATH_FIXED}\\${test_assigned} (Inactive)")
        ENDIF ()
        #MESSAGE("${IDE_PATH_FIXED}")

        SOURCE_GROUP ("${IDE_PATH_FIXED}" FILES "${file}")

    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_SOURCE_FILE source_files header_files test_assigned test_current ide_path file)
    IF (EXISTS ${file})
        TGS_ADD_FILE_TO_IDE(${source_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
        IF ((${test_current} STREQUAL ${test_assigned}))
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.c)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.c)
        ELSE ()
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
        ENDIF ()
    ELSE ()
        MESSAGE("FILE DOES NOT EXIST: " ${file})
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_INCSRC_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY HEADER_FILE_ONLY TRUE)
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_HEADER_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY  HEADER_FILE_ONLY TRUE)
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_CMAKE_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO()


##########################################################################################################################################################################################################
# Validate the DXC path for DX12 and Vulkan
IF (NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "REF" AND NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
    FIND_PATH (DXC_COMPILER_PATH dxc.exe)
    CMAKE_PATH (SET CMAKE_DXC_COMPILER NORMALIZE "${DXC_COMPILER_PATH}/dxc.exe")

    EXECUTE_PROCESS (
        COMMAND ${CMAKE_DXC_COMPILER} --version
        OUTPUT_VARIABLE DXC_VERSION
    )
    STRING (REGEX MATCHALL "[0-9.]+\\s" DXC_VERSION_REGEX "${DXC_VERSION}")
    SET (CMAKE_DXC_VERSION "${DXC_VERSION_REGEX}")

    IF (NOT DEFINED CMAKE_DXC_COMPILER)
        MESSAGE (FATAL_ERROR "DXC compiler not found")
    ENDIF ()
ENDIF ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER source_files header_files test_assigned test_current ide_path file)
    IF (NOT EXISTS ${file})
        MESSAGE (SEND_ERROR "FILE DOES NOT EXIST: " ${file})
        RETURN ()
    ENDIF ()

    GET_FILENAME_COMPONENT (FILE_NAME_E "${file}" NAME_WLE)
    GET_FILENAME_COMPONENT (HLSL_CHECK "${file}" LAST_EXT)

    IF (NOT ${HLSL_CHECK} STREQUAL ".hlsl")
        MESSAGE (SEND_ERROR "FILE NAME DOES NOT TERMINATE WITH HLSL: " ${HLSL_CHECK} " - " ${file})
        RETURN ()
    ENDIF ()

    GET_FILENAME_COMPONENT (FILE_NAME "${FILE_NAME_E}" NAME_WE)
    GET_FILENAME_COMPONENT (SHADER_TYPE "${FILE_NAME_E}" LAST_EXT)

    IF (${SHADER_TYPE} STREQUAL ".vs")

        SET (SHADER_TYPE_NAME "Vertex")
        SET (SHADER_TYPE_EXT_UPPER "VS")
        SET (SHADER_TYPE_EXT_LOWER "vs")

    ELSEIF (${SHADER_TYPE} STREQUAL ".ps")

        SET (SHADER_TYPE_NAME "Pixel")
        SET (SHADER_TYPE_EXT_UPPER "PS")
        SET (SHADER_TYPE_EXT_LOWER "ps")

    ELSE ()

        MESSAGE (SEND_ERROR "UNKNOWN HLSL SHADER FILE TYPE: " ${SHADER_TYPE} " - " ${file})
        RETURN ()

    ENDIF ()

    GET_PROPERTY (isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    IF (isMultiConfig)
        SET (SHADER_CONFIG_LIST "${CMAKE_CONFIGURATION_TYPES}")
    ELSE ()
        SET (SHADER_CONFIG_LIST "${MK_COMPILE__TYPE}")
    ENDIF ()

    IF (NOT TARGET ${MK_BUILD_ROOT__MODULE_NAME}-Shaders)
        DEFINE_PROPERTY (TARGET PROPERTY "HLSL_SHADER_GENERATED")
        ADD_CUSTOM_TARGET (
            ${MK_BUILD_ROOT__MODULE_NAME}-Shaders
            ALL
            DEPENDS $<TARGET_PROPERTY:${MK_BUILD_ROOT__MODULE_NAME}-Shaders,HLSL_SHADER_GENERATED>
        )
        SET_TARGET_PROPERTIES("${MK_BUILD_ROOT__MODULE_NAME}-Shaders" PROPERTIES FOLDER "External Dependencies")
    ENDIF ()

    STRING (REPLACE "/" "\\" INCLUDE_FIXED "${GIT_ROOT_PATH}/teikitu_sdk/TgS KERNEL")
    STRING (REPLACE "/" "\\" MK_BUILD_MODULE_FIXED "${MK_BUILD_MODULE__SRC_DIR}")

    FOREACH (SHADER_CONFIG IN ITEMS ${SHADER_CONFIG_LIST})
        STRING (TOUPPER ${SHADER_CONFIG} SHADER_CONFIG_UPPER)
        SET (SHADER_OUTPUT_FULL_PATH "${CMAKE_BINARY_DIR}\\lib\\${SHADER_CONFIG_UPPER}\\${FILE_NAME}")

        # Add the custom command for non-MSVC generators
        # OUTPUT "${MK_BUILD_MODULE_FIXED}\\${SHADER_CONFIG_UPPER}\\${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.hlsl.h"
        # TARGET ${MK_BUILD_ROOT__MODULE_NAME}-Shaders
        IF (NOT MK_IDE__MSVC AND (${test_current} STREQUAL ${test_assigned}))
            ADD_CUSTOM_COMMAND (OUTPUT "${MK_BUILD_MODULE_FIXED}\\${SHADER_CONFIG_UPPER}\\${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.hlsl.h"
                                       "${SHADER_OUTPUT_FULL_PATH}.${SHADER_TYPE_EXT_LOWER}.cso"
                                COMMAND ${CMAKE_DXC_COMPILER} -T ${SHADER_TYPE_EXT_LOWER}_6_2 -nologo -E"main" -HV 2021 -Zpc -Zsb -Zi -I"${INCLUDE_FIXED}" /
                                        -Vn "g_ui${FILE_NAME}_${SHADER_TYPE_EXT_UPPER}_Compiled" /
                                        -Fh "${MK_BUILD_MODULE_FIXED}\\${SHADER_CONFIG_UPPER}\\${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.hlsl.h" /
                                        -Fo "${SHADER_OUTPUT_FULL_PATH}.${SHADER_TYPE_EXT_LOWER}.cso" /
                                        -Frs "${SHADER_OUTPUT_FULL_PATH}.root_sig" /
                                        -Fsh "${SHADER_OUTPUT_FULL_PATH}.hash" /
                                        ${file}
                                MAIN_DEPENDENCY ${file}
                                COMMENT "Building HLSL object ${file}"
            )
            SET_PROPERTY (TARGET ${MK_BUILD_ROOT__MODULE_NAME}-Shaders APPEND PROPERTY HLSL_SHADER_GENERATED "${MK_BUILD_MODULE_FIXED}\\${SHADER_CONFIG_UPPER}\\${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.hlsl.h")
        ENDIF ()

        # Add all of the generated header files to the IDE project list.
        IF (MK_IDE__INCLUDE_NON_SOURCE_FILES)
            SET (HEADER_PATH "${MK_BUILD_MODULE__SRC_DIR}/${SHADER_CONFIG_UPPER}/${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.hlsl.h")
            IF (NOT EXISTS "${HEADER_PATH}")
                FILE (WRITE "${HEADER_PATH}" "")
                MESSAGE (STATUS "Created file: ${HEADER_PATH}")
            ENDIF ()

            CMAKE_PATH (SET HEADER_PATH_NORMALIZED NORMALIZE "${HEADER_PATH}")
            CMAKE_PATH (SET IDE_HEADER_PATH NORMALIZE "${ide_path}/../Header Files/${SHADER_CONFIG}")

            TGS_ADD_FILE_TO_IDE (${header_files} ${header_files} ${test_assigned} ${test_current} "${HEADER_PATH}" IDE_PATH ${IDE_HEADER_PATH})
            SET_PROPERTY (SOURCE "${MK_BUILD_MODULE__SRC_DIR}/${SHADER_CONFIG_UPPER}/${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.hlsl.h" PROPERTY HEADER_FILE_ONLY TRUE)
        ENDIF ()
    ENDFOREACH ()

    IF (MK_IDE__INCLUDE_NON_SOURCE_FILES)
        # Set the MSVC shader type properties
        SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_TYPE ${SHADER_TYPE_NAME})
        SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_VARIABLE_NAME "g_ui${FILE_NAME}_${SHADER_TYPE_EXT_UPPER}_Compiled")
        SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_OUTPUT_HEADER_FILE "${MK_BUILD_MODULE_FIXED}\\$(Configuration)\\${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.hlsl.h")
        SET_PROPERTY (SOURCE ${file} PROPERTY VS_SETTINGS "AdditionalIncludeDirectories=${INCLUDE_FIXED}")
        SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_MODEL 6.2)
        SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_ENTRYPOINT main)
        SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_FLAGS [=[-HV 2021 -Zpc -Frs "$(OutDir)%(Filename).root_sig" -Fsh "$(OutDir)%(Filename).hash" -Zsb -Zi]=])

        TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
    ENDIF ()

ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_HLSL_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            GET_FILENAME_COMPONENT( FILE_NAME_E "${file}" NAME_WLE )
            GET_FILENAME_COMPONENT( HLSL_CHECK "${file}" LAST_EXT )
            IF (${HLSL_CHECK} STREQUAL ".hlsl")
                GET_FILENAME_COMPONENT( FILE_NAME "${FILE_NAME_E}" NAME_WE )
                GET_FILENAME_COMPONENT( SHADER_TYPE "${FILE_NAME_E}" LAST_EXT )
                IF (${SHADER_TYPE} STREQUAL ".vs")
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_TYPE Vertex)
                ELSEIF (${SHADER_TYPE} STREQUAL ".ps")
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_TYPE Pixel)
                ELSE ()
                    MESSAGE("UNKNOWN HLSL SHADER FILE TYPE: " ${SHADER_TYPE} " - " ${file})
                ENDIF ()

                STRING (REPLACE "/" "\\" INCLUDE_FIXED "${GIT_ROOT_PATH}/teikitu_sdk/TgS KERNEL")
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SETTINGS "AdditionalIncludeDirectories=${INCLUDE_FIXED}")

                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_MODEL 6.2)
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_ENTRYPOINT main)
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_OBJECT_FILE_NAME [=[$(LOCALAPPDATA)\Teikitu\%(Filename).cso]=])
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_FLAGS [=[-HV 2021 -Zpc -Fd "$(OutDir)%(Filename).debug" -Frs "$(OutDir)%(Filename).root_sig" -Fre "$(OutDir)%(Filename).reflection" -Fsh "$(OutDir)%(Filename).hash" -Zsb -Zi]=])
            ELSE ()
                MESSAGE("FILE NAME DOES NOT TERMINATE WITH HLSL: " ${HLSL_CHECK} " - " ${file})
            ENDIF ()
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# Test compile a simple C++20 file to retrieve the hardware L1 cache line size
MACRO(TGS_RETRIEVE_CACHE_LINE_DEFINITION)

    string(CONCAT __TestCacheLineSize "\n
        #define __STDC_WANT_LIB_EXT1__ 1
        #include <cstdint>
        #include <cstdint>
        #include <cstddef>
        #include <cstdio>
        #include <new>
        int main(int argc, char* argv[])
        {
           (void)argc;
           (void)argv;
        #ifdef __cpp_lib_hardware_interference_size
           using std::hardware_constructive_interference_size;
           using std::hardware_destructive_interference_size;
           printf(\"C++20 CACHE LINE SIZE USED\\n\");
        #else
           // 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
           constexpr std::size_t hardware_constructive_interference_size = 64;
           constexpr std::size_t hardware_destructive_interference_size = 64;
           printf(\"DEFAULT CACHE LINE SIZE USED\\n\");
        #endif
           printf(\"hardware_constructive_interference_size: %zd\\n\",hardware_constructive_interference_size);
           printf(\"hardware_destructive_interference_size: %zd\\n\", hardware_destructive_interference_size);
        }"
    )

    TRY_RUN (
        TgBUILD_REPORT_CACHE_LINE_SIZE_RUN
        TgBUILD_REPORT_CACHE_LINE_SIZE_COMPILE
        SOURCE_FROM_VAR TestCacheLineSize.cxx __TestCacheLineSize
        LOG_DESCRIPTION "Retrieving L1 Cache Size"
        CXX_STANDARD 20
        COMPILE_OUTPUT_VARIABLE __TgBUILD_REPORT_CACHE_LINE_SIZE_COMPILE_OUTPUT
        RUN_OUTPUT_VARIABLE __TgBUILD_REPORT_CACHE_LINE_SIZE_RUN_OUTPUT
    )

    MESSAGE(DEBUG "__TgBUILD_REPORT_CACHE_LINE_SIZE_COMPILE_OUTPUT: " ${__TgBUILD_REPORT_CACHE_LINE_SIZE_COMPILE_OUTPUT})
    MESSAGE(DEBUG "__TgBUILD_REPORT_CACHE_LINE_SIZE_RUN_OUTPUT: " ${__TgBUILD_REPORT_CACHE_LINE_SIZE_RUN_OUTPUT})

    STRING (REGEX MATCH "hardware_constructive_interference_size: ([0-9]+)" _ ${__TgBUILD_REPORT_CACHE_LINE_SIZE_RUN_OUTPUT})
    SET (MK_COMPILE_HARDWARE_CONSTRUCTIVE_INTERFERENCE_SIZE ${CMAKE_MATCH_1})

    STRING (REGEX MATCH "hardware_destructive_interference_size: ([0-9]+)" _ ${__TgBUILD_REPORT_CACHE_LINE_SIZE_RUN_OUTPUT})
    SET (MK_COMPILE_HARDWARE_DESTRUCTIVE_INTERFERENCE_SIZE ${CMAKE_MATCH_1})

    IF (NOT __TgBUILD_REPORT_CACHE_LINE_SIZE_RUN_OUTPUT MATCHES "20 CACHE LINE SIZE USED")
        MESSAGE(WARNING "CACHE LINE SIZE is using fallback values")
    ENDIF ()

ENDMACRO ()


# ========================================================================================================================================================================================================
#  Function: TGS_SET_STANDARD_PROPERTIES
# ========================================================================================================================================================================================================

MACRO (TGS_SET_STANDARD_PROPERTIES TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES SDK_HEADER_FILES)

    # Add standard include paths
    CMAKE_PATH ( SET PCH_SOURCE_PATH NORMALIZE "${PCH_SOURCE_DIR}")
    TARGET_INCLUDE_DIRECTORIES(${TARGET} BEFORE PRIVATE "${PCH_SOURCE_PATH}")
    #MESSAGE( STATUS "CMAKE BUILD: INCLUDE PATH ${PCH_SOURCE_PATH}")

    CMAKE_PATH ( SET PROJECT_SOURCE_PATH NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/")
    TARGET_INCLUDE_DIRECTORIES(${TARGET} BEFORE PRIVATE "${PROJECT_SOURCE_PATH}")
    #MESSAGE( STATUS "CMAKE BUILD: INCLUDE PATH ${PROJECT_SOURCE_PATH}")

    # Custom properties used in our version of CMake to set the intermediate directory
    SET_TARGET_PROPERTIES (${TARGET} PROPERTIES INTERMEDIATE_OUTPUT_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY})
    SET_TARGET_PROPERTIES (${TARGET} PROPERTIES VS_LLVM_VERSION 15.0.4)

    # Add the name of the target as a compiler definition
    STRING (REPLACE "-" "_" TARGET_DEFINITION_NAME ${TARGET})
    TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE ${TARGET_DEFINITION_NAME})

    # Copy all runtime DLLs into the execution directory.
    GET_TARGET_PROPERTY (TARGET_TYPE ${TARGET} TYPE)
    IF (TARGET_TYPE STREQUAL "EXECUTABLE")
        IF (MK_BUILD_OS__WINDOWS)
            SET_TARGET_PROPERTIES (${TARGET} PROPERTIES WIN32_EXECUTABLE 1)
        ENDIF ()

        # _Ring_0___TgS_COMMON__OS_PRELOAD needs to be the first library on the link line. Executable, Shared Library, Module specific link additions need to be done after setting the SDK properties.
        TARGET_LINK_LIBRARIES (${TARGET} PRIVATE _Ring_0___TgS_COMMON__OS_PRELOAD)

        # Check to see if the target has any runtime DLL dependencies, and if so copy them to the build target directory.
        IF (MK_BUILD_OS__WINDOWS AND (NOT "${MK_BUILD_AUTOMATION}" STREQUAL "CICD_BUILD"))
            SET (HAVE_RUNTIME_DLL $<BOOL:$<TARGET_RUNTIME_DLLS:${TARGET}>>)
            #SET (CUSTOM_COMMAND_DEBUG ${CMAKE_COMMAND} -E echo $<TARGET_RUNTIME_DLLS:${TARGET}> $<TARGET_FILE_DIR:${TARGET}>)
            #ADD_CUSTOM_COMMAND (TARGET ${TARGET} POST_BUILD
            #    COMMAND "$<${HAVE_RUNTIME_DLL}:${CUSTOM_COMMAND_DEBUG}>"
            #    COMMAND_EXPAND_LISTS
            #)
            SET (CUSTOM_COMMAND ${CMAKE_COMMAND} -E copy_if_different_with_retry $<TARGET_RUNTIME_DLLS:${TARGET}> $<TARGET_FILE_DIR:${TARGET}>)
            ADD_CUSTOM_COMMAND (TARGET ${TARGET} POST_BUILD
                COMMAND "$<${HAVE_RUNTIME_DLL}:${CUSTOM_COMMAND}>"
                COMMAND_EXPAND_LISTS
            )
        ENDIF ()
    ENDIF ()

    # Create a dependency with the module shader target, if it exists
    IF ( TARGET ${MK_BUILD_ROOT__MODULE_NAME}-Shaders)
        ADD_DEPENDENCIES (${TARGET} ${MK_BUILD_ROOT__MODULE_NAME}-Shaders)
    ENDIF ()




    # -- SOURCE COMPILE OPTIONS AND DEFINITIONS --

    # NOTE: This marks the file, independent of the target (i.e. source file properties are retained within an instance of an invocation.
    FOREACH (MK_LIST_ITEM__FILE_NAME IN ITEMS ${${SOURCE_FILES}} )

        TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "FI\"${PCH_INCLUDE}\"") # Force include
        TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "Yu\"${PCH_INCLUDE}\"") # Use PCH

        GET_FILENAME_COMPONENT( FILE_EXTENSION "${MK_LIST_ITEM__FILE_NAME}" EXT )
        IF (MK_COMPILER__MSVC OR ${FILE_EXTENSION} STREQUAL ".cpp")
            # stdatomic is not supported in MSVC 2022. Compile everything as a C++ project
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" PROPERTY LANGUAGE CXX)
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" APPEND_STRING PROPERTY COMPILE_DEFINITIONS TgCOMPILE_FILE__CXX)
            TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "std:c++20") # Set the CXX standard
            TGS_SOURCE_APPEND_GNU_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "std=c++20") # Set the CXX standard
            TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" [=[Fp"$(IntDir)$(TargetName)_CXX.pch"]=])
        ELSE ()
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" PROPERTY LANGUAGE C)
            TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "std:c17") # Set the C standard
            TGS_SOURCE_APPEND_GNU_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "std=c17") # Set the C standard
            TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" [=[Fp"$(IntDir)$(TargetName)_C.pch"]=])
        ENDIF ()

    ENDFOREACH ()

    # Mark the CXX File source file for PCH creation.
    IF (EXISTS "${PCH_SOURCE_DIR}/${PCH_SOURCE}.cpp")
        TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${PCH_SOURCE_DIR}/${PCH_SOURCE}.cpp" [=[Yc]=]) # Set the CXX standard
    ENDIF ()

    # Mark the C File source file for PCH creation.
    IF (EXISTS "${PCH_SOURCE_DIR}/${PCH_SOURCE}.c")
        TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${PCH_SOURCE_DIR}/${PCH_SOURCE}.c" [=[Yc]=]) # Set the CXX standard
    ENDIF ()



    # -- TARGET COMPILE DEFINITIONS AND OPTIONS --

    # Server/Client Compilation Flags
    GET_PROPERTY (TEST_COMPILE_OPTIONS TARGET ${TARGET} PROPERTY COMPILE_DEFINITIONS)
    LIST (FIND TEST_COMPILE_OPTIONS "TgBUILD_FEATURE__SERVER" INDEX__TgBUILD_FEATURE__SERVER)
    LIST (FIND TEST_COMPILE_OPTIONS "TgBUILD_FEATURE__CLIENT" INDEX__TgBUILD_FEATURE__CLIENT)
    IF (NOT ${INDEX__TgBUILD_FEATURE__SERVER} GREATER -1 AND NOT ${INDEX__TgBUILD_FEATURE__CLIENT} GREATER -1)
        TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE TgBUILD_FEATURE__SERVER)
        TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE TgBUILD_FEATURE__CLIENT)
    ENDIF ()

    IF (MK_BUILD__PRELOAD__MALLOC_OVERRIDE)
        TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE TgBUILD_FEATURE__MALLOC_OVERRIDE)
    ENDIF ()

    IF (MK_BUILD__MIMALLOC_ALLOCATOR)
        TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE TgBUILD_FEATURE__MIMALLOC_ALLOCATOR)
    ENDIF ()

    IF (MK_BUILD__MIMALLOC_DEFAULT)
        TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE TgBUILD_FEATURE__MIMALLOC_DEFAULT)
    ENDIF ()

    TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE TgCOMPILE_DEFAULT_PCH=${PCH_INCLUDE})
    TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE __MODULE__=${MK_BUILD_ROOT__MODULE_NAME})
    TARGET_COMPILE_FEATURES (${TARGET} PUBLIC c_std_${CMAKE_C_STANDARD})
    TARGET_COMPILE_FEATURES (${TARGET} PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
    SET_PROPERTY (TARGET ${TARGET} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

    IF (MK_BUILD_OS__WINDOWS)
        ADD_COMPILE_DEFINITIONS (TgCOMPILE__PLATFORM_TIME)
        IF (MK_BUILD__OS_TEXT_WIDE)
            TARGET_COMPILE_DEFINITIONS(${TARGET} PRIVATE _UNICODE)
            TARGET_COMPILE_DEFINITIONS(${TARGET} PRIVATE UNICODE)
        ENDIF ()
        #IF (MK_COMPILER_FRONTEND__MSVC)
        #    TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE /MD$<$<CONFIG:Debug>:d>)
        #ENDIF ()
    ENDIF ()

    IF (MK_COMPILER_FRONTEND__MSVC)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE /utf-8) # Use UTF8
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE /EHs)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE /Wall)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE $<$<CONFIG:Debug>:/Od /RTC1>)
    ENDIF ()

    IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        # No precompiled headers for clang as they are primarily for template processing (literally not really supported)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -include ${PCH_SOURCE_DIR}/${PCH_INCLUDE})
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -fno-exceptions) # Disable runtime exception handling
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -fno-rtti) # Disable Run Time Type Information
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -fvisibility-inlines-hidden) # Do not add inline functions into the linker symbol tables
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Weverything) # Enable "Everything" warning level
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Werror) # Enforce warnings as errors
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-reserved-macro-identifier) #
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Xclang -fno-dllexport-inlines) # Do not add inline functions into the linker symbol tables
        TARGET_COMPILE_DEFINITIONS(${TARGET} PRIVATE _XOPEN_SOURCE=700)
    ENDIF ()

    IF (MK_BUILD_OS__POSIX AND (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE))
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-old-style-cast)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-zero-as-null-pointer-constant)
    ENDIF()

    IF (MK_COMPILER__MSVC)
        TARGET_COMPILE_DEFINITIONS(${TARGET} PRIVATE D_ANALYSIS)
    ENDIF ()

    # If the host is not Apple
    #TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -fdebug-macro) # Emit macro debug information




    # -- STATIC LIBRARY SETTINGS ----

    IF (TARGET_TYPE STREQUAL "STATIC_LIBRARY")
        IF (MK_COMPILER_FRONTEND__MSVC)
            SET_TARGET_PROPERTIES (${TARGET} PROPERTIES STATIC_LIBRARY_OPTIONS /MACHINE:X64)
        ENDIF ()
    ENDIF ()



    # -- SHARED LIBRARY SETTINGS ----

    IF (TARGET_TYPE STREQUAL "SHARED_LIBRARY")
    ENDIF ()



    # -- LINKER SETTINGS ----

    IF (TARGET_TYPE STREQUAL "EXECUTABLE")
    ENDIF ()

    IF (TARGET_TYPE STREQUAL "EXECUTABLE" OR TARGET_TYPE STREQUAL "SHARED_LIBRARY")
        #TARGET_LINK_OPTIONS (${TARGET} PRIVATE /errorlimit:0)

        IF (MK_COMPILER_FRONTEND__MSVC)
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE /DEBUG)
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE /MACHINE:X64)
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE /NODEFAULTLIB)

            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "KERNEL32")
            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "UUID")
            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "ucrt$<$<CONFIG:Debug>:d>")
            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "vcruntime$<$<CONFIG:Debug>:d>")
            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "msvcrt$<$<CONFIG:Debug>:d>")
        ENDIF ()

        IF (MK_PLATFORM__MAC)
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE "SHELL:-framework AudioToolbox")
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE "SHELL:-framework CoreGraphics")
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE "SHELL:-framework QuartzCore")
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE "SHELL:-framework UIKit")
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE "SHELL:-framework Foundation")
        ENDIF ()
    ENDIF ()

    IF (MK_COMPILER_FRONTEND__GNU)
      IF (MK_BUILD__HOST_LINUX OR MK_BUILD_OS__ANDROID)
          TARGET_LINK_OPTIONS (${TARGET} PRIVATE "-lm")
      ENDIF ()
    ENDIF ()



    # -- INSTALL SETTINGS ----

    SET (MK_BUILD_VERSION_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${MK_BUILD_PACKAGE_PROJECT_NAME}ConfigVersion.cmake")
    SET (MK_BUILD_PROJECT_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${MK_BUILD_PACKAGE_PROJECT_NAME}Config.cmake")
    SET (MK_BUILD_NAMESPACE "${MK_BUILD_PACKAGE_PROJECT_NAME}::")
    SET (MK_BUILD_PROJECT_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${MK_BUILD_PACKAGE_PROJECT_NAME}")

    # Install the resulting targets (libraries, excecutables, etc.)
    TGS_INSTALL( ${TARGET} )
    SET (MK_BUILD_TARGETS_EXPORT_NAME "${MK_BUILD_PACKAGE_PROJECT_NAME}Targets")

    # Install the SDK related header files.
    FOREACH (MK_LIST_ITEM__FILE_NAME IN ITEMS ${${SDK_HEADER_FILES}} )

        FILE (RELATIVE_PATH MK_LIST_ITEM__RELATIVE_PATH ${GIT_ROOT_PATH}/teikitu_sdk/ ${MK_LIST_ITEM__FILE_NAME})
        CMAKE_PATH (GET MK_LIST_ITEM__RELATIVE_PATH PARENT_PATH MK_RELATIVE_PATH)
        INSTALL (FILES ${MK_LIST_ITEM__FILE_NAME} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${MK_BUILD_PACKAGE_PROJECT_NAME}/${MK_RELATIVE_PATH}/")

    ENDFOREACH ()

    # Write the cmake configuration file.
    WRITE_BASIC_PACKAGE_VERSION_FILE ("${MK_BUILD_VERSION_CONFIG_FILE}" VERSION ${CMAKE_PROJECT_VERSION} COMPATIBILITY SameMajorVersion)
    CONFIGURE_PACKAGE_CONFIG_FILE ("${GIT_ROOT_PATH}/cmake/${MK_BUILD_PACKAGE_PROJECT_NAME}-config.cmake.in" "${MK_BUILD_PROJECT_CONFIG_FILE}" INSTALL_DESTINATION "${MK_BUILD_PROJECT_CONFIG_INSTALL_DIR}")
    INSTALL (FILES "${MK_BUILD_PROJECT_CONFIG_FILE}" "${MK_BUILD_VERSION_CONFIG_FILE}" DESTINATION "${MK_BUILD_PROJECT_CONFIG_INSTALL_DIR}")
    INSTALL (EXPORT "${MK_BUILD_TARGETS_EXPORT_NAME}" NAMESPACE "${MK_BUILD_NAMESPACE}" DESTINATION "${MK_BUILD_PROJECT_CONFIG_INSTALL_DIR}")

ENDMACRO (TGS_SET_STANDARD_PROPERTIES)




# ========================================================================================================================================================================================================
#  Function: TGS_SET_STANDARD_LIBRARY_PROPERTIES
# ========================================================================================================================================================================================================

MACRO (TGS_SET_STANDARD_LIBRARY_PROPERTIES TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES SDK_HEADER_FILES)

    ADD_LIBRARY (${MK_BUILD_PACKAGE_PROJECT_NAME}::${TARGET} ALIAS ${TARGET})

    GET_TARGET_PROPERTY (TARGET_TYPE ${TARGET} TYPE)
    IF (TARGET_TYPE STREQUAL "SHARED_LIBRARY")
        TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE MK_BUILD__SHARED_LIBRARY)
    ELSEIF (TARGET_TYPE STREQUAL "STATIC_LIBRARY")
        TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE MK_BUILD__STATIC_LIBRARY)
    ELSE ()
        MESSAGE (FATAL_ERROR "TGS_SET_STANDARD_LIBRARY_PROPERTIES being called on a target that is not a library.")
    ENDIF ()
    TGS_SET_STANDARD_PROPERTIES ( ${TARGET} ${PCH_SOURCE_DIR} ${PCH_SOURCE} ${PCH_INCLUDE} ${SOURCE_FILES} ${HEADER_FILES} ${SDK_HEADER_FILES})

ENDMACRO (TGS_SET_STANDARD_LIBRARY_PROPERTIES)




# ========================================================================================================================================================================================================
#  Function: TGS_SET_STANDARD_EXECUTABLE_PROPERTIES
# ========================================================================================================================================================================================================

MACRO (TGS_SET_STANDARD_EXECUTABLE_PROPERTIES TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES)

    #SET_TARGET_PROPERTIES (${TARGET} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer: Andrew Aye")
    SET (SDK_HEADER_FILES "")
    TGS_SET_STANDARD_PROPERTIES ( ${TARGET} ${PCH_SOURCE_DIR} ${PCH_SOURCE} ${PCH_INCLUDE} ${SOURCE_FILES} ${HEADER_FILES} SDK_HEADER_FILES)

ENDMACRO (TGS_SET_STANDARD_EXECUTABLE_PROPERTIES)




# ========================================================================================================================================================================================================
#  Function: TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES
# ========================================================================================================================================================================================================

MACRO (TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES)

    # Add Unit Test paths for compilation
    TARGET_INCLUDE_DIRECTORIES(${TARGET}            PRIVATE "${GIT_ROOT_PATH}/teikitu_private/tests/TgS UNIT TEST")

    # SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Sign to Run Locally")
    SET (SDK_HEADER_FILES "")
    TGS_SET_STANDARD_PROPERTIES ( ${TARGET}         ${PCH_SOURCE_DIR} ${PCH_SOURCE} ${PCH_INCLUDE} ${SOURCE_FILES} ${HEADER_FILES} SDK_HEADER_FILES)

ENDMACRO (TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES)
