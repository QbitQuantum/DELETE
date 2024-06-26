//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Copyright � 2000-2002 OtDiatlovaOU�, RU, KZ. All Rights Reserved.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Module: ODKNB64.h
//
//  ����������:
//      ����� ������� ��� ��������� �� ����� .386 � ����������� .387.         //

#ifndef __ODKNB64_H
#define __ODKNB64_H

#include <ODDef32.h>     //�������� ����������� ��� ���������� ������.        //
#include <ODExpImp.h>    // ������� � ������ ������� � �������.               //


#define  kODKNB64	const ODKNB64 // ����������� �������� ������ ODKNB64. //

#ifndef OD_NO_NAMESPACE
namespace OtDiatlovaOU {
#endif
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
//  �����: ODKNB64
//
//  ����������:
//      1. ������������ ������ � ������ ��� ����� 64-� ������� �������.
//
//  ����������:
//
class _ODK_DLL ODKNB64
{   public:
      NB32  EK_1; // ������� �����.
      NB32  EK_2; // ������� �����.

      _ODK_DLL// ��� �������� ������������� ������� __declspec(dllexport).

// ������������:
      ODKNB64(){}
      ODKNB64(NB32 dwArg):EK_1(dwArg), EK_2(0UL){}
      ODKNB64(NB32 dwArg2, NB32 dwArg):EK_1(dwArg), EK_2(dwArg2){}
      ~ODKNB64(){}
// ������� ���������: + - * / % == != <= < >= > += -= *= /= %= << >>  = [] () ->
   // ��������������� ������ � ����������� ���������: |= ^= &= <<= >>=
      // ��������� ��� |=:
      ODKNB64& operator|=(kODKNB64& KUI64)
                             {EK_1|=KUI64.EK_1; EK_2|=KUI64.EK_2; return *this;}
      ODKNB64& operator|=(NB32 dwArg)               {EK_1|=dwArg; return *this;}
      friend NB32& operator|=(NB32& dwArg, kODKNB64& KUI64)
                                              {dwArg|=KUI64.EK_1; return dwArg;}
      // ��������� ����������� ��� ^=:
      ODKNB64& operator^=(kODKNB64& KUI64)
                             {EK_1^=KUI64.EK_1; EK_2^=KUI64.EK_2; return *this;}
      ODKNB64& operator^=(NB32 dwArg)               {EK_1^=dwArg; return *this;}
      friend NB32& operator^=(NB32& dwArg, kODKNB64& KUI64)
                                              {dwArg^=KUI64.EK_1; return dwArg;}
      // ��������� � &=:
      ODKNB64& operator&=(kODKNB64& KUI64)
                             {EK_1&=KUI64.EK_1; EK_2&=KUI64.EK_2; return *this;}
      ODKNB64& operator&=(NB32 dwArg)               {EK_1&=dwArg; return *this;}
      friend NB32& operator&=(NB32& dwArg, kODKNB64& KUI64)
                                              {dwArg&=KUI64.EK_1; return dwArg;}
      // ��������� ����� ����� <<=:
      ODKNB64& __fastcall operator<<=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator<<=(NB32 dwArg);
      friend NB32& __fastcall operator<<=(NB32& dwArg, kODKNB64& KUI64);
      // ��������� ����� ������ >>=:
      ODKNB64& __fastcall operator>>=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator>>=(NB32 dwArg);
      friend NB32& __fastcall operator>>=(NB32& dwArg, kODKNB64& KUI64);
   // ��������������� ������ ���������: ~ | ^ & << >>
      // ��������� ��� ~:
      ODKNB64 __fastcall operator~();
      // ��������� ��� |:
      ODKNB64 __fastcall operator|(kODKNB64& KUI64) const;
      ODKNB64 __fastcall operator|(NB32 dwArg) const;
      friend ODKNB64 __fastcall operator|(NB32 dwArg, kODKNB64& KUI64);
      // ��������� ����������� ��� ^:
      ODKNB64 __fastcall operator^(kODKNB64& KUI64) const;
      ODKNB64 __fastcall operator^(NB32 dwArg) const;
      friend ODKNB64 __fastcall operator^(NB32 dwArg, kODKNB64& KUI64);
      // ��������� � &:
      ODKNB64 __fastcall operator&(kODKNB64& KUI64) const;
      ODKNB64 __fastcall operator&(NB32 dwArg) const;
      friend ODKNB64 __fastcall operator&(NB32 dwArg, kODKNB64& KUI64);
      // ��������� ����� ����� <<:
      ODKNB64 __fastcall operator<<(kODKNB64& KUI64) const;
      ODKNB64 __fastcall operator<<(NB32 dwArg) const;
      friend ODKNB64 __fastcall operator<<(NB32 dwArg, kODKNB64& KUI64);
      // ��������� ����� ������ >>:
      ODKNB64 __fastcall operator>>(kODKNB64& KUI64) const;
      ODKNB64 __fastcall operator>>(NB32 dwArg) const;
      friend ODKNB64 __fastcall operator>>(NB32 dwArg, kODKNB64& KUI64);
   // ���������� ���������:  ! || &&
      // ��:
      NB32 operator!() const                              {return !(EK_1|EK_2);}
      // ���:
      NB32 operator||(kODKNB64& KUI64) const
                                  {return (EK_1|EK_2)||(KUI64.EK_1|KUI64.EK_2);}
      NB32 operator||(NB32 dwArg) const             {return (EK_1|EK_2)||dwArg;}
      friend NB32 operator||(NB32 dwArg, kODKNB64& KUI64)
                                        {return dwArg||(KUI64.EK_1|KUI64.EK_2);}
      // �:
      NB32 operator&&(kODKNB64& KUI64) const
                                  {return (EK_1|EK_2)&&(KUI64.EK_1|KUI64.EK_2);}
      NB32 operator&&(NB32 dwArg) const             {return (EK_1|EK_2)&&dwArg;}
      friend NB32 operator&&(NB32 dwArg, kODKNB64& KUI64)
                                        {return dwArg&&(KUI64.EK_1|KUI64.EK_2);}
   // ��������� ���������: == != <= < >= > 
      // �����:
      bool __fastcall operator==(kODKNB64& KUI64) const;
      bool __fastcall operator==(NB32 dwArg) const;
      friend bool __fastcall operator==(NB32 dwArg, kODKNB64& KUI64);
      // �� �����:
      bool __fastcall operator!=(kODKNB64& KUI64) const;
      bool __fastcall operator!=(NB32 dwArg) const;
      friend bool __fastcall operator!=(NB32 dwArg, kODKNB64& KUI64);
      // ������ ��� �����:
      bool __fastcall operator<=(kODKNB64& KUI64) const;
      bool __fastcall operator<=(NB32 dwArg) const;
      friend bool __fastcall operator<=(NB32 dwArg, kODKNB64& KUI64);
      // ������:
      bool __fastcall operator<(kODKNB64& KUI64) const;
      bool __fastcall operator<(NB32 dwArg) const;
      friend bool __fastcall operator<(NB32 dwArg, kODKNB64& KUI64);
      // ������ ��� �����:
      bool __fastcall operator>=(kODKNB64& KUI64) const;
      bool __fastcall operator>=(NB32 dwArg) const;
      friend bool __fastcall operator>=(NB32 dwArg, kODKNB64& KUI64);
      // ������:
      bool __fastcall operator>(kODKNB64& KUI64) const;
      bool __fastcall operator>(NB32 dwArg) const;
      friend bool __fastcall operator>(NB32 dwArg, kODKNB64& KUI64);
   // �������������� ���������: += + ++ -= - -- *= * /= / %= %
     // ����: += + ++  // ��� ������������ ��������� ������������:
      // �������� � ����������� ����������: +=
      ODKNB64& __fastcall operator+=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator+=(NB32 dwArg);
      friend NB32& __fastcall operator+=(NB32& dwArg, kODKNB64& KU64P);
      // ��������: +
      friend ODKNB64 __fastcall operator+(kODKNB64& KU64L, kODKNB64& KU64P);
      friend ODKNB64 __fastcall operator+(kODKNB64& KU64L, NB32 dwArg);
      friend ODKNB64 __fastcall operator+(NB32 dwArg, kODKNB64& KU64P);
      // ���� � ���� ��������� ����������� ��� ���� ���������: ++
      friend ODKNB64& __fastcall operator++(ODKNB64& KU64L);
     // �����: -= - --  // ��� ������� ������ ���� ��������� = 0:
      // ��������� � ����������� ����������: -=
      ODKNB64& __fastcall operator-=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator-=(NB32 dwArg);
      friend NB32& __fastcall operator-=(NB32& dwArg, kODKNB64& KU64P);
      // ���������: -
      friend ODKNB64 __fastcall operator-(kODKNB64& KU64L, kODKNB64& KU64P);
      friend ODKNB64 __fastcall operator-(kODKNB64& KU64L, NB32 dwArg);
      friend ODKNB64 __fastcall operator-(NB32 dwArg, kODKNB64& KU64P);
      // ���� � ���� ��������� ����������� ��� ���� ���������: --
      friend ODKNB64& __fastcall operator--(ODKNB64& KUI64);
     // ��������: *= *  // ��� ������������ ��������� ������������:
      // ��������� � ����������� ����������: *=
      ODKNB64& __fastcall operator*=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator*=(NB32 dwArg);
      friend NB32& __fastcall operator*=(NB32& dwArg, kODKNB64& KU64P);
      // ���������: *
      friend ODKNB64 __fastcall operator*(kODKNB64& KU64L, kODKNB64& KU64P);
      friend ODKNB64 __fastcall operator*(kODKNB64& KU64L, NB32 dwArg);
      friend ODKNB64 __fastcall operator*(NB32 dwArg, kODKNB64& KU64P);
     // ���������: /= / :
      // ������� � ����������� ����������: /=
      ODKNB64& __fastcall operator/=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator/=(NB32 dwArg);
      friend NB32& __fastcall operator/=(NB32& dwArg, kODKNB64& KU64P);
      // �������: /
      friend ODKNB64 __fastcall operator/(kODKNB64& KU64L, kODKNB64& KU64P);
      friend ODKNB64 __fastcall operator/(kODKNB64& KU64L, NB32 dwArg);
      friend ODKNB64 __fastcall operator/(NB32 dwArg, kODKNB64& KU64P);
     // ��������� �� ������: %= %  :
      // ������� �� ������ � ����������� ����������: %=
      ODKNB64& __fastcall operator%=(kODKNB64& KUI64);
      ODKNB64& __fastcall operator%=(NB32 dwArg);
      friend NB32& __fastcall operator%=(NB32& dwArg, kODKNB64& KU64P);
      // ������� �� ������: %
      friend ODKNB64 __fastcall operator%(kODKNB64& KU64L, kODKNB64& KU64P);
      friend ODKNB64 __fastcall operator%(kODKNB64& KU64L, NB32 dwArg);
      friend ODKNB64 __fastcall operator%(NB32 dwArg, kODKNB64& KU64P);
      // ����������:
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
      // ����������:
      ODKNB64& operator()()                  {EK_1=0UL; EK_2=0UL; return *this;}
      ODKNB64& operator()(NB32 dwArg)      {EK_1=dwArg; EK_2=0UL; return *this;}
      ODKNB64& operator()(NB32 dwArg2, NB32 dwArg)
                                        {EK_1=dwArg; EK_2=dwArg2; return *this;}
      // ��� �������������� � ���� unsigned int:
      operator unsigned int() const                               {return EK_1;}
#ifdef __ODDEF32_H
      // ��� �������������� � ���������� ��������� ���� int:
      operator DANET() const                               {return (EK_1|EK_2);}
#elif _WINDEF_
      // ��� �������������� � ���������� ��������� ���� int:
      operator BOOL() const                                {return (EK_1|EK_2);}
#else
      // ��� �������������� � ���� int:
      operator int() const                                        {return EK_1;}
#endif
      // ��� �������������� � ���� ���������� ��������� � 1 ����:
      operator bool() const                                {return (EK_1|EK_2);}
      // ��� �������������� � ���� unsigned long:
      operator NB32() const                                       {return EK_1;}
      // ��� �������������� � ���� long:
      operator long() const                                       {return EK_1;}
      // ��� �������������� � ���� NB16:
      operator NB16() const                                       {return EK_1;}
      // ��� �������������� � ���� short:
      operator short() const                                      {return EK_1;}
      // ��� �������������� � ���� unsigned char:
      operator unsigned char() const                              {return EK_1;}
      // ��� �������������� � ���� char:
      operator char() const                                       {return EK_1;}
      // ��� �������������� � ���� const char*:
      //operator const char*() const {return EK_1;}
      // ��� �������������� � ���� float. ��������� � FPU.387.:
      __fastcall operator float() const;
      // ��� �������������� � ���� double. ��������� � FPU.387.:
      __fastcall operator double() const;
      // ��� �������������� � ���� long double. ��������� � FPU.387.:
      __fastcall operator long double() const;
// �������: ()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()
   // �������� ������ � �������� ���� ������� ASCII �������� �������� ������:
      // VsStr() ��������� ������ ��������� ������ ���������.
      // ���������:
         // szByfer - ������� ����� ��� ������.
         // dwForm  - ����� ������:
            // ������� ���� �1 - ��������� ������ ����� ����� �������� ���� �2.
            // ��������: �������� 3 ��������� ����� 1234567890 ���
               // ����� 1 234 567 890.
            // ���� �2 - ���� �������� �����. ��� 0 ������.
            // ���� �3 - ������ ������� ������������.
            // ��������: �������� 10 ��������� ����� 12345 ���
               // ����� 0 000 012 345, � ����� 5 ��� 0 000 000 005.
         // lSisSch  - ������� ��������� 2 ������ ��������, 8 - ������������,
            // 10 - ������������, 16 - �����������������.
      // �������: ������ - ����� ������ � ������ ��� ����� ��������� ����.
               // ������ - 0.
      ONB32 __fastcall VsStr(iNB8 szByfer, NB32 dwForm, long lSisSch);
      // VsStr10() ��������� ������ ������������ ������� ���������.
      // ����� �����������:
#define  ODKNB64_STR10_BYFER   44  // ����������� ������ ������.
      // ���������: szByfer - ������� ����� ��� ������. ������ �� ����� 44 �����.
                 // dwForm  - ����� ������: �� �� ��� � � VsStr().
      ONB32 VsStr10(iNB8 szByfer, NB32 dwForm=3)
                                            {return VsStr(szByfer, dwForm, 10);}
// VsStr2() ��������� ������ �������� ������� ���������.
      // ����� �����������:
#define  ODKNB64_STR2_BYFER   132 // ����������� ������ ������.
      // ���������: szByfer - ������� ����� ��� ������. ������ �� ����� 132 �����.
                 // dwForm  - ����� ������: �� �� ��� � � VsStr().
      ONB32 VsStr2(iNB8 szByfer, NB32 dwForm=4)
                                             {return VsStr(szByfer, dwForm, 2);}
      // VsStr8() ��������� ������ ������������ ������� ���������.
      // ����� �����������:
#define  ODKNB64_STR8_BYFER   48  // ����������� ������ ������.
      // ���������: szByfer - ������� ����� ��� ������. ������ �� ����� 48 ����.
                 // dwForm  - ����� ������: �� �� ��� � � VsStr().
      ONB32 VsStr8(iNB8 szByfer, NB32 dwForm=3)
                                             {return VsStr(szByfer, dwForm, 8);}
      // VsStr16() ��������� ������ ����������������� ������� ���������.
      // ����� �����������:
#define  ODKNB64_STR16_BYFER   36 // ����������� ������ ������.
      // ���������: szByfer - ������� ����� ��� ������. ������ �� ����� 36 ����.
                 // dwForm  - ����� ������: �� �� ��� � � VsStr().
                 // ���� �4 - ���������� � ������� ������ "ABCDEF".
                       // ��������: �������� 32 ��������� ����� "ABCDEF" ���
                       // ����� "abcdef".
      ONB32 VsStr16(iNB8 szByfer, NB32 dwForm=2)
                                            {return VsStr(szByfer, dwForm, 16);}
   // ����� ������ � �������� ���� ������� ASCII ��� ��������� �������� ������:
      // VzStr() ��������� �������� �� ������ ��������� ������ ���������.
      // ���������: szStr - ������ � �������� dwForm ���� �3.
                    // ������ ������ ������������ ������� ���������: 98...210.
                       // ���������� �������� ���� �� ����� 20.
                    // ������ ������ ����������������� ������� ���������: 0xFE...210.
                       // ���������� �������� ���� �� ����� 16.
                    // ������ ������ ������������ ������� ���������: 0o76...210.
                       // ���������� �������� ���� �� ����� 22.
                    // ������ ������ �������� ������� ���������: 0b10.
                       // ���������� �������� ���� �� ����� 64.
                 // dwForm  - ����� ������:
                    // ������� ���� �1 - ��������� ������ ������, ����� ���� 0.
                    // ���� �2 - ���� �������� �����. ��� 0 ������.
                    // ���� �3 - ���� ��������� ������.
      // �������: ������ - 1.
               // ������ - 0.
      ONB32 __fastcall VzStr(kiNB8 szStr, NB32 dwForm=0);
};

// ����������� ��� ������:
#undef  kODKNB64
//typedef ODKNB64                 NB64;
//typedef const ODKNB64           kNB64;
//typedef ODKNB64*                iNB64;
//typedef const ODKNB64*          kiNB64;
//typedef ODKNB64&                sNB64;
//typedef const ODKNB64&          ksNB64;
typedef const ODKNB64  kODKNB64; // ����������� �������� ������ ODKNB64.      //
typedef ODKNB64*       iODKNB64; // ��������� �� ����� ODKNB64.               //
typedef const ODKNB64* kiODKNB64;// ����������� ��������� �� ������ ODKNB64.  //
typedef ODKNB64&       sODKNB64; // ������ �� ����� ODKNB64.                  //
typedef const ODKNB64& ksODKNB64;// ����������� ������ �� ������ ODKNB64.     //

#ifndef OD_NO_NAMESPACE
} // namespace OtDiatlovaOU.
#endif

#endif  // __ODKNB64_H
