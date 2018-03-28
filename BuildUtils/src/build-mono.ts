import * as path from 'path'
import * as fs from 'fs-extra'
import execa from 'execa'

const MONO_COMPILER = `C:/Program Files/Mono/bin/mcs`;
const MONO_LIB_PATH = `C:/Program Files/Mono/lib`;

const MONO_OPTIONS = ["-target:library"];

const MONO_AOT_ASSEMBLY_OUTPUT_PATH = `MonoScripts/MonoScripts.dll`;

const MONO_FILES = [
    "ISystem.cs",
    "TestScript.cs"
];

const MONO_LIBS = [];

export async function BuildMonoProject(solutionDirectory: string, monoProjectDirectory: string) {
    console.log(`Building Mono Project: ${monoProjectDirectory}`);
    const args: string[] = [];
    
    for (const option of MONO_OPTIONS) {
        args.push(option);
    }

    // TODO: Find *.cs files under directory
    for (const monoScript of MONO_FILES) {
        const monoScriptPath = path.join(monoProjectDirectory, monoScript);
        args.push(monoScriptPath);
    }

    const outputDirectory = "-out:" + path.join(solutionDirectory, MONO_AOT_ASSEMBLY_OUTPUT_PATH);
    args.push(outputDirectory);
    
    await execa(MONO_COMPILER, args, { stdio: 'inherit' });
}
