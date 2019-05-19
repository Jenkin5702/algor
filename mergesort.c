#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void merge_sort(double* array,double* sorted_array,int start,int end){
	srand((int)time(0));
	if(start==end) sorted_array[start]=array[start]; else{
		int middle=(start+end)/2;
		for(int a=start;a<=end;a++) printf("%f ",array[a]);
		printf("\n\t-> ");
		for(int a=start;a<=middle;a++) printf("%f ",array[a]);
		printf("\n\t-> ");
		for(int a=middle+1;a<=end;a++) printf("%f ",array[a]);
		printf("\n");
		merge_sort(array,sorted_array,start,middle);
		merge_sort(array,sorted_array,middle+1,end);
		double temp[end-start+1];
		int i=start,j=middle+1,k=0;
		while(i<=middle&&j<=end){
			if(sorted_array[i]<=sorted_array[j]) temp[k++]=sorted_array[i++];
			else temp[k++]=sorted_array[j++];
		}
		while(i<=middle) temp[k++]=sorted_array[i++];
		while(j<=end) temp[k++]=sorted_array[j++];
		k=0;
		for(i=start;i<=end;i++) sorted_array[i]=temp[k++];
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
	double b[n];
	merge_sort(a,b,0,n-1);
	for(int i=0;i<n;i++){
		printf("%f ",b[i]);
	}
	printf("\n");
	return 0;
}
