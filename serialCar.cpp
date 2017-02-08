//-------------------------------------------------------------------------------------------------- 
// EINDHOVEN UNIVERSITY OF TECHNOLOGY
//-------------------------------------------------------------------------------------------------- 
// Author: Luis Albert Zavala Mondragon
// Team 18
// Date and place: July 24th, 2016. Eindhoven, Netherlands
//-------------------------------------------------------------------------------------------------- 
// Based on the code found at:
//  *   http://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
//  *   https://www.cmrr.umn.edu/~strupp/serial.html
//  *   https://en.wikibooks.org/wiki/Serial_Programming/termiosi
//  *   http://tldp.org/HOWTO/Serial-Programming-HOWTO/ 
//-------------------------------------------------------------------------------------------------- 
//  AVAILABLE FUNCTIONS:
//  int openPort(void);
//  *   void setupSerial(int uart0_filestream);
//  *   void sendCommand(unsigned char* command,int uart0_filestream);
//  *   FILE *startLog(void);
//  *   void logEnergy(int uart0_filestream, FILE *logFile);
//-------------------------------------------------------------------------------------------------- 
// EXAMPLE USAGE:
/* 
    #include <termios.h>		//Used for UART
    #include "serialCar.h"
    #include <string.h>
    
    
    int main(void){
        unsigned char command[5]    = {'0','0','1','T','+'};
       
        // Serial Communicaion 
        int uart0_filestream        = openPort();
        setupSerial(uart0_filestream);
        sendCommand(command,uart0_filestream);
    
        FILE *logFile = startLog(); 
        while(1){
            logEnergy(uart0_filestream,logFile);
        }
        fclose(logFile);
        return(0);
    }
*/
//-------------------------------------------------------------------------------------------------- 

int openPort(){
    int uart0_filestream = -1;
    //uart0_filestream = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);        //Open in non blocking read/write mode
    uart0_filestream = open(SERIAL_DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);        //Open in non blocking read/write mode
    if (uart0_filestream == -1) {
        printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
    }
    return(uart0_filestream); 
}

void setupSerial(int uart0_filestream){
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;        //<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
}

void sendCommand(unsigned char* command,int uart0_filestream){
    if (uart0_filestream != -1) {
        //int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));
        int count = write(uart0_filestream,command , 5);
        if (count < 0) {
            printf("UART TX error\n");
        }
    }
}

void logEnergy(int uart0_filestream, FILE *logFile){
    int res;
    char buf[255];

    res = read(uart0_filestream,buf,255);
    if(strlen(buf)!=0)
        fputs(buf,logFile);
    buf[res]=0;
}


FILE *startLog(void){
    return(fopen(LOG_FILE_NAME,"w")); 
}
