###########################################################################
# makefile
# 	Orchestrates the compilation and linking of the project. Defines rules
# 	for compiling source files, linking object files, and cleaning up the
# 	binaries. Includes configuration files and defines variables used
#	throughout the build process.
# Author: Shiry Ezzat
###########################################################################

include compilerCfg.mk


# CFILES and OSCFILES macro contains all the (.c) files with their original directory
# 	this is a static macro should not be changed
# 	it takes all the source files directories and searches for the (.c) files in them
CFILES	=	$(foreach D,$(SRCDIR),$(wildcard $(D)/*.c))
OSCFILES=	$(foreach D,$(OSSRCDIR),$(wildcard $(D)/*.c))

# OSASFILES macro contains all the (.s) files with their original directory
# 	this is a static macro should not be changed
# 	it takes all the assembly files directories and searches for the (.s) files in them
OSASFILES=	$(foreach D,$(OSASDIR),$(wildcard $(D)/*.asm))

# OBJ and OSOBJ macro contains all the (.o) files with the executable directory
# 	this is a static macro should not be changed
# 	it changes the project directory of the (.c) files, and substitutes the suffix .c with .o
OBJ		=	$(patsubst %.c,%.o,$(subst $(PROJDIR),$(EWDIR),${CFILES}))
OSOBJ	=	$(patsubst %.c,%.o,$(subst $(OSPROJDIR),$(EWDIR),${OSCFILES}))

# OSASOBJ macro contains all the (.o) files with the executable directory
# 	this is a static macro should not be changed
# 	it changes the project directory of the (.s) files, and substitutes the suffix .c with .o
OSASOBJ	=	$(patsubst %.asm,%.o,$(subst $(OSPROJDIR),$(EWDIR),${OSASFILES}))

# DEPFILES macro contains all the dependancy files with the executable directory
# 	this is a static macro should not be changed
# 	it loops for each objects file in OBJ, takes the directoery and concatenats it with .<filename>.o.d
DEPFILES=	${foreach T, ${OBJ} , $(dir $(T)).$(notdir $(T)).d}
OSDEPFILES=	${foreach T, ${OSOBJ} , $(dir $(T)).$(notdir $(T)).d}


all : "${PROJ}.elf"

"${PROJ}.elf" : ${OBJ} ${OSOBJ} ${OSASOBJ}
	@-${ECHO} Linking to ${@F}
	@${CPC}	$(LD_FLAGS)

-include $(DEPFILES)
-include $(OSDEPFILES)

# NOTE:
# 	the directory of ${OBJ} must be the same as $(EWDIR)%.o
#	substituded the shared part between the original source directory and the object directory and by %
# This way solves the problem of putting the object files in different directory than the source files
# 	without the need to force recompile each time, note how this way handles all the source codes from 
# 	different directories without the need of making a dependancy rule for each directory
${OBJ}: $(EWDIR)%.o : $(PROJDIR)%.c
	$(info Compiling ${<F})
	@${CPC} $(CPC_FLAGS)

${OSOBJ}: $(EWDIR)%.o : $(OSPROJDIR)%.c
	$(info Compiling ${<F})
	@${CPC} $(CPC_FLAGS)

${OSASOBJ}: $(EWDIR)%.o : $(OSPROJDIR)%.asm
	$(info Assembling ${<F})
	@${AS} -o $(@D)/${@F} $(<D)/${<F} -gAHLs --error-limit=42 


# Create all the directories in OBJ, -p creates any needed parent directory
create_dir:
	@-mkdir -p $(dir ${OBJ}) $(dir ${OSOBJ}) 2>/dev/null || true

CLEANFILES	=	$(foreach D,$(dir ${OBJ}) $(dir ${OSOBJ}),$(wildcard $(D).*) $(wildcard $(D)*)) $(EWDIR).* $(EWDIR)*.elf  $(EWDIR)*.map  $(EWDIR)*.mdf
# Clean all the contents of the Executable folder
clean:
	@-rm -r -f $(CLEANFILES) 2> /dev/null || true
	$(info All clean)

.PHONY: clean create_dir