#define FLASH_RATE_HZ 2
#define BUTTON_PIN 4
#define LED_PIN 0
#define PWM_MAX 255

// Operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flashing
int operating_mode = 0;
int button_pushed = 0;
int previous_button_state = 0;
int pwm_out = 0;
int time_lag = 0;
int time_delay = 250;


void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(BUTTON_PIN, button_detect, FALLING);
  //the falling state catches when it goes from high to low
  //button_pushed is a function later on when the button is pushed
  //BUTTON_IN is a pin state that is associated with the pin

}


void loop() {

  check_button_status();

  led_mode();

}

void shine_led() {
  // Shine LED 
  analogWrite(LED_PIN, pwm_out);
}


void flash_the_light() {
  // Flash light at 2Hz
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}


void led_mode() {
  // Use switch case statement to change LED mode
  switch (operating_mode) {
    case 0:
      pwm_out = 0;
      shine_led();
      break;
    case 1:
      pwm_out = PWM_MAX;
      shine_led();
      break;
    case 2:
      pwm_out = int(PWM_MAX / 2);
      shine_led();
      break;
    case 3:
      pwm_out = int(PWM_MAX / 4);
      shine_led();
      break;
    case 4:
      flash_the_light();
  }
}


void check_button_status() {
  // set operating mode
  // reset previous button state, interrupt catch, etc
  if (button_pushed == 1) {
    if (millis() - time_lag > time_delay) {
      operating_mode = operating_mode + 1;
      if (operating_mode == 5) {
        operating_mode = 0;
      }
      time_lag = millis();
    }
  }
  button_pushed = previous_button_state;
}


void button_detect() {
  // Detect button activation
  button_pushed = 1;
}
