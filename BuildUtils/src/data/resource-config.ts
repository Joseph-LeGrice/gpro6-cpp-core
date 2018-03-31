export class ResourceConfig
{
    private get sourceDirectory(): string { return this._sourceDirectory; }
    private get targetDirectory(): string { return this._targetDirectory; }

    constructor(
        private _sourceDirectory: string,
        private _targetDirectory: string
    ) { }
}