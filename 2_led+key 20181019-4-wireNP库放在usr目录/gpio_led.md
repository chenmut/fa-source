### GPIO

#### 实例1：按键控制 led  (version 0.1)

1. ##### WiringNP 在 NanoPi NEO 上的安装

```shell
$ git clone https://github.com/friendlyarm/WiringNP
$ cd WiringNP/
$ chmod 755 build
$ ./build
```

测试安装

```shell
$ gpio readall
```

2. 进入程序目录

```shell
$ cd src
$ make 
```

3. 执行可执行文件

```shell
$ ./ledButton
```
