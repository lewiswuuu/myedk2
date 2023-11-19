/** @file
    A simple, basic, application showing how the Hello application could be
    built using the "Standard C Libraries" from StdLib.

    Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
    This program and the accompanying materials
    are licensed and made available under the terms and conditions of the BSD License
    which accompanies this distribution. The full text of the license may be found at
    http://opensource.org/licenses/bsd-license.

    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/
//#include  <Uefi.h>
//#include  <Library/UefiLib.h>
//#include  <Library/ShellCEntryLib.h>

#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/ShellCEntryLib.h>
#include  <Library/DebugLib.h>

#include <Library/BaseMemoryLib.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
//#include <Protocol/SimpleTextInEx.h>
//#include <Library/PciLib.h>
//#include <Library/PciExpressLib.h>
//#include <IndustryStandard/Pci.h>
#include <Protocol/PciIo.h>						
#include <Protocol/PciRootBridgeIo.h>	
#include <IndustryStandard/Pci.h>  

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>



EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *gPCIRootBridgeIO;
EFI_PCI_IO_PROTOCOL *gPCIIO;
//Functions declare

EFI_STATUS LocatePCIRootBridgeIO(void);
EFI_STATUS LocatePCIIO(void);
EFI_STATUS PciDevicePresent (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridgeIo,
  OUT PCI_TYPE00                          *Pci,
  IN  UINT8                               Bus,
  IN  UINT8                               Device,
  IN  UINT8                               Func
  );
EFI_STATUS GetSpecifyPciDevice(
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridgeIo,
  OUT PCI_TYPE00                          *Pci,
  IN	UINT16 VendorID,
  IN	UINT16 DeviceID
  );
EFI_STATUS ListPCIMessage(void);


/***
  Demonstrates basic workings of the main() function by displaying a
  welcoming message.

  Note that the UEFI command line is composed of 16-bit UCS2 wide characters.
  The easiest way to access the command line parameters is to cast Argv as:
      wchar_t **wArgv = (wchar_t **)Argv;

  @param[in]  Argc    Number of argument tokens pointed to by Argv.
  @param[in]  Argv    Array of Argc pointers to command line tokens.

  @retval  0         The application exited normally.
  @retval  Other     An error occurred.
***/
int
main (
  IN int Argc,
  IN char **Argv
  )
{
	EFI_STATUS      Status;


	Status=LocatePCIRootBridgeIO();
	if (EFI_ERROR (Status)) 
	{
		Print(L"Call LocatePCIRootBridgeIO, Can't find protocol!\n");
	}
	else
	{
		Print(L"Call LocatePCIRootBridgeIO, Find protocol!\n");
	}
	// Status=LocatePCIIO();
	// if (EFI_ERROR (Status)) 
	// {
	// 	Print(L"Call LocatePCIIO, Can't find protocol!\n");
	// }
	// else
	// {
	// 	Print(L"Call LocatePCIIO, Find protocol!\n");
	// }
	ListPCIMessage();
	// Status=GetSpecifyPciDevice(gPCIRootBridgeIO,&Pci,0x9999,0x8000);
	// if (EFI_ERROR (Status)) 
	// {
	// 	Print(L"Call GetSpecifyPciDevice, Can't find device!\n");
	// }
	// else
	// {
	// 	Print(L"Call GetSpecifyPciDevice, device!\n");
	// 	Print(L"BaseAddress0 = %x\n",Pci.Device.Bar[0]);
	// 	Print(L"BaseAddress2 = %x\n",Pci.Device.Bar[1]);
	// 	Print(L"BaseAddress2 = %x\n",Pci.Device.Bar[2]);
	// 	Print(L"BaseAddress3 = %x\n",Pci.Device.Bar[3]);
	// 	Print(L"BaseAddress4 = %x\n",Pci.Device.Bar[4]);
	// 	Print(L"BaseAddress5 = %x\n",Pci.Device.Bar[5]);
		
	// }

}
	
//===========================================PCI function begin======================================
//Name: LocatePCIRootBridgeIO
//Input: 
//Output: *gPCIRootBridgeIO
//Descriptor:
EFI_STATUS LocatePCIRootBridgeIO(void)
{
	EFI_STATUS                         Status;
	EFI_HANDLE                         *PciHandleBuffer = NULL;
	UINTN                              HandleIndex = 0;
	UINTN                              HandleCount = 0;
	//get the handles which supports 
	Status = gBS->LocateHandleBuffer(
		ByProtocol,
		&gEfiPciRootBridgeIoProtocolGuid,
		NULL,
		&HandleCount,
		&PciHandleBuffer
		);
	if (EFI_ERROR(Status))	return Status;		//unsupport
//	if (EFI_ERROR(Status))	
//	{
//		Print(L"LocatePCIRootBridgeIO: err 1\n");
//		return Status;		//unsupport
//	}
	
	for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++)
	{
		Status = gBS->HandleProtocol(
			PciHandleBuffer[HandleIndex],
			&gEfiPciRootBridgeIoProtocolGuid,
			(VOID**)&gPCIRootBridgeIO);
		if (EFI_ERROR(Status))	continue;
		else
		{
			return EFI_SUCCESS;
		}
	}
	return Status;
}
//Name: LocatePCIIO
//Input: 
//Output: *gPCIIO
//Descriptor:
EFI_STATUS LocatePCIIO(void)
{
	EFI_STATUS                         Status;
	EFI_HANDLE                         *PciHandleBuffer = NULL;
	UINTN                              HandleIndex = 0;
	UINTN                              HandleCount = 0;
	//get the handles which supports 
	Status = gBS->LocateHandleBuffer(
		ByProtocol,
		&gEfiPciIoProtocolGuid,
		NULL,
		&HandleCount,
		&PciHandleBuffer
		);
	if (EFI_ERROR(Status))	return Status;		//unsupport
	for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++)
	{
		Status = gBS->HandleProtocol(
			PciHandleBuffer[HandleIndex],
			&gEfiPciIoProtocolGuid,
			(VOID**)&gPCIIO);
		if (EFI_ERROR(Status))	continue;
		else
		{
			return EFI_SUCCESS;
		}
	}
	return Status;
}
/**
  This routine is used to check whether the pci device is present.

  @param PciRootBridgeIo   Pointer to instance of EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.
  @param Pci               Output buffer for PCI device configuration space.
  @param Bus               PCI bus NO.
  @param Device            PCI device NO.
  @param Func              PCI Func NO.

  @retval EFI_NOT_FOUND    PCI device not present.
  @retval EFI_SUCCESS      PCI device is found.

**/

EFI_STATUS PciDevicePresent (
  IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridgeIo,
  OUT PCI_TYPE00                          *Pci,
  IN  UINT8                               Bus,
  IN  UINT8                               Device,
  IN  UINT8                               Func
  )
{
  UINT64      Address;
  EFI_STATUS  Status;
  
  // Create PCI address map in terms of Bus, Device and Func
  Address = EFI_PCI_ADDRESS (Bus, Device, Func, 0);
  // Read the Vendor ID register
  Status = PciRootBridgeIo->Pci.Read (
                                  PciRootBridgeIo,
                                  EfiPciWidthUint32,
                                  Address,
                                  1,
                                  Pci
                                  );

  if (!EFI_ERROR (Status) && (Pci->Hdr).VendorId != 0xffff) {
    // Read the entire config header for the device  
    Status = PciRootBridgeIo->Pci.Read (
                                    PciRootBridgeIo,
                                    EfiPciWidthUint32,
                                    Address,
                                    sizeof (PCI_TYPE00) / sizeof (UINT32),
                                    Pci
                                    );

    return EFI_SUCCESS;
  }

  return EFI_NOT_FOUND;
}

//Name: ListPCIMessage(void)
//Input:
//Output:
EFI_STATUS ListPCIMessage(void)
{
	EFI_STATUS                         Status=EFI_SUCCESS;
	PCI_TYPE00 Pci;
	UINT16 i,j,k,count=0;
	
	Print(L"NO.  Bus. Dev. Func. | Vendor. Device. ClassCode\n");
	for(k=0;k<256;k++)
		for(i=0;i<=PCI_MAX_DEVICE;i++)
			for(j=0;j<=PCI_MAX_FUNC;j++)
			{
				Status = PciDevicePresent(gPCIRootBridgeIO,&Pci,(UINT8)k,(UINT8)i,(UINT8)j);
				if (Status == EFI_SUCCESS)		//Find device
				{
					++count;
					Print(L" %d    %x    %x    %x",count,(UINT8)k,(UINT8)i,(UINT8)j);
					Print(L"       %x       %x        %x",Pci.Hdr.VendorId,Pci.Hdr.DeviceId,Pci.Hdr.ClassCode[0]);
					Print(L"\n");
				}
			}
	return EFI_SUCCESS;
}
//Name GetSpecifyPciDevice
//Input:
//Output:
EFI_STATUS GetSpecifyPciDevice(
	IN  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridgeIo,
  OUT PCI_TYPE00                          *Pci,
  IN	UINT16 VendorID,
  IN	UINT16 DeviceID
  )
{
	UINT8 Bus,Dev,Func;
	EFI_STATUS                         Status=EFI_NOT_FOUND;
	BOOLEAN myFlag=TRUE;
	//Find specify device
	for(Bus=0;Bus<=10;Bus++)		
		for(Dev=0;Dev<=PCI_MAX_DEVICE;Dev++)
			for(Func=0;Func<=PCI_MAX_FUNC;Func++)
			{
				if(myFlag)
				{
					Status = PciDevicePresent(gPCIRootBridgeIO,Pci,Bus,Dev,Func);
					if (Status == EFI_SUCCESS)		//Find device
					{
						Print(L"mes:   %x    %x    %x",Bus,Dev,Func);
						Print(L"       %x       %x        %x\n",(Pci->Hdr).VendorId,(Pci->Hdr).DeviceId,(Pci->Hdr).ClassCode[0]);
						if(((Pci->Hdr).VendorId == VendorID) && ((Pci->Hdr).DeviceId == DeviceID))
						{
							Status=EFI_SUCCESS;
							myFlag=FALSE;
							Print(L"GetSpecifyPciDevice OK,bus=%x,dev=%x,func=%d\n",Bus,Dev,Func);
							break;
						}
					}
				}
			}
	
	return Status;
}
//===========================================PCI function end======================================