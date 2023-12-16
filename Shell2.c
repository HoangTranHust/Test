#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h>
#include <dirent.h>
#define MAXN 100
#define MAXARG 2 

// Clear terminal
void clear() {
    printf("\033[H\033[J");
}

void initShell() 
{ 
	clear(); 
	printf("\n\n******************************************"); 
	printf("\n\n****WELCOME TO MY LINUX TINY SHELL****"); 
    printf("\n\n****Tran Huy Hoang 20210386****"); 
	printf("\n\n******************************************"); 
	sleep(1.5);
	clear(); 
} 

int getInput(char* str) 
{ 
	char* buf; 

	buf = readline(":TINY_SHELL>> "); 
	if (strlen(buf) != 0) { 
		add_history(buf); 
		strcpy(str, buf); 
		return 0; 
	} else return 1; 
}

//Test chuc nang HELP
void help(){
    printf("This is HELP COMMAND\n");
}

// In ra duong dan hien tai
void printDir() 
{ 
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd)); 
	printf("\n%s", cwd); 
}

//Chuc nang ls
void listFiles() {
    struct dirent *entry;
    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\t", entry->d_name);
        }
    }
    printf("\n");
    closedir(dir);
}

//Chuc nang cd
void changeDir(char *path){
    if (chdir(path) != 0) {
        perror("Error changing directory");
    }
    else{
        printf("Current directory has been changed!\n");
    } 
}

// Test foreground mode
// void foregroundMode(char *s) {
//     pid_t child_pid, wpid;
//     int status;

//     // Fork a child process
//     child_pid = fork();

//     if (child_pid == -1) {
//         perror("Fork failed");
//         exit(EXIT_FAILURE);
//     }

//     if (child_pid == 0) {
//         // Child process
//         char *args[] = {s, NULL};
//         if (execvp(s, args) == -1) {
//             perror("execvp failed");
//             exit(EXIT_FAILURE);
//         }
//     } else {
//         // Parent process
//         do {
//             wpid = waitpid(child_pid, &status, WUNTRACED);
//         } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//     }
// }


// Xu ly command
void processCmd(char * cmd){
    char *token;
    char arr[100][100]; 

    // Dung strtok de tach chuoi
    token = strtok(cmd, " ");

    // Lặp qua tất cả các token và sao chép vào mảng arr
    int k = 0; // Bắt đầu từ arr[0], k la so argument
    while (token != NULL) {
        strcpy(arr[k], token);
        k++;
        token = strtok(NULL, " ");
    }

    // Neu k > MAXARG thi thong bao loi
    if(k > MAXARG){
        printf("Bad command. Please try again");
    }
    else{
        // Neu chi co 1 arg
        if(k == 1){
            if(strcmp(arr[0], "help") == 0){
                help();
            }
            if(strcmp(arr[0], "ls") == 0){
                listFiles();
            }
        }
        // Neu co 2 arg
        else{
            if((strcmp(arr[0], "cd") == 0)){
                changeDir(arr[1]);
            }
            // Foreground Mode
            // if((strcmp(arr[1], "fg") == 0)){
            //     if((strcmp(arr[0], "calc") == 0)){
            //         foregroundMode("gnome-calculator");
            //     }
            // }
        }
    }
}

int main(){
    initShell();
    while(1){
        printDir();
        char str[100];
        getInput(str);
        processCmd(str);
    }
    return 1;
}