#pragma once

#include "resource.h"

/*

   This file contains definitions used by the Hex-Rays decompiler output.
   It has type definitions and convenience macros to make the
   output more readable.

   Copyright (c) 2007-2015 Hex-Rays

*/

#ifndef HEXRAYS_DEFS_H
#define HEXRAYS_DEFS_H

#if defined(__GNUC__)
  typedef          long long ll;
  typedef unsigned long long ull;
  #define __int64 long long
  #define __int16 short
  #define __int8  char
  #define MAKELL(num) num ## LL
  #define FMT_64 "ll"
#elif defined(_MSC_VER)
  typedef          __int64 ll;
  typedef unsigned __int64 ull;
  #define MAKELL(num) num ## i64
  #define FMT_64 "I64"
#elif defined (__BORLANDC__)
  typedef          __int64 ll;
  typedef unsigned __int64 ull;
  #define MAKELL(num) num ## i64
  #define FMT_64 "L"
#else
  #error "unknown compiler"
#endif
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;
typedef ll              int64;
typedef ll              sint64;
typedef ull             uint64;

// Partially defined types. They are used when the decompiler does not know
// anything about the type except its size.
#define _BYTE  uint8
#define _WORD  uint16
#define _DWORD uint32
#define _QWORD uint64
#if !defined(_MSC_VER)
#define _LONGLONG __int128
#endif

// Non-standard boolean types. They are used when the decompiler can not use
// the standard "bool" type because of the size mistmatch but the possible
// values are only 0 and 1. See also 'BOOL' type below.
typedef int8 _BOOL1;
typedef int16 _BOOL2;
typedef int32 _BOOL4;

#ifndef _WINDOWS_
typedef int BOOL;       // uppercase BOOL is usually 4 bytes
#endif
typedef int64 QWORD;
#ifndef __cplusplus
typedef int bool;       // we want to use bool in our C programs
#endif

#define __pure          // pure function: always returns the same value, has no
                        // side effects

// Non-returning function
#if defined(__GNUC__)
#define __noreturn  __attribute__((noreturn))
#else
#define __noreturn  __declspec(noreturn)
#endif


#ifndef NULL
#define NULL 0
#endif

// Some convenience macros to make partial accesses nicer
// first unsigned macros:
#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)         // third word of the object, unsigned
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)

// now signed macros (the same but with sign extension)
#define SLOBYTE(x)   (*((int8*)&(x)))
#define SLOWORD(x)   (*((int16*)&(x)))
#define SLODWORD(x)  (*((int32*)&(x)))
#define SHIBYTE(x)   (*((int8*)&(x)+1))
#define SHIWORD(x)   (*((int16*)&(x)+1))
#define SHIDWORD(x)  (*((int32*)&(x)+1))
#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define SBYTE1(x)   SBYTEn(x,  1)
#define SBYTE2(x)   SBYTEn(x,  2)
#define SBYTE3(x)   SBYTEn(x,  3)
#define SBYTE4(x)   SBYTEn(x,  4)
#define SBYTE5(x)   SBYTEn(x,  5)
#define SBYTE6(x)   SBYTEn(x,  6)
#define SBYTE7(x)   SBYTEn(x,  7)
#define SBYTE8(x)   SBYTEn(x,  8)
#define SBYTE9(x)   SBYTEn(x,  9)
#define SBYTE10(x)  SBYTEn(x, 10)
#define SBYTE11(x)  SBYTEn(x, 11)
#define SBYTE12(x)  SBYTEn(x, 12)
#define SBYTE13(x)  SBYTEn(x, 13)
#define SBYTE14(x)  SBYTEn(x, 14)
#define SBYTE15(x)  SBYTEn(x, 15)
#define SWORD1(x)   SWORDn(x,  1)
#define SWORD2(x)   SWORDn(x,  2)
#define SWORD3(x)   SWORDn(x,  3)
#define SWORD4(x)   SWORDn(x,  4)
#define SWORD5(x)   SWORDn(x,  5)
#define SWORD6(x)   SWORDn(x,  6)
#define SWORD7(x)   SWORDn(x,  7)


// Helper functions to represent some assembly instructions.

#ifdef __cplusplus

// check that unsigned multiplication does not overflow
template<class T> bool is_mul_ok(T count, T elsize)
{
  CASSERT((T)(-1) > 0); // make sure T is unsigned
  if ( elsize  == 0 || count == 0 )
    return true;
  return count <= ((T)(-1)) / elsize;
}

// multiplication that saturates (yields the biggest value) instead of overflowing
// such a construct is useful in "operator new[]"
template<class T> bool saturated_mul(T count, T elsize)
{
  return is_mul_ok(count, elsize) ? count * elsize : T(-1);
}

#include <stddef.h> // for size_t

// memcpy() with determined behavoir: it always copies
// from the start to the end of the buffer
// note: it copies byte by byte, so it is not equivalent to, for example, rep movsd
inline void *qmemcpy(void *dst, const void *src, size_t cnt)
{
  char *out = (char *)dst;
  const char *in = (const char *)src;
  while ( cnt > 0 )
  {
    *out++ = *in++;
    --cnt;
  }
  return dst;
}

// Generate a reference to pair of operands
template<class T>  int16 __PAIR__( int8  high, T low) { return ((( int16)high) << sizeof(high)*8) | uint8(low); }
template<class T>  int32 __PAIR__( int16 high, T low) { return ((( int32)high) << sizeof(high)*8) | uint16(low); }
template<class T>  int64 __PAIR__( int32 high, T low) { return ((( int64)high) << sizeof(high)*8) | uint32(low); }
template<class T> uint16 __PAIR__(uint8  high, T low) { return (((uint16)high) << sizeof(high)*8) | uint8(low); }
template<class T> uint32 __PAIR__(uint16 high, T low) { return (((uint32)high) << sizeof(high)*8) | uint16(low); }
template<class T> uint64 __PAIR__(uint32 high, T low) { return (((uint64)high) << sizeof(high)*8) | uint32(low); }

// rotate left
template<class T> T __ROL__(T value, int count)
{
  const uint nbits = sizeof(T) * 8;

  if ( count > 0 )
  {
    count %= nbits;
    T high = value >> (nbits - count);
    if ( T(-1) < 0 ) // signed value
      high &= ~((T(-1) << count));
    value <<= count;
    value |= high;
  }
  else
  {
    count = -count % nbits;
    T low = value << (nbits - count);
    value >>= count;
    value |= low;
  }
  return value;
}

inline uint8  __ROL1__(uint8  value, int count) { return __ROL__((uint8)value, count); }
inline uint16 __ROL2__(uint16 value, int count) { return __ROL__((uint16)value, count); }
inline uint32 __ROL4__(uint32 value, int count) { return __ROL__((uint32)value, count); }
inline uint64 __ROL8__(uint64 value, int count) { return __ROL__((uint64)value, count); }
inline uint8  __ROR1__(uint8  value, int count) { return __ROL__((uint8)value, -count); }
inline uint16 __ROR2__(uint16 value, int count) { return __ROL__((uint16)value, -count); }
inline uint32 __ROR4__(uint32 value, int count) { return __ROL__((uint32)value, -count); }
inline uint64 __ROR8__(uint64 value, int count) { return __ROL__((uint64)value, -count); }

// carry flag of left shift
template<class T> int8 __MKCSHL__(T value, uint count)
{
  const uint nbits = sizeof(T) * 8;
  count %= nbits;

  return (value >> (nbits-count)) & 1;
}

// carry flag of right shift
template<class T> int8 __MKCSHR__(T value, uint count)
{
  return (value >> (count-1)) & 1;
}

// sign flag
template<class T> int8 __SETS__(T x)
{
  if ( sizeof(T) == 1 )
    return int8(x) < 0;
  if ( sizeof(T) == 2 )
    return int16(x) < 0;
  if ( sizeof(T) == 4 )
    return int32(x) < 0;
  return int64(x) < 0;
}

// overflow flag of subtraction (x-y)
template<class T, class U> int8 __OFSUB__(T x, U y)
{
  if ( sizeof(T) < sizeof(U) )
  {
    U x2 = x;
    int8 sx = __SETS__(x2);
    return (sx ^ __SETS__(y)) & (sx ^ __SETS__(x2-y));
  }
  else
  {
    T y2 = y;
    int8 sx = __SETS__(x);
    return (sx ^ __SETS__(y2)) & (sx ^ __SETS__(x-y2));
  }
}

// overflow flag of addition (x+y)
template<class T, class U> int8 __OFADD__(T x, U y)
{
  if ( sizeof(T) < sizeof(U) )
  {
    U x2 = x;
    int8 sx = __SETS__(x2);
    return ((1 ^ sx) ^ __SETS__(y)) & (sx ^ __SETS__(x2+y));
  }
  else
  {
    T y2 = y;
    int8 sx = __SETS__(x);
    return ((1 ^ sx) ^ __SETS__(y2)) & (sx ^ __SETS__(x+y2));
  }
}

// carry flag of subtraction (x-y)
template<class T, class U> int8 __CFSUB__(T x, U y)
{
  int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
  if ( size == 1 )
    return uint8(x) < uint8(y);
  if ( size == 2 )
    return uint16(x) < uint16(y);
  if ( size == 4 )
    return uint32(x) < uint32(y);
  return uint64(x) < uint64(y);
}

// carry flag of addition (x+y)
template<class T, class U> int8 __CFADD__(T x, U y)
{
  int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
  if ( size == 1 )
    return uint8(x) > uint8(x+y);
  if ( size == 2 )
    return uint16(x) > uint16(x+y);
  if ( size == 4 )
    return uint32(x) > uint32(x+y);
  return uint64(x) > uint64(x+y);
}

#else
// The following definition is not quite correct because it always returns
// uint64. The above C++ functions are good, though.
#define __PAIR__(high, low) (((uint64)(high)<<sizeof(high)*8) | low)
// For C, we just provide macros, they are not quite correct.
#define __ROL__(x, y) __rotl__(x, y)      // Rotate left
#define __ROR__(x, y) __rotr__(x, y)      // Rotate right
#define __CFSHL__(x, y) invalid_operation // Generate carry flag for (x<<y)
#define __CFSHR__(x, y) invalid_operation // Generate carry flag for (x>>y)
#define __CFADD__(x, y) invalid_operation // Generate carry flag for (x+y)
#define __CFSUB__(x, y) invalid_operation // Generate carry flag for (x-y)
#define __OFADD__(x, y) invalid_operation // Generate overflow flag for (x+y)
#define __OFSUB__(x, y) invalid_operation // Generate overflow flag for (x-y)
#endif

// No definition for rcl/rcr because the carry flag is unknown
#define __RCL__(x, y)    invalid_operation // Rotate left thru carry
#define __RCR__(x, y)    invalid_operation // Rotate right thru carry
#define __MKCRCL__(x, y) invalid_operation // Generate carry flag for a RCL
#define __MKCRCR__(x, y) invalid_operation // Generate carry flag for a RCR
#define __SETP__(x, y)   invalid_operation // Generate parity flag for (x-y)

// In the decompilation listing there are some objects declarared as _UNKNOWN
// because we could not determine their types. Since the C compiler does not
// accept void item declarations, we replace them by anything of our choice,
// for example a char:

#define _UNKNOWN char

#ifdef _MSC_VER
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#endif

#endif // HEXRAYS_DEFS_H

/*
   This file has been generated by IDA.
   It contains local type definitions from
   the type library 'DoConfig'
*/

#define __int8 char
#define __int16 short
#define __int64 long long

struct _SCOPETABLE_ENTRY;
struct HDC__;
struct _iobuf;
union _LARGE_INTEGER;

/* 1 */
typedef struct _SCOPETABLE_ENTRY *PSCOPETABLE_ENTRY;

/* 23 */
typedef void *PVOID;

/* 2 */
struct _EH3_EXCEPTION_REGISTRATION
{
  struct _EH3_EXCEPTION_REGISTRATION *Next;
  PVOID ExceptionHandler;
  PSCOPETABLE_ENTRY ScopeTable;
  DWORD TryLevel;
};

/* 3 */
typedef struct _EH3_EXCEPTION_REGISTRATION EH3_EXCEPTION_REGISTRATION;

/* 4 */
typedef struct _EH3_EXCEPTION_REGISTRATION *PEH3_EXCEPTION_REGISTRATION;

/* 5 */
struct CPPEH_RECORD
{
  DWORD old_esp;
  EXCEPTION_POINTERS *exc_ptr;
  struct _EH3_EXCEPTION_REGISTRATION registration;
};

/* 6 */
struct _SCOPETABLE_ENTRY
{
  int EnclosingLevel;
  void *FilterFunc;
  void *HandlerFunc;
};

/* 8 */
typedef HDC__ *HDC;

/* 10 */
typedef int BOOL;

/* 14 */
typedef unsigned __int8 BYTE;

/* 18 */
typedef char CHAR;

/* 17 */
typedef CHAR *LPSTR;

/* 19 */
typedef unsigned __int16 WORD;

/* 20 */
typedef BYTE *LPBYTE;

/* 21 */
typedef void *HANDLE;

/* 27 */
typedef void *LPVOID;

/* 29 */
typedef unsigned int UINT;

/* 33 */
typedef _iobuf FILE;

/* 36 */
typedef _LARGE_INTEGER LARGE_INTEGER;

/* 39 */
typedef __int64 LONGLONG;

/* 41 */
enum MACRO_USER_PROFILE
{
  USER_PROFILE_PARMNUM = 52,
  USER_HOME_DIR_DRIVE_PARMNUM = 53,
  USER_NAME_INFOLEVEL = 1001,
  USER_PASSWORD_INFOLEVEL = 1003,
  USER_PASSWORD_AGE_INFOLEVEL = 1004,
  USER_PRIV_INFOLEVEL = 1005,
  USER_HOME_DIR_INFOLEVEL = 1006,
  USER_COMMENT_INFOLEVEL = 1007,
  USER_FLAGS_INFOLEVEL = 1008,
  USER_SCRIPT_PATH_INFOLEVEL = 1009,
  USER_AUTH_FLAGS_INFOLEVEL = 1010,
  USER_FULL_NAME_INFOLEVEL = 1011,
  USER_USR_COMMENT_INFOLEVEL = 1012,
  USER_PARMS_INFOLEVEL = 1013,
  USER_WORKSTATIONS_INFOLEVEL = 1014,
  USER_LAST_LOGON_INFOLEVEL = 1015,
  USER_LAST_LOGOFF_INFOLEVEL = 1016,
  USER_ACCT_EXPIRES_INFOLEVEL = 1017,
  USER_MAX_STORAGE_INFOLEVEL = 1018,
  USER_UNITS_PER_WEEK_INFOLEVEL = 1019,
  USER_LOGON_HOURS_INFOLEVEL = 1020,
  USER_PAD_PW_COUNT_INFOLEVEL = 1021,
  USER_NUM_LOGONS_INFOLEVEL = 1022,
  USER_LOGON_SERVER_INFOLEVEL = 1023,
  USER_COUNTRY_CODE_INFOLEVEL = 1024,
  USER_CODE_PAGE_INFOLEVEL = 1025,
  USER_PRIMARY_GROUP_INFOLEVEL = 1051,
};

/* 44 */
struct Config_Data_File
{
  char proof[32];
  char font_name[64];
  int move_button_mode;
  int attack_button_mode;
  int ok_button_mode;
  int display_mode;
  int joystick_mode;
  int joystick_button[8];
};

