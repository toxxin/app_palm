#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

s_BOARD SlaveBoard = {"0", "250K"};

void InitNode(CO_Data *d, UNS32 id)
{
	setNodeId(&TestSlave_Data, NODE_SLAVE_ID);

	setState(&TestSlave_Data, initialisation);
}

void Exit(CO_Data *d, UNS32 id)
{

}


int main(int argc, char **argv)
{
	TimerInit();

	char *LibraryPath = "../../drivers/can_virtual/libcanfestival_can_virtual.so";

	if (LoadCanDriver(LibraryPath) == NULL)
	{
		printf("Unable to load library: %s\n", LibraryPath);
		exit(-1);
	}
	
	TestSlave_Data.heartbeatError = TestSlave_heartbeatError;
	TestSlave_Data.initialisation = TestSlave_initialisation;
	TestSlave_Data.preOperational = TestSlave_preOperational;
	TestSlave_Data.operational = TestSlave_operational;
	TestSlave_Data.stopped = TestSlave_stopped;
	TestSlave_Data.post_sync = TestSlave_post_sync;
	TestSlave_Data.post_TPDO = TestSlave_post_TPDO;
	TestSlave_Data.storeODSubIndex = TestSlave_storeODSubIndex;
	TestSlave_Data.post_emcy = TestSlave_post_emcy;

	if (!canOpen(&SlaveBoard ,&TestSlave_Data))
	{
		printf("Cannot open Slave Board (%s,%s)\n", SlaveBoard.busname, SlaveBoard.baudrate);
		exit(-1);
	}

	StartTimerLoop(&InitNode);

	pause();

	StopTimerLoop(&Exit);

	return 0;
}
