/*  Project : MicroMote
 *  makerbrains.com 2023
 *  Author  : Mukesh Sankhla
 */

#include <esp_now.h>
#include <WiFi.h>

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
esp_err_t result;

void setup() {
  Serial.begin(115200);

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
}

void loop()
{
  //Your custom code
}