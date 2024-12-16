/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common -- VERSION.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON__VERSION_H)
#define TGS_COMMON__VERSION_H
#pragma once

// TODO Review Console Text processing (and any other text processing)
// TODO Add support for modern intrinsics - 256 and 512 (also note the expanded set of registers for these intrinsics)
// TODO __builtin_shufflevector
// TODO __attribute__((cpu_specific(ivybridge))), __attribute__((cpu_specific(generic)))
// TODO Effect commented out code
// TODO Render each of the basic geometry forms
// TODO Implement physics
// TODO Implement input on all apple devices (ugh)
// TODO Refactor Doxygen - Send in sample


/*
 Checklist
  - Copyright notice
  - Document - data structures
  - Document - API
 
 */


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */


/* 5.11 */ /* C1663C45-B8EA-46E7-8607-56216A251FC8 */ /* May 2020 - After losing work to reset --hard */
/*  Brief: May 2020 - After losing work to reset --hard
    Description: Includes: reformatting to a wide default file width (size), standardization on C11, cleanup of CMakeFiles, C11 atomics, enforced alignment - the old GCC style
    attribute does not seem to have work in Clang. Moving to C11 alignment command highlighted some areas to improve. Same with the use of C11 atomics, where issues came up that
    were appearing to have worked in the past. Enabled POSIX. Cleaned up the compiler, hardware, platform sequence of defines and includes for compilation to a target platform.
    Created the new text object (to differentiate from strings). This will be the standard way that text is used in the engine and will be based on UTF standards. Unfortunately,
    uchar.h is not available on the Mac. Once it is more common, will integrate it into the text object. In the mean time, will separate out the char type declaration for use with
    the operating system from the common character type used in the engine. Removed the old atomic functions. Kept the other wrapper functions for numerics for standardization. */

/* 5.12 */ /* 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  Brief: May 2020 - After changing the integer types
    Description: Bumped the version again for an indicator that data structures have been reviewed for C11 atomic implementation and for the distinction between the fast and exact
    integer types. The default should be to use the fast integer types. However, these can be of a indeterminate size and alignment, making structure packing difficult. It is in
    these cases that the exact bit sized versions need to be used. Including doxygen / java docs style comments in all headers.
        Note: STg1_XXX is for low level wrappers of operating system objects. All other types should be STg2. */

/* 5.15 */ /* 00D008E0-5616-4AAF-8989-24865B450F52 */
/*  Brief: June 2020 - WIP for Release 0.1
    Description: Mark files where unit test coverage is 100% (best intention reminder that changes to the file require an update to the unit tests). Modify the header to include
    the necessary @file command (for global functions). Include new group definitions.
        Note: File name nomenclature for include files XXX.h is part of the direct include chain. XXX [YYY].h is part of indirect include chain (include contained in parent file).
 */

/* 5.16 */ /* 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  Brief: June 2020 - WIP for Release 0.1, Finalizing Doxygen configuration and documentation
    Description: Move Doxygen configuration into the individual header files. Include [in] and [out] on the parameter declarations for comments. Move file wide comments into the
    group definition so that it appears under the group. Add comments to all of the header files, including the code generation files (h_inc).
 */

/* 5.17 */ /* 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  Brief: August 2020 - WIP for Release 0.2, Apple & ARM compilation and support, change in math standards
    Description: Change to column major storage for matrices, row major matrix representation. Changes to compilation for Apple Universal support, ARM builds, iOS and MacOS.
    Refactor of Geometry library to use native vector types. Removal of the include-of-include file types and compilation pattern (h_inc, i_inc, c_inc). These files were changed
    to be their regular type and use a self-include header. This does cause some confusion for IDE parsers, but to date has not been an issue for the actual compilers. It improves
    the IDE warning and error checking (live) since the files now match expectations. Standardization of the native and scalar math libraries. Move to standardize (nomenclature)
    on the vector based math implementation.  Support for Ninja, MSVC, and Windows builds.
 */

/* 5.18 */ /* 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  Brief: September 2020 - Update of Collision library, refactor of Common Geometry types and implementation. 
    Description: Complete removal of scalar floating point values in geometry types and implementation. Refactor and update of the collision library.
 */

/* 5.19 */ /* 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  Brief: June 2022 - Update header format towards (but not matching) GNU. Massive update from previous versions.
    Description: Completed the update of Common library with validation for column major matrices. Continued to improve the percentage of compiled collision code. Finished the
    current phase of the Kernel module, which included GPU support. Test is able to create nine windows, six on one adapter, three on the second adapter. Each set of three
    windows contains render targets that are (in order) an 8 bit buffer, HDR 10 bit buffer, HDR 16bit buffer. The test renders a reference image, debug text, and a set of
    unlit cubes, and a lit cubes (cycling through RGB colours). Effect library successfully compiles. Changes were made to allow for compilation when in headless mode (which is
    assumed to be the case where the GPU target is set to none). The remaining modules (most of which are bootstrap only, waiting for the porting from older versions) have also
    been brought into the build, and made to compile successfully. All of these changes have most definitely broken the apple build, and will have to go back to it, sometime
    in the future to fix the build. Next steps (next version increment) will be rendering, physics, and execution modules. 
 */

/* 5.20 */ /* DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  Brief: September 2022 - This version will represent the full bring up of the Render, Physic, and Execution Modules. (Working non-test executable.)
    Description: 
 */



/* =============================================================================================================================================================================== */

/* Ran 9/6/2022 */
/*  % cloc --exclude-dir=doc --force-lang="C",c_inc --force-lang="C",i_inc --force-lang="C",h_inc --force-lang="C",h --force-lang="C",inl .
 
     981 text files.
     912 unique files.
      86 files ignored.

    github.com/AlDanial/cloc v 1.95  T=0.40 s (2307.9 files/s, 533957.2 lines/s)
    -------------------------------------------------------------------------------
    Language                     files          blank        comment           code
    -------------------------------------------------------------------------------
    C                              824          39325          49201         116063
    CMake                           32           1130            421           2137
    HLSL                            33            202             48            783
    C++                              9            164            196            517
    PowerShell                       5            116             27            425
    Text                             3             24              0             67
    YAML                             1             11              2             65
    XML                              3              8             17             30
    Markdown                         1              4              0              8
    XAML                             1              1              0              7
    -------------------------------------------------------------------------------
    SUM:                           912          40985          49912         120102
    -------------------------------------------------------------------------------

*/


/* =============================================================================================================================================================================== */

#endif
