//#######################################################################################################
//#################################### Plugin 002: Analog ###############################################
//#######################################################################################################

// Adapted from ESP Easy, changes:
//   WebServer.arg() -> WebServerarg()
//   port selection as we have a lot of analog ports here...

#define PLUGIN_002
#define PLUGIN_ID_002         2
#define PLUGIN_NAME_002       "Analog input"
#define PLUGIN_VALUENAME1_002 "Analog"
boolean Plugin_002(byte function, struct EventStruct *event, String& string)
{
  boolean success = false;

  switch (function)
  {

    case PLUGIN_DEVICE_ADD:
      {
        Device[++deviceCount].Number = PLUGIN_ID_002;
        Device[deviceCount].Type = DEVICE_TYPE_ANALOG;
        Device[deviceCount].VType = SENSOR_TYPE_SINGLE;
        Device[deviceCount].Ports = 1;
        Device[deviceCount].PullUpOption = false;
        Device[deviceCount].InverseLogicOption = false;
        Device[deviceCount].FormulaOption = true;
        Device[deviceCount].ValueCount = 1;
        Device[deviceCount].SendDataOption = true;
        Device[deviceCount].TimerOption = true;
        Device[deviceCount].GlobalSyncOption = true;
        break;
      }

    case PLUGIN_GET_DEVICENAME:
      {
        string = F(PLUGIN_NAME_002);
        break;
      }

    case PLUGIN_GET_DEVICEVALUENAMES:
      {
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[0], PSTR(PLUGIN_VALUENAME1_002));
        break;
      }
      
    case PLUGIN_READ:
      {
        int value = analogRead(Settings.TaskDevicePort[event->TaskIndex]);
        UserVar[event->BaseVarIndex] = (float)value;
        String log = F("ADC  : Analog port ");
        log += Settings.TaskDevicePort[event->TaskIndex];
        log += F(" value: ");
        log += value;
        addLog(LOG_LEVEL_INFO,log);
        success = true;
        break;
      }
  }
  return success;
}
