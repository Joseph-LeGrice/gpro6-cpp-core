"use strict";
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];
    result["default"] = mod;
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
const argparse = __importStar(require("argparse"));
const copy_dlls_1 = require("./copy-dlls");
const copy_resources_1 = require("./copy-resources");
const build_mono_1 = require("./build-mono");
const argParser = new argparse.ArgumentParser({
    "description": "Post Build Script for GPUPro"
});
argParser.addArgument(["-a", "--architecture"], {
    "choices": ["x64", "x86"],
    "help": "Should be either x86 or x64",
    "defaultValue": "x64"
});
argParser.addArgument(["--copy-dlls"], {
    "action": "storeTrue",
    "help": "Copy DLL's"
});
argParser.addArgument(["--package-resources"], {
    "action": "storeTrue",
    "help": "Package Resource Files"
});
argParser.addArgument(["--build-mono-project"], {
    "action": "storeTrue",
    "help": "Package Resource Files"
});
argParser.addArgument(["--solution-directory"], {
    "required": true,
    "help": "The root directory of the solution"
});
argParser.addArgument(["--build-directory"], {
    "help": "The build output directory"
});
argParser.addArgument(["--mono-project-directory"], {
    "help": "The Mono Project Directory"
});
const args = argParser.parseArgs();
console.log('Solution Directory: ' + args.solution_directory);
console.log('Build Directory: ' + args.build_directory);
if (args.copy_dlls) {
    console.log(`Copying DLL's...`);
    if (args.build_directory) {
        copy_dlls_1.CopyDLLs(args.solution_directory, args.build_directory, args.architecture);
    }
    else {
        console.log(`ERROR! Missing build_directory`);
    }
}
if (args.package_resources) {
    console.log(`Copying Resource's...`);
    if (args.build_directory) {
        copy_resources_1.CopyResources(args.solution_directory, args.build_directory);
    }
    else {
        console.log(`ERROR! Missing build_directory`);
    }
}
if (args.build_mono_project) {
    console.log(`Copying Resource's...`);
    if (args.mono_project_directory) {
        build_mono_1.BuildMonoProject(args.solution_directory, args.mono_project_directory);
    }
    else {
        console.log(`ERROR! Missing mono_project_directory`);
    }
}
console.log('Done!');
//# sourceMappingURL=main.js.map