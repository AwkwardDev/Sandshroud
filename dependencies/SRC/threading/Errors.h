/***
 * Demonstrike Core
 */

#pragma once

#if PLATFORM == PLATFORM_WIN && defined(CRASHHANDLER_ENABLED)
#define WPAssert2( assertion ) { if( !(assertion) ) { fprintf( stderr, "\n%s:%i ASSERTION FAILED:\n  %s\n", __FILE__, __LINE__, #assertion ); CThreadPool::Suicide(); } }
#endif

#define WPAssert( assertion ) { if( !(assertion) ) { fprintf( stderr, "\n%s:%i ASSERTION FAILED:\n  %s\n", __FILE__, __LINE__, #assertion ); assert(assertion); } }
#define WPError( assertion, errmsg ) if( ! (assertion) ) { bLog.outError( "%s:%i ERROR:\n  %s\n", __FILE__, __LINE__, (char *)errmsg ); assert( false ); }
#define WPWarning( assertion, errmsg ) if( ! (assertion) ) { bLog.outError( "%s:%i WARNING:\n  %s\n", __FILE__, __LINE__, (char *)errmsg ); }

// This should always halt everything.  If you ever find yourself wanting to remove the assert( false ), switch to WPWarning or WPError
#define WPFatal( assertion, errmsg ) if( ! (assertion) ) { bLog.outError( "%s:%i FATAL ERROR:\n  %s\n", __FILE__, __LINE__, (char *)errmsg ); assert( #assertion &&0 ); abort(); }

// An assert isn't necessarily fatal, although if compiled with asserts enabled it will be.
#if PLATFORM == PLATFORM_WIN && defined(_DEBUG) && defined(CRASHHANDLER_ENABLED)
#define ASSERT WPAssert2
#else
#define ASSERT WPAssert
#endif