import os
import sys
import glob
import json
import shutil

from utils import (join_path, show_usage, mkdir_if_not_exist, file_read, file_write, file_replace,
                   copy_file, copy_folder, copy_glob_files, file_rename, files_replace,
                   copy_awtk_files, copy_app_sources, copy_app_assets, set_cmake_includes,
                   config_get_app_full_name, config_get_app_name, config_get_sources,
                   config_get_includes, merge_and_check_config
                   )


ANDROID_HOME = os.environ.get('ANDROID_HOME')
ANDROID_NDK_HOME = os.environ.get('ANDROID_NDK_HOME')
AWTK_ANDROID_DIR = os.path.abspath(os.path.normpath(os.getcwd()))
BUILD_DIR = join_path(AWTK_ANDROID_DIR, 'build')
TEMPLATE_DIR = join_path(AWTK_ANDROID_DIR, 'android-project')

if ANDROID_HOME == None or ANDROID_NDK_HOME == None:
    print('ANDROID_HOME or ANDROID_NDK_HOME is not set!')
    sys.exit(0)

print('AWTK_ANDROID_DIR:' + AWTK_ANDROID_DIR)


def rename_files_content(app_root_dst, app_full_name, app_name):
    files = [
        'app/build.gradle',
        'app/src/main/AndroidManifest.xml',
        'app/src/main/res/values/strings.xml',
        'app/src/main/java/org/zlgopen/awtktemplate/MainActivity.java',
    ]
    files_replace(files, app_root_dst, app_full_name, app_name)


def rename_folders_and_files(app_root_dst, app_full_name):
    items = app_full_name.split('.')
    src = join_path(app_root_dst, 'app/src/main/java/org/zlgopen/awtktemplate')
    dst = join_path(app_root_dst, 'app/src/main/java/org/zlgopen/' + items[2])
    file_rename(src, dst)

    src = join_path(app_root_dst, 'app/src/main/java/org/zlgopen')
    dst = join_path(app_root_dst, 'app/src/main/java/org/' + items[1])
    file_rename(src, dst)

    src = join_path(app_root_dst, 'app/src/main/java/org')
    dst = join_path(app_root_dst, 'app/src/main/java/' + items[0])
    file_rename(src, dst)


def update_local_props(app_root_dst):
    filename = join_path(app_root_dst, 'local.properties')
    content = 'sdk.dir=' + ANDROID_HOME + '\n'
    content += 'ndk.dir=' + ANDROID_NDK_HOME + '\n'
    file_write(filename, content)


def show_result(app_name):
    print("====================================================")
    print("project is created at: build/" + app_name)
    print("to build: ")
    print(" bash: ")
    print("  cd build/" + app_name + " && ./gradlew build")
    print(" cmd: ")
    print("  cd build/" + app_name + " && gradlew build")
    print("====================================================")


def create_project(config, app_root_src):
    app_name = config_get_app_name(config)
    app_full_name = config_get_app_full_name(config)
    app_root_dst = join_path(BUILD_DIR, app_name)

    copy_folder(TEMPLATE_DIR, app_root_dst)
    rename_files_content(app_root_dst, app_full_name, app_name)
    rename_folders_and_files(app_root_dst, app_full_name)

    update_local_props(app_root_dst)
    copy_awtk_files(join_path(app_root_dst, 'app/src/main/cpp/awtk'))
    copy_app_sources(config, join_path(
        app_root_dst, 'app/src/main/cpp/app'), app_root_src)
    copy_app_assets(config, join_path(
        app_root_dst, 'app/src/main/assets/assets/default/raw'), app_root_src)
    set_cmake_includes(config, join_path(
        app_root_dst, "app/src/main/cpp/CMakeLists.txt"))

    show_result(app_name)


app_json = ''
if len(sys.argv) < 2:
    show_usage()
else:
    app_json = os.path.abspath(sys.argv[1])

with open(app_json, 'r') as load_f:
    config = merge_and_check_config(json.load(load_f), 'android')
    create_project(config, os.path.dirname(app_json))
