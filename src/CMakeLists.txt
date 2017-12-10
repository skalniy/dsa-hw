cmake_minimum_required (VERSION 3.0)

foreach(TABLE_NAME stl_wrapper chain double_hash cuckoo)
    add_library(${TABLE_NAME} "${TABLE_NAME}.cxx")
    target_include_directories(${TABLE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

    add_executable("${TABLE_NAME}-bin" main.cxx)
    target_compile_definitions("${TABLE_NAME}-bin" PUBLIC 
        TABLE_NAME=${TABLE_NAME}
        HEADER_NAME="${TABLE_NAME}.hxx"
    )
    target_include_directories("${TABLE_NAME}-bin" PUBLIC "${PROJECT_BINARY_DIR}/include")
    target_link_libraries("${TABLE_NAME}-bin" "${TABLE_NAME}")
    set_target_properties("${TABLE_NAME}-bin" PROPERTIES OUTPUT_NAME "${TABLE_NAME}")
endforeach(TABLE_NAME)
