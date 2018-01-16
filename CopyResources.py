import os.path
import shutil

RESOURCE_DIRECTORIES = [
    {
        "src": "GPUPro-6/src/Engine/Shaders",
        "dst": "Shaders"
    },
    {
        "src": "Game/src/Resources",
        "dst": ""
    }
]

RESOURCE_BASE_DIR = "Resources"

def copy_resources(solution_dir, build_path):
    for resource_dir in RESOURCE_DIRECTORIES:
        src_dir = os.path.join(solution_dir, resource_dir["src"])
        dst_dir = os.path.join(os.path.join(build_path, RESOURCE_BASE_DIR), resource_dir["dst"])
        if os.path.exists(dst_dir):
            shutil.rmtree(dst_dir)
        shutil.copytree(src_dir, dst_dir)
