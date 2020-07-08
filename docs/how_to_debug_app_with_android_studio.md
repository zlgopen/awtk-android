# 如何用 android studio 调试 awtk android app

用 create_project.py 生成 android app 的工程之后，可以直接在命令行下编译和安装 apk。如果 app 遇到运行时问题，则需要借助 android studio 了。

## 用 android studio 导入 awtk app

* 运行 android studio，在启动界面选择"Import project(Gradle,Eclipse ADT,etc)

![](images/android_studio_start.png)

* 选择前面生成的 awtk app 的目录（如 demoui)。

![](images/android_studion_import.png)

* 导入之后 android studio 自动开始编译，通常需要比较久的时间，请耐心等待。

![](images/android_studio_build.png)

## 调试

调试方法请参考 android studio 的资料。
	
