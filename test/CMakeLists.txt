if(TARGET_ARCH STREQUAL "test")
    add_subdirectory(linebot)
    add_subdirectory(adapters)
    add_subdirectory(utils)
    add_subdirectory(mocks)
endif()
