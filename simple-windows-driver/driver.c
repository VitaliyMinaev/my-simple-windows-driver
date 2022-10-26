#include "driver.h"

UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\Device\\mydevice-driver");
UNICODE_STRING SymbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\mydevice-driver-link");

PDEVICE_OBJECT DeviceObject = NULL;

NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT driverObject,
	_In_ PUNICODE_STRING registryPath
) 
{
	DbgPrintEx(0, 0, ("[win-driver]"__FUNCTION__));
	NTSTATUS status;

	driverObject->DriverUnload = DriverUnload;

	status = IoCreateDevice(driverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, 
		FILE_DEVICE_SECURE_OPEN, FALSE, &DeviceObject);

	if (!NT_SUCCESS(status)) {
		DbgPrintEx(0, 0, ("Creating device failed! \r\n"));
		return status;
	}

	status = IoCreateSymbolicLink(&SymbolicLinkName, &DeviceName);

	if (!NT_SUCCESS(status)) {
		DbgPrintEx(0, 0, ("Creating symbolic link failed! \r\n"));
		IoDeleteDevice(DeviceObject);

		return status;
	}

	DbgPrintEx(0, 0, ("Driver has been loaded \r\n"));

	return status;
}

VOID DriverUnload(
	_In_ PDRIVER_OBJECT driverObject)
{
	IoDeleteSymbolicLink(&SymbolicLinkName);
	IoDeleteDevice(DeviceObject);

	DbgPrintEx(0, 0, ("Driver has been unloaded \r\n"));
}