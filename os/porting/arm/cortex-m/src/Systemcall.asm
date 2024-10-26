
.extern OS_syscallTable
.extern Kern_Schedule
.extern UpdateTaskPSP
.extern Kernel
.extern Os_CreateStackFrame

.section .text
.thumb


.equ SVC_NUMBER_SHIFT,	    -2
.equ LR_SHIFT,	    		0	
.equ R4_SHIFT,	 			4
.equ R5_SHIFT,	 			8
.equ TEMP_STACK_FOOT_PRINT, 12

	
.equ OS_N_SYSCALL, 			21	
.equ PC_SHIFT, 				24
.equ PC_POSITION,		    24

.equ SchedulerNeededFlag,	18
.equ NoSchedulerNeeded,		0
	
.equ DispatcherNeededFlag,	19
.equ NoDispatcherNeeded,	0	

.equ NewContextFlag,    	20
.equ TaskStackInitNeeded,	1	
	
	
.global SVC_Handler
.global NewTaskStackInit
.global SaveAndSwitchContext

	
 SVC_Handler:
 
	MRS R0, PSP
	LDMIA R0,{R0, R1, R2, R3}
	
	MRS  R3,PSP
	LDR  R3,[R3,#PC_SHIFT]
	LDRB R3 ,[R3,#-2]
	
	CMP R3,#OS_N_SYSCALL
	BHS InvalidSysCall
	BLO	SystemCall
	
InvalidSysCall:

	BX    LR
	
SystemCall:
	
	SUB   SP,SP,#TEMP_STACK_FOOT_PRINT
	
    STR   R4,[SP,#R4_SHIFT]
    STR   R5,[SP,#R5_SHIFT]

    MOV   R4,LR
    STR   R4,[SP,#LR_SHIFT]
	
	
	LDR   R4,= OS_syscallTable
    LSLS  R3,R3,#2
    LDR   R3,[R4,R3]
		
	CPSID I
	
    BLX   R3
	
    MRS   R4,psp
    STR   R0,[R4]
	
	LDR   R4,= Kernel
	LDRB  R5,[R4,#SchedulerNeededFlag]
	CMP   R5,#NoSchedulerNeeded
	BEQ   RestoreNoContextSwitch
	
	PUSH {LR}
	
	BL Kern_Schedule
	
	POP {LR}
	
	ldr   R4,= Kernel
    ldrb  R5,[R4,#DispatcherNeededFlag]
    cmp   R5,#NoDispatcherNeeded
    beq   RestoreNoContextSwitch
	
	ldr   R4,= Kernel
    ldrb  R5,[R4,#NewContextFlag]
    cmp   R5,#TaskStackInitNeeded
    beq   NewTaskStackInit

	b	  RestoreMspContent
	
RestoreNoContextSwitch:
	
    LDR   R4,[SP,#LR_SHIFT]
    MOV   LR,R4
	
    LDR   R5,[SP,#R5_SHIFT]
    LDR   R4,[SP,#R4_SHIFT]

    ADD   SP,SP,#TEMP_STACK_FOOT_PRINT

    CPSIE I   	

	BX LR
	
	
NewTaskStackInit:
		
	PUSH {LR}
	PUSH {R0}
	
	BL Os_CreateStackFrame
	
	pop {R0}
	POP {LR}
	
    cmp   R0,#50
    beq   SaveAndSwitchContext	
	
	B RestoreMspContent
	
RestoreMspContent:

	LDR   R4,[sp,#LR_SHIFT]
    MOV   LR,R4
	
    LDR   R4,[SP,#R4_SHIFT]
    LDR   R5,[SP,#R5_SHIFT]
	
	ADD   SP,SP,#TEMP_STACK_FOOT_PRINT
	
	B SaveAndSwitchContext

SaveAndSwitchContext:	
	
	
	MRS   R0, PSP
	
	
	STMDB R0!, {R4 - R11}
	
	
	PUSH {LR}

	
	BL UpdateTaskPSP
	
	
	LDMIA R0!,{R4-R11}

	
	MSR PSP,R0
	
	
	POP {LR}
	
	
	CPSIE I
	
	PUSH {R0}
	
	MRS R0,CONTROL
	ORR R0,R0,#0x01
	MSR CONTROL,R0
	
	POP {R0}
	
	
	BX LR
	
.endsec
