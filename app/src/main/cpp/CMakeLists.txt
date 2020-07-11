# 打印输出 --------------- .cxx/cmake/debug/armeabi-v7a/build_output.txt
set(var 123)
message("var = ${var}--${CMAKE_ANDROID_ARCH_ABI}")
set(list_var
        1
        2
        3
        )
message("list_var = ${list_var}")
# 输出测试 ----------------

# 设置最小支持的版本
cmake_minimum_required(VERSION 3.4.1)
# 设置跟路径
set(ROOT_PATH C:/project/Android/ndk/project1/app/src/main)

# 设置cppFlags -std=gnu++11 , cFlags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_C_FLAGS "")

# 设置头文件目录
include_directories(${CMAKE_SOURCE_DIR}/libxml2/include/libxml)

# 1.查找当前目录下的所有源文件，并将其保存到LIBXML2_SOURCES，不能查找子目录
#aux_source_directory(. LIBXML2_SOURCES)

# 2.查找当前目录下的所有源文件
file(GLOB LIBXML2_SOURCES *.c *.cpp)

# 3.设置单个 c 或者 c++ 文件
#[[set(LIBXML2_SOURCES
        "libxml2/SAX.c"
        "libxml2/entities.c"
        "libxml2/encoding.c"
        "libxml2/error.c"
        "libxml2/parserInternals.c"
        "libxml2/parser.c"
        "libxml2/tree.c"
        "libxml2/hash.c"
        "libxml2/list.c"
        "libxml2/xmlIO.c"
        "libxml2/xmlmemory.c"
        "libxml2/uri.c"
        "libxml2/valid.c"
        "libxml2/xlink.c"
        "libxml2/debugXML.c"
        "libxml2/xpath.c"
        "libxml2/xpointer.c"
        "libxml2/xinclude.c"
        "libxml2/DOCBparser.c"
        "libxml2/catalog.c"
        "libxml2/globals.c"
        "libxml2/threads.c"
        "libxml2/c14n.c"
        "libxml2/xmlstring.c"
        "libxml2/buf.c"
        "libxml2/xmlregexp.c"
        "libxml2/xmlschemas.c"
        "libxml2/xmlschemastypes.c"
        "libxml2/xmlunicode.c"
        "libxml2/xmlreader.c"
        "libxml2/relaxng.c"
        "libxml2/dict.c"
        "libxml2/SAX2.c"
        "libxml2/xmlwriter.c"
        "libxml2/legacy.c"
        "libxml2/chvalid.c"
        "libxml2/pattern.c"
        "libxml2/xmlsave.c"
        "libxml2/xmlmodule.c"
        "libxml2/schematron.c"
        )]]

add_library(
        native-lib
        SHARED
        native-lib.cpp
)

add_library(
        xml2
        SHARED
        ${LIBXML2_SOURCES}
)

#[[# 导入第三方的预编译好的库
add_library(libiconv
        SHARED
        IMPORTED
        )

# 设置第三方库属性 so 库路径
set_target_properties(libiconv
        PROPERTIES IMPORTED_LOCATION
        ${ROOT_PATH}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libiconv.so
        )]]

# 导入第三方的预编译好的库
add_library(libzbar
        SHARED
        IMPORTED
        )

# 设置第三方库属性 so 库路径
set_target_properties(libzbar #指明目标库名
        PROPERTIES IMPORTED_LOCATION    #指明要设置的参数
        ${ROOT_PATH}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libzbarjni.so
        )

# 查找系统库 并赋值给log-lib
find_library(
        log-lib
        log
)

# ${log-lib} 找的文件
# C:\Users\yin13\AppData\Local\Android\Sdk\ndk\21.0.6113669\platforms\android-29\arch-arm\usr\lib

# 设置依赖的库（第一个参数必须为目标模块，顺序不能变）
target_link_libraries(
        native-lib
        xml2
        libzbar
        ${log-lib}
)
