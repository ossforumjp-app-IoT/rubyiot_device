#----------------------------------------------#
#     Makefile - project "rubyiot_device"      #
#     **This Makefile designed for FM3/FM4     #
#----------------------------------------------#

# Target Hardware (Choose FM3 or FM4)
HW = FM3

# Project Name (Set PROJECT)
PROJECT = rubyiot_device

# Built Sources and Objects (Set SRCS(*.c) and OBJDIR)
SRCS = main.c
ifeq ($(HW), FM3)
SRCS += startup_fm3_2.c mfs.c
else ifeq ($(HW), FM4)
SRCS += system_mb9abxxx.c mb9bf56x_vector.c
endif
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# Parameters to Generate mruby Bytecode (Set MRSDIR, MRSRCS and BYTENAME)
# -> It runs with Build Processing
MRSDIR = ../mruby
MRSRCS = rubyiot_device.rb
BYTENAME = mrbprcs
MRCFLAGS = -B$(BYTENAME)
BYTESRCS = $(MRSRCS:.rb=.c)
MRBOBJS = $(addprefix $(OBJDIR)/, $(MRSRCS:.rb=.o))
SRCDIR = .

# CPU
ifeq ($(HW), FM3)
CPU = cortex-m3
else ifeq ($(HW), FM4)
CPU = cortex-m4
endif

# Program to Build Project (Set CCDIR)
CCDIR = C:/Launchpad
CC = $(CCDIR)/bin/arm-none-eabi-gcc.exe
OBJCOPY = $(CCDIR)/bin/arm-none-eabi-objcopy.exe
OBJDUMP = $(CCDIR)/bin/arm-none-eabi-objdump.exe
SIZE = $(CCDIR)/bin/arm-none-eabi-size.exe
NM = $(CCDIR)/bin/arm-none-eabi-nm.exe

# Program to Flash Program (Set OCDDIR)
ifeq ($(HW), FM3)
OCDDIR = C:/ocd
else ifeq ($(HW), FM4)
OCDDIR = C:/openocd_0.9.0-dev_00038-gae3baa9_fm4/i686
endif
OCD = $(OCDDIR)/openocd.exe

# Program to Connect Debug (Set DBGDIR)
DBGDIR = C:/arm-none-eabi-insight
INSIGHT = $(DBGDIR)/bin/arm-none-eabi-insight.exe

#KEIL Directory (Set KEILDIR)
KEILDIR = C:/Keil_v5

# Directory of mruby (Set MRUBYDIR)
MRUBYDIR = C:/mruby-1.1.0
MRC = $(MRUBYDIR)/bin/mrbc.exe

# Directories of Include Files (Set directories)
INCDIR = .
INCDIR += $(CCDIR)/arm-none-eabi/include
INCDIR += $(KEILDIR)/ARM/Pack/ARM/CMSIS/3.20.4/CMSIS/Include

# Flash Program Setting (Set OCDMODE, WRITER and MPSSE)
OCDMODE = JTAG
WRITER = USBSTICK
MPSSE = ftdi
ifeq ($(WRITER), USBSTICK)
INTERFACECFG = openocd-usb.cfg
else ifeq ($(WRITER), ARM-USB-TINY-H)
INTERFACECFG = olimex-arm-usb-tiny-h.cfg
endif
ifeq ($(HW), FM3)
TARGETCFG = mb9bf618t_flash.cfg
else ifeq ($(HW), FM4)
TARGETCFG = mb9bf568_flash.cfg
endif
ifeq ($(OCDMODE), SWD)
ifeq ($(WRITER), VERSALOON)
OCDCMD = -s $(OCDDIR)/tcl -f interface/vsllink_swd.cfg -f target/mb9bf618t_flash.cfg
else ifeq ($(WRITER), STLINKV2)
OCDCMD = -s $(OCDDIR)/tcl -f interfaca/stlink-v2.cfg -f target/mb9bf618t_hla_flash.cfg
endif
else
OCDCMD = -s $(OCDDIR)/tcl -f interface/$(MPSSE)/$(INTERFACECFG) -f target/$(TARGETCFG)
endif

# Connect Debug Setting (Set DEBUG)
DEBUG = dwarf-2

# Optimization Level (Choose 0, 1, 2, 3, 4 or s)
OPTIMIZE = s

# Linker script for target MCU
ifeq ($(HW), FM3)
LINKSCRIPT = MB9BF618.ld
else ifeq ($(HW), FM4)
LINKSCRIPT = FLASH.ld MB9BF56x.ld MB9BF568.ld
endif

# Cross Compiler Flags (Set STD and WARNINGS)
STD = gnu89
WARNINGS = all extra
CFLAGS = -mthumb
CFLAGS += -mcpu=$(CPU)
CFLAGS += $(addprefix -I, $(INCDIR))
CFLAGS += -std=$(STD)
CFLAGS += -g$(DEBUG)
CFLAGS += -O$(OPTIMIZE)
CFLAGS += $(addprefix -W, $(WARNINGS))
CFLAGS += -mapcs-frame -fno-inline
CFLAGS += -Wp,-MM,-MP,-MT,$(OBJDIR)/$(*F).o,-MF,$(OBJDIR)/$(*F).d

# Linker Flags
LDFLAGS = -nostartfiles -Wl,-Map=$(OBJDIR)/$(PROJECT).map,--cref,--gc-sections
LDFLAGS += -lc -lgcc -lnosys
LDFLAGS += -lm
LDFLAGS += $(addprefix -T, $(LINKSCRIPT))

# mruby Flags
MRUBYCFLAGS = -I$(MRUBYDIR)/include
MRUBYLIBFLAGS = $(MRUBYDIR)/build/$(HW)/lib/libmruby.a

# -------- Build Processing --------
# run "make" to Build Project

# Built Targets(Set OUTPUT)
OUTPUT = hex
HEXFMT = ihex
ELF = $(OBJDIR)/$(PROJECT).elf
HEX = $(OBJDIR)/$(PROJECT).hex
BIN = $(OBJDIR)/$(PROJECT).bin
LST = $(OBJDIR)/$(PROJECT).lst
SYM = $(OBJDIR)/$(PROJECT).sym

TARGET = mrbbc
ifeq ($(OUTPUT), hex)
TARGET += $(ELF) $(HEX) $(LST) $(SYM)
else ifeq ($(OUTPUT), bin)
TARGET += $(ELF) $(BIN) $(LST) $(SYM)
else ifeq ($(OUTPUT), both)
TARGET += $(ELF) $(HEX) $(BIN) $(LST) $(SYM)
endif
TARGET += size

all: $(TARGET)

# Size Check
size:
	@echo ----------
	@echo Size Check...
	$(SIZE) -A $(ELF)
	
# Generating mruby Bytecode
mrbbc: $(BYTESRCS)
$(BYTESRCS): $(MRSDIR)/$(MRSRCS)
	@echo ----------
	@echo Generating mruby Bytecode...
	$(MRC) $(MRCFLAGS) $(MRSDIR)/$(MRSRCS)
	mv $(MRSDIR)/$(BYTESRCS) $(SRCDIR)

# Building hex File
$(HEX): $(ELF)
	$(OBJCOPY) -O $(HEXFMT) $(ELF) $(HEX)

# Building bin File
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $(BIN) $(ELF)

# Building lst File
$(LST): $(ELF)
	$(OBJDUMP) -h -S -C $(ELF) > $(LST)

# Building sym File
$(SYM): $(ELF)
	$(NM) -n $(ELF) > $(SYM)

# Building elf File
$(ELF): $(OBJS) $(MRBOBJS)
	@echo ----------
	@echo Linking...
	$(CC) $(CFLAGS) $(OBJS) $(MRBOBJS) $(MRUBYLIBFLAGS) -o $(ELF) $(LDFLAGS)

# Compileing C Sources
$(OBJS): $(OBJDIR)/%.o: %.c
	@echo ----------
	@echo Compiling $< ...
	$(CC) -c $(CFLAGS) $(MRUBYCFLAGS) $< -o $@

# Compileing mruby Bytecodes
$(MRBOBJS): $(BYTESRCS)
	@echo ----------
	@echo Compiling $(BYTESRCS) ...
	$(CC) -c $(CFLAGS) $(MRUBYCFLAGS) $< -o $@

# -------- Clean Processing --------
# run "make clean" to Clean

clean:
	rm -f -r $(OBJDIR)
	mkdir $(OBJDIR)
	rm $(BYTESRCS)

# -------- Program Processing --------
# run "make program" to Flash Program

program:
	$(OCD) $(OCDCMD) -c "mt_flash $(ELF)"

# -------- Debug Processing --------
# run "make debug" to Connect Debug

debug:
	cmd /c start /B $(INSIGHT) $(ELF)
	$(OCD) $(OCDCMD) -c"init" -c"reset halt"
