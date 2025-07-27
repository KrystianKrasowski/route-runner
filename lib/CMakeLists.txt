if(TARGET_RUNTIME STREQUAL "freertos")
    add_subdirectory(freertos_kernel)
endif()

add_subdirectory(etl)
