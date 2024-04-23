// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27, 20, 4); // Ganti alamat sesuai dengan modul I2C LCD Anda
// int i = 0;
// int j = 0;
// int randomnum;
// int k = 0;
// byte customChar1[] = {
//   0x0E,
//   0x0E,
//   0x0E,
//   0x0E,
//   0x0E,
//   0x0E,
//   0x0E,
//   0x0E
// };

// byte customChar2[] = {
//   0x00,
//   0x00,
//   0x0E,
//   0x0E,
//   0x0E,
//   0x0E,
//   0x0E,
//   0x0E
// };
// byte customChar3[] = {
//   0x00,
//   0x00,
//   0x00,
//   0x00,
//   0x0E,
//   0x0E,
//   0x0E,
//   0x0E
// };
// byte customChar4[] = {
//   0x00,
//   0x00,
//   0x00,
//   0x00,
//   0x00,
//   0x00,
//   0x0E,
//   0x0E
// };
// byte customChar5[] = {
//   0x00,
//   0x00,
//   0x00,
//   0x00,
//   0x00,
//   0x00,
//   0x00,
//   0x00
// };
// void setup() {
//   lcd.init();
//   lcd.backlight();
//   lcd.createChar(4, customChar1);
//   lcd.createChar(3, customChar2);
//   lcd.createChar(2, customChar3);
//   lcd.createChar(1, customChar4);
//   lcd.createChar(0, customChar5);
//   lcd.setCursor(4, 1);
//   lcd.print("Welcome");
//   lcd.setCursor(1, 2);
//   lcd.print("JekIELTRiC021");
//   delay(2000);
//   lcd.clear();
// }

// void loop() {
//   randomnum = random(7, 9);
//   Serial.print("random numer = ");
//   Serial.println(randomnum);

//   for (i = randomnum; i > 0; i--) {
//     int z = i;
//     Serial.print("i value = ");
//     Serial.println(i);
//     Serial.print("j= ");
//     Serial.println(j);
//     Serial.print("k= ");
//     Serial.println(k);
//     test();
//     lcd.setCursor(7, 0);
//     lcd.write(j);
//     lcd.setCursor(7, 1);
//     lcd.write(k);
//     i--;
//     test();
//     lcd.setCursor(8, 0);
//     lcd.write(j);
//     lcd.setCursor(8, 1);
//     lcd.write(k);
//     lcd.setCursor(6, 0);
//     lcd.write(j);
//     lcd.setCursor(6, 1);
//     lcd.write(k);
//     i--;
//     test();
//     lcd.setCursor(9, 0);
//     lcd.write(j);
//     lcd.setCursor(9, 1);
//     lcd.write(k);
//     lcd.setCursor(5, 0);
//     lcd.write(j);
//     lcd.setCursor(5, 1);
//     lcd.write(k);

//     i--;
//     test();
//     lcd.setCursor(10, 0);
//     lcd.write(j);
//     lcd.setCursor(10, 1);
//     lcd.write(k);
//     lcd.setCursor(4, 0);
//     lcd.write(j);
//     lcd.setCursor(4, 1);
//     lcd.write(k);

//     i--;
//     test();
//     lcd.setCursor(11, 0);
//     lcd.write(j);
//     lcd.setCursor(11, 1);
//     lcd.write(k);
//     lcd.setCursor(3, 0);
//     lcd.write(j);
//     lcd.setCursor(3, 1);
//     lcd.write(k);

//     i--;
//     test();
//     lcd.setCursor(12, 0);
//     lcd.write(j);
//     lcd.setCursor(12, 1);
//     lcd.write(k);
//     lcd.setCursor(2, 0);
//     lcd.write(j);
//     lcd.setCursor(2, 1);
//     lcd.write(k);

//     i--;
//     test();
//     lcd.setCursor(13, 0);
//     lcd.write(j);
//     lcd.setCursor(13, 1);
//     lcd.write(k);
//     lcd.setCursor(1, 0);
//     lcd.write(j);
//     lcd.setCursor(1, 1);
//     lcd.write(k);

//     i--;
//     test();
//     lcd.setCursor(14, 0);
//     lcd.write(j);
//     lcd.setCursor(14, 1);
//     lcd.write(k);
//     lcd.setCursor(0, 0);
//     lcd.write(j);
//     lcd.setCursor(0, 1);
//     lcd.write(k);

//     delay(50);
//     lcd.clear();

//     i = z;
//   }
// }

// void test() {
//   if (i == 8) {
//     j = 4;
//     k = 4;
//   }
//   if (i == 7) {
//     j = 3;
//     k = 4;
//   }
//   if (i == 6) {
//     j = 2;
//     k = 4;
//   }
//   if (i == 5) {
//     j = 1;
//     k = 4;
//   }
//   if (i == 4) {
//     j = 0;
//     k = 4;
//   }
//   if (i == 3) {
//     j = 0;
//     k = 3;
//   }
//   if (i == 2) {
//     j = 0;
//     k = 2;
//   }
//   if (i == 1) {
//     j = 0;
//     k = 1;
//   }
//   if (i == 0) {
//     j = 0;
//     k = 0;
//   }
// }


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // Ganti alamat sesuai dengan modul I2C LCD Anda
int i = 0;
int j = 0;
int randomnum;
int k = 0;

byte customChar1[] = {
  0b00000,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b00000
};

byte customChar2[] = {
  0b00000,
  0b00000,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110
};

byte customChar3[] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b01110,
  0b01110,
  0b01110
};

byte customChar4[] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b01110
};

byte customChar5[] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(4, customChar1);
  lcd.createChar(3, customChar2);
  lcd.createChar(2, customChar3);
  lcd.createChar(1, customChar4);
  lcd.createChar(0, customChar5);
  
  lcd.setCursor(6, 1);
  lcd.print("Welcome");
  lcd.setCursor(3, 2);
  lcd.print("JekIELTRiC021");
  delay(2000);
  lcd.clear();
}

void loop() {
  randomnum = random(7, 9);
  Serial.print("random numer = ");
  Serial.println(randomnum);

  for (i = randomnum; i > 0; i--) {
    int z = i;
    Serial.print("i value = ");
    Serial.println(i);
    Serial.print("j = ");
    Serial.println(j);
    Serial.print("k = ");
    Serial.println(k);
    test();
    lcd.setCursor(7, 0);
    lcd.write(j);
    lcd.setCursor(7, 1);
    lcd.write(k);
    i--;
    test();
    lcd.setCursor(8, 0);
    lcd.write(j);
    lcd.setCursor(8, 1);
    lcd.write(k);
    lcd.setCursor(6, 0);
    lcd.write(j);
    lcd.setCursor(6, 1);
    lcd.write(k);
    i--;
    test();
    lcd.setCursor(9, 0);
    lcd.write(j);
    lcd.setCursor(9, 1);
    lcd.write(k);
    lcd.setCursor(5, 0);
    lcd.write(j);
    lcd.setCursor(5, 1);
    lcd.write(k);

    i--;
    test();
    lcd.setCursor(10, 0);
    lcd.write(j);
    lcd.setCursor(10, 1);
    lcd.write(k);
    lcd.setCursor(4, 0);
    lcd.write(j);
    lcd.setCursor(4, 1);
    lcd.write(k);

    i--;
    test();
    lcd.setCursor(11, 0);
    lcd.write(j);
    lcd.setCursor(11, 1);
    lcd.write(k);
    lcd.setCursor(3, 0);
    lcd.write(j);
    lcd.setCursor(3, 1);
    lcd.write(k);

    i--;
    test();
    lcd.setCursor(12, 0);
    lcd.write(j);
    lcd.setCursor(12, 1);
    lcd.write(k);
    lcd.setCursor(2, 0);
    lcd.write(j);
    lcd.setCursor(2, 1);
    lcd.write(k);

    i--;
    test();
    lcd.setCursor(13, 0);
    lcd.write(j);
    lcd.setCursor(13, 1);
    lcd.write(k);
    lcd.setCursor(1, 0);
    lcd.write(j);
    lcd.setCursor(1, 1);
    lcd.write(k);

    i--;
    test();
    lcd.setCursor(14, 0);
    lcd.write(j);
    lcd.setCursor(14, 1);
    lcd.write(k);
    lcd.setCursor(0, 0);
    lcd.write(j);
    lcd.setCursor(0, 1);
    lcd.write(k);

    delay(50);
    lcd.clear();

    i = z;
  }
}

void test() {
  if (i == 8) {
    j = 4;
    k = 4;
  }
  if (i == 7) {
    j = 3;
    k = 4;
  }
  if (i == 6) {
    j = 2;
    k = 4;
  }
  if (i == 5) {
    j = 1;
    k = 4;
  }
  if (i == 4) {
    j = 0;
    k = 4;
  }
  if (i == 3) {
    j = 0;
    k = 3;
  }
  if (i == 2) {
    j = 0;
    k = 2;
  }
  if (i == 1) {
    j = 0;
    k = 1;
  }
  if (i == 0) {
    j = 0;
    k = 0;
  }
}
