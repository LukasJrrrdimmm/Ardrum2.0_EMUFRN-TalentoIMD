 
//==============================================================================
//=>                microDRUM/nanoDRUM firmware v1.4.0                        <= 
//=>                        www.microdrum.net                                 <=
//=>                         CC BY-NC-SA 3.0                                  <=
//=>                                                                          <=
//=> Massimo Bernava                                                          <=
//=> massimo.bernava@gmail.com                                                <=
//=> 2015-12-30                                                               <=
//=>           ADAPTADO PARA O ARDUINO MEGA SEM USO DOS MULTIPLEX             <=
//=>                               POR                                        <=
//=>                       PEDRO HENRIQUE KNUP                                <=
//=>                      facebook.com/pedroknup                              <=
//=>                            06/06/2016                                    <=
//==============================================================================

//========CONFIGURE=============

#define FASTADC           1     // FASTADC = Prescaler_16, VERYFASTADC = Prescaler_8, VERYVERYFASTADC = Prescaler_4
#define SERIALSPEED       1     // 1 = 115200, 0 = 31250 (MIDI) , picoMIDI use 115200 therefore with nanoDrum and v0.8 use 1
//==============================


#define TIMEFUNCTION millis() //NOT micros() (thresold error)


  #define fastNoteOn(_note,_velocity) { Serial.write(0x90 | 0x09); Serial.write(_note); Serial.write(_velocity);}
  #define fastMidiCC(_number,_value) { Serial.write((0xB0 | 0x09)); Serial.write(_number); Serial.write(_value); }


//===========MODE============
enum mode:byte
{
  Off     = 0,
  Standby = 1,
  MIDI    = 2,
  Tool    = 3
};
//============================

//===GLOBAL========================
mode Mode=Off;
unsigned long GlobalTime;
//=================================

//===SETTING================
//===General================
const int delayTime=0;
byte GeneralXtalk=0;
const byte NPin=11;
const byte NPinD=1;
//===========================

//===HiHat==================


//===========================

//===Xtalk===================
const byte NXtalkGroup=4;//Max number XTalk groups
int MaxXtalkGroup[NXtalkGroup] = {-1};
int MaxMultiplexerXtalk[8]={-1};
//===========================




