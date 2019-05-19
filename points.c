#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define INF 0xFFFFFF
#define N 10000

typedef struct{
    double x;
    double y;
}point;

point pointsX[N];
point pointsY[N];

double distance(point p1,point p2){
    return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

double violent(int l,int r, point* p1,point* p2){
    double md=INF;
    double d;
    for(int i=l;i<r;i++){
        for(int j=l;j<r;j++){
            if(i!=j){
                d=distance(pointsX[i],pointsX[j]);
                if(d<md) {
                    md=d;
                    *p1=pointsX[i];
                    *p2=pointsX[j];
                }
            } 
        }
    }
    return md;
}

void merge(int left,int right){
    int mid=(left+right)/2;
    int l=left,r=mid+1;
    int index=l;
    while(l<=mid&&r<=right){
        if(pointsX[r].y>pointsX[l].y) pointsY[index++]=pointsX[l++];
        else pointsY[index++]=pointsX[r++];
    }
    while(l<=mid) pointsY[index++]=pointsX[l++];
    while(r<=right) pointsY[index++]=pointsX[r++];
    for(l=left;l<=right;l++) pointsX[l]=pointsY[l];
}

double divide(int l,int r, point* p1,point* p2){
    if(r-l<=0) return INF;
    else if(r-l==1){
        //merge(l,r);
        *p1=pointsX[l];
        *p2=pointsX[r];
        return distance(pointsX[l],pointsX[r]);
    }else{
        point lp1;
        point lp2;
        point rp1;
        point rp2;
        double min_distance;
        int i,j,mid=(r+l)/2;
        double middle_x=pointsX[mid].x;
        
        double min_distance_l = divide(l, mid, &lp1, &lp2);
        double min_distance_r = divide(mid + 1, r, &rp1, &rp2);

        if (min_distance_l<min_distance_r){
            min_distance=min_distance_l;
            *p1=lp1;
            *p2=lp2;
        }else{
            min_distance=min_distance_r;
            *p1=rp1;
            *p2=rp2;
        }
        int rb=mid;
        int lb=mid;
        while(pointsX[rb].x<middle_x+min_distance&&rb<=r) rb++;
        while(pointsX[lb].x>middle_x-min_distance&&lb>=l) lb--;
        point tp1;
        point tp2;
        double mmd=violent(lb,rb,&tp1,&tp2);
        if(mmd<min_distance){
            min_distance=mmd;
            *p1=tp1;
            *p2=tp2;
        }
        return min_distance;
    }
}
void merge_sort(double* array,int start,int end){
	if(start==end) array[start]=array[start]; else{
		int middle=(start+end)/2;
		merge_sort(array,start,middle);
		merge_sort(array,middle+1,end);
		double temp[end-start+1];
		int i=start,j=middle+1,k=0;
		while(i<=middle&&j<=end){
			if(array[i]<=array[j]) temp[k++]=array[i++];
			else temp[k++]=array[j++];
		}
		while(i<=middle) temp[k++]=array[i++];
		while(j<=end) temp[k++]=array[j++];
		k=0;
		for(i=start;i<=end;i++) array[i]=temp[k++];
	}
}

int main(){
    srand((int)time(0));
    double x[N];
    double x2[N];
    for(int i=0;i<N;i++) x[i]=(double)rand()/RAND_MAX*10000;
    merge_sort(x,0,N-1);
    for(int i=0;i<N;i++){
        pointsX[i].x=x[i];
        pointsX[i].y=(double)rand()/RAND_MAX*10000;
    }
    point p1;
    point p2;
    double md;
    clock_t start;
    clock_t end;

    start=clock();
    md=divide(0,N-1,&p1,&p2);
    printf("\nDivide method\n");
    printf("Min distance=%f\n",md);
    printf("Point 1 (%f,%f)\n",p1.x,p1.y);
    printf("Point 2 (%f,%f)\n",p2.x,p2.y);
    end=clock();
    printf("Time consumed:%f\n",end-start);

    start=clock();
    md=violent(0,N,&p1,&p2);
    printf("\nViolent method\n");
    printf("Min distance=%f\n",md);
    printf("Point 1 (%f,%f)\n",p1.x,p1.y);
    printf("Point 2 (%f,%f)\n",p2.x,p2.y);
    end=clock();
    printf("Time consumed:%f\n",end-start);

    return 0;
}