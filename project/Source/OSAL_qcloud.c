#include "OSAL.h"
#include "OSAL_Tasks.h"


/* HCI */
#include "hci_tl.h"

/* LL */
#include "ll.h"


/* L2CAP */
#include "l2cap.h"

/* gap */
#include "gap.h"
#include "gapgattserver.h"
#include "gapbondmgr.h"

/* GATT */
#include "gatt.h"

#include "gattservapp.h"

/* Profiles */
#include "peripheral.h"

/* Application */
#include "at_task.h"
#include "qcloud.h"
#include "mytimer.h"

#include "peripheral_hal.h"


// The order in this table must be identical to the task initialization calls below in osalInitTask.
const pTaskEventHandlerFn tasksArr[] =
{
    LL_ProcessEvent,
    HCI_ProcessEvent,
    L2CAP_ProcessEvent,
    GAP_ProcessEvent,
    GATT_ProcessEvent,
    SM_ProcessEvent,
    GAPRole_ProcessEvent,
    GATTServApp_ProcessEvent,
    /* app */
    ATTask_ProcessEvent,
    Qcloud_ProcessEvent,
    /*  Peripheral Hal */
    Peripheral_ProcessEvent,
    /*  All processEvent before it */
    Timer_ProcessEvent,
};

const uint8 tasksCnt = sizeof( tasksArr ) / sizeof( tasksArr[0] );
uint16 *tasksEvents;


void osalInitTasks( void )
{
    uint8 taskID = 0;

    tasksEvents = (uint16 *)osal_mem_alloc( sizeof( uint16 ) * tasksCnt);
    osal_memset( tasksEvents, 0, (sizeof( uint16 ) * tasksCnt));

    /* LL Task */
    LL_Init( taskID++ );

    /* HCI Task */
    HCI_Init( taskID++ );

    /* L2CAP Task */
    L2CAP_Init( taskID++ );

    /* GAP Task */
    GAP_Init( taskID++ );

    /* GATT Task */
    GATT_Init( taskID++ );

    /* SM Task */
    SM_Init( taskID++ );

    /* Profiles */
    GAPRole_Init( taskID++ );

    GATTServApp_Init( taskID++ );

    /* Application */
    ATTask_Init( taskID++ );

    Qcloud_Init( taskID++ );

    Peripheral_Task(taskID++ );

    Timer_Init( taskID );

}
