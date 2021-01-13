import os
from os import listdir
from os.path import isfile, join, getmtime
import shutil
import sys
from pathlib import Path

print("Starting post build script")

# Properties
target_dir = Path(sys.argv[1])

print("Target directory: " + target_dir.as_posix())

def create_new_or_updated_for_path(src_dir_path, end_dir_path):

    def file_new_or_updated(src, dest_files):
        src_path = join(src_dir_path, src)
        dest_path = join(end_dir_path, src)

        if src in dest_files and getmtime(src_path) > getmtime(join(end_dir_path, src)):
            return True
        elif src not in dest_files:
            return True
        return False

    return file_new_or_updated

def update_data(src_dir_path, end_dir_path):

    if not Path(end_dir_path).exists():
        os.mkdir(end_dir_path)

    src_dir_content = listdir(src_dir_path)
    end_dir_content = listdir(end_dir_path)

    predicate = create_new_or_updated_for_path(src_dir_path, end_dir_path)

    src_files = [f for f in src_dir_content if isfile(join(src_dir_path, f))]
    end_files = [f for f in end_dir_content if isfile(join(end_dir_path, f))]

    src_dirs = [f for f in src_dir_content if not isfile(join(src_dir_path, f))]
    end_dirs = [f for f in end_dir_content if not isfile(join(end_dir_path, f))]

    extra_files_in_end = [f for f in end_files if f not in src_files]
    extra_dirs_in_end = [f for f in end_dirs if f not in src_dirs]

    for extra_file in extra_files_in_end:
        os.remove(join(end_dir_path, extra_file))

    for extra_dir in extra_dirs_in_end:
        shutil.rmtree(join(end_dir_path, extra_dir), True)

    for file_for_update in [f for f in src_files if predicate(f, end_files)]:
        print("Updating file: " + join(src_dir_path, file_for_update))
        shutil.copyfile(join(src_dir_path, file_for_update), join(end_dir_path, file_for_update))

    for src_dir in src_dirs:
        if src_dir not in end_dirs:
            os.mkdir(join(end_dir_path, src_dir))

        update_data(join(src_dir_path, src_dir), join(end_dir_path, src_dir))

print("Copying data directory...")
update_data("./data", (target_dir / "data").as_posix())

print("Ending post build script")