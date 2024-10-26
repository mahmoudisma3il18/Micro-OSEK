###########################################################################
# projectCfg.mk
# 	Contains project-specific configurations.Defines variables for project
# 	directories, source directories, include paths, and library paths.
# Author: Shiry Ezzat
###########################################################################




PROJ 	= OS_HSM

# Project folders directories
PROJDIR	:=	../../TC399x/HSM/
EWDIR	:=	../Executable/
OSPROJDIR	:=../

# Folder names
MAIN	=	Main
SSW		= 	Ssw
APPLICATION = Application/
SSWSRC	=	Ssw/src
SSWINC	=	Ssw/inc
REG		=	Reg
MCAL	=	Mcal/
INC		=	inc
SRC		=	src
BRIDGE	=	Mcal/Bridge/
TRNG	=	Mcal/TRNG/
NVIC	=	Mcal/NVIC/
TIMER   =   Mcal/Timer/
AES     =   Mcal/AES/
HASH    =   Mcal/Hash/
CMAC    =   Mcal/CMAC/
HMAC    =   Mcal/HMAC/
KEY    =   Application/KeyM/


MAIN_SRCDIR	=	$(PROJDIR)$(MAIN)
SSW_SRCDIR	=	$(PROJDIR)$(SSWSRC)
REG_SRCDIR	=	$(PROJDIR)$(REG)

# Do not change the macro name only change the directories
SRCDIR		+=	$(MAIN_SRCDIR) \
				$(SSW_SRCDIR) \
				$(REG_SRCDIR) \
				$(PROJDIR)$(BRIDGE)$(SRC) \
				$(PROJDIR)$(TRNG)$(SRC) \
				$(PROJDIR)$(NVIC)$(SRC) \
				$(PROJDIR)$(TIMER)$(SRC) \
				$(PROJDIR)$(APPLICATION)$(SRC) \
				$(PROJDIR)$(AES)$(SRC) \
				$(PROJDIR)$(CMAC)$(SRC) \
				$(PROJDIR)$(HASH)$(SRC) \
				$(PROJDIR)$(HMAC)$(SRC) \
				$(PROJDIR)$(KEY)$(SRC) \
				
OSSRCDIR	+=	$(OSPROJDIR)$(SRC)/kernel \
				$(OSPROJDIR)$(SRC)/user \
				$(OSPROJDIR)generate \
				$(OSPROJDIR)Port/Cortex-M4/src

OSASDIR		+=	$(OSPROJDIR)Port/Cortex-M4/src

INCS	:=	-I"$(PROJDIR)" \
			-I"$(PROJDIR)$(MAIN)" \
			-I"$(PROJDIR)$(SSWINC)" \
			-I"$(PROJDIR)$(REG)" \
			-I"$(PROJDIR)$(BRIDGE)$(INC)" \
			-I"$(PROJDIR)$(TRNG)$(INC)" \
			-I"$(PROJDIR)$(NVIC)$(INC)" \
			-I"$(PROJDIR)$(TIMER)$(INC)" \
			-I"$(PROJDIR)$(APPLICATION)$(INC)" \
			-I"$(PROJDIR)$(AES)$(INC)" \
			-I"$(PROJDIR)$(CMAC)$(INC)" \
			-I"$(PROJDIR)$(HASH)$(INC)" \
			-I"$(PROJDIR)$(HMAC)$(INC)" \
			-I"$(PROJDIR)$(KEY)$(INC)" \
			-I"../../AutoSar/BSW/static/MCAL/Infrastructure/Platform" \
			-I"../../TC399x/Host Core\CryptoKeyManagement\inc" \
			-I"$(OSPROJDIR)include/External" \
			-I"$(OSPROJDIR)include/Internal" \
			-I"$(OSPROJDIR)include/memmap" \
			-I"$(OSPROJDIR)generate" \
			-I"$(OSPROJDIR)Port/Cortex-M4/inc"

LIBS	:=

LKDIR	:=	$(PROJDIR)Linkerscript/
LK_LSL	:=	$(LKDIR)HSM_LINKER.lsl