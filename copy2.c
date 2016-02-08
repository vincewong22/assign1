second version of copy

#include <stdio.h>

int main(int argc, char *argv[]){

	FILE *ifp, *ofp;
	int c;
	
	//we need to validate the command line argument
	if(argc !=3){
		fprintf(stderr, "usage: %s {source-file} {destination-file}\n", argv[0]);
		return 1;
		}
		
	//we open the two files
	
	if((ifp = fopen(argv[1], "rb")) ==0){
	perror("fopen");
	return 2;
	}
	
	if((ofp = fopen(argv[2], "wb")) == 0){
	perror("fopen");
	return 3;
	}
	//main part of program
	//fgetc variant of getChar to get from file
	while((c = fgetc(ifp)) !=EOF)
		fputc(c,ofp);
	
	if(fclose(ifp) !=0){
	perror("fclose");
	return 4;
	}
	if(fclose(ofp != 0){
	perror("fclose");
	return 5;
	}
	
	return 0;
}

//a.out Test.class abc
//cmp Test.class abc  //this compares files, if they are the same there won't be a message, if they are different there will bea message
// echo $?  open file for reading, what return
//no such file, error from perror
