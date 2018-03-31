
export class MonoBuildConfig
{
    public get projectRootDirectory(): string { return this._projectRootDirectory; }
    public get outputFile(): string { return this._outputFile; }
    public get libraries(): string[] { return this._libraries; }

    constructor(
        private _projectRootDirectory: string,
        private _outputFile: string,
        private _libraries: string[]
    ) { }
}