#ifndef _MY_PROTOCOL_H
#define _MY_PROTOCOL_H

#include <Uefi.h>

#define EFI_COMPARE_PROTOCOL_GUID \
    { 0xc6e4e42a, 0x4858, 0x4f03, {0xa3, 0xad, 0x22, 0xed, 0xb5, 0x22, 0x14, 0xc2 } }

typedef struct _EFI_COMPARE_PROTOCOL EFI_COMPARE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *COMPARE)(IN EFI_COMPARE_PROTOCOL *This, IN UINT8 a, IN UINT8 b);

struct _EFI_COMPARE_PROTOCOL {
    COMPARE Compare;
};

extern EFI_GUID gEfiCompareProtocolGuid;

#endif