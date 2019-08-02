import os
import sys
import glob
import json
import shutil


def join_path(root, subdir):
    return os.path.abspath(os.path.normpath(os.path.join(root, subdir)))


def mkdir_if_not_exist(fullpath):
    if os.path.exists(fullpath):
        print(fullpath+' exist.')
    else:
        os.makedirs(fullpath)


def file_read(name):
    with open(name) as infile:
        return infile.read()


def file_write(name, content):
    with open(name, 'w') as outfile:
        outfile.write(content)


def file_replace(name, sfrom, sto):
    content = file_read(name)
    new_content = content.replace(sfrom, sto)
    file_write(name, new_content)


def copy_folder(src, dst):
    print(src + '=>' + dst)
    if os.path.exists(dst):
        shutil.rmtree(dst)
    shutil.copytree(src, dst)


def copy_file(src, dst):
    print(src + '=>' + dst)
    with open(dst, 'w') as outfile:
        with open(src) as infile:
            outfile.write(infile.read())
            outfile.write('\n')



AWTK_ANDROID_DIR = join_path('./', '../')
AWTK_DIR = join_path(AWTK_ANDROID_DIR, '../awtk')
BUILD_DIR = join_path(AWTK_ANDROID_DIR, 'build')
TEMPLATE_DIR = join_path(AWTK_ANDROID_DIR, 'android-project')

print('AWTK_DIR:' + AWTK_DIR)
print('AWTK_ANDROID_DIR:' + AWTK_ANDROID_DIR)


filename = ''


def show_usage():
    print('Usage: python create_proj.py app.json')
    sys.exit(0)


if len(sys.argv) < 2:
    show_usage()
else:
    filename = os.path.abspath(sys.argv[1])

def rename_files_content(app_root_dst, app_full_name, app_name):
    files = ['AwtkTemplate.iml',
             'app/build.gradle',
             'app/src/main/AndroidManifest.xml',
             'app/src/main/res/values/strings.xml',
             'app/src/main/java/org/zlgopen/awtktemplate/MainActivity.java',
             ]

    for f in files:
        filename = join_path(app_root_dst, f)
        print('process ' + filename)
        file_replace(filename, 'org.zlgopen.awtktemplate', app_full_name)
        file_replace(filename, 'awtktemplate', app_name)
        file_replace(filename, 'AwtkTemplate', app_name)


def rename_item(src, dst):
    if src != dst:
        os.rename(src, dst)
        print(src + ' => ' + dst)


def rename_folders_and_files(app_root_dst, app_full_name):
    items = app_full_name.split('.')
    src = join_path(app_root_dst, 'app/src/main/java/org/zlgopen/awtktemplate')
    dst = join_path(app_root_dst, 'app/src/main/java/org/zlgopen/' + items[2])
    rename_item(src, dst)

    src = join_path(app_root_dst, 'app/src/main/java/org/zlgopen')
    dst = join_path(app_root_dst, 'app/src/main/java/org/' + items[1])
    rename_item(src, dst)

    src = join_path(app_root_dst, 'app/src/main/java/org')
    dst = join_path(app_root_dst, 'app/src/main/java/' + items[0])
    rename_item(src, dst)

    src = join_path(app_root_dst, 'AwtkTemplate.iml')
    dst = join_path(app_root_dst, items[2] + '.iml')
    rename_item(src, dst)


def copy_awtk_files(app_root_dst):
    awtk_src = join_path(AWTK_DIR, 'src')
    awtk_src_to = join_path(app_root_dst, 'app/src/main/cpp/awtk/src')
    copy_folder(awtk_src, awtk_src_to)

    awtk_3rd = join_path(AWTK_DIR, '3rd')
    awtk_3rd_to = join_path(app_root_dst, 'app/src/main/cpp/awtk/3rd')
    copy_folder(awtk_3rd, awtk_3rd_to)


def copy_app_files(config, app_root_dst, app_root_src):
    assets_dir = config['assets'];
    sources = config_get_android_sources(config);

    for f in sources:
        sfrom = join_path(app_root_src, f)
        sto = join_path(join_path(app_root_dst, 'app/src/main/cpp/app'), f)
        print(sfrom + '=>' + sto)
        copy_file(sfrom, sto)

    sfrom =  join_path(app_root_src, assets_dir + '/raw');
    sto = join_path(app_root_dst, 'app/src/main/assets/assets/raw');
    copy_folder(sfrom, sto);

def config_get_app_full_name(config):
    return config['android']['app_name']


def config_get_app_name(config):
    app_full_name = config_get_app_full_name(config)
    items = app_full_name.split('.')
    return items[2]


def config_get_android_sources(config):
    return config['android']['sources']


def check_config(config):
    app_full_name = config_get_app_full_name(config)
    items = app_full_name.split('.')

    if len(items) != 3:
        print('invalid app name')
        sys.exit(0)

    if len(config_get_android_sources(config)) < 1:
        print('no sources')
        sys.exit(0)

    return config


def create_project(config, app_root_src):
    app_name = config_get_app_name(config)
    app_full_name = config_get_app_full_name(config)
    app_root_dst = join_path(BUILD_DIR, app_name)

    copy_folder(TEMPLATE_DIR, app_root_dst)
    rename_files_content(app_root_dst, app_full_name, app_name)
    rename_folders_and_files(app_root_dst, app_full_name)

    copy_awtk_files(app_root_dst)
    copy_app_files(config, app_root_dst, app_root_src)


with open(filename, 'r') as load_f:
    create_project(check_config(json.load(load_f)), os.path.dirname(filename))
