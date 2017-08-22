/*
    Copyright 2008 David House

    This file is part of Countenance.

    Countenance is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Countenance is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Countenance.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Commands.h"

pascal void TickBatteryAWindow();

pascal OSStatus BatteryCWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) {

	printf("Recieved event from Battery C Window\n");

	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID from Menu. Ex: About box had commandID "abtb"
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {
			
		case 'NXBC': printf("Battery C Next....\n");
			
			// Save results in ratings
			if(BatteryCHandler()){
				
				// Clean up all windows
				ResetBatteryCWindow();
				
				// Attempt to cycle to next model
				bool attempt = currentTrial.nextModel();
				
				// If no model, end trial
				if(! attempt){
					printf("Ending Battery C\n");
					
					// Close trial window
					ShowHide(gBatteryCWindow, FALSE);
					
					// Open Survey Window
					ShowHide(gSurveyWindow, TRUE);
					SelectWindow(gSurveyWindow);
					
				}
				
				// If a new model was found...
				else if (attempt){
					
					// Hide Model & Rating Window
					ShowHide(gBatteryCWindow,FALSE);
					
					// Draw new model
					DrawBatteryCCurrentModel();
					
					// Cycle windows
					ShowHide(gBatteryCWindow,TRUE);
					SelectWindow(gBatteryCWindow);
					
				}
			}
			
			else{
				// Display notice
				DialogRef theItem;
				DialogItemIndex itemIndex;
				
				CreateStandardAlert(kAlertNoteAlert,  
									CFSTR("Notice.\n"),  
									CFSTR("You must choose all ratings to continue.\n"),
									NULL, &theItem); 
				
				RunStandardAlert (theItem, NULL, &itemIndex);
			}
			
			
		default:
			break;		
	}
	
	result = noErr;
	return result;
}

pascal OSStatus BatteryACompetenceWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) {
	
	printf("Recieved event from A-Competence Window\n");
	
	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID from Menu. Ex: About box had commandID "abtb"
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {

		case 'NXA1': printf("Going to Window 2.\n");
			
			// Save rating based on currentModel
			if(BatteryAHandler1()){
			
				// Cycle to window2
				ShowHide(gBatteryAWindow1, FALSE);
				ShowHide(gBatteryAWindow2, TRUE);
				SelectWindow(gBatteryAWindow2);
				
			}
			
			else{
				
				// Display notice
				DialogRef theItem;
				DialogItemIndex itemIndex;
				
				CreateStandardAlert(kAlertNoteAlert,  
									CFSTR("Notice\n"),  
									CFSTR("You must choose a rating to continue.\n"),
									NULL, &theItem); 
				
				RunStandardAlert (theItem, NULL, &itemIndex);
			}

			result = noErr;
	}
	
	return result;	
}

pascal OSStatus BatteryATrustWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) {
	
	printf("Recieved event from A-Trust Window\n");

	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID from Menu. Ex: About box had commandID "abtb"
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {

		case 'NXA2': printf("Going to Window 3.\n");
			
			// Save rating based on currentModel
			if(BatteryAHandler2()){
			
				// Cycle to window3
				ShowHide(gBatteryAWindow2, FALSE);
				ShowHide(gBatteryAWindow3, TRUE);
				SelectWindow(gBatteryAWindow3);
			}
			
			else{
				
				// Display notice
				DialogRef theItem;
				DialogItemIndex itemIndex;
				
				CreateStandardAlert(kAlertNoteAlert,  
									CFSTR("Notice\n"),  
									CFSTR("You must choose a rating to continue.\n"),
									NULL, &theItem); 
				
				RunStandardAlert (theItem, NULL, &itemIndex);
				
			}
			
			result = noErr;
	}
	
	return result;
}

pascal OSStatus BatteryALikeableWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) {
	
	printf("Recieved event from A-Likeable Window\n");
	
	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID from Menu. Ex: About box had commandID "abtb"
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {
		
		case 'NXA3': printf("Going to Window 4.\n");
			
			// Save rating based on currentModel
			if(BatteryAHandler3()){
			
				// Cycle to window4
				ShowHide(gBatteryAWindow3, FALSE);
				ShowHide(gBatteryAWindow4, TRUE);
				SelectWindow(gBatteryAWindow4);
			}
			
			else{
				
				// Display notice
				DialogRef theItem;
				DialogItemIndex itemIndex;
				
				CreateStandardAlert(kAlertNoteAlert,  
									CFSTR("Notice.\n"),  
									CFSTR("You must choose a rating to continue.\n"),
									NULL, &theItem); 
				
				RunStandardAlert (theItem, NULL, &itemIndex);
			}
			
			result = noErr;
	}
	
	return result;
}

pascal OSStatus BatteryAAttractivenessWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) {
	
	printf("Recieved event from A-Attractive Window\n");
	
	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID from Menu. Ex: About box had commandID "abtb"
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {
		
		case 'NXA4': printf("Thinking About Continuing...\n");
			
			// Save results in ratings
			if(BatteryAHandler4()){
			
				// Clean up all windows
				ResetAllBatteryAWindows();
				
				// Attempt to cycle to next model
				bool attempt = currentTrial.nextModel();
				
				// If no model, end trial
				if(! attempt){
					printf("Ending Battery\n");
					
					// Close trial window
					ShowHide(gBatteryAWindow, FALSE);
					ShowHide(gBatteryAWindow4, FALSE);
					
					// Open Survey Window
					ShowHide(gSurveyWindow, TRUE);
					SelectWindow(gSurveyWindow);	
				}
				
				// If a new model was found...
				else if (attempt){
					
					// Hide Model & Rating Window
					ShowHide(gBatteryAWindow,FALSE);
					ShowHide(gBatteryAWindow4,FALSE);
					
					// Draw new model
					DrawBatteryACurrentModel();
					
					if(currentTrial.trialMode == 1){
						// Cycle windows
						ShowHide(gBatteryAWindow,TRUE);
						ShowHide(gBatteryAWindow1,TRUE);
						SelectWindow(gBatteryAWindow1);
					}
					
					else if (currentTrial.trialMode == 2){
						TickBatteryAWindow();
						ShowHide(gBatteryAWindow1,TRUE);
						SelectWindow(gBatteryAWindow1);
					}
				}
			}
			
			else{
				
				// Display notice
				DialogRef theItem;
				DialogItemIndex itemIndex;
				
				CreateStandardAlert(kAlertNoteAlert,  
									CFSTR("Notice.\n"),  
									CFSTR("You must choose a rating to continue.\n"),
									NULL, &theItem); 
				
				RunStandardAlert (theItem, NULL, &itemIndex);
			}
			
			result = noErr;
	}
	
	return result;
}

// Main Window (+Menu) Event Handler
// Handles events from the Main Window & Menu
pascal OSStatus MainWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) { 
	
	printf("Recieved event from Main Window\n");
	
	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID from Menu. Ex: About box had commandID "abtb"
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	// switch handles every possible commandID (in this case, Menu item)
	printf("Command: %d\n",command.commandID);
    	switch (command.commandID) {
		
		case StartTrial1: printf("Beginning Trial.\n");
			// Init Group List
			ClearTrialGroupListDataBrowser();
			InitializeTrialGroupListDataBrowser();
			// Clear New Trial Window
			ResetNewTrialWindow();
			currentTrial.ResetTrial();
			
			ShowHide(window, FALSE);
			ShowHide(gNewTrialWindow, TRUE);
			SelectWindow(gNewTrialWindow);
			result = noErr;
			break;
		
		case EditModelList: printf("Editing Model List.\n");
			ShowHide(window, FALSE);
			ShowHide(window2, TRUE);
			SelectWindow(window2);
			result = noErr;
			break;
			
		case EditGroupList: printf("Editing Group List.\n");
			ShowHide(window, FALSE);
			ShowHide(gGroupListWindow, TRUE);
			SelectWindow(gGroupListWindow);
			result = noErr;
			break;
	
		default: break;
	}

    return result; 
}

// Model List Window Event Handler
// Handles events from the Model List Window
pascal OSStatus ModelListWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) { 
	
	printf("Recieved event from Model List Window\n");

	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID of event.
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
						   sizeof (HICommand), NULL, &command);   
		
	// switch handles every possible commandID
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {

		case AddModelToList: printf("Adding model to list.\n");
				
			ShowHide(window3, TRUE);
			SelectWindow (window3);
			result = noErr;
			break;
				
		case ViewModel: printf("Viewing Model.\n");
				
			if(ViewModelCommandHandler()){
				ShowHide(window5, TRUE);
				SelectWindow (window5);
			}

			result = noErr;
			break;
				
		case DeleteModelFromList: printf("Removing model from list.\n");
			if(DeleteModelCommandHandler()){
				ClearModelDataBrowser();
				InitializeModelDataBrowser ();
				ClearModelGroupDataBrowser();
				InitializeModelGroupDataBrowser();
				masterModelList.SaveModels();
			}

			result = noErr;
			break;
				
		case FinishedWithWindow: printf("Hiding Window.\n");
			ShowHide(window2, FALSE);
			ShowHide(window, TRUE);
			SelectWindow (window);  
			result = noErr;
			break;
					
		default: break;
	}
		
	return result; 
} 

// Model List Window State Change Event Handler
// Handles Window Close Event from the Model List Window
pascal OSStatus ModelListWindowCloseEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) { 
	
	printf("Recieved window close event from Model List Window\n");
	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	UInt32 eventKind;
	
	// Returns the kind of event
	eventKind = GetEventKind (event);              
	
	// If event is window close, then hide window
	if (eventKind == kEventWindowClose){ 
		
		printf("Hiding Window.\n");

		// Hides window
		ShowHide ( (WindowRef) userData, FALSE);              
		
		// Returns focus to Main Window
		ShowHide(window, TRUE);
		SelectWindow (window);                 
		
		// Tells result that something was handled
		result =  noErr; 
	}
	
	return result;
}

// Add Model Window Event Handler
// Handles events from the Add Model Window
pascal OSStatus AddModelWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) { 
	
	printf("Recieved event from Add Model Window\n");

	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID of event.
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	// switch handles every possible commandID
	printf("Command: %d\n",command.commandID);

	switch (command.commandID) {
		
		case ConfirmAddModel: printf("Adding model.\n");
			if (! AddModelCommandHandler())
				ShowHide(window4, TRUE);
			else
				InitializeModelDataBrowser();
			
			ShowHide(window3, FALSE);
			SelectWindow (window2); 
			result = noErr;
			break;
			
		case GetPictureName: printf("Getting Model Picture Info.\n");
			GetPictureNameCommandHandler();
			result = noErr;
			break;
			
		case CancelAddModel: printf("Cancelled Transaction.\n");
			CancelModelCommandHandler();
			ShowHide(window3, FALSE);
			SelectWindow (window2);  
			result = noErr;
			break;
			
		default: break;
	}
	
    return result; 
} 

// Add Model Window State Change Event Handler
// Handles Window Close Event from the Add Model Window
pascal OSStatus AddModelWindowCloseEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) { 
	
	printf("Recieved window close event from Add Model Window\n");
	
	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	UInt32 eventKind;
	
	// Returns the kind of event
	eventKind = GetEventKind (event);              
	
	// If event is window close, then hide window
	if (eventKind == kEventWindowClose){ 
		
		printf("Hiding Window.\n");
		
		// Reset Fields
		resetAddModelDialog();
		
		// Hides window
		ShowHide ( (WindowRef) userData, FALSE);              
		
		// Returns focus to Main Window
		SelectWindow (window2);                 
		
		// Tells result that something was handled
		result =  noErr; 
	}
	
	return result;
}

pascal OSStatus SurveyWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) { 
	
	printf("Recieved event from Survey Window\n");

	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID from Menu. Ex: About box had commandID "abtb"
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	// switch handles every possible commandID (in this case, Menu item)
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {
			
		case CloseSurvey: printf("Done with Survey.\n");
			
			// Save Survey Information
			if(SurveyCommandHandler()){
			
				// Save responses
				if(currentTrial.trialMode == 1)
					currentTrial.SaveBatteryA();
				
				else if (currentTrial.trialMode == 2)
					currentTrial.SaveBatteryB();
				
				else if(currentTrial.trialMode == 3)
					currentTrial.SaveBatteryC();
				
				// Hide Window
				ShowHide(gSurveyWindow, FALSE);
					
				// Reset window
				ClearSurveyWindow();
					
				// Reset trial
				currentTrial.ResetTrial();
				
				// Display notice
				DialogRef theItem;
				DialogItemIndex itemIndex;
				
				CreateStandardAlert(kAlertNoteAlert,  
									CFSTR("Thank you.\n"),  
									CFSTR("This concludes the trial.\n"),
									NULL, &theItem); 
				
				RunStandardAlert (theItem, NULL, &itemIndex);
				
				// Hide Survey Window
				ShowHide(gSurveyWindow, FALSE);
					
				// Open main window
				ShowHide(window, TRUE);
				SelectWindow(window);
			}
			
			else{
				
				// Display notice
				DialogRef theItem;
				DialogItemIndex itemIndex;
				
				CreateStandardAlert(kAlertNoteAlert,  
									CFSTR("Notice\n"),  
									CFSTR("Please complete the survey to continue.\n"),
									NULL, &theItem); 
				
				RunStandardAlert (theItem, NULL, &itemIndex);
				
			}
			
			result = noErr;
			break;
			
		default: break;	
	}

	return result;
}


// Add Model Error Alert Window Event Handler
// Handles events from the Add Model Error Alert Window
pascal OSStatus AddErrorWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) { 
	
	printf("Recieved event from Add Error Alert\n");
	
	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID of event.
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	// switch handles every possible commandID
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {
		case ClearAlert: printf("Clearing Dialog\n");
			// Reset Fields
			resetAddModelDialog();
			ShowHide(window4, FALSE);
			SelectWindow (window2); 
			result = noErr;
			break;
			
		default: break;
	}
	
    return result; 
} 

pascal OSStatus ViewModelWindowEventHandler(EventHandlerCallRef handlerRef, EventRef event, void *userData) {

	printf("Recieved event from View Model Window\n");
	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID from Menu. Ex: About box had commandID "abtb"
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	// switch handles every possible commandID (in this case, Menu item)
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {
		case CloseViewModel: printf("Closing Window.\n");
			ShowHide(window5, FALSE);
			ShowHide(window2, TRUE);
			SelectWindow(window2);
			result = noErr;
			break;
			
		default: break;
	} 

    return result; 
}

pascal OSStatus GroupListWindowEventHandler(EventHandlerCallRef handlerRef, EventRef event, void *userData) {

	printf("Recieved event from Group List Window\n");

	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID of event.
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	// switch handles every possible commandID
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {
		case AddGrouptoList: printf("Adding group to list.\n");
			
			ShowHide(gAddGroupWindow, TRUE);
			SelectWindow (gAddGroupWindow);
			result = noErr;
			break;
			
		case EditGroupinList: printf("Editing group.\n");
			// Get selected group ID; if none, print error
			// Pass selected group ID to command handler
			// If get selected id returns true, initialize both lists and show
			// else, return error message and break pico
			
			groupID = GetGroupSelection();
			if(groupID != -1){
				printf("ID: %d\n", groupID);
				groupIndex = masterGroupList.GetIndexFromID(groupID);
				
				if(groupIndex != -1){
					printf("INDEX IS %d\n", groupIndex);
				
					ClearModelGroupDataBrowser();
					InitializeModelGroupDataBrowser();
				
					ClearGroupMemberDataBrowser();
					InitializeGroupMemberDataBrowser(groupIndex);
				
					// init both lists
					ShowHide(gEditGroupWindow, TRUE);
					SelectWindow (gEditGroupWindow);
				}
			}
			
			result = noErr;
			break;
			
		case DeleteGroupfromList: printf("Removing group from list.\n");
			if(DeleteGroupCommandHandler()){
				ClearGroupListDataBrowser();
				InitializeGroupListDataBrowser ();
				masterGroupList.SaveGroups();
			}

			result = noErr;
			break;
			
		case CloseGroupList: printf("Hiding Window.\n");
			ShowHide(gGroupListWindow, FALSE);
			ShowHide(window, TRUE);
			SelectWindow (window);  
			result = noErr;
			break;
			
		default: break;
	}
	
    return result;	
}

// Group List Window State Change Event Handler
// Handles Window Close Event from the Group List Window
pascal OSStatus GroupListWindowCloseEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) { 
	
	printf("Recieved window close event from Group List Window\n");

	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	UInt32 eventKind;
	
	// Returns the kind of event
	eventKind = GetEventKind (event);              
	
	// If event is window close, then hide window
	if (eventKind == kEventWindowClose){ 

		printf("Hiding Window.\n");
		
		// Reset Fields
		//resetAddModelDialog();
		
		// Hides window
		ShowHide ( (WindowRef) userData, FALSE);     
		
		// Shows main window
		ShowHide ( window, TRUE); 
		
		// Returns focus to Main Window
		SelectWindow (window);                 
		
		// Tells result that something was handled
		result =  noErr; 
	}
	
	return result;
}

pascal OSStatus AddGroupWindowEventHandler(EventHandlerCallRef handlerRef, EventRef event, void *userData) {
	
	printf("Recieved event from Add Group Window\n");

	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID of event.
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	// switch handles every possible commandID
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {
		case ConfirmAddGroup: printf("Adding group to list.\n");
			
			if(AddGroupCommandHandler()){
				ClearGroupListDataBrowser();
				InitializeGroupListDataBrowser();
				masterGroupList.SaveGroups();
			}
			ShowHide(gAddGroupWindow, FALSE);
			SelectWindow (gGroupListWindow);
			result = noErr;
			break;
			
		case CancelAddGroup: printf("Cancelled Transaction.\n");
			
			CancelAddGroupCommandHandler();
			ShowHide(gAddGroupWindow, FALSE);
			SelectWindow (gGroupListWindow);  
			result = noErr;
			break;
			
		default: printf("default.\n");break;
	}
	
    return result;
}

pascal OSStatus EditGroupWindowEventHandler(EventHandlerCallRef handlerRef, EventRef event, void *userData) {
	
	printf("Recieved event from Edit Group Window\n");

	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID of event.
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	// switch handles every possible commandID
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {
		case AddToGroupButton: printf("Adding model to group.\n");
			
			if(AddGroupMemberCommandHandler()){
				ClearGroupMemberDataBrowser();
				InitializeGroupMemberDataBrowser(groupIndex);
				masterGroupList.SaveGroups();
			}
			
			result = noErr;
			break;
			
		case DeleteFromGroupButton: printf("Removing model from group.\n");
			
			if(DeleteGroupMemberCommandHandler()){
				ClearGroupMemberDataBrowser();
				InitializeGroupMemberDataBrowser(groupIndex);
				masterGroupList.SaveGroups();
			}
			
			result = noErr;
			break;
			
		case DoneWithEditGroup: printf("Closing edit group window.\n");

			ShowHide(gEditGroupWindow, FALSE);
			SelectWindow(gGroupListWindow);
			result = noErr;
			break;
				
		default: printf("default.\n");break;
	}
	
	return result;
}

// New Trial Window Event Handler
// Handles events from the New Trial window
pascal OSStatus NewTrialWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) { 
	
	int runTrial = 0;
	
	printf("Recieved event from New Trial Window\n");
	
	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID from Menu. Ex: About box had commandID "abtb"
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	// switch handles every possible commandID (in this case, Menu item)
	printf("Command: %d\n",command.commandID);
	switch (command.commandID) {
		case BeginTrial: printf("Beginning New Trial.\n");
			
			runTrial = BeginNewTrialCommandHandler();
			
			if(runTrial == 1){
				printf("Running Trial 1.\n");
				currentTrial.trialMode=1;
				
				// Cycle currentModel to a new model
				if(currentTrial.nextModel()){
				
					// Draw the model into Battery A pic window
					DrawBatteryACurrentModel();
					
					// Hide old windows, show battery A window and battery A window 1
					ShowHide(gNewTrialWindow, FALSE);
					ShowHide(gBatteryAWindow, TRUE);
					ShowHide(gBatteryAWindow1, TRUE);
					SelectWindow(gBatteryAWindow1);
				}
			}
			
			else if(runTrial == 2){
				printf("Running Trial 2.\n");
				currentTrial.trialMode = 2;
				
				// Cycle currentModel to a new model
				if(currentTrial.nextModel()){
					
					// Draw the model into Battery A pic window
					DrawBatteryACurrentModel();
					
					// Hide old windows, show battery A window and battery A window 1
					ShowHide(gNewTrialWindow, FALSE);
					TickBatteryAWindow();
					ShowHide(gBatteryAWindow1, TRUE);
					SelectWindow(gBatteryAWindow1);
				}				
			}
			
			else if(runTrial == 3){
				printf("Running Trial 3.\n");
				currentTrial.trialMode=3;
				
				// Cycle currentModel to a new model
				if(currentTrial.nextModel()){
					
					// Draw the model into Battery C pic window
					DrawBatteryCCurrentModel();
					
					// Hide old windows, show battery C Window
					ShowHide(gNewTrialWindow, FALSE);
					ShowHide(gBatteryCWindow, TRUE);
					SelectWindow(gBatteryCWindow);
					
				}
			}
			
			result = noErr;
			break;
			
		case CancelTrial: printf("Cancelling Trial.\n");
			ShowHide(gNewTrialWindow, FALSE);
			ShowHide(window, TRUE);
			SelectWindow(window);
			result = noErr;
			break;
	
		default: break;
	}

    return result; 
}

// Battery A Window Event Handler
// Handles events from the Battery A window
pascal OSStatus BatteryAWindowEventHandler (EventHandlerCallRef handlerRef, EventRef event, void *userData) {

	printf("Recieved event from Battery A Window\n");
	
	// sets result to err so Carbon Event Manager will take over if event not handled
	OSStatus result = eventNotHandledErr;           
	HICommand command;
	
	// Gets commandID from Menu. Ex: About box had commandID "abtb"
	GetEventParameter (event, kEventParamDirectObject, typeHICommand, NULL, 
					   sizeof (HICommand), NULL, &command);   
	
	// switch handles every possible commandID (in this case, Menu item)
	printf("Command: %d\n",command.commandID);
	switch (command.commandID){
			
		default: break;
	}
	
	result = noErr;
	return result; 
}

pascal void TickBatteryAWindow() {
	
	// show target
	ShowHide(gTargetAlertWindow,TRUE);
	
	// wait 3 seconds
	sleep(3);
	
	// hide target
	ShowHide(gTargetAlertWindow, FALSE);
	
	// show battery b picture window
	ShowHide(gBatteryAWindow, TRUE);
	
	// Wait 250ms
	printf("Tick\n");
	struct timespec onemillisec = {0};              
	onemillisec.tv_nsec = 250000000L; 
	nanosleep(&onemillisec,NULL); 
	printf("Tock\n"); 
	
	// Hide battery b picture window
	ShowHide(gBatteryAWindow, FALSE);
}


