#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>


int split_line(char *args[], char line[]) {
	int i=0;
	args[i] = strtok(line," ");
	while(1) {
		char *temp = strtok(NULL," ");
		if (temp == NULL){
			break;
		}
		i++;
		args[i]=temp;
	}
	return i;
}


void read_line(char line[]) {
	int i=0;
	fgets(line, 200, stdin);
	while(1) {
		if(line[i] == '\n'){
			line[i] = '\0';
			break;
		}
		i++;
	}
	
}
void writeChildId(int id){
	FILE* fp ;
 	fp = fopen("ID.log" , "a");
 	fprintf(fp, " Child is terminate . Child id is %d \n" ,id);
	fclose(fp);
}

void handler() {

	//printf("handler\n");

	int id =getpid();
	writeChildId(id);
}

int main() {

	while (1){
	
	char *args[20];
	char line[200];
	printf("AKL>");
	read_line(line);


	int len = split_line(args,line);

	char *comm = args[0];
	if(comm == NULL) continue;
	if( strcmp(comm,"exit")==0)
		exit(0);
	char *attrs[20];

	
	for(int i=1; i<=len; i++){
		attrs[i] = args[i];
	}
	attrs[len+1]=NULL;
	signal(SIGCHLD,handler);
	pid_t child_pid=fork();
	if (child_pid==0) {
		int w = execvp(comm, attrs);
		if (w==-1){
			printf("Error:%s not found!\n",comm);
			exit(0);
				}
		}
	else 
		if(strcmp(args[len], "&") != 0){
		waitpid(child_pid,0, 0);
		//printf("Parent ID is %d \n",getpid());
            }
}
	return 0;
}
