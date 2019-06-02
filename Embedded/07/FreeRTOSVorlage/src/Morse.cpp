#include <Energia.h>

#include "OutputStrategy.h"
class Morse{
  public:
    void morseString(OutputStrategy out, char* input){
      String morsecode = "";
      Serial.write("morse");
      for(int i = 0; input[i] != '/0'; i++){
    	  if(input[i] == 'a'){
          out.printMorse('-');
          out.printMorse('.');
    	  }
        morsecode += "";
      }
    }
};

