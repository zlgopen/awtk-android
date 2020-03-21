import os
import sys
import glob
import json
import shutil

from utils import (join_path, show_usage, mkdir_if_not_exist, file_read, file_write, file_replace,
                   copy_file, copy_folder, copy_glob_files, file_rename, files_replace,
                   copy_awtk_files, copy_app_sources, copy_app_assets, update_cmake_file,
                   config_get_app_full_name, config_get_app_name, config_get_sources,
                   config_get_includes, merge_and_check_config, config_get_plugins,
                   copy_folder_overwrite
                   )


ANDROID_HOME = os.environ.get('ANDROID_HOME')
ANDROID_NDK_HOME = os.environ.get('ANDROID_NDK_HOME')
AWTK_ANDROID_DIR = os.path.abspath(os.path.normpath(os.getcwd()))
BUILD_DIR = join_path(AWTK_ANDROID_DIR, 'build')
TEMPLATE_DIR = join_path(AWTK_ANDROID_DIR, 'android-project')
PLUGINS_DIR = join_path(os.getcwd(), '../awtk-mobile-plugins')

if ANDROID_HOME == None or ANDROID_NDK_HOME == None:
    print('ANDROID_HOME or ANDROID_NDK_HOME is not set!')
    sys.exit(0)

print('AWTK_ANDROID_DIR:' + AWTK_ANDROID_DIR)

def apply_plugins_config(config, app_root_dst):
    nameClassPairs = []
    activities = []
    permissions = []
    dependencies = []

    plugins = config_get_plugins(config)
    
    for p in plugins:
        plugin_json = join_path(PLUGINS_DIR, 'src/' + p + '/plugin.json');

        with open(plugin_json, 'r') as f:
            plugin_config = json.load(f);
            name = plugin_config['name'];

            if 'android' in plugin_config:
                android_config = plugin_config['android'];
                if 'class' in android_config:
                    className = android_config['class']
                    nameClassPairs.append((name, className))
                if 'permissions' in android_config:
                    permissions += android_config['permissions']
                if 'activities' in android_config:
                    activities += android_config['activities']
                if 'dependencies' in android_config:
                    dependencies += android_config['dependencies']
                    

    activities = sorted(set(activities))
    permissions = sorted(set(permissions))
    dependencies = sorted(set(dependencies))

    activities = '\n    '.join(activities);
    permissions = '\n    '.join(permissions);
    dependencies = '\n    '.join(dependencies);

    filename = join_path(app_root_dst, 'app/build.gradle')
    file_replace(filename, 'EXTRA_DEPENDENCIES', dependencies);
    
    filename = join_path(app_root_dst, 'app/src/main/AndroidManifest.xml')
    file_replace(filename, 'EXTRA_ACTIVITIES', activities);
    file_replace(filename, 'EXTRA_PERMISSION', permissions);


    imports = ''
    registers = ''
    
    for iter in nameClassPairs:
        name,className = iter
        registers += 'PluginManager.register(\"'
        registers += name.lower()+'\", new '+className+'(PluginManager.activity, id++));\n';

    filename = join_path(app_root_dst, 'app/src/main/java/org/zlgopen/plugins/common/PluginManager.java')
    file_replace(filename, 'EXTRA_IMPORTS', imports);
    file_replace(filename, 'EXTRA_REGISTERS', registers);

def copy_plugins(config, app_root_dst):
    plugins = config_get_plugins(config)
    if len(plugins) == 0:
        return;
   
    sfrom = join_path(PLUGINS_DIR, "src/common/*.*");
    sfrom_dir = join_path(PLUGINS_DIR, "src");
    sto = join_path(app_root_dst, "app/src/main/cpp/plugins");
    copy_glob_files(sfrom, sfrom_dir, sto);
    
    sfrom = join_path(PLUGINS_DIR, "src/common/android/java");
    sto = join_path(app_root_dst, "app/src/main/java");
    copy_folder_overwrite(sfrom, sto);
   
    for p in plugins:
        sfrom = join_path(PLUGINS_DIR, "src/"+p+"/*.*");
        sfrom_dir = join_path(PLUGINS_DIR, "src");
        sto = join_path(app_root_dst, "app/src/main/cpp/plugins");
        copy_glob_files(sfrom, sfrom_dir, sto);
    
        sfrom = join_path(PLUGINS_DIR, "src/"+p+"/android/java");
        sto = join_path(app_root_dst, "app/src/main/java");
        copy_folder_overwrite(sfrom, sto);

   

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
    update_cmake_file(config, join_path(
        app_root_dst, "app/src/main/cpp/CMakeLists.txt"))

    copy_plugins(config, app_root_dst);
    apply_plugins_config(config, app_root_dst);

    show_result(app_name)

app_json = ''
if len(sys.argv) < 2:
    show_usage()
else:
    app_json = os.path.abspath(sys.argv[1])

with open(app_json, 'r') as load_f:
    config = merge_and_check_config(json.load(load_f), 'android')
    create_project(config, os.path.dirname(app_json))
