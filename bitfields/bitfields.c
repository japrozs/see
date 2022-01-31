#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TS_BUF_LENGTH 30

#define LOG_TIME  0x01 // 0x00000001
#define LOG_DATE  0x02 // 0x00000010
#define LOG_USER  0x04 // 0x00000100
#define LOG_COUNT 0x08 // 0x00001000

void logmsg(FILE *fp, char *message, uint8_t options){
	static uint64_t logcount = 0;

	time_t time_val;
	char timestamp[TS_BUF_LENGTH];
	char datestamp[TS_BUF_LENGTH];
	struct tm* tm_info;

	time_val = time(NULL);
	tm_info = localtime(&time_val);

	strftime(datestamp, TS_BUF_LENGTH, "%F (%a)", tm_info);
	strftime(timestamp, TS_BUF_LENGTH, "%H:%M:%S (%a)", tm_info);

	if(options & LOG_COUNT)
		fprintf(fp, "%lli, ", ++logcount);
	if(options & LOG_DATE)
		fprintf(fp, "%s, ", datestamp);
	if(options & LOG_TIME)
		fprintf(fp, "%s, ", timestamp);
	if(options & LOG_USER)
		fprintf(fp, "%s, ", getlogin());
	fprintf(fp, "%s\n", message);
}

int main(){
	logmsg(stdout, "Things are running fine.", 0);
	logmsg(stdout, "Hmmm...maybe not.What's this?", LOG_USER | LOG_DATE);
	logmsg(stdout, "The wheels are coming off!", LOG_TIME | LOG_USER | LOG_COUNT);
	logmsg(stdout, "AAAAAARGH.", LOG_COUNT);
}
