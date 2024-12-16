
<h1 align="center">Teikitu: Real-Time Interactive Engine</h1>
<p align="center">
  A low-level real-time interactive engine written in C, and a game platform written in C++.<br>
  <a href="https://aaye.github.io/projects/teikitu/documentation"><strong>Explore Teikitu documentation »</strong></a><br><br>
  <a href="https://github.com/teikitu-rti/teikitu_release/issues/new?template=bug_report.md">Report bug</a> · <a href="https://github.com/teikitu-rti/teikitu_release/issues/new?template=feature_request.md">Request feature</a>
</p>

## Personal Project by Andrew Aye
Contact: [`GitHub`][rep-url], [`LinkedIn`][linkedin-url], [`Mail`][mail], [`Personal Page`][personal-page-url]
, [`Blog`][blog-url]

## Table of Contents

- [Project Status](#project-status)
- [Project History](#quick-start)
- [Author History](#quick-start)
- [Quick Start](#quick-start)
- [Repo Structure](#repo-structure)
- [Prerequisites and Dependencies](#prerequisites-and-dependencies)
- [Known Issues and Workflow Improvements](#known-issues-and-workflow-improvements)
- [Copyright and license](#copyright-and-license)

## Project Status

[![CodeFactor](https://www.codefactor.io/repository/github/teikitu-rti/teikitu_release/badge/master)](https://www.codefactor.io/repository/github/teikitu-rti/teikitu_release/overview/master)
[![Documentation][documentation-badge]][documentation-url]
[![License: CC BY-NC-SA 4.0][license-badge]][license-url]
![GitHub Sponsors](https://img.shields.io/github/sponsors/aaye)

### Internal Development Build Status

| Build-Compiler-C STD-CPU-Thread-OS-Device-GPU API-Audio | Status |
|:-:|:-:|
| `ninja_clang_c17_x64_posix_posix_desktop_none_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A22%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hlnx_ninja_clang_c17_x64_posix_posix_desktop_none_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A23%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hlnx_ninja_clang_c17_x64_posix_posix_desktop_none_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A22%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hlnx_ninja_clang_c17_x64_posix_posix_desktop_none_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A23%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hlnx_ninja_clang_c17_x64_posix_posix_desktop_none_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A22%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hlnx_ninja_clang_c17_x64_posix_posix_desktop_none_none_tools_release.yml)<br>|
| `ninja_clang_c17_x64_windows_windows_desktop_dx12_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A20%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_dx12_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A20%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_dx12_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A22%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_dx12_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A23%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_dx12_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A21%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_dx12_none_tools_release.yml)<br>|
| `ninja_clang_c17_x64_windows_windows_desktop_none_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A18%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_none_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A19%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_none_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A20%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_none_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A21%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_none_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A21%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_none_none_tools_release.yml)<br>|
| `ninja_clang_c17_x64_windows_windows_desktop_ref_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A20%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_ref_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A21%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_ref_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A21%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_ref_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A20%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_ref_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A20%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_ref_none_tools_release.yml)<br>|
| `ninja_clang_c17_x64_windows_windows_desktop_vulkan_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A20%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_vulkan_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A21%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_vulkan_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A21%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_vulkan_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A22%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_vulkan_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A22%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_vulkan_none_tools_release.yml)<br>|
| `ninja_clang_c17_arm_posix_android_desktop_none_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A16%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hlnx_ninja_clang_c17_arm_posix_android_desktop_none_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A18%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hlnx_ninja_clang_c17_arm_posix_android_desktop_none_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A17%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hlnx_ninja_clang_c17_arm_posix_android_desktop_none_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A20%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hlnx_ninja_clang_c17_arm_posix_android_desktop_none_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A19%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hlnx_ninja_clang_c17_arm_posix_android_desktop_none_none_tools_release.yml)<br>|
| `ninja_clang_c17_arm_posix_posix_desktop_metal_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A05%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_metal_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A09%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_metal_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A07%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_metal_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A17%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_metal_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A19%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_metal_none_tools_release.yml)<br>|
| `ninja_clang_c17_arm_posix_posix_desktop_none_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A11%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_none_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A15%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_none_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A13%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_none_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A21%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_none_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2005%3A23%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu/blob/main/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_none_none_tools_release.yml)<br>|

### Public Release Build Status

| Build-Compiler-C STD-CPU-Thread-OS-Device-GPU API-Audio | Status |
|:-:|:-:|
| `ninja_clang_c17_x64_posix_posix_desktop_none_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A46%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hlnx_ninja_clang_c17_x64_posix_posix_desktop_none_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A47%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hlnx_ninja_clang_c17_x64_posix_posix_desktop_none_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A46%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hlnx_ninja_clang_c17_x64_posix_posix_desktop_none_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A47%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hlnx_ninja_clang_c17_x64_posix_posix_desktop_none_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A48%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hlnx_ninja_clang_c17_x64_posix_posix_desktop_none_none_tools_release.yml)<br>|
| `ninja_clang_c17_x64_windows_windows_desktop_none_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A47%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_none_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A48%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_none_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A48%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_none_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A47%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_none_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A50%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_none_none_tools_release.yml)<br>|
| `ninja_clang_c17_x64_windows_windows_desktop_ref_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A48%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_ref_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A48%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_ref_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A48%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_ref_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A49%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_ref_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A50%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_ref_none_tools_release.yml)<br>|
| `ninja_clang_c17_x64_windows_windows_desktop_dx12_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A49%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_dx12_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A49%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_dx12_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A49%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_dx12_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A49%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_dx12_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A48%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hwin_ninja_clang_c17_x64_windows_windows_desktop_dx12_none_tools_release.yml)<br>|
| `ninja_clang_c17_arm_posix_posix_desktop_none_none` | [![](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A39%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_none_none_debug.yml)<br>[![](https://img.shields.io/badge/Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A43%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_none_none_release.yml)<br>[![](https://img.shields.io/badge/Final-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A41%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_none_none_final.yml)<br>[![](https://img.shields.io/badge/Tools%20Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A45%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_none_none_tools_debug.yml)<br>[![](https://img.shields.io/badge/Tools%20Release-Success-2EA043?style=flat-square&logo=github&labelColor=333333)![](https://img.shields.io/badge/-2024%2F12%2F23%2007%3A47%20UTC-blue?style=flat-square)](https://github.com/teikitu-rti/teikitu_release/blob/master/.github/workflows/build__hmac_ninja_clang_c17_arm_posix_posix_desktop_none_none_tools_release.yml)<br>|


## Project History

I started this code base at the University of Waterloo (1993-2000). Since then, it has seen over eight significant refactors. The original implementation was object-oriented and Windows com-compliant. The current version is written in a functional style using C17. I am aware that there are many advantages to modern C++. However, when using C++, authors tend to adopt object-orientated paradigms, which, in my opinion, are not a good match for an engine. I have also found that the coding flexibility I adopt in coding this engine has crushed C++ compilers and optimizers. I once had a  revision of the code base with the entire math and geometry library implemented as templates to facilitate an easy way to test 32bit and 64bit floats (for simulation issues and inconsistencies). The release build failed to finish after running for 24 hours. The current implementation, which uses the C pre-processor language for code generation to replace the use of templates, compiles in seconds (under a minute).

## Author History

**Andrew Aye** has worked in the game industry since March 2001. His responsibilities were to create significant game engine features (for example, a modern simulation on the PS2) and then to create and modify all aspects of a game engine (real-time interactive). Along the way, he became responsible for growing other engineers and organizations. The highlight (to date) of this career was owning the responsibility for leading and managing two Call of Duty projects (Modern Warfare 3, and Ghosts). In 2017, he transitioned into a traditional tech company (Amazon) and helped to bootstrap the Amazon Pharmacy project. In his role on the leadership team of North America Consumables, he helped navigate the pandemic for the engineering teams (remote work) and collaborated on creative solutions for the excessive demand placed on the amazon.com site. He then spent a brief period in an SMS Ad startup (Attentive) as their first Senior Director to support their hyper-scale growth. He later transitioned to Meta in the Instagram Ads organization and, most recently, into the Developer Relations organization for Reality Labs.

## Quick Start

Several quick start options are available:
- Tested (supported) generators are Visual Studio 2022, Xcode, Unix Makefiles, Ninja (Windows)
- Teikitu currently uses the superbuild process using CMake
  - The root CMakeLists.txt file contains only a list of external projects (including Teikitu)
  - Most of the projects are Teikitu dependencies
  - Once all the projects have been successfully built and installed, you can iterate only on Teikitu (or your personal project) without running cmake on the root.
- In an effort to reduce operation burden, I have standardized on using Powershell as the shell for all platforms
- It may be necessary to build my flavor of CMake due to breaking issues in the standard build
  - Example build line: @teikitu//build_scripts/cmake_command.ps1 -MODULE:CMAKE -OS:WINDOWS -CPU:C17_X64 -DEVICE:DESKTOP -THREAD:WINDOWS -COMPILER:CLANG -IDE:NINJA
  - EZ Build Script: @teikitu//build_scripts/make_cmake_windows.ps1
- On a Windows host computer, clone the repo: `git clone https://github.com/teikitu-rti/teikitu_release.git`
  - Create a Visual Studio solution using the MSVC compiler and a project using LLVM and Clang
    - Iterating is faster with the Visual Studio solution/project. However, it is not an approved build format since we are forced to use the C++ compiler.
    - `cd build_scripts` (or equivalent)
    - `./make_windows.ps1 -GPU:DX12`
    - Visual Studio solution file will be in ***//build/msvc17_msvc_c17_x64_win_win_desktop_dx12_none***
    - Ninja Clang project will be in ***//build/msvc17_msvc_c17_x64_win_win_desktop_dx12_none***
  - Compile the matrix of supported configurations
    - `cd build_scripts` (or equivalent)
    - `./test_windows.ps1`
    - Build results will be in ***//build/ninja_xxx***
- On a Mac host computer (preferably Apple hardware / ARM), clone the repo: `git clone https://github.com/teikitu-rti/teikitu_release.git`
  - Work in Progress [Tested - Issue for script to automate the process](https://github.com/teikitu-rti/teikitu/issues/22)
- On a Linux host computer, clone the repo: `git clone https://github.com/teikitu-rti/teikitu_release.git`
  - Work in Progress [Tested on WSL (Windows Linux Environment) - Issue for script to automate the process](https://github.com/teikitu-rti/teikitu/issues/23)

## Repo Structure

```text
teikitu
├──build_scripts/ - START HERE - contains scripts for creating IDE project files or building the project.
├──cmake/ - the core cmake files.
├──teikitu_assets/ - location is created during the build process to store reference data assets.
│  ├──images/ - contains reference images used in the unit tests.
├──teikitu_external/ - location for external dependencies.
├──teikitu_ide/ - contains files needed when generating ide specific project files.
├──teikitu_private/ - contains the source code for the project, including the unit tests.
│  ├──src/ - contains the source code of the project.
│  └──tests/ - contains the unit tests for validating the project.
├──teikitu_samples/ - contains some basic games and applications using Teikitu.
├──teikitu_sdk/ - contains the public include and inline files for using Teikitu.
└──teikitu_tools/ - contains some basic tools created to work with Teikitu.
```
      
## Prerequisites and Dependencies

Used in the compilation process and will need to be installed on the host computer. I used [chocolate](https://community.chocolatey.org/).
- [cmake][cmake-url] – Open-Source, cross-platform build tool.
  - I keep a personal git fork to control the intermediate directory on MSVC projects.
- [Ninja](https://community.chocolatey.org/packages/ninja) - Preferred build manager on Windows.
- [LLVM](https://LLVM.org) - Preferred compiler including Windows.
- [Flex Bison](https://community.chocolatey.org/packages/winflexbison) - Required for Doxygen. Only Windows version is no longer supported.
- [Python 3.x](https://community.chocolatey.org/packages/python3/3.11.5) - Used by OpenSubDiv and OpenUSD.
  - Installed with pip3: Jinga2, PyOpenGL, PySide6 (or PySide2).
  - It should be noted that getting either Pyside on Windows is difficult.<br>
    This worked: `pip3 install pyside6==6.5.1.1 --ignore-installed`

The following projects are cloned, built, and installed in the teikitu_external folder.
- [MiMalloc](https://github.com/microsoft/mimalloc.git), [TIFF](https://gitlab.com/libtiff/libtiff.git), [ZLIB](https://github.com/intel/zlib.git), [ZStd](https://github.com/facebook/zstd.git), [LibDeflate](https://github.com/ebiggers/libdeflate.git), [Directx-Headers](https://github.com/microsoft/DirectX-Headers.git), [OneAPI](https://github.com/oneapi-src/oneTBB.git), [Boost](https://github.com/boostorg/boost.git), [GLFW](https://github.com/glfw/glfw.git), [OpenEXR](https://github.com/AcademySoftwareFoundation/openexr.git), [OpenSubDiv](https://github.com/PixarAnimationStudios/OpenSubdiv.git), [OpenUSD](https://github.com/PixarAnimationStudios/OpenUSD.git), [Iconv](https://github.com/sys-bio/iconv.git), [Doxygen](https://github.com/doxygen/doxygen.git)

The following projects are downloaded and used in place.
- [Teikitu Asset Library](https://github.com/teikitu-rti/teikitu_assets.git), [DirectX Agile SDK](https://www.nuget.org/api/v2/package/Microsoft.Direct3D.D3D12/1.610.5)

## Known Issues and Workflow Improvements

**1. Microsoft Visual Studio Compiler (only) will compile all files as CXX**
<details><summary>2. Standard atomic header for the Microsoft Visual Studio Compiler</summary>
The header file has an error in its 16-byte template overrides. I fixed the defect and validated the change by both the removal of a deadlock that the locking version created and by a size comparison of the atomic 16-byte data structures. If it is not using the 16-byte CAS instructions, the structure will pad to 32 bytes instead of 16. The corrected file was placed into the Teikitu external directory and is used instead of the standard (included) file.
</details>
<details><summary>3. Microsoft Visual Studio Clang-CL (no longer supported)</summary>
    
***C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Microsoft\VC\v170\Microsoft.Cpp.ClangCl.Common.targets*** updated to prevent a Clang warning-as-error issue. If EnableFiberSafeOptimizations is enabled (/GT on the command line) it causes Clang-CL to issue a warning about an unused command-line argument. I suggest adding the following after a similar block that is used to clear out Multiprocessor Compilation (/MP)
```
<!-- copy EnableFiberSafeOptimizations to _EnableFiberSafeOptimizations.
     EnableFiberSafeOptimizations is cleared to avoid passing /GT to clang-cl, which generates a warning -->

<ItemGroup>
  <ClCompile Condition="'%(ClCompile.EnableFiberSafeOptimizations)' == 'true'">
    <_EnableFiberSafeOptimizations>true</_EnableFiberSafeOptimizations>
    <EnableFiberSafeOptimizations>false</EnableFiberSafeOptimizations>
  </ClCompile>`<br>
</ItemGroup>`
```

***C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Microsoft\VC\v170\Microsoft.Cpp.ClangCl.Common.targets*** updated to prevent a critical issue where Clang-CL is not passing through the C-standard flag to Clang. The result caused PCH and compilation mis-matches (the PCH was not compiled using the same C-standard flags as the C source files).

Object created near line 132 (<!-- Precompiled headers - need to build them first -->)
Missing an assignment for

```
LanguageStandard_C =“%(ClCompile.LanguageStandard_C)”
```

</details>
<details><summary>4. CMake Improvements when generating Visual Studio project files. (Personal preference change, not necessary by others)</summary>
Modified to allow me to set the intermediate directory.
</details>
<details><summary><strong>5. CMake breaks C-only projects through injection of a C++ ForceLinkerLanguage file.</strong></summary>
I could only modify the code responsible for injecting this file (CMake source, not in CMake files). It is unclear by the way they inject it if the file is ever correctly configured for the project context. In any case, I found multiple points of breakage with various files in the system include chain due to this injection and my specific project context. After configuration, the manual way to deal with the issue is to go into the XCode project and manually delete all of the CMakeCForceLinker files. I have done this and can confirm that the manual process will also work.
</details>




## Copyright and License

Teikitu is subject to the [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/) unless otherwise stated.


[bug-report-url]: https://github.com/twbs/bootstrap/issues/new?template=bug_report.md
[feature-request-url]: https://github.com/twbs/bootstrap/issues/new?template=feature_request.md

[rep-url]: https://github.com/aaye
[linkedin-url]: https://www.linkedin.com/in/andrew-aye/
[mail]: andrew.aye@gmail.com
[personal-page-url]: https://andrew.aye.page
[blog-url]: https://aaye.github.io/professional/blog/

[codefactor-badge]: https://img.shields.io/codefactor/grade/github/aaye/teikitu_release
[codefactor-url]: https://www.codefactor.io/repository/github/aaye/teikitu_release
[documentation-badge]: https://github.com/teikitu-rti/teikitu/actions/workflows/documentation.yml/badge.svg
[documentation-url]: https://aaye.github.io/projects/
[license-badge]: https://img.shields.io/badge/License-CC_BY--NC--SA_4.0-lightgrey.svg
[license-url]: http://creativecommons.org/licenses/by-nc-sa/4.0/

[cmake-url]: https://cmake.org/
