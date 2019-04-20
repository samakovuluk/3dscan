const int ena = 8; //habilita o motor
const int dir = 2; //determina a direção
const int pul = 5; //executa um passo

// mudanças de estado do pulso
boolean pulso = LOW; //estado do pulso


const int sw = 10;
const int sc = 12;

int ppr = 0;
int drr = 0;
int spr = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(ena, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(pul, OUTPUT);
  digitalWrite(ena, LOW);
  digitalWrite(dir, HIGH);
  digitalWrite(pul, LOW);
  Serial.println("Set up conf");
  boolean r = false;
  while (r != true) {
    String data =  Serial.readString();
    boolean t = false;
    if (data != "" && data.length() > 3) {
      data.replace("\n", "");
      String directon, pulse, sped;
      for (int i = 0; i < data.length(); i++) {
        if (i == 0) {
          directon = data[i];
        }
        else {
          if (data[i] == ':' && t == false && i == 1) {
            t = true;
          }
          else {
            if (t == true && data[i] != ':') {
              pulse += data[i];
            }
            else {
              t = false;
              if (data[i] != ':') {
                sped += data[i];
              }
            }
          }
        }
      }
      if (directon.length() == 1 && (directon == "f" || directon == "t") && isnum(pulse) == 1 && isnum(sped) == 1 )
      {
        //ward(true,1000,130);
        bool dr;
        if (directon == "f") {
          dr = false;
        }
        else {
          dr = true;
        }
        int pl = atoi( pulse.c_str() );
        int spp = atoi(sped.c_str());
        //Serial.println(dr);
        //Serial.println(pl);
        //Serial.println(spp);
        Serial.println("Done");
        digitalWrite(ena, LOW);
        ppr = pl;
        drr = dr;
        spr = spp;
        Serial.println("Done command ward");
        Serial.println(ppr);
        Serial.println(drr);
        Serial.println(spr);
        r = true;

      }
      else {
        Serial.println("Invalid input.");
      }
    }
  }


  //calbr();

}
void calbr() {
  while (digitalRead(sw) != HIGH && digitalRead(sc) != HIGH) {
    ward(true, 1, spr);
  }
  Serial.println("Calibration is done.");
  digitalWrite(pul, LOW);
}
void loop()
{

  String data =  Serial.readString();
  boolean t = false;
  if (data != "" && data.length() > 3) {
    data.replace("\n", "");
    String directon, pulse, sped;
    for (int i = 0; i < data.length(); i++) {
      if (i == 0) {
        directon = data[i];
      }
      else {
        if (data[i] == ':' && t == false && i == 1) {
          t = true;
        }
        else {
          if (t == true && data[i] != ':') {
            pulse += data[i];
          }
          else {
            t = false;
            if (data[i] != ':') {
              sped += data[i];
            }
          }
        }
      }
    }
    if (directon.length() == 1 && (directon == "f" || directon == "t") && isnum(pulse) == 1 && isnum(sped) == 1 )
    {
      //ward(true,1000,130);
      bool dr;
      if (directon == "f") {
        dr = false;
      }
      else {
        dr = true;
      }
      long long int pl = 0;

      for (int i = 0; i < pulse.length(); i++) {
        pl += pulse[i] - '0';
        pl *= 10;
      }
      pl /= 10;
      Serial.println(pulse);
      //                                                                                                                                                 Serial.println(pl);
      long int spp = atoi(sped.c_str());
      //Serial.println(dr);
      //Serial.println(pl);
      //Serial.println(spp);
      digitalWrite(ena, LOW);

      Serial.println(spp);
      //        Serial.println(pl);
      spr = spp;
      ward(dr, pl, spp);
      digitalWrite(pul, LOW);

    }
    else {
      Serial.println("Invalid input.");
    }
  }
  else if (data == "c\n") {
    calbr();
  }
  else if (data == "f\n") {
    ward(true, 1, 140);
    Serial.println("Done command f");

  }
  else if (data == "b\n") {
    ward(false, 1, 140);
    Serial.println("Done command b");
  }

}
void ward(boolean d, long long int p, int sp) {
  boolean r = true;
  if (d == true) {
    digitalWrite(dir, HIGH);
  }
  else {
    digitalWrite(dir, LOW);
  }
  for (int i = 0; i < p; i++) {
    /*if(Serial.readString()=="s\n"){
      break;
      }*/
    pulso = !pulso;
    digitalWrite(pul, pulso);
    delayMicroseconds(sp);
    if (digitalRead(sw) == HIGH || digitalRead(sc) == HIGH) {
      Serial.println("Done command ward with error");
      r = false;
      break;
    }
  }

}
bool isnum(String line)
{
  char* p;
  strtol(line.c_str(), &p, 10);
  return *p == 0;
}
