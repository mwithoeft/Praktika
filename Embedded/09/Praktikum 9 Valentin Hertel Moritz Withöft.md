# Praktikum 9 Valentin Hertel Moritz Withöft

## Aufgabe 1:

#### Beantworten Sie die Fragen vor dem Praktikum schriftlich:

##### a) Wie lautet die Adresse des DS1621, mit dem dieser in der dargestellten Schaltung angesteuert wird? Erklären Sie, wie sich die Adresse zusammensetzt und wie Sie die Adresse mit der Wire-Bibliothek benutzen.

Die Adresse des DS1621 Sensors setzt sich immer aus den ersten 4 statischen Bits zusammen (1001) und der Nummer des Pins. Für den angeschlossenen SDA Pin wird die 3-stellige binär zahl 000 benötigt. Das letzte Bit sagt aus ob es ein read (1) oder ein write (0) ist. Also ist die Adresse zum lesen 10010001 und zum schreiben 10010000. In der Wire Bibliothek kann die Adresse, in der Funktion beginTransmission(address) benutzt werden, um die Datenübertragung zu beginnen.



##### b) Wie setzt sich das Format zur Übertragung von Temperaturwerten bei dem DS1621 zusammen? Welche Befehle und Parameter (mit der Wire-Bibliothek) müssen an den DS1621 gesendet werden, um dessen Pin 3 (TOUT) so einzustellen, dass dieser bei einer Temperatur größer 25° Celsius auf HIGH geht?

Der Temperaturwert ist ein 9 Bit Zahl, die in 2 Bytes übertragen wird. Das erste Byte bestimmt den Temperaturwert vor dem Komma. Beim zweiten Byte wird nur das höherwertige Bit betrachtet, für eine 1 beträgt die Nachkommastelle ,5 und für ein 0 ,0.

```c++
const char Address = 72;
const char AccessTH = 161;
const char WriteDelay = 10;
const char AccessConf = 172;

char conf;
char thFlag = 64;

//Read config
Wire.beginTransmission(Address);
  Wire.write(AccessConf);
  Wire.endTransmission(false);
  Wire.requestFrom(Address,1,true);
  if (Wire.available() >= 1)
  {
    conf = Wire.read();
  }

Wire.beginTransmission(adresse);
//set TH flag
Wire.write(AccessConf);
delay(WriteDelay);
wire.write(conf | thFlag);
//set TH value
Wire.write(accessTH);
delay(writeDelay);
Wire.write(25);
delay(writeDelay);
Wire.write(0);
Wire.endTransmission();    

```



##### c) Mit welchen Anweisungen bekommen Sie die Temperatur vom DS1621 geliefert?



  ```c++
  	const char Address = 72
    const char ReadTemp = 170;
	const char ReadDelay = 50;
	const char StartConvert = 119;
	const char StopConvert = 34;

    char[] temp = char[2];
  	int count = 0;

  	Wire.beginTransmission(Adresse);
	Wire.write(StartConvert);
	Wire.write(StopConvert);
  	Wire.write(ReadTemp);
  	Wire.endTransmission();    
  	Wire.request(address, 2);
      while (Wire.available()&&count<2){
          temp[count]= Wire.read();
          delay(ReadDelay);
          count++;
      }
  ```


Als erstes muss die Übertragung, mit beginTransmission(adresse) aufgebaut werden. Dann muss das Konvertieren mit write(StartCOnvert) begonnen werden und anschließend beendet, damit man die Temperatur auslesen kann. Anschließend muss der Befehl zur Temperaturabfrage übertragen werden (write(102)). Im nächsten Schritt wird die Übertragung mit endTransmission() beendet, damit die Temperatur abgefragt werden kann. Dazu muss request(adresse, 2) ausgeführt werden um anschließend in der schleife,
while(Wire.available()&&count<2)  die Temperatur mit read() in ein Char Array zu speichern.