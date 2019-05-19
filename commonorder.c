#include<stdio.h>
#include<stdlib.h>

int common_order(int m,int n,char* x,char* y){
    int L[m+1][n+1];
    int S[m+1][n+1];
    for(int i=0;i<=m;i++){
        L[i][0]=0;
        S[i][0]=0;
    }
    for(int i=0;i<=n;i++){
        L[0][i]=0;
        S[0][i]=0;
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(x[i]==y[j]){
                L[i+1][j+1]=L[i][j]+1;
                S[i+1][j+1]=1;
            }else if(L[i][j-1]>=L[i][j+1]){
                L[i+1][j+1]=L[i+1][j];
                S[i+1][j+1]=2;
            }else{
                L[i+1][j+1]=L[i][j+1];
                S[i+1][j+1]=3;
            }
        }
    }

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%d ",L[i+1][j+1]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%d ",S[i+1][j+1]);
        }
        printf("\n");
    }
    return 0;
}

int main(){
    char a[]="abcbdb";
    char b[]="acbbabdbb";
    common_order(6,9,a,b);
}