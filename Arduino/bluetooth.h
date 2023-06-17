//Yeah there's only one function here

bool BT_receive(char cmdline[]){
  if(Serial1.available()){
    char cmd;
    cmd = Serial1.read();
    if(cmd == '{'){
      int i=0;
      cmdline[i] = cmd; i++;
      while(cmd != '}'&& i<1000){
        if(Serial1.available()){
          cmd = Serial1.read();
          cmdline[i] = cmd; i++;
        }
      }
      cmdline[i+1] = '\0';
      Serial.println(cmdline);
      return true;
    }
    else Serial1.read();
  }
  return false;
}


