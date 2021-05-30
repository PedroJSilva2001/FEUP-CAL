cmake_minimum_required(VERSION 3.17)
project(CAL-TP_classes)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

# Add the source files of each TP class
file(GLOB TP1_FILES CONFIGURE_DEPENDS
        "TP1/*.cpp"
        )
file(GLOB TP2_FILES CONFIGURE_DEPENDS
        "TP2/*.cpp"
        )
file(GLOB TP3_FILES CONFIGURE_DEPENDS
        "TP3/*.cpp"
        )
file(GLOB TP4_FILES CONFIGURE_DEPENDS
        "TP4/*.cpp"
        )
file(GLOB TP5_FILES CONFIGURE_DEPENDS
        "TP5/*.cpp"
        )
file(GLOB TP6_FILES CONFIGURE_DEPENDS
        "TP6/*.cpp"
        )
file(GLOB TP7_FILES CONFIGURE_DEPENDS
        "TP7/*.cpp"
        )
file(GLOB TP8_FILES CONFIGURE_DEPENDS
        "TP8/*.cpp"
        )
file(GLOB TP9_FILES CONFIGURE_DEPENDS
        "TP9/*.cpp"
        )
file(GLOB TP10_FILES CONFIGURE_DEPENDS
        "TP10/*.cpp"
        )

add_executable(TP1
        main.cpp
        ${TP1_FILES}
        )
add_executable(TP2
        main.cpp
        ${TP2_FILES}
        )
add_executable(TP3
        main.cpp
        ${TP3_FILES}
        )
add_executable(TP4
        main.cpp
        ${TP4_FILES}
        )
add_executable(TP5
        main.cpp
        ${TP5_FILES}
        )
add_executable(TP6
        main.cpp
        ${TP6_FILES}
        )
add_executable(TP7
        main.cpp
        ${TP7_FILES}
        )
add_executable(TP8
        main.cpp
        ${TP8_FILES}
        )
add_executable(TP9
        main.cpp
        ${TP9_FILES}
        )
add_executable(TP10
        main.cpp
        ${TP10_FILES}
        )

target_link_libraries(TP1 gtest_main gmock_main)
target_link_libraries(TP2 gtest_main gmock_main)
target_link_libraries(TP3 gtest_main gmock_main)
target_link_libraries(TP4 gtest_main gmock_main)
target_link_libraries(TP5 gtest_main gmock_main)
target_link_libraries(TP6 gtest_main gmock_main)
target_link_libraries(TP7 gtest_main gmock_main)
target_link_libraries(TP8 gtest_main gmock_main)
target_link_libraries(TP9 gtest_main gmock_main)
target_link_libraries(TP10 gtest_main gmock_main)