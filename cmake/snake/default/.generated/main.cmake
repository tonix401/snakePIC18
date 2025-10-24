# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(snake_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(snake_default_default_XC8_FILE_TYPE_assemble)
add_library(snake_default_default_XC8_assemble OBJECT ${snake_default_default_XC8_FILE_TYPE_assemble})
    snake_default_default_XC8_assemble_rule(snake_default_default_XC8_assemble)
    list(APPEND snake_default_library_list "$<TARGET_OBJECTS:snake_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(snake_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(snake_default_default_XC8_assemblePreprocess OBJECT ${snake_default_default_XC8_FILE_TYPE_assemblePreprocess})
    snake_default_default_XC8_assemblePreprocess_rule(snake_default_default_XC8_assemblePreprocess)
    list(APPEND snake_default_library_list "$<TARGET_OBJECTS:snake_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(snake_default_default_XC8_FILE_TYPE_compile)
add_library(snake_default_default_XC8_compile OBJECT ${snake_default_default_XC8_FILE_TYPE_compile})
    snake_default_default_XC8_compile_rule(snake_default_default_XC8_compile)
    list(APPEND snake_default_library_list "$<TARGET_OBJECTS:snake_default_default_XC8_compile>")
endif()

add_executable(snake_default_image_ywhjNp6H ${snake_default_library_list})

set_target_properties(snake_default_image_ywhjNp6H PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${snake_default_output_dir})
set_target_properties(snake_default_image_ywhjNp6H PROPERTIES OUTPUT_NAME "default")
set_target_properties(snake_default_image_ywhjNp6H PROPERTIES SUFFIX ".elf")

target_link_libraries(snake_default_image_ywhjNp6H PRIVATE ${snake_default_default_XC8_FILE_TYPE_link})


# Add the link options from the rule file.
snake_default_link_rule(snake_default_image_ywhjNp6H)



