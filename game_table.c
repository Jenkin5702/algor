#include<stdio.h>
#include<stdlib.h>

#define N 16
int a[N][N];

void game_table(){
    int n=2;
    a[0][0]=1;
    a[0][1]=2;
    a[1][0]=2;
    a[1][1]=1;
    while(n<N){
        int temp=n;
        n=n*2;
        for(int i=temp;i<n;i++) 
        for(int j=0;j<temp;j++)
        a[i][j]=a[i-temp][j]+temp;
        for(int i=0;i<temp;i++)
         for(int j=temp;j<n;j++)
          a[i][j]=a[i][j-temp]+temp;
        for(int i=temp;i<n;i++)
         for(int j=temp;j<n;j++)
          a[i][j]=a[i-temp][j-temp];
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                printf("%2d ",a[i][j]);
            }
            printf("\n");
        }
    }
}

int main(){
    game_table();
    return 0;
}