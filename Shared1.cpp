#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	int sharedID = shmget(1234, 100, 0666 | IPC_CREAT);
	char* memory = static_cast<char *>(shmat(sharedID, 0, 0));
	strcpy(memory,"Hi Mom!");

return 0;
}
