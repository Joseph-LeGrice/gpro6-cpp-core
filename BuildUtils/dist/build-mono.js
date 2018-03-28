"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : new P(function (resolve) { resolve(result.value); }).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];
    result["default"] = mod;
    return result;
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const path = __importStar(require("path"));
const execa_1 = __importDefault(require("execa"));
const MONO_COMPILER = `C:/Program Files/Mono/bin/mcs`;
const MONO_LIB_PATH = `C:/Program Files/Mono/lib`;
const MONO_OPTIONS = ["-target:library"];
const MONO_AOT_ASSEMBLY_OUTPUT_PATH = `MonoScripts/MonoScripts.dll`;
const MONO_FILES = [
    "ISystem.cs",
    "TestScript.cs"
];
const MONO_LIBS = [];
function BuildMonoProject(solutionDirectory, monoProjectDirectory) {
    return __awaiter(this, void 0, void 0, function* () {
        console.log(`Building Mono Project: ${monoProjectDirectory}`);
        const args = [];
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
        yield execa_1.default(MONO_COMPILER, args, { stdio: 'inherit' });
    });
}
exports.BuildMonoProject = BuildMonoProject;
//# sourceMappingURL=build-mono.js.map