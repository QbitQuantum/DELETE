//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Copyright © 2000-2005 OtDiatlovaOU™, RU, KZ, All Rights Reserved.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Module: main.cpp
//
//  НАЗНАЧЕНИЕ:  Демонстрирует работу класса ODKNB64                          //

// RU: table - 1251

#define  ODK_IMPORT    // Импорт класса.                                      //
#include <ODKNB64.h>   // Работа с целыми без знака 64-х битными числами.     //
#include <iostream.h>  //

using namespace OtDiatlovaOU;

int main()
{  char snBuff[0x100]; // Буфер для строк.
   int  i;
   // Объявление экземпляров:
   ODKNB64 n64A=0, n64B=0xFFFFFFFF, n64C=0xFFFFFFFF-1;

   // Преобразование числа в строку и вывод на экран:
   n64A.VsStr10(snBuff);
   cout<<"n64A = "<<snBuff<<endl;
   n64B.VsStr10(snBuff);
   cout<<"n64B = "<<snBuff<<endl;
   n64C.VsStr10(snBuff);
   cout<<"n64C = "<<snBuff<<endl;
   //
   
   // Матаматические операции, преобразование в строку и вывод:
   n64A=n64B+100;
   n64A.VsStr10(snBuff);
   cout<<"n64A = n64B + 100;  n64A = "<<snBuff<<endl;
   //
   n64A=n64B*n64C;
   n64A.VsStr10(snBuff);
   cout<<"n64A = n64B * n64C; n64A = "<<snBuff<<endl;
   //
   n64A/=88;
   n64A.VsStr10(snBuff);// формирует строку десятеричной системы счисления.   //
   cout<<"n64A /= 88; radix is 10 n64A = "<<snBuff<<endl;
   n64A.VsStr16(snBuff);// формирует строку шестнадцатеричной системы счисления.
   cout<<"n64A /= 88;  radix is 16 n64A = "<<snBuff<<endl;
   n64A.VsStr8(snBuff); // формирует строку восьмеричной системы счисления.   //
   cout<<"n64A /= 88;  radix is 8  n64A = "<<snBuff<<endl;
   n64A.VsStr2(snBuff); // формирует строку двоичной системы счисления.       //
   cout<<"n64A /= 88;  radix is 2  n64A = "<<snBuff<<endl;
   //
   // И так далее...
   //
   cin>>i;
   return 0;
}

