// Template_Application_ESP32_V2.0

#include "../src/apps/atApp_ABC.h"
#include "../src/apps/atApp_Relay.h"
#include "../src/apps/atApp_WDT.h"
#include "../src/apps/atApp_Blink.h"
#include "../src/apps/atApp_CP.h"
#include "../src/apps/atApp_485.h"

void setup() {

// Serial.begin(115200);
// Serial.printf("Flash size : %f",ESP.getFlashChipSize());


// uncomment to put the app in debug mod
   atApp_WDT.Debug();
  // atApp_RTC.Debug();
  // atApp_Wifi.Debug();
  // atApp_MB_RTU_SL.Debug();
  // atApp_MB_TCP_MA.Debug();
  // atApp_MB_TCP_SL.Debug();
  // atApp_INVT.Debug();
  // atApp_CD.Debug();
  // atApp_SGP30.Debug();
  // atApp_SHT30.Debug();
  // atApp_ADE.Debug();
  // atApp_exDELAY.Debug();
  // atApp_DELAY.Debug();
  // atApp_OTA.Debug();

  // atApp_SNM.Debug();
  // atApp_DID.Debug();

  // atApp_CP.Debug();
  
//--------------------------------------------------------------------Tasks table ----------------------------------------------------------------------------------//     
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// || Creation           ||     Task function         ||     PC name                    || heap size  || Parameter || Priority  || Task handle          || CoreID   ||
  
  xTaskCreatePinnedToCore(  atApp_Relay_Task_Func       , "atApp_Relay_Application"         ,  2048      ,     NULL    ,   2       , &Task_atApp_Relay       ,    0     );
  xTaskCreatePinnedToCore(  atApp_WDT_Task_Func       , "atApp_WDT_Application"         ,  2048      ,     NULL    ,   2       , &Task_atApp_WDT       ,    0     );
  xTaskCreatePinnedToCore(  atApp_Blink_Task_Func       , "atApp_Blink_Application"         ,  2048      ,     NULL    ,   2       , &Task_atApp_Blink       ,    0     );
  xTaskCreatePinnedToCore(  atApp_CP_Task_Func       , "atApp_CP_Application"         ,  10000      ,     NULL    ,   2       , &Task_atApp_CP       ,    0     );
  xTaskCreatePinnedToCore(  atApp_485_Task_Func       , "atApp_485_Application"         ,  2048      ,     NULL    ,   2       , &Task_atApp_485       ,    0     );

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//


// Some tasks will be suspended after initting 
  // vTaskSuspend(Task_atApp_OTA);
  // vTaskSuspend(Task_atApp_MB_TCP_MA);
  // vTaskSuspend(Task_atApp_DID);
  // vTaskSuspend(Task_atApp_SNM);
}
void loop() {}
