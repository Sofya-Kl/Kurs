#include <stdio.h>
#include "cformat.h"

void cformat(char file[]) {
	FILE *f = fopen(file,"r");
	char buffile[20];
	sprintf(buffile,"%s.txt",file);
	FILE *f1 = fopen(buffile,"w");
	int lvl = 0, str = 0, len = 0;
	int sf0 = 0, sf1 = 0, sk0 = 0, sk1 = 0, skv0 = 0, skv1 = 0; 
	char c, old;
	while(!feof(f)) {
		c = fgetc(f);
		switch(c) {
	        case '{': sf0++; break;
	        case '}': sf1++; break;    
	        case '(': sk0++; break;
	        case ')': sk1++; break;
	        case '[': skv0++; break;
	        case ']': skv1++; break;
    	}
    	len++;
	    if(len >= 80 && (c == ' ' || c == '\t')) {
	    	fprintf(f1,"\n");
	        str = 1;
	        len = 0;
	    }
	    if(c == '{'&& old != '\'') {
	        lvl++;
	        for(int i = 0; i < lvl - 1; i++){
	            fprintf(f1,"\t");
	        }
	        if(old != '\n'){
	            fprintf(f1,"\n");
	            for(int i = 0; i < lvl - 1; i++){
	                fprintf(f1,"\t");
	            }
	            fprintf(f1,"{\n");
	        } else
	            fprintf(f1,"{\n");
	        str = 1;
	        len = 0;
	    } 
		else if(c == '}' && old != '\'') {
	        if(old == ';')
				fprintf(f1,"\n");
	        for(int i = 0; i < lvl-1; i++) {
	            fprintf(f1,"\t");
	        }
	        fprintf(f1,"}\n");
	        lvl--;
	        str = 1;
	        len = 0;
	    } 
		else if(c == '\n') {
	        str = 1;
	        len = 0;
	        fprintf(f1,"\n");
	    } 
		else if(c != '\t') {
	        if(str == 1){
	            for(int i = 0; i < lvl; i++) {
	                fprintf(f1,"\t");
	            }
	            str = 0;
	        }
	        if (old == ';'){
	        	fprintf(f1,"\n");
	        	for(int i = 0; i < lvl; i++) {
	                fprintf(f1,"\t");
	            }
			}	
	        fprintf(f1,"%c",c);
	    }
	    old = c;
	}
	fclose(f);
	fclose(f1);
	if(sf0 != sf1 || sk0 != sk1 || skv0 != skv1) {
		printf("Error with brackets!");
	}
	else {
		remove(file);
    	rename(buffile,file);
	}
}
