# awtk-android

awtk android 移植

## 安装 android 开发环境

安装 android 开发环境比较麻烦，建议花几十块在淘宝上请人安装，绝对物有所值。

## 设置 android 环境变量

```
export ANDROID_HOME=/Users/jim/Library/Android/sdk/
export ANDROID_NDK_HOME=/Users/jim/Library/Android/sdk/ndk-bundle/
export PLATFORM_TOOLS_HOME=/Users/jim/Library/Android/sdk/platform-tools

export PATH=$PATH:$NDK_HOME:$PLATFORM_TOOLS_HOME
```
> 具体路径请根据平台调整。


## 下载 awtk 和 awtk-android 源码

```
git clone https://github.com/zlgopen/awtk.git
git clone https://github.com/zlgopen/awtk-android.git
```

## 创建并编译 demoui 的工程

```
cd awtk-android 

python create_project.py ../awtk/demos/demoui_build.json

cd build/demoui && ./gradlew build
```

## 创建并编译自己的工程

创建并编译自己的工程需要先写一个配置文件，请参考 [Android 平台编译配置](https://github.com/zlgopen/awtk/blob/master/docs/build_config.md)

后续过程和 demoui 完全一样。

> 不同平台有些差异，请酌情修改。
