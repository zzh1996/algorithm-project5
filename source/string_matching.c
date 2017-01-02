#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ASIZE 62

char T[131073],P[65];

int pi[65];

void KMP_pre(int m){
	int k,q;
	pi[1]=0;
	k=0;
	for(q=1;q<m;q++){
		while(k>0&&P[k]!=P[q])
			k=pi[k];
		if(P[k]==P[q])
			k++;
		pi[q+1]=k;
	}
}

int KMP(int n,int m){
	int q=0,i;
	for(i=0;i<n;i++){
		while(q>0&&P[q]!=T[i])
			q=pi[q];
		if(P[q]==T[i])
			q++;
		if(q==m)
			return i+1-m;
	}
	return -1;
}

int Qs_Bc[ASIZE];

void QS_pre(int m){
	int i;
	for(i=0;i<ASIZE;i++)
		Qs_Bc[i]=m+1;
	for(i=0;i<m;i++)
		Qs_Bc[P[i]]=m-i;
}

int QS(int n,int m){
	int i=0;
	while(i<=n-m){
		if(memcmp(P,T+i,m)==0)
			return i;
		i+=Qs_Bc[T[i+m]];
	}
	return -1;
}

//#define Q 34636831
#define Q 34636831

int p,t,h;

void RK_pre(int m){
	int i;
	p=0;
	t=0;
	h=1;
	for(i=0;i<m;i++){
		p=(ASIZE*p+P[i])%Q;
		t=(ASIZE*t+T[i])%Q;
		if(i>0)h=(ASIZE*h)%Q;
	}
}

int RK(int n,int m){
	int s;
	for(s=0;s<=n-m;s++){
		if(p==t)
			if(memcmp(P,T+s,m)==0)
				return s;
		if(s<n-m)
			t=(ASIZE*(((ASIZE-1)*Q+t-T[s]*h)%Q)+T[s+m])%Q;
	}
	return -1;
}

char convert(char c){
	if(c<'A')
		return c-'0';
	else if(c<'a')
		return c-'A'+10;
	else
		return c-'a'+36;
}

int main(){
	int i,j,n,m;
	FILE *in=fopen("../input/input.txt","r");
	FILE *out;
	char filename[100];
	double pre_time,run_time;
    struct timespec start,stop;
    int result;

	for(i=1;i<=5;i++){
		fscanf(in,"%d,%d,%[^,],%[^;];",&n,&m,T,P);

		for(j=0;j<n;j++)T[j]=convert(T[j]);
		for(j=0;j<m;j++)P[j]=convert(P[j]);

		sprintf(filename,"../output/output_%d.txt",i);
		out=fopen(filename,"w");

		clock_gettime(CLOCK_MONOTONIC,&start); //开始计时
        KMP_pre(m);
        clock_gettime(CLOCK_MONOTONIC,&stop); //结束计时
        pre_time=(stop.tv_sec-start.tv_sec)+(double)(stop.tv_nsec-start.tv_nsec)/1000000000L;

		clock_gettime(CLOCK_MONOTONIC,&start); //开始计时
        result=KMP(n,m);
        clock_gettime(CLOCK_MONOTONIC,&stop); //结束计时
        run_time=(stop.tv_sec-start.tv_sec)+(double)(stop.tv_nsec-start.tv_nsec)/1000000000L;

		fprintf(out,"KMP:%d,%d,%d,%.9fs,%.9fs\n",n,m,result,pre_time,run_time);

		clock_gettime(CLOCK_MONOTONIC,&start); //开始计时
        QS_pre(m);
        clock_gettime(CLOCK_MONOTONIC,&stop); //结束计时
        pre_time=(stop.tv_sec-start.tv_sec)+(double)(stop.tv_nsec-start.tv_nsec)/1000000000L;

		clock_gettime(CLOCK_MONOTONIC,&start); //开始计时
        result=QS(n,m);
        clock_gettime(CLOCK_MONOTONIC,&stop); //结束计时
        run_time=(stop.tv_sec-start.tv_sec)+(double)(stop.tv_nsec-start.tv_nsec)/1000000000L;

		fprintf(out,"QS:%d,%d,%d,%.9fs,%.9fs\n",n,m,result,pre_time,run_time);

		clock_gettime(CLOCK_MONOTONIC,&start); //开始计时
        RK_pre(m);
        clock_gettime(CLOCK_MONOTONIC,&stop); //结束计时
        pre_time=(stop.tv_sec-start.tv_sec)+(double)(stop.tv_nsec-start.tv_nsec)/1000000000L;

		clock_gettime(CLOCK_MONOTONIC,&start); //开始计时
        result=RK(n,m);
        clock_gettime(CLOCK_MONOTONIC,&stop); //结束计时
        run_time=(stop.tv_sec-start.tv_sec)+(double)(stop.tv_nsec-start.tv_nsec)/1000000000L;

		fprintf(out,"RK:%d,%d,%d,%.9fs,%.9fs\n",n,m,result,pre_time,run_time);
		
		fclose(out);
	}
	fclose(in);
	return 0;
}