using namespace std;

#include <iostream>
#include <unistd.h>

void keyPress3(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay);
void keyPress6(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay);
void keyPress9(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay); 
void keyPress12(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay);               
int getRandomDelay(int minDelaym, int maxDelay);  
void sendUdpPacket(string deviceId, string deviceIpAddress, int deviceUdpPort, 
                   string b1, string b2, string b3, string b4);             


// Нажатие клавиши с 3-х значным кодом
void keyPress3(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay) {
    
    // Случайная задержка
    usleep(1000 * getRandomDelay(minDelay, maxDelay));
            
    // Нажать 
    sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode, "00000", "00000");
    usleep(releaseDelay * 1000);
    
    // Отпустить
    sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode, "00000", "00000");
    usleep(releaseDelay * 1000);
}


// Нажатие клавиши с 6-ти значным кодом
void keyPress6(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay) {
                   
    // Случайная задержка                    
    usleep(1000 * getRandomDelay(minDelay, maxDelay));
            
    // Нажать Shift или Ctrl
    sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(0, 3), "00000", "00000");
    usleep(releaseDelay * 1000);
    
    // Нажать клавишу
    sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "1", symbolCode.substr(3, 3), "00000", "00000");
    usleep(releaseDelay * 1000);
    
    if(!(symbolCode == "228225")) {
        
        // Отпустить клавишу
        sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(3, 3), "00000", "00000");
        usleep(releaseDelay * 1000);
    
        // Отпустить Shift или Ctrl
        sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(0, 3), "00000", "00000");
        usleep(releaseDelay * 1000);
        
    } else {    // Переключить раскладку на RUS - "228225"
        
        // Отпустить Shift или Ctrl
        sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(0, 3), "00000", "00000");
        usleep(releaseDelay * 1000);
        
        // Отпустить клавишу
        sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "2", symbolCode.substr(3, 3), "00000", "00000");
        usleep(releaseDelay * 1000);
        
    }
                  
}


// Нажатие клавиши с 9-ти значным кодом
void keyPress9(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay) {

    // Случайная задержка
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
                   
}


// Нажатие клавиши с 12-ти значным кодом
void keyPress12(string deviceId, string deviceIpAddress, int deviceUdpPort, 
               string symbolCode, int minDelay, int maxDelay, int releaseDelay) {

    // Случайная задержка
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
