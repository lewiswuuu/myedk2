#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/ShellCEntryLib.h>
#include <Library/UefiBootServicesTableLib.h>    // gST, gBS
#include <Library/UefiRuntimeServicesTableLib.h> // gRT
#include <stdio.h>
#include <stdlib.h>

int main(IN int Argc, IN char **Argv) {
    EFI_TIME curTime;
    printf("Hello, this is Entry of main!\n");
    gBS->Stall(2000);
    gRT->GetTime(&curTime, NULL);
    printf("Current Time: %d-%d-%d %02d:%02d:%02d\n", curTime.Year, curTime.Month, curTime.Day, curTime.Hour, curTime.Minute, curTime.Second);
    gST->ConOut->OutputString(gST->ConOut, L"Test SystemTable...\r\n");

    return 0;
}