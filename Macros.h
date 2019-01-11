#ifndef VANIR_MACROS_H
#define VANIR_MACROS_H

#if defined(_WIN32)
#ifndef PLATFORM_WINDOWS
#define PLATFORM_WINDOWS
#endif
#if !defined(_WIN64)
#define PLATFORM_32
#else
#define PLATFORM_64
#endif

#elif defined(__APPLE__)
#ifndef PLATFORM_MACOSX
#define PLATFORM_MACOSX
#endif
#if !defined(__ppc64__)
#define PLATFORM_32
#else
#define PLATFORM_64
#endif

#elif  defined(__linux__)
#ifndef PLATFORM_LINUX
#define PLATFORM_LINUX
#endif
#if !defined(__LP64__)
#define PLATFORM_32
#else
#define PLATFORM_64
#endif
#endif

#if defined(_DEBUG)
#ifndef CONFIGURATION_DEBUG
#define CONFIGURATION_DEBUG
#endif
#else
#ifndef CONFIGURATION_RELEASE
#define CONFIGURATION_RELEASE
#endif
#endif

#if defined(_UNICODE) || defined(UNICODE)
#define CHARSET_UNICODE
#else
#define CHARSET_MBCS
#endif

#define SAFE_DELETE(pointer) \
    if ((pointer)) \
    { \
        delete (pointer); \
        (pointer) = nullptr; \
    }

#endif /* VANIR_MACROS_H. */