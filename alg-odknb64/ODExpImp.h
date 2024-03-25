//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::)
//
// Copyright © 2000-2001 OtDiatlovaOU™, RU, KZ, All Rights Reserved.
//
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
//  МОДУЛЬ:   ODExpImp.h
//
//  НАЗНАЧЕНИЕ:  Определения для экспорта и импорта классов и функций.
//
//  КОМЕНТАРИИ:
//

// Для динамических библиотек:
// Выбрать:
//#define  ODF_EXPORT    // Экспорт класса. //
//#define  ODF_IMPORT    // Импорт класса.  //
#if   defined(ODF_EXPORT)// Определяется при создании динамической библиотеки.
#   undef  _ODF_DLL
#   define _ODF_DLL __declspec(dllexport)
#elif defined(ODF_IMPORT)// Определяется при связи с динамической библиотеки.
#   undef  _ODF_DLL
#   define _ODF_DLL __declspec(dllimport)
#else
#   undef  _ODF_DLL
#   define _ODF_DLL
#endif


// Выбрать:
//#define  ODK_EXPORT    // Экспорт класса. //
//#define  ODK_IMPORT    // Импорт класса.  //
#if   defined(ODK_EXPORT)// Определяется при создании динамической библиотеки.
#   undef  _ODK_DLL
#   define _ODK_DLL __declspec(dllexport)
#elif defined(ODK_IMPORT)// Определяется при связи с динамической библиотеки.
#   undef  _ODK_DLL
#   define _ODK_DLL __declspec(dllimport)
#else
#   undef  _ODK_DLL
#   define _ODK_DLL
#endif

