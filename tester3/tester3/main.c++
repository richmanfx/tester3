using namespace std;

#include <map>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <termios.h>

// Прототипы функций
map<string, string> getSymbolCode();
void mouseMove(string deviceId, string deviceIpAddress, int deviceUdpPort, string offset);
void controlKeysInterception();
int getRandomDelay(int minDelaym, int maxDelay);
std::string getFileMessage(const std::string& fileName);
void sendUdpPacket(string deviceId, string deviceIpAddress, int deviceUdpPort, 
                   string b1, string b2, string b3, string b4);

int main(void)
{
	cout << "Start tester3" << endl;
    
    // TODO: Читать эти параметры из файла
    string deviceId = "3485";                       // Идентификатор устройства
    string deviceIpAddress = "192.168.0.222";       // IP-адрес устройства
    int deviceUdpPort = 12345;                      // UDP-порт устройства
    string messageFileName = "message.txt";
    int minDelay = 100;     // Минимальная задержка нажатия клавиш, миллисекунды
    int maxDelay = 700;     // Максимальная задержка нажатия клавиш, миллисекунды
    int releaseDelay = 10;  // Миллисекунды на отпускание клавиш
    
    srand((unsigned)time(NULL));        // Инициализация случайного генератора временем
        
    // Читать файл с текстовым сообщением
    string txtMessage = getFileMessage(messageFileName);
//    string txtMessage = "Инициализация ";       // Строка для отладки
    
    map<string, string> symbolCodesMap = getSymbolCode();
    
    for (long unsigned int i = 0; i < txtMessage.length(); i++) {
        
        // Перехват клавиш управления
//        controlKeysInterception();


        // Индикатор работы
        if (i % 50 == 0) {
            cout << i << endl;
        }
        

        // Пошевелить мышкой через каждые 300 нажатий кнопок
        if (i % 300 == 0) {
            mouseMove(deviceId, deviceIpAddress, deviceUdpPort,  "00007");      // X=+7, Y=+7 пикселей
            usleep(10000 * getRandomDelay(minDelay, maxDelay));
            mouseMove(deviceId, deviceIpAddress, deviceUdpPort,  "65529");      // X=-7, Y=-7 пикселей
            cout << "Mouse" << endl;
        }
        
        char symbol= txtMessage.at(i);
//         cout << int(symbol) << endl;       // Вывод в консоль для отладки
        string symbolCode = symbolCodesMap[std::to_string(int(symbol))];
    
        if (symbolCode.length() == 3) {
            
            usleep(1000 * getRandomDelay(minDelay, maxDelay));
            
            // Нажать и отпустить 
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode, "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode, "00000", "00000");
            usleep(releaseDelay * 1000); 
            
        } else if (symbolCode.length() == 6) {
            
            usleep(1000 * getRandomDelay(minDelay, maxDelay));
            
            // C Шифтом или Ctrl нажимать
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(0, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(3, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(3, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(0, 3), "00000", "00000");
            usleep(releaseDelay * 1000);

        } else if (symbolCode.length() == 6 && symbolCode == "228225") {   // Переключить раскладку на RUS
        
            usleep(1000 * getRandomDelay(minDelay, maxDelay));
        
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(0, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(3, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(0, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(3, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            
        } else if (symbolCode.length() == 9) {
            
            usleep(1000 * getRandomDelay(minDelay, maxDelay));
            
            // Нажать клавишу русскую
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(0, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(0, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            
            // Переключиться обратно в LAT
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(3, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(6, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(3, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(6, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            
        } else if (symbolCode.length() == 12) {
            
            usleep(1000 * getRandomDelay(minDelay, maxDelay));
            
            // Нажать Шифт
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(0, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            
            
            // Нажать клавишу русскую
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(3, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(3, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            
            // Отпустить Шифт
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(0, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            
            // Переключиться обратно в LAT
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(6, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(9, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(6, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
            sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(9, 3), "00000", "00000");
            usleep(releaseDelay * 1000);
        }
    }
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

void mouseMove(string deviceId, string deviceIpAddress, int deviceUdpPort, string offset) {
    
    // 348540000012300123
    // 348540006541365413

    // Переместить курсор мыши на X=offset, Y=offset
    sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "4", "000", offset, offset);
            
}
