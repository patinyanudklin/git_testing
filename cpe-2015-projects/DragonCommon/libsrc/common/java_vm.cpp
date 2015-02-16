#include "drelease.h"
extern "C" const char JAVA_VM_ID[] 
    = "\0@(#) " __FILE__ " $Revision: 1.6 $$Date: 2014/12/10 11:10:34 $";
//***************************************************************
//
//          java_vm.cpp - Create or destroy a Java VM for jni
//                        Starting with Java 1.6, this has become 
//			  quite complex
//
//          ~~ Copyright 2010-2014 by Kurt Rudahl and Sally Goldin
//
//	All rights are reserved. Copying or other reproduction of
//	this program except for archival purposes is prohibited
//	without the prior written consent of Goldin-Rudahl Associates.
//
//			  RESTRICTED RIGHTS LEGEND
//
//	Use, duplication, or disclosure by the U.S. Government
//	is subject to restrictions as set forth in
//	paragraph (b) (3) (B) of the Rights in Technical
//	Data and Computer Software clause in DAR 7-104.9(a).
//
//	The moral right of the copyright holder is hereby asserted
//	~~ EndC
//***************************************************************
//	Developers
// 		ktr	Kurt Rudahl
//		seg	Sally Goldin
//
//	Revision History
// 5.10	2010-09-09 ktr	created
//
//***************************************************************
//   $Id: java_vm.cpp,v 1.6 2014/12/10 11:10:34 rudahl Exp $
//   $Log: java_vm.cpp,v $
//   Revision 1.6  2014/12/10 11:10:34  rudahl
//   _PRODUCT_ in identifier line was problematic
//
//   Revision 1.5  2014/12/05 14:24:30  rudahl
//   reconciled DragonProfessional with OpenDragon
//
//   Revision 1.4  2010/10/10 08:49:34  rudahl
//   remove redundant PRODUCT defn
//
//   Revision 1.3  2010/10/10 04:21:27  rudahl
//   fixed for java 1.6 per OpenDragon
//
//   Revision 1.2  2010/10/03 12:26:11  rudahl
//   incorporated changes from OpenDragon as of 2010-10-3
//
//   Revision 1.1.2.2  2010/09/20 06:21:31  rudahl
//   changed SetupJVM for tracing
//
//   Revision 1.1.2.1  2010/09/11 11:18:10  rudahl
//   perlim. support tracing
//
//   Revision 1.1  2010/09/10 04:30:17  rudahl
//   for java 1.6
//

#include <stddef.h>	// offsetof
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#if defined __GCC__ || defined __MINGCC__
#include <unistd.h>
#define _snprintf snprintf
#endif

#if ! defined __GCC__
#include <io.h>   	// for _access 
#include <dos.h>	/* needed for _getdiskfree */
#include <direct.h>	/* needed for _chdrive */
#include <windows.h>
#endif

#include "dtypes.h"
//#include "dlimits.h"
#include "jni.h"
#include "java_vm.h"

/*************************************************************************
 * 
 * functions inspired by java_md.c in java source
 *
 * The code here is quite different, and customized for Dragon
 * However, the (rather incomprehensible) comments have been
 * copied to here for their poetic beauty.
 *
 *************************************************************************/
#if ! defined __GCC__

#define MAXPATHLEN 2048
#define JVM_DLL "jvm.dll"
#define JAVA_DLL "java.dll"
#define CRT_DLL "msvcr71.dll"

/*
 * The preJVMStart is a function in the jkernel.dll, which 
 * performs the final step of synthesizing back the decomposed 
 * modules  (partial install) to the full JRE. Any tool which 
 * uses the  JRE must peform this step to ensure the complete synthesis.
 * The EnsureJreInstallation function calls preJVMStart based on
 * the conditions outlined below, noting that the operation
 * will fail silently if any of conditions are not met.
 * NOTE: this call must be made before jvm.dll is loaded, or jvm.cfg
 * is read, since jvm.cfg will be modified by the preJVMStart.
 * 1. Are we on a supported platform.
 * 2. Find the location of the JRE or the Kernel JRE.
 * 3. check existence of JREHOME/lib/bundles
 * 4. check jkernel.dll and invoke the entry-point
 */
typedef VOID (WINAPI *PREJVMSTART)();

// get the architecture flag based on the compiler flags
static const char * GetArch()
    {
#ifdef _M_AMD64
    return "amd64";
#elif defined(_M_IA64)
    return "ia64";
#else
    return "i386";
#endif
    }

/*
 * Find path to library file based on current location
 * look for it in current directory, or in jre1.6.0/bin/
 * @param path		where to store the path found with dllname appended
 * @param pathsize	size of buffer		
 * @param dllname	dll or other file we're seeking
 * @return		TRUE if found
 */
static BOOL GetLibPath(char *path, jint pathsize,const char * dllname,
		       BOOL bVerbose,Log_t * pLog)
    {
    char javadll[MAXPATHLEN];
    memset(path,0,pathsize);
    // first try the local directory
    strncpy(path,".\\",pathsize-1);
    _snprintf (javadll,sizeof(javadll),"%s%s",path,dllname);
    // next try jre1.6.0/bin
    if (_access(javadll, 0) != 0) 
        {
	strncpy(path,".\\jre1.6.0\\bin\\",pathsize-1);
        _snprintf (javadll,sizeof(javadll),"%s%s",path,dllname);
	}
    // next try system/jre1.6.0/bin
    if (_access(javadll, 0) != 0) 
        {
	strncpy(path,".\\system\\jre1.6.0\\bin\\",pathsize-1);
        _snprintf (javadll,sizeof(javadll),"%s%s",path,dllname);
	}
    // next try jre/bin
    if (_access(javadll, 0) != 0) 
        {
	strncpy(path,".\\jre\\bin\\",pathsize-1);
        _snprintf (javadll,sizeof(javadll),"%s%s",path,dllname);
	}
    // next try system/jre/bin
    if (_access(javadll, 0) != 0) 
        {
	strncpy(path,".\\system\\jre\\bin\\",pathsize-1);
        _snprintf (javadll,sizeof(javadll),"%s%s",path,dllname);
	}
    if (bVerbose)
        printf("dll path is %s\n", javadll);

    if (_access(javadll, 0) != 0) 
        {
	fprintf(stderr, "Error: could not find %s\n",dllname);
	return JNI_FALSE;
	}

    strncat(path,dllname,pathsize-strlen(path)-1);
    if (bVerbose)
        ( *pLog)("Library is at %s\n", path);
    return JNI_TRUE;
    }

static BOOL LoadMSVCRT(BOOL bVerbose,Log_t * pLog)
    {
    // Only do this once
    static BOOL bLoaded = FALSE;

    if (!bLoaded) 
        {
        /*
         * The Microsoft C Runtime Library apparently needs to be loaded first.
	 * A copy is assumed to be present in the "JRE path" directory.  
         */
	char crtpath[MAXPATHLEN];
	if (GetLibPath(crtpath, MAXPATHLEN, CRT_DLL, bVerbose, pLog)) 
	    {
	    if (LoadLibrary(crtpath) == 0) 
		{
		fprintf(stderr,"Error loading: %s", crtpath);
		return FALSE;
		}
	    }
	bLoaded = TRUE;
	}
    return TRUE;
    }

/* return 0 if OK */
static int EnsureJreInstallation(const char* jrepath,BOOL bVerbose,
				 Log_t * pLog) 
    {
    HINSTANCE handle;
    PREJVMSTART PreJVMStart;

    /* 32 bit windows only please */
    if (strcmp(GetArch(), "i386") != 0 ) 
        {
        if (bVerbose)
	    ( *pLog)("EnsureJreInstallation:unsupported platform\n");
	return -1;
	}
    /* Does jkernel dll exist ? */
    if (_access(jrepath, 0) != 0) 
        {
        if (bVerbose)
	    ( *pLog)("EnsureJreInstallation:<%s>:not found\n", jrepath);
        return -2;
	}
    /* The Microsoft C Runtime Library needs to be loaded first. */
    if (!LoadMSVCRT(bVerbose,pLog)) 
        {
        if (bVerbose)
	    ( *pLog)("EnsureJreInstallation:could not load C runtime DLL\n");
        return -3;
	}
    /* Load the jkernel.dll */
    if ((handle = LoadLibrary(jrepath)) == 0) 
        {
        if (bVerbose)
	    ( *pLog)("EnsureJreInstallation:%s:load failed\n", jrepath);
        return -4;
	}
    /* Get the function address */
    PreJVMStart = (PREJVMSTART)GetProcAddress(handle, "preJVMStart");
    if (PreJVMStart == NULL) 
        {
        if (bVerbose)
	    ( *pLog)("EnsureJreInstallation:preJVMStart:function lookup failed\n");
	FreeLibrary(handle);
	return -5;
	}
    PreJVMStart();
    if (bVerbose)
	( *pLog)("EnsureJreInstallation:preJVMStart:called\n");
    FreeLibrary(handle);
    return 0;
    } 

/*
 * Pointers to the needed JNI invocation API, initialized by LoadJavaVM.
 * from java.h
 */
typedef jint (JNICALL *CreateJavaVM_t)(JavaVM **pvm, void **env, void *args);
typedef jint (JNICALL *GetDefaultJavaVMInitArgs_t)(void *args);

typedef struct 
    {
    CreateJavaVM_t CreateJavaVM;
    GetDefaultJavaVMInitArgs_t GetDefaultJavaVMInitArgs;
    } InvocationFunctions;

/*
 * Load a jvm from "jvmpath" and initialize the invocation functions.
 */
static BOOL LoadJavaVM(const char *jvmpath, InvocationFunctions *ifn,
		       BOOL bVerbose,Log_t * pLog)
    {
    HINSTANCE handle;
    if (bVerbose)
	( *pLog)("JVM path is %s\n", jvmpath);

    /* The Microsoft C Runtime Library needs to be loaded first. */
    LoadMSVCRT(bVerbose,pLog);

    /* Load the Java VM DLL */
    if ((handle = LoadLibrary(jvmpath)) == 0) 
        {
	fprintf(stderr,"Error loading: %s\n", (char *)jvmpath);
	return JNI_FALSE;
        }

    /* Now get the function addresses */
    ifn->CreateJavaVM =
	(CreateJavaVM_t)GetProcAddress(handle, "JNI_CreateJavaVM");
    ifn->GetDefaultJavaVMInitArgs =
	(GetDefaultJavaVMInitArgs_t)GetProcAddress(handle,
						   "JNI_GetDefaultJavaVMInitArgs");
    if (ifn->CreateJavaVM == 0 || ifn->GetDefaultJavaVMInitArgs == 0) 
        {
	fprintf(stderr,"Error: can't find JNI interfaces in: %s\n", 
		(char *)jvmpath);
	return JNI_FALSE;
	}

    return JNI_TRUE;
    }
#endif // #if ! defined __GCC__

/*************************************************************************
 * 
 * end of functions inspired by java_md.c in java source
 *
 *************************************************************************/

#if defined __GCC__ || defined __MINGCC__
// function which can be used as value for pLog in SetupJVM
// this fn is not needed for the viewport
void printMsg(const char * pczMessage,...)
    {
    va_list marker;
    va_start(marker,pczMessage);
    vfprintf(stderr,pczMessage,marker);
    va_end(marker);
    }
#endif

static JavaVM * jvm = NULL;

/** create a jvm
 *  @param bTest
 *  @param pEnv		where env gets stored (JNIEnv **)
 *  @param pOptions	options used in creating VM
 *  @param iOptcount	how many options
 *  @param bVerbose	TRUE => show progress
 *  @param pLog		function to use to show progress
 *			usually printMsg, but logTrace for viewport
 *  @return		0 if OK 
 *			else error number:
 *			  -102 = could not find runtime environment
 *			  -104 = could not find JVM of specified type
 *			  -103 = EnsureJRE failed (run with -v for details)
 *			  -106 = could not load VM
 *			  -20 = could not load VM		
 *			  -24 = could not create VM		
 *			  others from CreateVM including -4=ENOMEM
 *			
 */
int SetupJVM(int bTest,void ** pEnv,JavaVMOption * pOptions,int iOptcount,
	     BOOL bVerbose,Log_t * pLog)
    {
    jint jret;
    int ret = -21;
    JavaVMInitArgs vm_args;
    vm_args.version = JNI_VERSION_1_2;
    //    JNI_GetDEfaultJavaVMInitArgs(&vm_args);
    vm_args.nOptions = iOptcount;
    vm_args.options = pOptions;
    vm_args.ignoreUnrecognized = JNI_TRUE; /* ~~ eventually FALSE */

#if ! defined __GCC__
    char s_msg[256];
    const char * pczJavaHome = getenv("JAVA_HOME"); /* for testing */
    if (bVerbose)
        (* pLog)("JavaHome is %p and test is %d version=x%X\n",
		pczJavaHome,bTest,vm_args.version);
    HINSTANCE hVM;
        {
	char jrepath[MAXPATHLEN] = ".";
	char jvmpath[MAXPATHLEN];
	char * jvmtype;
	InvocationFunctions ifn;
	/* Find out where the JRE is that we will be using. */
	if (!GetLibPath(jrepath, MAXPATHLEN,"jkernel.dll",bVerbose,pLog)) 
	    {
	    (* pLog)("Error: could not find Java SE Runtime Environment\n");
	    return -102;
	    }

    /* Do this before we read jvm.cfg */
	if (EnsureJreInstallation(jrepath,bVerbose,pLog))
	    return -103;
	ifn.CreateJavaVM = 0;
	ifn.GetDefaultJavaVMInitArgs = 0;

	jvmtype = "client\\" JVM_DLL; // CheckJvmType(_argc, _argv, JNI_FALSE);
	jvmpath[0] = '\0';
//	if (!GetJVMPath(jrepath, jvmtype, jvmpath, MAXPATHLEN))
	if (!GetLibPath(jvmpath, MAXPATHLEN, jvmtype, bVerbose, pLog)) 
	    {
	    const char * format = "Error: no `%s' JVM at `%s'.\n";
	    (* pLog)(format, jvmtype, jvmpath); 
	    return -104;
	    }
	if (!LoadJavaVM(jvmpath, &ifn, bVerbose, pLog))
	    {
	    (* pLog)("Error: LoadJavaVM\n");
	    return -106;
	    }

	}
#ifdef NOMORE
    if (bTest && (pczJavaHome != NULL))
        {
	int byteCount = strlen(pczJavaHome)+50;
	char * pczJvm = (char *)calloc(byteCount,1);
	if(pczJvm == NULL)
	    {
	    (* pLog)("Calloc of pczJvm failed - about to exit\n");
            return -101;
	    }
	sprintf(pczJvm,"%s%s",pczJavaHome,"\\jre\\bin\\client\\jvm.dll");
//	(* pLog)("loading '%s'\n",pczJvm);
        hVM = LoadLibrary(pczJvm);
	_snprintf(s_msg,sizeof(s_msg),"Branch 1 hVM = %p\n",hVM);
	free(pczJvm);
	}
    else 
        {
#endif
	char * pczDll = "msvcr71.dll";
	HINSTANCE hDLL = LoadLibrary(pczDll);
	char * pczJvm = "jvm.dll";
        hVM = LoadLibrary(pczJvm);
	_snprintf(s_msg,sizeof(s_msg),"Branch 2 jvm=%s hDLL=%p hVM = %p\n",
		 pczJvm,hDLL,hVM);
//	}
    if (bVerbose)
        (* pLog)(s_msg);
    void * pProcAddr;
    if (hVM == NULL)
        {
	(* pLog)("Could not load Java\n");
	if (bVerbose)
	    (* pLog)("SetupJVM (ex) returning -20\n");
	return -20;
	}
    pProcAddr = (void *)GetProcAddress(hVM,"JNI_CreateJavaVM");
    if (pProcAddr == NULL)
        {
	if (bVerbose)
	    (* pLog)("SetupJVM (ex) returning -22\n");
	return -22;
        } 
    if (bVerbose)
        (* pLog)("SetupJVM about to createJVM at %p\n",pProcAddr);
    jret = 
        (*(jint (*)(void *,void **, void *))pProcAddr)(&jvm,pEnv,&vm_args);
#else // if ! defined __GCC__
    if (bVerbose)
        (* pLog)("SetupJVM about to createJVM\n");
    jret = JNI_CreateJavaVM(&jvm,pEnv,&vm_args);
#endif
    //    if (jret == 0)
    //    ret = 0;
    ret = jret; // -4 => ENOMEM; others?
    if (bVerbose)
        (* pLog)("SetupJVM (ex) returning %d\n", ret);
    return ret;
    }

jint DestroyJVM()
    {
    jint retval = jvm->DestroyJavaVM();
    return retval;
    }
