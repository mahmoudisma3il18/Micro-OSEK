###########################################################################
# compiler.mk
# 	Contains compiler-specific configurations and flags. Defines variables
# 	for the control program, C compiler, assembler, linker, and other 
# 	compiler-related tools. Depending on the selected TASKING compiler,
#	the appropriate set of tools and flags are defined.
# Author: Shiry Ezzat
###########################################################################

# TASKING used compilers
TRICORE_COMPILER	:=	ctc
ARM_COMPILER		:=	carm


ifdef TASKING_COMPILER	# Compiler used is TASKING
ifeq ($(TASKING_COMPILER),${TRICORE_COMPILER})	# The TASKING VX-toolset TriCore utilities
CPC 	:= cctc			# Control Program
AMKC	:= amk			# A make utility to maintain, update, and reconstruct groups of programs
MKC		:= mktc			# For backwards compatibility with older versions of the toolset
ECLIPC	:= eclipsec		# Eclipse console utility
ARCHC	:= artc			# Archiver
HLLODC	:= hldumptc		# A high level language (HLL) object dumper
ELFPC	:= elfpatch		# Make Changes in (.o), (.out) and (.a) files
EXPC	:= expiretc		# A utility to limit the size of the cache
PROFC	:= proftool		# A utility used by the TASKING Profiler perspective in Eclipse

CC		:= ctc			# C Compiler
AS		:= astc			# Assembler
LD		:= ltc			# Linker
AR		:= artc			# Archiver


# Control Program options
CPC_FLAGS	= 	-o $(@D)/${@F} $(<D)/${<F} -Ctc39x --lsl-core=tc0 -t $(INCS) ${AS_FLAGS} --iso=11 ${CC_FLAGS} \
				-c --dep-file="$(@D)/.${@F}.d" -Wc--make-target="$(@D)/${@F}"

# IDE
CC_FLAGS	=	-Wc-g2 --language=-gcc,-volatile,+strings,-kanji --fp-model=3 \
				--switch=auto --align=0 --default-near-size=0 --default-a0-size=0 --default-a1-size=0 \
				-O2 --tradeoff=4 --compact-max-size=200 -g --error-limit=42 --source
# # C Compiler options 
# CC_FLAGS	:= --core=tc1.6.x -D_CTRI --iso=99	\
# 			--language=-gcc,-strings --switch=auto --align=4 -ONRpfceogvIlywakmsU 		\
# 			--tradeoff=2 --compact-max-size=200 --max-call-depth=-1 --inline-max-incr=35\
# 			--inline-max-size=10 -g --misrac-version=2004 --immediate-in-code

# IDE
AS_FLAGS	= -Wa-gAHLs --emit-locals=-equs,-symbols -Wa-Ogs -Wa--error-limit=42 
# # Assembler options 
# AS_FLAGS 	:=--list-format=Ldegilmnpqrsvwxyz --optimize=gs --debug-info=+hll -il

LD_FLAGS	=	-o "$(EWDIR)$(PROJ).elf" ${OBJ} $(EXT_LIBRARIES) ${PCP_FILES} \
				-Ctc39x --lsl-core=tc0 -t $(LK_FLAGS) -g --fp-model=3 -Wl--dep-file="$(EWDIR).$(PROJ).elf.d" \
				-Wl--make-target="$(EWDIR)$(PROJ).elf"
# IDE
LK_FLAGS	= 	$(LK_LSL) -Wl-OtxycL --no-map-file -Wl--map-file="$(EWDIR)$(PROJ).map" -Wl-mcrfiklSmNOduQ \
				-Wl--error-limit=42

LK_UNUSED	=	-dextmem.lsl -D__NO_VTC -D__CPU__=tc39x -D__PROC_TC39X__ -Wl--core=mpe:tc0
# # Linker options 
# LD_FLAGS	:= -D__CPU__=tc39x --map-file -OtcxyL --core=mpe:vtc

else
ifeq ($(TASKING_COMPILER),${ARM_COMPILER})		# The TASKING VX-toolset ARM utilities
CPC 	:= ccarm		# Control Program
AMKC	:= amk			# A make utility to maintain, update, and reconstruct groups of programs
ECLIPC	:= eclipsec		# Eclipse console utility
ARCHC	:= ararm		# Archiver
HLLODC	:= hldumparm	# A high level language (HLL) object dumper
EXPC	:= expirearm	# A utility to limit the size of the cache

CC		:= carm			# C Compiler
AS		:= asarm		# Assembler
LD		:= lkarm --first-library-first		# Linker
AR		:= ararm		# Archiver	


# Control Program options
CPC_FLAGS	=	-o $(@D)/${@F} $(<D)/${<F} -Ccortex_m3 -t $(INCS) $(AS_FLAGS)-Wc-O0 \
				--iso=11 $(CC_FLAGS) -c --dep-file="$(@D)/.${@F}.d" -Wc--make-target="$(@D)/${@F}"	

# CPC_FLAGS	=	-o $(@D)/${@F} $(<D)/${<F} -Ccortex_m3 -t -Wa-gAHLs -Wa--error-limit=42 \
# 				$(INCS) \
# 				--iso=11 --language=-gcc,-volatile,+strings,-kanji -O1 --tradeoff=4 -g --error-limit=42 \
# 				--source --global-type-checking --dsp-library -c --dep-file="$(@D)/.${@F}.d" \
# 				-Wc--make-target="$(@D)/${@F}"


# C Compiler options 
CC_FLAGS	=	--language=-gcc,-volatile,+strings,-kanji -O1 --tradeoff=4\
 				-g --error-limit=42 --source --global-type-checking

# Assembler options 
AS_FLAGS	=	

# Linker options 
LD_FLAGS	=	-o "$(EWDIR)$(PROJ).elf" ${OBJ} ${OSOBJ} ${OSASOBJ} -Ccortex_m3 -t  \
				--fpu=none -g --global-type-checking $(LK_FLAGS)

# LD_FLAGS 	= 	-o "$(EWDIR)$(PROJ).elf" ${OBJ} ${OSOBJ} $(EXT_LIBRARIES) -Ccortex_m3 -t \
# 				-Wl-D__DEVICE_LSL_FILE=cm3.lsl "$(LK_LSL)" -Wl-OtZxycL \
# 				-Wl-mcrfiklSmNOduQ -Wl--error-limit=42 \
# 				--fpu=none -g --global-type-checking --dsp-library \
# 				-Wl--dep-file="$(EWDIR).$(PROJ).elf.d" -Wl--make-target="$(EWDIR)$(PROJ).elf"


# $(addprefix -Wl,$(LIBS)) --no-default-libraries

LK_FLAGS	=	--lsl-file=$(LK_LSL) -Wl-OtZxycL --no-map-file \
  				-Wl--map-file="$(EWDIR)$(PROJ).map" -Wl-mcrfiklSmNOduQ -Wl--error-limit=42 \
   				-Wl--dep-file="$(EWDIR).$(PROJ).abs.d" -Wl--make-target="$(EWDIR)$(PROJ).abs"

else
# Other Compilers

endif	# ifeq ($(TASKING_COMPILER),${TRICORE_COMPILER})	# TriCore Compiler
endif	# ifeq ($(TASKING_COMPILER),${ARM_COMPILER})		# ARM Compiler


endif	# ifdef TASKING_COMPILER	# Compiler used is TASKING