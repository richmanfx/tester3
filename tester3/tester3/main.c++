using namespace std;

#include <map>
#include <cmath>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "INIreader.hpp"


// Прототипы функций
void usage(void);
void controlKeysInterception();
map<string, string> getSymbolCode();
int getRandomDelay(int minDelaym, int maxDelay);
std::string getFileMessage(const std::string& fileName);
void sendUdpPacket(string deviceId, string deviceIpAddress, int deviceUdpPort, 
                   string b1, string b2, string b3, string b4);
void keyPress3(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay);  
void keyPress6(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay);
void keyPress9(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay); 
void keyPress12(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay);  
void mouseMove(string deviceId, string deviceIpAddress, int deviceUdpPort, string offset);               
void mouseBigMove(int currentSymbolNumber, int workSymbolNumber, string plusMoveSize, string minusMoveSize,
                  string deviceId, string deviceIpAddress, int deviceUdpPort, int minDelay, int maxDelay);


int main(int argc, char *argv[])
{
    // Если запустить не с числом аргументов равным одному
    if(argc != 2) usage();                 
    
    // Сообщение о старте программы
	cout << "Start" << endl;
    
    // Читать параметры из конфигурационного файла
    string iniFileName = "tester3.ini";
    INIReader reader(iniFileName);
    if (reader.ParseError() < 0) {
        cout << "Can't load '" << iniFileName << "'" << endl;
        return 1;
    }
    string deviceId = reader.Get("device", "id", "3485");       // Идентификатор устройства
    string deviceIpAddress = reader.Get("device", "ipAddress", "192.168.0.222");       // IP-адрес устройства
    int deviceUdpPort = reader.GetInteger("device", "udpPort", 12345);                      // UDP-порт устройства
    int minDelay = reader.GetInteger("delays", "minDelay", 100);     // Минимальная задержка нажатия клавиш, миллисекунды
    int maxDelay = reader.GetInteger("delays", "maxDelay", 700);     // Максимальная задержка нажатия клавиш, миллисекунды
    int releaseDelay = reader.GetInteger("delays", "releaseDelay", 10);  // Миллисекунды на отпускание клавиш
    
    // Инициализация случайного генератора временем
    srand((unsigned)time(NULL));        
        
    // Читать файл из аргумента командной строки с текстовым сообщением
    string txtMessage = getFileMessage(argv[1]);
    
    // Получить коды символов (клавиш)
    map<string, string> symbolCodesMap = getSymbolCode();
    
    // Бежать про символам сообщения
    for (long unsigned int i = 0; i < txtMessage.length(); i++) {
        
        // Перехват клавиш управления
//        controlKeysInterception();


        // Индикатор работы
        if (i % 50 == 0) {
            cout << i << endl;
        }

        // Пошевелить мышкой через каждые 300 нажатий кнопок
        // X=+7, Y=+7 пикселей и X=-7, Y=-7 пикселей
        mouseBigMove(i, 300, "00007", "65529", deviceId, deviceIpAddress, deviceUdpPort, minDelay, maxDelay);     
        
        // Получить код символа
        char symbol= txtMessage.at(i);
//         cout << int(symbol) << endl;       // Вывод в консоль для отладки
        string symbolCode = symbolCodesMap[std::to_string(int(symbol))];
    
        // Нашимать клавиши в зависимости от длины кода символа
        if (symbolCode.length() == 3) {
            keyPress3(deviceId, deviceIpAddress, deviceUdpPort, symbolCode, minDelay, maxDelay, releaseDelay);
        } else if (symbolCode.length() == 6) {
            keyPress6(deviceId, deviceIpAddress, deviceUdpPort, symbolCode, minDelay, maxDelay, releaseDelay);
        } else if (symbolCode.length() == 6 && symbolCode == "228225") {   // Переключить раскладку на RUS
            keyPress6(deviceId, deviceIpAddress, deviceUdpPort, symbolCode, minDelay, maxDelay, releaseDelay);
        } else if (symbolCode.length() == 9) {
            keyPress9(deviceId, deviceIpAddress, deviceUdpPort, symbolCode, minDelay, maxDelay, releaseDelay);
        } else if (symbolCode.length() == 12) {
            keyPress12(deviceId, deviceIpAddress, deviceUdpPort, symbolCode, minDelay, maxDelay, releaseDelay);
        }
    }
    cout << "Stop" << endl;
    exit(0);
}


// Читать текст сообщения из заданного файла
std::string getFileMessage(const std::string& fileName) {
    std::ifstream inputFileStream(fileName);
    std::stringstream stringStream;
    stringStream << inputFileStream.rdbuf();
    return stringStream.str();
}


// Послать UDP сообщение
void sendUdpPacket(string deviceId, string deviceIpAddress, int deviceUdpPort, 
                   string b1, string b2, string b3, string b4) {
    
    char message[18];
    struct sockaddr_in address;
    
    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if(socketDescriptor < 0) {
        perror("Socket error");
        exit(1);
    }
    
    address.sin_family = AF_INET;
    address.sin_port = htons(deviceUdpPort); 
    address.sin_addr.s_addr = inet_addr(deviceIpAddress.c_str());
    if(connect(socketDescriptor, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Connect error");
        exit(2);
    }
    
    sprintf(message, "%s%s%s%s%s", deviceId.c_str(), b1.c_str(), b2.c_str(), b3.c_str(), b4.c_str());
    // cout << message << endl;      // Вывод в консоль для отладки
    send(socketDescriptor, message, sizeof(message), 0);
    close(socketDescriptor);
}


// Случайная задержка из заданного диапазона
int getRandomDelay(int minDelay, int maxDelay) {
    return minDelay + rand() % (maxDelay - minDelay + 1);
    // cout << randomDelay << " ";       // Вывод в консоль для отладки
}


// Перехват клавиш управления
void controlKeysInterception() {
    
    // Структуры хранения состояния терминалов. oldt - до приема клавиши, newt - во время приема.
    struct termios oldt, newt;
    
    // Нажатая клавиша
    int ch;     
    
    // Отключить для ввода флаги "каноничный" и "эхо"
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    
    // Переключиться в новый режим
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    
    // Принять клавишу
    ch = getchar();
    
    // Переключиться в старый режим
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    
    // Вывести клавишу
    cout << ch;
    
}


// Сообщение usage-help
void usage(void){ 
    cout << "\n Использование:\n\t tester3 <имя_файла_сообщения>\n\n";
    exit(0);
}
