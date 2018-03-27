import os
import os.path
import subprocess

MONO_COMPILER = "\"C:\\Program Files\\Mono\\bin\\mcs\""
MONO_LIB_PATH = os.path.join("C:\\", "Program Files", "Mono", "lib")

MONO_OPTIONS = ["-target:library"]

MONO_PROJECT_PATH = "MonoScripts"
MONO_AOT_ASSEMBLY_OUTPUT_PATH = os.path.join("MonoScripts", "MonoScripts.dll")

MONO_FILES = [
    "MonoScript.cs",
    "TestScript.cs"
]

MONO_LIBS = []

def build_mono_project(solution_directory):
    args = ["cmd", MONO_COMPILER]
    for option in MONO_OPTIONS:
        args.append(option)
    for mono_script in MONO_FILES:
        mono_script_path = os.path.join(solution_directory, MONO_PROJECT_PATH, mono_script)
        args.append(mono_script_path)
    output_directory = "-out:"+os.path.join(solution_directory, MONO_AOT_ASSEMBLY_OUTPUT_PATH)
    args.append(output_directory)
    print('Running Command: ' + ' '.join(args))
    subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

if __name__ == '__main__':
    cwd = os.getcwd()
    mono_project = os.path.join(cwd, MONO_PROJECT_PATH)
    print('Building Mono Project: ' + mono_project)
    build_mono_project(cwd)
    input("Press Enter to terminate...")
