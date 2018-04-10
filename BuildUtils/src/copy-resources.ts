import * as path from 'path'
import * as fs from 'fs-extra'
import { ResourceConfig } from './data/config-files';

export function CopyResource(resource: ResourceConfig, rootDirectory: string, buildPath: string): void {
    let srcPath = null;
    if (resource.absoluteSourceDirectory) {
        srcPath = resource.absoluteSourceDirectory;
    } else if (resource.relativeSourceDirectory) {
        srcPath = path.join(rootDirectory, resource.relativeSourceDirectory);
    }
    
    if (srcPath !== null) {
        const dstPath = path.join(buildPath, resource.relativeTargetDirectory);
        console.log(`Copying ${srcPath} -> ${dstPath}`);
        try {
            fs.copySync(srcPath, dstPath);
        } catch (e) {
            console.log(`An error occured: ${e}`);
        }
    }
}
