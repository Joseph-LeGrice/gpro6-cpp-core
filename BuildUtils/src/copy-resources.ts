import * as path from 'path'
import * as fs from 'fs-extra'
import { ResourceConfig } from './data/config-files';

const RESOURCE_BASE_DIR = "Resources"

export function CopyResources(resource: ResourceConfig, rootDirectory: string, buildPath: string): void {
    const src = path.join(rootDirectory, resource.relativeSourceDirectory);
    const dst = path.join(buildPath, RESOURCE_BASE_DIR, resource.relativeTargetDirectory);
    fs.copySync(src, dst);
}
