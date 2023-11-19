#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include "../MyProtocol/MyProtocol.h"

EFI_STATUS
EFIAPI
MyProtocolUser(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable){

    EFI_STATUS Status;
    EFI_COMPARE_PROTOCOL *Protocol;
    Status = gBS->LocateProtocol(&gEfiCompareProtocolGuid, NULL, (void **)&Protocol);
    if (EFI_ERROR(Status)){
        Print(L"Locate Compare Protocol failed\n");
    }
    Protocol->Compare(Protocol, 4, 8);
    return EFI_SUCCESS;
}