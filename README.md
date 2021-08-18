[中文](README.md) ||  [English](README.en.md)  
# XEngine_MQService
本仓库有开发和主分支,如果要使用,请使用master分支下的代码  

## 介绍
c c++ 软件更新服务  
c c++ Software update service  

## 软件架构
此软件基于XEngine开发.采用C/C++作为开发语言  
此软件是一个更新客户端,可以让用户方便的更新自己的软件  

## 软件特性
此软件支持以下特性  
1. 文件更新  
2. 模块更新
3. 文件解压  
4. 自动运行  
5. 支持相对路径和绝对路径
6. 支持更新删除指定文件或文件夹

## 安装教程

#### 版本需求
支持WINDOWS 7SP1和LINUX(UBUNT20.04,CENTOS8)以上系统  
XEngine版本需要V7.19或者以上版本  
vcpkg 需要2021.05.11以上版本  

#### Windows
使用VS2019 x86(debug release) x64(release)打开并且编译
你需要按照下面的方式配置环境,不然你可能需要自己在项目中设置库目录
##### 三方库环境
需要使用VCPKG安装环境.代码地址:https://github.com/microsoft/vcpkg  
安装好后你可能需要把它集成到你的VS中  
然后命令安装环境: vcpkg.exe install jsoncpp   
集成VS环境: vcpkg integrate install  
vcpkg 主要为了方便安装jsoncpp,如果你想自己配置jsoncpp的环境,可以不使用vcpkg...  

##### XEngine环境
XEngine可以直接下载,下载完毕后添加用户环境变量,需要下面两个  
- XEngine_Include 指向头文件目录地址
- XEngine_Library 指向库文件目录地址

#### Linux
Linux使用Makefile编译  
UBUNTU20.04 x64或者CENTOS8 x64均可  

##### 三方库环境
基于不同系统,可能命令不同,比如在Ubuntu下面  
sudo apt install libjsoncpp-devel  
Centos8.x  
sudo dnf install jsoncpp-devel  

##### XEngine环境
XEngine可以通过脚本文件安装sudo XEngine_RunEnv.sh -i 3
##### 编译命令
在XEngine_Source目录下执行命令
make 编译  
make FLAGS=InstallAll 安装库程序  
make FLAGS=CleanAll 清理编译  

#### 使用说明

1.  切换到MASTER分支
2.  下载代码
3.  编译
4.  安装
5.  运行
6.  运行演示代码

## 目录结构
- XEngine_Release  安装目录结构  
- XEngine_Source   源代目录结构  

## 参与贡献
由于我们提供的是控制台方式的检查和下载更新,可能不会太符合各位的软件需求  
我们欢迎大家FORK仓库并且修改适合自己的更新程序  

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request  

## 关注我们
如果你觉得这个软件对你有帮助,请你给我们一个START吧

## 提交问题

如果你有问题,可以在issues中提交