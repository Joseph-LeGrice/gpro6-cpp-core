import * as path from 'path'
import * as fs from 'fs-extra'
import { DllConfig } from './data/config-files';
import { CopyResource } from './copy-resources';

export function CopyDLLs(dll: DllConfig, rootDirectory: string, buildPath: string, arch: string): void {
    console.log(`Copying DLL...`);
    const dllResource = dll[arch];
    CopyResource(dllResource, rootDirectory, buildPath);
}
