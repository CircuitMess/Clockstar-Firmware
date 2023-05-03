file(GLOB_RECURSE SOURCES "src/**.cpp" "src/**.c")
idf_component_register(SRCS "main.cpp" ${SOURCES} INCLUDE_DIRS "src")
