#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/* Globale variable */
int size;
int capacity;
int *weight,*profit,*selected;

/*Funtion declaration*/
int readFile(char*);
int dynamicKnapsack();
/*
* @brief: Main function where the execution starts
*/
int main(int argc, char ** argv){
	char *input;
	int i,totalProfit=0,totalWeight=0;
	if(argc!=2) {
		printf("\nError: Invalid number of arguments!\n\n");
		return 0;
	}
	input = argv[1];
	readFile(input);

	totalProfit = dynamicKnapsack();
	
	/*Prints the output*/
	printf("\nSelected Items: {");
	for(i=0;i<size;i++) {
		if(selected[i]==1) {
			totalWeight+=weight[i];
			printf(" (Item%d, %d, %d),",i+1,weight[i],profit[i]);
		}
	}
	printf(" }\n");
	
	printf("Total Profit = %d\n",totalProfit);
	printf("Total Weight = %d\n\n",totalWeight);

	/*Free the memory*/
	free(selected);
	free(weight);
	free(profit);
	
	return 0;
}

/*
* @brief: Dynamic 0-1 knapsack 
*/
int dynamicKnapsack() {
	int i,w,result=0;
	int B[size+1][capacity+1];
	
	for(w=0;w<=capacity;w++)
		B[0][w]=0;
	for(i=0;i<=size;i++)
		B[i][0]=0;

	for(i=1;i<=size;i++){
		for(w=1;w<=capacity;w++){
			if((weight[i-1] <= w) && ((B[i-1][w-weight[i-1]] + profit[i-1]) > B[i-1][w])) {
				B[i][w]=B[i-1][w-weight[i-1]] + profit[i-1];
			}
			else {
				B[i][w]=B[i-1][w];
			}
		}
	}
	//Get the selected elements
	for(i=0;i<size;i++)
		selected[i]=0;

	w=capacity;i=size;
	while(B[i][w]!=0) {
		if(B[i][w] == B[i-1][w]){
			i=i-1;
		} 
		else{
			selected[i-1]=1;
			w=w-weight[i-1];
			i=i-1;
		}
	}

	return B[size][capacity];
}

/*
* @brief: Reads the knapsack.txt input file
*/
int readFile(char * filename) {
	FILE *fp;
	char num[255];
	int i=0,j=0;

	fp = fopen(filename,"r");
	if(fp == NULL) {
		printf("\nERROR in opening the file!\n\n");
		return 0;
	}
	char ch;
	ch=fgetc(fp);
	while(ch!='\n' && ch!=EOF) {
		//Read size;
		while(ch!='\n'){
			num[j++]=ch;
			ch=fgetc(fp);
		}
		num[j]='\n';
		size = atoi(num);
		// create weight and profit array
		weight = (int*) malloc(sizeof(int)*size);
		profit = (int*) malloc(sizeof(int)*size);
		selected = (int*) malloc(sizeof(int)*size);
		
		ch=fgetc(fp);
		//Read the weights.
		for(i=0;i<size;i++){
			j=0;
			while(ch!=',' && ch!='\n'){
				num[j++]=ch;
				ch=fgetc(fp);
			}
			num[j]='\n';
			weight[i]=atoi(num);
			if(ch=='\n')
				break;
			ch=fgetc(fp);
		}
		
		ch=fgetc(fp);
		//Read the profit.
		for(i=0;i<size;i++){
			j=0;
			while(ch!=',' && ch!='\n'){
				num[j++]=ch;
				ch=fgetc(fp);
			}
			num[j]='\n';
			profit[i]=atoi(num);
			if(ch=='\n')
				break;
			ch=fgetc(fp);
		}
		//Read capacity
		ch=fgetc(fp);
		j=0;
		while(ch!='\n' && ch!=EOF){
			num[j++]=ch;
			ch=fgetc(fp);
		}
		num[j]='\n';
		capacity = atoi(num);		
	}	
	fclose(fp);
	return 0;
}