/* +++ deprecated +++ */

#if defined(BME_set_MutexType)
  #error BME_set_MutexType is no longer here, it will be picked automaticly. \
    if you want BME to be implemented without any library, define BME_set_NoLibrary 1. \
    also define BME_set_Sleep
#endif
#if defined(BME_set_Backend)
  #error BME_set_Backend is no longer used. BME will use __platform defines.
#endif

/* --- deprecated --- */

#ifndef BME_set_Prefix
  #error ifndef BME_set_Prefix
#endif

#ifndef BME_set_AreWeInsideStruct
  #define BME_set_AreWeInsideStruct 0
#endif

#ifndef BME_set_Pad
  #define BME_set_Pad 0
#endif

#ifndef BME_set_CountLockFail
  #define BME_set_CountLockFail 0
#endif

#ifndef BME_set_Language
  #if BME_set_AreWeInsideStruct
    #define BME_set_Language 1
  #else
    #define BME_set_Language 0
  #endif
#endif

#ifndef BME_set_NoLibrary
  #if defined(__platform_libc)
    #define BME_set_NoLibrary 0
  #else
    #define BME_set_NoLibrary 1
  #endif
#endif

#ifndef BME_set_Sleep
  #define BME_set_Sleep 1
#endif

#ifndef BME_set_StructFormat
  #if BME_set_Language == 0
    #define BME_set_StructFormat 0
  #elif BME_set_Language == 1
    #define BME_set_StructFormat 1
  #else
    #error ?
  #endif
#endif

#ifndef BME_set_LockValue
  #define BME_set_LockValue 0
#endif
#if BME_set_LockValue != 0 && BME_set_LockValue != 1
  #error ?
#endif

#define _BME_P(p) CONCAT3(BME_set_Prefix,_,p)

#if BME_set_StructFormat == 0
  #define BME_StructBegin(n) typedef struct{
  #define BME_StructEnd(n) }n;
#elif BME_set_StructFormat == 1
  #define BME_StructBegin(n) struct n{
  #define BME_StructEnd(n) };
#else
  #error ?
#endif

#if BME_set_Language == 0
  #define _BME_POFTWBIT(p0) _BME_P(p0)
  #define _BME_SOFTWBIT static
  #define _BME_PTFF t
  #define _BME_PTFFC _BME_PTFF,
  #define _BME_DTFF _BME_P(t) *_BME_PTFF
  #define _BME_DTFFC _BME_DTFF,
  #define _BME_GetType _BME_PTFF
  #define _BME_OCITFFE ,
#elif BME_set_Language == 1
  #define _BME_POFTWBIT(p0) p0
  #define _BME_SOFTWBIT
  #define _BME_PTFF
  #define _BME_PTFFC
  #define _BME_DTFF
  #define _BME_DTFFC
  #define _BME_GetType this
  #define _BME_OCITFFE
#endif

#include "internal/rest.h"

#undef _BME_POFTWBIT
#undef _BME_SOFTWBIT
#undef _BME_PTFF
#undef _BME_PTFFC
#undef _BME_DTFF
#undef _BME_DTFFC
#undef _BME_GetType
#undef _BME_OCITFFE

#undef BME_StructEnd
#undef BME_StructBegin

#undef _BME_P

#ifdef BME_set_Conditional
  #undef BME_set_Conditional
#endif
#undef BME_set_LockValue
#undef BME_set_StructFormat
#undef BME_set_Sleep
#undef BME_set_NoLibrary
#undef BME_set_Language
#ifdef BME_set_CountLockFailGlobal
  #undef BME_set_CountLockFailGlobal
#endif
#undef BME_set_CountLockFail
#undef BME_set_Pad
#undef BME_set_AreWeInsideStruct
#undef BME_set_Prefix
