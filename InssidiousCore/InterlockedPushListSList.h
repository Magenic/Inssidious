#ifndef INTERLOCKEDPUSHLISTSLIST_H
#define INTERLOCKEDPUSHLISTSLIST_H

/* To use the InterlockedPushListSList API with a Windows 8+ SDK, NTDDI & WIN32_WINNT must be Win7 or earlier */
/* And _CONTRACT_GEN must be defined, and APISET_INTERLOCKE_VER must be 0x0100 or lower */
/* Defining those allows the use of the InterlockedPushListSList. */

#define NTDDI_VERSION 0x06010000
#define _WIN32_WINNT 0x0601
#define _CONTRACT_GEN
#define _APISET_INTERLOCKED_VER 0x0100

/* Though that also stops synchapi.h from defining the Sleep api, so that's here manually now */

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"

extern "C"
WINBASEAPI VOID WINAPI Sleep(_In_ DWORD dwMilliseconds);

#pragma comment(lib, "kernel32.lib")

extern "C"
PSLIST_ENTRY __fastcall InterlockedPushListSList(
IN PSLIST_HEADER ListHead,
IN PSLIST_ENTRY List,
IN PSLIST_ENTRY ListEnd,
IN ULONG Count
);



#endif //INTERLOCKEDPUSHLISTSLIST_H