import * as path from 'path'
import * as fs from 'fs-extra'
import execa from 'execa'
import { MonoBuildConfig } from './data/config-files';

const MONO_COMPILER = `C:/Program Files/Mono/bin/mcs`;
const MONO_LIB_PATH = `C:/Program Files/Mono/lib`;

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

export async function BuildMonoProject(monoProject: MonoBuildConfig, rootDirectory: string, buildDirectory: string) {
    console.log(`Building Mono Project: ${monoProject.relativeProjectDirectory}`);
    
    const args: string[] = [];
    args.push("-target:library");
    args.push(`-out:${path.join(buildDirectory, monoProject.relativeTargetDirectory)}`);

    const fullPath = path.join(rootDirectory, monoProject.relativeProjectDirectory);
    const allFiles: string[] = [];
    getFiles(fullPath, allFiles);
    for (const monoScriptPath of allFiles) {
        console.log(monoScriptPath);
        args.push(monoScriptPath);
    }
    
    const exec = execa(MONO_COMPILER, args);
    exec.stdout.on('data', data => console.log(data.toString()));
    exec.stderr.on('data', data => console.log(data.toString()));
    await exec;
}
