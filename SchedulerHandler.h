#ifndef SCHEDULER_HANDLER_h
#define SCHEDULER_HANDLER_h

#define MAX_SCHEDULES 10

class SchedulerHandler{
public:
  SchedulerHandler(){
    }
  void initialize(){
    //set up 100 hz timer interrupt on timer2
    noInterrupts();           // disable all interrupts
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 250;            // preload timer 16000000
    TCCR2B |= (1 << WGM12);   // CTC mode
    TCCR2B |= (1 << CS12);    // 256 prescaler
    TIMSK2 |= (1 << OCIE1A);  // enable timer compare interrupt
    interrupts();
  }
  void addScheduler(Scheduler *toAdd){
    if(schedules < MAX_SCHEDULES){
      schedulers[schedules] = toAdd;
      schedules ++;
    }
    else{
      Serial.println("ERROR! TO MANY SCHEDULES!");
      while(true) delay(100);
    }
  }
  void add(void (*func)(),long millisUpdate){
    if(schedules < MAX_SCHEDULES){
      schedulers[schedules] = new Scheduler(func, millisUpdate);
      schedules ++;
    }
    else{
      Serial.println("ERROR! TO MANY SCHEDULES!");
      while(true) delay(100);
    }
  }
  void update(){
    //Serial.println("Updating!");
    //Serial.println(schedules);
    for(int i = 0; i < schedules; i ++){
      schedulers[i]->update();
      //Serial.println("Update: " + String(i));
    }
    //Serial.println("Done Updating!");
  }
private:
  Scheduler *schedulers[10];
  int schedules = 0;
};

#endif
