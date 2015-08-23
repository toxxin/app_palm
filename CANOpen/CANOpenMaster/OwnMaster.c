#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

s_BOARD MasterBoard = {"0", "250K"};

void InitNode(CO_Data *d, UNS32 id)
{
	setNodeId(&TestMaster_Data, NODE_MASTER_ID);

	setState(&TestMaster_Data, initialisation);
}

void Exit(CO_Data *d, UNS32 id)
{
	masterSendNMTstateChange(&TestMaster_Data, 0x02, NMT_Reset_Node);

	setState(&TestMaster_Data, Stopped);
}


int main(int argc, char **argv)
{
	char *LibraryPath = "../../drivers/can_virtual/libcanfestival_can_virtual.so";

	if (LoadCanDriver(LibraryPath) == NULL)
	{
		printf("Unable to load library: %s\n", LibraryPath);
		exit(-1);
	}
	
	TestMaster_Data.heartbeatError = TestMaster_heartbeatError;
	TestMaster_Data.initialisation = TestMaster_initialisation;
	TestMaster_Data.preOperational = TestMaster_preOperational;
	TestMaster_Data.operational = TestMaster_operational;
	TestMaster_Data.stopped = TestMaster_stopped;
	TestMaster_Data.post_sync = TestMaster_post_sync;
	TestMaster_Data.post_TPDO = TestMaster_post_TPDO;
	TestMaster_Data.storeODSubIndex = TestMaster_storeODSubIndex;
	TestMaster_Data.post_emcy = TestMaster_post_emcy;

	if (!canOpen(&MasterBoard ,&TestMaster_Data))
	{
		printf("Cannot open Master Board (%s,%s)\n", MasterBoard.busname, MasterBoard.baudrate);
		exit(-1);
	}

	StartTimerLoop(&InitNode);

	pause();

	StopTimerLoop(&Exit);

	return 0;
}