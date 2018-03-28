import * as path from 'path'
import * as fs from 'fs-extra'

class ResourceConfig { "src" : string; "dst" : string; };

const RESOURCE_DIRECTORIES : ResourceConfig[] = [
    {
        "src": `GPUPro-6/src/Engine/Shaders`,
        "dst": "Shaders"
    },
    {
        "src": `GPUPro-6/src/Resources`,
        "dst": "GameResources"
    }
]

const RESOURCE_BASE_DIR = "Resources"

export function CopyResources(solutionDir: string, buildPath: string): void {
    const rootResourceDir = path.join(buildPath, RESOURCE_BASE_DIR);

    if (fs.existsSync(rootResourceDir)) {
        fs.removeSync(rootResourceDir);
        for (const resourceDir of RESOURCE_DIRECTORIES) {
            const srcDir = path.join(solutionDir, resourceDir["src"])
            const dstDir = path.join(rootResourceDir, resourceDir["dst"])
            fs.copySync(srcDir, dstDir);
        }
    }
}
