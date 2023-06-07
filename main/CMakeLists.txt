file(GLOB_RECURSE SOURCES "src/**.cpp" "src/**.c")

if(CONFIG_CM_BUILD_FIRMWARE)
    set(ENTRY "main.cpp")
elseif(CONFIG_CM_EXAMPLE_ANCS)
    set(ENTRY "../examples/ancs.cpp")
endif()

idf_component_register(SRCS ${ENTRY} ${SOURCES} INCLUDE_DIRS "src")

spiffs_create_partition_image(storage ../spiffs_image FLASH_IN_PROJECT)