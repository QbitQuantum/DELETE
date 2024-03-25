//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::)
//
// Copyright © 2000-2005 OtDiatlovaOU™, RU, KZ All Rights Reserved.
//
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
//  МОДУЛЬ:   ODDef32.h  V 1.1.2005.304
//
//  НАЗНАЧЕНИЕ:  Содержит определения.
//
//  КОМЕНТАРИИ:
//
//

#ifndef __ODDEF32_H
#define __ODDEF32_H

// Для вызовов функций:
#define  ODFASTCALL    __fastcall // Порядок передачи аргументов и чистка стека.

#ifndef OD_NO_NAMESPACE
namespace OtDiatlovaOU {
#endif

// Ошибки при выбросе исключений: (ПОРЯДОК НЕ МЕНЯТЬ)
enum ERRORS
{  kOD_NO_DATA=1,           // Нет данных.                //
   kOD_INVALID_ARGUMENT,    // Не правильный параметр.    //
   kOD_ERROR_LENGTH,        // Ошибка в заданом размере.  //
   kOD_OUT_OF_RANGE,        // Выход за диапазон.         //
   kOD_OVERFLOW,            // Переполнение значения.     //
   kOD_OP_NEW_NULL,         // Оператор new вернул 0.     //
   kOD_WIN,                 // Ошибка в функциях Windows. //
   KOD_XALLOC_OP_NEW,       // Исключение от оператора new//
   kOD_EXCEPTION_STL,       // Исключение от STL.         //
   //
   kOD_KONEC_ERRORS,          // Оператор new вернул 0.     //


   kOD_VSEGO_ERRORS=(kOD_KONEC_ERRORS-1)
};

// Определение типов: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Префиксы: "k"= const, "i"= индекс*, "s"= ссылка&.

// Определение для нулевого указателя:         //
#ifndef NYL                                    //
#if defined(__cplusplus) || defined(_Windows)  //
#define NYL    0                               //
#else                                          //
#define NYL    ((void *)0)                     //
#endif                                         //
#endif                                         //
// Двузначный тип ДА или НЕТ:                  //
typedef int                     DANET;

// Пустой тип и указатели:                     //
typedef void                    VACUUM;
typedef void*                   iVACUUM;
typedef const void*             kiVACUUM;
typedef void*                   INDEKS;
typedef const void*             kINDEKS;
typedef void**                  iINDEKS;
typedef const void**            kiINDEKS;
typedef void*                   INDEX;
typedef const void*             kINDEX;
typedef void**                  iINDEX;
typedef const void**            kiINDEX;

// 8 битные натуральные и отрицательные типы чисел, и указатели на них:
typedef unsigned char           NB8;
typedef const unsigned char     kNB8;
typedef unsigned char*          iNB8;
typedef const unsigned char*    kiNB8;
typedef unsigned char&          sNB8;
typedef const unsigned char&    ksNB8;
typedef signed char             ONB8;
typedef const signed char       kONB8;
typedef signed char*            iONB8;
typedef const signed char*      kiONB8;
typedef signed char&            sONB8;
typedef const signed char&      ksONB8;
typedef signed char             ZB8;
typedef const signed char       kZB8;
typedef signed char*            iZB8;
typedef const signed char*      kiZB8;
typedef signed char&            sZB8;
typedef const signed char&      ksZB8;

// 16 битные натуральные и отрицательные типы чисел, и указатели на них:
typedef unsigned short          NB16;
typedef const unsigned short    kNB16;
typedef unsigned short*         iNB16;
typedef const unsigned short*   kiNB16;
typedef unsigned short&         sNB16;
typedef const unsigned short&   ksNB16;
typedef signed short            ONB16;
typedef const signed short      kONB16;
typedef signed short*           iONB16;
typedef const signed short*     kiONB16;
typedef signed short&           sONB16;
typedef const signed short&     ksONB16;
typedef signed short            ZB16;
typedef const signed short      kZB16;
typedef signed short*           iZB16;
typedef const signed short*     kiZB16;
typedef signed short&           sZB16;
typedef const signed short&     ksZB16;

// 32 битные натуральные и отрицательные типы чисел, и указатели на них:
typedef unsigned long           NB32;
typedef const unsigned long     kNB32;
typedef unsigned long*          iNB32;
typedef const unsigned long*    kiNB32;
typedef unsigned long&          sNB32;
typedef const unsigned long&    ksNB32;
typedef signed long             ONB32;
typedef const signed long       kONB32;
typedef signed long*            iONB32;
typedef const signed long*      kiONB32;
typedef signed long&            sONB32;
typedef const signed long&      ksONB32;
typedef signed long             ZB32;
typedef const signed long       kZB32;
typedef signed long*            iZB32;
typedef const signed long*      kiZB32;
typedef signed long&            sZB32;
typedef const signed long&      ksZB32;

// 32 битные реальные (действительные) типы чисел, и указатели на них:
typedef float                   REAL32;
typedef const float             kREAL32;
typedef float*                  iREAL32;
typedef const float*            kiREAL32;
typedef float&                  sREAL32;
typedef const float&            ksREAL32;

// 64 битные натуральные типы чисел, и указатели на них:
#if(__BCPLUSPLUS__ >= 0x0550)
typedef unsigned __int64        NB64;
typedef __int64                 ONB64;

typedef const ONB64             kONB64;
typedef ONB64*                  iONB64;
typedef const ONB64*            kiONB64;
typedef ONB64&                  sONB64;
typedef const ONB64&            ksONB64;
#else
union NB64
{  class
   {public:
      NB32  EK_1; // Меньний элемент класса.     //
      NB32  EK_2; // Больший элемент класса.     //
   }K;
   double EO64;   // 64 битный элемент объединения.
   __stdcall NB64(){}
   __stdcall NB64(bool danet)
   {  if(danet){K.EK_1=0xFFFFFFFF; K.EK_1=0xFFFFFFFF;}
      else     {K.EK_1=0; K.EK_1=0;}
   }
};
#endif
    
typedef const NB64              kNB64;
typedef NB64*                   iNB64;
typedef const NB64*             kiNB64;
typedef NB64&                   sNB64;
typedef const NB64&             ksNB64;

// 64 битные реальные (действительные) типы чисел, и указатели на них:
typedef double                  REAL64;
typedef const double            kREAL64;
typedef double*                 iREAL64;
typedef const double*           kiREAL64;
typedef double&                 sREAL64;
typedef const double&           ksREAL64;

// 80 битные реальные (действительные) типы чисел, и указатели на них:
typedef long double             REAL80;
typedef const long double       kREAL80;
typedef long double*            iREAL80;
typedef const long double*      kiREAL80;
typedef long double&            sREAL80;
typedef const long double&      ksREAL80;

// Определение типов. <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// Выбор между функциями и макросами.                                         //
#ifdef NO_INLINE_FUNC
#define  set_uint64(ret64, High, Low)  \
                       {*((NB32*)&ret64)=Low; *((NB32*)((NB32)&ret64+4))=High;};
#else
inline void set_uint64(sNB64 ret64, NB32 High, NB32 Low)
                        {*((NB32*)&ret64)=Low; *((NB32*)((NB32)&ret64+4))=High;}
#endif // INLINE_FUNC


#ifndef OD_NO_NAMESPACE
} // namespace OtDiatlovaOU.
#endif

#endif  // __ODDEF32_H
