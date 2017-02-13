// stdafx.cpp : source file that includes just the standard includes
//	WinTextFilePatch.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

BOOL PeekAndPump()
{
  static MSG msg;

  while(::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
  {
     if(!AfxGetApp()->PumpMessage())
    {
        ::PostQuitMessage(0);
        return FALSE;
     }   
  }

  return TRUE;
}