//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::)
//
// Copyright � 2000-2001 OtDiatlovaOU�, RU, KZ, All Rights Reserved.
//
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
//  ������:   ODExpImp.h
//
//  ����������:  ����������� ��� �������� � ������� ������� � �������.
//
//  ����������:
//

// ��� ������������ ���������:
// �������:
//#define  ODF_EXPORT    // ������� ������. //
//#define  ODF_IMPORT    // ������ ������.  //
#if   defined(ODF_EXPORT)// ������������ ��� �������� ������������ ����������.
#   undef  _ODF_DLL
#   define _ODF_DLL __declspec(dllexport)
#elif defined(ODF_IMPORT)// ������������ ��� ����� � ������������ ����������.
#   undef  _ODF_DLL
#   define _ODF_DLL __declspec(dllimport)
#else
#   undef  _ODF_DLL
#   define _ODF_DLL
#endif


// �������:
//#define  ODK_EXPORT    // ������� ������. //
//#define  ODK_IMPORT    // ������ ������.  //
#if   defined(ODK_EXPORT)// ������������ ��� �������� ������������ ����������.
#   undef  _ODK_DLL
#   define _ODK_DLL __declspec(dllexport)
#elif defined(ODK_IMPORT)// ������������ ��� ����� � ������������ ����������.
#   undef  _ODK_DLL
#   define _ODK_DLL __declspec(dllimport)
#else
#   undef  _ODK_DLL
#   define _ODK_DLL
#endif

