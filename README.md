# awtk-android

awtk android 移植

## 安装 android 开发环境

安装 android 开发环境比较麻烦，建议花几十块在淘宝上请人安装，绝对物有所值。

## 设置 android 环境变量

如果使用bash，可以按下面的方式设置：

> Windows 下可以使用 git bash，或者设置到系统环境变量中。

```
export ANDROID_HOME=/Users/jim/Library/Android/sdk/
export ANDROID_NDK_HOME=/Users/jim/Library/Android/sdk/ndk-bundle/
export PLATFORM_TOOLS_HOME=/Users/jim/Library/Android/sdk/platform-tools

export PATH=$PATH:$NDK_HOME:$PLATFORM_TOOLS_HOME
```

> 具体路径请根据自己的情况进行调整。


## 下载 awtk 和 awtk-android 源码

```
git clone https://github.com/zlgopen/awtk.git
git clone https://github.com/zlgopen/awtk-android.git
```

## 创建并编译 demoui 的工程

* 进入awtk-android

```
cd awtk-android 
```

* 创建工程

```
python create_project.py ../awtk/demos/demoui_build.json
```

* 编译工程

```
cd build/demoui && ./gradlew build
```

## 创建并编译自己的工程

创建并编译自己的工程需要先写一个配置文件，请参考 [Android 平台编译配置](https://github.com/zlgopen/awtk/blob/master/docs/build_config.md)

后续过程和 demoui 完全一样。

> 不同平台有些差异，请酌情修改。建议使用bash，Windows下可以使用git bash。


