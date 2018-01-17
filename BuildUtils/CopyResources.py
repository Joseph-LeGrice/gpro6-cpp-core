import os.path
import shutil

RESOURCE_DIRECTORIES = [
    {
        "src": "GPUPro-6\\src\\Engine\\Shaders",
        "dst": "Shaders"
    },
    {
        "src": "Game\\src\\Resources",
        "dst": "GameResources"
    }
]

RESOURCE_BASE_DIR = "Resources"

def copy_resources(solution_dir, build_path):
    root_resource_dir = os.path.join(build_path, RESOURCE_BASE_DIR)
    if os.path.exists(root_resource_dir):
        shutil.rmtree(root_resource_dir)
    for resource_dir in RESOURCE_DIRECTORIES:
        src_dir = os.path.join(solution_dir, resource_dir["src"])
        dst_dir = os.path.join(root_resource_dir, resource_dir["dst"])
        shutil.copytree(src_dir, dst_dir)
