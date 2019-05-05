#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
#include<ctime>
#define THREE_DAYS  3600*24*3

using namespace std;

int stringPartToInt (string input, int start, int length){
    input =input.substr(start,length);
    return atoi(input.c_str());
}
vector<tm> parse (string input){
    vector<tm> endVector;
    input = input.substr (1,input.length()-2);
    tm parsedDate;
    const char* inputChar = input.c_str();
    char * date = strdup (inputChar);
    char *singleDate = strtok (date,",");    
    while (singleDate!=NULL){
        string dateAfter = singleDate;
        if (dateAfter.length()!=21){
            cout<<"Incorect input\n";
            exit (-1);
        }
    parsedDate.tm_year=stringPartToInt (dateAfter,1,4);
    parsedDate.tm_mon=stringPartToInt (dateAfter,6,2);
    parsedDate.tm_mday=stringPartToInt (dateAfter,9,2);
    parsedDate.tm_hour=stringPartToInt (dateAfter,12,2);
    parsedDate.tm_min=stringPartToInt (dateAfter,15,2);
    parsedDate.tm_sec=stringPartToInt (dateAfter,18,2);
    endVector.push_back(parsedDate);
    singleDate = strtok (NULL,",");     
    }
    free(singleDate);
    free(date);
    return endVector; 
    
}
bool isNewSession (tm lastLog, tm currentLog){
    int timeDiff = mktime(&lastLog)-mktime(&currentLog);
    return !(timeDiff <= 30*60);
}
bool isNewDay (tm lastLog, tm currentLog){
    return !(currentLog.tm_year==lastLog.tm_year && 
        currentLog.tm_mon==lastLog.tm_mon &&
        currentLog.tm_mday ==lastLog.tm_mday)
}
bool isLessThanTreeDays (tm lastLog, tm currentLog){
    int timeDiff = mktime(&currentLog)-mktime(&lastLog);
    return timeDiff<=THREE_DAYS;

}
bool sendRequestToClient (string input){
    vector <tm> datesVector = parse(input);
    tm lastLog, currentLog;
    int size = datesVector.size() -1;
    int sessionLog=1, days_log=1;

    lastLog = datesVector[size];
    currentLog = datesVector[size];
    while (size>=0 && isLessThanTreeDays(lastLog,currentLog)){
        if (isNewSession(lastLog,currentLog))
            sessionLog++;
        if (isNewDay(lastLog,currentLog))
            days_log++;
        lastLog=currentLog;
        size--;
        currentLog = datesVector[size];        
    }
    return sessionLog>=6 && days_log==3;
}
int main(){
    string input ="['2017-03-10 08:13:11','2017-03-10 19:01:27','2017-03-11 07:35:55','2017-03-11 16:15:11','2017-03-12 08:01:41','2017-03-12 17:19:08']";
    cout<<sendRequestToClient (input);

}