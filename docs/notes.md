# 安卓开发笔记

对于熟悉 android 开发的人来说，有些属于常识问题，对于偶尔弄一下 android 的人，却要花很多时间才能搞定。这里做个笔记供大家参考：

## 1. 使用外部项目的库

### 1.1 修改 settings.gradle，增加外部库的引用

如：

```
include ':openCV'
project(':openCV').projectDir = new File(settingsDir, '../../../awtk-lpr/openCV')

include ':ocr'
project(':ocr').projectDir = new File(settingsDir, '../../../awtk-lpr/ocr')
```

### 1.2 在 app/build.gradle 中加入依赖关系

如：

```
...
dependencies {
  implementation project(path: ':ocr')
}
...
```

### 2. 忽略编译警告

正常情况我们是不应该忽略警告的，但是有时使用第三方库，如果不忽略警告就没法编译。这时，可以修改 build.gradle，增加一下代码：

```
    lintOptions {
       abortOnError false        // true by default
       checkAllWarnings false
       checkReleaseBuilds false
       ignoreWarnings true       // false by default
       quiet true                // false by default
    }
```    

### 3. 指定cmake的编译参数


修改 build.gradle即可。如：

```
    externalNativeBuild {
      cmake {
        cppFlags "-std=c++11 -frtti  -fexceptions"
         abiFilters 'armeabi-v7a'
         arguments  '-DANDROID_STL=gnustl_static'
        }
    }
    ndk {
      abiFilters 'armeabi-v7a'
    }
```        