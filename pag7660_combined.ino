#include <WiFi.h>
#include "Gesture.h"
#include <esp_now.h>

pag7660 Gesture; // Combined mode is used by default

int deviceNo = 1;    

//Universal Mac Address
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//Message(Data) send and receive doc
typedef struct messageData
{
  int color = 0;
} messageData;

messageData deviceData;     //Local Data
messageData recData;        //Received Data

// Create peer interface
esp_now_peer_info_t peerInfo;

//Called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

//Called when data is recived
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&recData, incomingData, sizeof(recData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.println(recData.color);
}

//Declare the send result
esp_err_t resultt;

void setup() {
    Serial.begin(9600);
    while(!Serial) {
        delay(100);
    }
    Serial.println("\nPAG7660 TEST DEMO: Gesture combined mode.");
    
    if(Gesture.init()) {
        Serial.println("PAG7660 initialization success");
    } else {
        Serial.println("PAG7660 initialization failed");
    }
    Serial.println("Please input your gestures:\n");

    WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  recData.color = deviceNo;
}

void loop() {
    pag7660_gesture_t result;
    if (Gesture.getResult(result)) {
        printResultCombinedMode(result);
    }
    delay(100);
}

void printResultCombinedMode(const pag7660_gesture_t& result) {
    const char *cursor_str[] = {
        NULL,
        "Tap",
        "Grab",
        "Pinch",
    };
    switch (result.type) {
    case 0:
        switch (result.cursor.type) {
        case 1:
        case 2:
        case 3:
            if (result.cursor.select)
                Serial.println(cursor_str[result.cursor.type]);
            break;
        default:
            break;
        }
        break;
    case 1:
        deviceData.color = recData.color = 1;
        resultt = esp_now_send(broadcastAddress, (uint8_t *) &deviceData, sizeof(deviceData));
        delay(2000);
        break;
    case 2:
        deviceData.color = recData.color = 2;
        resultt = esp_now_send(broadcastAddress, (uint8_t *) &deviceData, sizeof(deviceData));
        delay(2000);
        break;
    case 3:
        deviceData.color = recData.color = 3;
        resultt = esp_now_send(broadcastAddress, (uint8_t *) &deviceData, sizeof(deviceData));
        delay(2000);
        break;
    case 4:
        deviceData.color = recData.color = 4;
        resultt = esp_now_send(broadcastAddress, (uint8_t *) &deviceData, sizeof(deviceData));
        delay(2000);
        break;
    case 5:
        deviceData.color = recData.color = 5;
        resultt = esp_now_send(broadcastAddress, (uint8_t *) &deviceData, sizeof(deviceData));
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 19:
        deviceData.color = recData.color = 6;
        resultt = esp_now_send(broadcastAddress, (uint8_t *) &deviceData, sizeof(deviceData));
        delay(2000);
        break;
    case 20:
        deviceData.color = recData.color = 7;
        resultt = esp_now_send(broadcastAddress, (uint8_t *) &deviceData, sizeof(deviceData));
        delay(2000);
        break;
    case 21:
        deviceData.color = recData.color = 8;
        resultt = esp_now_send(broadcastAddress, (uint8_t *) &deviceData, sizeof(deviceData));
        delay(2000);
        break;
    case 22:
        deviceData.color = recData.color = 9;
        resultt = esp_now_send(broadcastAddress, (uint8_t *) &deviceData, sizeof(deviceData));
        delay(2000);
        break;
    case 23:
        deviceData.color = recData.color = 10;
        resultt = esp_now_send(broadcastAddress, (uint8_t *) &deviceData, sizeof(deviceData));
        delay(2000);
        break;
    default:
        break;
    }
}