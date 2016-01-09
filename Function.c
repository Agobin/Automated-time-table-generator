#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"Function.h"

void  printfilecontent(char *filename, int num){ //fxn to print the content of a file
    FILE *ptr;
    char element[30];
    int sn=0,size;
    ptr=fopen(filename,"r");
    system("reset");
    if( num == 0)
        printf("\t\t\t\tLIST OF CLASSES AND THEIR SIZES.");
    else
        printf("\n\t\t\tLIST OF SUGGESTED CLASSES AND THEIR SIZES.");
    printf("\n\t _______________________________________________________________________\n");
    printf("\t| S/N |  Name of classroom       |\t  Size of classroom /students   |\n");
    printf("\t|_____|__________________________|______________________________________|\n");
    while( !feof(ptr) ){
        fscanf(ptr,"%s%d",element,&size);
        if( num == 0){   //prints all elements in the file
            printf("\t|     |                          |                                      |\n");
            printf("\t|%3d  |  %-24s|      %-32d|\n",sn+1,element,size);
            printf("\t|_____|__________________________|______________________________________|\n");
        sn++;
        }
        if( size > num-10 && size < num+10 ){   //prints the elements based on a selection
            printf("\t|     |                          |                                      |\n");
            printf("\t|%3d  |  %-24s|      %-32d|\n",sn+1,element,size);
            printf("\t|_____|__________________________|______________________________________|\n");
        sn++;
        }
    }
    if( num == 0){
        printf("\n    Enter del to delete a record,   sch to schedule a class,  view to view scheduled classes.\n");
        printf("    Enter exit application,     sug to seek for suggestion to schedule a class         view-all to view all of the timetable for a week.\n");
    }
    printf("\n");
    fclose(ptr);
}

bool present(char *filename,char * element){  //fxn to check if an element is already present in the file for classrooms and their sizes
    FILE *ptr;
    char fromfile[30];
    int size;
    ptr=fopen(filename,"r");
    while( !feof(ptr)){
        fscanf(ptr,"%s%d",fromfile,&size);
        if ( strcmp(element,fromfile) == 0){
            fclose(ptr);
            return true;
        }
    }
    fclose(ptr);
    return false;
}
void delete(char * filename, char * element){        //fxn to delete
	FILE *fp,*fp1;
	char classname[30];
	int class_size;
	fp=fopen(filename,"r");
	fp1=fopen("delete.txt","w");
	while( !feof(fp)){
		fscanf(fp,"%s%d",classname,&class_size);
		fprintf(fp1,"\n%s\t\t%d",classname,class_size);
	}
	fclose(fp);
	fclose(fp1);
	fp=fopen(filename,"w");
	fp1=fopen("delete.txt","r");
	while(!feof(fp1)){
		fscanf(fp1,"%s%d",classname,&class_size);
		if(strcmp(classname,element) == 0)
			continue;
		else
			fprintf(fp,"\n%s\t\t%d",classname,class_size);
	}
    printf("\nData deleted successfully!\n");
	fclose(fp1);
	fclose(fp);

}
void uppercase( char *name){
        name[0]=toupper(name[0]);
}
bool isfree( char *day,char * classname,char *course_code,char *time){
    FILE *dayptr;
    char fclassname[30],fcoursecode[15],ftime[10];
    if( strcmp(day,"MONDAY" ) == 0 )    //in case the day falls on monday to saturday location of pointer varies
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/MONDAY.txt","r");
    if( strcmp(day,"TUESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/TUESDAY.txt","r");
    if( strcmp(day,"WEDNESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/WEDNESDAY.txt","r");
    if( strcmp(day,"THURSDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/THURSDAY.txt","r");
    if( strcmp(day,"FRIDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/FRIDAY.txt","r");
    if( strcmp(day,"SATURDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/SATURDAY.txt","r");

    while( !feof(dayptr)){   //reading through whole of file
        fscanf(dayptr,"%s%s%s",fclassname,fcoursecode,ftime);
        if(  strcmp(classname,fclassname) == 0 && strcmp(course_code,fcoursecode) == 0 && strcmp(time,ftime) == 0  ){
            printf("\n\tCurrent schedule already exist!\n");
            fclose(dayptr);
            return false;
        }
        if(  strcmp(classname,fclassname) == 0 && strcmp(time,ftime) == 0  ){
            fclose(dayptr);
            return false;
        }
    }
    fclose(dayptr);
    return true;
}
 void writefile( char *day,char *classname, char *course_code, char*time ) {     //fxn to write schedules to files
    FILE *dayptr;
    if( strcmp(day,"MONDAY" ) == 0 )    //in case the day falls on monday to saturday location of pointer varies
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/MONDAY.txt","a+");
    if( strcmp(day,"TUESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/TUESDAY.txt","a+");
    if( strcmp(day,"WEDNESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/WEDNESDAY.txt","a+");
    if( strcmp(day,"THURSDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/THURSDAY.txt","a+");
    if( strcmp(day,"FRIDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/FRIDAY.txt","a+");
    if( strcmp(day,"SATURDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/SATURDAY.txt","a+");
    fprintf(dayptr,"\n%s\t%s\t%s",classname,course_code,time);
    fclose(dayptr);
}
bool checkday(char *day){
    int i;
    for( i=0;i<sizeof(day)+1;i++)  //converts the characters of the day to upper case
        day[i]=toupper( day[i]);
    if( strcmp(day,"MONDAY") == 0 || strcmp(day,"TUESDAY") == 0 || strcmp(day,"WEDNESDAY") == 0 || strcmp(day,"THURSDAY") == 0 ||   \
        strcmp(day,"FRIDAY") == 0 || strcmp(day,"SATURDAY") == 0 )
        return true;
    else
        return false;
}
bool schedulePresent(char *day,char * classname,char *coursecode,char * time){
    FILE *dayptr;
    char fclassname[30],fcoursecode[15],ftime[10];
    int i;
    for( i=0;i< sizeof(day);i++)
        day[i]=toupper(day[i]);
    if( strcmp(day,"MONDAY" ) == 0 )    //in case the day falls on monday to saturday location of pointer varies
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/MONDAY.txt","r");
    if( strcmp(day,"TUESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/TUESDAY.txt","r");
    if( strcmp(day,"WEDNESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/WEDNESDAY.txt","r");
    if( strcmp(day,"THURSDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/THURSDAY.txt","r");
    if( strcmp(day,"FRIDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/FRIDAY.txt","r");
    if( strcmp(day,"SATURDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/SATURDAY.txt","r");
    while( !feof(dayptr)){
        fscanf(dayptr,"%s%s%s",fclassname,fcoursecode,ftime);
        if( strcmp(classname,fclassname) == 0 && strcmp(coursecode,fcoursecode) == 0 && strcmp( time,ftime) == 0)
            return true;
    }
    return false;
}
void Deleteschedule(char *day,char * classname,char *coursecode,char * time){
    FILE *dayptr,*temp;
    char fclassname[30],fcoursecode[15],ftime[10];
    int i;
    for( i=0;i< sizeof(day) + 3;i++)
        day[i]=toupper(day[i]);
    if( strcmp(day,"MONDAY" ) == 0 )    //in case the day falls on monday to saturday location of pointer varies
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/MONDAY.txt","r");
    if( strcmp(day,"TUESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/TUESDAY.txt","r");
    if( strcmp(day,"WEDNESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/WEDNESDAY.txt","r");
    if( strcmp(day,"THURSDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/THURSDAY.txt","r");
    if( strcmp(day,"FRIDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/FRIDAY.txt","r");
    if( strcmp(day,"SATURDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/SATURDAY.txt","r");
        
    temp=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/Temporal.txt","w");
    
    while( !feof(dayptr)){         //transfering items except that to be deleted
        fscanf(dayptr,"%s%s%s",fclassname,fcoursecode,ftime);
        if( strcmp(classname,fclassname) ==0 && strcmp(coursecode,fcoursecode) ==0 && strcmp(time,ftime)  ==0 )  //removes targeted data
            continue;
        else
            fprintf(temp,"\n%s\t\t%s\t\t%s",fclassname,fcoursecode,ftime);
    }
    fclose(temp);
    fclose(dayptr);
    temp=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/Temporal.txt","r");
    if( strcmp(day,"MONDAY" ) == 0 )    //in case the day falls on monday to saturday location of pointer varies
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/MONDAY.txt","w");
    if( strcmp(day,"TUESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/TUESDAY.txt","w");
    if( strcmp(day,"WEDNESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/WEDNESDAY.txt","w");
    if( strcmp(day,"THURSDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/THURSDAY.txt","w");
    if( strcmp(day,"FRIDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/FRIDAY.txt","w");
    if( strcmp(day,"SATURDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/SATURDAY.txt","w");
        
    while( !feof(temp)){   //returning items back
        fscanf(temp,"%s%s%s",fclassname,fcoursecode,ftime);
        fprintf(dayptr,"\n%s\t\t%s\t\t%s",fclassname,fcoursecode,ftime);
    }
    fclose(dayptr);
    fclose(temp);
}
void print_schedule(char * day){           //fxn to print the schedules on a day
    FILE *dayptr;
    char fclassname[30],fcoursecode[15],ftime[10];
    if( strcmp(day,"MONDAY" ) == 0 )    //in case the day falls on monday to saturday location of pointer varies
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/MONDAY.txt","r");
    if( strcmp(day,"TUESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/TUESDAY.txt","r");
    if( strcmp(day,"WEDNESDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/WEDNESDAY.txt","r");
    if( strcmp(day,"THURSDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/THURSDAY.txt","r");
    if( strcmp(day,"FRIDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/FRIDAY.txt","r");
    if( strcmp(day,"SATURDAY" ) == 0 )
        dayptr=fopen("/home/fobi/Desktop/Automated_Time_Table in linux/Schedules/SATURDAY.txt","r");
    printf("\n\n\t\t\t\tSchedules on %s\n",day);
    int i=0;
    while( !feof(dayptr)){
        fscanf(dayptr,"%s%s%s",fclassname,fcoursecode,ftime);
        if( i==0){  //prints the heading diferently
            printf("\n\t __________________________________________________________________________\n");
            printf("\t|       |                                |                  |              |\n");
            printf("\t|  S/N  |        %-24s|    %-14s|    %-10s|\n",fclassname,fcoursecode,ftime);
            printf("\t|_______|________________________________|__________________|______________|\n");
        }
        else{
            printf("\t|       |                                |                  |              |\n");
            printf("\t|  %2d   |      %-24s  |      %-10s  |  %-10s  |\n",i,fclassname,fcoursecode,ftime);
            printf("\t|_______|________________________________|__________________|______________|\n");
        }
        i++;
    }
    fclose(dayptr);
    printf("\n\n");
}

