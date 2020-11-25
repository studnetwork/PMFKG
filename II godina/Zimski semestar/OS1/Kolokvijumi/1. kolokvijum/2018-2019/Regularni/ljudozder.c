#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

typedef struct Message {
    long mtype;
    int pid;
} Message;

void signal_handler(int sig) {
    printf("Ljudozder (%d) se ukrcao na brod\n", getpid());\
    exit(0); // sign off
}

int main() {

    key_t uniqueId = ftok("/home/squirrelosopher/Desktop/OS/OS/2018-19R/postavka.pdf", 'a');
    if (uniqueId == -1) {
        perror("Unable to obtain unique id: ");
        exit(1);
    }

    int msgflg = IPC_CREAT | 0666;
    int msgQueueId = msgget(uniqueId, msgflg);
    if (msgQueueId == -1) {
        perror("Unable to obtain message queue id: ");
        exit(1);
    }

    Message message;
    message.mtype = 2; // type 2 for Cannibal

    signal(SIGINT, signal_handler); // Note that all child processes will be triggered if Ctrl + C is used to stop in terminal

    int sleepTime;
    while (1) {
        
        switch (fork())
        {
        case -1:
            perror("Unable to fork process: ");
            exit(1);
        case 0:

            message.pid = getpid();
            if ((msgsnd(msgQueueId, &message, sizeof(message) - sizeof(long), 0)) == -1) {
                perror("Unable to send message to a queue: ");
                exit(1);
            }

            srand(message.pid);
            sleepTime = (rand() % 20) + 1; // rand 1 - 20
            printf("Ljudozder (%d) se prijavio, spavanje narednih %d sekundi\n", message.pid, sleepTime);
            
            sleep(sleepTime);
            break;
        default:
            srand(getpid());
            sleepTime = (rand() % 20) + 1; // rand 1 - 20
            sleep(sleepTime);

            break;
        }
    }

    return 0;
}