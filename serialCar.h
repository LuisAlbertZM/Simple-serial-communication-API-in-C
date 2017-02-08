#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#define LOG_FILE_NAME "logEnergy.txt"    
#define SERIAL_DEVICE "/dev/ttyACM0"

int openPort(void);
void setupSerial(int uart0_filestream);
void sendCommand(unsigned char* command,int uart0_filestream);
FILE *startLog(void);
void logEnergy(int uart0_filestream, FILE *logFile);

