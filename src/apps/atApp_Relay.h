/**
@file

*/
/*
  Application example t

  Library::

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_Relay_
#define _Application_atApp_Relay_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include <Arduino.h>
#include "../services/atService_XYZ.h"
#include <esp_task_wdt.h>  
/* _____DEFINITIONS__________________________________________________________ */
#define CONTROL_PIN 4		   // Control pin relay
#define KEY_CLOSE "C9fJx8QvZ2" // Close key value to compare
#define KEY_OPEN "X7pLm4BkU1"  // Open key value to compare
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_Relay;
void atApp_Relay_Task_Func(void *parameter);

///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

enum{
	OFF = 0,
	ON = 1
} ;
/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_RELAY : public Application
{
public:
	App_RELAY();
	~App_RELAY();
	String receivedData = "";
	bool CMD = OFF;
protected:
private:
	static void App_RELAY_Pend();
	static void App_RELAY_Start();
	static void App_RELAY_Restart();
	static void App_RELAY_Execute();
	static void App_RELAY_Suspend();
	static void App_RELAY_Resume();
	static void App_RELAY_End();
	static void control_relay(int state);
} atApp_Relay;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_RELAY::App_RELAY(/* args */)
{
	_Pend_User = *App_RELAY_Pend;
	_Start_User = *App_RELAY_Start;
	_Restart_User = *App_RELAY_Restart;
	_Execute_User = *App_RELAY_Execute;
	_Suspend_User = *App_RELAY_Suspend;
	_Resume_User = *App_RELAY_Resume;
	_End_User = *App_RELAY_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"RELAY Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_RELAY::~App_RELAY()
{
}

/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_RELAY::App_RELAY_Pend()
{
	// atService_XYZ.Debug();
}
/**
 * This start function will init some critical function
 */
void App_RELAY::App_RELAY_Start()
{
	// init atXYZ Service in the fist running time
	// atService_XYZ.Run_Service();
	// Serial.begin(9600);
	// Serial.println("RS485 Listener Started");
	pinMode(CONTROL_PIN, OUTPUT);
	atApp_Relay.control_relay(OFF); // Set relay to OFF state
}
/**
 * Restart function of SNM  app
 */
void App_RELAY::App_RELAY_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_RELAY::App_RELAY_Execute()
{
	// if (Serial1.available())
	// {
	// 	// catching the incoming data
	// 	char incomingByte = Serial1.read();
	// 	if (incomingByte == '*')
	// 	{
	// 		receivedData = ""; // Reset buffer
	// 	}
	// 	else
	// 	{
	// 		receivedData += incomingByte;
	// 	}
	// }

	// // Chuyển sang switch-case để xử lý
	// if (atApp_Relay.receivedData.length() >= 10){
	// 	switch (atApp_Relay.receivedData[0]) // Kiểm tra ký tự đầu tiên
	// {
	// case 'X':
	// 	if (atApp_Relay.receivedData == KEY_OPEN)
	// 	{
	// 		digitalWrite(CONTROL_PIN, LOW);
	// 		vTaskDelay(50 / portTICK_PERIOD_MS);
	// 		atApp_Relay.receivedData = "";
	// 	}
	// 	break;

	// case 'C':
	// 	if (atApp_Relay.receivedData == KEY_CLOSE)
	// 	{
	// 		digitalWrite(CONTROL_PIN, HIGH);
	// 		vTaskDelay(50 / portTICK_PERIOD_MS);
	// 		atApp_Relay.receivedData = "";
	// 	}
	// 	break;

	// default:
	// 	atApp_Relay.receivedData = "";
	// 	break;
	// }
	// // Sau khi xử lý xong, xóa buffer
	// atApp_Relay.receivedData = "";
	// }
	if (atApp_Relay.CMD == ON)
	{
		atApp_Relay.control_relay(ON);
	}
	else
	{
		atApp_Relay.control_relay(OFF);
	}
	//vTaskDelay(1000 / portTICK_PERIOD_MS);
	esp_task_wdt_reset(); // Kick WDT để tránh reset
	if (atApp_Relay.User_Mode == APP_USER_MODE_DEBUG)
	{
	}
}
void App_RELAY::App_RELAY_Suspend() {}
void App_RELAY::App_RELAY_Resume() {}
void App_RELAY::App_RELAY_End() {}
void App_RELAY::control_relay(int state)
{
	if (state == ON)
	{
		digitalWrite(CONTROL_PIN, LOW);
	}
	else
	{
		digitalWrite(CONTROL_PIN, HIGH);
	}
}
void atApp_Relay_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_Relay.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
#endif