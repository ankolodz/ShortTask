#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
#include<ctime>
#define THREE_DAYS  3600*24*3

using namespace std;

int cutInt (string input, int start, int stop){
    string tmp ="";
    tmp.append(input,start,stop);
    const char* finish = tmp.c_str();
    return atoi(finish);
}
vector<tm> parse (string input){
    vector<tm> endVector;
    input = input.erase(0,1);
    input = input.erase(input.length()-1,1);
    tm parseEvent;
    char *oneDate;
    const char* inputChar = input.c_str();
    char * date = strdup (inputChar);
    char signumParse [] =",";
    oneDate = strtok (date,signumParse);
    while (oneDate!=NULL){
        string dateAfter = oneDate;
        if (dateAfter.length()!=21){
            cout<<"Incorect input: "<<dateAfter<<endl;
            exit (-1);
        }
    parseEvent.tm_year=cutInt (dateAfter,1,4);
    parseEvent.tm_mon=cutInt (dateAfter,6,7);
    parseEvent.tm_mday=cutInt (dateAfter,9,10);
    parseEvent.tm_hour=cutInt (dateAfter,12,13);
    parseEvent.tm_min=cutInt (dateAfter,15,16);
    parseEvent.tm_sec=cutInt (dateAfter,18,19);
    endVector.push_back(parseEvent);
    oneDate = strtok (NULL,signumParse);     
    }
    free(oneDate);
    free(date);
    return endVector; 
    
}
bool isNewSesion (tm ActuallLog, tm LastLog){
    int beetwenTime;
    beetwenTime = mktime(&ActuallLog)-mktime(&LastLog);
    if (beetwenTime <= 30*60)
        return false;
    return true;
}
bool isNewDay (tm ActuallLog, tm LastLog){
        if (LastLog.tm_year==ActuallLog.tm_year && 
            LastLog.tm_mon==ActuallLog.tm_mon &&
            LastLog.tm_mday ==ActuallLog.tm_mday)
            return false;
        return true;
}
bool isLessThreeDays (tm ActuallLog, tm LastLog){
    int beetwenTime;
    beetwenTime = mktime(&LastLog)-mktime(&ActuallLog);
    if (beetwenTime<=THREE_DAYS)
        return true;
    return false;

}
bool askQuestion (string input){
    vector <tm> listOfDate = parse(input);
    tm lastLog, iterator;
    int size = listOfDate.size() -1;
    int sesion_log=1, days_log=1;

    lastLog = listOfDate[size];
    iterator = listOfDate[size];
    while (size>=0 && isLessThreeDays(lastLog,iterator)==true){
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
    cout<<askQuestion (input);

}