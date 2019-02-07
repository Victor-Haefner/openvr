//========= Copyright Valve Corporation ============//
#include "sharedlibtools_public.h"
#include <string.h>
#include <stdio.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#if defined(POSIX)
#include <dlfcn.h>
#endif

SharedLibHandle SharedLib_Load( const char *pchPath )
{
#if defined( _WIN32)
	return (SharedLibHandle)LoadLibraryEx( pchPath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );
#elif defined(POSIX)
	SharedLibHandle h = (SharedLibHandle)dlopen(pchPath, RTLD_LOCAL|RTLD_NOW);
	if (!h) printf("dlopen failed: %s\n", dlerror());
	return h;
#endif
}

void *SharedLib_GetFunction( SharedLibHandle lib, const char *pchFunctionName)
{
#if defined( _WIN32)
	return (void*)GetProcAddress( (HMODULE)lib, pchFunctionName );
#elif defined(POSIX)
	return dlsym( lib, pchFunctionName );
#endif
}


void SharedLib_Unload( SharedLibHandle lib )
{
	if ( !lib )
		return;
#if defined( _WIN32)
	FreeLibrary( (HMODULE)lib );
#elif defined(POSIX)
	if (lib) dlclose( lib );
#endif
}


