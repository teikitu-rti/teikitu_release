
# Personal Project by Andrew Aye

## Teikitu: Real-Time Interactive Engine

### Release Snap Shot

Public (release) copy of the Teikitu engine project

### Status

![Build Status](https://github.com/aaye/teikitu_release/actions/workflows/ninja-clang.yml/badge.svg) <sup><sub>| Ninja, Clang | Windows OS | Windows Threading | C11 Vector | No GPU / REF GPU / DX12 GPU |</sub></sup>

### Project History

I started the version revision of this code base while I was still at the University of Waterloo. Since 
then it has seen over eight significant refactors and drastic overhauls. The original implementation was
an object-oriented windows com-compliant implementation. The current is written in a functional style
using C17. I am aware that there are many advantages to modern C++, and I am also aware how difficult
it would be to create efficient and effective optimizers for the resulting compilation. I once had a
 revision of the code base that had the entire math and geometry library implemented as templates to
 facilitate an easy way to test both 32bit and 64bit floats (for simulation issues and inconsistencies).
 The release build failed to finish after running for 24 hours. The current implementation, with even
 more lines of code than that previous version, can compiled in seconds (under a minute).

### Author History

**Andrew Aye** has been working in the game industry since March 2001. His responsibilities were first
focused on creating significant game engine features (for example a modern simulation on the PS2) evolving
to creating and modifying all aspects of a game engine (real-time interactive). Along the way, he became
responsible for growing other engineers and then organizations. He always took a collaborative and
partnership stance with cross-functional partners. The highlight (to date) of this career was owning the
responsibility for leading and managing two Call of Duty projects (Modern Warfare 3, and Ghosts). In 2017
he transitioned into a traditional tech company (Amazon) and helped to bootstrap the Amazon Pharmacy
project. In his role on the leadership team of North America Consumables, he helped navigate the pandemic
for the engineering teams (remote work) and collaborated on creative solutions for the excessive demand
that was placed on the amazon.com site.

He is currently taking a break and looking forward to his next challenge. It is an open question if this
will be another role to feed, drive, and grow an organization, or if he will dive back into code to drive
impact for the next generation of real-time interactive software.

### License

The source code snippets posted or attached to this blog are subject to the [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/) unless otherwise stated.

### Installation of the Teikitu Real-Time Interactive Engine

I wish I could tell you that this will be entirely turn key. Unfortunately, it is close - but not quite that easy on Windows PCs.
1. MSBuild v1.70 which is used by Visual Studio 2022 has an issue (bug). See addendum 1.
2. For the cleanest version of the install, I made a couple changes to CMake. They are not necessary, however for consideration:
    a) Allowed myself to select the LLVM version to be used. I have tested against 14.0.5.
    b) Modified to allow me to set the intermediate directory.
3. I have not implemented a robust compilation test (yet) for the different configurations. My core PC test uses,
    MSVC IDE, clang compiler (clang-cl), windows os, windows threading, C11 vector support.
    I have compiled it on Mac OS using Xcode. In Phase 2, will setup CI with my github to validate the compilation of as many builds as is reasonable.

### Build Notes for the Teikitu Real-Time Interactive Engine

1. Using windows Terminal, you can use the example script file setup_msvc_17.ps1 to create a VS 2022 solution.
2. MSVC will compile all of the C code as CXX, due to the lack of a stdatomic implementation. Clang will compile the code using the correct compilers.

### Addendums to the Installtion and Build Notes for Teikitu Real-Time Interactive Engine

**Addendum 1 - MSBuild Fixes**

**ISSUE #1**

C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Microsoft\VC\v170\Microsoft.Cpp.ClangCl.Common.targets

If EnableFiberSafeOptimizations is enabled (/GT on the command line) it causes Clang-CL to issue a warning about an unused command-line argument. I suggest adding the following after a similar block that is used to clear out Multiprocessor Compilation (/MP)

```
<!-- copy EnableFiberSafeOptimizations to _EnableFiberSafeOptimizations.
     EnableFiberSafeOptimizations is cleared to avoid passing /GT to clang-cl which generates a warning -->

<ItemGroup>
  <ClCompile Condition="'%(ClCompile.EnableFiberSafeOptimizations)' == 'true'">
    <_EnableFiberSafeOptimizations>true</_EnableFiberSafeOptimizations>
    <EnableFiberSafeOptimizations>false</EnableFiberSafeOptimizations>
  </ClCompile>`<br>
</ItemGroup>`
```

**ISSUE #2**

C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Microsoft\VC\v170\Microsoft.Cpp.ClangCl.Common.targets
Object created near line 132 (<!-- Precompiled headers - need to build them first -->)
Missing an assignment for

```
LanguageStandard_C =“%(ClCompile.LanguageStandard_C)”
```

Causing PCH and compilation mis-matches

**ISSUE #3**

MSFT standard atomic header has an error in its 16 byte template overrides. I fixed this (and validated by both the removal a dead lock that the locking-version created, and by a size comparison of the atomic 16 byte data structures. If it is not using the 16 byte CAS instructions, the structure will pad to 32 bytes instead of 16.)

I copied the MSFT header file and made the needed changes, and added it into the external folder for compilation.
