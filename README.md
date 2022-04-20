[中文](README.md) ||  [English](README.en.md)  
# XEngine_UPDate
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
XEngine版本需要V7.32或者以上版本  

#### XEngine环境
安装XEngine可以参考其Readme文档  
GITEE:https://gitee.com/xyry/libxengine  
GITHUB:https://github.com/libxengine/xengine  

#### Windows
使用VS打开并且编译
你需要按照下面的方式配置环境,不然你可能需要自己在项目中设置库目录

#### Linux
Linux使用Makefile编译  
UBUNTU20.04 x64或者CENTOS8 x64均可  

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
- XEngine_Docment  文档目录结构

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