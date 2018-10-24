# 全志H3 VNC连接

## 一、vnc登录：

这里主要介绍安装vnc服务以及登录。

### 1、安装vnc服务：

sudo apt-get install vnc4server

### 2、安装完VNC，要求设置服务密码，也就是每次连接VNC时需要输入的密码，为了简单，就输入6位数字了，最低得6位。

vncpasswd

然后输入你的密码即可，我设置的是：123456

#### 3、启动VNCServer，命令：

vncserver

其实输入这个命令，说明你已经开了一个服务器号了，默认是从1开始累加上去的。就是下次你输入再vncserver，服务器号就变为2了。这个服务器号在后面的登录会用到的。

#### 4、登录vnc

## 二、安装xfce4的桌面环境，命令如下：

#### 1、安装xfce4:

sudo apt-get install xfce4

#### 2、过程比较漫长，大小有200MB左右。等安装完成后，我们就可以使用VNC调用Xface了

更改VNC配置，加载Xface桌面

sudo vi .vnc/xstartup

修改配置文件如下：

其实就是把这句话x-window-manager &替换为xfce4-session &就行啦。
爱后再用vnc viewer软件登录

 

在桌面打开终端，如下：


输入命令：sudo shutdown -h down 进行关机