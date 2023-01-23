set(TARGET thrust)

set(SOURCES
    main.cpp
)

set(INCLUDE_DIRS
    ${${CONAN_INCLUDE_DIRS}}
)

add_executable(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRS})
