#include <stdio.h>
#include <stdlib.h>
#include "cformat.h"

int main(){
	char file[255];
	scanf("%s",file);
	cformat(file);
	printf("The end");
	return 0;
}
