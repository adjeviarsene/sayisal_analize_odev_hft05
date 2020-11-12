#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define n 3

int fowardElim(double matrix[n][n+1]);
void backsub(double matrix[n][n+1]);
void gaussianElim(double matrix[n][n+1]);
void swap_row(double matrix[n][n+1],int i,int j);
void print(double matrix[n][n+1]);

int main(int argc,char **argv){
     double mat[n][n+1];
     printf("Enter the matrix matrix[n][n+1]\n");
     for(int i=0;i<n;i++){
          for(int j=0;j<=n;j++){
               printf("[%d][%d]:",i,j);
               scanf("%lf",&mat[i][j]);
          }
     }

     print(mat);
    gaussianElim(mat);
     return(0);
}

void gaussianElim(double matrix[n][n+1]){
     int singular_flag=fowardElim(matrix);
     if(singular_flag !=-1){
          printf("Singular matrix .\n");
          if(matrix[singular_flag][n]){
               printf("Inconsistent Matrix\n");
          }
          else{
               printf("May have infinitely may solution\n");
          }
          return;
     }
     backsub(matrix);
}

void swap_row(double matrix[n][n+1],int i ,int j){
#ifdef DEBUG
     printf("Swapped row %d and %d\n",i,j);
#endif
     for(int k=0;k<=n;k++){
          double temp=matrix[i][k];
          matrix[i][k]=matrix[j][k];
          matrix[j][k]=temp;
     }
}
void print(double matrix[n][n+1]){
     for(int i=0;i<n;i++){
          for(int j=0;j<=n;j++){
               printf("%.2lf ",matrix[i][j]);
          }
          printf("\n");
     }
}
int fowardElim(double matrix[n][n+1]){
     for(int k=0;k<n;k++){
          //Initialize maximum value and index for pivot
          int i_max=k;
          int v_max=matrix[i_max][k];
          /*find the grater  amplitude for the pivot if any*/
          for(int i=k+1;i<n;i++){
               if(abs(matrix[i][k])>v_max){
                    v_max=matrix[i][k];
                    i_max=i;
               }
          }

          if(!matrix[k][i_max]){
               return k;//Matrix is singular
          }
          if(i_max != k){
               swap_row(matrix,k,i_max);
          }
          for(int i=k+1;i<n;i++){
               double f=matrix[i][k]/matrix[k][k];
               for(int j=k+1;j<=n;j++){
                    matrix[i][j] -=matrix[k][j]*f;
                    matrix[i][k]=0;
               }
          }
     }
     return -1;
}
void backsub(double matrix[n][n+1]){
     double x[n]; // temporaire array to storte the solution
     for(int i=n-1;i>=0;i--){
          x[i]=matrix[i][n];
          for(int j=i+1;j<n;j++){
               x[i] -=matrix[i][j]*x[j];
          }

          x[i]=x[i]/matrix[i][i];
     }
     printf("Solution of the system:\n");
     for(int i=0;i<n;i++){
          printf("%lf\n",x[i]);
     }
}
