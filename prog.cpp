#include <stdio.h>
#include <stdlib.h>

void cformat(char file[]){
  FILE *f = fopen(file,"r");
  char buffile[255];
  sprintf(buffile,"%s.temp",file);
  FILE *f1 = fopen(buffile,"w");
  int lvl = 0, str = 0, len = 0;
  int kf0 = 0, kf1 = 0, kk0 = 0, kk1 = 0, kz0 = 0, kz1 = 0; // {, }, (, ), [, ]
  char c, old;
  while(!feof(f)){
    c = fgetc(f);
    switch(c){
        case '{': kf0++; break;
        case '}': kf1++; break;    
        case '(': kk0++; break;
        case ')': kk1++; break;
        case '[': kz0++; break;
        case ']': kz1++; break;
    }
    len++;
    if(len >= 80 && (c == ' ' || c == '\t')){
        fprintf(f1,"\n");
        str = 1;
        len = 0;
    }
    if(c == '{' && old != '\''){
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
    } else if(c == '}' && old != '\''){
        if(old == ';') fprintf(f1,"\n");
        for(int i = 0; i < lvl-1; i++){
            fprintf(f1,"\t");
        }
        fprintf(f1,"}\n");
        lvl--;
        str = 1;
        len = 0;
    } else if(c == '\n'){
        str = 1;
        len = 0;
        fprintf(f1,"\n");
    } else if(c != '\t'){
        if(str == 1){
            for(int i = 0; i < lvl; i++){
                fprintf(f1,"\t");
            }
            str = 0;
        }
        fprintf(f1,"%c",c);
    }
    old = c;
  }
  fclose(f);
  fclose(f1);
  if(kf0 != kf1 || kk0 != kk1 || kz0 != kz1){
    printf("Error with brackets!");
  } else {
    remove(file);
    rename(buffile,file);
  }
}

int main(){
  char file[255];
  scanf("%s",file);
  cformat(file);
  system("PAUSE");
  return 0;
}
