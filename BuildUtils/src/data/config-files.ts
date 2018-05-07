
export interface Config
{
    dlls?: DllConfig[]
    resources?: ResourceConfig[];
}

export interface DllConfig 
{
    [arch: string]: ResourceConfig;
};

export interface ResourceConfig
{
    absoluteSourceDirectory?: string;
    relativeSourceDirectory?: string;
    relativeTargetDirectory: string;
};
