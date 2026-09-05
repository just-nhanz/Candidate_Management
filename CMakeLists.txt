cmake_minimum_required(VERSION 3.14)
project(CandidateManagement VERSION 1.0.0 LANGUAGES CXX)

# ─── Chuẩn C++17 ──────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ─── Compiler warnings ────────────────────────────────────────────────────────
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -O2)
endif()

# ─── Include directories ──────────────────────────────────────────────────────
include_directories(include)

# ─── Source files (dùng chung cho cả main và benchmark) ──────────────────────
set(COMMON_SOURCES
    src/Candidate.cpp
    src/Node.cpp
    src/LinkedList.cpp
    src/HashTable.cpp
    src/CandidateSorter.cpp
    src/GroupManager.cpp
    src/RoomManager.cpp
    src/FileManager.cpp
    src/CandidateManager.cpp
)

# ─── Executable chính ─────────────────────────────────────────────────────────
add_executable(candidate_manager main.cpp ${COMMON_SOURCES})

# ─── Benchmark (không build theo mặc định, dùng: cmake --build . --target benchmark) ──
add_executable(benchmark EXCLUDE_FROM_ALL
    tests/benchmark.cpp
    src/Candidate.cpp
    src/Node.cpp
    src/LinkedList.cpp
    src/HashTable.cpp
    src/CandidateSorter.cpp
    src/FileManager.cpp
)

# ─── Đặt thư mục làm việc khi chạy từ build/ để tìm được data/ ───────────────
set_target_properties(candidate_manager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
set_target_properties(benchmark PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
)

# ─── Hướng dẫn build ──────────────────────────────────────────────────────────
message(STATUS "")
message(STATUS "  Build với CMake:")
message(STATUS "    mkdir build && cd build")
message(STATUS "    cmake ..")
message(STATUS "    cmake --build .")
message(STATUS "    ./candidate_manager  (chạy từ thư mục gốc)")
message(STATUS "")
