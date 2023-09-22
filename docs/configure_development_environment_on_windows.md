# 在 windows 上面搭开发环境

​	通过 create_project.py 最终是生成出来一个 androidstudio 的项目出来，所以最终我们需要配置出一个让 androidstudio 编译的环境，才可以调用 gradlew build 命令编译。

​	下面开始配置各项环境配置：

## 1. 安装 JDK 环境

​	目前使用的 JDK 17 的版本，这个版本有可能根据 androidstudio 的版本不同而需要升级的，下载地址：

~~~
https://www.oracle.com/java/technologies/downloads/#jdk21-windows
~~~

​	下载完后直接安装，安装后，在环境变量中创建一个名为 JAVA_HOME 的变量，其数值为 JDK 的安装目录路径（默认为 C:\Program Files\Java\jdk-17）。

​	然后在 PATH 的环境变量中加入 %JAVA_HOME%\bin。

​	最后在命令行输入 java 查看是否配置正确，如果可以正确运行 java 的话，就是配置正确。

## 2. android-sdk-windows 环境

​	现在 sdk 都是通过谷歌新的 sdkmanager 工具来生成的，所以去下面的地址中下载最新的“command line tools only”软件包，然后将其解压缩。

~~~
https://developer.android.google.cn/studio
~~~

​	创建一个 android-sdk-windows 的文件夹（假设为 C:\android-sdk-windows），用于存放 android-sdk-windows 的文件。

​	然后进入解压后的 sdkmanager 目录下的 bin 文件夹目录，输入下面的命令：

1. 下载安卓版本 33 的工具包：

~~~cmd
sdkmanager "platform-tools" "platforms;android-33" --sdk_root=C:\android-sdk-windows
~~~

2. 更新 sdk 的 licenses：

~~~cmd
sdkmanager --licenses --sdk_root=C:\android-sdk-windows
~~~

​	最后在环境变量中创建 ANDROID_HOME 的变量，其数值为 android-sdk-windows 的目录路径。

## 3. NDK 环境

​	ndk 是用于安装下的 c/c++ 的交叉编译工具链，下载地址为：

~~~
https://developer.android.google.cn/ndk/downloads?hl=zh-cn
~~~

​	在该地址上面，下载对应的 NDK 版本就可以了（这里是使用 r25c 的版本），下载后解压，在环境变量中创建 ANDROID_NDK_HOME 的变量，其数值为解压后的目录路径。

## 4. 编译下载

​	根据 readme 文件中，执行 gradlew build 命令后，会自动远程下载 androidstudio 的工具（有可能需要翻墙），这些工具包括 cmake 等，如果之前已经配置好了就不会重新再下载，然后等待编译完成即可。
