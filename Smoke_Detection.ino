#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     9
#define OLED_DC        8
#define OLED_CS        10

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         &SPI, OLED_DC, OLED_RESET, OLED_CS);

#define MQ135_PIN A0 // Analog pin for MQ-135

void setup() {
  Serial.begin(9600);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("MQ-135 Gas Sensor");
  display.display();
  delay(2000); // Wait 2 seconds
}

void loop() {
  int gasValue = analogRead(MQ135_PIN);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Air Quality:");

  // Categorizing the air quality based on gas value
  display.setTextSize(2);
  display.setCursor(0, 20);

  if (gasValue < 300) {
    display.println("Good");
  } 
  else if (gasValue < 600) {
    display.println("Moderate");
  } 
  else {
    display.println("Poor");
  }

  // Show numerical gas value below air quality
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("Value: ");
  display.println(gasValue);

  display.display();

  delay(1000); // Wait 1 second before next reading
}
