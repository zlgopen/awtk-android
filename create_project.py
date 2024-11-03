import os
import sys
import json

AWTK_ROOT = os.path.normpath(os.path.abspath(os.path.join(os.getcwd(), "../awtk")))
sys.path.append(os.path.join(AWTK_ROOT, "scripts"))

import mobile_project_helper as helper

ANDROID_HOME = os.environ.get('ANDROID_HOME')
ANDROID_NDK_HOME = os.environ.get('ANDROID_NDK_HOME')
WORK_DIR = os.path.abspath(os.path.normpath(os.getcwd()))
BUILD_DIR = helper.join_path(WORK_DIR, 'build')
TEMPLATE_DIR = helper.join_path(WORK_DIR, 'android-project')
PLUGINS_DIR = helper.join_path(os.getcwd(), '../awtk-mobile-plugins')

if ANDROID_HOME == None or ANDROID_NDK_HOME == None:
    print('ANDROID_HOME or ANDROID_NDK_HOME is not set!')
    sys.exit(0)

print('WORK_DIR:' + WORK_DIR)

def is_fullscreen(config):
    if 'features' in config and 'fullscreen' in config['features']:
        return True
    return False
    
def apply_features(config, app_root_dst):
    if is_fullscreen(config):
        activityPreferTheme = 'android:theme="@android:style/Theme.NoTitleBar.Fullscreen"'
        appPreferTheme = 'android:theme="@android:style/Theme.NoTitleBar"'
        filename = helper.join_path(app_root_dst, 'app/src/main/java/org/libsdl/app/SDLActivity.java')
        helper.file_replace(filename, '//setWindowStyle(false);', "setWindowStyle(true);");
    else:
        activityPreferTheme = 'android:theme="@style/AppTheme"'
        appPreferTheme = ''

    filename = helper.join_path(app_root_dst, 'app/src/main/AndroidManifest.xml')
    helper.file_replace(filename, 'APP_PREFER_THEME', appPreferTheme);
    helper.file_replace(filename, 'ACTIVITY_PREFER_THEME', activityPreferTheme);

def apply_plugins_config(config, app_root_dst):
    nameClassPairs = []
    activities = []
    permissions = []
    dependencies = []

    plugins = helper.config_get_plugins(config)

    for p in plugins:
        plugin_json = helper.join_path(PLUGINS_DIR, 'src/' + p + '/plugin.json');

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

    filename = helper.join_path(app_root_dst, 'app/build.gradle')
    helper.file_replace(filename, 'EXTRA_DEPENDENCIES', dependencies);
    
    filename = helper.join_path(app_root_dst, 'app/src/main/AndroidManifest.xml')
    helper.file_replace(filename, 'EXTRA_ACTIVITIES', activities);
    helper.file_replace(filename, 'EXTRA_PERMISSION', permissions);

    imports = ''
    registers = ''
    
    for iter in nameClassPairs:
        name,className = iter
        registers += 'PluginManager.register(\"'
        registers += name.lower()+'\", new '+className+'(PluginManager.activity, id++));\n';

    filename = helper.join_path(app_root_dst, 'app/src/main/java/org/zlgopen/plugins/common/PluginManager.java')
    helper.file_replace(filename, 'EXTRA_IMPORTS', imports);
    helper.file_replace(filename, 'EXTRA_REGISTERS', registers);

def copy_plugins(config, app_root_dst):
    plugins = helper.config_get_plugins(config)
   
    sfrom = helper.join_path(PLUGINS_DIR, "src/common/*.*");
    sfrom_dir = helper.join_path(PLUGINS_DIR, "src");
    sto = helper.join_path(app_root_dst, "app/src/main/cpp/plugins");
    helper.copy_glob_files(sfrom, sfrom_dir, sto);
    
    sfrom = helper.join_path(PLUGINS_DIR, "src/common/android/java");
    sto = helper.join_path(app_root_dst, "app/src/main/java");
    helper.copy_folder_overwrite(sfrom, sto);
   
    for p in plugins:
        sfrom = helper.join_path(PLUGINS_DIR, "src/"+p+"/*.*");
        sfrom_dir = helper.join_path(PLUGINS_DIR, "src");
        sto = helper.join_path(app_root_dst, "app/src/main/cpp/plugins");
        helper.copy_glob_files(sfrom, sfrom_dir, sto);
    
        sfrom = helper.join_path(PLUGINS_DIR, "src/"+p+"/android/java");
        sto = helper.join_path(app_root_dst, "app/src/main/java");
        helper.copy_folder_overwrite(sfrom, sto);

        sfrom = helper.join_path(PLUGINS_DIR, "src/"+p+"/android/aidl");
        sto = helper.join_path(app_root_dst, "app/src/main/aidl");
        if os.path.exists(sfrom):
          helper.copy_folder_overwrite(sfrom, sto);


def replace_files_content(app_root_dst, config):
    files = [
        'app/build.gradle',
        'app/src/main/AndroidManifest.xml',
        'app/src/main/res/values/strings.xml',
        'app/src/main/java/org/zlgopen/awtktemplate/MainActivity.java',
    ]
    helper.files_replace_with_config(files, app_root_dst, config)


def rename_folders_and_files(app_root_dst, app_full_name):
    items = app_full_name.split('.')
    src = helper.join_path(app_root_dst, 'app/src/main/java/org/zlgopen/awtktemplate')
    dst = helper.join_path(app_root_dst, 'app/src/main/java/org/zlgopen/' + items[2])
    helper.file_rename(src, dst)

    src = helper.join_path(app_root_dst, 'app/src/main/java/org/zlgopen')
    dst = helper.join_path(app_root_dst, 'app/src/main/java/org/' + items[1])
    helper.file_rename(src, dst)

    src = helper.join_path(app_root_dst, 'app/src/main/java/org')
    dst = helper.join_path(app_root_dst, 'app/src/main/java/' + items[0])
    helper.file_rename(src, dst)


def update_local_props(app_root_dst):
    filename = helper.join_path(app_root_dst, 'local.properties')
    content = 'sdk.dir=' + ANDROID_HOME + '\n'
    content += 'ndk.dir=' + ANDROID_NDK_HOME + '\n'
    helper.file_write(filename, content)


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
    app_name = helper.config_get_app_name(config)
    app_full_name = helper.config_get_app_full_name(config)
    app_root_dst = helper.join_path(BUILD_DIR, app_name)

    helper.copy_folder(TEMPLATE_DIR, app_root_dst)
    replace_files_content(app_root_dst, config)
    rename_folders_and_files(app_root_dst, app_full_name)
    update_local_props(app_root_dst)
    helper.copy_awtk_files(helper.join_path(app_root_dst, 'app/src/main/cpp/awtk'))
    helper.copy_app_sources(config, helper.join_path(
        app_root_dst, 'app/src/main/cpp/app'), app_root_src)
    helper.copy_app_assets(config, helper.join_path(
        app_root_dst, 'app/src/main/assets/assets'), app_root_src)
    helper.update_cmake_file(config, helper.join_path(
        app_root_dst, "app/src/main/cpp/CMakeLists.txt"))

    copy_plugins(config, app_root_dst);
    apply_features(config, app_root_dst);
    apply_plugins_config(config, app_root_dst);

    show_result(app_name)

app_json = ''
if len(sys.argv) < 2:
    helper.show_usage()
else:
    app_json = os.path.abspath(sys.argv[1])

config = helper.load_config(app_json, 'android')
create_project(config, os.path.dirname(app_json))
