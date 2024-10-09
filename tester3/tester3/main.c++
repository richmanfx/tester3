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
    // string txtMessage = "ЭЮЯ";       // Строка для отладки
    
    map<string, string> symbolCodesMap = {
        
        {"-47", "228225"},      // Переключить на русский - Ctrl+Shift
        {"-48", "228225"},      // Переключить на русский - Ctrl+Shift
        
        {"-80", "009228225"},   // Русская 'а' и назад в английскую раскладку
        {"-79", "054228225"},   // Русская 'б' и назад в английскую раскладку
        {"-78", "007228225"},   // Русская 'в' и назад в английскую раскладку
        {"-77", "024228225"},   // Русская 'г' и назад в английскую раскладку
        {"-76", "015228225"},   // Русская 'д' и назад в английскую раскладку
        {"-75", "023228225"},   // Русская 'е' и назад в английскую раскладку
        
        {"-74", "051228225"},   // Русская 'ж' и назад в английскую раскладку
        {"-73", "019228225"},   // Русская 'з' и назад в английскую раскладку
        {"-72", "005228225"},   // Русская 'и' и назад в английскую раскладку
        {"-71", "020228225"},   // Русская 'й' и назад в английскую раскладку
        {"-70", "021228225"},   // Русская 'к' и назад в английскую раскладку
        {"-69", "014228225"},   // Русская 'л' и назад в английскую раскладку
        {"-68", "025228225"},   // Русская 'м' и назад в английскую раскладку
        {"-67", "028228225"},   // Русская 'н' и назад в английскую раскладку
        
        {"-66", "013228225"},   // Русская 'о' и назад в английскую раскладку
        {"-65", "010228225"},   // Русская 'п' и назад в английскую раскладку
        {"-128", "011228225"},  // Русская 'р' и назад в английскую раскладку
        {"-127", "006228225"},  // Русская 'с' и назад в английскую раскладку
        {"-126", "017228225"},  // Русская 'т' и назад в английскую раскладку
        
        {"-125", "008228225"},  // Русская 'у' и назад в английскую раскладку
        {"-124", "004228225"},  // Русская 'ф' и назад в английскую раскладку
        {"-123", "047228225"},  // Русская 'х' и назад в английскую раскладку
        {"-122", "026228225"},  // Русская 'ц' и назад в английскую раскладку
        {"-121", "027228225"},  // Русская 'ч' и назад в английскую раскладку
        
        {"-120", "012228225"},  // Русская 'ш' и назад в английскую раскладку
        {"-119", "018228225"},  // Русская 'щ' и назад в английскую раскладку
        {"-118", "048228225"},  // Русская 'ъ' и назад в английскую раскладку
        {"-117", "022228225"},  // Русская 'ы' и назад в английскую раскладку
        {"-116", "016228225"},  // Русская 'ь' и назад в английскую раскладку
        
        {"-115", "052228225"},  // Русская 'э' и назад в английскую раскладку
        {"-114", "055228225"},  // Русская 'ю' и назад в английскую раскладку
        {"-113", "029228225"},  // Русская 'я' и назад в английскую раскладку
        
        // Заглавные русские
        {"-112", "225009228225"},   // Русская 'А' и назад в английскую раскладку
        {"-111", "225054228225"},   // Русская 'Б' и назад в английскую раскладку
        {"-110", "225007228225"},   // Русская 'В' и назад в английскую раскладку
        {"-109", "225024228225"},   // Русская 'Г' и назад в английскую раскладку
        {"-108", "225015228225"},   // Русская 'Д' и назад в английскую раскладку
        {"-107", "225023228225"},   // Русская 'Е' и назад в английскую раскладку
        
        {"-106", "225051228225"},   // Русская 'Ж' и назад в английскую раскладку
        {"-105", "225019228225"},   // Русская 'З' и назад в английскую раскладку
        {"-104", "225005228225"},   // Русская 'И' и назад в английскую раскладку
        {"-103", "225020228225"},   // Русская 'Й' и назад в английскую раскладку
        {"-102", "225021228225"},   // Русская 'К' и назад в английскую раскладку
        {"-101", "225014228225"},   // Русская 'Л' и назад в английскую раскладку
        {"-100", "225025228225"},   // Русская 'М' и назад в английскую раскладку
        {"-99", "225028228225"},    // Русская 'Н' и назад в английскую раскладку
        
        {"-98", "225013228225"},   // Русская 'О' и назад в английскую раскладку
        {"-97", "225010228225"},   // Русская 'П' и назад в английскую раскладку
        {"-96", "225011228225"},   // Русская 'Р' и назад в английскую раскладку
        {"-95", "225006228225"},   // Русская 'С' и назад в английскую раскладку
        {"-94", "225017228225"},   // Русская 'Т' и назад в английскую раскладку
        
        {"-93", "225008228225"},  // Русская 'У' и назад в английскую раскладку
        {"-92", "225004228225"},  // Русская 'Ф' и назад в английскую раскладку
        {"-91", "225047228225"},  // Русская 'Х' и назад в английскую раскладку
        {"-90", "225026228225"},  // Русская 'Ц' и назад в английскую раскладку
        {"-89", "225027228225"},  // Русская 'Ч' и назад в английскую раскладку
        
        {"-88", "225012228225"},  // Русская 'Ш' и назад в английскую раскладку
        {"-87", "225018228225"},  // Русская 'Щ' и назад в английскую раскладку
        {"-86", "225048228225"},  // Русская 'Ъ' и назад в английскую раскладку
        {"-85", "225022228225"},  // Русская 'Ы' и назад в английскую раскладку
        {"-84", "225016228225"},  // Русская 'ь' и назад в английскую раскладку
        
        {"-83", "225052228225"},  // Русская 'Э' и назад в английскую раскладку
        {"-82", "225055228225"},  // Русская 'Ю' и назад в английскую раскладку
        {"-81", "225029228225"},  // Русская 'Я' и назад в английскую раскладку
        
        // Cимволы
        {"10", "040"},      // Enter
        {"9", "043"},       // Tab
        {"32", "044"},      // Пробел
        {"45", "045"},      // Минус
        {"61", "046"},      // Равно
        {"91", "047"},      // "["
        {"93", "048"},      // "]"
        {"92", "049"},      // Обратный слеш - '\\'
        {"44", "054"},      // Запятая
        {"46", "055"},      // Точка
        {"47", "056"},      // Слеш
        {"59", "051"},      // Точка с запятой
        {"39", "052"},      // Одинарная кавычка
        
        // Цифры
        {"49", "030"},
        {"50", "031"},
        {"51", "032"},
        {"52", "033"},
        {"53", "034"},
        {"54", "035"},
        {"55", "036"},
        {"56", "037"},
        {"57", "038"},
        {"48", "039"},
        
        // Символы с Шифтом
        {"33", "225030"},
        {"64", "225031"},
        {"35", "225032"},
        {"36", "225033"},
        {"37", "225034"},
        {"94", "225035"},
        {"38", "225036"},
        {"42", "225037"},
        {"40", "225038"},
        {"41", "225039"},
        {"95", "225045"},
        {"43", "225046"},
        {"123", "225047"},
        {"125", "225048"},
        {"58", "225051"},       // Двоеточие
        {"34", "225052"},       // Двойная кавычка - '\"'
        {"60", "225054"},       // Меньше
        {"62", "225055"},       // Больше
        {"63", "225056"},       // Знак вопроса
        {"124", "225049"},      // Пайп - '|'
        
        
        // Латинские прописные буквы
        {"97", "004"},
        {"98", "005"},
        {"99", "006"},
        {"100", "007"},
        {"101", "008"},
        {"102", "009"},
        {"103", "010"},
        {"104", "011"},
        {"105", "012"},
        {"106", "013"},
        {"107", "014"},
        {"108", "015"},
        {"109", "016"},
        {"110", "017"},
        {"111", "018"},
        {"112", "019"},
        {"113", "020"},
        {"114", "021"},
        {"115", "022"},
        {"116", "023"},
        {"117", "024"},
        {"118", "025"},
        {"119", "026"},
        {"120", "027"},
        {"121", "028"},
        {"122", "029"},
        
        // Латинские заглавные
        {"65", "225004"},
        {"66", "225005"},
        {"67", "225006"},
        {"68", "225007"},
        {"69", "225008"},
        {"70", "225009"},
        {"71", "225010"},
        
        {"72", "225011"},
        {"73", "225012"},
        {"74", "225013"},
        {"75", "225014"},
        {"76", "225015"},
        {"77", "225016"},
        {"78", "225017"},
        
        {"79", "225018"},
        {"80", "225019"},
        {"81", "225020"},
        {"82", "225021"},
        {"83", "225022"},
        {"84", "225023"},
        {"85", "225024"},
        
        {"86", "225025"},
        {"87", "225026"},
        {"88", "225027"},
        {"89", "225028"},
        {"90", "225029"}
    };
    
    for (long unsigned int i = 0; i < txtMessage.length(); i++) {
        
        // Перехват клавиш управления
//        controlKeysInterception();


        // Пошевелить мышкой через каждые "n" нажатий кнопок
        int n = 500;
        if (i % n == 0) {
            mouseMove(deviceId, deviceIpAddress, deviceUdpPort,  "00007");      // X=+7, Y=+7 пикселей
            usleep(10000 * getRandomDelay(minDelay, maxDelay));
            mouseMove(deviceId, deviceIpAddress, deviceUdpPort,  "65529");      // X=-7, Y=-7 пикселей
            cout << "Mouse! " << i << endl;
        }
        
        char symbol= txtMessage.at(i);
        // cout << int(x) << endl;       // Вывод в консоль для отладки
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
