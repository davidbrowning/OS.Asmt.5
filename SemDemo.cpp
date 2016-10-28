#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string>


const int SEMAPHORE_KEY		= 1234;
const short ADD_KEY			= 1;
const short WAIT_KEY		= -1;


int main(int argc,char *argv[])
{
	int semID;
	if (argc == 1)
	{
		semID = semget(SEMAPHORE_KEY, 1, 0666|IPC_CREAT);
		semctl(semID, 0, SETVAL, 1);
	}
	else
	{
		semID = semget(SEMAPHORE_KEY, 1, 0666);
	}

	std::cout << "Press enter to take the key";
	std::string input;
	std::getline(std::cin, input, '\n');

	std::cout << "Waiting on the key...";
	std::cout.flush();

	//
	// Wait and take the key
	sembuf buf;

	buf.sem_num = 0;
	buf.sem_flg = 0;
	buf.sem_op = WAIT_KEY;
	semop(semID, &buf, 1);

	std::cout << "We've got the key" << std::endl;
	std::cout << "Press enter to return the key" << std::endl;
	std::getline(std::cin, input, '\n');

	buf.sem_num = 0;
	buf.sem_flg = 0;
	buf.sem_op = ADD_KEY;
	semop(semID, &buf, 1);

	std::cout << "Key has been returned" << std::endl;

	return 0;
}
