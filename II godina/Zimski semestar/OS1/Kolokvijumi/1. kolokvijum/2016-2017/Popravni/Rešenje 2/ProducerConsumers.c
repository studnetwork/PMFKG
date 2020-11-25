#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct Message {
	long mtype;
	char message[20];
} Message;

void sendMessages(int msgQueueId) {
	Message messageTemplate;
	messageTemplate.mtype = 1;
	int currentMessage = 1;

	pid_t producerPid = getpid();
	char ppid[10];
	sprintf(ppid, "%d ", producerPid);

	char currentProducerNum[10];

	while (1) {
		
		strcpy(messageTemplate.message, "Proizvodjac ");
		strcat(messageTemplate.message, ppid);

		sprintf(currentProducerNum, "%d", currentMessage++);
		strcat(messageTemplate.message, currentProducerNum);

		// printf("Sending message '%s'\n", messageTemplate.message);
		if ((msgsnd(msgQueueId, &messageTemplate, sizeof(messageTemplate) - sizeof(long), 0)) == -1) {
			perror("Unable to send message: ");
			exit(1);
		}

		sleep(5); // not neccessary
	}
}

void receiveMessages(int msgQueueId, int consumerId) { // consumerId not neccessary
	Message receivedMessage;

	while (1) {
		if ((msgrcv(msgQueueId, &receivedMessage, sizeof(receivedMessage) - sizeof(long), 1, 0)) == -1) {
			perror("Unable to receive message: ");
			exit(1);
		}

		printf("[%d] Potrosac: %s\n", consumerId, receivedMessage.message);
	}
}

int main() {
	
	key_t uniqueId = ftok("/home/squirrelosopher/Desktop/OS/OS/2016-17P/ProducerConsumers.c", 'a');
	if (uniqueId == -1) {
		perror("Unable to create unique id: ");
		exit(1);
	}
	
	int msgflg = IPC_CREAT | 0666;
	int msgQueueId = msgget(uniqueId, msgflg);
	if (msgQueueId == -1) {
		perror("Unable to create message queue: ");
		exit(1);
	}
	
	
	pid_t consumerOne = fork();
	if (consumerOne == -1) {
		perror("Unable to fork first Consumer: ");
		exit(1);
	} else if (consumerOne == 0) {
		// consumer one

		pid_t consumerTwo = fork();
		switch (consumerTwo) {
		case -1:
			perror("Unable to fork second Consumer: ");
			exit(1);
		case 0:
		default:
			receiveMessages(msgQueueId, getpid());
		}
	} else {
		sendMessages(msgQueueId);
	}
	
	return 0;
}
