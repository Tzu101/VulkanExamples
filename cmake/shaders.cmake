function(compile_shader SOURCE_FILE)
    set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/${SOURCE_FILE})
    set(OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${SOURCE_FILE}.spv)

    add_custom_command(
        OUTPUT ${OUTPUT_PATH}
        COMMAND ${GLSL_COMPILER} -V ${SOURCE_PATH} -o ${OUTPUT_PATH}
        DEPENDS ${SOURCE_PATH}
        COMMENT "Compiling ${SOURCE_PATH} to ${OUTPUT_PATH}"
        VERBATIM
    )
    
    string(REPLACE "/" "_" TARGET_NAME ${SOURCE_FILE})
    add_custom_target(${TARGET_NAME} ALL DEPENDS ${OUTPUT_PATH})
endfunction()

function(compile_shaders SHADER_FOLDER)
    file(GLOB SHADER_FILES "${SHADER_FOLDER}/*")
    
    foreach(SHADER_FILE ${SHADER_FILES})
        if(IS_DIRECTORY ${SHADER_FILE})
            get_filename_component(SHADER_SUBFOLDER ${SHADER_FILE} NAME)
            compile_shaders("${SHADER_FOLDER}/${SHADER_SUBFOLDER}")
        else()
            get_filename_component(SHADER_NAME ${SHADER_FILE} NAME)
            compile_shader(${SHADER_FOLDER}/${SHADER_NAME})
        endif()
    endforeach()
endfunction()