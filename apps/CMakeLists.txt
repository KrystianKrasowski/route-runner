# "freertos" variable comes from previous implementation, where there was also superloop variant
if(TARGET_RUNTIME STREQUAL "freertos")
    add_subdirectory(freertos)
endif()
