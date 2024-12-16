$Jobs = @()

@('windows-latest') | ForEach-Object {
  $os = $_
  $build_cpu = 'C11_X64'
  $build_thread = 'WIN'
  $build_os = 'WIN'
  $build_device = 'DESKTOP_X86'
  $build_audio = 'NONE'
  @('NONE','REF','DX12') | ForEach-Object {
    $build_gpu = $_
    @('DEBUG','RELEASE','FINAL','TOOLS') | ForEach-Object {
      $build_type = $_
      $Jobs += @{
        job_name = "Run OS: $build_os WIDE: $build_wide GPU: $build_gpu TYPE: $build_type"
        os = $os
        cmake_cpu = $build_cpu
        cmake_thread = $build_thread
        cmake_os = $build_os
        cmake_device = $build_device
        cmake_audio = $build_audio
        cmake_gpu = $build_gpu
        cmake_type = $build_type
        clang_major_version = '14'
        clang_version = '14.0.6'
      }
    }
  }
}


Write-Host ($Jobs | ConvertTo-JSON)

if ($Raw) {
  Write-Host ($Jobs | ConvertTo-JSON)
} else {
  # Output the result for consumption by GitHub Actions
  Write-Host "::set-output name=matrix::$($Jobs | ConvertTo-JSON -Compress))"
}
