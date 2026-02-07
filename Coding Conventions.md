# Coding Convention Document

## General Principles (Tenets)

1. The code base will bias towards preformance, simplicity, and readability. 
2. 


**Reasons, Exceptions, and General Thoughts**

1. Complex code can have many advantages leading to flexibility, extensability and performance impact. However, it is also prone to defects caused by the loss of institutional
   knowledge of the code, the asummptions and context when it was created. This code base will bias towards maintaining performance in ways that are as simple as possible to
   protect against knowledge loss, and so that readers can understand the code without issue. It is preferable if others can use the code base as a learning tool as well as
   as its core product purposes.

2. The choice of C was purposeful. Object oriented programming is a great invention that has aided the science and practive of software engineering. However, when placing an
   engineer into a C++ environment, there is a tendency to assume that object oriented programming is the required approach to a problem. Being a base platform (engine), this
   code base biases towards functional programming and resolving as many platform specific overrides at compilation time over runtime. 

   a) The last major refactor of the code base saw it transition to ANSI C. Since then we have moved it forward to use some of the functionality found in C11, C17. However,
      the intention is that the code base should adhere to ANSI C rules and compilation requirements as closely as possible to make it viable to port it back to ANSI C.

3. 


## C/C++ Types

### Functions (General)

#### Declaration

> /** @brief Update the Axis Aligned Bounding Box for the given object. @return Result Code.
>     @param [in] ARG0 Pointer to the prune and sweep system.
>     @param [in] ARG1 Unique identifier for the object.
>     @param [in] ARG2 Pointer to Axis Aligned Bounding Box to be added to the system. */
> TgEXTN TgRESULT
> tgPA_Graph_Object_Update(
>     TgPARTITION_GRAPH_ID_C ARG0, TgPARTITION_OBJECT_ID_C ARG1, TgBOXAA_F32_04_CPCU TgANALYSIS_NO_NULL ARG2 );

#### Definition

/* ---- tgPA_Graph_Object_Update ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgPA_Graph_Object_Update( TgPARTITION_GRAPH_ID_C tiPA, TgPARTITION_OBJECT_ID_C tiObject, TgBOXAA_F32_04_CPCU psBA )
{
    ...
}

/* ---- tgPA_Graph_PNS_Object_Update_Interval ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPA_Graph_PNS_Object_Update_Interval( STg2_PA_Graph__Prune_And_Sweep_PCU psPA_PNS, STg2_PA_Graph__PNS__Point_End_PCU psX, TgFLOAT32_C fMin0,
                                                     TgFLOAT32_C fMax0, TgFLOAT32_C fMin1, TgFLOAT32_C fMax1, TgPARTITION_OBJECT_ID_C tiObject )
{

}

**Reasons, Exceptions, and General Thoughts**

1. The common practice in C to have functions return the result (output) makes chaining function calls practical. However, it led to a proliferation of needing to have the return
   values represent two different intents - the success of the function call, as well as the desired output value of the function. This is problematic in many cases and requires
   a strong knowledge transfer and diligent checks of return values at all times for it to work. This code base will attempt to adhere to keeping these two intents separated.
   Most functions will return a result code (similar to the Windows API returning a HRESULT). The exception are the math functions where doing so would make common scenarios
   unreasonable for the coder (the juice is not worth the squeeze). 
2. Declaration Format: Doxygen style comments preceed the function call. A brief description followed by a description of the parameters. In many cases (see above) the return
   value is self-described (Result Code). In those cases, it is added to the end of the @brief line for documentation generation while not extending the comment block for 
   readers of the code base.
3. Definition Format: Comment header is used a readability break. 
4. The rest of the format is self-described by the example.

### Enumeration

**General Format**:

> enum E[Tg][MODULE SHORT FORM][NAME]: TgSINT_E32
>
>    E[Tg][MODULE SHORT FORM][NAME]__BEGIN,
>
>    E[Tg][MODULE SHORT FORM][NAME]__UNKNOWN = E[Tg][MODULE SHORT FORM][NAME]__BEGIN,
>    E[Tg][MODULE SHORT FORM][NAME]__[ENUM1],
>    E[Tg][MODULE SHORT FORM][NAME]__[ENUM2],
>
>    E[Tg][MODULE SHORT FORM][NAME]__END,
>    E[Tg][MODULE SHORT FORM][NAME]__MAX = E[Tg][MODULE SHORT FORM][NAME]__END,
>    E[Tg][MODULE SHORT FORM][NAME]__COUNT = E[Tg][MODULE SHORT FORM][NAME]__END - E[Tg][MODULE SHORT FORM][NAME]__BEGIN,
>
> E: Enumeration, Tg: Teikitu Game Engine

**Reasons, Exceptions, and General Thoughts**

NOTE: We assume the common practice of this document that a cleared state is undefined or unknown. The collolary is that a variable that is in a reset state (i.e. where the memory
      has been set to zero) cannot be a valid value.

1. "Unknown" enumeration is required in the case that the enumeration value may exist in an undefined (or unknwown state). The common example is when an enumeration is used as
   a member of a structure or class in a cleared state. (See the NOTE 1).
2. The specification adoption of enumeration classes and type safety means that its is beneficial to have a common nomenclature for enumerations used in loops.
3. The nomenclature also facilitates preprocessor macros for validation purposes.


### Structures

**General Format**:

> TgTYPE_STRUCT(S[Tg][2]_[MODULE SHORT FORM]_[NAME],)
> {
>     TgPARTITION_GRAPH_ID_SINGLETON              m_tiGraph_Singleton;
>     ETgPA_GRAPH_TYPE                            m_enPA_Graph;
> };
>
> S: Structure, Tg: Teikitu Game Engine, 2: 2nd Revision (*Historical Note*: Created when I transitioned the engine from C++ to C in 2010-2015)

**Reasons, Exceptions, and General Thoughts**

1. The spacing between type and field name is deliberate and part of the convention. In normal practice, when reading code, the clear separation aids in quick scanning when looking
   for specific fields of interest. 
2. The use of the preprocessor macro for the structure header is enforced as well. It is responsible for declaring the typedef and the associated standard set of nomenclature and
   associated modifiers. (e.g. [STRUCT]_P being a pointer type of the structure.)



