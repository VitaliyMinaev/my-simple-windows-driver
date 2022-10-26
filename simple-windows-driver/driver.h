#include <ntddk.h>



NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
);

VOID DriverUnload(
	_In_ PDRIVER_OBJECT DriverObject);