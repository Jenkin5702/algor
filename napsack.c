#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#define N 5
#define MAXW 10

int max(int a,int b){
    return a>b?a:b;
}

int main(){
    int value[N]={6,3,5,4,6};
    int weight[N]={2,2,6,5,4};
    int v[N+1][MAXW+1];
    for(int i=0;i<=N;i++) v[i][0]=0;
    for(int j=0;j<=MAXW;j++) v[0][j]=0;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=MAXW;j++){
            v[i][j]=0;
            if (j<weight[i-1]) v[i][j]=v[i-1][j];
            else v[i][j]=max(v[i-1][j],v[i-1][j-weight[i-1]]+value[i-1]);
            printf("%d\t", v[i][j]);
        }
        printf("\n");
    }
    return 0;
}