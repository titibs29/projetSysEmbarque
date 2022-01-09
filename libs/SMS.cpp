#include "SMS.h"


using namespace std;

 void SendSMS(string numero, string message)
{
    int connection;
    printf("Opening connection \n");
    connection = serialOpen("/dev/ttyAMA0", 9600);
    delay(1000);
    printf("Connection:  %d\n", connection);
    printf("\n");

    //Set gsm to text mode
    serialPuts(connection, "AT+CMGF=1\r\n");
    delay(1000);

    //Numb that the message should be sent to
    char num[20];
    strcpy(num, message.c_str());
    serialPuts(connection, "AT+CMGS=" );
    serialPuts(connection, num);
    serialPuts(connection, "\r\n");

    delay(1000);

    //The message
    char msg[200];
    strcpy(msg, message.c_str());
    serialPuts(connection, msg);
    delay(1000);

    //Print ctrl+x
    serialPuts(connection, "\x1A");

    delay(1000);

    printf("Done \n");

    serialClose(connection);

} 
