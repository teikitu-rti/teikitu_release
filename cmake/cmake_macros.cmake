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
# Function to create a symlink immediately upon execution (configure time)
FUNCTION (create_symlink_at_configure TARGET_PATH LINK_PATH)
    
    GET_FILENAME_COMPONENT(_LINK_DIR "${LINK_PATH}" DIRECTORY)

    # Use the portable cmake -E create_symlink command
    EXECUTE_PROCESS (
        # Ensure parent directory for the link exists
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_LINK_DIR}"
        RESULT_VARIABLE _result
    )
    IF (_result EQUAL 0)
        # MESSAGE (STATUS "Folder created successfully: ${_LINK_DIR}")
    ENDIF ()

    EXECUTE_PROCESS (
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${TARGET_PATH}" "${LINK_PATH}"
        RESULT_VARIABLE _result
    )
    IF (_result EQUAL 0)
        MESSAGE (STATUS "Creating symlink: ${LINK_PATH} -> ${TARGET_PATH}")
    ELSE ()
        # This message will only appear if the error wasn't fatal (i.e., if 
        # COMMAND_ERROR_IS_FATAL_LAST was not used or failed for other reasons)
        MESSAGE (FATAL_ERROR "Failed to create symlink. Result code: ${_result}")
    ENDIF ()

ENDFUNCTION ()


##########################################################################################################################################################################################################
# add a source file to the given list
FUNCTION (TGS_ADD_FILE_TO_IDE source_files header_files test_assigned test_current file)
    CMAKE_PARSE_ARGUMENTS (TGS_ADD_FILE_TO_IDE "" "IDE_PATH" "" ${ARGN} )
    #MESSAGE("${source_files}")
    #MESSAGE("${TGS_ADD_FILE_TO_IDE_IDE_PATH}")
    #MESSAGE("${file}")
    #MESSAGE(TEST: ${test_current} ${test_assigned})

    SET (TGS_ADD_FILE_TO_IDE__FOUND FALSE PARENT_SCOPE)

    IF (NOT EXISTS ${file})
        STRING (REPLACE "teikitu_private/src" "teikitu_private/int" link_file ${file})
        STRING (REPLACE "teikitu_sdk" "teikitu_private/int" link_file ${link_file})
        #MESSAGE (STATUS "Creating symlink for file: ${link_file}")

        # Automatically attempt to fall back to POSIX implementation if OS file does not exist.
        STRING (REPLACE "MAC" "POSIX" posix_file ${file})
        IF (EXISTS ${posix_file} AND NOT EXISTS ${link_file})
            create_symlink_at_configure ("${posix_file}" "${link_file}")
            IF (NOT EXISTS ${link_file})
                MESSAGE("FILE DOES NOT EXIST AFTER SYMLINK CREATION: " ${link_file})
                RETURN ()
            ENDIF ()
        ENDIF ()

        # Automatically attempt to fall back to POSIX implementation if OS file does not exist.
        STRING (REPLACE "IOS" "POSIX" posix_file ${file})
        IF (EXISTS ${posix_file} AND NOT EXISTS ${link_file})
            create_symlink_at_configure ("${posix_file}" "${link_file}")
            IF (NOT EXISTS ${link_file})
                MESSAGE("FILE DOES NOT EXIST AFTER SYMLINK CREATION: " ${link_file})
                RETURN ()
            ENDIF ()
        ENDIF ()

        # Automatically attempt to fall back to POSIX implementation if OS file does not exist.
        STRING (REPLACE "APPLE" "CLANG" posix_file ${file})
        IF (EXISTS ${posix_file} AND NOT EXISTS ${link_file})
            create_symlink_at_configure ("${posix_file}" "${link_file}")
            IF (NOT EXISTS ${link_file})
                MESSAGE("FILE DOES NOT EXIST AFTER SYMLINK CREATION: " ${link_file})
                RETURN ()
            ENDIF ()
        ENDIF ()

    ELSE ()
        SET (link_file ${file})
    ENDIF ()

    IF (NOT EXISTS ${link_file})
        MESSAGE("FILE DOES NOT EXIST: " ${file})
        RETURN ()
    ENDIF ()

    SET (TGS_ADD_FILE_TO_IDE__FOUND TRUE PARENT_SCOPE)

    # Add the file to the correct list for compilation
    IF ((${test_current} STREQUAL ${test_assigned}))
        SET (${source_files} ${${source_files}} "${link_file}" PARENT_SCOPE)

    ELSEIF (MK_IDE__INCLUDE_NON_SOURCE_FILES)
        SET (${header_files} ${${header_files}} "${link_file}" PARENT_SCOPE)
        SET_PROPERTY(SOURCE ${link_file} PROPERTY HEADER_FILE_ONLY TRUE)

    ENDIF ()

    # Assign an IDE path (folder structure)
    IF (TGS_ADD_FILE_TO_IDE_IDE_PATH AND NOT ${TGS_ADD_FILE_TO_IDE_IDE_PATH} STREQUAL "")
        STRING (REPLACE "/" "\\" IDE_PATH_FIXED ${TGS_ADD_FILE_TO_IDE_IDE_PATH})
        #MESSAGE("${IDE_PATH_FIXED}")

        IF (MK_IDE__INCLUDE_NON_SOURCE_FILES AND NOT (${test_current} STREQUAL ${test_assigned}))
            SET (IDE_PATH_FIXED "${IDE_PATH_FIXED}\\${test_assigned} (Inactive)")
        ENDIF ()
        #MESSAGE("${IDE_PATH_FIXED}")

        SOURCE_GROUP ("${IDE_PATH_FIXED}" FILES "${link_file}")

    ENDIF ()
ENDFUNCTION ()


##########################################################################################################################################################################################################
# add a source file to the given list
FUNCTION (TGS_ADD_SOURCE_FILE source_files header_files test_assigned test_current ide_path file)

    TGS_ADD_FILE_TO_IDE(${source_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
    IF (NOT TGS_ADD_FILE_TO_IDE__FOUND)
        RETURN ()
    ENDIF ()

    SET (${source_files} ${${source_files}} PARENT_SCOPE)
    SET (${header_files} ${${header_files}} PARENT_SCOPE)

ENDFUNCTION ()


##########################################################################################################################################################################################################
# add a source file to the given list
FUNCTION (TGS_ADD_INCSRC_FILE source_files header_files test_assigned test_current ide_path file)

    TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
    IF (NOT TGS_ADD_FILE_TO_IDE__FOUND)
        RETURN ()
    ENDIF ()

    SET (${source_files} ${${source_files}} PARENT_SCOPE)
    SET (${header_files} ${${header_files}} PARENT_SCOPE)

    SET_PROPERTY(SOURCE ${local_file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
    SET_PROPERTY(SOURCE ${local_file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
    SET_PROPERTY(SOURCE ${local_file} PROPERTY HEADER_FILE_ONLY TRUE)
ENDFUNCTION ()


##########################################################################################################################################################################################################
# add a source file to the given list
FUNCTION (TGS_ADD_HEADER_FILE source_files header_files test_assigned test_current ide_path file)

    TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
    IF (NOT TGS_ADD_FILE_TO_IDE__FOUND)
        RETURN ()
    ENDIF ()

    SET (${source_files} ${${source_files}} PARENT_SCOPE)
    SET (${header_files} ${${header_files}} PARENT_SCOPE)

    SET_PROPERTY(SOURCE ${local_file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
    SET_PROPERTY(SOURCE ${local_file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
    SET_PROPERTY(SOURCE ${local_file} PROPERTY  HEADER_FILE_ONLY TRUE)
ENDFUNCTION ()


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
    FIND_PROGRAM (CMAKE_DXC_COMPILER NAMES dxc HINTS "$ENV{VULKAN_SDK}/bin")

    IF (EXISTS "${CMAKE_DXC_COMPILER}")
        EXECUTE_PROCESS (
            COMMAND ${CMAKE_DXC_COMPILER} --version
            OUTPUT_VARIABLE DXC_VERSION
        )
        STRING (REGEX MATCHALL "[0-9.]+\\s" DXC_VERSION_REGEX "${DXC_VERSION}")
        SET (CMAKE_DXC_VERSION "${DXC_VERSION_REGEX}")
    ELSE ()
        MESSAGE (FATAL_ERROR "DXC compiler not found")
    ENDIF ()
ENDIF ()


##########################################################################################################################################################################################################
# add a source file to the given list
FUNCTION (TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER source_files header_files test_assigned test_current ide_path file)
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
    STRING (REPLACE "/" "\\" MK_BUILD_MODULE_FIXED "${MK_BUILD_MODULE__INT_DIR}")

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
            SET (HEADER_PATH "${MK_BUILD_MODULE__INT_DIR}/${SHADER_CONFIG_UPPER}/${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.hlsl.h")
            IF (NOT EXISTS "${HEADER_PATH}")
                FILE (WRITE "${HEADER_PATH}" "")
                MESSAGE (STATUS "Created file: ${HEADER_PATH}")
            ENDIF ()

            CMAKE_PATH (SET HEADER_PATH_NORMALIZED NORMALIZE "${HEADER_PATH}")
            CMAKE_PATH (SET IDE_HEADER_PATH NORMALIZE "${ide_path}/../Header Files/${SHADER_CONFIG}")

            TGS_ADD_FILE_TO_IDE (${header_files} ${header_files} ${test_assigned} ${test_current} "${HEADER_PATH}" IDE_PATH ${IDE_HEADER_PATH})
            SET_PROPERTY (SOURCE "${MK_BUILD_MODULE__INT_DIR}/${SHADER_CONFIG_UPPER}/${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.hlsl.h" PROPERTY HEADER_FILE_ONLY TRUE)
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

ENDFUNCTION ()


##########################################################################################################################################################################################################
# add a GLSL file and compile it to a header file
FUNCTION (TGS_ADD_GLSL_FILE_AND_COMPILE_TO_HEADER source_files header_files test_assigned test_current ide_path file)
    MESSAGE(STATUS "Configuring GLSL Shader: ${file}")

    IF (NOT EXISTS ${file})
        MESSAGE (SEND_ERROR "FILE DOES NOT EXIST: " ${file})
        RETURN ()
    ENDIF ()

    GET_FILENAME_COMPONENT (FILE_NAME_E "${file}" NAME_WLE)
    GET_FILENAME_COMPONENT (GLSL_CHECK "${file}" LAST_EXT)

    IF (NOT ${GLSL_CHECK} STREQUAL ".glsl")
        MESSAGE (SEND_ERROR "FILE NAME DOES NOT TERMINATE WITH GLSL: " ${GLSL_CHECK} " - " ${file})
        RETURN ()
    ENDIF ()

    GET_FILENAME_COMPONENT (FILE_NAME "${FILE_NAME_E}" NAME_WE)
    GET_FILENAME_COMPONENT (SHADER_TYPE "${FILE_NAME_E}" LAST_EXT)

    IF (${SHADER_TYPE} STREQUAL ".vert")

        SET (SHADER_TYPE_NAME "Vertex")
        SET (SHADER_TYPE_EXT_UPPER "VERT")
        SET (SHADER_TYPE_EXT_LOWER "vert")

    ELSEIF (${SHADER_TYPE} STREQUAL ".frag")

        SET (SHADER_TYPE_NAME "Fragment")
        SET (SHADER_TYPE_EXT_UPPER "FRAG")
        SET (SHADER_TYPE_EXT_LOWER "frag")

    ELSEIF (${SHADER_TYPE} STREQUAL ".mesh")

        SET (SHADER_TYPE_NAME "Mesh")
        SET (SHADER_TYPE_EXT_UPPER "MESH")
        SET (SHADER_TYPE_EXT_LOWER "mesh")

    ELSEIF (${SHADER_TYPE} STREQUAL ".comp")

        SET (SHADER_TYPE_NAME "Compute")
        SET (SHADER_TYPE_EXT_UPPER "COMP")
        SET (SHADER_TYPE_EXT_LOWER "comp")

    ELSEIF (${SHADER_TYPE} STREQUAL ".task")

        SET (SHADER_TYPE_NAME "Task")
        SET (SHADER_TYPE_EXT_UPPER "TASK")
        SET (SHADER_TYPE_EXT_LOWER "task")

    ELSE ()

        MESSAGE (SEND_ERROR "UNKNOWN GLSL SHADER FILE TYPE: " ${SHADER_TYPE} " - " ${file})
        RETURN ()

    ENDIF ()

    GET_PROPERTY (isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    IF (isMultiConfig)
        SET (SHADER_CONFIG_LIST "${CMAKE_CONFIGURATION_TYPES}")
    ELSE ()
        SET (SHADER_CONFIG_LIST "${MK_COMPILE__TYPE}")
    ENDIF ()

    IF (NOT TARGET ${MK_BUILD_ROOT__MODULE_NAME}-Shaders)
        MESSAGE(STATUS "Creating Custom Target: ${MK_BUILD_ROOT__MODULE_NAME}-Shaders")
        DEFINE_PROPERTY (TARGET PROPERTY "GLSL_SHADER_GENERATED")
        ADD_CUSTOM_TARGET (
            ${MK_BUILD_ROOT__MODULE_NAME}-Shaders
            ALL
            DEPENDS $<TARGET_PROPERTY:${MK_BUILD_ROOT__MODULE_NAME}-Shaders,GLSL_SHADER_GENERATED>
        )
        SET_TARGET_PROPERTIES("${MK_BUILD_ROOT__MODULE_NAME}-Shaders" PROPERTIES FOLDER "External Dependencies")
    ENDIF ()

    IF (CMAKE_HOST_WIN32)
        STRING (REPLACE "/" "\\" INCLUDE_FIXED "${GIT_ROOT_PATH}/teikitu_sdk/TgS KERNEL")
        STRING (REPLACE "/" "\\" MK_BUILD_MODULE_FIXED "${MK_BUILD_MODULE__INT_DIR}")
    ELSE ()
        SET (INCLUDE_FIXED "${GIT_ROOT_PATH}/teikitu_sdk/TgS KERNEL")
        SET (MK_BUILD_MODULE_FIXED "${MK_BUILD_MODULE__INT_DIR}")
    ENDIF ()

    FIND_PROGRAM (CMAKE_GLSLANGVALIDATOR NAMES glslangValidator HINTS "$ENV{VULKAN_SDK}/bin")
    IF (NOT EXISTS "${CMAKE_GLSLANGVALIDATOR}")
        MESSAGE (FATAL_ERROR "glslangValidator not found")
    ENDIF ()

    FOREACH (SHADER_CONFIG IN ITEMS ${SHADER_CONFIG_LIST})
        STRING (TOUPPER ${SHADER_CONFIG} SHADER_CONFIG_UPPER)
        SET (SHADER_OUTPUT_FULL_PATH "${CMAKE_BINARY_DIR}/lib/${SHADER_CONFIG_UPPER}/${FILE_NAME}")
        SET (SHADER_OUTPUT_FULL_PATH_FIXED "${SHADER_OUTPUT_FULL_PATH}")
        # STRING (REPLACE "/" "\\" SHADER_OUTPUT_FULL_PATH_FIXED "${SHADER_OUTPUT_FULL_PATH}")

        # Add the custom command to compile GLSL to header
        IF (${test_current} STREQUAL ${test_assigned})
            SET (SHADER_HEADER_OUTPUT "${MK_BUILD_MODULE__INT_DIR}/${SHADER_CONFIG_UPPER}/${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.glsl.h")

            MESSAGE(STATUS "Adding Custom Command for: '${SHADER_HEADER_OUTPUT}'")

            # Create a list of potential dependency files (headers that might be included)
            FILE(GLOB_RECURSE POTENTIAL_DEPENDENCIES "${INCLUDE_FIXED}/*HLSL.*" "${GIT_ROOT_PATH}/teikitu_private/src/TgS KERNEL/Default_VLKN_Common.glsl")

            # Add a custom command that forces regeneration if output doesn't exist or is empty
            ADD_CUSTOM_COMMAND (
                OUTPUT "${SHADER_HEADER_OUTPUT}"
                WORKING_DIRECTORY ${GIT_ROOT_PATH}

                # Step 0: Create output directory
                COMMAND ${CMAKE_COMMAND} -E echo "Build Step 0: Creating directories for ${SHADER_HEADER_OUTPUT}"
                COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/lib/${SHADER_CONFIG_UPPER}"
                COMMAND ${CMAKE_COMMAND} -E make_directory "${MK_BUILD_MODULE__INT_DIR}/${SHADER_CONFIG_UPPER}"

                # Step 1: Check if output exists and has content, if not force rebuild
                COMMAND ${CMAKE_COMMAND} -E echo "Build Step 1: Touching output file"
                COMMAND ${CMAKE_COMMAND} -E touch "${SHADER_HEADER_OUTPUT}"

                # Step 2: Preprocess with DXC to expand includes and dependencies
                COMMAND ${CMAKE_COMMAND} -E echo "Build Step 2: Preprocessing ${file} with DXC"
                COMMAND pwsh -Command "& '${CMAKE_DXC_COMPILER}' -P -E main -I '${GIT_ROOT_PATH}/teikitu_sdk/TgS KERNEL' -Fi '${SHADER_OUTPUT_FULL_PATH_FIXED}_temp.${SHADER_TYPE_EXT_LOWER}.glsl' '${file}'"

                # Step 3: Remove line directives (platform-specific) and add GLSL required headers
                COMMAND ${CMAKE_COMMAND} -E echo "Build Step 3: Filtering line directives"
                COMMAND pwsh -Command "& '${CMAKE_COMMAND}' --log-level=ERROR -P '${GIT_ROOT_PATH}/cmake/filter_line_directives_and_add_header.cmake' '${SHADER_OUTPUT_FULL_PATH_FIXED}_temp.${SHADER_TYPE_EXT_LOWER}.glsl' '${SHADER_OUTPUT_FULL_PATH_FIXED}_processed.${SHADER_TYPE_EXT_LOWER}.glsl'"

                # Step 4: Compile with glslangValidator to header file
                COMMAND ${CMAKE_COMMAND} -E echo "Build Step 4: Compiling with glslangValidator"
                COMMAND pwsh -Command "& '${CMAKE_GLSLANGVALIDATOR}' -e main -S ${SHADER_TYPE_EXT_LOWER} -o '${SHADER_HEADER_OUTPUT}' --target-env vulkan1.3 --vn 'g_ui${FILE_NAME}_${SHADER_TYPE_EXT_UPPER}_Compiled' '${SHADER_OUTPUT_FULL_PATH_FIXED}_processed.${SHADER_TYPE_EXT_LOWER}.glsl'"

                # Step 5: Verify the output file was created and has content
                COMMAND ${CMAKE_COMMAND} -E echo "Build Step 5: Verifying output"
                COMMAND pwsh -Command "& '${CMAKE_COMMAND}' --log-level=ERROR -P '${GIT_ROOT_PATH}/cmake/verify_shader_output.cmake' '${SHADER_HEADER_OUTPUT}'"

                # Step 6: Clean up temporary files
                COMMAND ${CMAKE_COMMAND} -E echo "Build Step 6: Cleaning up"
                COMMAND ${CMAKE_COMMAND} -E remove -f "${SHADER_OUTPUT_FULL_PATH_FIXED}_temp.${SHADER_TYPE_EXT_LOWER}.glsl" "${SHADER_OUTPUT_FULL_PATH_FIXED}_processed.${SHADER_TYPE_EXT_LOWER}.glsl"

                MAIN_DEPENDENCY "${file}"
                DEPENDS ${POTENTIAL_DEPENDENCIES}
                COMMENT "Compiling GLSL shader '${file}' to header files"
                VERBATIM
            )

            # Add the generated file as a dependency to the custom target
            SET_PROPERTY (TARGET ${MK_BUILD_ROOT__MODULE_NAME}-Shaders APPEND PROPERTY GLSL_SHADER_GENERATED "${SHADER_HEADER_OUTPUT}")

            # Ensure the file exists so CMake doesn't complain during configure
            IF (NOT EXISTS "${SHADER_HEADER_OUTPUT}")
                FILE (WRITE "${SHADER_HEADER_OUTPUT}" "")
                MESSAGE (STATUS "Created placeholder file: ${SHADER_HEADER_OUTPUT}")
            ENDIF ()

            # Add the generated file to the target sources so CMake tracks the dependency
            CMAKE_PATH (SET IDE_HEADER_PATH NORMALIZE "${ide_path}/../Header Files/${SHADER_CONFIG}")
            TGS_ADD_FILE_TO_IDE (${header_files} ${header_files} ${test_assigned} ${test_current} "${SHADER_HEADER_OUTPUT}" IDE_PATH ${IDE_HEADER_PATH})
            SET_PROPERTY (SOURCE "${SHADER_HEADER_OUTPUT}" PROPERTY HEADER_FILE_ONLY TRUE)

        ENDIF ()

        # Add all of the generated header files to the IDE project list (for other configs or if IDE flag is on)
        IF (MK_IDE__INCLUDE_NON_SOURCE_FILES AND NOT (${test_current} STREQUAL ${test_assigned}))
            SET (HEADER_PATH "${MK_BUILD_MODULE__INT_DIR}/${SHADER_CONFIG_UPPER}/${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.glsl.h")
            IF (NOT EXISTS "${HEADER_PATH}")
                FILE (WRITE "${HEADER_PATH}" "")
                MESSAGE (STATUS "Created file: ${HEADER_PATH}")
            ENDIF ()

            CMAKE_PATH (SET HEADER_PATH_NORMALIZED NORMALIZE "${HEADER_PATH}")
            CMAKE_PATH (SET IDE_HEADER_PATH NORMALIZE "${ide_path}/../Header Files/${SHADER_CONFIG}")

            TGS_ADD_FILE_TO_IDE (${header_files} ${header_files} ${test_assigned} ${test_current} "${HEADER_PATH}" IDE_PATH ${IDE_HEADER_PATH})
            SET_PROPERTY (SOURCE "${MK_BUILD_MODULE__INT_DIR}/${SHADER_CONFIG_UPPER}/${FILE_NAME}_${SHADER_TYPE_EXT_LOWER}.glsl.h" PROPERTY HEADER_FILE_ONLY TRUE)
        ENDIF ()
    ENDFOREACH ()

    IF (MK_IDE__INCLUDE_NON_SOURCE_FILES)
        TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
    ENDIF ()

ENDFUNCTION ()


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
# Scope Keywords (PRIVATE, PUBLIC, INTERFACE) in CMAKE
# PRIVATE: The PCH is used only for building this target (my_app).
# INTERFACE: The PCH is not used for this target, but is added to targets that link to it.
# PUBLIC: Used for this target and propagated to targets that link to it.
# ========================================================================================================================================================================================================

MACRO (TGS_SET_STANDARD_PROPERTIES TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES SDK_HEADER_FILES)

    # Add standard include paths
    CMAKE_PATH ( SET PCH_SOURCE_PATH NORMALIZE "${PCH_SOURCE_DIR}")
    TARGET_INCLUDE_DIRECTORIES(${TARGET} BEFORE PRIVATE "${PCH_SOURCE_PATH}")
    #MESSAGE( STATUS "CMAKE BUILD: INCLUDE PATH ${PCH_SOURCE_PATH}")

    CMAKE_PATH ( SET PROJECT_SOURCE_PATH NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/")
    TARGET_INCLUDE_DIRECTORIES(${TARGET} BEFORE PRIVATE "${PROJECT_SOURCE_PATH}")
    #MESSAGE( STATUS "CMAKE BUILD: INCLUDE PATH ${PROJECT_SOURCE_PATH}")

    CMAKE_PATH ( SET LINK_SOURCE_PATH NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/int/")
    TARGET_INCLUDE_DIRECTORIES(${TARGET} BEFORE PRIVATE "${LINK_SOURCE_PATH}")
    #MESSAGE( STATUS "CMAKE BUILD: INCLUDE PATH ${LINK_SOURCE_PATH}")

    # Custom properties used in our version of CMake to set the intermediate directory
    SET_TARGET_PROPERTIES (${TARGET} PROPERTIES INTERMEDIATE_OUTPUT_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY})
    SET_TARGET_PROPERTIES (${TARGET} PROPERTIES VS_LLVM_VERSION 21)

    IF (NOT MK_COMPILER_FRONTEND__MSVC)
        SET_TARGET_PROPERTIES (${TARGET} PROPERTIES
            C_STANDARD 23
            C_STANDARD_REQUIRED ON
            C_EXTENSIONS OFF
        )
    ENDIF ()

    SET_TARGET_PROPERTIES (${TARGET} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )

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
        IF (MK_BUILD__PRELOAD__MALLOC_OVERRIDE)
            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE _Ring_0___TgS_COMMON__OS_PRELOAD)
        ENDIF ()

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
    IF (TARGET ${MK_BUILD_ROOT__MODULE_NAME}-Shaders)
        #MESSAGE( STATUS "Adding Dependency: ${TARGET} ${MK_BUILD_ROOT__MODULE_NAME}-Shaders")
        ADD_DEPENDENCIES (${TARGET} ${MK_BUILD_ROOT__MODULE_NAME}-Shaders)
    ENDIF ()




    # -- SOURCE COMPILE OPTIONS AND DEFINITIONS --

    # NOTE: This marks the file, independent of the target (i.e. source file properties are retained within an instance of an invocation.
    FOREACH (MK_LIST_ITEM__FILE_NAME IN ITEMS ${${SOURCE_FILES}} )

        TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "FI\"${PCH_INCLUDE}\"") # Force include

        GET_FILENAME_COMPONENT( FILE_EXTENSION "${MK_LIST_ITEM__FILE_NAME}" EXT )

        IF (MK_COMPILER__MSVC OR ${FILE_EXTENSION} STREQUAL ".cpp")
            # stdatomic is not supported in MSVC 2022, and there CAS2 implementation is still wrong (10+ years later). Compile everything as a C++ project
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" PROPERTY LANGUAGE CXX)
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" APPEND_STRING PROPERTY COMPILE_DEFINITIONS TgCOMPILE_FILE__CXX)
        ELSEIF (${FILE_EXTENSION} STREQUAL ".mm")
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" PROPERTY LANGUAGE OBJCXX)
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" APPEND_STRING PROPERTY COMPILE_DEFINITIONS TgCOMPILE_FILE__CXX)
        ENDIF ()

        GET_SOURCE_FILE_PROPERTY (IS_PCH_SKIPPED "${MK_LIST_ITEM__FILE_NAME}" SKIP_PRECOMPILE_HEADERS)

        IF (NOT IS_PCH_SKIPPED)
            TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "Yu\"${PCH_INCLUDE}\"") # Use PCH
            IF (MK_COMPILER__MSVC OR ${FILE_EXTENSION} STREQUAL ".cpp")
                TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" [=[Fp"$(IntDir)$(TargetName)_CXX.pch"]=])
            ELSEIF (${FILE_EXTENSION} STREQUAL ".c")
                TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" [=[Fp"$(IntDir)$(TargetName)_C.pch"]=])
            ENDIF ()
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
        IF (MK_BUILD__MIMALLOC_DEFAULT)
            TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE TgBUILD_FEATURE__MIMALLOC_DEFAULT)
        ENDIF ()
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

    IF (MK_COMPILER_FRONTEND__GNU)
        # No precompiled headers for clang as they are primarily for template processing (literally not really supported)
        TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE _XOPEN_SOURCE=700)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -include ${PCH_SOURCE_DIR}/${PCH_INCLUDE})
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -fno-short-enums) # Include support for UTF8 character type and literals
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -finline-functions) # Inline suitable functions
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Weverything) # Enable "Everything" warning level
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Werror) # Enforce warnings as errors
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-reserved-macro-identifier) # 
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-poison-system-directories) # 
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Xclang -fno-dllexport-inlines) # Do not add inline functions into the linker symbol tables
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE  $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE  $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE  $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-old-style-cast)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-zero-as-null-pointer-constant)
    ENDIF()

    IF (MK_COMPILER__APPLE)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-missing-include-dirs)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-c++98-compat-pedantic)
        TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE _DARWIN_C_SOURCE)
        TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE __DARWIN_C_LEVEL=__DARWIN_C_FULL)
    ENDIF()

    IF (MK_COMPILER_FRONTEND__APPLE)
        MESSAGE(FATAL_ERROR "Apple compiler support is not currently maintained.")
    ENDIF ()

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

    CMAKE_PATH ( SET MK_BUILD_MODULE__LINK_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/int/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
    IF (EXISTS ${MK_BUILD_MODULE__LINK_DIR})
        TARGET_INCLUDE_DIRECTORIES(${TARGET} BEFORE PRIVATE "${MK_BUILD_MODULE__LINK_DIR}")
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
