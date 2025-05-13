/**
@file

*/
/*
  Application example t

  Library::

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_Blink_
#define _Application_atApp_Blink_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include <Arduino.h>
#include "../services/atService_XYZ.h"
/* _____DEFINITIONS__________________________________________________________ */
#define LED_PIN 8			// GPIO pin for LED
#define BLINK_INTERVAL 1000 // Blink interval in milliseconds (0.5s)
#define KEY_CLOSE "C9fJx8QvZ2" // Close key value to compare
#define KEY_OPEN "X7pLm4BkU1"  // Open key value to compare
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_Blink;
void atApp_Blink_Task_Func(void *parameter);

///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_BLINK : public Application
{
public:
	App_BLINK();
	~App_BLINK();
	String receivedData = ""; // Buffer to store incoming data
	bool comment = false;  // Status of the application
protected:
private:
	static void App_BLINK_Pend();
	static void App_BLINK_Start();
	static void App_BLINK_Restart();
	static void App_BLINK_Execute();
	static void App_BLINK_Suspend();
	static void App_BLINK_Resume();
	static void App_BLINK_End();
} atApp_Blink;

/**
 * This function will be automatically called when an object is created by this class
 */
App_BLINK::App_BLINK(/* args */)
{
	_Pend_User = *App_BLINK_Pend;
	_Start_User = *App_BLINK_Start;
	_Restart_User = *App_BLINK_Restart;
	_Execute_User = *App_BLINK_Execute;
	_Suspend_User = *App_BLINK_Suspend;
	_Resume_User = *App_BLINK_Resume;
	_End_User = *App_BLINK_End;

	// change the ID of application
	ID_Application = 2;
	// change the application name
	Name_Application = (char *)"BLINK Application";
}
/**
 * This function will be automatically called when the object of class is deleted
 */
App_BLINK::~App_BLINK()
{
}

/**
 * Pend to start is the first task of this application it will do prerequisite condition.
 */
void App_BLINK::App_BLINK_Pend()
{
	// atService_XYZ.Debug();
}

/**
 * This start function will init some critical function
 */
void App_BLINK::App_BLINK_Start()
{
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);
}

/**
 * Restart function of SNM  app
 */
void App_BLINK::App_BLINK_Restart()
{
}

/**
 * Execute function of SNM app
 */
void App_BLINK::App_BLINK_Execute()
{
	// if (atApp_Blink.receivedData.length() >= 10)
	// {
	// 	// Chuyển sang switch-case để xử lý
	// 	switch (atApp_Blink.receivedData[0]) // Kiểm tra ký tự đầu tiên
	// 	{
	// 	case 'X':
	// 		if (atApp_Blink.receivedData == KEY_OPEN)
	// 		{
	// 			digitalWrite(8, LOW);
	// 			vTaskDelay(50 / portTICK_PERIOD_MS);
	// 		}
	// 		break;

	// 	case 'C':
	// 		if (atApp_Blink.receivedData == KEY_CLOSE)
	// 		{
	// 			digitalWrite(8, HIGH);
	// 			vTaskDelay(50 / portTICK_PERIOD_MS);
	// 		}
	// 		break;

	// 	default:
	// 		atApp_Blink.receivedData = "";
	// 		break;
	// 	}
	// 	// Sau khi xử lý xong, xóa buffer
	// 	atApp_Blink.receivedData = "";
	// }
	// digitalWrite(LED_PIN, LOW);						 // Turn off LED
	// vTaskDelay(BLINK_INTERVAL / portTICK_PERIOD_MS); // Wait for the blink interval
	// digitalWrite(LED_PIN, HIGH);					 // Turn on LED
	// vTaskDelay(BLINK_INTERVAL / portTICK_PERIOD_MS); // Wait for the blink interval
	if(atApp_Blink.comment == true)
	{
		digitalWrite(LED_PIN, LOW);	
		vTaskDelay(BLINK_INTERVAL / portTICK_PERIOD_MS); // Wait for the blink interval
		digitalWrite(LED_PIN, HIGH);// Turn off LED
		atApp_Blink.comment = false;
	}
	digitalWrite(LED_PIN, LOW);	
	vTaskDelay(BLINK_INTERVAL/10 / portTICK_PERIOD_MS); // Wait for the blink interval
	digitalWrite(LED_PIN, HIGH);// Turn off LED
	// else
	// {
	// 	digitalWrite(LED_PIN, HIGH);
	// }
}
void App_BLINK::App_BLINK_Suspend()
{
}

void App_BLINK::App_BLINK_Resume()
{
}

void App_BLINK::App_BLINK_End()
{
}

void atApp_Blink_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_Blink.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
#endif

// Define the static member
