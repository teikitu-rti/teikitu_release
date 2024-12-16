/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Linear-Linear.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* ==== Linear - Point =========================================================================================================================================================== */
/**
    Segment Definition: G0(α) = P0 + α•D0 | α ε [ 0, 1]

   Derivation:
    Let the points of closest contact be Q0 = P0+γ•D0, and v = P1-Q0
    Geometrically we know that the vector connecting the two closest points of contact ( or the minimal distance vector ) must be perpendicular to the line.
    Thus, D0•v=0, D1•v=0, DS=P1-P0, v=P1-(P0+γ•D0)

        0 = D0_(P1-P0-γ•D0,DIM)
        0 = D0_(DS-γ•D0,DIM)
        0 = D0•DS-γ•D0•D0
        γ = D0•DS / D0•D0

   However, we know that γ ε [ 0, 1], generating three cases:
  
   [1] γ ε (-∞, 0) || γ = 0
      Distance: The distance between P0 and P1
         = (P1-P0)T_(P1-P0,DIM)
         = DS•DS

   [2] γ ε [ 0, 1] || γ = (DS•D0) / (D0•D0)
      Distance: The distance value would be || v ||.
         = || v || = v•v = (DS-γ•D0)T_(DS-γ•D0,DIM)
         = DS•DS + γ•γ•D0•D0 - 2•γ•DS•D0
         = DS•DS + γ•(γ•D0•D0 - 2•DS•D0)
         = DS•DS + γ•((DS•D0 / D0•D0)•D0•D0 - 2•DS•D0)
         = DS•DS + γ•(DS•D0 - 2•DS•D0)
         = DS•DS - γ•(DS•D0)

   [3] γ ε ( 1, ∞) || γ = 1
      Distance: The distance between P0+D0 and P1
         = (P1-P0-D0)•(P1-P0-D0)
         = (DS-D0)•(DS-D0)
         = DS•DS - 2•DS•D0 + D0•D0
*/


/* ==== Linear - Linear ========================================================================================================================================================== */
/**
    Segment Definition: G0(α) = P0 + α•D0 | α ε [ 0, 1]
    Segment Definition: G1(β) = P1 + β•D1 | β ε [ 0, 1]

   Derivation:
    Let the points of closest contact be Q0 = P0+γ•D0 and Q1 = P1+Φ•D1, and v = Q1-Q0
    Geometrically we know that the vector connecting the two closest points of contact ( or the minimal distance
      vector ) must be perpendicular to both lines.  Thus, D0•v=0, D1•v=0, DS=P1-P0, v=(P1+Φ•D1)-(P0+γ•D0)

        v = (P1+Φ•D1) - (P0+γ•D0)
          = P1 + Φ•D1 - P0 - γ•D0
          = P1 - P0 + Φ•D1 - γ•D0
          = DS + Φ•D1 - γ•D0

        0 = D0_(DS + Φ•D1 - γ•D0,DIM)               and     0 = D1_(DS + Φ•D1 - γ•D0,DIM)
        0 = (DS•D0) + Φ_(D0•D1,DIM) - γ_(D0•D0,DIM)     and     0 = (DS•D1) + Φ_(D1•D1,DIM) - γ_(D0•D1,DIM)
        γ = (DS•D0)/(D0•D0) + Φ_(D0•D1,DIM)/(D0•D0)     and     γ = (DS•D1)/(D0•D1) + Φ_(D1•D1,DIM)/(D0•D1)
        Φ = γ_(D0•D0,DIM)/(D0•D1) - (DS•D0)/(D0•D1)     and     Φ = γ_(D0•D1,DIM)/(D1•D1) - (DS•D1)/(D1•D1)

   Two equations, two unknowns - solving for the gamma and theta yields:

        0 = γ_(D0•D0,DIM)T_(D1•D1,DIM) - (DS•D0)T_(D1•D1,DIM) - γ_(D0•D1,DIM)T_(D0•D1,DIM) + (DS•D1)T_(D0•D1,DIM)
        0 = γ_((D0•D0,DIM)T_(D1•D1,DIM) - (D0•D1)T_(D0•D1,DIM)) + (DS•D1)T_(D0•D1,DIM) - (DS•D0)T_(D1•D1,DIM)
        γ = ((DS•D0)T_(D1•D1,DIM) - (DS•D1)T_(D0•D1,DIM)) / ((D0•D0)T_(D1•D1,DIM) - (D0•D1)T_(D0•D1,DIM))

        0 = Φ_(D1•D1,DIM)T_(D0•D0,DIM) + (DS•D1)T_(D0•D0,DIM) - Φ_(D0•D1,DIM)T_(D0•D1,DIM) - (DS•D0)T_(D0•D1,DIM)
        0 = Φ_((D1•D1,DIM)T_(D0•D0,DIM) - (D0•D1)T_(D0•D1,DIM)) + (DS•D1)T_(D0•D0,DIM) - (DS•D0)T_(D0•D1,DIM)
        Φ = ((DS•D0)T_(D0•D1,DIM) - (DS•D1)T_(D0•D0,DIM)) / ((D0•D0)T_(D1•D1,DIM) - (D0•D1)T_(D0•D1,DIM))

   If ((D0•D0)T_(D1•D1,DIM) - (D0•D1)T_(D0•D1,DIM)) < ε, the lines are parallel

   However, we know that γ ε [ 0, 1], Φ ε [ 0, 1], generating nine cases:

   [1] γ ε (-∞, 0) | Φ ε (-∞, 0)
      [A] DS•D0 ε ( 0, D0•D0) || γ = DS•D0 / D0•D0 | Φ = 0
           = (P1 - P0 - γ•D0)T_(P1 - P0 - γ•D0,DIM)
           = (DS - γ•D0)T_(DS - γ•D0,DIM)
           = (DS•DS) - 2•γ_(DS•D0,DIM) + γ•γ_(D0•D0,DIM)
           = (DS•DS) + 2_(DS•D0 / D0•D0,DIM)T_(DS•D0,DIM) + (DS•D0 / D0•D0)T_(DS•D0 / D0•D0,DIM)T_(D0•D0,DIM)
           = (DS•DS) - (DS•D0)T_(DS•D0,DIM) / (D0•D0)
           = (DS•DS) - γ_(DS•D0,DIM)
      [B] DS•D0 ε ( D0•D0, ∞) || γ = 1 | Φ = 0
           = (P1 - P0 - D0)T_(P1 - P0 - D0,DIM)
           = (DS - D0)T_(DS - D0,DIM)
           = (DS•DS) - 2_(DS•D0,DIM) + (D0•D0)
      [C] DS•D0 ε (-∞, 0), DS•D1 ε [ 0, ∞) || γ = 0 | Φ = 0
           = (P1 - P0)T_(P1 - P0,DIM)
           = (DS•DS)
      [D] DS•D0 ε (-∞, 0), DS•D1 ε (-DS•D1, 0) || γ = 0 | Φ = -DS•D1 / D1•D1
           = (P1 + Φ•D1 - P0)T_(P1 + Φ•D1 - P0,DIM)
           = (DS + Φ•D1)T_(DS + Φ•D1,DIM)
           = (DS•DS) + 2•Φ_(DS•D1,DIM) + Φ•Φ_(D1•D1,DIM)
           = (DS•DS) + 2•Φ_(DS•D1,DIM) + Φ_(-DS•D1 / D1•D1,DIM)T_(D1•D1,DIM)
           = (DS•DS) + Φ_(DS•D1,DIM)
      [E] DS•D0 ε (-∞, 0), DS•D1 ε (-∞,-D1•D1] || γ = 0 | Φ = 1
           = (P1 + D1 - P0)T_(P1 + D1 - P0,DIM)
           = (DS + D1)T_(DS + D1,DIM)
           = (DS•DS) + 2_(DS•D1,DIM) + (D1•D1)

   [2] γ ε (-∞, 0) | Φ ε [ 0, 1]
      [A] DS•D1 ε [ 0, ∞) || γ = 0 | Φ = 0
           Same as [1C]
      [B] DS•D1 ε (-D1•D1, 0) || γ = 0 | Φ = -DS•D1 / D1•D1
           Same as [1D]
      [C] DS•D1 ε (-∞,-D1•D1) || γ = 0 | Φ = 1
           Same as [1E]

   [3] γ ε (-∞, 0) | Φ ε ( 1, ∞)
      [A] DS•D0 ε [D0•D0 - D0•D1, ∞) || γ = 1 | Φ = 1
           = (P1 + D1 - P0 - D0)T_(P1 + D1 - P0 - D0,DIM)
           = (DS + D1 - D0)T_(DS + D1 - D0,DIM)
           = (DS•DS) + (DS•D1) - (DS•D0) + (DS•D1) + (D1•D1) - (D0•D1) - (DS•D0) - (D0•D1) + (D0•D0)
           = (DS•DS) + 2_(DS•D1,DIM) - 2_(D0•D1,DIM) - 2_(DS•D0,DIM) + (D0•D0) + (D1•D1)
      [B] DS•D0 ε (-D0•D1, D0•D0 - D0•D1) || γ = ((D0•D1) + (DS•D0)) / (D0•D0) | Φ = 1
           = (P1 + D1 - P0 - γ•D0)T_(P1 + D1 - P0 - γ•D0,DIM)
           = (DS + D1 - γ•D0)T_(DS + D1 - γ•D0,DIM)
           = (DS•DS) + 2_(DS•D1,DIM) + (D1•D1) - 2•γ_(D0•D1,DIM) - 2•γ_(DS•D0,DIM) + γ•γ_(D0•D0,DIM)
           = (DS•DS) + 2_(DS•D1,DIM) + (D1•D1) - γ_(2•(D0•D1,DIM) + 2_(DS•D0,DIM) - γ_(D0•D0,DIM))
           = (DS•DS) + 2_(DS•D1,DIM) + (D1•D1) - γ_(2•(D0•D1,DIM) + 2_(DS•D0,DIM) - (D0•D1) - (DS•D0))
           = (DS•DS) + 2_(DS•D1,DIM) + (D1•D1) - γ_((D0•D1,DIM) + (DS•D0))
           = (DS•DS) + 2_(DS•D1,DIM) + (D1•D1) - γ•γ_(D0•D0,DIM)
      [C] DS•D0 ε (-∞,-D0•D1) | DS•D1 ε ( 0, ∞) || γ = 0 | Φ = 0
           Same as [1C]
      [D] DS•D0 ε (-∞,-D0•D1) | DS•D1 ε (-D1•D1, 0) || γ = 0 | Φ = -DS•D1 / D1•D1
           Same as [1D]
      [E] DS•D0 ε (-∞,-D0•D1) | DS•D1 ε (-∞,-D1•D1) || γ = 0 | Φ = 1
           Same as [1E]

   [4] γ ε [ 0, 1] | Φ ε (-∞, 0)
      [A] DS•D0 ε (-∞, 0) || γ = 0 | Φ = 0
           Same as [1C]
      [B] DS•D0 ε [ 0, D0•D0] || γ = DS•D0 / D0•D0 | Φ = 0
           Same as [1A]
      [C] DS•D0 ε ( D0•D0, ∞) || γ = 1 | Φ = 0
           Same as [1B]

   [5] γ ε [ 0, 1] | Φ ε [ 0, 1]
       Distance: The distance value would be || v ||.
         = || v || = v•v = (P1 + Φ•D1 - P0 - γ•D0)T_(P1 + Φ•D1 - P0 - γ•D0,DIM)
         = (DS + Φ•D1 - γ•D0)T_(DS + Φ•D1 - γ•D0,DIM)
         = (DS•DS) + 2•Φ_(DS•D1,DIM) - 2•γ_(DS•D0,DIM) + Φ•Φ_(D1•D1,DIM) - 2•γ•Φ_(D0•D1,DIM) + γ•γ_(D0•D0,DIM)
         = (DS•DS) + Φ_(Φ•(D1•D1,DIM) + 2_(DS•D1,DIM)) + γ_(γ•(D0•D0,DIM) - 2_(DS•D0,DIM)) - 2•γ•Φ_(D0•D1,DIM)

   [6] γ ε [ 0, 1] | Φ ε ( 1, ∞)
      [A] DS•D0 ε [D0•D0 - D0•D1, ∞) || γ = 1 | Φ = 1
           Same as [3A]
      [B] DS•D0 ε (-D0•D1, D0•D0 - D0•D1) || γ = ((D0•D1) + (DS•D0)) / (D0•D0) | Φ = 1
           Same as [3B]
      [C] DS•D0 ε (-∞,-D0•D1) || γ = 0 | Φ = 1
           Same as [1E]

   [7] γ ε ( 1, ∞) | Φ ε (-∞, 0)
      [A] DS•D0 ε (-∞, 0) || γ = 0 | Φ = 0
           Same as [1C]
      [B] DS•D0 ε [ 0, D0•D0) || γ = DS•D0 / D0•D0 | Φ = 0
           Same as [1A]
      [C] DS•D0 ε ( D0•D0, ∞), DS•D1 ε ( D0•D1, ∞) || γ = 1 | Φ = 0
           Same as [1B]
      [D] DS•D0 ε ( D0•D0, ∞), DS•D1 ε ( D0•D1 - D1•D1, D0•D1) || γ = 1 | Φ = ((D0•D1) - (DS•D1)) / (D1•D1)
           = (P1 + Φ•D1 - P0 - D0)T_(P1 + Φ•D1 - P0 - D0,DIM)
           = (DS + Φ•D1 - D0)T_(DS + Φ•D1 - D0,DIM)
           = (DS•DS) + 2•Φ_(DS•D1,DIM) + Φ•Φ_(D1•D1,DIM) - 2•Φ_(D0•D1,DIM) - 2_(DS•D0,DIM) + (D0•D0)
           = (DS•DS) + Φ_(2•(DS•D1,DIM) - 2_(D0•D1,DIM) + Φ_(D1•D1,DIM)) - 2_(DS•D0,DIM) + (D0•D0)
           = (DS•DS) + Φ_((DS•D1,DIM) - (D0•D1)) - 2_(DS•D0,DIM) + (D0•D0)
           = (DS•DS) - Φ•Φ_(D1•D1,DIM) - 2_(DS•D0,DIM) + (D0•D0)
      [E] DS•D0 ε ( D0•D0, ∞), DS•D1 ε (-∞, D0•D1 - D1•D1) || γ = 1 | Φ = 1
           Same as [3A]

   [8] γ ε ( 1, ∞) | Φ ε [ 0, 1]
      [A] DS•D1 ε ( D0•D1, ∞) || γ = 1 | Φ = 0
           Same as [1B]
      [B] DS•D1 ε ( D0•D1 - D1•D1, D0•D1) || γ = 1 | Φ = ((D0•D1) - (DS•D1)) / (D1•D1)
           Same as [7D]
      [C] DS•D1 ε (-∞, D0•D1 - D1•D1) || γ = 1 | Φ = 1
           Same as [3A]

   [9] γ ε ( 1, ∞) | Φ ε ( 1, ∞)
      [A] DS•D0 ε [-D0•D1, D0•D0-D0•D1] || γ = ((D0•D1) + (DS•D0)) / (D0•D0) | Φ = 1
           Same as [3B]
      [B] DS•D0 ε (-∞,-D0•D1) || γ = 0 | Φ = 1
           Same as [1E]
      [C] DS•D0 ε ( D0•D0-D0•D1, ∞), DS•D1 ε ( D0•D1, ∞) || γ = 1 | Φ = 0
           Same as [1B]
      [D] DS•D0 ε ( D0•D0-D0•D1, ∞), DS•D1 ε ( D0•D1 - D1•D1, D0•D1) || γ = 1 | Φ = ((D0•D1) - (DS•D1)) / (D1•D1)
           Same as [7D]
      [E] DS•D0 ε ( D0•D0-D0•D1, ∞), DS•D1 ε (-∞, D0•D1 - D1•D1) || γ = 1 | Φ = 1
           Same as [3A]

   -- Parallel Segments --

   [1] D0•D1 ε (-∞, 0)
      [A] DS•D0 ε ( D0•D0-D0•D1, ∞) || γ = 1 | Φ = 1
           Same as [3A]
      [B] DS•D0 ε ( D0•D0, D0•D0-D0•D1] || γ = 1 | Φ = ((D0•D0) - (DS•D0)) / (D0•D1)
           = (P1 + Φ•D1 - P0 - D0)T_(P1 + Φ•D1 - P0 - D0,DIM)
           = (DS + Φ•D1 - D0)T_(DS + Φ•D1 - D0,DIM)
           = (DS•DS) + 2•Φ_(DS•D1,DIM) + Φ•Φ_(D1•D1,DIM) - 2•Φ_(D0•D1,DIM) - 2_(DS•D0,DIM) + (D0•D0)
           = (DS•DS) + 2•Φ_(DS•D1,DIM) + Φ•Φ_(D1•D1,DIM) - 2_((D0•D0,DIM) - (DS•D0)) - 2_(DS•D0,DIM) + (D0•D0)
           = (DS•DS) + 2•Φ_(DS•D1,DIM) + Φ•Φ_(D1•D1,DIM) - 2_(D0•D0,DIM) + 2_(DS•D0,DIM) - 2_(DS•D0,DIM) + (D0•D0)
           = (DS•DS) + 2•Φ_(DS•D1,DIM) + Φ•Φ_(D1•D1,DIM) - (D0•D0)
      [C] DS•D0 ε ( 0, D0•D0] || γ = DS•D0 / D0•D0 | Φ = 0
           Same as [1A]
      [D] DS•D0 ε (-∞, 0) || γ = 0 | Φ = 0
           Same as [1C]

   [2] D0•D1 ε [ 0, ∞)
      [A] DS•D0 ε [ D0•D0, ∞) || γ = 1 | Φ = 0
           Same as [1B]
      [C] DS•D0 ε (-D0•D1, D0•D0) || γ = 0 | Φ = -DS•D0 / D0•D1
           = (P1 + Φ•D1 - P0)T_(P1 + Φ•D1 - P0,DIM)
           = (DS + Φ•D1)T_(DS + Φ•D1,DIM)
           = (DS•DS) + 2•Φ_(DS•D1,DIM) + Φ•Φ_(D1•D1,DIM)
      [D] DS•D0 ε (-∞,-D0•D1] || γ = 0 | Φ = 1
           Same as [1E]
*/

#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)

#if !defined (ENABLE_RELOAD_GUARD)
    #define TEMPLATE__VECTOR_DIM 4

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define ENABLE_RELOAD_GUARD
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
        #undef TEMPLATE__TYPE_SIZE
        #undef ENABLE_RELOAD_GUARD
    #endif

    #define TEMPLATE__TYPE_SIZE 32
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCNI_VO(tgCO,ClosestSq_PM) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCNI_VO(tgCO,ClosestSq_PM)( VEC_T(1,P) pvT0, VEC_T(1,P) pvT1, VEC_T(1,C) vS0, VEC_T(1,C) vD0, VEC_T(1,C) vS1, VEC_T(1,C) vD1 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS1, vS0 );

    VEC_T(1,C)                          vD0_D0 = FCN_V(tgMH_LSQ)( vD0 );
    VEC_T(1,C)                          vD1_D1 = FCN_V(tgMH_LSQ)( vD1 );
    VEC_T(1,C)                          vD0_D1 = FCN_V(tgMH_DOT)( vD0, vD1 );

    VEC_T(1,C)                          vDS_D0 = FCN_V(tgMH_DOT)( vDS, vD0 );
    VEC_T(1,C)                          vDS_D1 = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( vDS, vD1 ) );
    VEC_T(1,C)                          vDS_DS = FCN_V(tgMH_LSQ)( vDS );

    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( vD0_D0, vD1_D1 );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( vD0_D1, vD0_D1 );
    VEC_T(1,C)                          vDet = FCN_V(tgMH_SUB)( vX0, vX1 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( vD0_D0, vD1_D1 );
    VEC_T(1,C)                          vROOT_EPS = FCN_V(tgMH_SET1)( VAR_K(KTgROOT_EPS) );
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_MUL)( vROOT_EPS, vX2 );
    VEC_T(1,C)                          vZR = FCN_V(tgMH_SET1)( TYPE_K(0) );
    VEC_T(1,C)                          vON = FCN_V(tgMH_SET1)( TYPE_K(1) );

    VEC_T(1)                            vT0, vT1, vK5, vK6, vK7;
    TgBOOL                              bFlag_0, bFlag_1, bFlag_2, bFlag_3, bFlag_4, bFlag_5, bFlag_6, bFlag_7;

    TgPARAM_CHECK( FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Vector)( vD0 ) );
    TgPARAM_CHECK( FCN_V(tgMH_Is_Valid_Point)( vS1 ) && FCN_V(tgMH_Is_Valid_Vector)( vD1 ) );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDet, vX3 ) ))
    {
        VEC_T(1,C)                          vX4 = FCN_V(tgMH_MUL)( vDS_D0, vD1_D1 );
        VEC_T(1,C)                          vX5 = FCN_V(tgMH_MAD)( vDS_D1, vD0_D1, vX4 );
        VEC_T(1,C)                          vX6 = FCN_V(tgMH_MUL)( vDS_D0, vD0_D1 );
        VEC_T(1,C)                          vX7 = FCN_V(tgMH_MAD)( vDS_D1, vD0_D0, vX6 );
        
        vT0 = vX5;
        vT1 = vX7;

        if (TEMPLATE__PRIM_0_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT0, vZR ) ))
        {   /* == Negative region for Segment 0 == */
            if (TEMPLATE__PRIM_1_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT1, vZR ) ))
            {   /* -- Negative region for Segment 1 -- */
                VEC_T(1,C)                          vX9 = FCN_V(tgMH_DIV)( vDS_D1, vD1_D1 );
                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vDS_D0, vZR );

                vT0 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vDS_D0, vD0_D0 ) );
                vT1 = FCN_V(tgMH_SEL)( FCN_V(tgMH_SAT)( vX9 ), vZR, vCMP_0 );
            }
            else if (!TEMPLATE__PRIM_1_CAP_1 || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vT1, vDet ) ))
            {   /* -- Interior region for Segment 1 -- */
                vT0 = vZR;
                vT1 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vDS_D1, vD1_D1 ) );
            }
            else
            {   /* -- Positive region for Segment 1 -- */
                VEC_T(1,C)                          vDE_D0 = FCN_V(tgMH_DOT)( vD0, FCN_V(tgMH_ADD)( vDS, vD1 ) );
                VEC_T(1,C)                          vX9 = FCN_V(tgMH_DIV)( vDS_D1, vD1_D1 );
                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vDE_D0, vZR );

                vT0 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vDE_D0, vD0_D0 ) );
                vT1 = FCN_V(tgMH_SEL)( FCN_V(tgMH_SAT)( vX9 ), vON, vCMP_0 );
            };
        }
        else if (!TEMPLATE__PRIM_0_CAP_1 || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vT0, vDet ) ))
        {   /* == Interior region for Segment 0 == */
            if (TEMPLATE__PRIM_1_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT1, vZR ) ))
            {   /* -- Negative region for Segment 1 -- */
                vT0 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vDS_D0, vD0_D0 ) );
                vT1 = vZR;
            }
            else if (!TEMPLATE__PRIM_1_CAP_1 || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vT1, vDet ) ))
            {   /* -- Interior region for Segment 1 -- */
                vT0 = FCN_V(tgMH_DIV)( vT0, vDet );
                vT1 = FCN_V(tgMH_DIV)( vT1, vDet );
            }
            else
            {   /* -- Positive region for Segment 1 -- */
                VEC_T(1,C)                          vDE_D0 = FCN_V(tgMH_DOT)( vD0, FCN_V(tgMH_ADD)( vDS, vD1 ) );

                vT0 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vDE_D0, vD0_D0 ) );
                vT1 = vON;
            };
        }
        else
        {   /* == Positive region for Segment 0 == */
            VEC_T(1,C)                          vX8 = FCN_V(tgMH_SUB)( vD0, vDS );
            VEC_T(1,C)                          vDF_D1 = FCN_V(tgMH_DOT)( vD1, vX8 );

            if (TEMPLATE__PRIM_1_CAP_0 && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT1, vZR ) ))
            {   /* -- Negative region for Segment 1 -- */
                VEC_T(1,C)                          vX9 = FCN_V(tgMH_DIV)( vDF_D1, vD1_D1 );
                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GT)( vDS_D0, vD0_D0 );

                vT0 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vDS_D0, vD0_D0 ) );
                vT1 = FCN_V(tgMH_SEL)( FCN_V(tgMH_SAT)( vX9 ), vZR, vCMP_0 );
            }
            else if (!TEMPLATE__PRIM_1_CAP_1 || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vT1, vDet ) ))
            {   /* -- Interior region for Segment 1 -- */
                vT0 = vON;
                vT1 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vDF_D1, vD1_D1 ) );
            }
            else
            {   /* -- Positive region for Segment 1 -- */
                VEC_T(1,C)                          vDE_D0 = FCN_V(tgMH_DOT)( vD0, FCN_V(tgMH_ADD)( vDS, vD1 ) );
                VEC_T(1,C)                          vX9 = FCN_V(tgMH_DIV)( vDF_D1, vD1_D1 );
                VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_LE)( vDE_D0, vD0_D0 );

                vT0 = FCN_V(tgMH_SAT)( FCN_V(tgMH_DIV)( vDE_D0, vD0_D0 ) );
                vT1 = FCN_V(tgMH_SEL)( FCN_V(tgMH_SAT)( vX9 ), vON, vCMP_0 );
            };
        };
    }
    else
    {
        /* Linears are parallel */

        VEC_T(1)                            vTest, vDSSQ;

        VEC_T(1,C)                          vDE_D0 = FCN_V(tgMH_ADD)( vDS_D0, vD0_D1 );
        VEC_T(1,C)                          vDF_D1 = FCN_V(tgMH_SUB)( vD0_D1, vDS_D1 );

        vT0 = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );
        vT1 = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );
        vDSSQ = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vD0_D1, vZR ) ))
        {
            /* Both segments have the same direction */
            VEC_T(1,C)                          vNEG_2 = FCN_V(tgMH_SET1)( -TYPE_K(2) );

            bFlag_0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDS_D0, vZR ) );
            bFlag_1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDS_D1, vD1_D1) );
            bFlag_2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDS_D0, vD0_D0 ) );
            bFlag_3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( FCN_V(tgMH_NEG)( vDS_D1 ), vD0_D1) );

            if (TEMPLATE__PRIM_0_CAP_0 && TEMPLATE__PRIM_1_CAP_1 && (bFlag_0 || bFlag_1 ))
            {
                /* First segment origin beyond second segment termination. */
                /* Second segment termination lies behind the first segment. */

                VEC_T(1,C)                          vX4 = FCN_V(tgMH_MAD)( vNEG_2, vDS_D1, vD1_D1 );

                vTest = FCN_V(tgMH_ADD)( vDS_DS, vX4 );
                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDSSQ ) ))
                {
                    vDSSQ = vTest;
                    vT0 = vZR;
                    vT1 = vON;
                };
            };

            if (TEMPLATE__PRIM_0_CAP_1 && TEMPLATE__PRIM_1_CAP_0 && (bFlag_2 || bFlag_3))
            {
                /* First segment termination behind the second segment. */
                /* Second segment origin beyond the first segment. */

                VEC_T(1,C)                          vX4 = FCN_V(tgMH_MAD)( vNEG_2, vDS_D0, vD0_D0 );

                vTest = FCN_V(tgMH_ADD)( vDS_DS, vX4 );
                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDSSQ ) ))
                {
                    vDSSQ = vTest;
                    vT0 = vON;
                    vT1 = vZR;
                };
            };
        }
        else
        {
            /* The segments have opposing direction. */
            bFlag_0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDF_D1, vD1_D1 ) );
            bFlag_1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDE_D0, vD0_D0 ) );
            bFlag_2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LT)(vDS_D0, vZR));
            bFlag_3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LT)(vDS_D1, vZR));

            if (TEMPLATE__PRIM_0_CAP_1 && TEMPLATE__PRIM_1_CAP_1 && (bFlag_0 || bFlag_1))
            {
                /*  First segment termination lies beyond the second segment termination. */
                VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vDS, vD0 );
                VEC_T(1,C)                          vK1 = FCN_V(tgMH_ADD)( vK0, vD1 );

                vTest = FCN_V(tgMH_LSQ)( vK1 );
                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDSSQ ) ))
                {
                    vDSSQ = vTest;
                    vT0 = vON;
                    vT1 = vON;
                };
            };

            if (TEMPLATE__PRIM_0_CAP_0 && TEMPLATE__PRIM_1_CAP_0 && (bFlag_2 || bFlag_3))
            {
                /*  First segment origin lies behind the second segment origin. */

                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDS_DS, vDSSQ ) ))
                {
                    vDSSQ = vDS_DS;
                    vT0 = vZR;
                    vT1 = vZR;
                };
            };
        };

        bFlag_0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vZR, vDS_D1 ) );
        bFlag_1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDS_D1, vD1_D1 ) );

        if ((!TEMPLATE__PRIM_1_CAP_0 || bFlag_0) && (!TEMPLATE__PRIM_1_CAP_1 || bFlag_1))
        {
            /* First segment origin inside second segment. */

            VEC_T(1,C)                          vK0 = FCN_V(tgMH_DIV)( vDS_D1, vD1_D1 );

            vTest = FCN_V(tgMH_SUB)( vDS_DS, FCN_V(tgMH_MUL)( vDS_D1, vK0 ) );
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDSSQ ) ))
            {
                vDSSQ = vTest;
                vT0 = vZR;
                vT1 = vK0;
            };
        };

        bFlag_2 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vZR, vDF_D1 ) );
        bFlag_3 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDF_D1, vD1_D1 ) );
        bFlag_4 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vZR, vDS_D0 ) );
        bFlag_5 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDS_D0, vD0_D0 ) );

        if (TEMPLATE__PRIM_0_CAP_1 && (!TEMPLATE__PRIM_1_CAP_0 || bFlag_2) && (!TEMPLATE__PRIM_1_CAP_1 || bFlag_3))
        {
            /* First segment termination inside second segment. */
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_DIV)( vDF_D1, vD1_D1 );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vK0, vD1 );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( vD0, vDS );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_SUB)( vK2, vK1 );

            vTest = FCN_V(tgMH_LSQ)( vK3 );
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDSSQ ) ))
            {
                vDSSQ = vTest;
                vT0 = vON;
                vT1 = vK0;
            };
        };

        if ((!TEMPLATE__PRIM_0_CAP_0 || bFlag_4) && (!TEMPLATE__PRIM_0_CAP_1 || bFlag_5))
        {
            /* Second segment origin inside first segment. */

            VEC_T(1,C)                          vK0 = FCN_V(tgMH_DIV)( vDS_D0, vD0_D0 );

            vTest = FCN_V(tgMH_SUB)( vDS_DS, FCN_V(tgMH_MUL)( vDS_D0, vK0 ) );
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDSSQ ) ))
            {
                vDSSQ = vTest;
                vT0 = vK0;
                vT1 = vZR;
            };
        };

        bFlag_6 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LT)(vZR, vDE_D0));
        bFlag_7 = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)(vDE_D0, vD0_D0));

        if (TEMPLATE__PRIM_1_CAP_1 && (!TEMPLATE__PRIM_0_CAP_0 || bFlag_6) && (!TEMPLATE__PRIM_0_CAP_1 || bFlag_7))
        {
            /* Second segment termination inside first segment. */

            VEC_T(1,C)                          vK0 = FCN_V(tgMH_DIV)( vDE_D0, vD0_D0 );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vK0, vD0 );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_ADD)( vDS, vD1 );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_SUB)( vK2, vK1 );

            vTest = FCN_V(tgMH_LSQ)( vK3 );
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDSSQ ) ))
            {
                vDSSQ = vTest;
                vT0 = vK0;
                vT1 = vON;
            };
        };

        TgERROR(FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT0, FCN_V(tgMH_SET1)( VAR_K(KTgMAX) ) ) ));
        TgERROR(FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT1, FCN_V(tgMH_SET1)( VAR_K(KTgMAX) ) ) ));
    };

    *pvT0 = vT0;
    *pvT1 = vT1;

    vK5 = FCN_V(tgMH_MUL)( vT0, vD0 );
    vK6 = FCN_V(tgMH_SUB)( vDS, vK5 );
    vK7 = FCN_V(tgMH_MAD)( vT1, vD1, vK6 );

    return (FCN_V(tgMH_LSQ)( vK7 ));
}


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TEMPLATE__PRIM_0_CAP_0 0
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__PRIM_1_CAP_0 0
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
    #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 0
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
    #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 0
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 1
    #define TEMPLATE__PRIM_1 LR
    #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__PRIM_1_CAP_0 0
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
    #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
    #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 1
    #define TEMPLATE__PRIM_1 LR
    #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 1
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__PRIM_1_CAP_0 0
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
    #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 1
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 0
    #define TEMPLATE__PRIM_1 LR
    #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 1
    #define TEMPLATE__PRIM_0 LR
    #define TEMPLATE__PRIM_1_CAP_0 1
    #define TEMPLATE__PRIM_1_CAP_1 1
    #define TEMPLATE__PRIM_1 LR
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */
