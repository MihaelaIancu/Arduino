#include <LedControl.h>
#include <LiquidCrystal.h>

#define V0_PIN 9
#define BUTTON_PIN 8

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int DIN_PIN = 12; //dataPin -> data gets shifted out
const int CS_PIN = 10; //select the device when data is to be sent
const int CLK_PIN = 11;// clock

const int joyX = A2;
const int joyY = A3;

int prevX1 = 0, prevY1 = 0, posX1 = 0, posY1 = 0;
unsigned long ultimulUpdate = 0;

int lastbuttonState = 0;
int buttonState = 0;
int buttonPushCounter = 0;
int ok = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

LedControl disp = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

const byte IMAGES[][8] = {
  {
    B01000000,
    B00000000,
    B00000000,
    B00000010,
    B00000000,
    B00100000,
    B00000000,
    B00000000
  }, {
    B00000000,
    B00000000,
    B00000010,
    B00000000,
    B00100000,
    B00000000,
    B00000000,
    B00000010
  }, {
    B00000000,
    B00000010,
    B00000000,
    B00100000,
    B00000000,
    B00000000,
    B00000010,
    B00000000
  }, {
    B00000010,
    B00000000,
    B00100000,
    B00000000,
    B00000000,
    B00000010,
    B00000000,
    B00000000
  }, {
    B00000000,
    B00100000,
    B00000000,
    B00000010,
    B00000000,
    B00000000,
    B00000000,
    B01000000
  }, {
    B00100000,
    B00000000,
    B00000000,
    B00000010,
    B00000000,
    B00000000,
    B01000000,
    B00000000
  }, {
    B00000000,
    B00000000,
    B00000010,
    B00000000,
    B00000000,
    B01000000,
    B00000000,
    B00000000
  }, {
    B00000000,
    B00000010,
    B00000000,
    B00000000,
    B01000000,
    B00000000,
    B00000000,
    B00000000
  }, {
    B00000010,
    B00000000,
    B00000000,
    B01000000,
    B00000000,
    B00000000,
    B00000000,
    B00000010
  }
};

const int IMAGES_LEN = sizeof(IMAGES) / 8;

void animatie(const byte* image)
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      disp.setLed(0, j, i, bitRead(image[i], 7 - j));
    }
  }
}

void pause() {

  bool matrix[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 1, 0},
    {0, 1, 1, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0}
  };

  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      disp.setLed(0, col, row, matrix[row][col]);
      // delay(25);
    }
  }

}

void buton()
{
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastbuttonState) {
    lastDebounceTime = millis();
    if (buttonState == LOW) {
      buttonPushCounter++;
      Serial.println("on");
      Serial.println("number of button pushes: ");
      Serial.println(buttonPushCounter);
    }
    else {
      Serial.println("off");
      delay(50);
      lastbuttonState = buttonState;
      if (buttonPushCounter >= 6) {
        buttonPushCounter = 0;
        //        //ok = LOW;
        //      } else {
        //        //ok = HIGH;
      }
    }
  }

  //    buttonState = digitalRead(BUTTON_PIN);
  //  Serial.println(buttonState);
  //  if (buttonState == 0) {
  if (buttonPushCounter == 0) {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("RACING");
    lcd.setCursor(6, 1);
    lcd.print("GAME");
  }
  else if (buttonPushCounter == 2)
  {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SA INCEAPA");
    lcd.setCursor(6, 1);
    lcd.print("JOCUL");
  }
  else if (buttonPushCounter == 1)
  {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("MISCA MASINA ");
    lcd.setCursor(0, 1);
    lcd.print("CU JOYSTICK-UL");
    //    for(int positionCounter = 0; positionCounter < 50; positionCounter++)
    //    {
    //      lcd.scrollDisplayLeft();
    //       delay(75);
    //    }
  }
  else if (buttonPushCounter == 3)
  {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SPEED UP");
    lcd.setCursor(3, 1);
    lcd.print("1");
  }
  else if (buttonPushCounter == 4)
  {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SPEED UP");
    lcd.setCursor(3, 1);
    lcd.print("2");
  }
  else if (buttonPushCounter == 5)
  {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SPEED UP");
    lcd.setCursor(3, 1);
    lcd.print("3");
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState != lastbuttonState) {
      lastbuttonState = buttonState;

      if (lastbuttonState == HIGH) {
        ok = !ok;
      }
    }
  }

  //lcd.println(ok);
  lastbuttonState = buttonState;
}

void setup() {
  // put your setup code here, to run once:
  disp.shutdown(0, false);
  disp.setIntensity(0, 5);
  disp.clearDisplay(0);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(V0_PIN, OUTPUT);
  analogWrite(V0_PIN, 90);


}

int i = 0;

void loop() {
  // put your main code here, to run repeatedly:
  //
  int intervalRecalculare = 60;
  int valX, valY;


  buton();

  //  if(buttonPushCounter==0){
  //    if ((millis() - ultimulUpdate) >= intervalRecalculare)
  //    {
  //
  //      ultimulUpdate = millis();
  //
  //      valX = analogRead(joyX);
  //      valY = analogRead(joyY);
  //
  //      prevX1 = posX1;
  //      prevY1 = posY1;
  //
  //      if (valX < 340)
  //      {
  //        if (posX1 < 6)
  //        {
  //          posX1++;
  //        }
  //      }
  //      else if (valX > 680)
  //      {
  //        if (posX1 > 0)
  //        {
  //          posX1--;
  //        }
  //      }
  //
  //      if (valY < 340)
  //      {
  //        if (posY1 < 6)
  //        {
  //          posY1++;
  //        }
  //      }
  //      else if (valY > 680)
  //      {
  //        if (posY1 > 0)
  //        {
  //          posY1--;
  //        }
  //      }
  //
  //      if (prevX1 != posX1 || prevY1 != posY1)
  //      {
  //        disp.setLed(0, prevY1, prevX1, 0);
  //        disp.setLed(0, prevY1 + 1, prevX1, 0);
  //        disp.setLed(0, prevY1, prevX1 + 1, 0);
  //        disp.setLed(0, prevY1 + 1, prevX1 + 1, 0);
  //      }
  //
  //      disp.setLed(0, posY1, posX1, 1);
  //      disp.setLed(0, posY1 + 1, posX1, 1);
  //      disp.setLed(0, posY1, posX1 + 1, 1);
  //      disp.setLed(0, posY1 + 1, posX1 + 1, 1);
  //    }
  //  }
  //else
  if (buttonPushCounter == 2) {

    if ((millis() - ultimulUpdate) >= intervalRecalculare)
    {

      ultimulUpdate = millis();

      valX = analogRead(joyX);
      valY = analogRead(joyY);

      prevX1 = posX1;
      prevY1 = posY1;

      if (valX < 340)
      {
        if (posX1 < 6)
        {
          posX1++;
        }
      }
      else if (valX > 680)
      {
        if (posX1 > 0)
        {
          posX1--;
        }
      }

      if (valY < 340)
      {
        if (posY1 < 6)
        {
          posY1++;
        }
      }
      else if (valY > 680)
      {
        if (posY1 > 0)
        {
          posY1--;
        }
      }

      if (prevX1 != posX1 || prevY1 != posY1)
      {
        disp.setLed(0, prevY1, prevX1, 0);
        disp.setLed(0, prevY1 + 1, prevX1, 0);
        disp.setLed(0, prevY1, prevX1 + 1, 0);
        disp.setLed(0, prevY1 + 1, prevX1 + 1, 0);
      }

      disp.setLed(0, posY1, posX1, 1);
      disp.setLed(0, posY1 + 1, posX1, 1);
      disp.setLed(0, posY1, posX1 + 1, 1);
      disp.setLed(0, posY1 + 1, posX1 + 1, 1);
    }
    delay(175);
    if (++i >= IMAGES_LEN) {
      i = 0;
    }
    animatie(IMAGES[i]);
  }

  else if (buttonPushCounter == 3) {

    if ((millis() - ultimulUpdate) >= intervalRecalculare)
    {

      ultimulUpdate = millis();

      valX = analogRead(joyX);
      valY = analogRead(joyY);

      prevX1 = posX1;
      prevY1 = posY1;

      if (valX < 340)
      {
        if (posX1 < 6)
        {
          posX1++;
        }
      }
      else if (valX > 680)
      {
        if (posX1 > 0)
        {
          posX1--;
        }
      }

      if (valY < 340)
      {
        if (posY1 < 6)
        {
          posY1++;
        }
      }
      else if (valY > 680)
      {
        if (posY1 > 0)
        {
          posY1--;
        }
      }

      if (prevX1 != posX1 || prevY1 != posY1)
      {
        disp.setLed(0, prevY1, prevX1, 0);
        disp.setLed(0, prevY1 + 1, prevX1, 0);
        disp.setLed(0, prevY1, prevX1 + 1, 0);
        disp.setLed(0, prevY1 + 1, prevX1 + 1, 0);
      }

      disp.setLed(0, posY1, posX1, 1);
      disp.setLed(0, posY1 + 1, posX1, 1);
      disp.setLed(0, posY1, posX1 + 1, 1);
      disp.setLed(0, posY1 + 1, posX1 + 1, 1);
    }
    delay(200);
    if (++i >= IMAGES_LEN) {
      i = 0;
    }
    animatie(IMAGES[i]);
  }

  else if (buttonPushCounter == 4) {

    if ((millis() - ultimulUpdate) >= intervalRecalculare)
    {

      ultimulUpdate = millis();

      valX = analogRead(joyX);
      valY = analogRead(joyY);

      prevX1 = posX1;
      prevY1 = posY1;

      if (valX < 340)
      {
        if (posX1 < 6)
        {
          posX1++;
        }
      }
      else if (valX > 680)
      {
        if (posX1 > 0)
        {
          posX1--;
        }
      }

      if (valY < 340)
      {
        if (posY1 < 6)
        {
          posY1++;
        }
      }
      else if (valY > 680)
      {
        if (posY1 > 0)
        {
          posY1--;
        }
      }

      if (prevX1 != posX1 || prevY1 != posY1)
      {
        disp.setLed(0, prevY1, prevX1, 0);
        disp.setLed(0, prevY1 + 1, prevX1, 0);
        disp.setLed(0, prevY1, prevX1 + 1, 0);
        disp.setLed(0, prevY1 + 1, prevX1 + 1, 0);
      }

      disp.setLed(0, posY1, posX1, 1);
      disp.setLed(0, posY1 + 1, posX1, 1);
      disp.setLed(0, posY1, posX1 + 1, 1);
      disp.setLed(0, posY1 + 1, posX1 + 1, 1);
    }
    delay(150);
    if (++i >= IMAGES_LEN) {
      i = 0;
    }
    animatie(IMAGES[i]);
  }

  else if (buttonPushCounter == 5) {

    if ((millis() - ultimulUpdate) >= intervalRecalculare)
    {

      ultimulUpdate = millis();

      valX = analogRead(joyX);
      valY = analogRead(joyY);

      prevX1 = posX1;
      prevY1 = posY1;

      if (valX < 340)
      {
        if (posX1 < 6)
        {
          posX1++;
        }
      }
      else if (valX > 680)
      {
        if (posX1 > 0)
        {
          posX1--;
        }
      }

      if (valY < 340)
      {
        if (posY1 < 6)
        {
          posY1++;
        }
      }
      else if (valY > 680)
      {
        if (posY1 > 0)
        {
          posY1--;
        }
      }

      if (prevX1 != posX1 || prevY1 != posY1)
      {
        disp.setLed(0, prevY1, prevX1, 0);
        disp.setLed(0, prevY1 + 1, prevX1, 0);
        disp.setLed(0, prevY1, prevX1 + 1, 0);
        disp.setLed(0, prevY1 + 1, prevX1 + 1, 0);
      }

      disp.setLed(0, posY1, posX1, 1);
      disp.setLed(0, posY1 + 1, posX1, 1);
      disp.setLed(0, posY1, posX1 + 1, 1);
      disp.setLed(0, posY1 + 1, posX1 + 1, 1);
    }
    delay(100);
    if (++i >= IMAGES_LEN) {
      i = 0;
    }
    animatie(IMAGES[i]);
  }
  else if (buttonPushCounter == 6) {
    pause();
  }
}
