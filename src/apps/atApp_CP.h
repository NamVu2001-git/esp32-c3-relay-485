/**
@file

*/
/*
  Application example t

  Library::

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_CP_
#define _Application_atApp_CP_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_XYZ.h"
#include "../apps/atApp_Relay.h"
#include "../apps/atApp_485.h"
#include "../apps/atApp_Blink.h"
// #include "../apps/atApp_Blink.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_CP;
void atApp_CP_Task_Func(void *parameter); ///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_CP : public Application
{
public:
	App_CP();
	~App_CP();
	bool atStatus;

protected:
private:
	static void App_CP_Pend();
	static void App_CP_Start();
	static void App_CP_Restart();
	static void App_CP_Execute();
	static void App_CP_Suspend();
	static void App_CP_Resume();
	static void App_CP_End();
} atApp_CP;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_CP::App_CP(/* args */)
{
	_Pend_User = *App_CP_Pend;
	_Start_User = *App_CP_Start;
	_Restart_User = *App_CP_Restart;
	_Execute_User = *App_CP_Execute;
	_Suspend_User = *App_CP_Suspend;
	_Resume_User = *App_CP_Resume;
	_End_User = *App_CP_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"CP Application";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_CP::~App_CP()
{
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_CP::App_CP_Pend()
{
	// atService_XYZ.Debug();
}
/**
 * This start function will init some critical function
 */
void App_CP::App_CP_Start()
{
	// init atXYZ Service in the fist running time
	// atService_XYZ.Run_Service();
}
/**
 * Restart function of SNM  app
 */
void App_CP::App_CP_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_CP::App_CP_Execute()
{
	// atApp_485.receivedData = atApp_Relay.receivedData;
	// atApp_485.receivedData = atApp_Blink.receivedData;
	// if (atApp_485.receivedData.length() >= 1)
	// {
	// switch (atApp_485.receivedData) // Kiểm tra ký tự đầu tiên
	// {
	// case 'X':
	if (atApp_485.receivedData == KEY_OPEN)
	{
		// open bus
		atApp_485.receivedData = "";
		atApp_CP.atStatus = true;
		atApp_Relay.CMD = ON;
		atApp_Blink.comment = true;
	}
	// break;

// case 'C':
	if (atApp_485.receivedData == KEY_CLOSE)
	{
		// close bus
		atApp_Relay.receivedData = "";
		atApp_CP.atStatus = false;
		atApp_Relay.CMD = OFF;
		atApp_Blink.comment = true;

	}
		// break;

	
	// Sau khi xử lý xong, xóa buffer
	atApp_485.receivedData = "";
	// }
}
void App_CP::App_CP_Suspend() {}
void App_CP::App_CP_Resume() {}
void App_CP::App_CP_End() {}
void atApp_CP_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_CP.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}
#endif