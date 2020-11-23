# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# generate lib
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)  ######### 增加此行，2019.10.17
aux_source_directory(. DIR_SRC)
add_library(Netlib ${DIR_SRC})

target_link_libraries(Netlib mysqlclient)