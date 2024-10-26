###########################################################################
# compilerCfg.mk
# 	Contains configurations related to the selected compiler. Defines
# 	the TASKING compiler used for the project. Depending on the specified 
# 	TASKING compiler, appropriate configurations are included.
# Author: Shiry Ezzat
###########################################################################

# Tasking Compiler	: ctc	|	carm
TASKING_COMPILER 	:= carm

# Change to 'info' in case 'echo' doesn't work
ECHO	:=echo

include projectCfg.mk
include compiler.mk

# # Control Program options
# CPC_FLAGS	= 	-o $(@D)/${@F} $(<D)/${<F} -Ctc39x --lsl-core=tc0 -t $(INCS) ${AS_FLAGS} --iso=11 ${CC_FLAGS} \
# 				-c --dep-file="$(@D)/.${@F}.d" -Wc--make-target="$(@D)/${@F}"

# # C Compiler options 
# CC_FLAGS	=	-Wc-g2 --language=-gcc,-volatile,+strings,-kanji --fp-model=3 \
# 				--switch=auto --align=0 --default-near-size=0 --default-a0-size=0 --default-a1-size=0 \
# 				-O2 --tradeoff=4 --compact-max-size=200 -g --error-limit=42 --source

# # Assembler options 
# AS_FLAGS	= -Wa-gAHLs --emit-locals=-equs,-symbols -Wa-Ogs -Wa--error-limit=42 

# # Linker options 
# LD_FLAGS	=	-o "$(EWDIR)$(PROJ).elf" ${OBJ} $(LIBS) \
# 				-Ctc39x --lsl-core=tc0 -t $(LK_FLAGS) -g --fp-model=3 -Wl--dep-file="$(EWDIR).$(PROJ).elf.d" \
# 				-Wl--make-target="$(EWDIR)$(PROJ).elf"

# LK_FLAGS	= 	$(LK_LSL) -Wl-OtxycL --no-map-file -Wl--map-file="$(EWDIR)$(PROJ).map" -Wl-mcrfiklSmNOduQ \
# 				-Wl--error-limit=42
# LK_UNUSED	= -dextmem.lsl -D__NO_VTC -D__CPU__=tc39x -D__PROC_TC39X__ -Wl--core=mpe:tc0