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

#include <Carbon/Carbon.h>
#include "Handlers.h"

static OSStatus        AppEventHandler( EventHandlerCallRef inCaller, EventRef inEvent, void* inRefcon );
static OSStatus        HandleNew();
static OSStatus        WindowEventHandler( EventHandlerCallRef inCaller, EventRef inEvent, void* inRefcon );

static IBNibRef        sNibRef;

//--------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
	OSStatus					err;
	static const EventTypeSpec			kAppEvents[] = {{ kEventClassCommand, kEventCommandProcess }};

	// Create a Nib reference, passing the name of the nib file (without the .nib extension).
	err = CreateNibReference( CFSTR("main"), &sNibRef );
	require_noerr( err, CantGetNibRef );
    
	// Once the nib reference is created, set the menu bar. "MainMenu" is the name of the menu bar
	err = SetMenuBarFromNib( sNibRef, CFSTR("MenuBar") );
	require_noerr( err, CantSetMenuBar );
    
	// Install our handler for common commands on the application target
	InstallApplicationEventHandler( NewEventHandlerUPP( AppEventHandler ),
                                    GetEventTypeCount( kAppEvents ), kAppEvents,
                                    0, NULL );
    
	// Create a new window. A full-fledged application would do this from an AppleEvent handler
	// for kAEOpenApplication.
	HandleNew();
    
	// Run the event loop
	RunApplicationEventLoop();

	CantSetMenuBar:
	CantGetNibRef:
    		return err;
}

//--------------------------------------------------------------------------------------------
DEFINE_ONE_SHOT_HANDLER_GETTER( WindowEventHandler )

//--------------------------------------------------------------------------------------------
static OSStatus
HandleNew() {

	OSStatus					err;
	
	// -- Event Type Specifiers -- //
	static const EventTypeSpec			kWindowEvents[] = {{ kEventClassCommand, kEventCommandProcess }};
		
	// Main Window event type specifier :: handles menu commands
	EventTypeSpec mainSpec = { kEventClassCommand, kEventProcessCommand};
	
	// Model Window event type specifier :: handles commands from model list window
	EventTypeSpec modelSpec = { kEventClassCommand, kEventProcessCommand};
	// Model window event type specifier :: handles close command from model list window
	EventTypeSpec modelSpecClose = { kEventClassWindow, kEventWindowClose };
	
	// Add Model Window event type specifier :: handles commands from add model window
	EventTypeSpec addmodelSpec = { kEventClassCommand, kEventProcessCommand};
	// Add Model window event type specifier :: handles close command from model list window
	EventTypeSpec addmodelSpecClose = { kEventClassWindow, kEventWindowClose };
	
	// Add Error Window event type specifier :: handles commands from add error alert
	EventTypeSpec adderrorSpec = { kEventClassCommand, kEventProcessCommand};
		
	// View Model Window event type specifier
	EventTypeSpec viewmodelSpec = { kEventClassCommand, kEventProcessCommand};
	
	// Group List Window event type specifier
	EventTypeSpec grouplistSpec = { kEventClassCommand, kEventProcessCommand};
	// Group List window close event type specifier :: handles close command from group list window
	EventTypeSpec grouplistSpecClose = { kEventClassWindow, kEventWindowClose };
	
	// Add Group Window event type specifier
	EventTypeSpec addgroupSpec = { kEventClassCommand, kEventProcessCommand};
	
	// Edit Group Window event type specifier
	EventTypeSpec editgroupSpec = { kEventClassCommand, kEventProcessCommand};
	
	// New Trial Window event type specifier
	EventTypeSpec newtrialSpec = {kEventClassCommand, kEventProcessCommand};
	
	// Battery A Window event type specifier
	EventTypeSpec batteryaSpec = {kEventClassCommand, kEventProcessCommand};
	
	// Battery A Competence event type specifier
	EventTypeSpec batteryacompSpec = {kEventClassCommand, kEventProcessCommand};
	
	// Battery A Trustworthy event type specifier
	EventTypeSpec batteryatrustSpec = {kEventClassCommand, kEventProcessCommand};
	
	// Battery A Likeable event type specifier
	EventTypeSpec batteryalikeSpec = {kEventClassCommand, kEventProcessCommand};
	
	// Battery A Attractiveness event type specifier
	EventTypeSpec batteryaattrSpec = {kEventClassCommand, kEventProcessCommand};
	
	// Survey Window event type specifier
	EventTypeSpec SurveySpec = {kEventClassCommand, kEventProcessCommand};
	
	// Battery C Window event type specifier
	EventTypeSpec batteryCSpec = {kEventClassCommand, kEventProcessCommand};

	// --------------------------- //
	
	// Create a window. "MainWindow" is the name of the window object. This name is set in 
	// InterfaceBuilder when the nib is created.
	err = CreateWindowFromNib( sNibRef, CFSTR("MainWindow"), &window );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("ModelListWindow"), &window2 );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("AddModelWindow"), &window3 );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("ErrorAddWindow"), &window4 );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("ViewModelWindow"), &window5 );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("GroupListWindow"), &gGroupListWindow );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("AddGroupWindow"), &gAddGroupWindow );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("EditGroupWindow"), &gEditGroupWindow );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("NewTrialWindow"), &gNewTrialWindow );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("BatteryAWindow"), &gBatteryAWindow );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("ACompetence"), &gBatteryAWindow1 );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("ATrustworthiness"), &gBatteryAWindow2 );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("ALikeability"), &gBatteryAWindow3 );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("AAttractiveness"), &gBatteryAWindow4 );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("TargetAlertWindow"), &gTargetAlertWindow );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("SurveyWindow"), &gSurveyWindow );
	require_noerr( err, CantCreateWindow );
	
	err = CreateWindowFromNib( sNibRef, CFSTR("BatteryCWindow"), &gBatteryCWindow );
	require_noerr( err, CantCreateWindow );
    
	// -- Install Command Handlers -- //
	InstallWindowEventHandler( window, GetWindowEventHandlerUPP(),
								   GetEventTypeCount( kWindowEvents ), kWindowEvents,
								   window, NULL );
		
	// Main Window Event Handler
	InstallWindowEventHandler (window, 
								   NewEventHandlerUPP (MainWindowEventHandler), 
								   1, &mainSpec, (void *) window, NULL);
	
	// Model List Window Event Handler
	InstallWindowEventHandler (window2, 
								   NewEventHandlerUPP (ModelListWindowEventHandler), 
								   1, &modelSpec, (void *) window2, NULL); 
	// Model List Window Event Handler :: Close
	InstallWindowEventHandler (window2, 
								   NewEventHandlerUPP (ModelListWindowCloseEventHandler), 
								   1, &modelSpecClose, (void *) window2, NULL); 
	
	// Add Model Window Event Handler
	InstallWindowEventHandler (window3, 
								   NewEventHandlerUPP (AddModelWindowEventHandler), 
								   1, &addmodelSpec, (void *) window3, NULL); 
	// Add Model Window Event Handler :: Close
	InstallWindowEventHandler (window3, 
								   NewEventHandlerUPP (AddModelWindowCloseEventHandler), 
								   1, &addmodelSpecClose, (void *) window3, NULL); 
	
	// Add Model Window Event Handler
	InstallWindowEventHandler (window4, 
								   NewEventHandlerUPP (AddErrorWindowEventHandler), 
								   1, &adderrorSpec, (void *) window4, NULL); 
	
	// View Model Window Event Handler
	InstallWindowEventHandler (window5, 
								   NewEventHandlerUPP (ViewModelWindowEventHandler), 
								   1, &viewmodelSpec, (void *) window5, NULL); 
	
	// Group List Window Event Handler
	InstallWindowEventHandler (gGroupListWindow, 
								   NewEventHandlerUPP (GroupListWindowEventHandler), 
								   1, &grouplistSpec, (void *) gGroupListWindow, NULL); 
	// Group List Window Close Event Handler
	InstallWindowEventHandler (gGroupListWindow, 
								   NewEventHandlerUPP (GroupListWindowCloseEventHandler), 
								   1, &grouplistSpecClose, (void *) gGroupListWindow, NULL);
		
	// Add Group Window Event Handler
	InstallWindowEventHandler (gAddGroupWindow, 
								   NewEventHandlerUPP (AddGroupWindowEventHandler), 
								   1, &addgroupSpec, (void *) gAddGroupWindow, NULL); 
	
	// Add Group Window Event Handler
	InstallWindowEventHandler (gEditGroupWindow, 
								   NewEventHandlerUPP (EditGroupWindowEventHandler), 
								   1, &editgroupSpec, (void *) gEditGroupWindow, NULL); 
	
	// New Trial Window Event Handler
	InstallWindowEventHandler (gNewTrialWindow, 
								   NewEventHandlerUPP (NewTrialWindowEventHandler), 
								   1, &newtrialSpec, (void *) gNewTrialWindow, NULL); 
	
	// Battery A Window Event Handler
	InstallWindowEventHandler (gBatteryAWindow, 
								   NewEventHandlerUPP (BatteryAWindowEventHandler), 
								   1, &batteryaSpec, (void *) gBatteryAWindow, NULL); 
	
	// Battery A Window Event Handler
	InstallWindowEventHandler (gBatteryAWindow1, 
							   NewEventHandlerUPP (BatteryACompetenceWindowEventHandler), 
							   1, &batteryacompSpec, (void *) gBatteryAWindow1, NULL); 
	
	// Battery A Window Event Handler
	InstallWindowEventHandler (gBatteryAWindow2, 
							   NewEventHandlerUPP (BatteryATrustWindowEventHandler), 
							   1, &batteryatrustSpec, (void *) gBatteryAWindow2, NULL); 
	
	// Battery A Window Event Handler
	InstallWindowEventHandler (gBatteryAWindow3, 
							   NewEventHandlerUPP (BatteryALikeableWindowEventHandler), 
							   1, &batteryalikeSpec, (void *) gBatteryAWindow3, NULL); 
	
	// Battery A Window Event Handler
	InstallWindowEventHandler (gBatteryAWindow4, 
							   NewEventHandlerUPP (BatteryAAttractivenessWindowEventHandler), 
							   1, &batteryaattrSpec, (void *) gBatteryAWindow4, NULL); 
	
	// Survey Window Event Handler
	InstallWindowEventHandler (gSurveyWindow, 
							   NewEventHandlerUPP (SurveyWindowEventHandler), 
							   1, &SurveySpec, (void *) gSurveyWindow, NULL); 
	
	// Battery C Window Event Handler
	InstallWindowEventHandler (gBatteryCWindow, 
							   NewEventHandlerUPP (BatteryCWindowEventHandler), 
							   1, &batteryCSpec, (void *) gBatteryCWindow, NULL); 
	
	// --------------------------- //
	
	// Position new windows in a centered arrangement on the main screen
	RepositionWindow( window, NULL, kWindowCenterOnMainScreen );
    
	// The window was created hidden, so show it
	ShowWindow( window );
	
	masterModelList.RebuildModels();
	masterGroupList.RebuildGroups();
	InitializeModelDataBrowser();
	InitializeGroupListDataBrowser();
	InitializeModelGroupDataBrowser();
	
	masterModelList.PrintDatabase();
    
	CantCreateWindow:
		return err;
}

//--------------------------------------------------------------------------------------------
static OSStatus
WindowEventHandler( EventHandlerCallRef inCaller, EventRef inEvent, void* inRefcon ) {
    
    OSStatus    err = eventNotHandledErr;
    
    switch ( GetEventClass( inEvent ) )
    {
        case kEventClassCommand:
        {
            HICommandExtended cmd;
            verify_noerr( GetEventParameter( inEvent, kEventParamDirectObject, typeHICommand, NULL, sizeof( cmd ), NULL, &cmd ) );
            
            switch ( GetEventKind( inEvent ) )
            {
                case kEventCommandProcess:
                    switch ( cmd.commandID )
                    {
                        // Add your own command-handling cases here
                        
                        default:
                            break;
                    }
                    break;
            }
            break;
        }
            
        default:
            break;
    }
    
    return err;
}

//--------------------------------------------------------------------------------------------
static OSStatus
AppEventHandler( EventHandlerCallRef inCaller, EventRef inEvent, void* inRefcon ) {
    
    OSStatus    result = eventNotHandledErr;
    
    switch ( GetEventClass( inEvent ) )
    {
        case kEventClassCommand:
        {
            HICommandExtended cmd;
            verify_noerr( GetEventParameter( inEvent, kEventParamDirectObject, typeHICommand, NULL, sizeof( cmd ), NULL, &cmd ) );
            
            switch ( GetEventKind( inEvent ) )
            {
					printf("%d\n", inEvent);
                case kEventCommandProcess:
                    switch ( cmd.commandID )
				{
					case kHICommandNew:
						result = HandleNew();
						break;
						
                        // Add your own command-handling cases here
                        
					default:
						break;
				}
                    break;
            }
            break;
        }
            
        default:
            break;
    }
    
    return result;
}
