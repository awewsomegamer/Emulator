# Szikra Emulator

Emulator for the Szikra assembler
# CLI Usage

`-i` specifies input file (program terminates if this is not specified) <br>
`-org` specifies where to load the program (defaults to 0) <br>
`-mmax` specifies the maximum amount of 32 bit unsigned integers the program can use (defaults to 65535) <br>
`-disk` specifies the binary "disk" to read from and write to.<br>
`-rom` specifies ROM, this includes the BIOS.<br>

# Random Access Memory Map

No map

# IO Port Map

<table>
	<tr>
		<th>Address</th>
		<th>Size</th>
		<th>Description</th>
		<th>Bit Description</th>
	</tr>
	<tr>
		<th>0x0</th>
		<th>uint32_t</th>
		<th>Keyboard port</th>
		<th>
			<pre>
0 +--------------+ 16 +-----------------------------------+ 24 +------+ 32
  | SDL scancode |    | 0x00 (Pressed) or 0xFF (Released) |    | 0x00 |
			</pre>
		</th>
	</tr>
</table>

# Read Only Memory Map

All of it is BIOS for now