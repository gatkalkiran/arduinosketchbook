#define relay_cs 47
#define sd_cs SS
#define gsm_power 5 // for gsm shield
#define gsm_power_fet 4 //for telit

#define batt_sense A4
#define temp_sense 11


void setup()
{
  Serial.begin(9600);
  Serial.println("started");

  setup_rtc();
  setup_temp();
  setup_sd();
  pinMode(gsm_power,OUTPUT);
  digitalWrite(gsm_power,LOW);
  pinMode(gsm_power_fet,OUTPUT);
  pinMode(sd_cs,OUTPUT);
  pinMode(relay_cs,OUTPUT);
  digitalWrite(sd_cs,LOW);
  digitalWrite(relay_cs,LOW);



  //dump_log();
  log();
}

long int last_send  = 0;
void loop()
{
  if( millis() > last_send + 60000 )
  {
    log();
    last_send = millis();
  }  
}

void log()
{
  int batt_sense = analogRead(batt_sense);
  //print_time();
  String log_string;

  log_string += get_temp();
  log_string += ",";
  log_string += batt_sense;


  write_log(log_string);

  setup_gsm();
  send_gsm_data(get_temp());
  power_down_gsm();
}


