#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
//#include<string.h>

using namespace std;
struct date{
    int year;
    int month;
    int day;
    int sesion;
};
struct last{
    date lastdate;
    int hour;
    int min;
    int sec;
};
int cutStrToInt (string input, int start, int stop){
    string tmp ="";
    tmp.append(input,start,stop);
    const char* finish = tmp.c_str();
    return atoi(finish);
}
vector<last> parser (string input){
    vector<last> endVector;// = new vector<last>;
    input = input.erase(0,1);
    input = input.erase(input.length()-1,1);
    last finished;
    char *oneDate;
    const char* constArray = input.c_str();
    char * array = strdup (constArray);
    char kolektor [] =",";
    oneDate = strtok (array,kolektor);
    while (oneDate!=NULL){
        string dateAfter = oneDate;
        if (dateAfter.length()!=21){
            cout<<"Incorect input: "<<dateAfter<<endl;
            exit (-1);
        }
    finished.lastdate.year=cutStrToInt (dateAfter,1,4);
    finished.lastdate.month=cutStrToInt (dateAfter,6,7);
    finished.lastdate.day=cutStrToInt (dateAfter,9,10);
    finished.hour=cutStrToInt (dateAfter,12,13);
    finished.min=cutStrToInt (dateAfter,15,16);
    finished.sec=cutStrToInt (dateAfter,18,19);
    endVector.push_back(finished);
    oneDate = strtok (NULL,kolektor);     
    }
    free(oneDate);
    free(array);
    return endVector; 
    
}
bool isNewSesion (last ActuallLog, last LastLog){
    if (LastLog.lastdate.year==ActuallLog.lastdate.year && 
        LastLog.lastdate.month==ActuallLog.lastdate.month &&
        LastLog.lastdate.day ==ActuallLog.lastdate.day){
            int pauseTime = ActuallLog.hour*3600;
                pauseTime += ActuallLog.min*60;
                pauseTime += ActuallLog.sec;
                pauseTime -= LastLog.hour*3600;
                pauseTime -= LastLog.min*60;
                pauseTime -= LastLog.sec;
        if (pauseTime <= 30 * 60)
            return false;
        }
    return true;
}
bool isNewDay (last LastLog, last ActuallLog){
        if (LastLog.lastdate.year==ActuallLog.lastdate.year && 
        LastLog.lastdate.month==ActuallLog.lastdate.month &&
        LastLog.lastdate.day ==ActuallLog.lastdate.day)
            return false;
        return true;
}
bool isThreeDays (last ActuallLog, last LastLog){
    int years = LastLog.lastdate.year - ActuallLog.lastdate.year;
    int months = LastLog.lastdate.month - ActuallLog.lastdate.month;
    int days = LastLog.lastdate.day - ActuallLog.lastdate.day;
    if (days <=0 && months == 0 && years == 0)
        return true;
    if (days == 28 && months == -11 && years == -1 )//new year
        return true;
    if (days == 27 && months == -1 && years == 0 && //month with 30 days
    ((LastLog.lastdate.month)==4||
    (LastLog.lastdate.month)==6||
    (LastLog.lastdate.month)==9||
    (LastLog.lastdate.month)==11))
        return true;
    if (days == 24 && months == -1 && years == 0 && //February only 27 days 
    (LastLog.lastdate.month)==2)
        return true;
    if (days == 28 && months == -1 && years == 0) // month with 31 days
        return true;
    return false;

}
bool decideFunction (string input){
    vector <last> listOfDate = parser(input);
    last lastLog, iterator;
    int size = listOfDate.size() -1;
    int sesion_log=1, days_log=1;

    lastLog = listOfDate[size];
    iterator = listOfDate[size];
    while (size>=0 && isThreeDays(lastLog,iterator)==true){
        if (isNewSesion(lastLog,iterator)==true)
            sesion_log++;
        if (isNewDay(lastLog,iterator)==true)
            days_log++;
        lastLog=iterator;
        size--;
        iterator = listOfDate[size];        
    }
    if (sesion_log>=6&& days_log==3)
        return true;
    return false;

}
int main(){
    string input ="['2017-03-10 08:13:11','2017-03-10 19:01:27','2017-03-11 07:35:55','2017-03-11 16:15:11','2017-03-12 08:01:41','2017-03-12 17:19:08']";
    cout<<decideFunction (input);

}