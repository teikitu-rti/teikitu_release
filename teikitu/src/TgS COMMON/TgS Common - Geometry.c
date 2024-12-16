/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */
#if defined (TGS_COMMON_GEOMETRY_H)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define t0              0.5773502691896257645091487805019F
/* #define fPhi4           6.4721359549995793928183473374626F */
/* #define fRadiusRatio    1.7013016167040798643630809941259F */
#define f2              0.5257311121191336060256690848475F
#define f3              0.8506508083520399321815404970625F




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- TETRAHEDRON -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgUINT_E16_C KTgGM_CUBE_P_INDEX[36] =
{
    0,1,2,  1,3,2,  4,6,5,  5,6,7,  0,5,1,  0,4,5,  2,7,6,  2,3,7,  0,6,4,  0,2,6,  1,7,3,  1,5,7
};

TgVEC_UN_F32_04_1_C KTgGM_CUBE_P_INDEX_VERTEX[8] =
{
    { .m_vS_F32_04_1 = {{ -0.5f, -0.5f, -0.5f, 1.0f }}},
    { .m_vS_F32_04_1 = {{ -0.5f, -0.5f,  0.5f, 1.0f }}},
    { .m_vS_F32_04_1 = {{ -0.5f,  0.5f, -0.5f, 1.0f }}},
    { .m_vS_F32_04_1 = {{ -0.5f,  0.5f,  0.5f, 1.0f }}},
    { .m_vS_F32_04_1 = {{  0.5f, -0.5f, -0.5f, 1.0f }}},
    { .m_vS_F32_04_1 = {{  0.5f, -0.5f,  0.5f, 1.0f }}},
    { .m_vS_F32_04_1 = {{  0.5f,  0.5f, -0.5f, 1.0f }}},
    { .m_vS_F32_04_1 = {{  0.5f,  0.5f,  0.5f, 1.0f }}},
};

TgVEC_UN_F32_04_1_C KTgGM_CUBE_PN_TRI_LIST_VERTEX[72] =
{
    { .m_vS_F32_04_1 = {{-0.5f,-0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{-1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f,-0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{-1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f, 0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{-1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f, 0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f,-1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f,-0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f,-1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f, 0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f,-1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f,-0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f,-1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f,-0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f,-1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f,-0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f,-1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f, 0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f,-1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f,-0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f,-1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f,-0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f,-1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f,-0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{-1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f, 0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{-1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f, 0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{-1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f,-0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f,-1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f,-0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f,-1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f,-0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f,-1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f, 0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f, 1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f,-0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f, 1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f,-0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f, 1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f, 0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f,-0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f, 0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f,-0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f, 0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f,-0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 1.0f, 0.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f, 0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f, 0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f, 0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f, 0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f, 0.5f,-0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f, 0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 1.0f, 0.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f, 0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f, 1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{-0.5f, 0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f, 1.0f, 0.f}}},
    { .m_vS_F32_04_1 = {{ 0.5f,-0.5f, 0.5f, 1.f}}}, { .m_vS_F32_04_1 = {{ 0.0f, 0.0f, 1.0f, 0.f}}},
};


/* ---- TETRAHEDRON -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgUINT_E16_C KTgGM_TETRAHEDRON_P_INDEX[12] =
{
       0,1,2,  0,3,1,  2,1,3,  3,0,2
};

TgVEC_UN_F32_04_1_C KTgGM_TETRAHEDRON_P_VERTEX[4] =
{
    { .m_vS_F32_04_1 = {{ t0, t0, t0, 1.0f}}},
    { .m_vS_F32_04_1 = {{-t0,-t0, t0, 1.0f}}},
    { .m_vS_F32_04_1 = {{-t0, t0,-t0, 1.0f}}},
    { .m_vS_F32_04_1 = {{ t0,-t0,-t0, 1.0f}}},
};


/* ---- OCTOGON ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

TgUINT_E16_C KTgGM_OCTOGON_P_INDEX[24] =
{
      0,4,2,  2,4,1,  1,4,3,  3,4,0,  0,2,5,  2,1,5,  1,3,5,  3,0,5
};

TgVEC_UN_F32_04_1_C KTgGM_OCTOGON_P_INDEX_VERTEX[6] =
{
    { .m_vS_F32_04_1 = {{ 1.f, 0.f, 0.f, 1.0f}}},
    { .m_vS_F32_04_1 = {{-1.f, 0.f, 0.f, 1.0f}}},
    { .m_vS_F32_04_1 = {{ 0.f, 1.f, 0.f, 1.0f}}},
    { .m_vS_F32_04_1 = {{ 0.f,-1.f, 0.f, 1.0f}}},
    { .m_vS_F32_04_1 = {{ 0.f, 0.f, 1.f, 1.0f}}},
    { .m_vS_F32_04_1 = {{ 0.f, 0.f,-1.f, 1.0f}}},
};


/* ---- ICOSAHEDRON -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgUINT_E16_C KTgGM_ICOSAHEDRON_PN_INDEX[60] =
{
     4, 8, 7,     4, 7, 9,     5, 6,11,     5,10, 6,     0, 4, 3,     0, 3, 5,     2, 7, 1,     2, 1, 6,     8, 0,11,     8,11, 1,
     9,10, 3,     9, 2,10,     8, 4, 0,    11, 0, 5,     4, 9, 3,     5, 3,10,     7, 8, 1,     6, 1,11,     7, 2, 9,     6,10, 2
};

TgVEC_UN_F32_04_1_C KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[24] =
{/*   XXXX, XXXX, XXXX, XXXX,         XXXX, XXXX, XXXX, XXXX, */
    { .m_vS_F32_04_1 = {{   f3,   f2, 0.0F, 1.0F }}},     { .m_vS_F32_04_1 = {{   f3,   f2, 0.0F, 0.0F }}},
    { .m_vS_F32_04_1 = {{  -f3,   f2, 0.0F, 1.0F }}},     { .m_vS_F32_04_1 = {{  -f3,   f2, 0.0F, 0.0F }}},
    { .m_vS_F32_04_1 = {{  -f3,  -f2, 0.0F, 1.0F }}},     { .m_vS_F32_04_1 = {{  -f3,  -f2, 0.0F, 0.0F }}},
    { .m_vS_F32_04_1 = {{   f3,  -f2, 0.0F, 1.0F }}},     { .m_vS_F32_04_1 = {{   f3,  -f2, 0.0F, 0.0F }}},
    { .m_vS_F32_04_1 = {{   f2, 0.0F,   f3, 1.0F }}},     { .m_vS_F32_04_1 = {{   f2, 0.0F,   f3, 0.0F }}},
    { .m_vS_F32_04_1 = {{   f2, 0.0F,  -f3, 1.0F }}},     { .m_vS_F32_04_1 = {{   f2, 0.0F,  -f3, 0.0F }}},
    { .m_vS_F32_04_1 = {{  -f2, 0.0F,  -f3, 1.0F }}},     { .m_vS_F32_04_1 = {{  -f2, 0.0F,  -f3, 0.0F }}},
    { .m_vS_F32_04_1 = {{  -f2, 0.0F,   f3, 1.0F }}},     { .m_vS_F32_04_1 = {{  -f2, 0.0F,   f3, 0.0F }}},
    { .m_vS_F32_04_1 = {{ 0.0F,   f3,   f2, 1.0F }}},     { .m_vS_F32_04_1 = {{ 0.0F,   f3,   f2, 0.0F }}},
    { .m_vS_F32_04_1 = {{ 0.0F,  -f3,   f2, 1.0F }}},     { .m_vS_F32_04_1 = {{ 0.0F,  -f3,   f2, 0.0F }}},
    { .m_vS_F32_04_1 = {{ 0.0F,  -f3,  -f2, 1.0F }}},     { .m_vS_F32_04_1 = {{ 0.0F,  -f3,  -f2, 0.0F }}},
    { .m_vS_F32_04_1 = {{ 0.0F,   f3,  -f2, 1.0F }}},     { .m_vS_F32_04_1 = {{ 0.0F,   f3,  -f2, 0.0F }}},
};


/* ---- ICOSAHEDRON_HEMI --------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgUINT_E16_C KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX[108] =
{
     /* Positive Cap */
      2, 6, 5, /* 0,P,0,*/
      3, 4, 7, /* 0,0,P,*/
      6, 0, 7, /* P,P,P,*/
      6, 7, 1, /* P,P,P,*/
      6, 2, 0, /* P,0,P,*/
      7, 0, 3, /* P,P,0,*/
      5, 6, 1, /* 0,P,P,*/
      4, 1, 7, /* 0,P,P,*/
      2, 8, 0,
      8, 3, 0,
      4, 9, 1,
      9, 5, 1,

     /* Negative Cap */
     12,15,16, /* 0,0,N,*/
     13,17,14, /* 0,N,0,*/
     16,17,11, /* N,N,N,*/
     16,10,17, /* N,N,N,*/
     12,16,11, /* 0,N,N,*/
     13,11,17, /* 0,N,N,*/
     15,10,16, /* 0,N,N,*/
     14,17,10, /* 0,N,N*/
     13,18,11,
     18,12,11,
     15,19,10,
     19,14,10,

     /* Tube Section */
      2,12, 8,
      8,12,18,
      8,18, 3,
      3,18,13,
      3,13, 4,
      4,13,14,
      4,14, 9,
      9,14,19,
      9,19, 5,
      5,19,15,
      5,15, 2,
      2,15,12,
};


TgVEC_UN_F32_04_1_C KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX[40] =
{/*   XXXX, XXXX, XXXX, XXXX,         XXXX, XXXX, XXXX, XXXX, */
    { .m_vS_F32_04_1 = {{   f3,   f2, 0.0F, 1.0F}}},      { .m_vS_F32_04_1 = {{   f3,   f2, 0.0F, 0.0F}}},
    { .m_vS_F32_04_1 = {{  -f3,   f2, 0.0F, 1.0F}}},      { .m_vS_F32_04_1 = {{  -f3,   f2, 0.0F, 0.0F}}},
    { .m_vS_F32_04_1 = {{   f2, 0.0F,   f3, 1.0F}}},      { .m_vS_F32_04_1 = {{   f2, 0.0F,   f3, 0.0F}}},
    { .m_vS_F32_04_1 = {{   f2, 0.0F,  -f3, 1.0F}}},      { .m_vS_F32_04_1 = {{   f2, 0.0F,  -f3, 0.0F}}},
    { .m_vS_F32_04_1 = {{  -f2, 0.0F,  -f3, 1.0F}}},      { .m_vS_F32_04_1 = {{  -f2, 0.0F,  -f3, 0.0F}}},
    { .m_vS_F32_04_1 = {{  -f2, 0.0F,   f3, 1.0F}}},      { .m_vS_F32_04_1 = {{  -f2, 0.0F,   f3, 0.0F}}},
    { .m_vS_F32_04_1 = {{ 0.0F,   f3,   f2, 1.0F}}},      { .m_vS_F32_04_1 = {{ 0.0F,   f3,   f2, 0.0F}}},
    { .m_vS_F32_04_1 = {{ 0.0F,   f3,  -f2, 1.0F}}},      { .m_vS_F32_04_1 = {{ 0.0F,   f3,  -f2, 0.0F}}},
    { .m_vS_F32_04_1 = {{ 0.5F, 0.0F, 0.0F, 1.0F}}},      { .m_vS_F32_04_1 = {{ 1.0F, 0.0F, 0.0F, 0.0F}}},
    { .m_vS_F32_04_1 = {{-0.5F, 0.0F, 0.0F, 1.0F}}},      { .m_vS_F32_04_1 = {{-1.0F, 0.0F, 0.0F, 0.0F}}},
    /* Positive Cap */

    { .m_vS_F32_04_1 = {{-f3,    -f2, 0.0F, 1.0F}}},      { .m_vS_F32_04_1 = {{  -f3,  -f2, 0.0F, 0.0F}}},
    { .m_vS_F32_04_1 = {{ f3,    -f2, 0.0F, 1.0F}}},      { .m_vS_F32_04_1 = {{   f3,  -f2, 0.0F, 0.0F}}},
    { .m_vS_F32_04_1 = {{ f2,   0.0F,   f3, 1.0F}}},      { .m_vS_F32_04_1 = {{   f2, 0.0F,   f3, 0.0F}}},
    { .m_vS_F32_04_1 = {{ f2,   0.0F,  -f3, 1.0F}}},      { .m_vS_F32_04_1 = {{   f2, 0.0F,  -f3, 0.0F}}},
    { .m_vS_F32_04_1 = {{-f2,   0.0F,  -f3, 1.0F}}},      { .m_vS_F32_04_1 = {{  -f2, 0.0F,  -f3, 0.0F}}},
    { .m_vS_F32_04_1 = {{-f2,   0.0F,   f3, 1.0F}}},      { .m_vS_F32_04_1 = {{  -f2, 0.0F,   f3, 0.0F}}},
    { .m_vS_F32_04_1 = {{ 0.0F,  -f3,   f2, 1.0F}}},      { .m_vS_F32_04_1 = {{ 0.0F,  -f3,   f2, 0.0F}}},
    { .m_vS_F32_04_1 = {{ 0.0F,  -f3,  -f2, 1.0F}}},      { .m_vS_F32_04_1 = {{ 0.0F,  -f3,  -f2, 0.0F}}},
    { .m_vS_F32_04_1 = {{ 0.5F, 0.0F, 0.0F, 1.0F}}},      { .m_vS_F32_04_1 = {{ 1.0F, 0.0F, 0.0F, 0.0F}}},
    { .m_vS_F32_04_1 = {{-0.5F, 0.0F, 0.0F, 1.0F}}},      { .m_vS_F32_04_1 = {{-1.0F, 0.0F, 0.0F, 0.0F}}},
    /* Negative Cap */
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgGM_Primitive_To_USZ ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgGM_Primitive_To_USZ( ETgPRIMITIVE_C enPM )
{
    switch (enPM)
    {
        case ETgPRIMITIVE_UNKNOWN:
        case ETgPRIMITIVE_MAX:
        default:
            return(u8"UNKNOWN");

        case ETgPOINT: return(u8"POINT");
        case ETgPARTICLE: return(u8"PARTICLE");

        case ETgLINE: return(u8"LINE");
        case ETgRAY: return(u8"RAY");
        case ETgSEGMENT: return(u8"SEGMENT");

        case ETgRECTANGLE2D: return(u8"RECTANGLE2D");
        case ETgELLIPSE2D: return(u8"ELLIPSE2D");

        case ETgCIRCLE: return(u8"CIRCLE");
        case ETgDISK: return(u8"DISK");
        case ETgELLIPSE: return(u8"ELLIPSE");
        case ETgPARALLELOGRAM: return(u8"PARALLELOGRAM");
        case ETgPLANE: return(u8"PLANE");
        case ETgRECTANGLE: return(u8"RECTANGLE");
        case ETgPTRI: return(u8"PTRI");
        case ETgETRI: return(u8"ETRI");
        case ETgCTRI: return(u8"CTRI");
        case ETgSTRI: return(u8"STRI");

        case ETgBOXAA: return(u8"BOXAA");
        case ETgBOX: return(u8"BOX");
        case ETgCAPSULE: return(u8"CAPSULE");
        case ETgCONE: return(u8"CONE");
        case ETgCYLINDER: return(u8"CYLINDER");
        case ETgFRUSTRUM: return(u8"FRUSTRUM");
        case ETgMESH_SIMPLE: return(u8"MESH_SIMPLE");
        case ETgMESH_BVT: return(u8"MESH_BVT");
        case ETgMESH_BA: return(u8"MESH_BA");
        case ETgSPHERE: return(u8"SPHERE");
        case ETgTETRAHEDRON: return(u8"TETRAHEDRON");
        case ETgTORUS: return(u8"TORUS");
        case ETgTUBE: return(u8"TUBE");
    };
}


/* ---- tgGM_Primitive_To_WSZ ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_WC_CP tgGM_Primitive_To_WSZ( ETgPRIMITIVE_C enPM )
{
    switch (enPM)
    {
        case ETgPRIMITIVE_UNKNOWN:
        case ETgPRIMITIVE_MAX:
        default:
            return(L"UNKNOWN");

        case ETgPOINT: return(L"POINT");
        case ETgPARTICLE: return(L"PARTICLE");

        case ETgLINE: return(L"LINE");
        case ETgRAY: return(L"RAY");
        case ETgSEGMENT: return(L"SEGMENT");

        case ETgRECTANGLE2D: return(L"RECTANGLE2D");
        case ETgELLIPSE2D: return(L"ELLIPSE2D");

        case ETgCIRCLE: return(L"CIRCLE");
        case ETgDISK: return(L"DISK");
        case ETgELLIPSE: return(L"ELLIPSE");
        case ETgPARALLELOGRAM: return(L"PARALLELOGRAM");
        case ETgPLANE: return(L"PLANE");
        case ETgRECTANGLE: return(L"RECTANGLE");
        case ETgPTRI: return(L"PTRI");
        case ETgETRI: return(L"ETRI");
        case ETgCTRI: return(L"CTRI");
        case ETgSTRI: return(L"STRI");

        case ETgBOXAA: return(L"BOXAA");
        case ETgBOX: return(L"BOX");
        case ETgCAPSULE: return(L"CAPSULE");
        case ETgCONE: return(L"CONE");
        case ETgCYLINDER: return(L"CYLINDER");
        case ETgFRUSTRUM: return(L"FRUSTRUM");
        case ETgMESH_SIMPLE: return(L"MESH_SIMPLE");
        case ETgMESH_BVT: return(L"MESH_BVT");
        case ETgMESH_BA: return(L"MESH_BA");
        case ETgSPHERE: return(L"SPHERE");
        case ETgTETRAHEDRON: return(L"TETRAHEDRON");
        case ETgTORUS: return(L"TORUS");
        case ETgTUBE: return(L"TUBE");
    };
}


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/*# defined (TGS_COMMON_GEOMETRY_H) */
#endif
