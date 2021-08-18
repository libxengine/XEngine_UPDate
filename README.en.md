[中文](README.md) ||  [English](README.en.md)  
# XEngine_MQService
This repository has a development and master branch. If you want to use it, please use the master branch  

#### Description
c c++ 软件更新服务  
c c++ Software update service  

#### Software Architecture
the software developed based on xengine,using c/c++ development  
the software is a update client,Allow users to easily update their own software  

## Software features
this software support following features  
1. File update  
2. Module update  
3. file uncompress  
4. auto run  
5. Support relative path and absolute path
6. Support delete file or dir when update

## install

#### Requirements  
support system above windows 7sp1 and linux(ubuntu20.04,centos8)  
XEngine need V7.19 or above  
vcpkg need 2021.05.11 or above  

#### Windows
use vs2019 x86(debug or release) x64(only release) open and complie  
You need to configure the environment in the following way, otherwise you may need to set the library directory in the project yourself  

##### install Dependent library
vcpkg:https://github.com/microsoft/vcpkg   
vcpkg.exe install jsoncpp  
vcpkg integrate install  
you can not use vcpkg and config jsoncpp development for youself   

##### XEngine
XEngine can be download with mine repository,whe you downloaded xengine,you have to add value to you user environment  
- XEngine_Include header file path
- XEngine_Library library file path

#### Linux
Linux use Makefile to complie  
supproted ubuntu x64 or centos x64     

##### install Dependent library
install jsoncpp to your system  
ubuntu20.04  
sudo apt install libjsoncpp-devel  
Centos8.x  
sudo dnf install jsoncpp-devel  

##### XEngine Install
you can install xengine env to your system by shell   
like this:sudo XEngine_RunEnv.sh -i 3  
##### complie
execute command in XEngine_Source path
make complie  
make FLAGS=InstallAll install  
make FLAGS=CleanAll clear  

#### use

1.  Switch to the MASTER branch
2.  download code
3.  complie
4.  install
5.  run
6.  run example code  

## directory struct
- XEngine_Release  install directory  
- XEngine_Source   code    directory  

## Participate in contribution
Since what we provide is a console method of checking and downloading updates, it may not meet your software needs too much  
We welcome everyone to the FORK warehouse and modify the update program that suits you  

1. Fork this code
2. Create new Feat_xxx branch
3. Submit the code
4. New Pull Request

## Follow us
If you think this software is helpful to you, please give us a START

## post issues

if you have eny quest.post issues...
