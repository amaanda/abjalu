#define AUTOPING_MS 1000

unsigned long now = 0;

void runAuto() {
  now = millis();
  
  runAutoping();  
}

bool autoping_on = false;

unsigned long last_autoping = 0;

int pingCount = 0;

void autoping() {
  autoping_on = !autoping_on;
  
  if(autoping_on)
    sayLinkit("Autoping is ON!");
  else {
    sayLinkit("Autoping is OFF!");
    pingCount = 0;
  }
}

void runAutoping() {
  if(autoping_on) {
    
    if(now - last_autoping >= AUTOPING_MS) {
      last_autoping = now;
      sayLinkit( String(pingCount) );
      saySlave("ping");
      pingCount++;
    }
     
  }
}

