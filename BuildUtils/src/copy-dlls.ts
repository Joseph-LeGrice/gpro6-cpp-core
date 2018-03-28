import * as path from 'path'
import * as fs from 'fs-extra'

class DllConfig { [arch: string] : { "src": string; "dst": string } };

const DLLS: DllConfig[] = [
    {
        "x86": { "src" : "lib/FreeImage/x86/FreeImage.dll", "dst" : "FreeImage.dll" },
        "x64": { "src" : "lib/FreeImage/x64/FreeImage.dll", "dst" : "FreeImage.dll" }
    }
]

export function CopyDLLs(solutionDir: string, buildPath: string, arch: string): void {
    for (const dllPath of DLLS) {
        const srcPath = path.join(solutionDir, dllPath[arch]["src"]);
        const dstPath = path.join(buildPath, dllPath[arch]["dst"]);
        fs.copySync(srcPath, dstPath, {
            "overwrite": true
        });
    }
}
