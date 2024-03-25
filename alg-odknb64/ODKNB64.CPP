//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Copyright © 2000-2002 OtDiatlovaOU™, RU, KZ. All Rights Reserved.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
//  МОДУЛЬ:   ODKNB64.cpp
//
//  НАЗНАЧЕНИЕ:
//      Содержит функции класса ODKNB64.
//
#include <ODKNB64.h> // Содержит Класс ODKNB64 64 битного целого числа.

#ifndef OD_NO_NAMESPACE
namespace OtDiatlovaOU {
#endif

// Глобальные переменные для модуля:
//char mszODMessage[]="\"Module: ODKNB64.cpp\"";// Для указания места ошибки.

// Функции операторы: + - * / % == != <= < >= > += -= *= /= %= << >>  = [] () ->
#pragma warn -rvl
// Манипулирование битами с присвоением операторы: |= ^= &= <<= >>=
// Побитовый сдвиг влево <<=:
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator<<=(kODKNB64& KU64)
{  asm{
      mov   cx, [edx]     // Количество сдвигов.
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigPrL// <32.
      mov   edx, [eax]    // Копирует мл. в ст.
      shl   edx, cl
      mov  [eax+4], edx   // >=32.
      mov   dword ptr[eax], 0
      jmp   MVwh_op_SdvigPrL
 M2_op_SdvigPrL:
      mov   edx, [eax]    //
      shld [eax+4],edx, cl
      shl   edx, cl
      mov  [eax], edx     // Копирует в буфер возврата.
 MVwh_op_SdvigPrL:
   }
}
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator<<=(NB32 dwMen)
{  asm{
      mov   cx, dx        // Количество сдвигов.
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigPrL2// <32.
      mov   edx, [eax]    // Копирует мл. в ст.
      shl   edx, cl
      mov  [eax+4], edx   // >=32.
      mov   dword ptr[eax],   0
      jmp   MVwh_op_SdvigPrL2
 M2_op_SdvigPrL2:
      mov   edx, [eax]    //
      shld [eax+4],edx, cl
      shl   edx, cl
      mov  [eax], edx     // Копирует в буфер возврата.
 MVwh_op_SdvigPrL2:
   }
}
#pragma argsused
NB32& __fastcall operator<<=(NB32& dwMen, kODKNB64& KU64)
{  asm{
      mov   cx, [edx]     // Количество сдвигов.
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigPrL3 // <32.
      mov   dword ptr[eax], 0// >=32.
      jmp   MVwh_op_SdvigPrL3
 M2_op_SdvigPrL3:
      shl   dword ptr[eax], cl
 MVwh_op_SdvigPrL3:
   }
}
// Побитовый сдвиг вправо >>=:
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator>>=(kODKNB64& KU64)
{  asm{
      mov   cx, [edx]     // Количество сдвигов.
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigPrP  // <32.
      mov   edx, [eax+4]  // Копирует ст. в мл. в буфер возврата.
      shr   edx, cl
      mov  [eax], edx     // >=32.
      mov   dword ptr[eax+4],   0
      jmp   MVwh_op_SdvigPrP
 M2_op_SdvigPrP:
      mov   edx, [eax+4]//
      shrd [eax],edx, cl
      shr   edx, cl
      mov  [eax+4], edx // Копирует в буфер возврата.
 MVwh_op_SdvigPrP:
   }
}
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator>>=(NB32 dwMen)
{  asm{
      mov   cx, dx       // Количество сдвигов.
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigPrP2  // <32.
      mov   edx, [eax+4]  // Копирует ст. в мл. в буфер возврата.
      shr   edx, cl
      mov  [eax], edx     // >=32.
      mov   dword ptr[eax+4],   0
      jmp   MVwh_op_SdvigPrP2
 M2_op_SdvigPrP2:
      mov   edx, [eax+4]//
      shrd [eax],edx, cl
      shr   edx, cl
      mov  [eax+4], edx // Копирует в буфер возврата.
 MVwh_op_SdvigPrP2:
   }
}
#pragma argsused
NB32& __fastcall operator>>=(NB32& dwMen, kODKNB64& KU64)
{  asm{
      mov   cx, [edx]     // Количество сдвигов.
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigPrP3 // <32.
      mov   dword ptr[eax],   0 // >=32.=0.
      jmp   MVwh_op_SdvigPrP3
 M2_op_SdvigPrP3:
      shr   dword ptr[eax], cl// Копирует в буфер возврата.
 MVwh_op_SdvigPrP3:
   }
}
// Манипулирование битами операторы: ~ & | ^ << >>
// Побитовое НЕТ ~:
ODKNB64 __fastcall ODKNB64::operator~()
{  asm{
      mov   ecx, [edx+4]
      not   ecx
      mov  [eax+4], ecx
      mov   ecx, [edx]
      not   ecx
      mov  [eax], ecx
   }
}
// Побитовое ИЛИ |:
#pragma argsused
ODKNB64 __fastcall ODKNB64::operator|(kODKNB64& KU64) const
{  asm{
      mov   ebx, [edx+4]
      or    ebx, [ecx+4]
      mov  [eax+4], ebx
      mov   ebx, [edx]
      or    ebx, [ecx]
      mov  [eax], ebx
   }
}
#pragma argsused
ODKNB64 __fastcall ODKNB64::operator|(NB32 dwMen) const
{  asm{
      or    ecx, [edx]
      mov  [eax], ecx
      mov   ecx, [edx+4]
      mov  [eax+4], ecx
   }
}
#pragma argsused
ODKNB64 __fastcall operator|(NB32 dwMen, kODKNB64& KU64)
{  asm{
      or      edx, [ecx]
      mov  [eax], edx
      mov   edx, [ecx+4]
      mov  [eax+4], edx
   }
}
// Побитовое исключающее ИЛИ ^:
#pragma argsused
ODKNB64 __fastcall ODKNB64::operator^(kODKNB64& KU64) const
{  asm{
      mov   ebx, [edx+4]
      xor   ebx, [ecx+4]
      mov  [eax+4], ebx
      mov   ebx, [edx]
      xor   ebx, [ecx]
      mov  [eax], ebx
   }
}
#pragma argsused
ODKNB64 __fastcall ODKNB64::operator^(NB32 dwMen) const
{  asm{
      xor   ecx, [edx]
      mov  [eax], ecx
      mov   ecx, [edx+4]
      mov  [eax+4], ecx
   }
}
#pragma argsused
ODKNB64 __fastcall operator^(NB32 dwMen, kODKNB64& KU64)
{  asm{
      xor   edx, [ecx]
      mov  [eax], edx
      mov   edx, [ecx+4]
      mov  [eax+4], edx
   }
}
// Побитовое И &:
#pragma argsused
ODKNB64 __fastcall ODKNB64::operator&(kODKNB64& KU64) const
{  asm{
      mov   ebx, [edx+4]
      and   ebx, [ecx+4]
      mov  [eax+4], ebx
      mov   ebx, [edx]
      and   ebx, [ecx]
      mov  [eax], ebx
   }
}
#pragma argsused
ODKNB64 __fastcall ODKNB64::operator&(NB32 dwMen) const
{  asm{
      and   ecx, [edx]
      mov  [eax], ecx
      mov   ecx, [edx+4]
      mov  [eax+4], ecx
   }
}
#pragma argsused
ODKNB64 __fastcall operator&(NB32 dwMen, kODKNB64& KU64)
{  asm{
      and   edx, [ecx]
      mov  [eax], edx
      mov   edx, [ecx+4]
      mov  [eax+4], edx
   }
}
// Побитовый сдвиг влево <<:
#pragma argsused
ODKNB64 __fastcall ODKNB64::operator<<(kODKNB64& KU64) const
{  asm{
      mov   cx, [ecx]     // Количество сдвигов.
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigL  // <32.
      mov   ebx, [edx]    // Копирует мл. в ст. в буфер возврата.
      mov  [eax+4], ebx   // >=32.
      mov   dword ptr[eax],   0
      shl   dword ptr[eax+4], cl
      jmp   MVwh_op_SdvigL
 M2_op_SdvigL:
      mov   ebx, [edx+4]  // Копирует в буфер возврата.
      mov  [eax+4], ebx   //
      mov   ebx, [edx]    //
      shld [eax+4],ebx, cl
      shl   ebx, cl
      mov  [eax], ebx     // Копирует в буфер возврата.
 MVwh_op_SdvigL:
   }
}
#pragma argsused
ODKNB64 __fastcall ODKNB64::operator<<(NB32 dwMen) const
{  asm{
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigL2 // <32.
      mov   ebx, [edx]    // Копирует мл. в ст. в буфер возврата.
      mov  [eax+4], ebx   // >=32.
      mov   dword ptr[eax],   0
      shl   dword ptr[eax+4], cl
      jmp   MVwh_op_SdvigL2
 M2_op_SdvigL2:
      mov   ebx, [edx+4]  // Копирует в буфер возврата.
      mov  [eax+4], ebx   //
      mov   ebx, [edx]    //
      shld [eax+4],ebx, cl
      shl   ebx, cl
      mov  [eax], ebx     // Копирует в буфер возврата.
 MVwh_op_SdvigL2:
   }
}
#pragma argsused
ODKNB64 __fastcall operator<<(NB32 dwMen, kODKNB64& KU64)
{  asm{
      mov   cx, [ecx]     // Количество сдвигов.
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigL3 // <32.
      mov  [eax+4], edx   // >=32.// Копирует мл. в ст. в буфер возврата.
      mov   dword ptr[eax],   0
      shl   dword ptr[eax+4], cl
      jmp   MVwh_op_SdvigL3
 M2_op_SdvigL3:
      mov   dword ptr[eax+4], 0// Копирует в буфер возврата.
      shld [eax+4],edx, cl
      shl   edx, cl
      mov  [eax], edx          // Копирует в буфер возврата.
 MVwh_op_SdvigL3:
   }
}
// Побитовый сдвиг вправо >>:
#pragma argsused
ODKNB64 __fastcall ODKNB64::operator>>(kODKNB64& KU64) const
{  asm{
      mov   cx, [ecx]     // Количество сдвигов.
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigP  // <32.
      mov   ebx, [edx+4]  // Копирует ст. в мл. в буфер возврата.
      mov  [eax], ebx     // >=32.
      mov   dword ptr[eax+4],   0
      shr   dword ptr[eax], cl
      jmp   MVwh_op_SdvigP
 M2_op_SdvigP:
      mov   ebx, [edx]  // Копирует в буфер возврата.
      mov  [eax], ebx   //
      mov   ebx, [edx+4]//
      shrd [eax],ebx, cl
      shr   ebx, cl
      mov  [eax+4], ebx // Копирует в буфер возврата.
 MVwh_op_SdvigP:
   }
}
#pragma argsused
ODKNB64 __fastcall ODKNB64::operator>>(NB32 dwMen) const
{  asm{
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigP2 // <32.
      mov   ebx, [edx+4]  // Копирует ст. в мл. в буфер возврата.
      mov  [eax], ebx   // >=32.
      mov   dword ptr[eax+4],   0
      shr   dword ptr[eax], cl
      jmp   MVwh_op_SdvigP2
 M2_op_SdvigP2:
      mov   ebx, [edx]  // Копирует в буфер возврата.
      mov  [eax], ebx   //
      mov   ebx, [edx+4]//
      shrd [eax],ebx, cl
      shr   ebx, cl
      mov  [eax+4], ebx     // Копирует в буфер возврата.
 MVwh_op_SdvigP2:
   }
}
#pragma argsused
ODKNB64 __fastcall operator>>(NB32 dwMen, kODKNB64& KU64)
{  asm{
      mov   cx, [ecx]     // Количество сдвигов.
      btr   cx, 5         // Сдвиг 32 бита = мл. в ст.
      jnc   M2_op_SdvigP3 // <32.
      mov   dword ptr[eax],   0 // >=32.=0.
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_SdvigP3
 M2_op_SdvigP3:
      mov   dword ptr[eax+4], 0// Копирует в буфер возврата.
      shr   edx, cl
      mov  [eax], edx          // Копирует в буфер возврата.
 MVwh_op_SdvigP3:
   }
}

// Отношений операторы: == != <= < >= >
// Равно:
#pragma argsused
bool __fastcall ODKNB64::operator==(kODKNB64& KU64) const
{  asm{
      mov   ecx, [edx+4]
      cmp   [eax+4], ecx  // Сравнивает старшие двойные слова.
      jne   M1_op_R
      mov   ecx, [edx]
      cmp   [eax], ecx    // Сравнивает младшие двойные слова.
 M1_op_R:
      sete  al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall ODKNB64::operator==(NB32 dwMen) const
{  asm{
      cmp   dword ptr[eax+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_R2
      cmp   [eax], edx    // Сравнивает младшие двойные слова.
 M1_op_R2:
      sete  al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall operator==(NB32 dwMen, kODKNB64& KU64)
{  asm{
      cmp   dword ptr[edx+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_R3
      cmp   [edx], eax    // Сравнивает младшие двойные слова.
 M1_op_R3:
      sete  al            // Устанавливает байт возврата.
   }
}
// Не равно:
#pragma argsused
bool __fastcall ODKNB64::operator!=(kODKNB64& KU64) const
{  asm{
      mov   ecx, [edx+4]
      cmp   [eax+4], ecx  // Сравнивает старшие двойные слова.
      jne   M1_op_NR
      mov   ecx, [edx]
      cmp   [eax], ecx    // Сравнивает младшие двойные слова.
 M1_op_NR:
      setne al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall ODKNB64::operator!=(NB32 dwMen) const
{  asm{
      cmp   dword ptr[eax+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_NR2
      cmp   [eax], edx    // Сравнивает младшие двойные слова.
 M1_op_NR2:
      setne  al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall operator!=(NB32 dwMen, kODKNB64& KU64)
{  asm{
      cmp   dword ptr[edx+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_NR3
      cmp   [edx], eax    // Сравнивает младшие двойные слова.
 M1_op_NR3:
      setne  al            // Устанавливает байт возврата.
   }
}
// Меньше или равно:
#pragma argsused
bool __fastcall ODKNB64::operator<=(kODKNB64& KU64) const
{  asm{
      mov   ecx, [edx+4]
      cmp   [eax+4], ecx  // Сравнивает старшие двойные слова.
      jne   M1_op_MR
      mov   ecx, [edx]
      cmp   [eax], ecx    // Сравнивает младшие двойные слова.
 M1_op_MR:
      setbe al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall ODKNB64::operator<=(NB32 dwMen) const
{  asm{
      cmp   dword ptr[eax+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_MR2
      cmp   [eax], edx    // Сравнивает младшие двойные слова.
 M1_op_MR2:
      setbe  al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall operator<=(NB32 dwMen, kODKNB64& KU64)
{  asm{
      cmp   dword ptr[edx+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_MR3
      cmp   [edx], eax    // Сравнивает младшие двойные слова.
 M1_op_MR3:
      setae  al            // Устанавливает байт возврата.
   }
}
// Меньше:
#pragma argsused
bool __fastcall ODKNB64::operator<(kODKNB64& KU64) const
{  asm{
      mov   ecx, [edx+4]
      cmp   [eax+4], ecx  // Сравнивает старшие двойные слова.
      jne   M1_op_M
      mov   ecx, [edx]
      cmp   [eax], ecx    // Сравнивает младшие двойные слова.
 M1_op_M:
      setb  al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall ODKNB64::operator<(NB32 dwMen) const
{  asm{
      cmp   dword ptr[eax+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_M2
      cmp   [eax], edx    // Сравнивает младшие двойные слова.
 M1_op_M2:
      setb  al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall operator<(NB32 dwMen, kODKNB64& KU64)
{  asm{
      cmp   dword ptr[edx+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_M3
      cmp   [edx], eax    // Сравнивает младшие двойные слова.
 M1_op_M3:
      seta  al            // Устанавливает байт возврата.
   }
}
// Больше или равно:
#pragma argsused
bool __fastcall ODKNB64::operator>=(kODKNB64& KU64) const
{  asm{
      mov   ecx, [edx+4]
      cmp   [eax+4], ecx  // Сравнивает старшие двойные слова.
      jne   M1_op_BR
      mov   ecx, [edx]
      cmp   [eax], ecx    // Сравнивает младшие двойные слова.
 M1_op_BR:
      setae al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall ODKNB64::operator>=(NB32 dwMen) const
{  asm{
      cmp   dword ptr[eax+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_BR2
      cmp   [eax], edx    // Сравнивает младшие двойные слова.
 M1_op_BR2:
      setae  al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall operator>=(NB32 dwMen, kODKNB64& KU64)
{  asm{
      cmp   dword ptr[edx+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_BR3
      cmp   [edx], eax    // Сравнивает младшие двойные слова.
 M1_op_BR3:
      setbe  al            // Устанавливает байт возврата.
   }
}
// Больше:
#pragma argsused
bool __fastcall ODKNB64::operator>(kODKNB64& KU64) const
{  asm{
      mov   ecx, [edx+4]
      cmp   [eax+4], ecx  // Сравнивает старшие двойные слова.
      jne   M1_op_B
      mov   ecx, [edx]
      cmp   [eax], ecx    // Сравнивает младшие двойные слова.
 M1_op_B:
      seta al             // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall ODKNB64::operator>(NB32 dwMen) const
{  asm{
      cmp   dword ptr[eax+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_B2
      cmp   [eax], edx    // Сравнивает младшие двойные слова.
 M1_op_B2:
      seta  al            // Устанавливает байт возврата.
   }
}
#pragma argsused
bool __fastcall operator>(NB32 dwMen, kODKNB64& KU64)
{  asm{
      cmp   dword ptr[edx+4], 0    // Сравнивает старшие двойные слова.
      jne   M1_op_B3
      cmp   [edx], eax    // Сравнивает младшие двойные слова.
 M1_op_B3:
      setb  al            // Устанавливает байт возврата.
   }
}
// Математические операторы: += + ++ -= - -- *= * /= / %= %
// Плюс: += + ++
// Сложение с присвоением результата: +=
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator+=(kODKNB64& KU64)
{  asm{// При переполнении результат максимальный:
      mov   ecx, [edx]
      add   [eax], ecx
      mov   ecx, [edx+4]
      adc   [eax+4], ecx
      jnc    M1_op_PlusPr
      or      dword ptr[eax],   0xFFFFFFFF
      or      dword ptr[eax+4], 0xFFFFFFFF
 M1_op_PlusPr:
   }
}
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator+=(NB32 dwMen)
{  asm{// При переполнении результат максимальный:
      add   [eax], edx
      adc   dword ptr[eax+4], 0
      jnc   M1_op_PlusPr2
      or      dword ptr[eax],   0xFFFFFFFF
      or      dword ptr[eax+4], 0xFFFFFFFF
 M1_op_PlusPr2:
   }
}
#pragma argsused
NB32& __fastcall operator+=(NB32& dwMen, kODKNB64& KU64P)
{  asm{// При переполнении результат максимальный:
      cmp   dword ptr[edx+4], 0
      jne   M1_op_PlusPr3
      mov   ecx, [edx]
      add   [eax], ecx
      jnc   M2_op_PlusPr3
 M1_op_PlusPr3:
      or      dword ptr[eax], 0xFFFFFFFF
 M2_op_PlusPr3:
   }
}
// Сложение: +
#pragma argsused
ODKNB64 __fastcall operator+(kODKNB64& KU64L, kODKNB64& KU64P)
{  asm{// При переполнении результат максимальный:
      mov   ebx, [edx]
      add   ebx, [ecx]
      mov   [eax], ebx
      mov   ebx, [edx+4]
      adc   ebx, [ecx+4]
      mov   [eax+4], ebx
      jnc   M1_op_Plus
      or      dword ptr[eax],   0xFFFFFFFF
      or      dword ptr[eax+4], 0xFFFFFFFF
 M1_op_Plus:
   }
}
#pragma argsused
ODKNB64 __fastcall operator+(kODKNB64& KU64L, NB32 dwMen)
{  asm{// При переполнении результат максимальный:
      add   ecx, [edx]
      mov   [eax], ecx
      mov   ecx, 0
      adc   ecx, [edx+4]
      mov   [eax+4], ecx
      jnc   M1_op_Plus2
      or      dword ptr[eax],   0xFFFFFFFF
      or      dword ptr[eax+4], 0xFFFFFFFF
 M1_op_Plus2:
   }
}
#pragma argsused
ODKNB64 __fastcall operator+(NB32 dwMen, kODKNB64& KU64P)
{  asm{// При переполнении результат максимальный:
      add   edx, [ecx]
      mov   [eax], edx
      mov   edx, 0
      adc   edx, [ecx+4]
      mov   [eax+4], edx
      jnc   M1_op_Plus3
      or      dword ptr[eax],   0xFFFFFFFF
      or      dword ptr[eax+4], 0xFFFFFFFF
 M1_op_Plus3:
   }
}
//#pragma warn .rvl
// Пред и пост инкримент выполняются как пред инкремент: ++
ODKNB64& __fastcall operator++(ODKNB64& KU64L)
{   if(++KU64L.EK_1)return KU64L;// Если переполнение.
   else if(++KU64L.EK_2)return KU64L;// Если переполнение.
   else KU64L.EK_2=KU64L.EK_1=0xFFFFFFFF; return KU64L;
}
// Минус: -= - --  // При разнице меньше нуля результат = 0:
// Вычитание с присвоением результата: -=
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator-=(kODKNB64& KU64)
{  asm{// При разнице меньше нуля результат = 0:
      mov   ebx, [edx]
      sub   [eax], ebx
      mov   ebx, [edx+4]
      sbb   [eax+4], ebx
      jnc    M1_op_MinPr
      xor   ebx, ebx
      mov   [eax],   ebx
      mov   [eax+4], ebx
 M1_op_MinPr:
   }
}
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator-=(NB32 dwMen)
{  asm{// При разнице меньше нуля результат = 0:
      sub   [eax], edx
      sbb   dword ptr[eax+4], 0
      jnc   M1_op_MinPr2
      mov   dword ptr[eax],   0
      mov   dword ptr[eax+4], 0
 M1_op_MinPr2:
   }
}
#pragma argsused
NB32& __fastcall operator-=(NB32& dwMen, kODKNB64& KU64P)
{  asm{// При разнице меньше нуля результат = 0:
      cmp   dword ptr[edx+4], 0
      jne   M1_op_MinPr3
      mov   ebx, [edx]
      sub   [eax], ebx
      jnc   M2_op_MinPr3
 M1_op_MinPr3:
      mov      dword ptr[eax], 0
 M2_op_MinPr3:
   }
}
// Сложение: +
#pragma argsused
ODKNB64 __fastcall operator-(kODKNB64& KU64L, kODKNB64& KU64P)
{  asm{// При разнице меньше нуля результат = 0:
      mov   ebx, [edx]
      sub   ebx, [ecx]
      mov   [eax], ebx
      mov   ebx, [edx+4]
      sbb   ebx, [ecx+4]
      mov   [eax+4], ebx
      jnc   M1_op_Min
      xor   ebx, ebx
      mov   [eax],   ebx
      mov   [eax+4], ebx
 M1_op_Min:
   }
}
#pragma argsused
ODKNB64 __fastcall operator-(kODKNB64& KU64L, NB32 dwMen)
{  asm{// При разнице меньше нуля результат = 0:
      mov   ebx, [edx]
      sub   ebx, ecx
      mov   [eax], ebx
      mov   ebx, [edx+4]
      sbb   ebx, 0
      mov   [eax+4], ebx
      jnc   M1_op_Min2
      xor   ebx, ebx
      mov   [eax],   ebx
      mov   [eax+4], ebx
 M1_op_Min2:
   }
}
#pragma argsused
ODKNB64 __fastcall operator-(NB32 dwMen, kODKNB64& KU64P)
{  asm{// При разнице меньше нуля результат = 0:
      cmp   dword ptr[ecx+4], 0
      jne   M1_op_Min3
      sub   edx, [ecx]
      jc    M1_op_Min3
      mov   [eax], edx
      mov   dword ptr[eax+4], 0
      jmp   M2_op_Min3
 M1_op_Min3:
      mov   dword ptr[eax],   0
      mov   dword ptr[eax+4], 0
 M2_op_Min3:
   }
}
// Пред и пост декримент выполняются как пред декримент: --
#pragma argsused
ODKNB64& __fastcall operator--(ODKNB64& KU64)
{  asm{// При разнице меньше нуля результат = 0:
      dec   dword ptr[eax]
      cmp   dword ptr[eax], 0xFFFFFFFF
      jne   M1_op_Dec
      dec   dword ptr[eax+4]
      cmp   dword ptr[eax+4], 0xFFFFFFFF
      jne   M1_op_Dec
      mov   dword ptr[eax],   0
      mov   dword ptr[eax+4], 0
 M1_op_Dec:
   }
}
// Умножить: *= *  // При переполнении результат максимальный:
// Умножение с присвоением результата: *=
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator*=(kODKNB64& KU64)
{  asm{// При переполнении результат максимальный:
      mov   edi, eax     // Адрес 1го множителя в индексный регистр "приёмник".
      cmp   dword ptr[eax+4], 0
      je    M0_op_YmnPr
      cmp   dword ptr[edx+4], 0
      jne   M1_op_YmnPr
 M0_op_YmnPr:
      mov   ecx, [eax]   // Копия 1го сомножителя (младшая).
      mov   ebx, [eax+4] // Копия 1го сомножителя (старшая).
      mov   esi, edx     // Адрес 2го множителя в индексный регистр "источник".
      // Как при умножении в "столбик".
      mov   eax, ecx     // Загружает для умножения младшую часть.
      mul   dword ptr[esi]// Умножает eax на число по адресу esi, старшая часть в edx.
      mov   [edi], eax   // Младшую часть в 1й сомножитель.
      mov   [edi+4], edx // Старшую часть в 1й сомножитель.
      mov   eax, ebx     // Загружает для умножения старшую часть.
      mul   dword ptr[esi]// Умножает eax на число по адресу esi, старшая часть в edx.
      jc    M1_op_YmnPr  // Превышает разрядность.
      add   [edi+4], eax
      jc    M1_op_YmnPr  // Превышает разрядность.
      mov   eax, ecx     // Загружает для умножения младшую часть.
      mul   dword ptr[esi+4]// Умножает eax на старшую часть.
      jc    M1_op_YmnPr  // Превышает разрядность.
      add   [edi+4], eax
      jc    M1_op_YmnPr  // Превышает разрядность.
      jmp   M2_op_YmnPr
 M1_op_YmnPr:
      or      dword ptr[edi],   0xFFFFFFFF
      or      dword ptr[edi+4], 0xFFFFFFFF
 M2_op_YmnPr:
      mov   eax, edi   // Возврат результата.
   }
}
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator*=(NB32 dwMen)
{  asm{// При переполнении результат максимальный:
      mov   ecx, [eax]   // Копия 1го сомножителя (младшая).
      mov   ebx, [eax+4] // Копия 1го сомножителя (старшая).
      mov   esi, edx     // Адрес 2го множителя в индексный регистр "источник".
      mov   edi, eax     // Адрес 1го множителя в индексный регистр "приёмник".
      // Как при умножении в "столбик".
      mov   eax, ecx     // Загружает для умножения младшую часть.
      mul   esi          // Умножает eax на число в esi, старшая часть в edx.
      mov   [edi], eax   // Младшую часть в 1й сомножитель.
      mov   [edi+4], edx // Старшую часть в 1й сомножитель.
      mov   eax, ebx     // Загружает для умножения старшую часть.
      mul   esi          // Умножает eax на число в esi, старшая часть в edx.
      jc    M1_op_YmnPr2 // Превышает разрядность.
      add   [edi+4], eax
      jc    M1_op_YmnPr2 // Превышает разрядность.
      jmp   M2_op_YmnPr2
 M1_op_YmnPr2:
      or      dword ptr[edi],   0xFFFFFFFF
      or      dword ptr[edi+4], 0xFFFFFFFF
 M2_op_YmnPr2:
      mov   eax, edi   // Возврат результата.
   }
}
#pragma argsused
NB32& __fastcall operator*=(NB32& dwMen, kODKNB64& KU64P)
{  asm{// При переполнении результат максимальный:
      mov   ecx, eax     // Адрес 1го множителя в индексный регистр "приёмник".
      cmp   dword ptr[edx+4], 0
      jne   M1_op_YmnPr3
      mov   eax, [eax]    // Загружает для умножения младшую часть.
      mul   dword ptr[edx]// Умножает eax на число по адресу esi, старшая часть в edx.
      jc    M1_op_YmnPr3  // Превышает разрядность.
      mov   [ecx], eax    // Младшую часть в 1й сомножитель.
      jmp   M2_op_YmnPr3
 M1_op_YmnPr3:
      or      dword ptr[ecx],   0xFFFFFFFF
 M2_op_YmnPr3:
      mov   eax, ecx   // Возврат результата.
   }
}
// Умножение: *
#pragma argsused
ODKNB64 __fastcall operator*(kODKNB64& KU64L, kODKNB64& KU64P)
{  asm{// При переполнении результат максимальный:
      mov   edi, eax     // Адрес буфера возврата в индексный регистр "приёмник".
      cmp   dword ptr[edx+4], 0
      je    M0_op_Ymn
      cmp   dword ptr[ecx+4], 0
      jne   M1_op_Ymn
 M0_op_Ymn:
      mov   esi, edx     // Адрес 2го множителя в индексный регистр "источник".
      // Как при умножении в "столбик".
      mov   eax, [ecx]    // Загружает для умножения младшую часть.
      mul   dword ptr[esi]// Умножает eax на число по адресу esi, старшая часть в edx.
      mov   [edi], eax    // Младшую часть в 1й сомножитель.
      mov   [edi+4], edx  // Старшую часть в 1й сомножитель.
      mov   eax, [ecx+4]  // Загружает для умножения старшую часть.
      mul   dword ptr[esi]// Умножает eax на число по адресу esi, старшая часть в edx.
      jc    M1_op_Ymn     // Превышает разрядность.
      add   [edi+4], eax
      jc    M1_op_Ymn  // Превышает разрядность.
      mov   eax, [ecx]     // Загружает для умножения младшую часть.
      mul   dword ptr[esi+4]// Умножает eax на старшую часть.
      jc    M1_op_Ymn  // Превышает разрядность.
      add   [edi+4], eax
      jc    M1_op_Ymn  // Превышает разрядность.
      jmp   M2_op_Ymn
 M1_op_Ymn:
      or      dword ptr[edi],   0xFFFFFFFF
      or      dword ptr[edi+4], 0xFFFFFFFF
 M2_op_Ymn:
      mov   eax, edi   // Возврат результата.
   }
}
#pragma argsused
ODKNB64 __fastcall operator*(kODKNB64& KU64L, NB32 dwMen)
{  asm{// При переполнении результат максимальный:
      mov   esi, edx     // Адрес 1го множителя в индексный регистр "источник".
      mov   edi, eax     // Адрес буфера возврата в индексный регистр "приёмник".
      // Как при умножении в "столбик".
      mov   eax, ecx    // Загружает для умножения младшую часть.
      mul   dword ptr[esi]// Умножает eax на число по адресу esi, старшая часть в edx.
      mov   [edi], eax    // Младшую часть в 1й сомножитель.
      mov   [edi+4], edx  // Старшую часть в 1й сомножитель.
      mov   eax, ecx  // Загружает для умножения старшую часть.
      mul   dword ptr[esi+4]// Умножает eax на старшую часть.
      jc    M1_op_Ymn2  // Превышает разрядность.
      add   [edi+4], eax
      jc    M1_op_Ymn2  // Превышает разрядность.
      jmp   M2_op_Ymn2
 M1_op_Ymn2:
      or      dword ptr[edi],   0xFFFFFFFF
      or      dword ptr[edi+4], 0xFFFFFFFF
 M2_op_Ymn2:
      mov   eax, edi   // Возврат результата.
   }
}
#pragma argsused
ODKNB64 __fastcall operator*(NB32 dwMen, kODKNB64& KU64P)
{  asm{// При переполнении результат максимальный:
      mov   esi, edx     // Адрес 1го множителя в индексный регистр "источник".
      mov   edi, eax     // Адрес буфера возврата в индексный регистр "приёмник".
      // Как при умножении в "столбик".
      mov   eax, [ecx]    // Загружает для умножения младшую часть.
      mul   esi           // Умножает eax на число по адресу esi, старшая часть в edx.
      mov   [edi], eax    // Младшую часть в 1й сомножитель.
      mov   [edi+4], edx  // Старшую часть в 1й сомножитель.
      mov   eax, [ecx+4]  // Загружает для умножения старшую часть.
      mul   esi           // Умножает eax на старшую часть.
      jc    M1_op_Ymn3  // Превышает разрядность.
      add   [edi+4], eax
      jc    M1_op_Ymn3  // Превышает разрядность.
      jmp   M2_op_Ymn3
 M1_op_Ymn3:
      or      dword ptr[edi],   0xFFFFFFFF
      or      dword ptr[edi+4], 0xFFFFFFFF
 M2_op_Ymn3:
      mov   eax, edi   // Возврат результата.
   }
}

// Разделить: /= /  // При частном меньше нуля результат = 0:
// Деление с присвоением результата: /=
const float gf2=2.0; // Множитель для корекции делимого после сдвига.
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator/=(kODKNB64& KU64)
{  asm{// Сравнивает:
      mov   ebx, [edx+4]
      cmp  [eax+4], ebx   // Сравнивает старшие двойные слова.
      ja    M3_op_DelPr   // Продолжить.
      jb    M1_op_DelPr   // Обнулить.
      mov   ebx, [edx]
      cmp  [eax], ebx     // Сравнивает младшие двойные слова.
      ja    M3_op_DelPr   // Продолжить.
      jb    M1_op_DelPr   // Обнулить.
      // При равенстве - единица и выход:
      mov   dword ptr[eax],   1
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_DelPr
 M1_op_DelPr:
      mov   dword ptr[eax],   0
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_DelPr
 M3_op_DelPr: // Проверка на нуль и единицу:
      cmp   dword ptr[edx+4], 0
      jne   M2_op_DelPr
      cmp   dword ptr[edx], 2
      jb    MVwh_op_DelPr
 M2_op_DelPr: // Деление делает сопроцессор .387:
      // Подготовка делимого при наличии знакового бита:
      .387
      bt    dword ptr[eax+4], 31 // Тест старшего(знакового) бита.
      jnc   M4_op_DelPr
      mov   ecx, [eax+4]
      mov   ebx, [eax]           // Сохраняет младшую часть.
      shrd [eax], ecx, 1         // Сдвиг мл.части.
      shr   dword ptr[eax+4], 1  // Сдвиг ст.части.
      fild   qword ptr[eax]       // Делимое в st(0).
      fmul  gf2   // Множитель = 2 для корекции делимого в FPU.387 после сдвига.
      bt    ebx, 0               // Тест младшего бита.
      jnc   M5_op_DelPr          // Если нет - далее, иначе восстановить.
      fld1                       // 1 в st(0).
      faddp st(1)                // Результат сложения в st(0).
      jmp   M5_op_DelPr
 M4_op_DelPr:
      fild   qword ptr[eax]   // Делимое.
 M5_op_DelPr:
      // Подготовка делителя при наличии знакового бита:
      bt    dword ptr[edx+4], 31 // Тест старшего(знакового) бита.
      jnc   M6_op_DelPr
      mov   ecx, [edx+4]
      mov   ebx, [edx]           // Сохраняет младшую часть.
      shrd [edx], ecx, 1         // Сдвиг мл.части.
      shr   dword ptr[edx+4], 1  // Сдвиг ст.части.
      fild   qword ptr[edx]       // Делимое в st(0).
      fmul  gf2   // Множитель = 2 для корекции делимого в FPU.387 после сдвига.
         // Восстановление в памяти делителя:
         mov   ecx, [edx]
         shld [edx+4], ecx, 1    // Сдвиг мл.части.
         mov  [edx], ebx         // Восстанавливает младшую часть.
      bt    ebx, 0               // Тест младшего бита.
      jnc   M7_op_DelPr          // Если нет - далее, иначе восстановить.
      fld1                       // 1 в st(0).
      faddp st(1)                // Результат сложения в st(0).
      jmp   M7_op_DelPr
 M6_op_DelPr:
      fild   qword ptr[edx]   // Делитель.
 M7_op_DelPr:
      fdivp st(1)            // st(1)/st(0), вытолкнуть из стека = в st(0).
      // Подготовка округления при записи:
      sub   esp, 4           // Память для контрольного слова.
      fstcw[esp]
      mov   cl, [esp+1]
      or    byte ptr[esp+1], 1100b  // Отбрасывает дробную часть.
      fldcw[esp]
      fistp   qword ptr[eax]
      // Восстановление контрольного слова:
      mov  [esp+1], cl
      fldcw[esp]
      add   esp, 4           // Вместо pop.
 MVwh_op_DelPr:
   }
}
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator/=(NB32 dwMen)
{  asm{// Сравнивает:
      xor   ecx, ecx
      cmp   dword ptr[eax+4], ecx// Сравнивает старшие двойные слова.
      jne   M3_op_DelPr2       // Продолжить.
      cmp  [eax], edx          // Сравнивает младшие двойные слова.
      ja    M3_op_DelPr2       // Продолжить.
      jb    M1_op_DelPr2       // Обнулить.
      // При равенстве - единица и выход:
      mov   dword ptr[eax],   1
      mov   dword ptr[eax+4], ecx
      jmp   MVwh_op_DelPr2
 M1_op_DelPr2:
      mov   dword ptr[eax],   ecx
      mov   dword ptr[eax+4], ecx
      jmp   MVwh_op_DelPr2
 M3_op_DelPr2: // Проверка на нуль и единицу:
      cmp   edx, 1
      jbe    MVwh_op_DelPr2
      // Деление делает сопроцессор .387:
      .387
      // Подготовка делимого при наличии знакового бита:
      bt    dword ptr[eax+4], 31 // Тест старшего(знакового) бита.
      jnc   M4_op_DelPr2
      mov   ecx, [eax+4]
      mov   ebx, [eax]           // Сохраняет младшую часть.
      shrd [eax], ecx, 1         // Сдвиг мл.части.
      shr   dword ptr[eax+4], 1  // Сдвиг ст.части.
      fild   qword ptr[eax]       // Делимое в st(0).
      fmul  gf2   // Множитель = 2 для корекции делимого в FPU.387 после сдвига.
      bt    ebx, 0               // Тест младшего бита.
      jnc   M5_op_DelPr2         // Если нет - далее, иначе восстановить.
      fld1                       // 1 в st(0).
      faddp st(1)                // Результат сложения в st(0).
      jmp   M5_op_DelPr2
 M4_op_DelPr2:
      fild   qword ptr[eax]   // Делимое.
 M5_op_DelPr2:
      // Подготовка делителя:
      push  0
      push  edx
      fild   qword ptr[esp]   // делител в st(0).
      fdivp st(1)   // Деление.
      // Подготовка округления при записи:
      fstcw[esp]
      mov   cl, [esp+1]
      or    byte ptr[esp+1], 1100b  // Отбрасывает дробную часть.
      fldcw[esp]
      fistp   qword ptr[eax]
      // Восстановление контрольного слова:
      mov  [esp+1], cl
      fldcw[esp]
      add   esp, 8           // Вместо pop.
 MVwh_op_DelPr2:
   }
}
#pragma argsused
NB32& __fastcall operator/=(NB32& dwMen, kODKNB64& KU64P)
{  asm{
      mov   ecx, eax
      cmp   dword ptr[edx+4], 0 // Сравнивает.
      jne   M1_op_DelPr3
      cmp   dword ptr[edx], 1   // Тест делителя на 0 и 1.
      jbe   M2_op_DelPr3
      mov   eax, [eax]          // Загружает для деления dwMen.
      mov   ebx, edx
      xor   edx, edx
      div   dword ptr[ebx]      // Деление.
      mov  [ecx], eax     
      jmp   M2_op_DelPr3
 M1_op_DelPr3:
      mov   dword ptr[ecx], 0
 M2_op_DelPr3:
      mov   eax, ecx   // Возврат результата.
   }
}
// Деление: /
#pragma argsused
ODKNB64 __fastcall operator/(kODKNB64& KU64L, kODKNB64& KU64P)
{  asm{
      mov   ebx, [ecx+4]
      cmp  [edx+4], ebx // Сравнивает старшие двойные слова.
      ja    M3_op_Del   // Продолжить.
      jb    M1_op_Del   // Обнулить.
      mov   ebx, [ecx]
      cmp  [edx], ebx   // Сравнивает младшие двойные слова.
      ja    M3_op_Del   // Продолжить.
      jb    M1_op_Del   // Обнулить.
      // При равенстве - единица и выход:
      mov   dword ptr[eax],   1
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_Del
 M1_op_Del:
      mov   dword ptr[eax],   0
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_Del
 M3_op_Del: // Проверка на нуль:
      cmp   dword ptr[ecx+4], 0
      jne   M2_op_Del
      cmp   dword ptr[ecx], 0
      je    MVwh_op_Del
 M8_op_Del: // Проверка на единицу:
      cmp   dword ptr[ecx], 1
      jne   M2_op_Del
      mov   ebx, [edx]        // Копирует делимое в буфер возврата.
      mov  [eax], ebx
      mov   ebx, [edx+4]
      mov  [eax+4], ebx
      jmp   MVwh_op_Del
 M2_op_Del: // Деление делает сопроцессор .387:
      // Подготовка делимого при наличии знакового бита:
      .387
      bt    dword ptr[edx+4], 31 // Тест старшего(знакового) бита.
      jnc   M4_op_Del
      mov   esi, [edx+4]
      mov   ebx, [edx]           // Сохраняет младшую часть.
      shrd [edx], esi, 1         // Сдвиг мл.части.
      shr   dword ptr[edx+4], 1  // Сдвиг ст.части.
      fild   qword ptr[edx]       // Делимое в st(0).
      fmul  gf2   // Множитель = 2 для корекции делимого в FPU.387 после сдвига.
      // Восстановление в памяти делимого:
         mov   esi, [edx]
         shld [edx+4], esi, 1    // Сдвиг ст.части.
         mov  [edx], ebx         // Восстанавливает младшую часть.
      bt    ebx, 0             // Тест младшего бита.
      jnc   M5_op_Del          // Если нет - далее, иначе восстановить.
      fld1                     // 1 в st(0).
      faddp st(1)              // Результат сложения в st(0).
      jmp   M5_op_Del
 M4_op_Del:
      fild   qword ptr[edx]   // Делимое.
 M5_op_Del:
      // Подготовка делителя при наличии знакового бита:
      bt    dword ptr[ecx+4], 31 // Тест старшего(знакового) бита.
      jnc   M6_op_Del
      mov   esi, [ecx+4]
      mov   ebx, [ecx]           // Сохраняет младшую часть.
      shrd [ecx], esi, 1         // Сдвиг мл.части.
      shr   dword ptr[ecx+4], 1  // Сдвиг ст.части.
      fild   qword ptr[ecx]       // Делитель в st(0).
      fmul  gf2   // Множитель = 2 для корекции делителя в FPU.387 после сдвига.
         // Восстановление в памяти делителя:
         mov   esi, [ecx]
         shld [ecx+4], esi, 1    // Сдвиг ст.части.
         mov  [ecx], ebx         // Восстанавливает младшую часть.
      bt    ebx, 0             // Тест младшего бита.
      jnc   M7_op_Del          // Если нет - далее, иначе восстановить.
      fld1                     // 1 в st(0).
      faddp st(1)              // Результат сложения в st(0).
      jmp   M7_op_Del
 M6_op_Del:
      fild   qword ptr[ecx]   // Делитель.
 M7_op_Del:
      fdivp st(1)            // st(1)/st(0), вытолкнуть из стека = в st(0).
      // Подготовка округления при записи:
      sub   esp, 4           // Память для контрольного слова.
      fstcw[esp]
      mov   cl, [esp+1]
      or    byte ptr[esp+1], 1100b  // Отбрасывает дробную часть.
      fldcw[esp]
      fistp   qword ptr[eax]
      // Восстановление контрольного слова:
      mov  [esp+1], cl
      fldcw[esp]
      add   esp, 4           // Вместо pop.
 MVwh_op_Del:
   }
}
#pragma argsused
ODKNB64 __fastcall operator/(kODKNB64& KU64L, NB32 dwMen)
{  asm{
      cmp   dword ptr[edx+4], 0 // Сравнивает старшие двойные слова.
      ja    M3_op_Del2   // Продолжить.
      cmp  [edx], ecx    // Сравнивает младшие двойные слова.
      ja    M3_op_Del2   // Продолжить.
      jb    M1_op_Del2   // Обнулить.
      // При равенстве - единица и выход:
      mov   dword ptr[eax],   1
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_Del2
 M1_op_Del2:
      mov   dword ptr[eax],   0
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_Del2
 M3_op_Del2: // Проверка на нуль:
      test  ecx, ecx
      jz    MVwh_op_Del2
 M8_op_Del2: // Проверка на единицу:
      cmp   ecx, 1
      jne   M2_op_Del2
      mov   ebx, [edx]        // Копирует делимое в буфер возврата.
      mov  [eax], ebx
      mov   ebx, [edx+4]
      mov  [eax+4], ebx
      jmp   MVwh_op_Del2
 M2_op_Del2: // Деление делает сопроцессор .387:
      // Подготовка делимого при наличии знакового бита:
      .387
      bt    dword ptr[edx+4], 31 // Тест старшего(знакового) бита.
      jnc   M4_op_Del2
      mov   esi, [edx+4]
      mov   ebx, [edx]           // Сохраняет младшую часть.
      shrd [edx], esi, 1         // Сдвиг мл.части.
      shr   dword ptr[edx+4], 1  // Сдвиг ст.части.
      fild   qword ptr[edx]       // Делимое в st(0).
      fmul  gf2   // Множитель = 2 для корекции делимого в FPU.387 после сдвига.
      // Восстановление в памяти делимого:
         mov   esi, [edx]
         shld [edx+4], esi, 1    // Сдвиг ст.части.
         mov  [edx], ebx         // Восстанавливает младшую часть.
      bt    ebx, 0             // Тест младшего бита.
      jnc   M5_op_Del2          // Если нет - далее, иначе восстановить.
      fld1                     // 1 в st(0).
      faddp st(1)              // Результат сложения в st(0).
      jmp   M5_op_Del2
 M4_op_Del2:
      fild   qword ptr[edx]   // Делимое.
 M5_op_Del2:
      // Подготовка делителя:
      push  0
      push  ecx
      fild   qword ptr[esp]   // делител в st(0).
      fdivp st(1)   // Деление.
      // Подготовка округления при записи:
      fstcw[esp]
      mov   cl, [esp+1]
      or    byte ptr[esp+1], 1100b  // Отбрасывает дробную часть.
      fldcw[esp]
      fistp   qword ptr[eax]
      // Восстановление контрольного слова:
      mov  [esp+1], cl
      fldcw[esp]
      add   esp, 8           // Вместо pop.
 MVwh_op_Del2:
   }
}
#pragma argsused
ODKNB64 __fastcall operator/(NB32 dwMen, kODKNB64& KU64P)
{  asm{
      mov   edi, eax
      cmp   dword ptr[ecx+4], 0 // Сравнивает.
      jne   M3_op_Del3
      cmp   edx, dword ptr[ecx]
      jae   M4_op_Del3
 M3_op_Del3:
      mov   dword ptr[eax],   0
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_Del3
 M4_op_Del3:
      cmp   dword ptr[ecx], 0 // Сравнивает.
      je    MVwh_op_Del3
      mov   eax, edx          // Загружает для деления dwMen.
      xor   edx, edx
      div   dword ptr[ecx]      // Деление.
      mov  [edi], eax
      mov   dword ptr[edi+4], 0
      mov   eax, edi   // Возврат результата.
 MVwh_op_Del3:
   }
}

// Разделить по модулю: %= %  :
// Деление по модулю с присвоением результата: %=
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator%=(kODKNB64& KU64)
{  asm{// Сравнивает:
      mov   ebx, [edx+4]
      cmp  [eax+4], ebx   // Сравнивает старшие двойные слова.
      ja    M3_op_DelModPr   // Продолжить.
      jb    MVwh_op_DelModPr // Выход.   // Вернуть делимое.
      mov   ebx, [edx]
      cmp  [eax], ebx     // Сравнивает младшие двойные слова.
      ja    M3_op_DelModPr   // Продолжить.
      jb    MVwh_op_DelModPr // Выход.   // Вернуть делимое.
      // При равенстве - нуль и выход:
      mov   dword ptr[eax],   0
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_DelModPr // Выход.
 M3_op_DelModPr: // Проверка на нуль:
      cmp   dword ptr[edx+4], 0
      jne   M2_op_DelModPr
      cmp   dword ptr[edx], 0
      je    MVwh_op_DelModPr
 M2_op_DelModPr: // Деление делает сопроцессор .387:
      // Подготовка делимого при наличии знакового бита:
      .387
      bt    dword ptr[eax+4], 31 // Тест старшего(знакового) бита.
      jnc   M4_op_DelModPr
      mov   ecx, [eax+4]
      mov   ebx, [eax]           // Сохраняет младшую часть.
      shrd [eax], ecx, 1         // Сдвиг мл.части.
      shr   dword ptr[eax+4], 1  // Сдвиг ст.части.
      fild   qword ptr[eax]       // Делимое в st(0).
      fmul  gf2   // Множитель = 2 для корекции делимого в FPU.387 после сдвига.
      bt    ebx, 0               // Тест младшего бита.
      jnc   M5_op_DelModPr          // Если нет - далее, иначе восстановить.
      fld1                       // 1 в st(0).
      faddp st(1)                // Результат сложения в st(0).
      jmp   M5_op_DelModPr
 M4_op_DelModPr:
      fild   qword ptr[eax]   // Делимое.
 M5_op_DelModPr:
      // Подготовка делителя при наличии знакового бита:
      bt    dword ptr[edx+4], 31 // Тест старшего(знакового) бита.
      jnc   M6_op_DelModPr
      mov   ecx, [edx+4]
      mov   ebx, [edx]           // Сохраняет младшую часть.
      shrd [edx], ecx, 1         // Сдвиг мл.части.
      shr   dword ptr[edx+4], 1  // Сдвиг ст.части.
      fild   qword ptr[edx]       // Делимое в st(0).
      fmul  gf2   // Множитель = 2 для корекции делимого в FPU.387 после сдвига.
         // Восстановление в памяти делителя:
         mov   ecx, [edx]
         shld [edx+4], ecx, 1    // Сдвиг мл.части.
         mov  [edx], ebx         // Восстанавливает младшую часть.
      bt    ebx, 0               // Тест младшего бита.
      jnc   M7_op_DelModPr          // Если нет - далее, иначе восстановить.
      fld1                       // 1 в st(0).
      faddp st(1)                // Результат сложения в st(0).
      jmp   M7_op_DelModPr
 M6_op_DelModPr:
      fild   qword ptr[edx]   // Делитель.
 M7_op_DelModPr:
      mov   ebx, eax         // Сохраняет eax.
      fxch  st(1)
 M8_op_DelModPr:       // Цикл вычисления остатка:
      fprem            // st(0)%st(1) = в st(0).
      fstsw ax         // Для теста флага "c2".
      sahf             // "c2" в "PF"
      jp    M8_op_DelModPr
      // Подготовка округления при записи:
      sub   esp, 4           // Память для контрольного слова.
      fstcw[esp]
      mov   cl, [esp+1]
      or    byte ptr[esp+1], 1100b  // Отбрасывает дробную часть.
      fldcw[esp]
      mov   eax, ebx         // Восстанавливает eax.
      fistp   qword ptr[eax]
      ffree st(0)
      // Восстановление контрольного слова:
      mov  [esp+1], cl
      fldcw[esp]
      add   esp, 4           // Вместо pop.
 MVwh_op_DelModPr:
   }
}
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator%=(NB32 dwMen)
{  asm{// Сравнивает:
      xor   ecx, ecx
      cmp   dword ptr[eax+4], ecx// Сравнивает старшие двойные слова.
      jne   M3_op_DelModPr2      // Продолжить.
      cmp  [eax], edx            // Сравнивает младшие двойные слова.
      ja    M3_op_DelModPr2      // Продолжить.
      jb    MVwh_op_DelModPr2    // Вернуть делимое.
      // При равенстве - нуль и выход:
      mov   dword ptr[eax],   ecx
      mov   dword ptr[eax+4], ecx
 M3_op_DelModPr2: // Проверка на нуль:
      cmp   edx, 0
      je    MVwh_op_DelModPr2
      // Деление делает сопроцессор .387:
      .387
      // Подготовка делимого при наличии знакового бита:
      bt    dword ptr[eax+4], 31 // Тест старшего(знакового) бита.
      jnc   M4_op_DelModPr2
      mov   ecx, [eax+4]
      mov   ebx, [eax]           // Сохраняет младшую часть.
      shrd [eax], ecx, 1         // Сдвиг мл.части.
      shr   dword ptr[eax+4], 1  // Сдвиг ст.части.
      fild   qword ptr[eax]       // Делимое в st(0).
      fmul  gf2   // Множитель = 2 для корекции делимого в FPU.387 после сдвига.
      bt    ebx, 0               // Тест младшего бита.
      jnc   M5_op_DelModPr2         // Если нет - далее, иначе восстановить.
      fld1                       // 1 в st(0).
      faddp st(1)                // Результат сложения в st(0).
      jmp   M5_op_DelModPr2
 M4_op_DelModPr2:
      fild   qword ptr[eax]   // Делимое.
 M5_op_DelModPr2:
      // Подготовка делителя:
      push  0
      push  edx
      fild   qword ptr[esp]   // делител в st(0).
      mov   ebx, eax         // Сохраняет eax.
      fxch  st(1)
 M8_op_DelModPr2:      // Цикл вычисления остатка:
      fprem            // st(0)%st(1) = в st(0).
      fstsw ax         // Для теста флага "c2".
      sahf             // "c2" в "PF"
      jp    M8_op_DelModPr2
      // Подготовка округления при записи:
      fstcw[esp]
      mov   cl, [esp+1]
      or    byte ptr[esp+1], 1100b  // Отбрасывает дробную часть.
      fldcw[esp]
      mov   eax, ebx         // Восстанавливает eax.
      fistp   qword ptr[eax]
      ffree st(0)
      // Восстановление контрольного слова:
      mov  [esp+1], cl
      fldcw[esp]
      add   esp, 8           // Вместо pop.
 MVwh_op_DelModPr2:
   }
}
#pragma argsused
NB32& __fastcall operator%=(NB32& dwMen, kODKNB64& KU64P)
{  asm{
      cmp   dword ptr[edx+4], 0 // Сравнивает.
      jne   MVwh_op_DelModPr3
      cmp   dword ptr[edx], 0   // Тест делителя на 0.
      je    MVwh_op_DelModPr3
      mov   ecx, eax
      mov   eax, [eax]          // Загружает для деления dwMen.
      mov   ebx, edx
      xor   edx, edx
      div   dword ptr[ebx]      // Деление.
      mov  [ecx], edx
      mov   eax, ecx   // Возврат результата.
 MVwh_op_DelModPr3:
   }
}
// Деление по модулю: %
#pragma argsused
ODKNB64 __fastcall operator%(kODKNB64& KU64L, kODKNB64& KU64P)
{  asm{
      mov   ebx, [ecx+4]
      cmp  [edx+4], ebx // Сравнивает старшие двойные слова.
      ja    M3_op_DelMod   // Продолжить.
      jb    M1_op_DelMod   // Вернуть делимое.
      mov   ebx, [ecx]
      cmp  [edx], ebx   // Сравнивает младшие двойные слова.
      ja    M3_op_DelMod   // Продолжить.
      jb    M1_op_DelMod   // Вернуть делимое.
      // При равенстве - 0 и выход:
      jmp   M8_op_DelMod
 M1_op_DelMod:
      mov   ebx, [edx+4]   // Вернуть делимое.
      mov  [eax+4], ebx    //
      mov   ebx, [edx]     //
      mov  [eax], ebx      //
      jmp   MVwh_op_DelMod
 M3_op_DelMod: // Проверка на нуль:
      cmp   dword ptr[ecx+4], 0
      jne   M2_op_DelMod
      cmp   dword ptr[ecx], 0
      je    MVwh_op_DelMod
      // Проверка на единицу:
      cmp   dword ptr[ecx], 1
      jne   M2_op_DelMod
 M8_op_DelMod: // Проверка на единицу - 0 и выход:
      mov   dword ptr[eax],   0
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_DelMod
 M2_op_DelMod: // Деление делает сопроцессор .387:
      // Подготовка делимого при наличии знакового бита:
      .387
      bt    dword ptr[edx+4], 31 // Тест старшего(знакового) бита.
      jnc   M4_op_DelMod
      mov   esi, [edx+4]
      mov   ebx, [edx]           // Сохраняет младшую часть.
      shrd [edx], esi, 1         // Сдвиг мл.части.
      shr   dword ptr[edx+4], 1  // Сдвиг ст.части.
      fild   qword ptr[edx]       // Делимое в st(0).
      fmul  gf2   // Множитель = 2 для корекции делимого в FPU.387 после сдвига.
      // Восстановление в памяти делимого:
         mov   esi, [edx]
         shld [edx+4], esi, 1    // Сдвиг ст.части.
         mov  [edx], ebx         // Восстанавливает младшую часть.
      bt    ebx, 0             // Тест младшего бита.
      jnc   M5_op_DelMod          // Если нет - далее, иначе восстановить.
      fld1                     // 1 в st(0).
      faddp st(1)              // Результат сложения в st(0).
      jmp   M5_op_DelMod
 M4_op_DelMod:
      fild   qword ptr[edx]   // Делимое.
 M5_op_DelMod:
      // Подготовка делителя при наличии знакового бита:
      bt    dword ptr[ecx+4], 31 // Тест старшего(знакового) бита.
      jnc   M6_op_DelMod
      mov   esi, [ecx+4]
      mov   ebx, [ecx]           // Сохраняет младшую часть.
      shrd [ecx], esi, 1         // Сдвиг мл.части.
      shr   dword ptr[ecx+4], 1  // Сдвиг ст.части.
      fild   qword ptr[ecx]       // Делитель в st(0).
      fmul  gf2   // Множитель = 2 для корекции делителя в FPU.387 после сдвига.
         // Восстановление в памяти делителя:
         mov   esi, [ecx]
         shld [ecx+4], esi, 1    // Сдвиг ст.части.
         mov  [ecx], ebx         // Восстанавливает младшую часть.
      bt    ebx, 0             // Тест младшего бита.
      jnc   M7_op_DelMod          // Если нет - далее, иначе восстановить.
      fld1                     // 1 в st(0).
      faddp st(1)              // Результат сложения в st(0).
      jmp   M7_op_DelMod
 M6_op_DelMod:
      fild   qword ptr[ecx]   // Делитель.
 M7_op_DelMod:
      mov   ebx, eax         // Сохраняет eax.
      fxch  st(1)
 M9_op_DelMod:       // Цикл вычисления остатка:
      fprem            // st(0)%st(1) = в st(0).
      fstsw ax         // Для теста флага "c2".
      sahf             // "c2" в "PF"
      jp    M9_op_DelMod
      // Подготовка округления при записи:
      sub   esp, 4           // Память для контрольного слова.
      fstcw[esp]
      mov   cl, [esp+1]
      or    byte ptr[esp+1], 1100b  // Отбрасывает дробную часть.
      fldcw[esp]
      mov   eax, ebx         // Восстанавливает eax.
      fistp   qword ptr[eax]
      ffree st(0)
      // Восстановление контрольного слова:
      mov  [esp+1], cl
      fldcw[esp]
      add   esp, 4           // Вместо pop.
 MVwh_op_DelMod:
   }
}
#pragma argsused
ODKNB64 __fastcall operator%(kODKNB64& KU64L, NB32 dwMen)
{  asm{
      cmp   dword ptr[edx+4], 0 // Сравнивает старшие двойные слова.
      ja    M3_op_DelMod2   // Продолжить.
      cmp  [edx], ecx       // Сравнивает младшие двойные слова.
      ja    M3_op_DelMod2   // Продолжить.
      jb    M1_op_DelMod2   // Вернуть делимое.
      // При равенстве - 0 и выход:
      jmp   M8_op_DelMod2
 M1_op_DelMod2:
      mov   ebx, [edx+4]   // Вернуть делимое.
      mov  [eax+4], ebx    //
      mov   ebx, [edx]     //
      mov  [eax], ebx      //
      jmp   MVwh_op_DelMod2
 M3_op_DelMod2: // Проверка на нуль:
      test  ecx, ecx
      jz    MVwh_op_DelMod2
      // Проверка на единицу:
      cmp   ecx, 1
      jne   M2_op_DelMod2
 M8_op_DelMod2: // При 1 = 0 и выход:
      mov   dword ptr[eax],   0
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_DelMod2
 M2_op_DelMod2: // Деление делает сопроцессор .387:
      // Подготовка делимого при наличии знакового бита:
      .387
      bt    dword ptr[edx+4], 31 // Тест старшего(знакового) бита.
      jnc   M4_op_DelMod2
      mov   esi, [edx+4]
      mov   ebx, [edx]           // Сохраняет младшую часть.
      shrd [edx], esi, 1         // Сдвиг мл.части.
      shr   dword ptr[edx+4], 1  // Сдвиг ст.части.
      fild   qword ptr[edx]       // Делимое в st(0).
      fmul  gf2   // Множитель = 2 для корекции делимого в FPU.387 после сдвига.
      // Восстановление в памяти делимого:
         mov   esi, [edx]
         shld [edx+4], esi, 1    // Сдвиг ст.части.
         mov  [edx], ebx         // Восстанавливает младшую часть.
      bt    ebx, 0             // Тест младшего бита.
      jnc   M5_op_DelMod2          // Если нет - далее, иначе восстановить.
      fld1                     // 1 в st(0).
      faddp st(1)              // Результат сложения в st(0).
      jmp   M5_op_DelMod2
 M4_op_DelMod2:
      fild   qword ptr[edx]   // Делимое.
 M5_op_DelMod2:
      // Подготовка делителя:
      push  0
      push  ecx
      fild   qword ptr[esp]   // делител в st(0).
      mov   ebx, eax         // Сохраняет eax.
      fxch  st(1)
 M9_op_DelMod2:       // Цикл вычисления остатка:
      fprem            // st(0)%st(1) = в st(0).
      fstsw ax         // Для теста флага "c2".
      sahf             // "c2" в "PF"
      jp    M9_op_DelMod2
      // Подготовка округления при записи:
      fstcw[esp]
      mov   cl, [esp+1]
      or    byte ptr[esp+1], 1100b  // Отбрасывает дробную часть.
      fldcw[esp]
      mov   eax, ebx         // Восстанавливает eax.
      fistp   qword ptr[eax]
      ffree st(0)
      // Восстановление контрольного слова:
      mov  [esp+1], cl
      fldcw[esp]
      add   esp, 8           // Вместо pop.
 MVwh_op_DelMod2:
   }
}
#pragma argsused
ODKNB64 __fastcall operator%(NB32 dwMen, kODKNB64& KU64P)
{  asm{
      cmp   dword ptr[ecx+4], 0 // Сравнивает.
      jne   M3_op_DelMod3       // Вернуть делимое.
      cmp   edx, dword ptr[ecx]
      jae   M4_op_DelMod3
 M3_op_DelMod3: // Вернуть делимое.
      mov   dword ptr[eax],   edx
      mov   dword ptr[eax+4], 0
      jmp   MVwh_op_DelMod3
 M4_op_DelMod3:
      cmp   dword ptr[ecx], 0 // Сравнивает.
      je    MVwh_op_DelMod3
      mov   edi, eax
      mov   eax, edx          // Загружает для деления dwMen.
      xor   edx, edx
      div   dword ptr[ecx]      // Деление.
      mov  [edi], edx
      mov   dword ptr[edi+4], 0
      mov   eax, edi   // Возврат результата.
 MVwh_op_DelMod3:
   }
}
// ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
// Функциональный элемент FE_Prisvoenie(). Использовать только с
// ODKNB64& __fastcall operator=(float& f32).
// ODKNB64& __fastcall operator=(double& fd64),
// ODKNB64& __fastcall operator=(long double& fld80),
void FE_Prisvoenie();

#pragma argsused
ODKNB64& __fastcall ODKNB64::operator=(const float& f32)
{  asm fld   dword ptr[edx]   // Загружает f32.
   FE_Prisvoenie();
}
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator=(const double& fd64)
{  asm fld   qword ptr[edx]   // Загружает fd64.
   FE_Prisvoenie();
}
#pragma argsused
ODKNB64& __fastcall ODKNB64::operator=(const long double& fld80)
{  asm fld   tbyte ptr[edx]   // Загружает fld80.
   FE_Prisvoenie();
}
// Предельно значение для перевода в целое /2. 9.22337203685477632e+18;
const char gfldPredNa2[10]={0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3D,0x40};
void FE_Prisvoenie()
{  asm{
      //fld   dword ptr[edx]   // Загружает 32 бита.
      //fld   qword ptr[edx]   // Загружает 64 бита.
      //fld   tbyte ptr[edx]   // Загружает 80 бит.
      mov   ch, byte ptr[edx]// Сохранение младшего байта мантиссы.
      mov   edx, eax         // Сохранение адреса.
      ftst                   // Тест st(0) с 0.
      fstsw ax
      sahf
      mov   eax, edx         // Восстановление адреса возврата.
      jp    M4_op_Pr         // Не число, выход без изменений.
      jc    M3_op_Pr         // st(0) < 0.
      jz    M3_op_Pr         // st(0) == 0.
      // Подготовка округления при записи:                   //
      sub   esp, 4                                           //
      fstcw[esp]                                             //
      mov   cl, [esp+1]                                      //
      or    byte ptr[esp+1], 1100b// Отбрасывает дробную часть.
      fldcw[esp]                                           ////

      fld   tbyte ptr gfldPredNa2// Предельное значение для перевода в целое /2.
      fcom  st(1)
      fstsw ax
      sahf
      jnc   M1_op_Pr         // fld80 < gfldPredNa2.
      fld   gf2
      fdivp st(2)            // fld80 / 2.
      fcom  st(1)
      fstsw ax
      sahf
      jnc   M2_op_Pr         // (fld80 / 2) < gfldPredNa2.
      mov   eax, edx         // Восстановление адреса.
      mov   dword ptr[eax],  0xFFFFFFFF
      mov   dword ptr[eax+4],0xFFFFFFFF
      ffree st(0)
      fincstp
      ffree st(0)
      fincstp
      jmp   MVwh_op_Pr
 M1_op_Pr:
      mov   eax, edx         // Восстановление адреса возврата.
      ffree st(0)
      fincstp
      fistp   qword ptr[eax]// Сохраняет.
      jmp   MVwh_op_Pr
 M2_op_Pr:
      mov   eax, edx         // Восстановление адреса.
      ffree st(0)
      fincstp
      fistp   qword ptr[eax]// Сохраняет.
      mov   edx, [eax]    // Корректирует после деления на 2.
      shld [eax+4],edx, 1 //
      shl   edx, 1        //
      bt    cx, 8
      jnc   M5_op_Pr
      or    dl, 1
 M5_op_Pr:
      mov  [eax], edx     // Корректирует после деления на 2.
 MVwh_op_Pr:
      // Восстановление контрольного слова:
      mov  [esp+1], cl                   //
      fldcw[esp]                         //
      add   esp, 4                     ////
      jmp   MVwh2_op_Pr
 M3_op_Pr:  // fld80 == 0 || fld80 < 0:
      mov   dword ptr[eax],  0
      mov   dword ptr[eax+4],0
 M4_op_Pr:  // Не число, выход без изменений.
      ffree st(0)
 MVwh2_op_Pr:
   }
}

// Для преобразования к типу float. Загружает в FPU.387.:
__fastcall ODKNB64::operator float() const
{  asm{// Подготовка при наличии знакового бита:
      .387
      bt    dword ptr[eax+4], 31 // Тест старшего(знакового) бита.
      jnc   M1_op_Pr2
      mov   ecx, [eax+4]
      mov   edx, [eax]           // Сохраняет младшую часть.
      shrd [eax], ecx, 1         // Сдвиг мл.части.
      shr   dword ptr[eax+4], 1  // Сдвиг ст.части.
      fild   qword ptr[eax]       // в st(0).
      fmul  gf2   // Множитель = 2 для корекции в FPU.387 после сдвига.
      // Восстановление в памяти:
         mov   ecx, [eax]
         shld [eax+4], ecx, 1    // Сдвиг ст.части.
         mov  [eax], edx         // Восстанавливает младшую часть.
      bt    edx, 0               // Тест младшего бита.
      jnc   MVwh_op_Pr2          // Если нет - далее, иначе восстановить.
      fld1                       // 1 в st(0).
      faddp st(1)                // Результат сложения в st(0).
      jmp   MVwh_op_Pr2
 M1_op_Pr2:
      fild   qword ptr[eax]       // Загрузка в FPU.387.
 MVwh_op_Pr2:
   }
}
// Для преобразования к типу double. Загружает в FPU.387.:
__fastcall ODKNB64::operator double() const
{  asm{// Подготовка при наличии знакового бита:
      .387
      bt    dword ptr[eax+4], 31 // Тест старшего(знакового) бита.
      jnc   M1_op_Pr3
      mov   ecx, [eax+4]
      mov   edx, [eax]           // Сохраняет младшую часть.
      shrd [eax], ecx, 1         // Сдвиг мл.части.
      shr   dword ptr[eax+4], 1  // Сдвиг ст.части.
      fild   qword ptr[eax]       // в st(0).
      fmul  gf2   // Множитель = 2 для корекции в FPU.387 после сдвига.
      // Восстановление в памяти:
         mov   ecx, [eax]
         shld [eax+4], ecx, 1    // Сдвиг ст.части.
         mov  [eax], edx         // Восстанавливает младшую часть.
      bt    edx, 0               // Тест младшего бита.
      jnc   MVwh_op_Pr3          // Если нет - далее, иначе восстановить.
      fld1                       // 1 в st(0).
      faddp st(1)                // Результат сложения в st(0).
      jmp   MVwh_op_Pr3
 M1_op_Pr3:
      fild   qword ptr[eax]       // Загрузка в FPU.387.
 MVwh_op_Pr3:
   }
}
// Для преобразования к типу long double. Загружает в FPU.387.:
__fastcall ODKNB64::operator long double() const
{  asm{// Подготовка при наличии знакового бита:
      .387
      bt    dword ptr[eax+4], 31 // Тест старшего(знакового) бита.
      jnc   M1_op_Pr4
      mov   ecx, [eax+4]
      mov   edx, [eax]           // Сохраняет младшую часть.
      shrd [eax], ecx, 1         // Сдвиг мл.части.
      shr   dword ptr[eax+4], 1  // Сдвиг ст.части.
      fild   qword ptr[eax]       // в st(0).
      fmul  gf2   // Множитель = 2 для корекции в FPU.387 после сдвига.
      // Восстановление в памяти:
         mov   ecx, [eax]
         shld [eax+4], ecx, 1    // Сдвиг ст.части.
         mov  [eax], edx         // Восстанавливает младшую часть.
      bt    edx, 0               // Тест младшего бита.
      jnc   MVwh_op_Pr4          // Если нет - далее, иначе восстановить.
      fld1                       // 1 в st(0).
      faddp st(1)                // Результат сложения в st(0).
      jmp   MVwh_op_Pr4
 M1_op_Pr4:
      fild   qword ptr[eax]       // Загрузка в FPU.387.
 MVwh_op_Pr4:
   }
}

#pragma warn +rvl
// Функции: ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()

// Вставить строку с конечным нулём формата ASCII текущего значения класса:
// VsStr() формирует строку различных систем счисления.
// Параметры: szByfer - Приёмный буфер для строки.
                 // dwForm  - Форма строки:
                    // Младший байт №1 - указывает размер групп через делитель байт №2.
                       // Например: значение 3 формирует число 1234567890 как
                       // число 1 234 567 890.
                    // Байт №2 - байт делитель групп. При 0 пробел.
                    // Байт №3 - размер нулевых заполнителей.
                       // Например: значение 10 формирует число 12345 как
                       // число 0 000 012 345, а число 5 как 0 000 000 005.
                 // lSisSch  - система счисления 2 значит двоичная, 8 - восьмеричная,
                    // 10 - десятеричная, 16 - шестнадцатиричная.
// Возврат: Удачно - длина строки в байтах без учёта конечного нуля.
         // Провал - 0.
ONB32 __fastcall ODKNB64::VsStr(iNB8 szByfer, NB32 dwForm, long lSisSch)
{  unsigned char *pForm;
   ONB32 i, j, k, iRazmByf;
   ODKNB64 KlChastnoe(*this);

   if(!szByfer)return 0;

   pForm=(iNB8)&dwForm;
   if(pForm[0])k=pForm[0];
   if(!pForm[1])pForm[1]=' '; // Делитель.
   i=0;
   if(lSisSch==10)
   {   j=iRazmByf=ODKNB64_STR10_BYFER;
      do // Главный цикл преобразования:
      {  j--; i++;
         szByfer[j]=KlChastnoe%10; szByfer[j]+='0';
         if(pForm[0]){k--; if(!k){k=pForm[0]; j--; szByfer[j]=pForm[1];}}
         KlChastnoe/=10;
      }while(KlChastnoe.EK_1|KlChastnoe.EK_2);
   }
   else if(lSisSch==16)
   {   j=iRazmByf=ODKNB64_STR16_BYFER;
      do // Главный цикл преобразования:
      {  j--; i++;
         szByfer[j]=KlChastnoe.EK_1&0xF;
         if(szByfer[j]<10) szByfer[j]+='0';
         else szByfer[j]+=0x40-9+pForm[3];
         if(pForm[0]){k--; if(!k){k=pForm[0]; j--; szByfer[j]=pForm[1];}}
         KlChastnoe>>=4;
      }while(KlChastnoe.EK_1|KlChastnoe.EK_2);
   }
   else if(lSisSch==2)
   {   j=iRazmByf=ODKNB64_STR2_BYFER;
      do // Главный цикл преобразования:
      {  j--; i++;
         szByfer[j]=KlChastnoe.EK_1&1; szByfer[j]+='0';
         if(pForm[0]){k--; if(!k){k=pForm[0]; j--; szByfer[j]=pForm[1];}}
         KlChastnoe>>=1;
      }while(KlChastnoe.EK_1|KlChastnoe.EK_2);
   }
   else if(lSisSch==8)
   {   j=iRazmByf=ODKNB64_STR8_BYFER;
      do // Главный цикл преобразования:
      {  j--; i++;
         szByfer[j]=KlChastnoe.EK_1&7; szByfer[j]+='0';
         if(pForm[0]){k--; if(!k){k=pForm[0]; j--; szByfer[j]=pForm[1];}}
         KlChastnoe>>=3;
      }while(KlChastnoe.EK_1|KlChastnoe.EK_2);
   }

   if(pForm[2]>(iRazmByf-4)/2)
      pForm[2]=(iRazmByf-4)/2;
   // Дописывает левые нули заполнители:
   while(i<pForm[2])
   {  j--; i++;
      szByfer[j]='0';
      if(pForm[0])
      {  k--;
         if(!k)
         {  k=pForm[0];
            j--;
            szByfer[j]=pForm[1];
         }
      }
   }
   // Переписывает из конца в начало:
   k=0;
   if(szByfer[j]==' ') j++;
   for(; j<iRazmByf; j++, k++)
      szByfer[k]=szByfer[j];
   szByfer[k]=0; // Конечный нуль.

   return k;
}

// Взять строку с конечным нулём формата ASCII для установки значения класса:
// VzStr() формирует значение из строки различных систем счисления.
// Параметры: szStr - Строка с конечным нулём.
                    // Формат строки десятеричной системы счисления: 98...210.
                       // Количество значащих цифр не более 20.
                    // Формат строки шестнадцатиричной системы счисления: 0xFE...210.
                       // Количество значащих цифр не более 16.
                    // Формат строки восьмеричной системы счисления: 076...210.
                       // Количество значащих цифр не более 22.
                    // Формат строки двоичной системы счисления: 0b10.
                       // Количество значащих цифр не более 64.
                 // dwForm  - Форма строки:
                    // Младший байт №1 - указывает размер строки, может быть 0.
                    // Байт №2 - байт делитель групп. При 0 пробел.
                    // Байт №3 - байт окончания числа.
// Возврат: Удачно - 1.
         // Провал - 0.
ONB32 __fastcall ODKNB64::VzStr(kiNB8 szStr, NB32 dwForm)
{  unsigned char *pForm;
   ONB32 i, j, k;
   ODKNB64 Klu64(0, 0), Klu64Mn(0, 10);

   if(!szStr||szStr[0]<'0'||szStr[0]>'9')return 0;

   pForm=(iNB8)&dwForm;
   j=0;
   if(!pForm[0])// Размер строки:
   {  while(szStr[j++]!=pForm[2]);
      j--;
   }
   else j=pForm[0];
   
   if(!pForm[1])pForm[1]=' '; // Делитель.
   // Формат строки десятеричной системы счисления: 98...210.
   if(szStr[1]>='0'&&szStr[1]<='9')
   {  j--;
   	if(szStr[j]>='0'&&szStr[j]<='9')
         *this=(NB32)szStr[j]&0x0F;
      else if(szStr[j]!=pForm[1])
          return 0;
   	while(j)// Главный цикл преобразования:
      {  j--;
      	if(szStr[j]>='0'&&szStr[j]<='9')
         {  Klu64=(NB32)szStr[j]&0x0F;
            Klu64*=Klu64Mn;
         	*this+=Klu64;
            Klu64Mn*=10;
         }
         else if(szStr[j]!=pForm[1])
            return 0;
      }
   }
   // Формат строки шестнадцатиричной системы счисления: 0xFE...210.
   else if(szStr[1]=='X'||szStr[1]=='x')
   {  operator()(0, 0);
      i=0;
   	while(j)// Главный цикл преобразования:
      {  j--;
      	if((szStr[j]>='0'&&szStr[j]<='9'))
         	Klu64=(NB32)szStr[j]&0x0F;
      	else if((szStr[j]>='A'&&szStr[j]<='F')||
              	  (szStr[j]>='a'&&szStr[j]<='f'))
            Klu64=(NB32)(szStr[j]&0x0F)+9;
         else if(szStr[j]!=pForm[1])
            return 0;
         else continue;
         if(i<64)
      	{  Klu64<<=i;
           *this|=Klu64;
         }
         i+=4;
      }
   }
   // Формат строки восьмеричной системы счисления: 0o76...210.
   else if(szStr[1]=='O'||szStr[1]=='o')
   {  operator()(0, 0);
      i=0;
   	while(j)// Главный цикл преобразования:
      {  j--;
      	if((szStr[j]>='0'&&szStr[j]<='7'))
         	Klu64=(NB32)szStr[j]&0x0F;
         else if(szStr[j]!=pForm[1])
            return 0;
         else continue;
         if(i<64)
      	{  Klu64<<=i;
           *this|=Klu64;
         }
         i+=3;
      }
   }
   // Формат строки двоичной системы счисления: 0b10.
   else if(szStr[1]=='B'||szStr[1]=='b')
   {  operator()(0, 0);
      i=0;
   	while(j)// Главный цикл преобразования:
      {  j--;
      	if((szStr[j]=='0'||szStr[j]=='1'))
         	Klu64=(NB32)szStr[j]&0x0F;
         else if(szStr[j]!=pForm[1])
            return 0;
         else continue;
         if(i<64)
      	{  Klu64<<=i;
           *this|=Klu64;
         }
         i++;
      }
   }
   else return 0;

   return 1;
}

#ifndef OD_NO_NAMESPACE
} // namespace OtDiatlovaOU.
#endif


