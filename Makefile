# ========================================================================
# $File: Makefile $
# $Date: 2017-12-11 04:15:56 $
# $Revision: $
# $Creator: Jen-Chieh Shen $
# $Notice: See LICENSE.txt for modification and distribution information
#					Copyright © 2017 by Shen, Jen-Chieh $
# ========================================================================


### Application Makefile Template ###

#----------------------------------------------
# JayCeS project directories preference.
#----------------------------------------------
# .
# ├── build
# │   ├── alib
# │   └── bin
# │   └── solib
# ├── data
# ├── doc
# ├── lib
# │   ├── alib
# │   └── solib
# ├── misc
# ├── src
# └── test
#----------------------------------------------

### General ###
# version number
VER		   = 1.0.1
ROOT_DIR   = .
# Enter the name of the build file. could either be a dynamic
# link, executable, etc.
BIN_NAME = rtc

### Directories ###
# Build executable directory.
BIN_DIR = $(ROOT_DIR)/build/bin
# Build library directory.
ALIB_DIR = $(ROOT_DIR)/build/alib
# Build library directory.
SOLIB_DIR = $(ROOT_DIR)/build/solib

### Commands ###
# assembler type
ASM	 = nasm
# disassembler commands
DAMS = objdump
# compiler type
CC	 = gcc
# linker commands
LD	 = ld
# compile lib file commands
AR	 = ar

### Flags ##
# assemble flags
ASM_FLAGS	  =
# disassemble flags
DASM_FLAGS	  = -D
# compile flags
C_FLAGS		  = -Wall -lcurl
# linker flags
LD_FLAGS	  = -L
# include flags
INCLUDE_FLAGS = -I
# static link flags
AR_FLAGS	  = rcs
# dynamic link flags
SOR_FLAGS	  = -shared
# output flags
OUTPUT_FLAGS  = -o

### Library File ###
# static link library
ALIB  = a_lib_name.a
# dynamic link library
SOLIB = so_lib_name.so

### Source Path ###
MAIN_PATH		= $(ROOT_DIR)/test
SOURCE_PATH		= $(ROOT_DIR)/src

### Include Path ###
INCLUDE_PATH   = $(ROOT_DIR)/include

### Library path ###
A_LIB_PATH	= $(ROOT_DIR)/lib/alib
A_LIBS = $(wildcard $(A_LIB_PATH)/*)

SO_LIB_PATH	 := $(ROOT_DIR)/lib/solib
SO_LIBS := $(wildcard $(SO_LIB_PATH)/*)

### All Source ###
# main source
MAINSRC := $(sort $(wildcard $(MAIN_PATH)/*.asm $(MAIN_PATH)/*.c $(MAIN_PATH)/*.cpp))
# asm source
ASMSRC	:= $(sort $(wildcard $(SOURCE_PATH)/*.asm))
# c/c++ source
GSRC	:= $(sort $(wildcard $(SOURCE_PATH)/*.c $(SOURCE_PATH)/*.cpp))
# static link library source
ASRC	:= $(sort $(wildcard $(SOURCE_PATH)/*.c $(SOURCE_PATH)/*.cpp $(A_LIB_PATH)/*.c $(A_LIB_PATH)/*.cpp))
# shared link library source
SOSRC	:= $(sort $(wildcard $(SOURCE_PATH)/*.c $(SOURCE_PATH)/*.cpp $(SO_LIB_PATH)/*.c $(SO_LIB_PATH)/*.cpp))

### objs ###
# main object file
MAINOBJ := $(sort $(patsubst %.c,%.o, $(patsubst %.cpp,%.o, $(MAINSRC))))
# list of object files
OBJS	:= $(sort $(patsubst %.c,%.o, $(patsubst %.cpp,%.o, $(GSRC))))
# .a object files
AOBJS	:= $(sort $(patsubst %.c,%.o, $(patsubst %.cpp,%.o, $(ASRC))))
# .so object files
SOOBJS	:= $(sort $(patsubst %.c,%.o, $(patsubst %.cpp,%.o, $(SOSRC))))

### ASM objs ###
ASMOBJS := $(sort $(subst .asm,.o,$(ASMSRC)))

### Dependencies ###
DEPDIR := $(ROOT_DIR)/mkdepGDEP	  := $(patsubst %.c,$(DEPDIR)/%.d,$(patsubst %.cpp,$(DEPDIR)/%.d, $(GSRC)))
ASMDEP := $(patsubst %.asm,$(DEPDIR)/%.d,$(ASMSRC))


.PHONY : build compile clean realclean test

test :
	echo "Test command..."

build :
	$(CC) $(GSRC) $(MAINSRC) \
	$(INCLUDE_FLAGS) $(INCLUDE_PATH) \
	$(A_LIBS) \
	$(SO_LIBS) \
	$(LD_FLAGS) $(A_LIB_PATH) \
	$(OUTPUT_FLAGS) $(BIN_DIR)/$(BIN_NAME) \
	$(C_FLAGS)

# compile all the source file to object file.
compile : $(MAINOBJ) $(OBJS) $(AOBJS) $(SOOBJS)

# Clean the project.
clean :
	rm -f $(MAINOBJ) $(OBJS) $(LOBJS)

realclean :
	rm -f $(MAINOBJ) $(OBJS) $(LOBJS) $(KASMOBJS) $(LASMOBJS) $(ALIB) $(SOLIB)

# include dependencies.
-include $(GDEP)
-include $(ASMDEP)

# example of compile the program main file.
program_main.o : program_main.c
	$(CC) $(C_FLAGS) $(OUTPUT_FLAGS) $@ $<

# generate static link library.
$(ALIB) : $(AOBJS)
	$(AR) $(AR_FLAGS) $(ALIB_DIR)/$@ $^

# generate shared link library.
$(SOLIB) : $(SOOBJS)
	$(CC) $(SOR_FLAGS) \
	$(OUTPUT_FLAGS) $(SOLIB_DIR)/$@ $^
