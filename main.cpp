#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <demos/lv_demos.h>
#include <WiFi.h>
#include <WiFiServer.h>

#define LED_PIN1 12
#define LED_PIN2 13

typedef struct Data{
  float cpu_load;
  float cpu_temp;
  float gpu_load;
  float gpu_temp;
} Data;

/*Change to your screen resolution*/
static const uint16_t screenWidth = 80;
static const uint16_t screenHeight = 160;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
// WiFiServer server(port);

const char* ssid="Zzzzzzzz";
const char* passwd="1111111111";
const int port = 34567;
bool wifi_conn=false;

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

void inline lvgl_init(){
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println(LVGL_Arduino);

  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
}

/* 初始化用户界面 */
void ui_show_setup(){


}

void change_led_timer(lv_timer_t* timer){
  lv_obj_t* led = (lv_obj_t*)(timer->user_data);
  Serial.printf("wifi_conn::%b\n",wifi_conn);
  if(wifi_conn){
    lv_led_on(led);
  }else{
    lv_led_toggle(led);
  }
}
void ui_network_setup(){
  Serial.println("init ui_network");
  lv_obj_t* txt = lv_label_create(lv_scr_act());
  lv_label_set_text(txt,"connecting wifi");
  lv_obj_align(txt,LV_ALIGN_CENTER,0,0);
  lv_obj_t* led = lv_led_create(lv_scr_act());
  lv_obj_align_to(led,txt,LV_ALIGN_BOTTOM_MID,0,0);
  // lv_timer_create(change_led_timer,300,led);
}


void connect_wifi(){
  ui_network_setup();
  Serial.println("start connect wifi");
  // WiFi.disconnect();
  delay(500);
  WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid,passwd);
  // for(int i=0;
  // .status()!=WL_CONNECTED;i++){
  //   Serial.print('.');
  //   delay(500);
  //   WiFi.begin(ssid,passwd);
  //   Serial.println(i)
  // }
  Serial.println(ssid, password);
  WiFi.begin(ssid, password); //连接网络
  Serial.println(WiFi.status());

  while (!WiFi.isConnected()) //等待网络连接成功
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");

  wifi_conn=true;
  Serial.println(WiFi.localIP);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //打印模块IP

  Serial.print("subnetMask: ");
  Serial.println(WiFi.subnetMask()); //打印子网掩码

  Serial.print("gateway: ");
  Serial.println(WiFi.gatewayIP()); //打印网关地址

  Serial.print("dns: ");
  Serial.println(WiFi.dnsIP()); //打印DNS地址

  Serial.print("mac Address: ");
  Serial.println(WiFi.macAddress()); //打印mac地址

  WiFi.setHostname("myHostName"); //设置主机名
  Serial.print("HostName: ");
  Serial.println(WiFi.getHostname()); //打印主机名

  Serial.println(WiFi.status());
  WiFi.disconnect(); //断开当前网络
  delay(1000);
  Serial.println(WiFi.status());

}
void setup()
{
  Serial.begin(115200); /* prepare for possible serial debug */
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  digitalWrite(LED_PIN1, HIGH);
  digitalWrite(LED_PIN2, HIGH);



  lvgl_init();
  tft.init();        /* TFT init */
  tft.setRotation(1); /* Landscape orientation, flipped */
  tft.fillScreen(TFT_BLACK);
  Serial.println("init tft success");
  /*-------------------------- main code----------------- */
  // connect_wifi();
  ui_network_setup();
  Serial.println("start connect wifi 1");
  // WiFi.disconnect();
  delay(500);
  WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid,passwd);
  // for(int i=0;
  // .status()!=WL_CONNECTED;i++){
  //   Serial.print('.');
  //   delay(500);
  //   WiFi.begin(ssid,passwd);
  //   Serial.println(i)
  // }
  Serial.println(ssid, password);
  WiFi.begin(ssid, password); //连接网络
  Serial.println(WiFi.status());

  while (!WiFi.isConnected()) //等待网络连接成功
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");

  wifi_conn=true;
  Serial.println(WiFi.localIP);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //打印模块IP

  Serial.print("subnetMask: ");
  Serial.println(WiFi.subnetMask()); //打印子网掩码

  Serial.print("gateway: ");
  Serial.println(WiFi.gatewayIP()); //打印网关地址

  Serial.print("dns: ");
  Serial.println(WiFi.dnsIP()); //打印DNS地址

  Serial.print("mac Address: ");
  Serial.println(WiFi.macAddress()); //打印mac地址

  WiFi.setHostname("myHostName"); //设置主机名
  Serial.print("HostName: ");
  Serial.println(WiFi.getHostname()); //打印主机名

  Serial.println(WiFi.status());
  WiFi.disconnect(); //断开当前网络
  delay(1000);
  Serial.println(WiFi.status());

  ui_show_setup();

  Serial.println("Setup done");
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
