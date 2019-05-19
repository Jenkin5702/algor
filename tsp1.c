#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int setequal(int *set1, int n1, int *set2, int n2){
	if (n1!=n2) return 0;
	else{
		for(int i=0;i<n1;i++){
			if(set1[i]!=set2[i]) return 0;
		}
		return 1;
	}
}
int sethas(int *set, int e, int n){
	for(int i=0;i<n;i++) if(set[i]==e) return 1;
	return 0;
}
int *setdiff(int *set1, int n1, int element) {
	int* s=(int*)calloc(n1,sizeof(int));
	for(int i=0;i<n1;i++) s[i]=set1[i];
	for(int i=0;i<n1;i++) if(s[i]==element) for(int k=i;k<n1-1;k++) s[k]=s[k+1];
	return s;
}
int* subset(int *set, int n){
	int p = pow(2, n);	//子集个数
	int index = 0;		//当前数组指针位置
	int* ss=(int*)calloc(n*p/2+p-1,sizeof(int)); //存储子集的数组
	for (int len = 1; len <= n; len++){
		int c = 1; //长度为len的子集的个数
		for (int j = 0; j < len; j++) c = c * (n - j) / (j + 1);
		int *pointers = (int *)calloc(len, sizeof(int)); //长度为len的索引指针
		for (int k = 0; k < len; k++) pointers[k] = k;
		for (int j = 0; j < c; j++){	//计算子集
			ss[index++] = len; 	//存入这个子集的长度
			for (int k = 0; k < len; k++) ss[index++] = set[pointers[k]]; //将索引指针指向的元素存入子集数组
			for (int k = 1; k <= len; k++){ 	//更新索引指针
				if (pointers[len - k] < n - k){
					pointers[len - k]++;
					for (int l = len - k + 1; l < len; l++) pointers[l] = pointers[l - 1] + 1;
					break;
				}
			}
		}
	}
	return ss;
}

int main(){
	int i, j, k=0;
	int n=4,INF=0xFFFFFF;
	int arc[]={INF,3,6,7,5,INF,2,3,6,4,INF,2,3,7,5,INF};

	int nd = pow(2.0, (int)n-1);	//子集个数
	int d[n*nd];	//距离表格(最后要完成的)
	for(i=0;i<n*nd;i++) d[i]=0;
	for(i=1;i<n;i++) d[i*nd]=arc[i*n];	//初始化表格第0列
	
	int set[n-1];		//原始集合{1,2,...,n}
	for(i=1;i<n;i++) set[i-1]=i;
	
	int* ss = subset(set, n-1);	//求子集
	int index=0;	//子集下标
	int col_index=1;//列号下标
	int cols[nd];	//列号(子集在ss中的起始位置)
	while(col_index<nd){
		cols[col_index++]=index;
		index+=ss[index]+1;
	}
	for (j=1;j<nd;j++){	//从第1列到最后
		for(i=1;i<n;i++){	//从第一行到最后
			int* current=ss+cols[j]+1;	//当前子集
			int len=ss[cols[j]];	//当前子集的长度
			if (!sethas(current,i,len)){	//若子集不包含i
				int min = INF;
				//寻找删去一个元素的子集所在的列
				if(len>1){	//前提是这个子集不止一个元素,否则不用这么麻烦
					for(k=0;k<len;k++){
						int* s_diff=setdiff(current,len,current[k]);	//求差集
						for(int l=1;l<nd;l++){	//遍历所有的列
							int* set_to_cmp=ss+cols[l]+1;
							int set_to_cmp_len=ss[cols[l]];
							if(setequal(s_diff,len-1,set_to_cmp ,set_to_cmp_len)){
								d[i*nd+j]=arc[i*n+current[k]]+d[current[k]*nd+l];
								if(d[i*nd+j]<min){
									min=d[i*nd+j];
									printf("{%d} ",j);
									printf("%d -> ",i+1);
									printf("%d ",current[k]+1);
									printf("{%d} ",l);
									printf("\n");
								}else d[i*nd+j]=min;
								break;
							}
						}
					}
				}else{	//如果子集只是一个元素的
					d[i*nd+j]=arc[i*n+(int)set[k]]+d[(int)set[k]*nd];
					if(d[i*nd+j]<min) min=d[i*nd+j]; else d[i*nd+j] = min;
				}
			}
		}
		k++;
	}
	int min=INF;
	for(k=0;k<n-1;k++){
		int* s_diff=setdiff(set,n-1,set[k]);	//求差集
		for(int l=1;l<nd;l++){	//遍历所有的列
			int* set_to_cmp=ss+cols[l]+1;
			int set_to_cmp_len=ss[cols[l]];
			if(setequal(s_diff,n-2,set_to_cmp ,set_to_cmp_len)){
				d[nd-1]=arc[set[k]]+d[set[k]*nd+l];
				if(d[nd-1]<min){
					min=d[nd-1];
					printf("%d ",set[k]);
					printf("%d ",l);
					printf("\n");
				}else d[nd-1]=min;
				break;
			}
		}
	}
	return 0;
}
