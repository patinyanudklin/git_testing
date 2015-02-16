@echo off
rem @(#) $RCSfile: setup-env.bat,v $$Revision: 1.1 $$Date: 2003/02/22 14:12:24 $
rem Setup-env.bat - setup environment for compiling this directory
rem usage: Setup-env
echo Initializing MSCompiler v 41.: %0
call Setup-MSVC32
set DEBUG=0
