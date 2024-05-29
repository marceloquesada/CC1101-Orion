
void start_timer(int interv){
  time_ref = millis();
  interval = interv;
}

bool update_timer(){
  if (millis() - time_ref >= interval){
    time_ref = millis();
    return true;
  }
  else {
    return false;
  }
}