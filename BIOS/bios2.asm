


jmp DATA_END

FAILED_TO_FIND_BOOTLOADER:
	ds "Failed to find bootable medium"
	db 0x0

FOUND_BOOTLOADER:
	ds "Found bootable medium, booting"
	db 0x0

BOOT_SIGNATURE_ERR:
	ds "Failed to find "


DATA_END:
