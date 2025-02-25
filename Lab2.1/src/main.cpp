#include <Arduino.h>
#include <stdio.h>  // Required for printf

/*
 * Sequential Task Application for Arduino Mega 2560
 * Task 1: Button LED - Changes LED state on button press
 * Task 2: Blinking LED - Active only when Task 1 LED is off
 * Task 3: State Variable - Increment/decrement a variable using two buttons
 * Idle Task: Reports system state using STDIO functions (printf)
 */

// Pin definitions
const int BUTTON_1_PIN = 2;     // Button for Task 1
const int LED_1_PIN = 11;       // LED for Task 1
const int LED_2_PIN = 12;       // LED for Task 2
const int INC_BUTTON_PIN = 3;   // Button to increment counter
const int DEC_BUTTON_PIN = 4;   // Button to decrement counter

// Global variables (signals) for provider/consumer communication
volatile bool led1State = false;        // Task 1 LED state
volatile int blinkCount = 5;            // Number of blinks for LED 2 (Task 3 variable)
volatile unsigned long lastTaskTime[3]; // To track task timing
volatile bool buttonPressed = false;    // Debounce flag for button 1
volatile bool incButtonPressed = false; // Debounce flag for increment button
volatile bool decButtonPressed = false; // Debounce flag for decrement button

// Task recurrence times (milliseconds)
const unsigned long TASK1_RECURRENCE = 50;   // Button debounce time
const unsigned long TASK2_RECURRENCE = 100;  // Blink rate
const unsigned long TASK3_RECURRENCE = 100;  // Button scan rate for inc/dec
const unsigned long IDLE_REPORT_INTERVAL = 1000; // Status report interval

// Offsets to stagger task execution
const unsigned long TASK1_OFFSET = 0;
const unsigned long TASK2_OFFSET = 20;
const unsigned long TASK3_OFFSET = 40;

// Function prototypes
void task1_ButtonLED();
void task2_BlinkingLED();
void task3_StateVariable();
void idleTask_Report();

// Initialize printf output to redirect to Serial
// This function is called by printf to output characters
int serialPutchar(char c, FILE* stream) {
  Serial.write(c);
  return 0;
}
// Set up a FILE stream for printf
FILE serial_stdout;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set up printf to use Serial
  fdev_setup_stream(&serial_stdout, serialPutchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &serial_stdout;
  
  printf("Sequential Task System Initialized\n");
  
  // Configure pins
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(INC_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DEC_BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize task timing
  unsigned long currentTime = millis();
  lastTaskTime[0] = currentTime + TASK1_OFFSET;
  lastTaskTime[1] = currentTime + TASK2_OFFSET;
  lastTaskTime[2] = currentTime + TASK3_OFFSET;
  
  // Set initial LED states
  digitalWrite(LED_1_PIN, led1State);
  digitalWrite(LED_2_PIN, LOW);
}

void loop() {
  unsigned long currentTime = millis();
  
  // Task 1 - Button LED
  if (currentTime - lastTaskTime[0] >= TASK1_RECURRENCE) {
    task1_ButtonLED();
    lastTaskTime[0] = currentTime;
  }
  
  // Task 2 - Blinking LED
  if (currentTime - lastTaskTime[1] >= TASK2_RECURRENCE) {
    task2_BlinkingLED();
    lastTaskTime[1] = currentTime;
  }
  
  // Task 3 - State Variable
  if (currentTime - lastTaskTime[2] >= TASK3_RECURRENCE) {
    task3_StateVariable();
    lastTaskTime[2] = currentTime;
  }
  
  // Idle Task - Reports system state
  idleTask_Report();
}

// Task 1: Change LED state on button press
void task1_ButtonLED() {
  // Provider: Reads button state and updates LED1 state
  int buttonReading = digitalRead(BUTTON_1_PIN);
  
  // Improved debounce logic - button is LOW when pressed (INPUT_PULLUP)
  if (buttonReading == LOW) {
    if (!buttonPressed) {
      // Toggle LED state on button press
      led1State = !led1State;
      digitalWrite(LED_1_PIN, led1State ? HIGH : LOW); // Explicitly set HIGH/LOW
      printf("Button pressed! LED1 is now: %s\n", led1State ? "ON" : "OFF");
      buttonPressed = true; // Set the debounce flag
    }
  } else {
    // Reset debounce flag when button is released
    buttonPressed = false;
  }
}

// Task 2: Blinking LED (active only when Task 1 LED is off)
void task2_BlinkingLED() {
  // Consumer: Uses led1State from Task 1
  static bool led2State = false;
  static int currentBlink = 0;
  
  if (!led1State) {
    // Only blink when LED1 is off
    led2State = !led2State;
    digitalWrite(LED_2_PIN, led2State ? HIGH : LOW); // Explicitly set HIGH/LOW
    
    // Count state changes when LED goes high
    if (led2State) {
      currentBlink++;
      if (currentBlink >= blinkCount) {
        currentBlink = 0;
      }
    }
  } else {
    // Turn off LED2 when LED1 is on
    digitalWrite(LED_2_PIN, LOW);
    currentBlink = 0;
  }
}

// Task 3: Increment/decrement variable using two buttons
void task3_StateVariable() {
  // Provider: Updates blinkCount based on button presses
  bool incButtonState = digitalRead(INC_BUTTON_PIN) == LOW;
  bool decButtonState = digitalRead(DEC_BUTTON_PIN) == LOW;
  
  // Increment button with debounce
  if (incButtonState && !incButtonPressed) {
    if (blinkCount < 20) { // Set a reasonable upper limit
      blinkCount++;
      printf("Blink count increased to: %d\n", blinkCount);
    }
    incButtonPressed = true;
  } else if (!incButtonState && incButtonPressed) {
    incButtonPressed = false;
  }
  
  // Decrement button with debounce
  if (decButtonState && !decButtonPressed) {
    if (blinkCount > 1) { // Ensure minimum value is 1
      blinkCount--;
      printf("Blink count decreased to: %d\n", blinkCount);
    }
    decButtonPressed = true;
  } else if (!decButtonState && decButtonPressed) {
    decButtonPressed = false;
  }
}

// Idle Task: Report system state
void idleTask_Report() {
  static unsigned long lastReportTime = 0;
  unsigned long currentTime = millis();
  
  // Consumer: Reports states at regular intervals
  if (currentTime - lastReportTime >= IDLE_REPORT_INTERVAL) {
    printf("--- System Status Report ---\n");
    printf("Task 1 LED State: %s\n", led1State ? "ON" : "OFF");
    printf("Task 2 Blink Status: %s\n", led1State ? "INACTIVE" : "ACTIVE");
    printf("Task 3 Blink Count: %d\n", blinkCount);
    printf("---------------------------\n");
    
    lastReportTime = currentTime;
  }
}