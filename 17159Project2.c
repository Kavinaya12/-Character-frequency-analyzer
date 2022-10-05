#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
typedef struct character{
       char c;
       char w[100];
       int num;
       float percent;
       struct character* next;
       int done;
   }str;


void print_space(int);
void graph(int y,int z,str* s,int);
int max_length(int n, str* s);
str* max(str* s,int r,int y);



    
str* charctr=NULL;
str* words=NULL;
str* wordsNew=NULL;
str* charctrNew=NULL;


int main (int argc, char** argv)
{  
   FILE *fp[argc],*files[argc];
 
  
   str* charctr=NULL;
   str* words=NULL;
   int word=0, charc=0,scaled=0,list=10,x=0,nullfile=0,wrolist=0,exit=0,err=0,nfile=0,len=0,word_count=0,char_count=0,i=0;
   float total_elements=0;
   char b[]="--scaled";
   if(argc==1){                      //if argc==1
      printf("No input files were given\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
      exit=1;
      }
   else{ 
        int j=1;
        while(j!=argc && exit!=1){                           //loop to detect cmd linr arc
            fp[j-1]=fopen(argv[j],"r");
            if(fp[j-1]==NULL){                      //if file is null
                nullfile++;
                x=j;       
                
                if(argv[x][0]=='-'){              //if commd begins with --
                    if(argv[x][1]=='c'&& argv[x][2]=='\0'){          //if -c
                        charc=1;
                        
                    }
                    else if(argv[x][1]=='w'&& argv[x][2]=='\0'){   //if -w
                        word=1;
                    }
                    
                    else if(strcmp(argv[x],b)==0){
                        scaled=1;                               //if --scaled
                    }
                    else if(argv[x][1]=='l' && argv[x][2]=='\0'){            //if -l
                        if(argv[x+1]==NULL){             //no options after -l
                            printf("Not enough options for [-l]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                            exit=1;                      //program exit=1
                            break;
                        }
                        else{
                            int a=atoi(argv[x+1]);
                            char* p = argv[x+1];
                            while (*p != '\0')
                            {   if(a<0){              //negative number   -l -3
                                    printf("Invalid option(negative) for [-l]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                                    exit=1;
                                    break;
                               }
                               
                               else if (*p<'0' || *p>'9')     //if not a number     -l r
                                {
                                    printf("Invalid option for [-l]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                                    exit=1;
                                    break;
                                }
                               else if(a==0){             //-l 0  zero
                                   exit=1;
                                   break;
                               }
                                
                                p++;
                            }
                           
                            if(a>0){
                                list=a;            //elements should print
                                j++;
                                nullfile++;
                            }
                        }
                    }                                
                    else{                                   //-## wrong input
                            printf("Invalid option [%s]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[x],argv[0]);
                            exit=1;
                            break;
                    }
              }                      //1.1 finish
              else{                                        //no ---
                      err=1;   //not correct format  ex: rehf
              }
              
            }   //null close
            else{
                
                files[i]=fopen(argv[j],"r");      //files 
                fclose(fp[j-1]);
                nfile++;
                i++;
            }
                
              j++;  
              
        }
        
   }  
   
   if(word==1 && charc==1 && exit!=1){   // if -c && -w
      printf("[-c] and [-w] cannot use together\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
      exit=1;
   }
   if(err==1 && exit!=1){              //not correct format err
       printf("Cannot open one or more given files\n");
       exit=1;
   }
   if(nullfile==argc-1 && exit!=1){      //no input files
       printf("No input files were given\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
       exit=1;
   }

 
    int done=0;
    if(exit==0 && charc==1){           //for print character
       int j=0;
       while(j<nfile){                //loop for number of files
           char C;
           while((C=fgetc(files[j]))!=EOF){   //loop for character
                 
               done=0;
               if((tolower(C)>=97 && tolower(C)<=122)||(tolower(C)>=48 && tolower(C)<=57) ){       //preprocessing
                  str *p=charctr;
                  while(p!=NULL && done!=1){           //loop for linked list
                     if(tolower(C)==p->c){             //if alresdy exist
                        (p->num)++;                    //add count by one
                        done=1;                        //added
                        total_elements++;              //total elements++
                     }
                   p=p->next;
                  }
                  if(done==0){                       //if not added
                      total_elements++;
                      char_count++;
                      str *s,*w;
                      s=(str*)malloc(sizeof(str));
                      s->c=tolower(C);
                      s->num=1;
                      s->next=NULL; 
                       if(charctr==NULL){
                          charctr=s;               //set as head
                      }
                      else{
                      w=charctr;
                      while(w->next!=NULL){  
                        w=w->next;
                      }
                      w->next=s;                     //set as node
                     }
                     }   
                  }
           }
           fclose(files[j]);
           j++;
       }
       
       if(total_elements==0){                           //there are no alphanumeric chars
       printf("No data to process\n");
       
       }
     else{
      /*str *q;
        int x=0;
        int l=0;*/
      
       str *v=NULL;
        int e=0,y=0;
       while(e<char_count && y<list ){                     //sorting
           int len=0;
           v=max(charctr,0,list);                           //finds maximum count occured c
           
          str *s,*w;                                                                   
       
                      s=(str*)malloc(sizeof(str));           //save the max to new list
                      s->c=v->c;
                      s->num=v->num;
                      s->next=NULL;
                      if(charctrNew==NULL){
                          charctrNew=s;
                      }
                      else{
                      w=charctrNew;
                      while(w->next!=NULL){
                        w=w->next;
                      }
                      w->next=s;
                     }
                     
        e++;
        y++;
       }
       
       
       
       str* k;
        k=charctrNew;
      while(k!= NULL){                                  
        k->percent=(float)(k->num)*(float)100/total_elements;     //calc the precentage
        k=k->next;
     }
     graph(list,scaled,charctrNew,0);                              //print the graph
     
     }
    }
    else if(exit==0){                                             //if should print word
       int j=0;
       while(j<nfile){                                            //loop fo no of files
       char C[100];
               while((fscanf(files[j],"%s",C))!=EOF){         
                 done=0;
                 int j;
                 for(int i=0;C[i]!='\0';++i){     
                     C[i]=tolower(C[i]);                                                             //change to lowercase
                     if(!(C[i]>=97 &&  C[i] <=122) && C[i]!='\0' && !(C[i]>=48 &&  C[i] <=57)){        //preprocessing
                         for(int j=i; C[j]!='\0'; ++j){
                           C[j]=C[j+1];                                                           
                         }
                       i=i-1;
                     }
                } 
                if(C[j]!='\0'){
               
                str *p=words;
                  while(p!=NULL && done!=1){
                     if(strcmp(p->w,C)==0){              //if word already exist
                        (p->num)++;
                        done=1;
                        total_elements++;
                     }
                     
                   p=p->next;
                  }
                  if(done==0){
                      total_elements++;
                      word_count++;
                       
                      str *s,*w; 
                      s=(str*)malloc(sizeof(str));      //if not word exist add it
                      strcpy(s->w,C);
                      s->num=1;
                      s->next=NULL;
                      if(words==NULL){
                          words=s;
                      }
                      else{
                      w=words;
                      while(w->next!=NULL){
                        w=w->next;
                      }
                      w->next=s;
                     }
                     } 
                    }  
           }
       fclose(files[j]);
       j++;
       }
       
        if(total_elements==0){                   //there are no alphanumeric chars
       printf("No data to process\n");
       
       }
       else{
       str *q=NULL;
        int x=0,l=0; 
       while(x<word_count && l<list ){               //sorting
           int len=0;
           q=max(words,1,list);                     //max occured word
           
          str *s,*w;                                                                   
       
                      s=(str*)malloc(sizeof(str));             //save to new list
                      strcpy(s->w,q->w);
                      s->num=q->num;
                      s->next=NULL;
                      if(wordsNew==NULL){
                          wordsNew=s;
                      }
                      else{
                      w=wordsNew;
                      while(w->next!=NULL){
                        w=w->next;
                      }
                      w->next=s;
                     }
                     
        x++;
        l++;
       }
       
        free(words);
        free(charctr);
       str* k;
      k=wordsNew;
      while(k!= NULL){
        k->percent=(float)(k->num)*(float)100/total_elements;   //calc percentage
        k=k->next;
     }
    
      graph(list,scaled,wordsNew,1);                              //prints graph
     
   
   
   }
    }
  
    free(wordsNew);
    free(charctrNew);
   
 return 0;     
} 






void graph(int y,int z,str* s,int yes){    //y=list count, scaled->(z=1)  else->(z=0)    ,yes=1->word ,yes=0->character
      float p_word,p_char;
      int line;
      int a=1,len=0,float_space=0;
      str* c=s;
      if(c->percent>=10 && c->percent<100 ){            // xx.xx%
      float_space=6;                   //space for frequency
      
      }
      
      else if(c->percent==100){        //100.00%
      float_space=7; 
      }
      
      else{                           //x.xx%
      float_space=5;                  //space for frequency
      }
      
      if(z==1){                //scaled
         p_word=(77-max_length(y,s)-float_space)/s->percent;  
         p_char=(76-float_space)/s->percent;
      }
      
      else if(z==0){          //not scaled
         p_word=(float)(77-max_length(y,s)-float_space)/100;
         p_char=(float)(76-float_space)/100;
      }
      
      
      printf("\n");
      
      if(yes==1){             //word graph
         len=max_length(y,s);  //max length of words
         
         while(a<=y && c!=NULL){ 
         if(c->percent==s->percent && z==1){
         line=77-max_length(y,s)-float_space;
         }
         else{
         line=p_word*c->percent;     //no of lines should print
         }
         for(int r=0;r<3;r++){ //3 lines for a element
        
           if(r==1){
               printf(" %s",c->w);                 //name
               print_space(len-strlen(c->w)+1);    //extra space
           }
           else{
               print_space(len+2);                  //space
           }   
           printf("\u2502");           //   | |
          
             for(int b=1;b<=line;b++){
                 printf("\u2591");          //prints box
             }
           if(r==1){
               printf("%.2f%%",c->percent);       //prints frequency
           }
           printf("\n");
         
         }
         
         print_space(len+2);          //space
         printf("\u2502");             // extra ||
         printf("\n");
         a++;
         c=c->next;
      }
    print_space(len+2);           
    printf("\u2514");              // L
    for(int n=0;n<77-len;n++){
    printf("\u2500");              //---
    }
     printf("\n");
      }
     if(yes==0 ){                   //charcter graph
       len=1;
       while(a<=y && c!=NULL){
       if(c->percent==s->percent && z==1){
         line=76-float_space;
         }
         else{
         line=p_char*c->percent;     //no of lines should print
         }
        
         for(int r=0;r<3;r++){ //3 lines for a element
        
           if(r==1){
               printf(" %c ",c->c);      //print charcter
              
           }
           else{
               print_space(3);
           }   
           printf("\u2502");           // |
           
             for(int b=1;b<=line;b++){
                 printf("\u2591");      //box
             }
        
           if(r==1){
               printf("%.2f%%",c->percent);  //frequency
           }
           printf("\n");
         
         }
         
         print_space(len+2);
         printf("\u2502");             // |
         printf("\n");
         a++;
         c=c->next;
      }
    print_space(len+2);  
    printf("\u2514");                   // L
    for(int n=0;n<77-len;n++){
    printf("\u2500");                  //-----
    }
     printf("\n");
      }
     
       
      
}




void print_space(int y){         //print space y times
   for(int i=0;i<y;i++){
       printf(" ");
   }
}





int max_length(int n,str* s){     //finds maximum length of first n no of max occured words
 str *c=s;
 int len=0,a=0;
   while(c!=NULL && a<n){         
      if(len<strlen(c->w)){        //finds max length
          len=strlen(c->w);
          
      }
      c=c->next;
      a++;
      }
      return len;
}






str* max(str* s,int word,int l){        //find max occured word/char    (word=1)->word  (word=0)->character
  str *q,*p;
  p=(str*)malloc(sizeof(str));
  int len=0,x=0;
  char t[50];
  char m;
  q=s;
    if(word==1){                                       //for words
    while(q!=NULL){
                if(len<(q->num) && (q->done)!=1){   //finds max occured word     
                    strcpy(t,q->w);
                    len=q->num;
                    
                }
                q=q->next;
                
                }
    q=s;
     while(q!=NULL){                    
        if(strcmp(t,q->w)==0){
          q->done=1;
     }     
      q=q->next;      
     }       
  
    p->num=len;
    strcpy(p->w,t);
    p->next=NULL;
    
    }
    else if(word==0){         //for charater
     while(q!=NULL){  
                if(len<(q->num) && (q->done)!=1){  //finds maximum occured character
                
                    m=q->c;
                    len=q->num;
                } 
               q=q->next;
            }
     q=s;
     while(q!=NULL){
        if(m==q->c){
          q->done=1;
     }     
      q=q->next;      
     }    
    p->num=len;
    p->c=m;
    }
    
    
    return p;
   }
  

