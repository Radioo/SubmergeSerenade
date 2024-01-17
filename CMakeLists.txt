cmake_minimum_required(VERSION 3.27)
project(SubmergeSerenade)

set(CMAKE_CXX_STANDARD 23)

# Download CPM.cmake
file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# Dependencies
find_package(Iconv REQUIRED)

CPMAddPackage(
        NAME imgui
        GITHUB_REPOSITORY ocornut/imgui
        GIT_TAG v1.90
)

# Compile imgui as static library
file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)

# nativefiledialog-extended
CPMAddPackage("gh:btzy/nativefiledialog-extended@1.1.1")

CPMAddPackage(
        NAME pugixml
        URL https://github.com/zeux/pugixml/releases/download/v1.14/pugixml-1.14.tar.gz
        VERSION 1.14
        DOWNLOAD_ONLY YES
)

if(pugixml_ADDED)
    # Header-only for simplicity, see manual for more options
    add_library(pugixml INTERFACE)
    target_compile_definitions(pugixml INTERFACE PUGIXML_HEADER_ONLY)
    target_include_directories(pugixml INTERFACE ${pugixml_SOURCE_DIR}/src)
endif()

add_executable(SubmergeSerenade src/main.cpp
        src/UI/MainWindow.cpp
        src/UI/MainWindow.hpp
        src/UI/GameUISection.cpp
        src/UI/GameUISection.hpp
        src/UI/SDVX/SdvxSection.cpp
        src/UI/SDVX/SdvxSection.hpp
        src/ChartManager/Managers/SDVXChartManager.cpp
        src/ChartManager/Managers/SDVXChartManager.hpp
        src/ChartManager/ChartManager.cpp
        src/ChartManager/ChartManager.hpp
        src/UI/UIHelpers.cpp
        src/UI/UIHelpers.hpp
        src/ChartManager/Structures/SDVXParsedSong.hpp
        src/ChartManager/Structures/SDVXParsedDifficulty.hpp
        src/ChartManager/Enums/SDVXDifficulty.hpp
        src/ChartManager/Parsers/SDVX1Parser.cpp
        src/ChartManager/Parsers/SDVX1Parser.hpp
        src/ChartManager/XMLHelper.cpp
        src/ChartManager/XMLHelper.hpp
)

target_link_libraries(SubmergeSerenade imgui d3d12 dxgi nfd pugixml Iconv::Iconv)