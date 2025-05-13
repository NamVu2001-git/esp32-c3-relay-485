/**
@file

*/
/*
  Application example t

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_WDT_
#define _Application_atApp_WDT_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_XYZ.h"
#include <esp_task_wdt.h>  

/* _____DEFINITIONS__________________________________________________________ */
#define WDT_TIMEOUT 5 
#define WDT_MONITOR_TASK Task_atApp_Relay 
#define WDT_DELAY_MS 1000 

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_WDT;  
void atApp_WDT_Task_Func(void *parameter);

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_WDT : public Application
{
public:
  	App_WDT();
 	~App_WDT();
protected:
private:
  	static void  App_WDT_Pend();
	static void  App_WDT_Start();
	static void  App_WDT_Restart();
	static void  App_WDT_Execute();
	static void  App_WDT_Suspend();
	static void  App_WDT_Resume();	  
	static void  App_WDT_End();
} atApp_WDT ;

/**
 * Constructor
 */
App_WDT::App_WDT(/* args */)
{
  	_Pend_User 	     = *App_WDT_Pend;
	_Start_User 	 = *App_WDT_Start;
	_Restart_User 	 = *App_WDT_Restart;
	_Execute_User 	 = *App_WDT_Execute;
	_Suspend_User	 = *App_WDT_Suspend;
	_Resume_User	 = *App_WDT_Resume;
	_End_User	     = *App_WDT_End;

	ID_Application = 2; 
	Name_Application = (char*)"Watchdog Application";
}

/**
 * Destructor
 */
App_WDT::~App_WDT()
{
	
}

/**
 * Pend to start
 */
void  App_WDT::App_WDT_Pend()
{
    
}

/**
 * This start function will init some critical function 
 */
void  App_WDT::App_WDT_Start()
{
	// ---- Khởi tạo Watchdog Timer ----
	esp_task_wdt_init(WDT_TIMEOUT, true);    
	// Add the tasks that you want to monitor
	esp_task_wdt_add(WDT_MONITOR_TASK); 
}  

/**
 * Restart function of App_WDT
 */
void  App_WDT::App_WDT_Restart()
{
	esp_task_wdt_delete(WDT_MONITOR_TASK);
	esp_task_wdt_add(WDT_MONITOR_TASK);
}

/**
 * Execute function of App_WDT
 */
void  App_WDT::App_WDT_Execute()
{	
	// // ---- Kiểm tra và kick Watchdog Timer ----
	// if (esp_task_wdt_status(WDT_MONITOR_TASK) == ESP_OK)
	// {
		// esp_task_wdt_reset(); // Kick WDT để tránh reset
	// }
	vTaskSuspend(Task_atApp_WDT);
	if (atApp_WDT.User_Mode == APP_USER_MODE_DEBUG)
	{

	}   

}

/**
 * Suspend the WDT monitoring
 */
void  App_WDT::App_WDT_Suspend()
{
	
}

/**
 * Resume the WDT monitoring
 */
void  App_WDT::App_WDT_Resume()
{
	
}

/**
 * End the WDT monitoring
 */
void  App_WDT::App_WDT_End()
{

}

/**
 * Task function for App_WDT
 */
void atApp_WDT_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_WDT.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(WDT_DELAY_MS / portTICK_PERIOD_MS);
	}
}
#endif
