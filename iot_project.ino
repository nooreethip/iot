
#include <TridentTD_LineNotify.h>
const char* ssid     = "All_for_one";
const char* password = "ggwp1234";
#define LINE_TOKEN  "VuiImBaCROKIRpTNFai7fHNo7O75knBa2o3vX0PWj26"
int Smoke_MQ2 = A0; //ประกาศตัวแปร MQ2 ให้ analogPin
int Smoke_MQ2Value = 0;
int Smoke_MQ2outputValue = 0; // ตัวแปรสำหรับ Map เพื่อคิด %
int buzzer = D8;

void setup()
{
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  Serial.println(LINE.getVersion());
  WiFi.begin(ssid, password);
  Serial.println("Connecting... ");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting... ");
    delay(250);
    Serial.print(".");
    Serial.printf("Connection Status: %d\n", WiFi.status());
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
}

void loop()
{

  int Smoke_MQ2Value = analogRead (Smoke_MQ2);
  int Smoke_MQ2outputValue = map(Smoke_MQ2Value, 0, 1023, 0, 100); //แปลงค่าจาก
  Serial.print("ค่าตรวจจับแก๊ส:     ");
  Serial.println(Smoke_MQ2outputValue);
  Serial.println(" %");
  if (Smoke_MQ2outputValue >= 40) { //ตั้งค่า % ที่ต้องการให้แจ้งเตือน 0-100
    LINE.notify("แจ้งเตือน : มีการสูบบุหรี่ !!"); // ส่งข้อความไปยัง Line "แจ้งเตือน : ตรวจพบควันเกินค่ากำหนด"
    digitalWrite(buzzer, LOW);   //เปิดเสียงเตือน
  }
  else {
    digitalWrite(buzzer, HIGH); //ปิดเสียงเตือน
  }
  delay(500);
}
