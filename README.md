ScancodeViewer
==============

ScancodeViewer is a utility for viewing key scancodes and names on Windows.
This tool is meant to be of use in creating
[scancode maps](https://msdn.microsoft.com/en-us/library/windows/hardware/jj128267.aspx#Scan_code_mapper_for_keyboards)
to remap keys. In the Scancode Map registry entry, keys can be remapped by
listing the scan codes to remap to and from, respectively. The program can be
terminated by pressing Ctrl-C.

For instance, if a user wished to remap Caps Lock (scancode 0x3a) to Esc
(scancode 0x01), they would set
`HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Keyboard Layout\Scancode
Map` to a REG_BINARY value of

    00 00 00 00 (Version Information)
    00 00 00 00 (Flags)
    02 00 00 00 (Number of Mappings including Null Terminator)
    01 00 3a 00 (Individual Mapping)
    00 00 00 00 (Null Terminator)
