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
int bruteforce();

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

	totalProfit = bruteforce();
	
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
	
	/*Free the allocated memory*/
	free(selected);
	free(weight);
	free(profit);
	return 0;
}

/*
*@brief: Brute Force implementation of 0-1 Knapsack problem
*/
int bruteforce() {
	int i,j,isSelected=1,maxWt,maxProfit;
	int iter=pow(2.0,size);
	int result=0;
	int temp[size];
	/*Initialize the temp array */
	for(i =0;i<size;i++)
		temp[i]=0;
	
	for(i=0;i<iter;i++) {
		isSelected=1;
		maxProfit=0;
		maxWt=0;
		
		for(j=0;j<size;j++){
			if(temp[j]==1){
				maxWt+=weight[j];
				maxProfit+= profit[j];
			}
		}
		if( maxWt <= capacity && maxProfit>result){
			/*Copies the selected item in array. */
			for(j=0;j<size;j++)
				selected[j]=temp[j];
			result=maxProfit;
		}
		
		/*Calculate the next subset */
		for(j=0;j<size;j++){
			temp[j]=temp[j]+isSelected;
			isSelected = temp[j]/2;
			temp[j]=temp[j]%2;	
		} 
	}
	return result;
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
		while(ch!='\n'){
			num[j++]=ch;
			ch=fgetc(fp);
		}
		num[j]='\n';
		size = atoi(num);
		//Create weight and profit array
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
		//Read profit
		
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

