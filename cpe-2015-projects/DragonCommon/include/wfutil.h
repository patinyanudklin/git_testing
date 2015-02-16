/*
 *	filename wfutil.h
 *		$Revision: 1.6 $ $Date: 2014/12/05 09:58:46 $	
 *
 *      ~~ Copyright 1989-2014 Kurt Rudahl and Sally Goldin
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
 ****************************************************************
 *
 *	Requirements:
 *	   
 *	   dtypes.h dlimits.h dhead.h
 *
 ****************************************************************
 *
 *	prototypes etc for wfutil.c  8/89 ktr
 *
 ****************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 * 8/14/92 ktr	removed host.h
 * 1/22/95 ktr	minor syntax  changes for MSC v 8.5
 * 5.5	2005-2-16 ktr	import from Dragon 5.4.4
 */

#ifndef WFUTIL_H
#define WFUTIL_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef WF_H
typedef struct 
	{
	char	*str;		/* command string */
	void	(*fnct)(char**); /* command to execute */
	int	nargs;		/* # of commandline arguments */
	char	*descr;		/* description for pr_ops */
	} 
	CMDS;			/* command table */

#endif

void cputs(char *);
/* SINT16 cat(char *,char *); */
int pr_ioerr(int);
int xcut_cmd(char **, CMDS *,char *);

     /* calculate and return a 32-bit checkup
      */
UINT32 checksum(const void * pData, const size_t uSize);

#ifdef __cplusplus
}
#endif

#endif
