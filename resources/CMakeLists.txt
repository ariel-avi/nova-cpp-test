add_library(data_resources INTERFACE)
target_compile_definitions(data_resources INTERFACE
        DATA_FILE="${CMAKE_CURRENT_SOURCE_DIR}/data.json"
)