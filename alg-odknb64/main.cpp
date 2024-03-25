//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Copyright � 2000-2005 OtDiatlovaOU�, RU, KZ, All Rights Reserved.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Module: main.cpp
//
//  ����������:  ������������� ������ ������ ODKNB64                          //

// RU: table - 1251

#define  ODK_IMPORT    // ������ ������.                                      //
#include <ODKNB64.h>   // ������ � ������ ��� ����� 64-� ������� �������.     //
#include <iostream.h>  //

using namespace OtDiatlovaOU;

int main()
{  char snBuff[0x100]; // ����� ��� �����.
   int  i;
   // ���������� �����������:
   ODKNB64 n64A=0, n64B=0xFFFFFFFF, n64C=0xFFFFFFFF-1;

   // �������������� ����� � ������ � ����� �� �����:
   n64A.VsStr10(snBuff);
   cout<<"n64A = "<<snBuff<<endl;
   n64B.VsStr10(snBuff);
   cout<<"n64B = "<<snBuff<<endl;
   n64C.VsStr10(snBuff);
   cout<<"n64C = "<<snBuff<<endl;
   //
   
   // �������������� ��������, �������������� � ������ � �����:
   n64A=n64B+100;
   n64A.VsStr10(snBuff);
   cout<<"n64A = n64B + 100;  n64A = "<<snBuff<<endl;
   //
   n64A=n64B*n64C;
   n64A.VsStr10(snBuff);
   cout<<"n64A = n64B * n64C; n64A = "<<snBuff<<endl;
   //
   n64A/=88;
   n64A.VsStr10(snBuff);// ��������� ������ ������������ ������� ���������.   //
   cout<<"n64A /= 88; radix is 10 n64A = "<<snBuff<<endl;
   n64A.VsStr16(snBuff);// ��������� ������ ����������������� ������� ���������.
   cout<<"n64A /= 88;  radix is 16 n64A = "<<snBuff<<endl;
   n64A.VsStr8(snBuff); // ��������� ������ ������������ ������� ���������.   //
   cout<<"n64A /= 88;  radix is 8  n64A = "<<snBuff<<endl;
   n64A.VsStr2(snBuff); // ��������� ������ �������� ������� ���������.       //
   cout<<"n64A /= 88;  radix is 2  n64A = "<<snBuff<<endl;
   //
   // � ��� �����...
   //
   cin>>i;
   return 0;
}

