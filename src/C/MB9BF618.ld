/* MB9BF618 Memory Definitions */

MEMORY
{
  ROM (rx) : ORIGIN = 0x00000000, LENGTH = (1024k)	/* Flash: 1M */
  RAM (w) : ORIGIN = 0x1FFF0000, LENGTH = (128k)	/* Both SRAM banks: 128k */
  RAM0 (w) : ORIGIN = 0x1FFF0000, LENGTH = (64k)	/* SRAM bank 0: 64k */
  RAM1 (w) : ORIGIN = 0x20000000, LENGTH = (64k)	/* SRAM bank 1: 64k */
}

/* higher address of the user mode stack */
_estack = ORIGIN(RAM)+LENGTH(RAM);

_hend = _estack - (16k);

/* Section Definitions */

SECTIONS
{
  /* .text section has program code, constants and read-only data. */
  /* It is located in ROM. */
  .text :
  {
	KEEP(*(.VECTOR))	/* Exception vector table */
	*(.text .text.*)	/* Program code */
	*(.gnu.linkonce.t*)
	*(.gcc_except_table)
	*(.rodata .rodata.*)	/* Read-only data (constants) */
	*(.gnu.linkonce.r*)
  } > ROM

   .ARM.excep :			/* Data table for library exception handling */
  {
	*(.ARM.exidx*)
	*(.ARM.extab*)
  } > ROM

  . = ALIGN(4);
  _etext = .;		/* End of .text section */
  _sidata = .;		/* Start of the initialization values of the .data section */


  /* .data section has static objects with initial value. It is located in RAM */
  /* but the content is placed to ROM area just below .text section. */
  /* This section will be initialized with the ROM data by startup code. */
  .data : AT (_sidata)
  {
	_sdata = .;	/* Start of .data section */
	*(.data .data.*)
	*(.gnu.linkonce.d*)
	. = ALIGN(4);
	_edata = .;	/* End of .data section */
  } > RAM


  /* .bss section has static oobjects with no initial value. */
  /* This section will be filled with zero by startup code to meet ANSI C standard. */
  .bss (NOLOAD) : ALIGN(4)
  {
	_sbss = .;	/* Start of .bss section */
	*(.bss .bss.*)
	*(.gnu.linkonce.b*)
	*(COMMON)
	. = ALIGN(4);
	_ebss = .;	/* End of .bss section */
  } > RAM
  __bss_end__ = . ;
  PROVIDE (__bss_end = .);

	.heap (NOLOAD) : 
	{
		_end = .;
		end = .;
		PROVIDE(_end = .);
		PROVIDE(end = .);
		PROVIDE(_heap = .);
		*(.heap)
		*(.heap.*)
		*(.HEAP)
		. = ALIGN(4);
		. = ABSOLUTE(_hend);
	} > RAM
	. = ALIGN(4);
	_heap_end = .;
	PROVIDE(_heap_end = .);

  .stack (NOLOAD) : 
  {
	_stack_top = . ;
	PROVIDE(_stack_top = .);
	*(.stack)
	*(.STACK)
	_stack = .;
	PROVIDE(_stack = .);
  } > RAM
  . = ALIGN(8);
  _stack_end = .;
  PROVIDE(_stack_end = .);

    /DISCARD/ :
    {
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
    }

  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }

	.note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
	.ARM.attributes 	0 : { KEEP (*(.ARM.attributes)) }
	/DISCARD/ : { *(.note.GNU-stack) }
	/DISCARD/ : { *(.gnu.lto*) }
}
