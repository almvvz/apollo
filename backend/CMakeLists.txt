cmake_minimum_required(VERSION 3.16)
project(backend CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(store STORE_SRC)
aux_source_directory(utils UTILS_SRC)

add_executable(${PROJECT_NAME}
    main.cc
    ${CTL_SRC}
    ${FILTER_SRC}
    ${STORE_SRC}
    ${UTILS_SRC}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon OpenSSL::SSL OpenSSL::Crypto)
