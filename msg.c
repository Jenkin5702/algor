#include<stdio.h>
#include<stdlib.h>

#define N 10
#define R 18
#define START 0
#define END 9
int routes[R][3]={
    {0,1,4},{0,2,2},{0,3,3},
    {1,4,9},{1,5,8},
    {2,4,6},{2,5,7},{2,6,8},
    {3,5,4},{3,6,7},
    {4,7,5},{4,8,6},
    {5,7,8},{5,8,6},
    {6,7,6},{6,8,5},
    {7,9,7},
    {8,9,3}
};

int distance[N-1];

void min_distance(){
    for(int i=N-2;i>=0;i--){
        int linked[N-1];
        int linked_n=0;
        int found=0;
        for(int j=0;j<R;j++) if(routes[j][0]==i) linked[linked_n++]=j;
        for(int j=0;j<linked_n;j++) if(routes[linked[j]][1]==END){
            distance[i]=routes[linked[j]][2];
            found=1;
        }
        if(found==0){
            int md=0xFFFFFF;
            for(int j=0;j<linked_n;j++){
                distance[i]=routes[linked[j]][2]+distance[routes[linked[j]][1]];
                if(distance[i]<md) md=distance[i];
                else distance[i]=md;
            }
        }
    }
}

int main(){
    min_distance();
    return 0;
}