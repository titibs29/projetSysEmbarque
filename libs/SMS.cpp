#include "SMS.h"

void SendSMS(char numero[20], char message[200])
{
    int connection;
    std::cout << "Opening connection " << std::endl;
    connection = serialOpen("/dev/ttyAMA0", 9600);
    delay(1000);
    std::cout << "Connection: " << connection << std::endl
              << std::endl;

    // Set gsm to text mode
    serialPuts(connection, "AT+CMGF=1 \r\n");
    delay(1000);

    // Numb that the message should be sent to
    serialPuts(connection, "AT+CMGS=");
    serialPuts(connection, numero);
    serialPuts(connection, "\r\n");

    delay(1000);

    // The message
    serialPuts(connection, message);
    delay(1000);

    // Print ctrl+x
    serialPuts(connection, "\x1A");

    delay(1000);

    std::cout << "Done" << std::endl;

    serialClose(connection);
}
