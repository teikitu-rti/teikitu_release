# PARAMETER LIST FOR SCRIPT
Param(
# --------------------------------------------------------------------------------------------------------------
    [Parameter(HelpMessage = "Select CMAKE Generator")]
    [string]$IDE = "Visual Studio 17 2022",

    [Parameter(HelpMessage = "Select compiler")]
    [ValidateSet("CLANG", "MSVC")]
    [string]$COMPILER="MSVC",

# --------------------------------------------------------------------------------------------------------------
    [Parameter(HelpMessage = "Clean directory")]
    [switch]$CLEAN,

    [Parameter(HelpMessage = "Run cmake with --fresh")]
    [switch]$FRESH,

    [Parameter(HelpMessage = "Build the target")]
    [switch]$BUILD,

    [Parameter(HelpMessage = "Log Output")]
    [switch]$LOG_STATUS,

    [Parameter(HelpMessage = "OS Wide Character Support")]
    [switch]$OS_WIDE,

    [Parameter(HelpMessage = "GitHub Workflow")]
    [switch]$GITHUB,

# --------------------------------------------------------------------------------------------------------------
    [Parameter(Mandatory=$true, HelpMessage = "Select target cpu: C11_X64, INTEL_X64, C11_ARM")]
    [ValidateSet("C11_X64", "INTEL_X64", "C11_ARM")]
    [string]$CPU,

    [Parameter(Mandatory=$true, HelpMessage = "Select target threading library: WIN POSIX")]
    [ValidateSet("WIN", "POSIX")]
    [string]$THREAD,

    [Parameter(Mandatory=$true)]
    [ValidateSet("WIN", "POSIX")]
    [string]$OS,

    [Parameter(Mandatory=$true, HelpMessage = "Select target device: DESKTOP_X86")]
    [ValidateSet("DESKTOP_X86")]
    [string]$DEVICE,

    [Parameter(HelpMessage = "Select target gpu: REF, DX12")]
    [ValidateSet("NONE", "REF", "DX12")]
    [string]$GPU,

    [Parameter(HelpMessage = "Select target gpu: REF, DX12")]
    [ValidateSet("NONE", "REF", "XAUDIO")]
    [string]$AUDIO,

# --------------------------------------------------------------------------------------------------------------
    [Parameter(Mandatory=$true, HelpMessage = "Select a build type: DEBUG, RELEASE, FINAL, TOOL")]
    [ValidateSet("DEBUG", "RELEASE", "FINAL", "TOOLS")]
    [string]$BUILD_TYPE

# --------------------------------------------------------------------------------------------------------------
)

. $PSScriptRoot\powershell_functions.ps1

$GITHUB_SWITCH=$false
If ($GITHUB)
{
    $GITHUB_SWITCH=$true
}



# BUILD PATH
$CMAKE_BUILD_PATH="..\bld\"

$IDE_Token_List = $IDE.Split(" ")
If ($IDE_Token_List[0] -match "Visual" -and $IDE_Token_List[1] -match "Studio")
{
    $CMAKE_BUILD_PATH += "msvc_" + $IDE_Token_List[2]
}
elseif ($IDE_Token_List[0] -match "Ninja")
{
    $CMAKE_BUILD_PATH += $IDE_Token_List[0].ToLower()
    $CMAKE_BUILD_PATH += "_" + $BUILD_TYPE.ToLower()
    If ($GPU)
    {
        $CMAKE_BUILD_PATH += "_" + $GPU.ToLower()
    }
    Else
    {
        $CMAKE_BUILD_PATH += "_none"
    }
    If ($AUDIO)
    {
        $CMAKE_BUILD_PATH += "_" + $AUDIO.ToLower()
    }
    Else
    {
        $CMAKE_BUILD_PATH += "_none"
    }
}
else
{
    Throw "Unknown CMAKE Generator for script: $IDE"
}

$CMAKE_BUILD_PATH += "_" + $COMPILER.ToLower()
$CMAKE_BUILD_PATH += "_" + $CPU.ToLower()
$CMAKE_BUILD_PATH += "_" + $THREAD.ToLower()
$CMAKE_BUILD_PATH += "_" + $OS.ToLower()
If ($OS_WIDE)
{
    $CMAKE_BUILD_PATH += "_wc"
}
$CMAKE_BUILD_PATH += "_" + $DEVICE.ToLower()

if ($PSBoundParameters.debug -and $PSBoundParameters.verbose) { Write-Host -fore DarkYellow "BUILD PATH: $CMAKE_BUILD_PATH" }




# Build Directory Validations and Bootstrap
If ($CLEAN)
{
    try { remove-item $CMAKE_BUILD_PATH -Recurse -Force -ErrorAction Stop } catch [System.Exception] { switch($_.Exception.GetType().FullName) { "System.Management.Automation.ItemNotFoundException" {} default { throw $error[0] } } }
}

$bootstrap_file_exists = Test-Path -Path .\$CMAKE_BUILD_PATH\bootstrap\cmakelists.txt -PathType Leaf
# Write-Debug -Message ("BOOTSTRAP FILE PATH: .\$CMAKE_BUILD_PATH\bootstrap\cmakelists.txt")
# Write-Debug -Message ("BOOTSTRAP FILE EXISTS: $bootstrap_file_exists")
If ($CLEAN -or !$bootstrap_file_exists)
{
    new-item -Name .\$CMAKE_BUILD_PATH\bootstrap -ItemType directory | out-null
    copy-item bootstrap_cmakelists.txt .\$CMAKE_BUILD_PATH\bootstrap\cmakelists.txt
    copy-item Directory.build.props .\$CMAKE_BUILD_PATH\bootstrap\Directory.build.props
}




# BUILD COMMON COMMAND LINE
$CMAKE_BUILD_COMMON_CMD=@() # Empty Array

If ($LOG_STATUS)
{
    $CMAKE_BUILD_COMMON_CMD += "--log-level=STATUS"
}

If ($FRESH)
{
    $CMAKE_BUILD_COMMON_CMD += "--fresh"
}

$CMAKE_BUILD_COMMON_CMD += '-G ' + '"' + $IDE + '"'

If ($IDE_Token_List[0] -match "Visual" -and $IDE_Token_List[1] -match "Studio")
{
    If ($CPU -match "C11_X64" -or $CPU -match "INTEL_X64")
    {
        $CMAKE_BUILD_COMMON_CMD += "-A x64"
    }

    If ($COMPILER -match "CLANG")
    {
        $CMAKE_BUILD_COMMON_CMD += "-T ClangCL"
    }
}

if ($IDE_Token_List[0] -match "Ninja" -and $COMPILER -match "CLANG")
{
    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_C_COMPILER:PATH="C:\Program Files\LLVM\bin\clang.exe"'
    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_CXX_COMPILER:PATH="C:\Program Files\LLVM\bin\clang++.exe"'
}

$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__HW=" + $CPU.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__THREAD=" + $THREAD.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__OS=" + $OS.ToUpper()
If ($OS_WIDE)
{
    $CMAKE_BUILD_COMMON_CMD += "-DMK_COMPILE_PLATFORM_TEXT__WIDE=1"
}
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__DEVICE=" + $DEVICE.ToUpper()
If ($GPU)
{
    $CMAKE_BUILD_COMMON_CMD += "-DMK_FEATURE__GRAPHICS=" + $GPU.ToUpper()
}
If ($AUDIO)
{
    $CMAKE_BUILD_COMMON_CMD += "-DMK_FEATURE__AUDIO=" + $AUDIO.ToUpper()
}
$CMAKE_BUILD_COMMON_CMD += "-DCMAKE_BUILD_TYPE=" + $BUILD_TYPE.ToUpper()

if ($PSBoundParameters.debug -and $PSBoundParameters.verbose) { Write-Host -fore DarkYellow "CMAKE COMMON: $CMAKE_BUILD_COMMON_CMD" }




# BUILD BOOTSTRAP COMMAND LINE
$cmake_stream_file_exists = Test-Path -Path .\$CMAKE_BUILD_PATH\cmake_stream.cmake -PathType Leaf
If ($CLEAN -or $FRESH -or !$bootstrap_file_exists -or !$cmake_stream_file_exists)
{
    $process = Process_Construct -FileName:"cmake.exe" -GITHUB:$GITHUB_SWITCH
    try {
        $process.StartInfo.Arguments = $CMAKE_BUILD_COMMON_CMD + "-S .\$CMAKE_BUILD_PATH\bootstrap" + "-B .\$CMAKE_BUILD_PATH\bootstrap"
        if ($PSBoundParameters.debug) { Write-Host -fore cyan "CMAKE BOOTSTRAP ARGUMENTS: $($process.StartInfo.Arguments)" }
        $process.Start() | Out-Null
        Process_Wait_And_Output -process:$process
    } catch { Write-Host -Fore white "FAILED: CMake Bootstrap."; Exit 1 } finally { $process.Dispose() }
}




# CMAKE COMMAND LINE
$process = Process_Construct -FileName:"cmake.exe" -GITHUB:$GITHUB_SWITCH
try {
    $process.StartInfo.Arguments = $CMAKE_BUILD_COMMON_CMD + "-S ." + "-B .\$CMAKE_BUILD_PATH"
    if ($PSBoundParameters.debug) { Write-Host -fore cyan "CMAKE BOOTSTRAP ARGUMENTS: $($process.StartInfo.Arguments)" }
    $process.Start() | Out-Null
    Process_Wait_And_Output -process:$process
} catch { Write-Host -Fore white "FAILED: CMake Project Build."; Exit 1 } finally { $process.Dispose() }




# BUILD COMMAND
If ($BUILD)
{
    $process = Process_Construct -FileName:"cmake.exe" -GITHUB:$GITHUB_SWITCH
    try {
        $process.StartInfo.Arguments = "--build $CMAKE_BUILD_PATH"
        if ($PSBoundParameters.debug) { Write-Host -fore cyan "CMAKE BOOTSTRAP ARGUMENTS: $($process.StartInfo.Arguments)" }
        $process.Start() | Out-Null
        Process_Wait_And_Output -process:$process
    } catch { Write-Host -Fore white "FAILED: CMake Build."; Exit 1 } finally { $process.Dispose() }
}
