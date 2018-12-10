#define FLASH_RATE_HZ 2
#define BUTTON_PIN 2
#define LED_PIN 11
#define PWM_MAX 255

// Operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flashing
int operating_mode = 0;
int button_pushed = 0;
//bool button_pushed = false;
int previous_button_state = 0;
int pwm_out = 0;


void setup() {
   //the rising state catches when it goes from low to high
  //button_detect is a function later on when the button is pushed
  //BUTTON_IN is a pin state that is associated with the pin
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_detect, RISING);
  pinMode(LED_PIN, OUTPUT);
}


void loop() {
  check_button_status();
  led_mode();
  shine_led(pwm_out);
}

void button_detect(){
  // Detects pushes greater that 500 ms away from each other
  int time_delay = 500;
  unsigned long interrupt_time_initial = 0;
  unsigned long interrupt_time_current = millis();
  
  if (interrupt_time_current - interrupt_time_initial > time_delay){
    button_pushed = 1;
  }
  interrupt_time_initial = interrupt_time_current;
}


void check_button_status() {
  // set operating mode
  // reset previous button state
  if ((button_pushed == 1) && (previous_button_state != 4)) {
      operating_mode = previous_button_state + 1;
      button_pushed = 0;
  }
  else if ((button_pushed == 1 ) && (previous_button_state == 4)){
    operating_mode = 0;
    button_pushed = 0;
  }
  previous_button_state = operating_mode;
}



void led_mode() {
  // Use switch case statement to change LED mode
  switch (operating_mode) {
    case 0:
      pwm_out = 0;
      break;
    case 1:
      pwm_out = PWM_MAX;
      break;
    case 2:
      pwm_out = int(PWM_MAX / 2);
      break;
    case 3:
      pwm_out = int(PWM_MAX / 4);
      break;
    case 4:
      flash_led();
      break;
  }
}

void shine_led(int pwm_out) {
  // Shine LED 
  analogWrite(LED_PIN, pwm_out);
}


void flash_led() {
  // Flash light at 2Hz
  digitalWrite(LED_PIN, HIGH);
  delay((1000/FLASH_RATE_HZ)/2);
  digitalWrite(LED_PIN, LOW);
  delay((1000/FLASH_RATE_HZ)/2);
}
