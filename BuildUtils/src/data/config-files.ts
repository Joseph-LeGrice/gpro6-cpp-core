
export interface Config
{
    dlls?: DllConfig[]
    resources?: ResourceConfig[];
    monoProjects?: MonoBuildConfig[];
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

export interface MonoBuildConfig
{
    relativeProjectDirectory: string;
    relativeTargetDirectory: string;
    libraries: string[];
};
