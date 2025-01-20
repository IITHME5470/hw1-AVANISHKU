#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void Print_to_file(int n,double **A,int format_flag){
char filename[50];
sprintf(filename,"array_%06d_%s",n,format_flag ==0 ?"asc.out" : "bin.out");

FILE *f=fopen(filename,format_flag==0 ? "w" : "wb");
if (f==NULL){
fprintf(stderr,"Error opening file!\n");
return;
}

if(format_flag==0){
for(int i=0;i<n;i++){
for(int j=0;j<n;j++){
fprintf(f,"%.15f ",A[i][j]);
}
fprintf(f,"\n");
}
}
else {
for(int i=0;i<n;i++){
fwrite(A[i],sizeof(double),n,f);
}
}
fclose(f);
}
int main(){
FILE *input=fopen("input.in","r");
if(input==NULL){
fprintf(stderr,"Error opening input file!\n");
return 1;
}
int n;
fscanf(input,"%d",&n);
fclose(input);

double **A=(double **)malloc(n*sizeof(double *));
for(int i=0;i<n;i++){
A[i]=(double *)malloc(n*sizeof(double));
for(int j=0;j<n;j++){
A[i][j]=i+j;
}
}

int format_flag= 1; //change this to 1 for binary format
Print_to_file(n,A,format_flag);
for(int i=0;i<n;i++){
free(A[i]);
}
free(A);
return 0;
}

