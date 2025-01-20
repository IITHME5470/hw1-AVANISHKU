#include<stdio.h>
#include<stdlib.h>
#include<math.h>


//Function to read a matrix from a file
void read_matrix(const char *filename, int n,double **matrix){
FILE *f=fopen(filename,"r");
if(f==NULL){
fprintf(stderr,"Error opening matrix file: %s\n",filename);
exit(1);
}
for(int i=0;i<n;i++){
for(int j=0;j<n;j++){
fscanf(f,"%lf",&matrix[i][j]);
}
}
fclose(f);
}


//Function to read a vector from a file
void read_vector(const char *filename, int n,double *vector){
FILE *f=fopen(filename,"r");
if(f==NULL){
fprintf(stderr,"Error opening vector file: %s\n",filename);
exit(1);
}
for(int i=0;i<n;i++){
fscanf(f,"%lf",&vector[i]);
}
fclose(f);
}


//Function to multiply matrix A by vector v
double *matrix_vector_multiply(double **matrix,double *vector,int n){
double *result1=malloc(n*sizeof(double));
for( int i=0;i<n;i++){
result1[i]=0.0;
for(int j=0;j<n;j++){
result1[i]+=matrix[i][j]*vector[j];
}
}
return result1;
}


//Function to check if a vector is an eigenvector of a matrix
int is_eigen_vector(int n,double **matrix, double *vector,double *eigenvalue){
double *result=matrix_vector_multiply(matrix,vector,n);
 
int valid_eigen=0;//Flag to check if a valid eigen value is found
for(int i=0;i<n;i++){
if(fabs(vector[i])>1e-10){//check if a vector element is not zero
double current_eigen=result[i]/vector[i];
if(!valid_eigen){
*eigenvalue=current_eigen;//set eigenvalue to first non zero element
valid_eigen=1;
} else if(fabs(current_eigen-*eigenvalue)>1e-10){
free(result);
return 0;//Eigen value mismatch
}
else if(fabs(result[i])>1e-10){
//if a vector[i] is zero but result[i] is non zero,it is  not a eigen vector
free(result);
return 0;
}
}
free(result);
return valid_eigen;
}
}


//Function to append eigenvalue to vector file
void append_eigenvalue(const char *filename,double eigenvalue){
FILE *f=fopen(filename,"a");
if(f==NULL){
fprintf(stderr,"Error opening vector file: %s\n", filename);
exit(1);
}
fprintf(f," %lf", eigenvalue);
fclose(f);
}


int main(){
FILE *input=fopen("input.in","r");
if(input==NULL){
fprintf(stderr,"Error opening input file!\n");
return 1;
}


int n;//Read matrix size n
fscanf(input,"%d",&n);
fclose(input);


double **matrix=(double **)malloc(n*sizeof(double*));//Allocates memory for matrix and vector
for(int i=0;i<n;i++){
matrix[i]=(double *)malloc(n*sizeof(double));
}


char matrix_filename[50];
sprintf(matrix_filename,"mat_%06d.in",n);
read_matrix(matrix_filename,n,matrix);


for(int vecnum=1;vecnum<=4;vecnum++){
char vector_filename[50];
sprintf(vector_filename,"vec_%06d_%06d.in",n,vecnum);


double *vector =(double *)malloc(n*sizeof(double));
read_vector(vector_filename,n,vector);

double eigenvalue;
if(is_eigen_vector(n,matrix,vector,&eigenvalue)){
printf("%s: is a eigenector: %lf\n",vector_filename,eigenvalue);
append_eigenvalue(vector_filename, eigenvalue);
} else {
printf("%s: Not a eigen vector\n",vector_filename);
}
free(vector);//free the memory for vector
}


for (int i=0;i<n;i++){
free(matrix[i]);//free the memory for matrix
}
free(matrix);
return 0;
}

