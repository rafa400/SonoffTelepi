char message_buff[100];
char topic_buff[100];
bool wasconnected=false;
String wassubscribed="";

void mqttmessage(int gpio,int value,String mytype) {
    if (mqttClient.connected()) {
      String pubString = (String(value)=="0"?"OFF":"ON");
      String topicString = configure->getVariable("MQTTServerPath")+(mytype=="Relay"?"light/":mytype+"/")+configure->getVariable("hostname")+(String(gpio)=="12"?"":"_"+String(gpio))+"/status" ;
      mqttClient.publish(topicString.c_str(), pubString.c_str());
    }
}

void mqttconfig(int gpio,String mytype) {
    if (mqttClient.connected()) {
      String thename=configure->getVariable("hostname")+(String(gpio)=="12"?"":"_"+String(gpio));
      String topicString = configure->getVariable("MQTTServerPath")+(mytype=="Relay"?"light/":mytype+"/")+thename ;
      String pubString = "{'name': '"+thename+"', 'platform':'mqtt_json', 'state_topic':'"+topicString+"status', 'command_topic':'"+topicString+"set'}";      
      topicString=topicString+"/config";
      mqttClient.publish(topicString.c_str(), pubString.c_str());
    } else {
      String a="HOLA";
      String b="ADIOS";
      mqttClient.publish(a.c_str(), b.c_str());
    }
    
}

void mqtton(){
    mqttClient = PubSubClient( TeWifi::parseIP(configure->getVariable("MQTT_IP")), configure->getVariable("MQTT_Port").toInt(), callback,wifiClient);
    if (mqttClient.connect(tewifi->hostname.c_str(),"admin",configure->getVariable("MQTTpassword").c_str())) {
      // Send DEBUG message after connect
      String subscribeme=configure->getVariable("MQTTServerPath")+"DEBUG/"+configure->getVariable("hostname")+"/BootIP";
      IPAddress ip=WiFi.localIP();
      String myip=String(ip[0])+"."+String(ip[1])+"."+String(ip[2])+"."+String(ip[3]);
      //mqttconfig(GPIO12Relay,"Relay");
      String thename=configure->getVariable("hostname");
      thename=(thename==NULL?"HOLA":thename);
      
      String topicString = configure->getVariable("MQTTServerPath")+"light/"+thename;
//      String pubString = "{'name': '"+thename+"', 'platform':'mqtt_json', 'state_topic':'"+topicString+"/status', 'command_topic':'"+topicString+"/set'}";      
      
      String pubString = "{\"name\": \""+thename+"\", \"platform\":\"mqtt_json\",\"state_topic\":\"elpla/ESP/status\",\"command_topic\":\"elpla/ESP/status/set\"}";      
      String a="HOLA";
      String b="ADIOS";
      topicString=topicString+"/config";
      
      mqttClient.publish(topicString.c_str(), b.c_str());
      mqttClient.publish(a.c_str(), pubString.c_str());
      mqttClient.publish(subscribeme.c_str(), myip.c_str());      
    }
}

void mqttoff(){
  if (mqttClient.connected()) {
    if (wassubscribed!="") { // remove previous subscription
      mqttClient.unsubscribe(wassubscribed.c_str());
      wassubscribed="";
    }
    mqttClient.disconnect(); 
  }
}

void mqttcheck() {
  if (mqttClient.connected()) {
    mqttClient.loop();
    wasconnected=true;
    if (wassubscribed!="") {
      if ( configure->getVariable("MQTTenabled")=="off") mqttoff();
      // If it's connected and subscribed, nothing to do => return
    } else {
      // Subscribe to receive rele ON/OFF commands from MQTT broker
      wassubscribed=configure->getVariable("MQTTServerPath")+configure->getVariable("hostname")+"/set/#";
      mqttClient.subscribe(wassubscribed.c_str());
    }
  } else { // If it's disconnected
    wasconnected=false;
    if (wassubscribed!="") { // remove previous subscription
      mqttClient.unsubscribe(wassubscribed.c_str());
      wassubscribed="";
    }
    if ( (bootmode==APDEFAULT) && (configure->getVariable("MQTTenabled")=="on") && (WiFi.status() == WL_CONNECTED) ) {
      mqtton();
      if (mqttClient.connected()) {
        // Subscribe to receive rele ON/OFF commands from MQTT broker
        wassubscribed=configure->getVariable("MQTTServerPath")+configure->getVariable("hostname")+"/set/#";
        mqttClient.subscribe(wassubscribed.c_str());
      }
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  int i = 0;
  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }  
  message_buff[i] = '\0';
  String msgString = String(message_buff);

  String topicString = configure->getVariable("MQTTServerPath")+"DEBUG/"+configure->getVariable("hostname")+"/RECEIVED";
  mqttClient.publish(topicString.c_str(), message_buff);

  if (msgString.equals("OFF")) {
      changeOUT_OFF(GPIO12Relay);
  } else if (msgString.equals("ON")) {
      changeOUT_ON(GPIO12Relay);
  } else if (msgString.equals("SENSE")) {
    //senseMode = MODE_SENSE;
  } else {
      topicString =  configure->getVariable("MQTTServerPath")+"DEBUG/"+configure->getVariable("hostname")+"/RECEIVED";
      mqttClient.publish(topicString.c_str(), msgString.c_str());
  }
}

