# 编程实现扫描线z缓冲器算法
##开发环境

Microsoft Windows 10 Pro 64bit

Visual Studio Community 2017

CMake 3.7.2

Qt 5.8.0

Boost 1.63.0

使用低版本的程序和库应该也能够编译运行
##编译

下载Qt，并将QT_DIR添加到环境变量。用本机的目录替换命令中的目录。

`setx -m QTDIR D:\qt-everywhere-opensource-src-5.8.0`

QTDIR目录下应当有qtbase目录。

把`%QTDIR%\qtbase\bin`添加到path中。

下载Boost（源码即可），并添加环境变量BOOST_ROOT。

`setx -m BOOST_ROOT D:\boost_1_63_0`

之后使用CMake打开源码目录，生成VS工程即可编译运行。

## 使用说明

## 数据结构

