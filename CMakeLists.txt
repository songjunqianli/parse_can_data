cmake_minimum_required(VERSION 3.5)
project(can_data_parser)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if (NOT (DEFINED ARCH_PLAT_VENDOR))
    # default for linux
    set(ARCH_PLAT_VENDOR x86_64_ubuntu)
endif ()

set(BUILD_TEST ON)

find_package(glog 0.5.0 REQUIRED)

include_directories(
        include)

file(GLOB_RECURSE PROJECT_SRC
    "src/*.cc")

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRC})

if(BUILD_TEST)
    #测试can口
    add_executable(test_can_port test/test_can_port.cc)
    target_link_libraries(test_can_port can_data_parser glog::glog)

    #测试载入DBC
    add_executable(test_load_dbc test/test_load_dbc.cc)
    target_link_libraries(test_load_dbc can_data_parser glog::glog)

    #测试在线解析数据
    add_executable(test_parse_candata_online test/test_parse_candata_online.cc)
    target_link_libraries(test_parse_candata_online can_data_parser glog::glog)

    #测试离线解析数据
    add_executable(testParseSpecialSignal test/testParseSpecialSignal.cc)
    target_link_libraries(testParseSpecialSignal can_data_parser glog::glog)

endif()

# install(TARGETS ${PROJECT_NAME}
#         LIBRARY DESTINATION lib
#         ARCHIVE DESTINATION lib
#         RUNTIME DESTINATION bin
#         INCLUDES DESTINATION .
#         )



