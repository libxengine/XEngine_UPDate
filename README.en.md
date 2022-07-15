[中文](README.md) ||  [English](README.en.md)  
# XEngine_UPDate
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

#### XEngine Evn
you must install XEngine,need V7.38 or above,install XEngine can be refer to xengine Readme docment  
GITEE:https://gitee.com/xyry/libxengine  
GITHUB:https://github.com/libxengine/xengine

##### fast to deployment 
git clone https://gitee.com/xyry/libxengine.git or git clone https://github.com/libxengine/xengine.git  
window Exection XEngine_WINEnv.bat   
Linux Exection:sudo ./XEngine_LINEnv.sh -i 3  
Macos Exection:./XEngine_LINEnv.sh -i 3

#### Windows
use vs open and complie,support windows 7sp1 and above   
Just Run it.

#### Linux
Linux use Makefile to complie  
supproted ubuntu x64 or centos x64  

#### MacOS
Linux use Makefile to complie,terminal exection,Requires mac 12 and above  

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
- XEngine_Docment  docment directory

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
