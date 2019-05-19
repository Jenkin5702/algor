#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void swap(double* a,double* b){
    double t=*a;*a=*b;*b=t;
}
int partition(double* array,int start,int end){
    int i=start,j=end;
    for(int k=start;k<=end;k++) printf("%f ",array[k]);
    printf("\n");
    while(i<j){
        while(i<j&&array[i]<=array[j]) j--;
        if(i<j) swap(&array[i],&array[j]);
        while(i<j&&array[i]<=array[j]) i++;
        if(i<j) swap(&array[i],&array[j]);
    }
    for(int k=start;k<=end;k++) printf("%f ",array[k]);
    printf("\n");
    return i;
}
void quick_sort(double* array,int start,int end){
    if(start<end){
        int piv=partition(array,start,end);
        quick_sort(array,start,piv-1);
        quick_sort(array,piv+1,end);
    }
}
int main(){
	int n=10;
	double a[n];
	for(int i=0;i<n;i++){
		a[i]=rand()%100;
		printf("%f ",a[i]);
	}
	printf("\n");
	quick_sort(a,0,n-1);
	for(int i=0;i<n;i++){
		printf("%f ",a[i]);
	}
	printf("\n");
	return 0;
}