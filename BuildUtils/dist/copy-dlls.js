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
class DllConfig {
}
;
const DLLS = [
    {
        "x86": { "src": "lib/FreeImage/x86/FreeImage.dll", "dst": "FreeImage.dll" },
        "x64": { "src": "lib/FreeImage/x64/FreeImage.dll", "dst": "FreeImage.dll" }
    }
];
function CopyDLLs(solutionDir, buildPath, arch) {
    for (const dllPath of DLLS) {
        const srcPath = path.join(solutionDir, dllPath[arch]["src"]);
        const dstPath = path.join(buildPath, dllPath[arch]["dst"]);
        fs.copySync(srcPath, dstPath, {
            "overwrite": true
        });
    }
}
exports.CopyDLLs = CopyDLLs;
//# sourceMappingURL=copy-dlls.js.map