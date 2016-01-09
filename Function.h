#ifndef FUNCTION_H
#define FUNCTION_H

#define FILENAME "Data.txt"
bool checkday(char *day_of_the_week);
void uppercase( char *word);
void print_schedule(char * filename);
void printfilecontent(char *filename, int number_of_students);
bool present(char *filename,char *element );
bool schedulePresent(char *day,char * classname,char *coursecode,char * time);
bool isfree( char *day_txt,char *classname,char *course_code,char *time);    //day,classroom ,course_code,time
void delete(char *filename, char *element);
void writefile( char *day,char *classname, char *course_code, char*time );  //day,classroom ,course_code,time
void Deleteschedule(char *day,char * classname,char *coursecode,char * time);


#endif // FUNCTION_H_INCLUDED
