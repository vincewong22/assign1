/*repeatedly get input*/
#include <stdio.h>
#include <string.h>
#define LINESIZE 1024
#define STUDENT_NO_SIZE 9
#define RECORD_SIZE 18

void print_intro(void);
int main_menu(void);
void display_records(FILE*);
void append_record(FILE*);
FILE read_file(char[]);
void modify_record(FILE*,int);
int get_student_no(char[]);
void change_num(int *number);

int main (int argc, char*argv[]){
	
	
char student_id[STUDENT_NO_SIZE];
FILE fp = read_file(argv[1]);
/*TODO:  alter main has duplicate code*/

/* get_student_no(student_id);
printf("yuyu student id is: %s",student_id); */

int num =0;
change_num(&num);
printf("%d\n",num);

printf("argument 1 is: %s\n",argv[1]);

char filename[LINESIZE];
	
int choice =0;

print_intro();
do{
choice = mainMenu();
printf("choice was: %d\n",choice);
switch(choice){
case -2:
	break;
case 0:
	display_records(&fp);
	break;
case -1:
	append_record(&fp);
	break;
default: 
	modify_record(&fp,choice);
	break;
}
}
while(choice !=-2);
printf("program has quit");
return 0;

}/*end of main*/

void print_intro(){
printf("\nMain Menu\n");
printf("menu choices\n");
}

int mainMenu(){
	
int command = 0;
char line[LINESIZE];
while(1){
printf("Enter a command -2 (quit) -1(append) 0 (display): ");

if(!fgets(line, LINESIZE, stdin)){
	clearerr(stdin);
	break;
}
if(sscanf(line, "%d", &command)==1)
	printf("command received: %d\n",command);
	break;
}	

return command;
}

void display_records(FILE *fp){
	printf("displaying records\n");
	
	char c;
	char student_id[STUDENT_NO_SIZE];
	int score;
	int counter=0;

	rewind(fp);
	
	while(fscanf(fp, "%s %d",student_id,&score)==2){
		fprintf(stderr,"%d %s %d\n",++counter,student_id,score);
	}
}

int get_student_no(char student_no[]){
	/*@return: -1 abort | 1 good student no | 0 bad student no, try again*/
	char line[LINESIZE];
	int exit;
	printf("Enter student number 334: ");
	
	if(!fgets(line, LINESIZE, stdin)){
	clearerr(stdin);
	return-1;
	}
	/*check for -1*/
	sscanf(line,"%d",&exit);
	if(exit ==-1){
		printf("-1 detected\n");
		return -1;
	}
	
	if(sscanf(line,"%s",student_no)==1){
		if(strlen(student_no) !=STUDENT_NO_SIZE){
			printf("bad length\n");
			return 0;
		}
		if(student_no[0] != 'a'){
		printf("first character is bad\n");
		return 0;
		}
		size_t i;
		
		for(i=1; i < STUDENT_NO_SIZE; i++)
		if(!isdigit(student_no[i])){
			printf("rest of char not digit\n");
			return 0;
		}
	}
return 1;
}	

void change_num(int *number){
	*number = 8;
}

int get_student_score(int *score){
	/*0 bad score try again*/
	char line[LINESIZE];
	int local_score;
	
	printf("Enter score: ");
	if(!fgets(line, LINESIZE, stdin)){
	clearerr(stdin);
	return 0;
	}
	if(sscanf(line,"%d",&local_score)==1){
		*score = local_score;
	if(local_score ==-1){
		return -1;
	}
	if(local_score <0 || local_score >100)
		return 0;
	else
		return 1;
	}
	else
	return 0;
}


void append_record(FILE *fp){
	char line[LINESIZE];
	char student_id[STUDENT_NO_SIZE];
	int score =0;
	char score_buffer[STUDENT_NO_SIZE];
	int abort;
	
	fseek(fp, 0, SEEK_END);
	
	while(1){
	abort = get_student_no(student_id);
	printf("abort value: %d\n",abort);
	if(abort ==-1 ||abort ==1)
		break;
	}
	while(1 && abort!=-1){
	abort = get_student_score(&score);
	if(abort ==-1 ||abort ==1)
		break;
	}
	
	if(abort !=-1){
	printf("appending record\n");
	size_t i;
	for(i=0; i < STUDENT_NO_SIZE; i++){
	fputc(student_id[i],fp);
	}
	fputc(' ',fp);
	sprintf(score_buffer, "%9d", score);
	for(i=0; i < STUDENT_NO_SIZE;i++){
	fputc(score_buffer[i],fp);
	}
	fputc('\n', fp);
	fflush(fp);
	}
}

void modify_record(FILE *fp, int choice){
	char line[LINESIZE];
	char student_id[STUDENT_NO_SIZE];
	int score =0;
	char score_buffer[STUDENT_NO_SIZE];
	int abort;
	
	char student_no[STUDENT_NO_SIZE];
	printf("modifying record #: %d\n",choice);
	
	/*choice and record storage is off by 1*/
	--choice;
	
	rewind(fp);
	int seek;
	/*each record occupies 18 characters*/
	seek = choice *20;
	fseek(fp,seek,SEEK_SET);
	
	while(1){
	abort = get_student_no(student_id);
	printf("abort value: %d\n",abort);
	if(abort ==-1 ||abort ==1)
		break;
	}
	while(1 && abort!=-1){
	abort = get_student_score(&score);
	if(abort ==-1 ||abort ==1)
		break;
	}
	
	if(abort !=-1){
	printf("appending record\n");
	size_t i;
	for(i=0; i < STUDENT_NO_SIZE; i++){
	fputc(student_id[i],fp);
	}
	fputc(' ',fp);
	sprintf(score_buffer, "%9d", score);
	for(i=0; i < STUDENT_NO_SIZE;i++){
	fputc(score_buffer[i],fp);
	}
	fputc('\n', fp);
	fflush(fp);
	}
	}
	


FILE read_file(char filename[]){
	FILE *fp;
	
	printf("reading file: %s\n",filename);
	
	/* if((fp = fopen(filename, "w+b")) ==0){ */
if((fp = fopen(filename, "r+b")) ==0){
	perror("fopen");
	}
	
return *fp;
}

