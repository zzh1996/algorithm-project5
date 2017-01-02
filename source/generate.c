#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char randchar(){
	int n=rand()%62;
	if(n<26)
		return 'A'+n;
	else if(n<52)
		return 'a'+(n-26);
	else
		return '0'+(n-52);
}

int main(){
	int i,j,n,m;
	FILE *fp=fopen("../input/input.txt","w");
	srand(time(0));
	for(i=0,n=32,m=4;i<5;i++,n*=8,m*=2){
		fprintf(fp,"%d,%d,",n,m);
		for(j=0;j<n;j++)
			fprintf(fp,"%c",randchar());
		fprintf(fp,",");
		for(j=0;j<m;j++)
			fprintf(fp,"%c",randchar());
		fprintf(fp,";\n");
	}
	fclose(fp);
	return 0;
}