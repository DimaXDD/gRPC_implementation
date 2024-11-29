cmake_minimum_required(VERSION 3.15)

project(gRPC)

set(re2_DIR "E:/v2/vcpkg/installed/x64-windows/share/re2")
set(absl_DIR "E:/v2/vcpkg/installed/x64-windows/share/absl")
set(gRPC_DIR "E:/v2/vcpkg/installed/x64-windows/share/grpc")
set(utf8_range_DIR "E:/v2/vcpkg/installed/x64-windows/share/utf8_range")
set(Protobuf_DIR "E:/v2/vcpkg/installed/x64-windows/share/protobuf")
set(ZLIB_INCLUDE_DIR "E:/v2/vcpkg/installed/x64-windows/include")
set(ZLIB_LIBRARY "E:/v2/vcpkg/installed/x64-windows/lib/zlib.lib")
set(c-ares_DIR "E:/v2/vcpkg/installed/x64-windows/share/c-ares")
set(OPENSSL_ROOT_DIR "E:/v2/vcpkg/installed/x64-windows")


find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(c-ares CONFIG REQUIRED)

if(NOT TARGET ZLIB::ZLIB)
  find_path(ZLIB_INCLUDE_DIR NAMES zlib.h PATHS ${ZLIB_INCLUDE_DIR})
  find_library(ZLIB_LIBRARY NAMES zlib PATHS ${ZLIB_LIBRARY})
  add_library(ZLIB::ZLIB STATIC IMPORTED)
  set_target_properties(ZLIB::ZLIB PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${ZLIB_INCLUDE_DIR}
    INTERFACE_LINK_LIBRARIES ${ZLIB_LIBRARY}
  )
endif()

include_directories(proto)

add_executable(server src/server.cpp proto/math_operations.grpc.pb.cc proto/math_operations.pb.cc)
add_executable(client src/client.cpp proto/math_operations.grpc.pb.cc proto/math_operations.pb.cc)

target_link_libraries(server PRIVATE gRPC::grpc++ gRPC::grpc++_reflection protobuf::libprotobuf ZLIB::ZLIB OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(client PRIVATE gRPC::grpc++ gRPC::grpc++_reflection protobuf::libprotobuf ZLIB::ZLIB OpenSSL::SSL OpenSSL::Crypto)