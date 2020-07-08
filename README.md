# awtk-android

awtk android 移植

## 安装 android 开发环境

安装 android 开发环境比较麻烦，建议花几十块在淘宝上请人安装，绝对物有所值。

> 找人安装 Android 开发环境的时候，让他把 NDK 也安装上去。可以用命令行编译，也可以用 android studio 编译。android studio 可以用来调试 C 代码。

## 设置 android 环境变量

如果使用 bash，可以按下面的方式设置：

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
git clone https://github.com/zlgopen/awtk-mobile-plugins.git
```

## 创建并编译 demoui 的工程

* 进入 awtk-android

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

> 生成的 apk 在：build/xxxxxx/app/build/outputs/apk/debug/app-debug.apk 
> 
> xxxxxx 是你的项目名。

## 创建并编译自己的工程

创建并编译自己的工程需要先写一个配置文件，请参考 [Android 平台编译配置](https://github.com/zlgopen/awtk/blob/master/docs/build_config.md)

后续过程和 demoui 完全一样。

> 不同平台有些差异，请酌情修改。建议使用 bash，Windows 下可以使用 git bash。

## 文档

* [用 android studio 调试应用程序](docs/how_to_debug_app_with_android_studio.md)

* [在 Windows 下编译 awtk android 版本](docs/build_on_windows.md)

## 其它问题

* 1. 修改 sdk 路径

如果 sdk 路径不对，可以直接修改 build/xxxxxx/local.properties 文件。

```
sdk.dir=/Users/jim/Library/Android/sdk/
ndk.dir=/Users/jim/Library/Android/sdk/ndk-bundle/
```

* 2. 修改 cmake 的版本号

如果 cmake 的版本与系统安装的不匹配，可以直接修改 build/xxxxxx/app/src/main/cpp/CMakeLists.txt 和 build/xxxxxx/app/build.gradle

* 3. 修改 gradle 的版本号

如果 gradle 的版本与系统安装的不匹配，可以直接修改 build/xxxxxx/build.gradle

* 4. 如果出现 Failed to install the following Android SDK packages as some licences have not been accepted

> 进入 SDK/tools/bin，执行。\sdkmanager.bat "platforms;android-28"

* 5. 使用国内镜像

> 请在网上搜索相关资料。

* 6. 设计时的分辨率

手机 APP 设计时可以采用 480x853，同时采用 layout 参数进行自适应布局。

* 7. 图标大小

手机 APP 需要提供不同屏幕密度的图标，请参考 [LCD 密度与图片的对应关系](https://github.com/zlgopen/awtk/blob/master/demos/assets/default/raw/images/README.md)
