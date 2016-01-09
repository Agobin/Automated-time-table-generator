#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define FILENAME "Data.txt"

int main(int argc,char *argv[]){
    FILE *pointer_to_data;
    char classname[30];
    int size=0;
    int num=0;
    bool skip = false;
    bool save = false;
    char *day_of_the_week[7] = {"MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"};
    
    for( ; ;){
        fflush(stdin);
        pointer_to_data=fopen(FILENAME,"a+");
        printfilecontent(FILENAME,0);
        printf("\n\nEnter name of classroom to add or a command: ");
        scanf("%s",classname);fflush(stdin);
        uppercase(classname);
        if( strcmp(classname,"View-all") == 0 ){
            int i;
            for( i=0;i< 6;i++)
                print_schedule( day_of_the_week[i]);
            skip = true;
            system("sleep 3");
        }  //end of viewing all of the timetable
        if( strcmp(classname,"View") == 0){   //code for viewing schedules
            char day[15];
            int i;
            skip = true;
            printf("\n\n\t\t\tViewing of schedules.\n\n");
            printf("Enter the day you wish to view schedule: ");
            scanf("%s",day);fflush(stdin);
            for( i=0;i< sizeof(day);i++)
                day[i]=toupper(day[i]);
            while( !checkday(day)){
                printf("Invalid day. Enter a valid day: ");
                scanf("%s",day);
                for( i=0;i< sizeof(day);i++)
                    day[i]=toupper(day[i]);
            }
            print_schedule(day);
            fflush(stdin);
            system("sleep 3");
        }   //end of code to view schedule
        if( strcmp(classname,"Sug") == 0){
            skip = true;
            printf("\n\n\t\tSuggestion.\n\n");
            printf("Enter number of students: ");
            scanf("%d",&num);fflush(stdin);
            printfilecontent(FILENAME,num);
            system("sleep 3");
        }
        if( strcmp(classname,"Sch") == 0){
            skip = true;
            fflush(stdin);
            
            char coursecode[20];
            char time[10];
            char day[15];
            char classname[30] , ch;
            int i;
            bool cont=false;
            
            printf("Enter mode(a to add a schedule / d to delete a schedule): ");
            scanf("%c",&ch);fflush(stdin);
          
            if( ch == 'd'){
                printf("\n\n\t\t\tDeleting a schedule.\n\n");
                printf("Enter the day of the schedule: ");
                scanf("%s",day);
                for( i=0;i< sizeof(day) + 3;i++)
                    day[i]=toupper(day[i]);
                while( !checkday(day) ){      //checks if the day entered is valid
                    printf("Enter a valid day: ");
                    scanf("%s",day);
                    for( i=0;i< sizeof(day) + 3;i++)
                        day[i]=toupper(day[i]);
                }
                print_schedule(day);
                printf("Enter the name of classroom: ");
                scanf("%s",classname);
                while( !present(FILENAME,classname)){
                    printf("\n\t%s is not a valid class name.\n",classname);
                    printf("\nPlease enter a valid class name: ");
                    scanf("%s",classname);
                }
                printf("Enter course code: ");
                scanf("%s",coursecode);fflush(stdin);
                printf("Enter time: ");
                scanf("%s",time);fflush(stdin);
                
                if( schedulePresent(day,classname,coursecode,time)){
                    printf("\n\n\tDo you want to delete schedule(Y/N): ");
                    scanf("%c",&ch);fflush(stdin);
                    if( ch == 'Y' || ch == 'y'){
                        Deleteschedule(day,classname,coursecode,time);
                        print_schedule(day);
                        printf("\n\tSchedule deleted successfully!\n");
                        system("sleep 3");
                    }
                    
                    if( ch == 'N' || ch == 'n'){
                        printf("\n\tSchedule not deleted!.\n");
                        system("sleep 3");
                    }
                }
                else{
                    printf("\n\tInputted schedule does not exist!\n");
                    system("sleep 3");
                }
            }
            else{
                printf("\n\n\t\t\tAdding a schedule.\n\n");
                printf("Enter day: ");
                scanf("%s",day);
                for( i=0;i<sizeof(day)+3;i++)  //converts the characters of the day to upper case
                    day[i]=toupper( day[i]);
                while( !checkday(day) ){      //checks if the day entered is valid
                    printf("Enter a valid day: ");
                     scanf("%s",day);
                    for( i=0;i<sizeof(day)+3;i++)  //converts the characters of the day to upper case
                        day[i]=toupper( day[i]);
                }
                print_schedule(day);
                printf("\nEnter course code: ");
                scanf("%s",coursecode);
                printf("Enter period on %s: ",day);
                scanf("%s",time);
                printf("Enter class name: ");
                scanf("%s",classname);
                if( present(FILENAME,classname)){
                    if( !isfree(day,classname,coursecode,time)){
                        printf("\n\tSorry period has being occupied\n");
                        system("sleep 3");
                    }
                    else{
                        printf("\n\tDo you want to save new schedule(Y/N): ");fflush(stdin);
                        scanf("%c",&ch);
                        ch = toupper(ch);
                        if ( isfree(day,classname,coursecode,time) && ch =='Y'   ){
                            writefile(day,classname,coursecode,time);
                            print_schedule(day);
                            printf("\n\t\tSchedule created successfully!\n\n");
                            save = true;
                            system("sleep 3");
                            print_schedule(day);
                            system("sleep 3");
                        }
                        if( ch == 'N'){
                            printf("\n\t\tSchedule not saved!\n");
                            system("sleep 3");
                        }
                    }   // if not free
                }  // end of if present
                    else
                        printf("\n\n\t%s is an invalid classroom name!\n",classname);

                    system("sleep 3");
            }  //end of else for adding
        }  // // end of schedulling code
        if (strcmp(classname,"Exit") == 0){      //in case the user wants to exit
            if( save)
                printf("\n\n\tData saved successfully!\n\n");
            fclose(pointer_to_data);
            system("sleep 2");
            exit(0);
        }   // end of exitting code
        if (strcmp(classname,"Del") == 0){      //in case the user wants to delete data of a classroom
        	char classname[30] , note;
        	int size;
        	skip=true;
            printf("\n\t\tDeleting data.\n");
            printf("\nEnter name of the class to delete: ");
            scanf("%s",classname);fflush(stdin);
            if ( present(FILENAME,classname) ) {  //if the classroom name is already in the file
            	fflush(stdin);
                printf("\nDo you want to proceed with delete(Y/N): ");
                scanf("%c",&note);fflush(stdin);
                note = toupper(note);
                if( note =='Y'){
                    delete(FILENAME,classname);
                 	printf("\n\t%s deleted succesfully!\n",classname); 
                 	system("sleep 3");
                 }
                if( note == 'N')
                    printf("\n\tData not deleted!.\n");
                system("sleep 3");
            }
        	  else{
        	  	printf("\n\tClass name %s could not be found. Please check again\n",classname);
                system("sleep 3");
        	  	}
        }   //// end of deleting code
        if ( present(FILENAME,classname)){  //if the classroom name is already in the file
            printf("\n\tClassroom name is already present!\n\n");
            system("sleep 2");
        }
        if( !present(FILENAME,classname) && skip == false ){
            printf("Enter size of classroom: ");
            scanf("%d",&size);
            save = true;
            fprintf(pointer_to_data,"\n%s\t%d",classname,size);
            fclose(pointer_to_data);
        }
		skip = false;
    } //end of infinite for loop

    return 0;
}
