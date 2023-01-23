#include "msh.h"

// #define MAX_LINE_LENGTH 256

// void execute_command(char* command) {
//     char* cmd = strtok(command, " ");
//     char* arg = strtok(NULL, " ");

//     if (strcmp(cmd, "cd") == 0) {
//         if (arg == NULL) {
//             fprintf(stderr, "cd: missing operand\n");
//             return;
//         }
//         if (chdir(arg) != 0) {
//             perror("cd");
//         }
//     } else if (strcmp(cmd, "mkdir") == 0) {
//         if (arg == NULL) {
//             fprintf(stderr, "mkdir: missing operand\n");
//             return;
//         }
//         if (mkdir(arg, 0777) != 0) {
//             perror("mkdir");
//         }
//     } else if (strcmp(cmd, "cat") == 0) {
//         if (arg == NULL) {
//             fprintf(stderr, "cat: missing operand\n");
//             return;
//         }
//         pid_t pid = fork();
//         if (pid == 0) {
//             // child process
//             execlp(cmd, cmd, arg, NULL);
//             printf("Command not found\n");
//             exit(1);
//         } else if (pid > 0) {
//             // parent process
//             int status;
//             wait(&status);
//         } else {
//             // fork failed
//             perror("Fork failed");
//             exit(1);
//         }
//     } else if (strcmp(cmd, "echo") == 0) {
//         if (arg == NULL) {
//             printf("\n");
//             return;
//         }
//         printf("%s\n", arg);
//     } else {
//         pid_t pid = fork();
//         if (pid == 0) {
//             // child process
//             execlp(command, command, NULL);
//             printf("Command not found\n");
//             exit(1);
//         } else if (pid > 0) {
//             // parent process
//             int status;
//             wait(&status);
//         } else {
//             // fork failed
//             perror("Fork failed");
//             exit(1);
//         }
//     }
// }

// int main(int argc, char *argv[])
// {
//     char command[MAX_LINE_LENGTH];

//     while (1) {
//         printf("minishell> ");
//         fgets(command, MAX_LINE_LENGTH, stdin);

//         // remove the newline character from the input
//         command[strcspn(command, "\n")] = 0;

//         if (strcmp(command, "exit") == 0) {
//             break;
//         }

//         execute_command(command);
//     }

//     return 0;
// }