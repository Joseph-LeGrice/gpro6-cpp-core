import * as path from 'path'
import * as fs from 'fs-extra'
import execa from 'execa'

const MONO_COMPILER = `C:/Program Files/Mono/bin/mcs`;
const MONO_LIB_PATH = `C:/Program Files/Mono/lib`;

const MONO_AOT_ASSEMBLY_OUTPUT_PATH = `MonoScripts/MonoScripts.dll`;

const EXCLUDED_DIRECTORIES = [
    "obj",
    "bin"
];

function getFiles(directory: string, results: string[]) : void {
    fs.readdirSync(directory).forEach((f, index, array) => {
        const fullPath = path.join(directory, f);
        if (fs.statSync(fullPath).isDirectory()
            && EXCLUDED_DIRECTORIES.findIndex((v, i ,o) => { return  v === f; }) !== -1) {
            getFiles(fullPath, results);
        } else {
            const extension = fullPath.substring(fullPath.lastIndexOf('.'));
            if (extension === '.cs') {
                results.push(fullPath);
            }
        }
    });
}

export async function BuildMonoProject(solutionDirectory: string, monoProjectDirectory: string) {
    console.log(`Building Mono Project: ${monoProjectDirectory}`);
    
    const args: string[] = [];
    args.push("-target:library");

    const allFiles: string[] = [];
    getFiles(monoProjectDirectory, allFiles);
    for (const monoScriptPath of allFiles) {
        console.log(monoScriptPath);
        args.push(monoScriptPath);
    }

    const outputDirectory = "-out:" + path.join(solutionDirectory, MONO_AOT_ASSEMBLY_OUTPUT_PATH);
    args.push(outputDirectory);
    
    await execa(MONO_COMPILER, args, { stdio: 'inherit' });
}
