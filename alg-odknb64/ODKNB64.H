//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Copyright © 2000-2002 OtDiatlovaOU™, RU, KZ. All Rights Reserved.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Module: ODKNB64.h
//
//  КОМЕНТАРИИ:
//      Класс написан под процессор не менее .386 и сопроцессор .387.         //

#ifndef __ODKNB64_H
#define __ODKNB64_H

#include <ODDef32.h>     //Содержит определения для включаемых файлов.        //
#include <ODExpImp.h>    // Экспорт и импорт классов и функций.               //


#define  kODKNB64	const ODKNB64 // Константное значение класса ODKNB64. //

#ifndef OD_NO_NAMESPACE
namespace OtDiatlovaOU {
#endif
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
//  КЛАСС: ODKNB64
//
//  НАЗНАЧЕНИЕ:
//      1. Обеспечивает работу с целыми без знака 64-х битными числами.
//
//  КОМЕНТАРИИ:
//
class _ODK_DLL ODKNB64
{   public:
      NB32  EK_1; // Меньная часть.
      NB32  EK_2; // Большая часть.

      _ODK_DLL// Для экспорта дружественных функций __declspec(dllexport).

// Конструкторы:
      ODKNB64(){}
      ODKNB64(NB32 dwArg):EK_1(dwArg), EK_2(0UL){}
      ODKNB64(NB32 dwArg2, NB32 dwArg):EK_1(dwArg), EK_2(dwArg2){}
      ~ODKNB64(){}
// Функции операторы: + - * / % == != <= < >= > += -= *= /= %= << >>  = [] () ->
   // Манипулирование битами с присвоением операторы: |= ^= &= <<= >>=
      // Побитовое ИЛИ |=:
      ODKNB64& operator|=(kODKNB64& KUI64)
                             {EK_1|=KUI64.EK_1; EK_2|=KUI64.EK_2; return *this;}
      ODKNB64& operator|=(NB32 dwArg)               {EK_1|=dwArg; return *this;}
      friend NB32& operator|=(NB32& dwArg, kODKNB64& KUI64)
                                              {dwArg|=KUI64.EK_1; return dwArg;}
      // Побитовое исключающее ИЛИ ^=:
      ODKNB64& operator^=(kODKNB64& KUI64)
                             {EK_1^=KUI64.EK_1; EK_2^=KUI64.EK_2; return *this;}
      ODKNB64& operator^=(NB32 dwArg)               {EK_1^=dwArg; return *this;}
      friend NB32& operator^=(NB32& dwArg, kODKNB64& KUI64)
                                              {dwArg^=KUI64.EK_1; return dwArg;}
      // Побитовое И &=:
      ODKNB64& operator&=(kODKNB64& KUI64)
                             {EK_1&=KUI64.EK_1; EK_2&=KUI64.EK_2; return *this;}
      ODKNB64& operator&=(NB32 dwArg)               {EK_1&=dwArg; return *this;}
      friend NB32& operator&=(NB32& dwArg, kODKNB64& KUI64)
                                              {dwArg&=KUI64.EK_1; return dwArg;}
      // Побитовый сдвиг влево <<=:
      ODKNB64& __fastcall operator<<=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator<<=(NB32 dwArg);
      friend NB32& __fastcall operator<<=(NB32& dwArg, kODKNB64& KUI64);
      // Побитовый сдвиг вправо >>=:
      ODKNB64& __fastcall operator>>=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator>>=(NB32 dwArg);
      friend NB32& __fastcall operator>>=(NB32& dwArg, kODKNB64& KUI64);
   // Манипулирование битами операторы: ~ | ^ & << >>
      // Побитовое НЕТ ~:
      ODKNB64 __fastcall operator~();
      // Побитовое ИЛИ |:
      ODKNB64 __fastcall operator|(kODKNB64& KUI64) const;
      ODKNB64 __fastcall operator|(NB32 dwArg) const;
      friend ODKNB64 __fastcall operator|(NB32 dwArg, kODKNB64& KUI64);
      // Побитовое исключающее ИЛИ ^:
      ODKNB64 __fastcall operator^(kODKNB64& KUI64) const;
      ODKNB64 __fastcall operator^(NB32 dwArg) const;
      friend ODKNB64 __fastcall operator^(NB32 dwArg, kODKNB64& KUI64);
      // Побитовое И &:
      ODKNB64 __fastcall operator&(kODKNB64& KUI64) const;
      ODKNB64 __fastcall operator&(NB32 dwArg) const;
      friend ODKNB64 __fastcall operator&(NB32 dwArg, kODKNB64& KUI64);
      // Побитовый сдвиг влево <<:
      ODKNB64 __fastcall operator<<(kODKNB64& KUI64) const;
      ODKNB64 __fastcall operator<<(NB32 dwArg) const;
      friend ODKNB64 __fastcall operator<<(NB32 dwArg, kODKNB64& KUI64);
      // Побитовый сдвиг вправо >>:
      ODKNB64 __fastcall operator>>(kODKNB64& KUI64) const;
      ODKNB64 __fastcall operator>>(NB32 dwArg) const;
      friend ODKNB64 __fastcall operator>>(NB32 dwArg, kODKNB64& KUI64);
   // Логические операторы:  ! || &&
      // НЕ:
      NB32 operator!() const                              {return !(EK_1|EK_2);}
      // ИЛИ:
      NB32 operator||(kODKNB64& KUI64) const
                                  {return (EK_1|EK_2)||(KUI64.EK_1|KUI64.EK_2);}
      NB32 operator||(NB32 dwArg) const             {return (EK_1|EK_2)||dwArg;}
      friend NB32 operator||(NB32 dwArg, kODKNB64& KUI64)
                                        {return dwArg||(KUI64.EK_1|KUI64.EK_2);}
      // И:
      NB32 operator&&(kODKNB64& KUI64) const
                                  {return (EK_1|EK_2)&&(KUI64.EK_1|KUI64.EK_2);}
      NB32 operator&&(NB32 dwArg) const             {return (EK_1|EK_2)&&dwArg;}
      friend NB32 operator&&(NB32 dwArg, kODKNB64& KUI64)
                                        {return dwArg&&(KUI64.EK_1|KUI64.EK_2);}
   // Отношений операторы: == != <= < >= > 
      // Равно:
      bool __fastcall operator==(kODKNB64& KUI64) const;
      bool __fastcall operator==(NB32 dwArg) const;
      friend bool __fastcall operator==(NB32 dwArg, kODKNB64& KUI64);
      // Не равно:
      bool __fastcall operator!=(kODKNB64& KUI64) const;
      bool __fastcall operator!=(NB32 dwArg) const;
      friend bool __fastcall operator!=(NB32 dwArg, kODKNB64& KUI64);
      // Меньше или равно:
      bool __fastcall operator<=(kODKNB64& KUI64) const;
      bool __fastcall operator<=(NB32 dwArg) const;
      friend bool __fastcall operator<=(NB32 dwArg, kODKNB64& KUI64);
      // Меньше:
      bool __fastcall operator<(kODKNB64& KUI64) const;
      bool __fastcall operator<(NB32 dwArg) const;
      friend bool __fastcall operator<(NB32 dwArg, kODKNB64& KUI64);
      // Больше или равно:
      bool __fastcall operator>=(kODKNB64& KUI64) const;
      bool __fastcall operator>=(NB32 dwArg) const;
      friend bool __fastcall operator>=(NB32 dwArg, kODKNB64& KUI64);
      // Больше:
      bool __fastcall operator>(kODKNB64& KUI64) const;
      bool __fastcall operator>(NB32 dwArg) const;
      friend bool __fastcall operator>(NB32 dwArg, kODKNB64& KUI64);
   // Математические операторы: += + ++ -= - -- *= * /= / %= %
     // Плюс: += + ++  // При переполнении результат максимальный:
      // Сложение с присвоением результата: +=
      ODKNB64& __fastcall operator+=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator+=(NB32 dwArg);
      friend NB32& __fastcall operator+=(NB32& dwArg, kODKNB64& KU64P);
      // Сложение: +
      friend ODKNB64 __fastcall operator+(kODKNB64& KU64L, kODKNB64& KU64P);
      friend ODKNB64 __fastcall operator+(kODKNB64& KU64L, NB32 dwArg);
      friend ODKNB64 __fastcall operator+(NB32 dwArg, kODKNB64& KU64P);
      // Пред и пост инкримент выполняются как пред инкремент: ++
      friend ODKNB64& __fastcall operator++(ODKNB64& KU64L);
     // Минус: -= - --  // При разнице меньше нуля результат = 0:
      // Вычитание с присвоением результата: -=
      ODKNB64& __fastcall operator-=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator-=(NB32 dwArg);
      friend NB32& __fastcall operator-=(NB32& dwArg, kODKNB64& KU64P);
      // Вычитание: -
      friend ODKNB64 __fastcall operator-(kODKNB64& KU64L, kODKNB64& KU64P);
      friend ODKNB64 __fastcall operator-(kODKNB64& KU64L, NB32 dwArg);
      friend ODKNB64 __fastcall operator-(NB32 dwArg, kODKNB64& KU64P);
      // Пред и пост декримент выполняются как пред декримент: --
      friend ODKNB64& __fastcall operator--(ODKNB64& KUI64);
     // Умножить: *= *  // При переполнении результат максимальный:
      // Умножение с присвоением результата: *=
      ODKNB64& __fastcall operator*=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator*=(NB32 dwArg);
      friend NB32& __fastcall operator*=(NB32& dwArg, kODKNB64& KU64P);
      // Умножение: *
      friend ODKNB64 __fastcall operator*(kODKNB64& KU64L, kODKNB64& KU64P);
      friend ODKNB64 __fastcall operator*(kODKNB64& KU64L, NB32 dwArg);
      friend ODKNB64 __fastcall operator*(NB32 dwArg, kODKNB64& KU64P);
     // Разделить: /= / :
      // Деление с присвоением результата: /=
      ODKNB64& __fastcall operator/=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator/=(NB32 dwArg);
      friend NB32& __fastcall operator/=(NB32& dwArg, kODKNB64& KU64P);
      // Деление: /
      friend ODKNB64 __fastcall operator/(kODKNB64& KU64L, kODKNB64& KU64P);
      friend ODKNB64 __fastcall operator/(kODKNB64& KU64L, NB32 dwArg);
      friend ODKNB64 __fastcall operator/(NB32 dwArg, kODKNB64& KU64P);
     // Разделить по модулю: %= %  :
      // Деление по модулю с присвоением результата: %=
      ODKNB64& __fastcall operator%=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator%=(NB32 dwArg);
      friend NB32& __fastcall operator%=(NB32& dwArg, kODKNB64& KU64P);
      // Деление по модулю: %
      friend ODKNB64 __fastcall operator%(kODKNB64& KU64L, kODKNB64& KU64P);
      friend ODKNB64 __fastcall operator%(kODKNB64& KU64L, NB32 dwArg);
      friend ODKNB64 __fastcall operator%(NB32 dwArg, kODKNB64& KU64P);
      // Присвоение:
      ODKNB64& operator=(NB32 Arg)     {EK_2=0UL; EK_1=(NB32)Arg; return *this;}
      ODKNB64& operator=(ONB32 Arg)
      {if(Arg==-1){EK_1=EK_2=-1;} else if(Arg<0){EK_1=EK_2=0UL;}
                                       else {EK_1=Arg; EK_2=0UL;} return *this;}
      ODKNB64& operator=(NB8 Arg)                 {return operator=((NB32)Arg);}
      ODKNB64& operator=(ONB8 Arg)               {return operator=((ONB32)Arg);}
      ODKNB64& operator=(NB16 Arg)                {return operator=((NB32)Arg);}
      ODKNB64& operator=(ONB16 Arg)              {return operator=((ONB32)Arg);}
      ODKNB64& __fastcall operator=(const float& f32);
      ODKNB64& __fastcall operator=(const double& fd64);
      ODKNB64& __fastcall operator=(const long double& fld80);
      // Начисление:
      ODKNB64& operator()()                  {EK_1=0UL; EK_2=0UL; return *this;}
      ODKNB64& operator()(NB32 dwArg)      {EK_1=dwArg; EK_2=0UL; return *this;}
      ODKNB64& operator()(NB32 dwArg2, NB32 dwArg)
                                        {EK_1=dwArg; EK_2=dwArg2; return *this;}
      // Для преобразования к типу unsigned int:
      operator unsigned int() const                               {return EK_1;}
#ifdef __ODDEF32_H
      // Для преобразования в логическое выражение типа int:
      operator DANET() const                               {return (EK_1|EK_2);}
#elif _WINDEF_
      // Для преобразования в логическое выражение типа int:
      operator BOOL() const                                {return (EK_1|EK_2);}
#else
      // Для преобразования к типу int:
      operator int() const                                        {return EK_1;}
#endif
      // Для преобразования к типу логическое выражение в 1 байт:
      operator bool() const                                {return (EK_1|EK_2);}
      // Для преобразования к типу unsigned long:
      operator NB32() const                                       {return EK_1;}
      // Для преобразования к типу long:
      operator long() const                                       {return EK_1;}
      // Для преобразования к типу NB16:
      operator NB16() const                                       {return EK_1;}
      // Для преобразования к типу short:
      operator short() const                                      {return EK_1;}
      // Для преобразования к типу unsigned char:
      operator unsigned char() const                              {return EK_1;}
      // Для преобразования к типу char:
      operator char() const                                       {return EK_1;}
      // Для преобразования к типу const char*:
      //operator const char*() const {return EK_1;}
      // Для преобразования к типу float. Загружает в FPU.387.:
      __fastcall operator float() const;
      // Для преобразования к типу double. Загружает в FPU.387.:
      __fastcall operator double() const;
      // Для преобразования к типу long double. Загружает в FPU.387.:
      __fastcall operator long double() const;
// Функции: ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
   // Вставить строку с конечным нулём формата ASCII текущего значения класса:
      // VsStr() формирует строку различных систем счисления.
      // Параметры:
         // szByfer - Приёмный буфер для строки.
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
      ONB32 __fastcall VsStr(iNB8 szByfer, NB32 dwForm, long lSisSch);
      // VsStr10() формирует строку десятеричной системы счисления.
      // Макро определения:
#define  ODKNB64_STR10_BYFER   44  // Необходимый размер буфера.
      // Параметры: szByfer - Приёмный буфер для строки. Размер не менее 44 байта.
                 // dwForm  - Форма строки: Те же что и у VsStr().
      ONB32 VsStr10(iNB8 szByfer, NB32 dwForm=3)
                                            {return VsStr(szByfer, dwForm, 10);}
// VsStr2() формирует строку двоичной системы счисления.
      // Макро определения:
#define  ODKNB64_STR2_BYFER   132 // Необходимый размер буфера.
      // Параметры: szByfer - Приёмный буфер для строки. Размер не менее 132 байта.
                 // dwForm  - Форма строки: Те же что и у VsStr().
      ONB32 VsStr2(iNB8 szByfer, NB32 dwForm=4)
                                             {return VsStr(szByfer, dwForm, 2);}
      // VsStr8() формирует строку восьмеричной системы счисления.
      // Макро определения:
#define  ODKNB64_STR8_BYFER   48  // Необходимый размер буфера.
      // Параметры: szByfer - Приёмный буфер для строки. Размер не менее 48 байт.
                 // dwForm  - Форма строки: Те же что и у VsStr().
      ONB32 VsStr8(iNB8 szByfer, NB32 dwForm=3)
                                             {return VsStr(szByfer, dwForm, 8);}
      // VsStr16() формирует строку шестнадцатеричной системы счисления.
      // Макро определения:
#define  ODKNB64_STR16_BYFER   36 // Необходимый размер буфера.
      // Параметры: szByfer - Приёмный буфер для строки. Размер не менее 36 байт.
                 // dwForm  - Форма строки: Те же что и у VsStr().
                 // Байт №4 - добавление к базовым буквам "ABCDEF".
                       // Например: значение 32 формирует буквы "ABCDEF" как
                       // буквы "abcdef".
      ONB32 VsStr16(iNB8 szByfer, NB32 dwForm=2)
                                            {return VsStr(szByfer, dwForm, 16);}
   // Взять строку с конечным нулём формата ASCII для установки значения класса:
      // VzStr() формирует значение из строки различных систем счисления.
      // Параметры: szStr - Строка с конечным dwForm байт №3.
                    // Формат строки десятеричной системы счисления: 98...210.
                       // Количество значащих цифр не более 20.
                    // Формат строки шестнадцатеричной системы счисления: 0xFE...210.
                       // Количество значащих цифр не более 16.
                    // Формат строки восьмеричной системы счисления: 0o76...210.
                       // Количество значащих цифр не более 22.
                    // Формат строки двоичной системы счисления: 0b10.
                       // Количество значащих цифр не более 64.
                 // dwForm  - Форма строки:
                    // Младший байт №1 - указывает размер строки, может быть 0.
                    // Байт №2 - байт делитель групп. При 0 пробел.
                    // Байт №3 - байт окончания строки.
      // Возврат: Удачно - 1.
               // Провал - 0.
      ONB32 __fastcall VzStr(kiNB8 szStr, NB32 dwForm=0);
};

// Определения для класса:
#undef  kODKNB64
//typedef ODKNB64                 NB64;
//typedef const ODKNB64           kNB64;
//typedef ODKNB64*                iNB64;
//typedef const ODKNB64*          kiNB64;
//typedef ODKNB64&                sNB64;
//typedef const ODKNB64&          ksNB64;
typedef const ODKNB64  kODKNB64; // Константное значение класса ODKNB64.      //
typedef ODKNB64*       iODKNB64; // Указатель на класс ODKNB64.               //
typedef const ODKNB64* kiODKNB64;// Константный указатель на класса ODKNB64.  //
typedef ODKNB64&       sODKNB64; // Ссылка на класс ODKNB64.                  //
typedef const ODKNB64& ksODKNB64;// Константная ссылка на класса ODKNB64.     //

#ifndef OD_NO_NAMESPACE
} // namespace OtDiatlovaOU.
#endif

#endif  // __ODKNB64_H
