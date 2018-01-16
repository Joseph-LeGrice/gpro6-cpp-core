import argparse
import CopyDLLs
import CopyResources

def main():
    arg_parser = argparse.ArgumentParser(description="Post Build Script for GPUPro")
    arg_parser.add_argument("-a", "--architecture", choices=["x64", "x86"], help="Should be either x86 or x64", default="x64")
    arg_parser.add_argument("solution_directory", help="The root directory of the solution")
    arg_parser.add_argument("build_directory", help="The build output directory")
    args_parsed = arg_parser.parse_args()
    print('Solution Directory: '+args_parsed.solution_directory)
    print('Build Directory: '+args_parsed.build_directory)
    CopyDLLs.copy_dlls(args_parsed.solution_directory, args_parsed.build_directory, args_parsed.architecture)
    CopyResources.copy_resources(args_parsed.solution_directory, args_parsed.build_directory)

if __name__ == '__main__':
    main()
