import os.path
import shutil

DLLS = [
    {
        "x86": "lib/FreeImage/x86/FreeImage.dll",
        "x64": "lib/FreeImage/x64/FreeImage.dll"
    }
]

def copy_dlls(solution_dir, build_path, arch):
    for dll_path in DLLS:
        src_path = os.path.join(solution_dir, dll_path[arch])
        shutil.copy(src_path, build_path)
