"use strict";
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];
    result["default"] = mod;
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
const path = __importStar(require("path"));
const fs = __importStar(require("fs-extra"));
class ResourceConfig {
}
;
const RESOURCE_DIRECTORIES = [
    {
        "src": `GPUPro-6/src/Engine/Shaders`,
        "dst": "Shaders"
    },
    {
        "src": `GPUPro-6/src/Resources`,
        "dst": "GameResources"
    }
];
const RESOURCE_BASE_DIR = "Resources";
function CopyResources(solutionDir, buildPath) {
    const rootResourceDir = path.join(buildPath, RESOURCE_BASE_DIR);
    if (fs.existsSync(rootResourceDir)) {
        fs.removeSync(rootResourceDir);
        for (const resourceDir of RESOURCE_DIRECTORIES) {
            const srcDir = path.join(solutionDir, resourceDir["src"]);
            const dstDir = path.join(rootResourceDir, resourceDir["dst"]);
            fs.copySync(srcDir, dstDir);
        }
    }
}
exports.CopyResources = CopyResources;
//# sourceMappingURL=copy-resources.js.map