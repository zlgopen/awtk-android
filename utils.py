import os
import sys
import glob
import json
import shutil


def join_path(root, subdir):
    return os.path.abspath(os.path.normpath(os.path.join(root, subdir)))


AWTK_DIR = join_path(os.getcwd(), '../awtk')
print('AWTK_DIR:' + AWTK_DIR)


def show_usage():
    print('Usage: python create_proj.py app.json')
    sys.exit(0)


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
    mkdir_if_not_exist(os.path.dirname(dst))
    shutil.copy(src, dst)


def copy_glob_files(src, srcdir, dstdir):
    files = glob.glob(src)
    for f in files:
        dst = join_path(dstdir, f[len(srcdir)+1:])
        copy_file(f, dst)


def file_rename(src, dst):
    if src != dst:
        os.rename(src, dst)
        print(src + ' => ' + dst)


def files_replace(files, app_root_dst, app_full_name, app_name):
    for f in files:
        filename = join_path(app_root_dst, f)
        print('process ' + filename)
        file_replace(filename, 'org.zlgopen.awtktemplate', app_full_name)
        file_replace(filename, 'awtktemplate', app_name)
        file_replace(filename, 'AwtkTemplate', app_name)


def copy_awtk_files(app_root_dst):
    awtk_src = join_path(AWTK_DIR, 'src')
    awtk_src_to = join_path(app_root_dst, 'src')
    copy_folder(awtk_src, awtk_src_to)

    awtk_3rd = join_path(AWTK_DIR, '3rd')
    awtk_3rd_to = join_path(app_root_dst, '3rd')
    copy_folder(awtk_3rd, awtk_3rd_to)


def copy_app_sources(config, app_sources_dst, app_root_src):
    sources = config_get_sources(config)

    for f in sources:
        sfrom = join_path(app_root_src, f)
        if sfrom.find("*") >= 0:
            sto = app_sources_dst
            copy_glob_files(sfrom, app_root_src, sto)
        else:
            sto = join_path(app_sources_dst, f)
            copy_file(sfrom, sto)


def copy_app_assets(config, app_assets_dst, app_root_src):
    assets_dir = config['assets']
    sfrom = join_path(app_root_src, assets_dir + '/default/raw')
    copy_folder(sfrom, app_assets_dst)


def set_cmake_includes(config, filename):
    includes = config_get_includes(config)
    sincludes = '${APP_SOURCE_DIR}/src\n  ${APP_SOURCE_DIR}/3rd\n'
    for f in includes:
        sincludes += '  ${APP_SOURCE_DIR}/' + f + '\n'
    print('process ' + filename)
    file_replace(filename, 'EXTRA_INCLUDES', sincludes)


def config_get_app_full_name(config):
    return config['app_name']


def config_get_app_name(config):
    app_full_name = config_get_app_full_name(config)
    items = app_full_name.split('.')
    return items[2]


def config_get_sources(config):
    return config['sources']


def config_get_includes(config):
    if 'includes' in config:
        return config['includes']
    else:
        return []


def merge_and_check_config(config, platform):
    for key in config[platform]:
        config[key] = config[platform][key]

    app_full_name = config_get_app_full_name(config)
    items = app_full_name.split('.')

    if len(items) != 3:
        print('invalid app name')
        sys.exit(0)

    if len(config_get_sources(config)) < 1:
        print('no sources')
        sys.exit(0)

    return config
