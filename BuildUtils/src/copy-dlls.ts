import * as path from 'path'
import * as fs from 'fs-extra'
import { DllConfig } from './data/config-files';

export function CopyDLLs(dll: DllConfig, rootDirectory: string, buildPath: string, arch: string): void {
    const srcPath = path.join(rootDirectory, dll[arch].relativeSourceDirectory);
    const dstPath = path.join(buildPath, dll[arch].relativeTargetDirectory);
    fs.copySync(srcPath, dstPath, {
        "overwrite": true
    });
}
