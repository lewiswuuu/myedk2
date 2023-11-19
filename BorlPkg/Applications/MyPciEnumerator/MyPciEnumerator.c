#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/IoLib.h>

CHAR16 *Describe[20] = {
    L" Device was built before Class Code definitions were finalized ",
    L"Mass storage controller.",
    L"Network controller.",
    L"Display controller.",
    L"Multimedia device.",
    L"Memory controller.",
    L"Bridge device.",
    L"Simple communications controllers.",
    L"Base system peripherals.",
    L"Input devices.",
    L"Docking stations.",
    L"Processors.",
    L"Serial bus controllers.",
    L"Wireless controllers.",
    L"Intelligent IO controllers.",
    L"Satellite communications controllers.",
    L"Encryption/Decryption controllers.",
    L"Data acquisition and signal processing controllers.",
    L"Reserved.",
    L"Device does not exist.",
};

UINT32 PciRead(UINT32 PciAddress) {
    UINT32 PciData;
    IoWrite32(0xcf8, PciAddress);
    PciData = IoRead32(0xcfc);
    return PciData;
}

EFI_STATUS EFIAPI UefiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    UINT32 PciAddress, PciData, Index;
    UINT16 DeviceId, VendorId;
    UINT8 ClassCode;
    for (UINT16 bus = 0; bus < 256; bus++) {
        for (UINT16 device = 0; device < 32; device++) {
            for (UINT16 func = 0; func < 8; func++) {
                PciAddress = 0x80000000 | (bus << 15) | (device << 10) | (func << 7);
                //read VendorId and DeviceId
                PciData = PciRead(PciAddress);
                VendorId = (UINT16)PciData & 0xffff;
                DeviceId = (UINT16)(PciData >> 16) & 0xffff;

                //read high byte of ClassCode
                Index = PciAddress | 0x08;
                PciData = PciRead(Index);
                ClassCode = (UINT8)(PciData >> 24) & 0xffff;

                if (VendorId != 0xffff && VendorId != 0) {
                    Print(L"Bus: %02d, Device: %02d, Func: %02d, VendorId: %02x, DeviceId: %02x, DeviceType: %s\n", bus, device, func,  VendorId, DeviceId, Describe[ClassCode]);
                }
                    
            }
        }
    }
    return EFI_SUCCESS;
}