import * as argparse from 'argparse'
import * as fs from 'fs-extra'
import { Config } from './data/config-files'
import { CopyDLLs } from './copy-dlls'
import { CopyResources } from './copy-resources'
import { BuildMonoProject } from './build-mono'

const argParser = new argparse.ArgumentParser({
    "description": "Post Build Script for GPUPro"
});

argParser.addArgument(["-a", "--architecture"], {
    choices: ["x64", "x86"],
    defaultValue: "x64",
    help: "Should be either x86 or x64"
});

argParser.addArgument(["--build-directory"], {
    required: true,
    type: 'string',
    help: "The build output directory"
});

argParser.addArgument(["--config-file"], {
    required: true,
    type: 'string',
    help: "The Configuration File"
});

const args = argParser.parseArgs();

const rootDirectory: string = args.config_file.substring(0, args.config_file.lastIndexOf("/"));
const jsonText = fs.readFileSync(args.config_file, { encoding: 'utf8' });
const configuration = <Config>JSON.parse(jsonText);

if (configuration.dlls) {
    console.log(`Copying DLL's...`);
    for (const dll of configuration.dlls) {
        CopyDLLs(dll, rootDirectory, args.build_directory, args.architecture);
    }
}

if (configuration.resources) {
    console.log(`Copying Resources...`);
    for (const resource of configuration.resources) {
        CopyResources(resource, rootDirectory, args.build_directory);
    }
}

if (configuration.monoProjects) {
    console.log(`Building Mono Projects...`);
    for (const monoProject of configuration.monoProjects) {
        BuildMonoProject(monoProject, rootDirectory, args.build_directory);
    }
}

console.log('Done!');
