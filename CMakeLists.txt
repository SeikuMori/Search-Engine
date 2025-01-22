cmake_minimum_required(VERSION 3.10)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)

# Подключаем библиотеку JSON
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# Добавляем основной исполняемый файл
add_executable(search_engine main.cpp src/ConverterJSON.cpp src/InvertedIndex.cpp src/SearchServer.cpp)

# Подключаем библиотеку JSON
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

# Подключаем Google Test для тестирования
enable_testing()
add_subdirectory(tests)
