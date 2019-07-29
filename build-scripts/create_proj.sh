#!/bin/bash

SOURCES=()
MKSOURCES=""
CURDIR=`pwd -P`

# Fetch sources
if [[ $# -ge 2 ]]; then
    for src in ${@:2}
    do
        SOURCES+=($src)
        MKSOURCES="$MKSOURCES $(basename $src)"
    done
else
    if [ -n "$1" ]; then
        while read src
        do
            SOURCES+=($src)
            MKSOURCES="$MKSOURCES $(basename $src)"
        done
    fi
fi

if [ -z "$1" ] || [ -z "$SOURCES" ]; then
    echo "Usage: androidbuild.sh com.yourcompany.yourapp < sources.list"
    echo "Usage: androidbuild.sh com.yourcompany.yourapp source1.c source2.c ...sourceN.c"
    echo "To copy SDL source instead of symlinking: COPYSOURCE=1 androidbuild.sh ... "
    exit 1
fi

AWTK_PATH="$( cd "$(dirname "$0")/../../awtk/" ; pwd -P )"
AWTK_ANDROID_PATH="$( cd "$(dirname "$0")/.." ; pwd -P )"

if [ -z "$ANDROID_HOME" ];then
    echo "Please set the ANDROID_HOME directory to the path of the Android SDK"
    exit 1
fi

if [ ! -d "$ANDROID_HOME/ndk-bundle" -a -z "$ANDROID_NDK_HOME" ]; then
    echo "Please set the ANDROID_NDK_HOME directory to the path of the Android NDK"
    exit 1
fi

APP="$1"
APPARR=(${APP//./ })
BUILDPATH="$AWTK_ANDROID_PATH/build/$APP"

# Start Building

rm -rf $BUILDPATH
mkdir -p $BUILDPATH

cp -rvf $AWTK_ANDROID_PATH/android-project/* $BUILDPATH

# Copy SDL sources
mkdir -p $BUILDPATH/app/jni/awtk
ln -s $AWTK_PATH/src $BUILDPATH/app/jni/awtk/src
ln -s $AWTK_PATH/3rd $BUILDPATH/app/jni/awtk/3rd

cp -r $AWTK_ANDROID_PATH/Android.mk $BUILDPATH/app/jni/awtk
sed -i -e "s|YourSourceHere.c|$MKSOURCES|g" $BUILDPATH/app/jni/src/Android.mk
sed -i -e "s|org\.libsdl\.app|$APP|g" $BUILDPATH/app/build.gradle
sed -i -e "s|org\.libsdl\.app|$APP|g" $BUILDPATH/app/src/main/AndroidManifest.xml

# Copy user sources
for src in "${SOURCES[@]}"
do
    cp $src $BUILDPATH/app/jni/src
done

# Create an inherited Activity
cd $BUILDPATH/app/src/main/java
for folder in "${APPARR[@]}"
do
    mkdir -p $folder
    cd $folder
done

ACTIVITY="${folder}Activity"
sed -i -e "s|\"SDLActivity\"|\"$ACTIVITY\"|g" $BUILDPATH/app/src/main/AndroidManifest.xml

# Fill in a default Activity
cat >"$ACTIVITY.java" <<__EOF__
package $APP;

import org.libsdl.app.SDLActivity;

public class $ACTIVITY extends SDLActivity
{
}
__EOF__

# Update project and build
echo "To build and install to a device for testing, run the following:"
echo "cd $BUILDPATH"
echo "./gradlew installDebug"
