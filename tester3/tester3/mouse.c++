using namespace std;

#include <iostream>
#include <unistd.h>


int getRandomDelay(int minDelaym, int maxDelay);
void mouseBigMove(int currentSymbolNumber, int workSymbolNumber, string plusMoveSize, string minusMoveSize,
                  string deviceId, string deviceIpAddress, int deviceUdpPort, int minDelay, int maxDelay);
void mouseMove(string deviceId, string deviceIpAddress, int deviceUdpPort, string offset);
void sendUdpPacket(string deviceId, string deviceIpAddress, int deviceUdpPort, 
                   string b1, string b2, string b3, string b4);


// Пошевелить мышкой через каждые "symbolNumber" нажатий кнопок.
// plusMoveSize - размер перемешения в плюс по X и Y
// minusMoveSize - размер перемешения в минус по X и Y
void mouseBigMove(int currentSymbolNumber, int workSymbolNumber, string plusMoveSize, string minusMoveSize, 
                  string deviceId, string deviceIpAddress, int deviceUdpPort, int minDelay, int maxDelay) {
    if (currentSymbolNumber % workSymbolNumber == 0) {
        mouseMove(deviceId, deviceIpAddress, deviceUdpPort, plusMoveSize);
        usleep(10000 * getRandomDelay(minDelay, maxDelay));
        mouseMove(deviceId, deviceIpAddress, deviceUdpPort, minusMoveSize);
        cout << "Mouse" << endl;
    }
        
}


// Переместить курсор мыши на X=offset, Y=offset
void mouseMove(string deviceId, string deviceIpAddress, int deviceUdpPort, string offset) {
    sendUdpPacket(deviceId, deviceIpAddress, deviceUdpPort, "4", "000", offset, offset);
}
