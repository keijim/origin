#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(void){
	//int byte = 0;
	unsigned char *byte;
	unsigned long long total = 0;
	unsigned long long bc[256];
	long double prob;
	long double entropy = 0.0;
	const int bs = 4096;

	int i;
	int status;

	byte = malloc(bs);
	if( byte == NULL ){
		fputs("Can't allocate memory.",stderr);
		exit( 1 );
	}
	memset(byte,0,bs);
	memset(bc,0,sizeof(bc));

	while(1){
		status = fread(byte,1,bs,stdin);
		if(status < bs){
			break;
		}
		for(i=0;i<bs;i++){
			bc[byte[i]]++;
		}
	}

	for(i=0;i<status;i++){
		bc[byte[i]]++;
	}

	i = 0;
	while(1){
		printf("%3d : %lld\n",i,bc[i]);
		total += bc[i];
		i++;
		if(i > 255){
			printf("total : %lld\n",total);
			break;
		}
	}
	i = 0;
	while(1){
		if(bc[i] != 0){
			prob = (long double) bc[i] / (long double) total;
			entropy += prob * log2l(prob);
		}	
		i++;
		if(i > 255){
			printf("entropy : %Lf\n",-entropy);
			break;
		}
	}
	return 0;
}
