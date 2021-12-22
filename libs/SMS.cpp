#include "SMS.h"

void SendSMS(char numero[20], char message[200])
{
    int connection;
    printf("Opening connection \n");
    connection = serialOpen("/dev/ttyAMA0", 9600);
    delay(1000);
    printf("Connection:  %d\n", connection);
    printf("\n");

    //Set gsm to text mode
    serialPuts(connection, "AT+CMGF=1 \r\n");
    delay(1000);

    //Numb that the message should be sent to
    serialPuts(connection, "AT+CMGS=" );
    serialPuts(connection, numero);
    serialPuts(connection, "\r\n");

    delay(1000);

    //The message
    serialPuts(connection, message);
    delay(1000);

    //Print ctrl+x
    serialPuts(connection, "\x1A");

    delay(1000);

    printf("Done \n");

    serialClose(connection);

}

