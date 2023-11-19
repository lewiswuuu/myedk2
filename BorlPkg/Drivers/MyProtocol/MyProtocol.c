#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "MyProtocol.h"

EFI_STATUS
EFIAPI
Compare(EFI_COMPARE_PROTOCOL *This, UINT8 a, UINT8 b) {
    Print(L"the max number is %u\n", a > b ? a : b);
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MyProtocolEntry(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

    EFI_STATUS Status;
    EFI_COMPARE_PROTOCOL *CompareProtocol;

    CompareProtocol = AllocatePool(sizeof(CompareProtocol));
    if (NULL == CompareProtocol) {
        Print(L"Allocate COMPARE PROTOCOL failed\n");
        return EFI_OUT_OF_RESOURCES;
    }
    CompareProtocol->Compare = Compare;

    Status = gBS->InstallProtocolInterface(&ImageHandle, &gEfiCompareProtocolGuid, EFI_NATIVE_INTERFACE, (void *)CompareProtocol);

    if (EFI_ERROR(Status)){
        Print(L"CompareProtocol InstallProtocolInterface failed\n");
    }

    return EFI_SUCCESS;
}