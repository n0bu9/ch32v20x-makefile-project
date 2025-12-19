##### Project #####

PROJECT			?= app
# The path for generated files
BUILD_DIR		= build

##### Options #####

# Include NetLib, y:yes, n:no
USE_NET_LIB		?= n
# Build with FreeRTOS, y:yes, n:no
USE_FREERTOS	?= n


##### Toolchains #######

#GCC_TOOCHAIN	?= /opt/gcc-riscv/xpack-riscv-none-embed-gcc-10.2.0-1.2/bin
#GCC_TOOCHAIN	?= /opt/gcc-riscv/xpack-riscv-none-elf-gcc-12.2.0-3/bin
#GCC_TOOCHAIN	?= /opt/gcc-riscv/riscv-wch-embedded-gcc-v1.60/bin
GCC_TOOCHAIN	?= /home/gary/workplace/toolchain/wch_risc_development/Toolchain/risc-v_embedded_gcc/bin

# riscv-none-embed- or riscv-none-elf-
GCC_PREFIX		?= riscv-none-embed-

OPENOCD_PATH	?= /home/user/mcu_wp/WCH_RISCV/OpenOCD/OpenOCD/bin

##### Paths ############

LDSCRIPT		= libraries/Ld/Link.ld
OPENOCD_CFG 	= misc/wch-riscv.cfg
# CH32V203: CH32V20x_D6
# CH32V203RB: CH32V20x_D8
# CH32V208: CH32V20x_D8W
LIB_FLAGS		= CH32V20x_D6

# C source folders
CDIRS	:= user \
		libraries/Core \
		libraries/Debug \
		libraries/Peripheral/src
# C source files (if there are any single ones)
CFILES := 

# ASM source folders
ADIRS	:= user
# ASM single files
AFILES	:= libraries/Startup/startup_ch32v20x_D6.S

LIBS 	:= 

# Include paths
INCLUDES	:= user \
		libraries/Core \
		libraries/Debug \
		libraries/NetLib \
		libraries/Peripheral/inc

##### Optional Libraries ############

ifeq ($(USE_NET_LIB),y)
CDIRS		+= libraries/NetLib
INCLUDES	+= libraries/NetLib
LIBS		+= libraries/NetLib/libwchnet.a
endif

ifeq ($(USE_FREERTOS),y)
ADIRS		+= libraries/FreeRTOS/portable/GCC/RISC-V

CDIRS		+= libraries/FreeRTOS \
			libraries/FreeRTOS/portable/GCC/RISC-V

CFILES		+= libraries/FreeRTOS/portable/MemMang/heap_4.c

INCLUDES	+= libraries/FreeRTOS/include \
			libraries/FreeRTOS/portable/GCC/RISC-V \
			libraries/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions
endif


include ./rules.mk
