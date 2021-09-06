

//=================================
//   DUAL SENSOR
//=================================

//===========CURVE============
const float _Exp[9] = {2.33, 3.85, 6.35, 10.48, 17.28, 28.5, 46.99 , 77.47, 127.74}; //e^((x/256)+0,85)
const float _Log[9] = {0, 83.67, 98.23, 106.74, 112.78, 117.47, 121.30 , 124.53, 127.34}; //21*ln(0,42*x)
const float _Sigma[9] = {2.28, 6.02, 15.13, 34.15, 63.5, 92.84, 111.86 , 120.97, 127.71}; //128/(1+e^((512-x)/128))
const float _Flat[9] = {0, 32.86, 46.42, 55.82, 64.0, 72.17, 81.57 , 95.13, 127}; //64-16*ln((1024/x)-1)

//===========TYPE============
enum type : byte
{
  Piezo    = 0,
  Switch   = 1,
  HHC      = 2,
  HH       = 3,
  HHs      = 4,
  YSwitch  = 5,
  Disabled = 15
};
//============================

//===========CURVE============
enum curve : byte
{
  Linear  = 0,
  Exp     = 1,
  Log     = 2,
  Sigma   = 3,
  Flat    = 4
};
//============================

//===========TIME============
enum state : byte
{
  Normal_Time     = 0,
  Scan_Time       = 1,
  Mask_Time       = 2,
  Retrigger_Time  = 3,
  Piezo_Time      = 4,
  Switch_Time     = 5,
  Choke_Time      = 6,
  Footsplash_Time = 7,
  Footclose_Time  = 8,
  Scanretrigger_Time = 9
};
//============================



const byte minn = 50;
const byte maxx = 127;
//===========================
//   PINOS ANALÓGICOS
//===========================

const byte P_CAIXA = 1;
const byte P_ARO  = 2;
const byte P_BUMBO      = 3;
const byte P_CHIMBAL   = 7;
const byte DP_HHC      = 0;
const byte P_RIDE   = 8;
const byte P_TOM1  = 4;
const byte P_TOM2  = 5;
const byte P_TOM3  = 10;
const byte P_ATAQUE  = 6;
const byte P_ATAQUE2  = 9;



//===========================
//   PINOS DIGITAIS 
//===========================


//===========================
//   CONFIGURAÇÃO DOS PINOS
//===========================
class pin
{
  public:

    //===========PIN============
    pin()
    {
      //CONFIGURAÇÃO INICIAL PARA TODOS AS ENTRADAS ANALÓGICAS
      Type = Disabled;

      //State;
      Note = 8;
      Gain = 40;

      Thresold = 10;
      ScanTime = 20;
      MaskTime = 10;
      Retrigger = 55;

      Curve = Linear;
      CurveForm = 75;
      Xtalk = 0;
      XtalkGroup = 0;

      //Time;
      MaxReading = -1;

      /*
            Type = Piezo;
        //State;
        Note = 38;
        Gain = 24;
        _pin = 0;
        Thresold = 2;
        ScanTime = 20;
        MaskTime = 10;
        Retrigger = 20;

        Curve = Linear;
        CurveForm = 80;
        Xtalk = 0;
        XtalkGroup = 0;

        //Time;
        MaxReading = -1;
      */

    }

    //===========SET============
    void set(byte pin)
    {
      Time = TIMEFUNCTION;
      this->Time = Time + this->MaskTime;
      this->_pin = pin;

      switch (pin)
      {
        //IR AJUSTANDO OS PARÂMETROS DE CADA PAD DE ACORDO COM SUAS NECESSIDADES.
        case P_CAIXA:
          this->Type = Piezo;
          this->Note = 38;
          this->CurveForm = 127;
          this->Gain = 20;
          this->MaskTime = 35;
          this->Retrigger = 45;
          this->ScanTime = 15;
          this->Thresold = 7;
          break;
          
        case P_ARO:
//          this->Type = Piezo;
          this->Note = 5;
          this->ScanTime = 20;
          this->Thresold = 30;
          break;

        case P_BUMBO:
          this->Type = Piezo;
          this->Note = 36;
          this->CurveForm = 127;
          this->Gain = 15;
          this->MaskTime = 50;
          this->Retrigger = 80;
          this->ScanTime = 15;
          break;
        case P_CHIMBAL: 
          this->Type = Piezo;
          this->Note = 8;
          this->CurveForm = 99;
          this->Gain = 50;
          this->MaskTime = 25;
          this->Retrigger = 35;
          this->ScanTime = 15;
          this->Thresold = 12;

          break;
        case P_RIDE:
          this->Type = Piezo;
          this->Note = 60;
          this->CurveForm = 99;
          this->Gain = 30;
          this->MaskTime = 30;
          this->Retrigger = 90;
          this->ScanTime = 30;

          break;
          case P_TOM1: 
          this->Type = Piezo;
          this->Note = 71;
          this->CurveForm = 99;
          this->Gain = 25;
          this->MaskTime = 30;
          this->Retrigger = 55;
          this->ScanTime = 10;
          break;

        case P_TOM2: 
          this->Type = Piezo;
          this->Note = 69;
          this->CurveForm = 99;
          this->Gain = 25;
          this->MaskTime = 30;
          this->Retrigger = 55;
          this->ScanTime = 30;
          break;

        case P_TOM3: 
          this->Type = Piezo;
          this->Note = 65;
          this->CurveForm = 99;
          this->Gain = 30;
          this->MaskTime = 30;
          this->Retrigger = 55;
          this->ScanTime = 30;
          break;
        case P_ATAQUE2: 
//          this->Type = Piezo;
          this->Note = 77;
          this->Gain = 25;
          this->MaskTime = 30;
          this->Retrigger = 55;
          this->ScanTime = 30;
          break;

        case P_ATAQUE: 
          this->Type = Piezo;
          this->Note = 79;//49
          this->CurveForm = 90;
          this->Gain = 20;
          this->MaskTime = 10;
          this->Retrigger = 75;
          this->ScanTime = 60;
          break;

        case DP_HHC:
//          this->Type = HHC;
          //this->Thresold = 5;
          this->CurveForm = 60;
          this->Gain = 50;
          this->Note = 4;
          break;
      }


    }
   
    
    //===========SCAN============
    void scan(byte sensor)
    {

      int yn_0 = -1;

      //===============================
      //        HHC
      //===============================
      if (Type == HHC) {
        scanHHC(_pin, analogRead(_pin));
        // Serial.println(_pin);
        return;
      }

      //===============================
      //        Switch
      //===============================
      if (Type == Switch)
      {
        yn_0 = analogRead(_pin);

        //DrawDiagnostic(MulSensor,yn_0/8);
        if (State == Normal_Time)
        {
          if (yn_0 < Thresold * 10 && yn_1 < Thresold * 10 )
          {
            //DrawDiagnostic(pin,0);
            State = Scan_Time;
            MaxReading = 0;
          }
        }
        else if (State == Scan_Time)
        {
          if (yn_0 < Thresold * 10 && yn_1 < Thresold * 10 ) MaxReading = MaxReading + 1;
          else
          {
            if (MaxReading > ScanTime) State = Switch_Time;
            else State = Normal_Time;
          }

          if (MaxReading > MaskTime) State = Choke_Time;
        }
        else if (State == Mask_Time)
        {
          //if(ZeroCountSensor[MulSensor]>0) DrawDiagnostic(MulSensor,ZeroCountSensor[MulSensor]*16);
          if (MaxReading > 0)
          {
            MaxReading = MaxReading - 1;
            //DrawDiagnostic(MulSensor,128);
          }
          else
          {
            if (yn_0 >= Thresold * 10 && yn_1 >= Thresold * 10 ) State = Normal_Time;
          }
        }
      }
      //===============================
      //        YSwitch
      //===============================
      else if (Type == YSwitch)
      {
        yn_0 = analogRead(sensor);

        if (yn_0 < Thresold * 4 )
        {
          State = Scan_Time;

          if (MaxReading <= MaskTime) MaxReading = MaxReading + 1;
        }
        else
        {
          if (MaxReading != 255 && MaxReading > ScanTime) //SwitchTime
          {
            ///DUAL
            //if(yn_0>DualThresoldSensor[MulSensor]*4)
            if (yn_0 > CurveForm * 4) MaxReading = MaxReading; //???
            else MaxReading = 512 + MaxReading;
          }
          State = Switch_Time;
        }
      }
      //===============================
      //        Piezo, HH
      //===============================
      else
      {

        GlobalTime = TIMEFUNCTION;


        if (State == Mask_Time)
        {
          if ((GlobalTime - Time) > MaskTime)
          {
            State = Retrigger_Time;
            Time = GlobalTime;
          }
        }

        yn_0 = 0.5 + ((float)analogRead(sensor) * (float)Gain) / 64.0;
        // yn_0 = analogRead(sensor);

        if (State == Retrigger_Time)
        {
          int MaxRetriggerSensor = MaxReading - ((GlobalTime - Time) * (Retrigger + 1) / 16);
          if (MaxRetriggerSensor > 0)
          {
            if ((yn_0 - yn_1) > Thresold && yn_0 > MaxRetriggerSensor)
            {
              State = Scan_Time;
              Time = GlobalTime;
              MaxReading = 0;
            }
          }
          else
            State = Normal_Time;
        }
        else if (State == Normal_Time)
        {
          if ((yn_0 - yn_1) > Thresold)
          {
            State = Scan_Time;
            Time = GlobalTime;
            MaxReading = 0;
          }
        }
        else if (State == Scan_Time)
        {
          if ((GlobalTime - Time) < ScanTime)
          {
            if (yn_0 > MaxReading)
            {
              MaxReading = yn_0;

              if (MaxXtalkGroup[XtalkGroup] == -1 || MaxXtalkGroup[XtalkGroup] < yn_0) //MaxGroup
                MaxXtalkGroup[XtalkGroup] = yn_0;


            }
          }
          else
            State = Piezo_Time;
        }


        //====================================
        //TOOL
        //====================================
        // if (Mode == Tool && LogPin == pin) LogTool(yn_0, pin);
        //====================================

        yn_1 = yn_0;
      }
    }

    //===========PLAY============
    void play(byte i)
    {
      //===============================
      //        Disabled
      //===============================
      if (Type == Disabled) return;

      //===============================
      //        HHC
      //===============================
      if (Type == HHC) //HH???
      {

      }

      if (State == Normal_Time || State == Scan_Time || State == Mask_Time || State == Retrigger_Time) return;


      playMIDI(i);

    }



    void playMIDI(byte i)
    {
      //===============================
      //        Single Switch
      //===============================
      if (Type == Switch)
      {
        /*if(TypeSensor[DualSensor(i)]==SWITCH) //Switch-Switch
          {
          fastNoteOn(ChannelSensor[i],NoteSensor[i],MaxReadingSensor[i]/8);

          #if WAVTRIGGER
          wavTrigger(i,MaxReadingSensor[i]/8);
          #endif

          MaxReadingSensor[i] = -1;
          }
          else if(TypeSensor[DualSensor(i)]==Disabled) //Switch-Disabled
          {

          }*/
        if (State == Switch_Time)
        {
          fastNoteOn(Note, 127);


          State = Mask_Time;
          MaxReading = Retrigger;
        }
        else if (State == Choke_Time) //Choke
        {
          fastNoteOn(ChokeNote, 127);

          State = Mask_Time;
          MaxReading = Retrigger;
        }
        return;
      }
      //===============================

      GlobalTime = TIMEFUNCTION;

      //===============================
      //          YSwitch
      //===============================
      if (Type == YSwitch)
      {
        if (MaxReading <= 512)
        {
          fastNoteOn(Note, min(127, MaxReading * 8));
        }
        //   else
        //    fastNoteOn(Channel, min(127, (MaxReading - 512) * 8)); //Dual??? ChokeNote

        MaxReading = -1;
        return;
      }
      //===============================

      //====================================================================
      if (State == Piezo_Time)
      {
        //Piezo
        if (Type == Piezo)
        {
          byte v = useCurve();

          fastNoteOn(Note, v);

          State = Mask_Time;
          /*
            //Piezo-Switch
            if (dual->Type == Switch && dual->State == Switch_Time )
            {
             fastNoteOn(dual->Channel, dual->Note, 127);
             dual->State = Mask_Time;
            }

            else if(TypeSensor[DualSensor(i)]==PIEZO && MaxReadingSensor[DualSensor(i)]> ThresoldSensor[DualSensor(i)]) //Piezo-Piezo
            {
              byte v=UseCurve(CurveSensor[DualSensor(i)],MaxReadingSensor[DualSensor(i)],CurveFormSensor[DualSensor(i)]);
              #if WAVTRIGGER
               wavTrigger(DualSensor(i),v);
              #endif
              fastNoteOn(ChannelSensor[DualSensor(i)],NoteSensor[DualSensor(i)],v);

              MaxReadingSensor[DualSensor(i)]=-1;  //Dual XTalk

            }*/
        }
        else //HH========================================
        {
          //??? dual != hhc
          byte note = Note;
          /*   if (MaxReading > HHThresoldSensor[3])
               note = HHNoteSensor[3];
             else if (MaxReading > HHThresoldSensor[2])
               note = HHNoteSensor[2];
             else if (MaxReading > HHThresoldSensor[1])
               note = HHNoteSensor[1];
             else if (MaxReading > HHThresoldSensor[0])
               note = HHNoteSensor[0];
          */
          //  fastNoteOn(note, useCurve());
        }//HH=======================

      }
    }
    //=======================
    byte Type: 4; //type
    byte State: 4; //state
    byte _pin;
    byte Note;
    union
    {
      byte ChokeNote;
      byte Gain;
    };

#if ENABLE_CHANNEL
    byte Channel;
#endif
    int antigo = 0;
    byte Thresold;
    byte ScanTime;
    byte MaskTime;
    byte Retrigger ;

    byte CurveForm;
    byte Curve: 4;
    byte XtalkGroup: 4;
    byte Xtalk;

    unsigned long Time;
    int MaxReading;
    int yn_1;

    byte useCurve()
    {
      int ret = 0;
      //float Xn=(float)Value;
      float f = ((float)CurveForm) / 32.0; //[1;127]->[0.;4.0]

      if (Curve == Linear)
      {
        ret = 0.5 + ((float)MaxReading * f / 8.0);
      }
      else
      {
        int i = MaxReading / 128;
        int m = MaxReading % 128;

        switch (Curve)
        {
          case Exp: ret = 0.5 + (((float)m * (_Exp[i + 1] - _Exp[i]) / 128.0) + _Exp[i]) * f; break;
          case Log: ret = 0.5 + (((float)m * (_Log[i + 1] - _Log[i]) / 128.0) + _Log[i]) * f; break;
          case Sigma: ret = 0.5 + (((float)m * (_Sigma[i + 1] - _Sigma[i]) / 128.0) + _Sigma[i]) * f; break;
          case Flat: ret = 0.5 + (((float)m * (_Flat[i + 1] - _Flat[i]) / 128.0) + _Flat[i]) * f; break;

          default: ret = i * 16; break; //Test mode
        }
      }

      if (ret <= 0) return 0;
      if (ret >= 127) return 127; //127
      return ret;
    }

    void scanHHC(byte pin, byte sensorReading)
    {
      if ((GlobalTime - Time) > MaskTime)
      {
        if (1)//(sensorReading > (/*yn_1*/MaxReading + Thresold) || sensorReading < (/*yn_1*/MaxReading - Thresold))
        {
           int fim = sensorReading;
          if (1)
          {

            sensorReading = constrain(sensorReading, minn, maxx);
            sensorReading =  map(sensorReading, minn, maxx, 0, 127);
            sensorReading = constrain(sensorReading, 0, 127);
            int fim = sensorReading;
           /* if (sensorReading < 25)
              fim = 0;
            else if (sensorReading < 50)
              fim = 40;
            else if (sensorReading < 80)
              fim = 75;
            else if (sensorReading < 107)
              fim = 100;
            else if (sensorReading <= 127)
              fim = 126;
              */
           // if (fim != antigo) {
              fastMidiCC(Note, fim);
             // fastNoteOn(Note, fim);

           // }
            antigo = fim;

            float m = (((float)MaxReading - (float)sensorReading) / ((float)Time - (float)GlobalTime)) * 100;

            MaxReading = sensorReading; //LastReading

            //Foot Splash
            //if (m > 0 && m > HHFootThresoldSensor[0])
            //State = Footsplash_Time;

            //FootClose
            //else if (m < 0 && -m > HHFootThresoldSensor[1])
            // State = Footclose_Time;

            Time = GlobalTime;
          }
        }
      }
    }
} Pin[NPin];
//===========================
