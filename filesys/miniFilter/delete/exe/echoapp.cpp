/*++

Copyright (c) Microsoft Corporation

Module Name:

    EchoApp.cpp

Abstract:

    An application to exercise the Minifilter "delete" sample driver.


Environment:

    user mode only

--*/


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int __cdecl
main(
    _In_ int argc,
    _In_reads_(argc) char* argv[]
    )
{
    UNREFERENCED_PARAMETER( argc );
    UNREFERENCED_PARAMETER( argv );

    WCHAR tempPath[MAX_PATH] = {0};
    auto ret = GetTempPath(MAX_PATH, tempPath);
    if (ret > MAX_PATH || !ret)
    {
        printf("ERROR Failed to get temporary path!\n");
        return 1;
    }
    printf("Path to temporary directory: %ws\n", tempPath);

    auto tempName = lstrcat(tempPath, L"test_xyz.txt");
    if (!tempName)
    {
        printf("ERROR Failed to get temporary name!\n");
        return 1;
    }

    auto hFile = CreateFile(tempName, GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, nullptr);
    if (INVALID_HANDLE_VALUE == hFile)
    {
        printf("ERROR Failed to CreateFile\n");
        return 1;
    }

    printf("CreateFile(\"%ws\")\n", tempName);

    UCHAR buffer[1000];
    INT bufferSize = sizeof(buffer);
    for (INT i = 0; i < bufferSize; i++)
        buffer[i] = 0x20 + i % 0x5e;

    OVERLAPPED overlapped = {0};
    overlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    if (!overlapped.hEvent)
    {
        printf("ERROR Failed to create event!\n");
    }
    else if (!WriteFile(hFile, buffer, bufferSize, nullptr, &overlapped))
    {
        if (GetLastError() == 997)
            printf("INFO Pending write\n");
        else
            printf("ERROR Failed to write file (%d)!\n", GetLastError());
    }

    ResetEvent(overlapped.hEvent);
    CloseHandle(overlapped.hEvent);
    CloseHandle(hFile);
    DeleteFile(tempName);

    return 0;
}
