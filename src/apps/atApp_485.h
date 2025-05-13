/**
@file

*/
/*
  Application example t

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_485_
#define _Application_atApp_485_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_XYZ.h"
/* _____DEFINITIONS__________________________________________________________ */
#define RS485_RX_PIN 10		   // RX pin UART1
#define RS485_TX_PIN 9		   // TX pin UART1
#define CONTROL_PIN 4		   // Control pin relay
#define BAUD_RATE 9600		   // baud rate
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_485;  
void atApp_485_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */
#define STARt_KEY_CHAR '*'
#define END_KEY_CHAR '#'
/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_485 : public Application
{
public:
  	App_485();
 	~App_485();
	String receivedData = "";
protected:
private:
	
  	static void  App_485_Pend();
	static void  App_485_Start();
	static void  App_485_Restart();
	static void  App_485_Execute();
	static void  App_485_Suspend();
	static void  App_485_Resume();	  
	static void  App_485_End();
} atApp_485 ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_485::App_485(/* args */)
{
  	_Pend_User 	     = *App_485_Pend;
	_Start_User 	 = *App_485_Start;
	_Restart_User 	 = *App_485_Restart;
	_Execute_User 	 = *App_485_Execute;
	_Suspend_User	 = *App_485_Suspend;
	_Resume_User	 = *App_485_Resume;
	_End_User	     = *App_485_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"485 Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_485::~App_485()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_485::App_485_Pend()
{
    // atService_XYZ.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_485::App_485_Start()
{
	Serial1.begin(BAUD_RATE, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	// init atXYZ Service in the fist running time
	// atService_XYZ.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_485::App_485_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_485::App_485_Execute()
{	
	while (Serial1.available())
	{
		// catching the incoming data
		char incomingByte = Serial1.read();
		if (incomingByte == STARt_KEY_CHAR)
		{
			atApp_485.receivedData = ""; // Reset buffer
		}
		else
		{

			atApp_485.receivedData += incomingByte;
		}
	}
	// atService_XYZ.Run_Service();
    if(atApp_485.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_485::App_485_Suspend(){}
void  App_485::App_485_Resume(){}	  
void  App_485::App_485_End(){}
void atApp_485_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_485.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(100/ portTICK_PERIOD_MS);
  }
}
#endif