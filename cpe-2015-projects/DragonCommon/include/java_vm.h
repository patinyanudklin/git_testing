/*
 *	filename java_vm.h - Create or destroy a Java VM for jni
 *                           Starting with Java 1.6, this has become 
 *	  		     quite complex
 *		$Id: java_vm.h,v 1.3 2011/01/12 04:42:34 rudahl Exp $
 *
 *      ~~ Copyright 2010 Kurt Rudahl and Sally Goldin
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *
 *	Use, duplication, or disclosure by the U.S. Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *
 *	The moral right of the copyright holder is hereby asserted
 *	~~ EndC
 *
 ********************************************************************
 * $Id: java_vm.h,v 1.3 2011/01/12 04:42:34 rudahl Exp $
 * $Log: java_vm.h,v $
 * Revision 1.3  2011/01/12 04:42:34  rudahl
 * added new registration fields to update_georef and header
 *
 * Revision 1.2  2010/10/10 04:21:27  rudahl
 * fixed for java 1.6 per OpenDragon
 *
 * Revision 1.1  2010/09/10 04:29:40  rudahl
 * for java 1.6
 *
 *
 ********************************************************************
 *   Maintain a database for status and other persistent info
 *
 * The methods in this class are specific to the needs of Dragon,
 * and are not at all a generic or orthogonal set of relational DB 
 * functions.
 *
 * class SSDb is a base class for use with different DB systems
 * class SSDbSqlite is the subclass for SQLite.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.10	2010-09-09 ktr	created
 ********************************************************************
 */

#ifndef JAVA_VM_H
#define JAVA_VM_H 1

// function which can be used as value for pLog in SetupJVM
// this fn is not needed for the viewport
void printMsg(const char * pczMessage,...);
typedef void (Log_t)(const char *,...);

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
 */
int SetupJVM(int bTest,void ** pEnv,JavaVMOption * pOptions,int iOptcount,
           BOOL bVerbose,Log_t * pLog);

jint DestroyJVM();

#endif
