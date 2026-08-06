/*
=========================================
 Pocket Remote v1
 Module 01
 Config
=========================================
*/

#include <Wire.h>
#include <Preferences.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>



// ---------- OLED ----------

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
SCREEN_WIDTH,
SCREEN_HEIGHT,
&Wire,
-1
);



// ---------- GPIO ----------

#define OLED_SDA 21
#define OLED_SCL 22

#define IR_SEND_PIN 25
#define IR_RECV_PIN 26

#define JOY_X 34
#define JOY_Y 35
#define JOY_SW 32

#define BATTERY_PIN 33



// ---------- EEPROM ----------

Preferences prefs;



// ---------- IR ----------

IRrecv irrecv(IR_RECV_PIN);

decode_results results;

IRsend irsend(IR_SEND_PIN);



// ---------- LIMITLER ----------

#define MAX_KEYS 20

#define NAME_LENGTH 8

#define RAW_BUFFER 300
/*
=========================================
 Pocket Remote v1
 Module 02
 Data
=========================================
*/

struct RemoteButton
{

char name[NAME_LENGTH+1];

bool used;

decode_type_t protocol;

uint16_t bits;

uint16_t rawLength;

uint16_t rawData[RAW_BUFFER];

};

RemoteButton buttons[MAX_KEYS];



// ---------- MENÜ ----------

String menuItems[] =
{
    "Yeni Tus",
    "Tuslar",
    "Pil",
    "Ayarlar"
};

const byte menuCount = 4;

byte menuCursor=0;



// ---------- EKRAN ----------

enum Screen
{

HOME,

NAME_EDITOR,

LEARN_IR,

SETTINGS,

BUTTON_LIST,

SEND_IR,

BATTERY,

DELETE_BUTTON

};

Screen currentScreen=HOME;
// ---------- SETTINGS ----------

bool soundEnabled = true;
bool dimMode = false;
byte settingsCursor = 0;



// ---------- JOYSTICK ----------

int joyX=0;

int joyY=0;



// ---------- BATARYA ----------

int batteryPercent=0;
String firmwareVersion = "v1.0";


// ---------- İSİM ----------

char alphabet[]=
"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-";

char tempName[NAME_LENGTH+1];

byte tempPos=0;

byte alphaPos=0;
// ---------- Function Prototypes ----------
int getButtonCount();
int getButtonIndex(byte visibleIndex);
void drawButtonList();
void drawSettings();
void settingsLoop();
void buttonListLoop();
void applyDisplaySettings();
void loadSettings();
void saveSettings();
void drawHome(); 
void homeLoop();
void drawBattery();
void batteryLoop();
void startDelete(byte id);
void drawDeleteScreen();
void deleteLoop();

byte createButtonSlot();
void displayInit();
void splashScreen();
void drawHeader(const char *title);

bool joyClick();
void updateJoystick();
bool joyUp();
bool joyDown();
bool joyLeft();
bool joyRight();


void saveButton(byte id);
void loadButtons();
void deleteButton(byte id);

void startLearning(byte id);
void drawLearnScreen();
void learnIRLoop();

void startSend(byte id);
void drawSendScreen();
void sendIRLoop();
/*
=========================================
 Pocket Remote v1
 Module 03
 Display
=========================================
*/

void displayInit()
{

  Wire.begin(OLED_SDA, OLED_SCL);

  display.begin(
    SSD1306_SWITCHCAPVCC,
    0x3C
  );

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);

}

void splashScreen()
{
  display.clearDisplay();

  display.setCursor(18,20);
  display.println("Pocket");

  display.setCursor(18,32);
  display.println("Remote");

  display.setCursor(72,54);
  display.print("OK");

  display.setCursor(100,54);
  display.print("DEL");

  display.display();

  delay(1200);
}

void drawHeader(const char *title)
{

  display.clearDisplay();

  display.setCursor(0,0);

  display.print(title);

  display.setCursor(98,0);

  display.print(batteryPercent);

  display.print("%");

}
void bootAnimation()
{
    display.clearDisplay();

    for(int x=-80;x<18;x+=4)
    {
        display.clearDisplay();

        display.setTextSize(2);
        display.setCursor(x,18);
        display.print("Pocket");

        display.setCursor(x,40);
        display.print("Remote");

        display.display();

        delay(15);
    }

    delay(500);

    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0,8);
    display.print("Pocket Remote");

    display.setCursor(0,24);
    display.print("Firmware:");
    display.print(firmwareVersion);

    display.setCursor(0,40);
    display.print("ESP32 Ready");

    display.display();

    delay(1200);
}
/*
=========================================
 Pocket Remote v1
 Module 04
 Joystick
=========================================
*/

bool joyClick()
{

  static unsigned long last=0;

  if(
    digitalRead(JOY_SW)==LOW &&
    millis()-last>220
  )
  {

    last=millis();

    return true;

  }

  return false;

}



void updateJoystick()
{

  joyX=analogRead(JOY_X);

  joyY=analogRead(JOY_Y);

}



bool joyUp()
{

  return joyY<900;

}



bool joyDown()
{

  return joyY>3200;

}



bool joyLeft()
{

  return joyX<900;

}



bool joyRight()
{

  return joyX>3200;

}
/*
=========================================
 Pocket Remote v1
 Module 05
 Main Menu
=========================================
*/

void drawHome()
{
    drawHeader("Pocket Remote");

    display.setCursor(78,54);
    display.print(getButtonCount());

    display.print("/20");

    for(byte i=0;i<menuCount;i++)
    {
        display.setCursor(0,16+i*14);

        if(i==menuCursor)
            display.print("> ");
        else
            display.print("  ");

        display.println(menuItems[i]);
    }

    display.display();
}

void homeLoop()
{
    if(joyUp())
    {
        if(menuCursor>0)
            menuCursor--;

        delay(180);
    }

    if(joyDown())
    {
        if(menuCursor<menuCount-1)
            menuCursor++;

        delay(180);
    }

    if(joyClick())
    {
        switch(menuCursor)
        {
            case 0:
                currentScreen=NAME_EDITOR;
                break;

            case 1:
                currentScreen=BUTTON_LIST;
                break;

            case 2:
                currentScreen=BATTERY;
                break;
            case 3:
                currentScreen = SETTINGS;
                break;
        }
    }
}
/*
=========================================
 Pocket Remote v1
 Module 06
 Name Editor
=========================================
*/

void clearTempName()
{
    memset(tempName,0,sizeof(tempName));

    tempPos=0;
    alphaPos=0;
}

void drawNameEditor()
{
    drawHeader("Yeni Tus");

    display.setCursor(0,16);
    display.print("Isim:");

    display.setCursor(42,16);
    display.print(tempName);

    display.setCursor(0,34);
    display.print("Harf:");

    display.setCursor(42,34);
    display.print(alphabet[alphaPos]);

    display.setCursor(0,54);
    display.print("OK=Sec");

    display.display();
}

void nameEditorLoop()
{

    if(joyLeft())
    {
        if(alphaPos>0)
            alphaPos--;

        delay(120);
    }

    if(joyRight())
    {
        if(alphaPos<strlen(alphabet)-1)
            alphaPos++;

        delay(120);
    }

    if(joyClick())
    {

        tempName[tempPos]=alphabet[alphaPos];

        if(tempPos<NAME_LENGTH-1)
        {
            tempPos++;
        }
        else
        {
            tempName[NAME_LENGTH]='\0';

        byte id = createButtonSlot();

        if(id != 255)
{
    startLearning(id);
}

            currentScreen=LEARN_IR;
        }

        delay(150);
    }

}
/*
=========================================
 Pocket Remote v1
 Module 07
 Preferences
=========================================
*/




void saveButton(byte id)
{

  String base="BTN"+String(id);



  prefs.putBool(
    (base+"U").c_str(),
    buttons[id].used
  );



  prefs.putString(
    (base+"N").c_str(),
    buttons[id].name
  );



  prefs.putUInt(
    (base+"L").c_str(),
    buttons[id].rawLength
  );



  prefs.putUInt(
    (base+"B").c_str(),
    buttons[id].bits
  );



  prefs.putUInt(
    (base+"P").c_str(),
    (uint32_t)buttons[id].protocol
  );



  for(int i=0;i<buttons[id].rawLength;i++)
  {

    prefs.putUInt(
      (base+"R"+String(i)).c_str(),
      buttons[id].rawData[i]
    );

  }

}




void loadButtons()
{

  for(int i=0;i<MAX_KEYS;i++)
  {

    String base="BTN"+String(i);

    buttons[i].used=
    prefs.getBool(
      (base+"U").c_str(),
      false
    );



    if(!buttons[i].used)
      continue;



    String name=
    prefs.getString(
      (base+"N").c_str(),
      ""
    );



    name.toCharArray(
      buttons[i].name,
      NAME_LENGTH+1
    );



    buttons[i].rawLength=
    prefs.getUInt(
      (base+"L").c_str(),
      0
    );



    buttons[i].bits=
    prefs.getUInt(
      (base+"B").c_str(),
      0
    );



    buttons[i].protocol=
    (decode_type_t)prefs.getUInt(
      (base+"P").c_str(),
      0
    );



    for(int j=0;j<buttons[i].rawLength;j++)
    {

      buttons[i].rawData[j]=
      prefs.getUInt(
        (base+"R"+String(j)).c_str(),
        0
      );

    }

  }

}




void deleteButton(byte id)
{

  if(id>=MAX_KEYS)
    return;



  buttons[id].used=false;

  buttons[id].rawLength=0;

  buttons[id].bits=0;

  buttons[id].protocol=UNKNOWN;

  memset(
    buttons[id].name,
    0,
    sizeof(buttons[id].name)
  );



  saveButton(id);

}

/*
=========================================
 Pocket Remote v1
 Module 12
 Create Button Fix
=========================================
*/

byte lastCreatedButton = 255;



byte createButtonSlot()
{
    for(byte i=0;i<MAX_KEYS;i++)
    {
        if(!buttons[i].used)
        {
            buttons[i].used = true;

            strcpy(
                buttons[i].name,
                tempName
            );

            buttons[i].rawLength = 0;
            buttons[i].bits = 0;
            buttons[i].protocol = UNKNOWN;

            saveButton(i);

            lastCreatedButton = i;

            return i;
        }
    }

display.clearDisplay();

display.setCursor(12,28);
display.println("Hafiza Dolu");

display.display();

delay(1200);

return 255;
}
/*
=========================================
 Pocket Remote v1
 Module 08
 IR Learn
=========================================
*/

byte learnIndex = 0;



void startLearning(byte id)
{

  learnIndex = id;

  currentScreen = LEARN_IR;

}



void drawLearnScreen()
{

  drawHeader("IR Ogren");

  display.setCursor(0,20);
  display.println("Kumandayi");

  display.setCursor(0,32);
  display.println("Cihaza Tut");

  display.setCursor(0,44);
  display.println("Tus Bas...");

  display.display();

}



void learnIRLoop()
{

  drawLearnScreen();



  if(irrecv.decode(&results))
  {

    if(learnIndex>=MAX_KEYS)
    {

      irrecv.resume();

      return;

    }



    buttons[learnIndex].protocol =
    results.decode_type;

    buttons[learnIndex].bits =
    results.bits;



    buttons[learnIndex].rawLength =
    results.rawlen;

    if(results.rawlen < 6)
{
    irrecv.resume();

    display.clearDisplay();

    display.setCursor(10,28);
    display.println("Gecersiz IR");

    display.display();

    delay(800);

    return;
}



    if(buttons[learnIndex].rawLength>
       RAW_BUFFER)
    {

      buttons[learnIndex].rawLength=
      RAW_BUFFER;

    }



    for(int i=0;
        i<buttons[learnIndex].rawLength;
        i++)
    {

      buttons[learnIndex].rawData[i]=
      results.rawbuf[i];

    }



    saveButton(learnIndex);



    display.clearDisplay();

    display.setCursor(10,28);

    display.println("Kaydedildi!");

    display.display();

    delay(1000);



    irrecv.resume();



    currentScreen=HOME;

  }

}
/*
=========================================
 Pocket Remote v1
 Module 09
 IR Send
=========================================
*/

byte sendIndex = 0;



void startSend(byte id)
{

  sendIndex=id;

  currentScreen=SEND_IR;

}




void drawSendScreen()
{

  drawHeader("IR Gonder");



  display.setCursor(0,20);

  display.print("Tus:");



  display.println(
    buttons[sendIndex].name
  );



  display.setCursor(0,38);

  display.println("Gonderiliyor...");



  display.display();

}




void sendIRLoop()
{

  drawSendScreen();



  if(sendIndex>=MAX_KEYS)
  {

    currentScreen=HOME;

    return;

  }



  if(!buttons[sendIndex].used)
  {

    currentScreen=HOME;

    return;

  }



  if(buttons[sendIndex].rawLength>0)
  {

    uint16_t rawBuffer[RAW_BUFFER];



    for(int i=0;
        i<buttons[sendIndex].rawLength;
        i++)
    {

      rawBuffer[i]=
      buttons[sendIndex].rawData[i];

    }



    irsend.sendRaw(

      rawBuffer,

      buttons[sendIndex].rawLength,

      38

    );



  }



  display.clearDisplay();

  display.setCursor(12,28);

  display.println("Gonderildi");

  display.display();

  delay(500);



  currentScreen=HOME;

}
//=========================================
// SETUP
//=========================================

void setup()
{
    Serial.begin(115200);

    pinMode(JOY_SW, INPUT_PULLUP);

    displayInit();

    applyDisplaySettings();

    bootAnimation();

    prefs.begin("Pocket", false);

    loadSettings();

    irrecv.enableIRIn();

    irsend.begin();

    loadButtons();
}


//=========================================
// LOOP
//=========================================

void loop()
{
    updateJoystick();

    switch(currentScreen)
    {
        case HOME:
            drawHome();
            homeLoop();
            break;
        case SETTINGS:
            drawSettings();
            settingsLoop();
            break;
        case BUTTON_LIST:
            drawButtonList();
            buttonListLoop();
            break;
        case DELETE_BUTTON:
            drawDeleteScreen();
            deleteLoop();
            break;
        case NAME_EDITOR:
            drawNameEditor();
            nameEditorLoop();
            break;

        case LEARN_IR:
            learnIRLoop();
            break;

        case SEND_IR:
            sendIRLoop();
            break;
        case BATTERY:
            drawBattery();
            batteryLoop();
            break;

        default:
            currentScreen = HOME;
            break;
    }
}

/*
=========================================
 Pocket Remote v1
 Module 10
 Button List
=========================================
*/

byte listCursor = 0;
byte listOffset = 0;

int getButtonCount()
{
    int count = 0;

    for(int i=0;i<MAX_KEYS;i++)
    {
        if(buttons[i].used)
            count++;
    }

    return count;
}



int getButtonIndex(byte visibleIndex)
{
    byte count = 0;

    for(int i=0;i<MAX_KEYS;i++)
    {
        if(buttons[i].used)
        {
            if(count==visibleIndex)
                return i;

            count++;
        }
    }

    return -1;
}
void drawButtonList()
{
    drawHeader("Tuslar");

    byte line = 0;

    for(byte i=listOffset;
        i<getButtonCount() && line<4;
        i++)
    {
        int index = getButtonIndex(i);

        if(index==-1)
            continue;

        display.setCursor(0,16+line*12);

        if(i==listCursor)
            display.print("> ");
        else
            display.print("  ");

        display.println(buttons[index].name);

        line++;
    }

    display.setCursor(72,54);
    display.print("OK");

    display.setCursor(100,54);
    display.print("DEL");

    display.display();
}
void buttonListLoop()
{
    if(joyUp())
    {
        if(listCursor>0)
            listCursor--;

        delay(180);
    }

    if(joyDown())
    {
        if(listCursor<getButtonCount()-1)
            listCursor++;

        delay(180);
    }

    // Scroll
    if(listCursor < listOffset)
        listOffset = listCursor;

    if(listCursor >= listOffset + 4)
        listOffset = listCursor - 3;

    // OK → Gönder
    if(joyClick())
    {
        int realIndex = getButtonIndex(listCursor);

        if(realIndex != -1)
            startSend(realIndex);

        delay(200);
    }

    // Sağ → Sil
    if(joyRight())
    {
        int realIndex = getButtonIndex(listCursor);

        if(realIndex != -1)
            startDelete(realIndex);

        delay(200);
    }

    // Sol → Ana Menü
    if(joyLeft())
    {
        currentScreen = HOME;
        delay(200);
    }
}
/*
=========================================
 Pocket Remote v1
 Module 13
 Battery
=========================================
*/

float batteryVoltage = 0.0;

void updateBattery()
{
    int adc = analogRead(BATTERY_PIN);

    // 100k + 100k voltaj bölücü
    batteryVoltage =
        (adc * 3.3 / 4095.0) * 2.0;

    batteryPercent = map(
        (int)(batteryVoltage * 100),
        330,
        420,
        0,
        100
    );

    if(batteryPercent < 0)
        batteryPercent = 0;

    if(batteryPercent > 100)
        batteryPercent = 100;
}

void drawBattery()
{
    drawHeader("Pil");

    display.setTextSize(2);

    display.setCursor(18,20);
    display.print(batteryPercent);
    display.print("%");
    
    display.setTextSize(1);

    display.setCursor(0,50);
    display.print(batteryVoltage,2);
    display.print("V");

    display.setCursor(70,50);
    display.print("OK:Geri");

    display.display();
}

void batteryLoop()
{
    updateBattery();

    if(joyClick())
    {
        currentScreen = HOME;
        delay(200);
    }
}
/*
=========================================
 Pocket Remote v1
 Module 14
 Delete Button
=========================================
*/

byte deleteIndex = 0;

void startDelete(byte id)
{
    deleteIndex = id;
    currentScreen = DELETE_BUTTON;
}

void drawDeleteScreen()
{
    drawHeader("Tus Sil");

    display.setCursor(0,18);
    display.println(buttons[deleteIndex].name);

    display.setCursor(0,36);
    display.println("OK = Sil");

    display.setCursor(0,50);
    display.println("Sag = Iptal");

    display.display();
}

void deleteLoop()
{
    if(joyClick())
    {
        deleteButton(deleteIndex);

        display.clearDisplay();
        display.setCursor(15,28);
        display.println("Silindi");
        display.display();

        delay(700);

        currentScreen = HOME;
        return;
    }

    if(joyRight())
    {
        currentScreen = BUTTON_LIST;
        delay(200);
    }
}
/*
=========================================
 Pocket Remote v1
 Module 15
 Settings
=========================================
*/

String settingsItems[] =
{
    "Ses",
    "Dim Mode",
    "Geri"
};

const byte settingsCount = 3;

void drawSettings()
{
    drawHeader("Ayarlar");

    for(byte i=0;i<settingsCount;i++)
    {
        display.setCursor(0,16+i*14);

        if(i==settingsCursor)
            display.print("> ");
        else
            display.print("  ");

        display.print(settingsItems[i]);

        if(i==0)
        {
            display.setCursor(92,16+i*14);
            display.print(soundEnabled ? "ON" : "OFF");
        }

        if(i==1)
        {
            display.setCursor(92,16+i*14);
            display.print(dimMode ? "ON" : "OFF");
        }
    }

    display.display();
}

void settingsLoop()
{
    if(joyUp())
    {
        if(settingsCursor>0)
            settingsCursor--;

        delay(180);
    }

    if(joyDown())
    {
        if(settingsCursor<settingsCount-1)
            settingsCursor++;

        delay(180);
    }

    if(joyClick())
    {
        switch(settingsCursor)
        {
            case 0:
                soundEnabled = !soundEnabled;
                break;
            saveSettings();

            case 1:
                dimMode = !dimMode;
                break;
            applyDisplaySettings();

            saveSettings();

            case 2:
                currentScreen = HOME;
                break;
        }

        delay(200);
    }
}
/*
=========================================
 Pocket Remote v1
 Module 16
 Settings Save
=========================================
*/

void loadSettings()
{
    soundEnabled =
        prefs.getBool("sound", true);

    dimMode =
        prefs.getBool("dim", false);
}

void saveSettings()
{
    prefs.putBool(
        "sound",
        soundEnabled
    );

    prefs.putBool(
        "dim",
        dimMode
    );
}
/*
=========================================
 Pocket Remote v1
 Module 17
 Display Settings
=========================================
*/

void applyDisplaySettings()
{
    if(dimMode)
        display.dim(true);
    else
        display.dim(false);
}