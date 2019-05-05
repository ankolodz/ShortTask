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
    tm parsedDate;
    char *singleDate;
    const char* inputChar = input.c_str();
    char * date = strdup (inputChar);
    char delimeter [] =",";
    singleDate = strtok (date,delimeter);
    while (singleDate!=NULL){
        string dateAfter = singleDate;
        if (dateAfter.length()!=21){
            cout<<"Incorect input: "<<dateAfter<<endl;
            exit (-1);
        }
    parsedDate.tm_year=cutInt (dateAfter,1,4);
    parsedDate.tm_mon=cutInt (dateAfter,6,7);
    parsedDate.tm_mday=cutInt (dateAfter,9,10);
    parsedDate.tm_hour=cutInt (dateAfter,12,13);
    parsedDate.tm_min=cutInt (dateAfter,15,16);
    parsedDate.tm_sec=cutInt (dateAfter,18,19);
    endVector.push_back(parsedDate);
    singleDate = strtok (NULL,delimeter);     
    }
    free(singleDate);
    free(date);
    return endVector; 
    
}
bool isNewSesion (tm lastLog, tm currentLog){
    int timeDiff;
    timeDiff = mktime(&lastLog)-mktime(&currentLog);
    if (timeDiff <= 30*60)
        return false;
    return true;
}
bool isNewDay (tm lastLog, tm currentLog){
        if (currentLog.tm_year==lastLog.tm_year && 
            currentLog.tm_mon==lastLog.tm_mon &&
            currentLog.tm_mday ==lastLog.tm_mday)
            return false;
        return true;
}
bool isLessThanTreeDays (tm lastLog, tm currentLog){
    int timeDiff;
    timeDiff = mktime(&currentLog)-mktime(&lastLog);
    return (timeDiff<=THREE_DAYS);

}
bool askQuestion (string input){
    vector <tm> datesVector = parse(input);
    tm lastLog, currentLog;
    int size = datesVector.size() -1;
    int session_log=1, days_log=1;

    lastLog = datesVector[size];
    currentLog = datesVector[size];
    while (size>=0 && isLessThanTreeDays(lastLog,currentLog)==true){
        if (isNewSesion(lastLog,currentLog)==true)
            session_log++;
        if (isNewDay(lastLog,currentLog)==true)
            days_log++;
        lastLog=currentLog;
        size--;
        currentLog = datesVector[size];        
    }
    return (session_log>=6&& days_log==3);

}
int main(){
    string input ="['2017-03-10 08:13:11','2017-03-10 19:01:27','2017-03-11 07:35:55','2017-03-11 16:15:11','2017-03-12 08:01:41','2017-03-12 17:19:08']";
    cout<<askQuestion (input);

}