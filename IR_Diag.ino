/*
 * IR_Diag -- Reads IR codes and displays them on an LCD, optionally to Serial
 * Bill Kibby 11/06/2014
 *
 * Based on the the IRremote library by Ken Shirriff: http://arcfn.com
 */

#include <IRremote.h>
#include <LiquidCrystal.h>

/* Configure the folllowing pin to read the IR detector */
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

/* This is based on my LCD shield, you may need to adjust this */
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/* Remove any comments on Serial commands to dump results to serial port simultaniously */

byte block[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

void clearline(int line) /* Clear previous line by printing an entire line of blocks, then really clearing line. Handy to see an update from several feet away */
{
  int p;
  int w=30;
  for(p=0; p<16; p++) 
  {
    lcd.setCursor(p,line);
    lcd.write((byte)0);
    delay(w);
  }
  delay(280);
  lcd.setCursor(0,line);
  lcd.write("                ");
}

void setup()
{
  // Serial.begin(115200);
  irrecv.enableIRIn();
  // Serial.println("Ready to decode IR!");
  lcd.createChar(0, block); // create a new character
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IR Remote Reader");
}

void dump(decode_results *results){
  char buffer[10];
  clearline(1);
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    // Serial.println("Could not decode message");
    lcd.setCursor(0,1);
    lcd.write("UNKNOWN TYPE ");
  } 
  else {
    if (results->decode_type == NEC) {
      // Serial.print("NEC: ");
      lcd.setCursor(0,1);
      lcd.write("NEC: ");
    } 
    else if (results->decode_type == SONY) {
      // Serial.print("SONY: ");
      lcd.setCursor(0,1);
      lcd.write("SONY: ");
    } 
    else if (results->decode_type == RC5) {
      // Serial.print("RC5: ");
      lcd.setCursor(0,1);
      lcd.write("RC5: ");
    } 
    else if (results->decode_type == RC6) {
      // Serial.print("RC6: ");
      lcd.setCursor(0,1);
      lcd.write("RC6: ");
    }
    // Serial.println(results->value, HEX);
    sprintf(buffer, "%08lX", (unsigned long)results->value);
    // Serial.println(buffer);
    lcd.write(buffer);
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    //    Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
  }
}
