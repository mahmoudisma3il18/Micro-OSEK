/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/
#include <Os_kernel.h>

extern void OS_CoretexIdle(void);

extern void OSEK_TASK_Task0 (void);
extern void OSEK_TASK_Task1 (void);



TaskPriorityType PriorityLevels [PRIORITY_LEVELS] = {2, 1};

TaskPriorityType PriorityLevelsSize [PRIORITY_LEVELS] = {1, 1};

Os_Task* PriorityLevel2Queue[1];
Os_Task* PriorityLevel1Queue[1];

Os_Task** PointerArrayToQueues [PRIORITY_LEVELS] = {
PriorityLevel2Queue,
PriorityLevel1Queue
};

TaskFlagsType Task0Flags =
{
	.Type = BASIC,
	.TaskSchedulingPolicy = FULL_PREEMPTIVE_SCHEDULING
};
TaskFlagsType Task1Flags =
{
	.Type = BASIC,
	.TaskSchedulingPolicy = FULL_PREEMPTIVE_SCHEDULING
};
TaskFlagsType IdleTaskFlags =
{
	.Type = BASIC,
	.TaskSchedulingPolicy = FULL_PREEMPTIVE_SCHEDULING
};





TaskStackType Task0Stack =
{
	.StackBase = (StackPtrType)0x20004000,
	.StackSize = 0x200,
};
TaskStackType Task1Stack =
{
	.StackBase = (StackPtrType)0x20004500,
	.StackSize = 0x200,
};
TaskStackType IdleTaskStack =
{
	.StackBase = (StackPtrType)0x20005000,
	.StackSize = 0x200,
};







Os_TaskDynamic Task0Dynamic =
{
	.Context = NULL_PTR,
	.Resources = NULL_PTR,
	.PriorityQueueIndex = 1,
	.EventsSet = 0,
	.EventsWaiting = 0,
	.TaskCurrentPriority = 1,
	.TaskState = SUSPENDED,
	.PendingActivationRequests = 0	
};
Os_TaskDynamic Task1Dynamic =
{
	.Context = NULL_PTR,
	.Resources = NULL_PTR,
	.PriorityQueueIndex = 0,
	.EventsSet = 0,
	.EventsWaiting = 0,
	.TaskCurrentPriority = 2,
	.TaskState = SUSPENDED,
	.PendingActivationRequests = 0	
};
Os_TaskDynamic IdleTaskDynamic =
{
	.Context = NULL_PTR,
	.Resources = NULL_PTR,
	.PriorityQueueIndex = 3,
	.EventsSet = 0,
	.EventsWaiting = 0,
	.TaskCurrentPriority = 0,
	.TaskState = SUSPENDED,
	.PendingActivationRequests = 0	
};

Os_Task Tasks[TASK_COUNT] =
{
	{
		.TaskStaticPriority = 1,
		.TaskID = Task0_ID,
		.ApplicationMode = OSDEFAULTAPPMODE,
		.NumOfActivationRequests = 1,
		.TaskFlags = &Task0Flags,
		.TaskStack = &Task0Stack,
		.EntryPoint = OSEK_TASK_Task0,
		.InternalResource = NULL_PTR,
		.EventsOwned = 0,
		.TaskDynamics = &Task0Dynamic
	},
	{
		.TaskStaticPriority = 2,
		.TaskID = Task1_ID,
		.ApplicationMode = OSDEFAULTAPPMODE,
		.NumOfActivationRequests = 1,
		.TaskFlags = &Task1Flags,
		.TaskStack = &Task1Stack,
		.EntryPoint = OSEK_TASK_Task1,
		.InternalResource = NULL_PTR,
		.EventsOwned = 0,
		.TaskDynamics = &Task1Dynamic
	},
	{
		.TaskStaticPriority = 0,
		.TaskID = IdleTaskId,
		.ApplicationMode = OSDEFAULTAPPMODE,
		.NumOfActivationRequests = 1,
		.TaskFlags = &IdleTaskFlags,
		.TaskStack = &IdleTaskStack,
		.EntryPoint = OS_CoretexIdle,
		.InternalResource = NULL_PTR,
		.EventsOwned = 0,
		.TaskDynamics = &IdleTaskDynamic
	}
};

TaskType AutoStartTasks [1] = {
	0
};

AlarmType AutoStartAlarms [1] = {
	0
};

Os_Kernel Kernel =
{
	.TaskQueueHead = NULL_PTR,
	.TaskRunning = NULL_PTR,
	.TaskPreempted = NULL_PTR,
	.CpuLoad = NULL_PTR,
	.OsState = OS_STATE_BOOT,
	.ForceScheduling = FALSE,
	.SchedulerNeeded = FALSE,
	.DispatcherNeeded = FALSE,
	.NewContext = FALSE
};

Os_AppMode ApplicationModes[MAX_NO_APPMODES] =
{
    {
        .AutoStartTaskSize = MAX_NO_TASKS_AUTOSTART,
        .AutoStartTasks = AutoStartTasks,
		.AutoStartAlarmsSize = 1,
		.AutoStartAlarms = AutoStartAlarms
	}
};

Os_Counter Counters [COUNTER_COUNT]=
{
	{
		/* Maximum possible allowed value of the system counter in ticks. */
		.OsCounterMaxAllowedValue = 0xEA60,
		/* The MINCYCLE attribute specifies the minimum allowed number of counter ticks for a cyclic alarm linked to the counter. */
		.OsCounterMinCycle = 0x01,
		/* The number of seconds in one OsTick. */
		.OsSecondsPerTick = 0x01,
		/* The type of the counter. */
		.OsCounterType = COUNTER_HARDWARE,
		/* The number of ticks of the counter that make up one OsTick. */
		.OsCounterTicksPerBase = 1,
		/* The index of head counter*/
		.OsCounterAlarmsHeadIndex  = 0
	}
};

Os_AlarmActivateTask Task1_Alarm0 =
{
	.OsAlarmActivateTaskRef = Task1_ID
};



Os_Alarm Alarms[ALARM_COUNT] = 
{
	{
		.OsAlarmAction =
		{
			.OsAlarmActivateTask = &Task1_Alarm0,
		},
		.OsAlarmCounterRef = &Counters[0],
		.OsAlarmActionType = ALARM_ACTIVATE_TASK,
		.OsAlarmAlarmTime = 5,
		.OsAlarmAutoStartType = ALARM_RELATIVE,
		.OsAlarmCycleTime = 5
	}
};

Os_Alarm* ActiveAlarmsHead[COUNTER_COUNT] =
{
	NULL_PTR
};