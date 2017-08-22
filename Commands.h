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

#include "Definitions.h"
#include "Models.h"
ModelDB				   masterModelList;
Trial				   currentTrial;

DataBrowserItemID groupID;
UInt32 groupIndex;

OSStatus SetImage(CFStringRef strvalue);
pascal bool AddModelCommandHandler();
pascal bool DeleteModelCommandHandler();
pascal void CancelModelCommandHandler();
pascal void resetAddModelDialog();
pascal bool GetPictureNameCommandHandler();
pascal void ModelListDataCallback (ControlRef, DataBrowserItemID, DataBrowserPropertyID, DataBrowserItemDataRef, Boolean );
pascal void InitializeModelDataBrowser ();
pascal void ClearModelDataBrowser();

pascal void ModelListGroupDataCallback (ControlRef, DataBrowserItemID, DataBrowserPropertyID, DataBrowserItemDataRef, Boolean );
pascal void InitializeModelGroupDataBrowser ();
pascal void ClearModelGroupDataBrowser();

pascal void GroupMemberDataCallback (ControlRef, DataBrowserItemID, DataBrowserPropertyID, DataBrowserItemDataRef, Boolean );
pascal void InitializeGroupMemberDataBrowser ();
pascal void ClearGroupMemberDataBrowser();

pascal bool AddGroupCommandHandler();
pascal bool DeleteGroupCommandHandler();
pascal void ClearGroupListDataBrowser();
pascal void InitializeGroupListDataBrowser();
pascal void resetAddGroupDialog();
pascal DataBrowserItemID GetGroupSelection();
pascal bool AddGroupMemberCommandHandler();
pascal bool DeleteGroupCommandHandler();

pascal void InitializeTrialGroupListDataBrowser();
pascal void ClearTrialGroupListDataBrowser();
pascal void ResetNewTrialWindow();
pascal int BeginNewTrialCommandHandler();

pascal void DrawBatteryACurrentModel();
pascal void ClearBatteryADialog();

pascal bool SurveyCommandHandler();
pascal void ClearSurveyWindow();
pascal void ResetAllBatteryAWindows();
pascal bool BatteryAHandler1();
pascal bool BatteryAHandler2();
pascal bool BatteryAHandler3();
pascal bool BatteryAHandler4();

pascal void DrawBatteryCCurrentModel();
pascal bool BatteryCHandler();
pascal void ResetBatteryCWindow();


pascal void ResetBatteryCWindow(){
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    healthField;
	ControlHandle    dareField;
	ControlHandle    attentiveField;
	ControlHandle    sociableField;
	ControlHandle    caringField;
	ControlHandle    stableField;
	ControlHandle    hireField;
	ControlHandle    ageboxField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  healthFieldControlID = { BCHealthySignature, 
	BCHealthyID }; 
	
	ControlID  dareFieldControlID = { BCDaringSignature, 
	BCDaringID }; 
	
	ControlID  attentiveFieldControlID = { BCAttentiveSignature, 
	BCAttentiveID }; 
	
	ControlID  sociableFieldControlID = { BCSociableSignature, 
	BCSociableID }; 
	
	ControlID  caringFieldControlID = { BCCaringSignature, 
	BCCaringID }; 
	
	ControlID  stableFieldControlID = { BCStableSignature, 
	BCStableID }; 
	
	ControlID  hireFieldControlID = { BCHireSignature, 
	BCHireID }; 
	
	ControlID  ageboxFieldControlID = { BCAgeSignature, 
	BCAgeID }; 
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gBatteryCWindow, &healthFieldControlID,               
					&healthField ); 
	
	GetControlByID (gBatteryCWindow, &dareFieldControlID,               
					&dareField ); 
	
	GetControlByID (gBatteryCWindow, &attentiveFieldControlID,               
					&attentiveField ); 
	
	GetControlByID (gBatteryCWindow, &sociableFieldControlID,               
					&sociableField ); 
	
	GetControlByID (gBatteryCWindow, &caringFieldControlID,               
					&caringField ); 
	
	GetControlByID (gBatteryCWindow, &stableFieldControlID,               
					&stableField ); 
	
	GetControlByID (gBatteryCWindow, &hireFieldControlID,               
					&hireField ); 
	
	GetControlByID (gBatteryCWindow, &ageboxFieldControlID,               
					&ageboxField );
	
	
	// Reset all sliders
	SetControl32BitValue(healthField, 0);
	SetControl32BitValue(dareField, 0);
	SetControl32BitValue(attentiveField, 0);
	SetControl32BitValue(sociableField, 0);
	SetControl32BitValue(caringField, 0);
	SetControl32BitValue(stableField, 0);
	SetControl32BitValue(hireField, 0);
	
	// Reset age box
	CFStringRef blank = CFSTR("");
	
	// Reset fields
	SetControlData( ageboxField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	
	CFRelease(blank);
}

pascal bool BatteryCHandler(){
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    healthField;
	ControlHandle    dareField;
	ControlHandle    attentiveField;
	ControlHandle    sociableField;
	ControlHandle    caringField;
	ControlHandle    stableField;
	ControlHandle    hireField;
	ControlHandle    ageboxField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  healthFieldControlID = { BCHealthySignature, 
	BCHealthyID }; 
	
	ControlID  dareFieldControlID = { BCDaringSignature, 
	BCDaringID }; 
	
	ControlID  attentiveFieldControlID = { BCAttentiveSignature, 
	BCAttentiveID }; 
	
	ControlID  sociableFieldControlID = { BCSociableSignature, 
	BCSociableID }; 
	
	ControlID  caringFieldControlID = { BCCaringSignature, 
	BCCaringID }; 
	
	ControlID  stableFieldControlID = { BCStableSignature, 
	BCStableID }; 
	
	ControlID  hireFieldControlID = { BCHireSignature, 
	BCHireID }; 
	
	ControlID  ageboxFieldControlID = { BCAgeSignature, 
	BCAgeID }; 
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gBatteryCWindow, &healthFieldControlID,               
					&healthField ); 
	
	GetControlByID (gBatteryCWindow, &dareFieldControlID,               
					&dareField ); 
	
	GetControlByID (gBatteryCWindow, &attentiveFieldControlID,               
					&attentiveField ); 
	
	GetControlByID (gBatteryCWindow, &sociableFieldControlID,               
					&sociableField ); 
	
	GetControlByID (gBatteryCWindow, &caringFieldControlID,               
					&caringField ); 
	
	GetControlByID (gBatteryCWindow, &stableFieldControlID,               
					&stableField ); 
	
	GetControlByID (gBatteryCWindow, &hireFieldControlID,               
					&hireField ); 
	
	GetControlByID (gBatteryCWindow, &ageboxFieldControlID,               
					&ageboxField ); 
	
	int health = 0;
	int dare = 0;
	int attentive = 0;
	int sociable = 0;
	int caring = 0;
	int stable = 0;
	int hire = 0;
	CFStringRef ageBox;
	
	// Get Rating Data
	health = GetControl32BitValue(healthField);
	dare = GetControl32BitValue(dareField);
	attentive = GetControl32BitValue(attentiveField);
	sociable = GetControl32BitValue(sociableField);
	caring = GetControl32BitValue(caringField);
	stable = GetControl32BitValue(stableField);
	hire = GetControl32BitValue(hireField);
	
	// Get Age Data
	GetControlData( ageboxField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &ageBox, NULL);
	
	// Copy age info
	CFStringRef setAge = CFStringCreateCopy(NULL, ageBox);
		
	CFStringRef blank = CFSTR("");
	
	// Check for No Age
	if(CFStringCompare(ageBox, blank, 0)==0)
		return false;
	
	// Check for No Ratings
	if(health == 0 || dare == 0 || attentive == 0 || sociable == 0 || caring == 0 || stable == 0 || hire == 0)
		return false;
	
	// Save User information
	currentTrial.SetBatteryCData(health, dare, attentive, sociable, caring, stable, hire, ageBox);
	
	// Must always do this after getting a string from interface
	CFRelease(ageBox);	
	
	return true;
}

pascal void DrawBatteryCCurrentModel(){
	
	// Get current model's image name
	CFStringRef imageName;
	imageName = masterGroupList.groupList[currentTrial.groupID].modelList[currentTrial.currentModel].imageName;
	
	// Convert CFStringRef to URL
	CFURLRef filenameURL = CFURLCreateWithString(kCFAllocatorDefault,imageName, NULL);
	CFShow(filenameURL);
	
	// load the image
	CGImageRef imagefile;
	CGDataProviderRef provider = CGDataProviderCreateWithURL( filenameURL );
	imagefile = CGImageCreateWithJPEGDataProvider( provider, NULL, false,  kCGRenderingIntentDefault );
	
	// find the control
	const HIViewID kImageViewID = {'BCVW', 910};
	HIViewRef imageViewRef = NULL;
	HIViewFindByID(HIViewGetRoot(gBatteryCWindow), 
				   kImageViewID, &imageViewRef);
	
	// set the image into the view.
	HIImageViewSetImage( imageViewRef, imagefile ); // retains the image.

	HIViewSetNeedsDisplay(imageViewRef, TRUE);
}


pascal bool BatteryAHandler1(){
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    compField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  compFieldControlID = { CompetenceSignature, 
	CompetenceID }; 
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gBatteryAWindow1, &compFieldControlID,               
					&compField ); 
	
	int comp = 0;
	
	comp = GetControl32BitValue(compField);
	
	if(comp>0){
		currentTrial.SetACompRating(comp);
		return true;
	}
	
	return false;
}

pascal bool BatteryAHandler2(){
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    trustField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  trustFieldControlID = { TrustSignature, 
	TrustID }; 
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gBatteryAWindow2, &trustFieldControlID,               
					&trustField ); 
	
	int trust = 0;
	
	trust = GetControl32BitValue(trustField);
	
	if(trust>0){
		currentTrial.SetATrustRating(trust);
		return true;
	}
	
	return false;
}

pascal bool BatteryAHandler3(){
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    likeField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  likeFieldControlID = { LikeSignature, 
	LikeID }; 
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gBatteryAWindow3, &likeFieldControlID,               
					&likeField ); 
	
	int like = 0;
	
	like = GetControl32BitValue(likeField);
	
	if(like>0){
		currentTrial.SetALikeRating(like);
		return true;
	}
	
	return false;
}

pascal bool BatteryAHandler4(){
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    attrField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  attrFieldControlID = { AttractiveSignature, 
	AttractiveID }; 
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gBatteryAWindow4, &attrFieldControlID, &attrField ); 
	
	int attr = 0;
	
	attr = GetControl32BitValue(attrField);
	
	if(attr>0){
		currentTrial.SetAAttrRating(attr);
		return true;
	}
	
	return false;
}

pascal void ResetAllBatteryAWindows(){

	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    compField;
	ControlHandle	 likeField;
	ControlHandle	 attrField;
	ControlHandle	 trustField;

	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  compFieldControlID = { CompetenceSignature, CompetenceID }; 
	ControlID  likeFieldControlID = { LikeSignature, LikeID }; 
	ControlID  attrFieldControlID = { AttractiveSignature, AttractiveID }; 
	ControlID  trustFieldControlID = { TrustSignature, TrustID }; 

	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gBatteryAWindow1, &compFieldControlID, &compField ); 

	GetControlByID (gBatteryAWindow3, &likeFieldControlID, &likeField ); 

	GetControlByID (gBatteryAWindow4, &attrFieldControlID, &attrField ); 

	GetControlByID (gBatteryAWindow2, &trustFieldControlID, &trustField ); 

	SetControl32BitValue(compField, 0);
	SetControl32BitValue(likeField, 0);
	SetControl32BitValue(attrField, 0);
	SetControl32BitValue(trustField, 0);
}

pascal bool SurveyCommandHandler(){
	
	CFStringRef userMarital;
	CFStringRef userIncome;
	CFStringRef userOrientation;
	CFStringRef userKids;
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    maritalField;
	ControlHandle	 incomeField;
	ControlHandle	 orientationField;
	ControlHandle	 kidsField;
	
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  maritalFieldControlID = { SurveyMaritalSignature, 
	SurveyMaritalID }; 
	
	ControlID  incomeFieldControlID = { SurveyIncomeSignature, 
	SurveyIncomeID }; 
	
	ControlID  orientationFieldControlID = { SurveyOrientationSignature, 
	SurveyOrientationID }; 
	
	ControlID  kidsFieldControlID = { SurveyChildrenSignature, 
	SurveyChildrenID }; 
	

	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gSurveyWindow, &maritalFieldControlID,               
					&maritalField ); 
	
	GetControlByID (gSurveyWindow, &incomeFieldControlID,               
					&incomeField );
	
	GetControlByID (gSurveyWindow, &orientationFieldControlID,               
					&orientationField );
	
	GetControlByID (gSurveyWindow, &kidsFieldControlID,               
					&kidsField );
	
	
	// Get Data from Input Field
	GetControlData( maritalField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &userMarital, NULL); 
	
	GetControlData( incomeField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &userIncome, NULL); 
	
	GetControlData( orientationField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &userOrientation, NULL); 
	
	GetControlData( kidsField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &userKids, NULL); 
	
	
	printf("Saving User Information\n");
	
	// copy user name
	CFStringRef setMarital = CFStringCreateCopy(NULL, userMarital);
	
	// copy user id
	CFStringRef setIncome = CFStringCreateCopy(NULL, userIncome);
	
	// copy user race
	CFStringRef setOrientation = CFStringCreateCopy(NULL, userOrientation);
	
	// copy user age
	CFStringRef setKids = CFStringCreateCopy(NULL, userKids);
	
	CFStringRef blank = CFSTR("");
	
	if(CFStringCompare(setMarital, blank, 0)==0)
		return false;
	if(CFStringCompare(setIncome, blank, 0)==0)
		return false;
	if(CFStringCompare(setOrientation, blank, 0)==0)
		return false;
	if(CFStringCompare(setKids, blank, 0)==0)
		return false;
	
	
	// Save User information
	currentTrial.SetUserSurveyData(setMarital, setIncome, setOrientation, setKids);
	
	// Must always do this after getting a string from interface
	CFRelease(userMarital);
	CFRelease(userIncome);
	CFRelease(userOrientation);
	CFRelease(userKids);
	
	return true;
}

pascal void ClearSurveyWindow(){
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    maritalField;
	ControlHandle	 incomeField;
	ControlHandle	 orientationField;
	ControlHandle	 kidsField;
	
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  maritalFieldControlID = { SurveyMaritalSignature, 
	SurveyMaritalID }; 
	
	ControlID  incomeFieldControlID = { SurveyIncomeSignature, 
	SurveyIncomeID }; 
	
	ControlID  orientationFieldControlID = { SurveyOrientationSignature, 
	SurveyOrientationID }; 
	
	ControlID  kidsFieldControlID = { SurveyChildrenSignature, 
	SurveyChildrenID }; 
	
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gSurveyWindow, &maritalFieldControlID,               
					&maritalField ); 
	
	GetControlByID (gSurveyWindow, &incomeFieldControlID,               
					&incomeField );
	
	GetControlByID (gSurveyWindow, &orientationFieldControlID,               
					&orientationField );
	
	GetControlByID (gSurveyWindow, &kidsFieldControlID,               
					&kidsField );
	
	
	CFStringRef blank = CFSTR("");
	
	// Reset fields
	SetControlData( maritalField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	
	SetControlData( incomeField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	
	SetControlData( orientationField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	
	SetControlData( kidsField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	
	
	CFRelease(blank);
}

pascal bool AddModelCommandHandler () { 
	
	bool outcome = true;
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    nameField;
	ControlHandle	 raceField;
	ControlHandle	 ageField;
	ControlHandle	 makeupField;
	ControlHandle	 pictureField;
	ControlHandle	 segmentField;
	ControlHandle	 maritalField;
	ControlHandle	 incomeField;
	ControlHandle	 orientationField;
	ControlHandle    hairField;
	ControlHandle    smileField;
	ControlHandle    mirrorField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  nameFieldControlID = { nameFieldSignature, 
	nameFieldID }; 
	
	ControlID  raceFieldControlID = { raceFieldSignature, 
	raceFieldID }; 
	
	ControlID  ageFieldControlID = { ageFieldSignature, 
	ageFieldID }; 
	
	ControlID  makeupFieldControlID = { makeupFieldSignature, 
	makeupFieldID }; 
	
	ControlID  pictureFieldControlID = { pictureFieldSignature, 
	pictureFieldID }; 
	
	ControlID  segmentFieldControlID = { segmentFieldSignature, 
	segmentFieldID }; 
	
	ControlID  maritalFieldControlID = { maritalFieldSignature, 
	maritalFieldID }; 
	
	ControlID  incomeFieldControlID = { incomeFieldSignature, 
	incomeFieldID }; 
	
	ControlID  orientationFieldControlID = { orientationFieldSignature, 
	orientationFieldID }; 
	
	ControlID  hairFieldControlID = { hairFieldSignature, 
	hairFieldID }; 
	
	ControlID  smileFieldControlID = { smileFieldSignature, 
	smileFieldID }; 
	
	ControlID  mirrorFieldControlID = { mirrorFieldSignature, 
	mirrorFieldID }; 
	
	CFStringRef nameInput;
	CFStringRef picInput;
	CFStringRef raceInput;
	CFStringRef ageInput;
	CFStringRef makeupInput;
	CFStringRef segmentInput;
	CFStringRef maritalInput;
	CFStringRef incomeInput;
	CFStringRef orientationInput;
	CFStringRef hairInput;
	CFStringRef smileInput;
	CFStringRef mirrorInput;
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (window3, &nameFieldControlID,               
					&nameField ); 
	
	GetControlByID (window3, &raceFieldControlID,               
					&raceField ); 
	
	GetControlByID (window3, &ageFieldControlID,               
					&ageField ); 
	
	GetControlByID (window3, &makeupFieldControlID,               
					&makeupField ); 
	
	GetControlByID (window3, &pictureFieldControlID,               
					&pictureField ); 
	
	GetControlByID (window3, &segmentFieldControlID,               
					&segmentField ); 
	
	GetControlByID (window3, &maritalFieldControlID,               
					&maritalField ); 
	
	GetControlByID (window3, &incomeFieldControlID,               
					&incomeField ); 
	
	GetControlByID (window3, &orientationFieldControlID,               
					&orientationField ); 
	
	GetControlByID (window3, &hairFieldControlID,               
					&hairField ); 
	
	GetControlByID (window3, &smileFieldControlID,               
					&smileField ); 
	
	GetControlByID (window3, &mirrorFieldControlID,               
					&mirrorField ); 
	

	// Get Data from Input Field
	GetControlData( nameField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &nameInput, NULL); 
	
	GetControlData( pictureField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &picInput, NULL); 
	
	GetControlData( raceField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &raceInput, NULL); 
	
	GetControlData( ageField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &ageInput, NULL); 
	
	GetControlData( makeupField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &makeupInput, NULL); 
	
	GetControlData( segmentField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &segmentInput, NULL); 
	
	GetControlData( maritalField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &maritalInput, NULL); 
	
	GetControlData( incomeField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &incomeInput, NULL); 
	
	GetControlData( orientationField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &orientationInput, NULL); 
	
	GetControlData( hairField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &hairInput, NULL); 
	
	GetControlData( smileField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &smileInput, NULL); 
	
	GetControlData( mirrorField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &mirrorInput, NULL); 
	
	
	// Check input
	if(! CFStringCompare(nameInput,CFSTR(""), 0))
		outcome = false;
	
	if(! CFStringCompare(picInput,CFSTR(""), 0))
		outcome = false;
	
	if(outcome){
		
		printf("Running Add Model Routine\n");
		
		// copy model name
		CFStringRef setName = CFStringCreateCopy(NULL, nameInput);
		
		// copy model pic
		CFStringRef setPic = CFStringCreateCopy(NULL, picInput);
		
		// copy model race
		CFStringRef setRace = CFStringCreateCopy(NULL, raceInput);
		
		// copy model age
		CFStringRef setAge = CFStringCreateCopy(NULL, ageInput);
		
		// copy model makeup
		CFStringRef setMakeup = CFStringCreateCopy(NULL, makeupInput);
		
		// copy model segment
		CFStringRef setSegment = CFStringCreateCopy(NULL, segmentInput);
		
		// copy model marital status
		CFStringRef setMarital = CFStringCreateCopy(NULL, maritalInput);
		
		// copy model income
		CFStringRef setIncome = CFStringCreateCopy(NULL, incomeInput);
		
		// copy model orientation
		CFStringRef setOrientation = CFStringCreateCopy(NULL, orientationInput);
		
		// copy model hair type
		CFStringRef setHair = CFStringCreateCopy(NULL, hairInput);
		
		// copy model smiling
		CFStringRef setSmile = CFStringCreateCopy(NULL, smileInput);
		
		// copy model mirror
		CFStringRef setMirror = CFStringCreateCopy(NULL, mirrorInput);
		
		masterModelList.AddModel(0, setName, setPic, setMakeup, setRace, setAge, setSegment, setMarital,
								setIncome, setOrientation, setHair, setSmile, setMirror);
		
		printf("There are now %d models in the database.\n", masterModelList.ReturnTotalModels());
		
		printf("flag 1\n");
		masterModelList.PrintDatabase();
		printf("***********\n");
		
	}
	printf("flag 1.2\n");
	// Reset Fields
	resetAddModelDialog();
	printf("flag 2\n");
	// Back Up Database
	masterModelList.SaveModels();
	printf("flag 3\n");
	
	// Must always do this after getting a string from interface
	CFRelease(nameInput);
	CFRelease(raceInput);
	CFRelease(ageInput);
	CFRelease(makeupInput);
	CFRelease(segmentInput);
	CFRelease(maritalInput);
	CFRelease(incomeInput);
	CFRelease(orientationInput);
	CFRelease(hairInput);
	CFRelease(smileInput);
	CFRelease(mirrorInput);
	printf("flag 4\n");
	return outcome;
} 

pascal void resetAddModelDialog() {
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    nameField;
	ControlHandle	 raceField;
	ControlHandle	 ageField;
	ControlHandle	 makeupField;
	ControlHandle	 pictureField;
	ControlHandle	 segmentField;
	ControlHandle	 maritalField;
	ControlHandle	 incomeField;
	ControlHandle	 orientationField;
	ControlHandle    hairField;
	ControlHandle    smileField;
	ControlHandle    mirrorField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  nameFieldControlID = { nameFieldSignature, 
	nameFieldID }; 
	
	ControlID  raceFieldControlID = { raceFieldSignature, 
	raceFieldID }; 
	
	ControlID  ageFieldControlID = { ageFieldSignature, 
	ageFieldID }; 
	
	ControlID  makeupFieldControlID = { makeupFieldSignature, 
	makeupFieldID }; 
	
	ControlID  pictureFieldControlID = { pictureFieldSignature, 
	pictureFieldID }; 
	
	ControlID  segmentFieldControlID = { segmentFieldSignature, 
	segmentFieldID }; 
	
	ControlID  maritalFieldControlID = { maritalFieldSignature, 
	maritalFieldID }; 
	
	ControlID  incomeFieldControlID = { incomeFieldSignature, 
	incomeFieldID }; 
	
	ControlID  orientationFieldControlID = { orientationFieldSignature, 
	orientationFieldID }; 
	
	ControlID  hairFieldControlID = { hairFieldSignature, 
	hairFieldID }; 
	
	ControlID  smileFieldControlID = { smileFieldSignature, 
	smileFieldID }; 
	
	ControlID  mirrorFieldControlID = { mirrorFieldSignature, 
	mirrorFieldID }; 

	CFStringRef blank = CFSTR("");
	CFStringRef select = CFSTR("Select");
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (window3, &nameFieldControlID,               
					&nameField ); 
	
	GetControlByID (window3, &raceFieldControlID,               
					&raceField ); 
	
	GetControlByID (window3, &ageFieldControlID,               
					&ageField ); 
	
	GetControlByID (window3, &makeupFieldControlID,               
					&makeupField ); 
	
	GetControlByID (window3, &pictureFieldControlID,               
					&pictureField ); 
	
	GetControlByID (window3, &segmentFieldControlID,               
					&segmentField ); 
	
	GetControlByID (window3, &maritalFieldControlID,               
					&maritalField ); 
	
	GetControlByID (window3, &incomeFieldControlID,               
					&incomeField ); 
	
	GetControlByID (window3, &orientationFieldControlID,               
					&orientationField ); 
	
	GetControlByID (window3, &hairFieldControlID,               
					&hairField ); 
	
	GetControlByID (window3, &smileFieldControlID,               
					&smileField ); 
	
	GetControlByID (window3, &mirrorFieldControlID,               
					&mirrorField ); 
	
	// Reset Image Display
	SetImage(CFSTR("blank.png"));
	
	// Reset fields
	SetControlData( nameField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	SetControlData( raceField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &select);
	SetControlData( ageField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &select);
	SetControlData( makeupField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &select);
	SetControlData( pictureField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	SetControlData( segmentField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &select);
	SetControlData( maritalField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &select);
	SetControlData( incomeField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &select);
	SetControlData( orientationField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &select);
	SetControlData( hairField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &select);
	SetControlData( smileField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &select);
	SetControlData( mirrorField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &select);
	
	CFRelease(blank);
	CFRelease(select);
}
	
CGImageRef LoadImage( CFStringRef inName ) {
	CGImageRef image = NULL;
	
	CFBundleRef appBundle = CFBundleGetMainBundle();
	if ( appBundle )
	{
		CFURLRef url = CFBundleCopyResourceURL( appBundle, inName, NULL, NULL );
		if (url != NULL)
		{	
			CGDataProviderRef provider = CGDataProviderCreateWithURL( url );
			if (provider != NULL)
			{
				image = CGImageCreateWithPNGDataProvider( provider, NULL, false,  kCGRenderingIntentDefault );
				CGDataProviderRelease( provider );
			}
			CFRelease( url );
		}
	}
	return image;
}

OSStatus SetImage(CFStringRef strvalue) {

	const HIViewID kImageViewID = {'pict', 130};
	
	// find the control
	HIViewRef imageViewRef = NULL;
	OSStatus status = HIViewFindByID(HIViewGetRoot(window3), kImageViewID, &imageViewRef);
	verify_noerr(status);
	
	// load the image
	CGImageRef imageRef = LoadImage(strvalue);
	
	// set the image into the view.
	status = HIImageViewSetImage( imageViewRef, imageRef ); // retains the image.
	verify_noerr(status);
	
	CFRelease(imageRef);  // release your image here
	
	std::cout << "   SetImage  = " << std::endl;
	return status;
}
	
pascal bool DeleteModelCommandHandler() {

	bool outcome = true;
	
	// Get table info
	const       ControlID  dbControlID  = { 'SLST', 0 };
	ControlRef  dbControl;
	
	GetControlByID (window2, &dbControlID, &dbControl);
	
	Handle selectedID = ::NewHandle(0);
	ItemCount size;
	
	printf("Running Delete Routine.\n");
	
	// Get selected item handle
	GetDataBrowserItems(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, selectedID);
	
	// Get selected item ID
	GetDataBrowserItemCount(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, &size);
	
	// If no model is selected, display error message, free handle, and return
	if(size<1){
		printf("No models selected!\n");
		outcome = false;
		
		DialogRef theItem;
		DialogItemIndex itemIndex;
		
		CreateStandardAlert(kAlertCautionAlert,  
						   CFSTR("No Model Selected.\n"),  
						   CFSTR("Please select a model to delete.\n"),
						   NULL, &theItem); 
		
		RunStandardAlert (theItem, NULL, &itemIndex);
		
		DisposeHandle(selectedID);
		
		return outcome;
	}
	
	// Extract itemID from handle
	HLock( selectedID );
	DataBrowserItemID *individualItem;
	individualItem = (DataBrowserItemID*)( *selectedID );
	printf("ID2: %d\n", *individualItem);
	
	// Display Alert
	CFStringRef removename = masterModelList.GetNameFromID(*individualItem);
	CFStringRef removepic = masterModelList.GetPicFromID(*individualItem);
	CFStringRef removemakeup = masterModelList.GetMakeupFromID(*individualItem);
	
	DialogRef theItem;
	DialogItemIndex itemIndex;
	
	struct AlertStdCFStringAlertParamRec params = {kStdCFStringAlertVersionOne,
		true, false, CFSTR("OK"), CFSTR("Cancel"), NULL, kAlertStdAlertOKButton,
		kAlertStdAlertCancelButton, kWindowAlertPositionParentWindowScreen,
	NULL};
	
	CreateStandardAlert(kAlertCautionAlert,
						removename,
						CFSTR("Are you sure you want to remove this model?"),
						&params, &theItem);
	
	RunStandardAlert (theItem, NULL, &itemIndex); 
	
	switch(itemIndex){
			case kAlertStdAlertOKButton:
				// Remove specified model from database
				masterModelList.RemoveModel(*individualItem);
			
			// Remove all model instances across all groups
			while(masterGroupList.UniversalRemoveModelFromGroup(removename, removepic, removemakeup));
			masterGroupList.SaveGroups();
			break;
			
			case kAlertStdAlertCancelButton:
				outcome = false;
			break;
			
		default:break;
	}
	
	DisposeHandle(selectedID);
	
	return outcome;
}

pascal void CancelModelCommandHandler () { 	
	
	resetAddModelDialog();
} 

// Gets picture name from Open File Dialog
// Sets Picture field of Add Model Dialog to picture path
pascal bool GetPictureNameCommandHandler() {
	
	ControlHandle    pictureField;
	
	ControlID  pictureFieldControlID = { pictureFieldSignature, 
	pictureFieldID }; 
	
	GetControlByID (window3, &pictureFieldControlID,               
					&pictureField ); 
	
	CFStringRef filename = CFSTR(" ");
	
	
	NavDialogCreationOptions dialogOptions;
	NavDialogRef dialog;
	NavReplyRecord replyRecord;
	CFURLRef fileAsCFURLRef = NULL;
	FSRef fileAsFSRef;
	OSStatus status;
	
	// Get the standard set of defaults
	status = NavGetDefaultDialogCreationOptions(&dialogOptions);
	
	// Make the window app-wide modal
	dialogOptions.modality = kWindowModalityAppModal;
	
	// Set File Options
	NavTypeListHandle hTypeList = (NavTypeListHandle) NewHandleClear (sizeof (NavTypeList) + sizeof (OSType) * (2 - 1)); 
	HLock ((Handle) hTypeList);
	// File type list
	(**hTypeList).osTypeCount = 2;
	(**hTypeList).osType[0] = 'JPEG';
	(**hTypeList).osType[1] = 'JPG ';
	
	// Create the dialog
	status = NavCreateGetFileDialog(&dialogOptions, hTypeList, NULL, NULL, NULL, NULL, &dialog);

	// Show it
	status = NavDialogRun(dialog);
	
	// Get the reply
	status = NavDialogGetReply(dialog, &replyRecord);
	
	// If the user clicked "Cancel", just bail
	if ( status == userCanceledErr )
		return false;
	
	// Get the file
	status = AEGetNthPtr(&(replyRecord.selection), 1, typeFSRef, NULL, NULL, &fileAsFSRef, sizeof(FSRef), NULL);

	// Convert it to a CFURL
	fileAsCFURLRef = CFURLCreateFromFSRef(NULL, &fileAsFSRef);
	
	CFURLRef output= CFURLGetBaseURL(fileAsCFURLRef);
	
	CFShow(output);
	
	// Convert it to a string
	filename = CFURLCopyPath(fileAsCFURLRef);
	CFMutableStringRef filename2 = CFStringCreateMutableCopy (kCFAllocatorDefault, 0, filename);
	CFStringRef newfile = CFSTR("file://localhost");
	CFMutableStringRef prefix = CFStringCreateMutableCopy (kCFAllocatorDefault, 0, newfile);
	CFStringAppend(prefix, filename2);
	
	// load the image
	CGImageRef imagefile;
	CGDataProviderRef provider = CGDataProviderCreateWithURL( fileAsCFURLRef );
	imagefile = CGImageCreateWithJPEGDataProvider( provider, NULL, false,  kCGRenderingIntentDefault );
	
	// find the control
	const HIViewID kImageViewID = {'pict', 130};
	HIViewRef imageViewRef = NULL;
	HIViewFindByID(HIViewGetRoot(window3), kImageViewID, &imageViewRef);
	
	// set the image into the view.
	status = HIImageViewSetImage( imageViewRef, imagefile );

	// Sets text field to value of string
	SetControlData( pictureField, 0, kControlEditTextCFStringTag, 
				   sizeof (CFStringRef), &prefix); 
	
	CFShow(fileAsCFURLRef);
	
	// Releases string
	CFRelease (newfile); 
	CFRelease (filename); 
	CFRelease(filename2);
	CFRelease(prefix);
	
	// Redraws text field to reflect new value
	DrawOneControl (pictureField);  
	
	return true;
}

pascal void ModelListDataCallback (ControlRef browser, DataBrowserItemID itemID, DataBrowserPropertyID property, DataBrowserItemDataRef itemData, Boolean changeValue) {

	long newItemID = itemID;
	int dataIndex = newItemID - 1;
	CFOptionFlags casechk;
	casechk= kCFCompareCaseInsensitive;
	
	if (!changeValue) switch (property) {
        	case nameColumn:	
			if(dataIndex<masterModelList.modelList.size()){
				SetDataBrowserItemDataText (itemData, masterModelList.modelList[dataIndex].modelName);
				masterModelList.modelList[dataIndex].tableID = newItemID;
			}
            		break;
			
        	case raceColumn:	
			if(dataIndex<masterModelList.modelList.size())
				SetDataBrowserItemDataText (itemData, masterModelList.modelList[dataIndex].race);
            		break;
			
		case ageColumn:	
			if(dataIndex<masterModelList.modelList.size())
				SetDataBrowserItemDataText (itemData, masterModelList.modelList[dataIndex].age);            
			break;
			
        	case makeupColumn:	
			if(dataIndex<masterModelList.modelList.size())
				SetDataBrowserItemDataText (itemData, masterModelList.modelList[dataIndex].makeupType);
			break;
			
		default:
            		break;
    }
}

pascal void InitializeModelDataBrowser() {

	const       ControlID  dbControlID  = { 'SLST', 0 };
	SInt32      numRows;
	ControlRef  dbControl;
	DataBrowserCallbacks  dbCallbacks;
	
	GetControlByID (window2, &dbControlID, &dbControl);
	
	dbCallbacks.version = kDataBrowserLatestCallbacks;
	InitDataBrowserCallbacks (&dbCallbacks);
	
	dbCallbacks.u.v1.itemDataCallback =
	NewDataBrowserItemDataUPP((DataBrowserItemDataProcPtr)
							  ModelListDataCallback);
	
	SetDataBrowserCallbacks(dbControl, &dbCallbacks);
	
	SetAutomaticControlDragTrackingEnabledForWindow (window2, true);
	
	printf("POPULATING LIST.\n");
	numRows = masterModelList.ReturnTotalModels();
	AddDataBrowserItems (dbControl, kDataBrowserNoItem, numRows, NULL, kDataBrowserItemNoProperty );
}

pascal void ClearModelDataBrowser() {
	
	const       ControlID  dbControlID  = { 'SLST', 0 };
	ControlRef  dbControl;
	DataBrowserCallbacks  dbCallbacks;
	
	GetControlByID (window2, &dbControlID, &dbControl);
	
	dbCallbacks.version = kDataBrowserLatestCallbacks;
	InitDataBrowserCallbacks (&dbCallbacks);
	
	dbCallbacks.u.v1.itemDataCallback =
	NewDataBrowserItemDataUPP((DataBrowserItemDataProcPtr)
							  ModelListDataCallback);
	
	SetDataBrowserCallbacks(dbControl, &dbCallbacks);
	
	SetAutomaticControlDragTrackingEnabledForWindow (window2, true);
		
	RemoveDataBrowserItems (dbControl, kDataBrowserNoItem, 0,NULL, kDataBrowserItemNoProperty);
}

pascal bool ViewModelCommandHandler() {	
	
	bool outcome = true;
	
	// Get table info
	const       ControlID  dbControlID  = { 'SLST', 0 }; 
	ControlRef  dbControl;
	
	GetControlByID (window2, &dbControlID, &dbControl);   
	
	Handle selectedID = ::NewHandle(0);
	ItemCount size;
	
	printf("Running View Model Routine.\n");
	
	// Get selected item handle
	GetDataBrowserItems(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, selectedID);
	
	// Get selected item ID
	GetDataBrowserItemCount(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, &size);
	
	// If no model is selected, display error message, free handle, and return
	if(size<1){
		printf("No models selected!\n");
		outcome = false;
		
		DialogRef theItem;
		DialogItemIndex itemIndex;
		
		CreateStandardAlert(kAlertCautionAlert, 
							CFSTR("No Model Selected.\n"),
							CFSTR("Please select a model to view.\n"),
							NULL, &theItem);
		
		RunStandardAlert (theItem, NULL, &itemIndex);
		
		DisposeHandle(selectedID);
		
		return outcome;
	}
	
	// Extract itemID from handle
	HLock( selectedID );
	DataBrowserItemID *individualItem;
	individualItem = (DataBrowserItemID*)( *selectedID );
	printf("ID2: %d\n", *individualItem);
	
	CFStringRef modelName;
	CFStringRef imageName;
	CFStringRef makeupType;
	CFStringRef race;
	CFStringRef age;
	CFStringRef segment;
	CFStringRef marital;
	CFStringRef income;
	CFStringRef orientation;
	CFStringRef hair;
	CFStringRef smile;
	CFStringRef mirror;
	
	// Set Content Here
	for(int i=0; i<masterModelList.modelList.size(); i++)
		if(masterModelList.modelList[i].tableID == *individualItem){
			modelName = masterModelList.modelList[i].modelName;
			imageName = masterModelList.modelList[i].imageName;
			makeupType = masterModelList.modelList[i].makeupType;
			race = masterModelList.modelList[i].race;
			age = masterModelList.modelList[i].age;
			segment = masterModelList.modelList[i].segment;
			marital = masterModelList.modelList[i].marital;
			income = masterModelList.modelList[i].income;
			orientation = masterModelList.modelList[i].orientation;
			hair = masterModelList.modelList[i].hair;
			smile = masterModelList.modelList[i].smile;
			mirror = masterModelList.modelList[i].mirror;
			
		}
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    nameField;
	ControlHandle	 raceField;
	ControlHandle	 ageField;
	ControlHandle	 makeupField;
	ControlHandle	 segmentField;
	ControlHandle	 maritalField;
	ControlHandle	 incomeField;
	ControlHandle	 orientationField;
	ControlHandle    hairField;
	ControlHandle    smileField;
	ControlHandle    mirrorField;
	
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  nameFieldControlID = { viewnameFieldSignature, 
	viewnameFieldID }; 
	
	ControlID  raceFieldControlID = { viewraceFieldSignature, 
	viewraceFieldID }; 
	
	ControlID  ageFieldControlID = { viewageFieldSignature, 
	viewageFieldID }; 
	
	ControlID  makeupFieldControlID = { viewmakeupFieldSignature, 
	viewmakeupFieldID }; 
	
	ControlID  segmentFieldControlID = { viewsegmentFieldSignature, 
	viewsegmentFieldID }; 
	
	ControlID  maritalFieldControlID = { viewmaritalFieldSignature, 
	viewmaritalFieldID }; 
	
	ControlID  incomeFieldControlID = { viewincomeFieldSignature, 
	viewincomeFieldID }; 
	
	ControlID  orientationFieldControlID = { vieworientationFieldSignature, 
	vieworientationFieldID }; 
	
	ControlID  hairFieldControlID = { viewhairFieldSignature, 
	viewhairFieldID }; 
	
	ControlID  smileFieldControlID = { viewsmileFieldSignature, 
	viewsmileFieldID }; 
	
	ControlID  mirrorFieldControlID = { viewmirrorFieldSignature, 
	viewmirrorFieldID }; 
	
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (window5, &nameFieldControlID,               
					&nameField ); 
	
	GetControlByID (window5, &raceFieldControlID,               
					&raceField ); 
	
	GetControlByID (window5, &ageFieldControlID,               
					&ageField ); 
	
	GetControlByID (window5, &makeupFieldControlID,               
					&makeupField ); 
	
	GetControlByID (window5, &segmentFieldControlID,               
					&segmentField ); 
	
	GetControlByID (window5, &maritalFieldControlID,               
					&maritalField ); 
	
	GetControlByID (window5, &incomeFieldControlID,               
					&incomeField ); 
	
	GetControlByID (window5, &orientationFieldControlID,               
					&orientationField ); 
	
	GetControlByID (window5, &hairFieldControlID,               
					&hairField ); 
	
	GetControlByID (window5, &smileFieldControlID,               
					&smileField ); 
	
	GetControlByID (window5, &mirrorFieldControlID,               
					&mirrorField ); 

	
	// Set fields
	SetControlData( nameField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &modelName);
	SetControlData( raceField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &race);
	SetControlData( ageField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &age);
	SetControlData( makeupField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &makeupType);
	SetControlData( segmentField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &segment);
	SetControlData( maritalField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &marital);
	SetControlData( incomeField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &income);
	SetControlData( orientationField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &orientation);
	SetControlData( hairField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &hair);
	SetControlData( smileField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &smile);
	SetControlData( mirrorField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &mirror);
	
	// Convert CFStringRef to URL
	CFURLRef filenameURL = CFURLCreateWithString(kCFAllocatorDefault,imageName, NULL);
	CFShow(filenameURL);
	
	// load the image
	CGImageRef imagefile;
	CGDataProviderRef provider = CGDataProviderCreateWithURL( filenameURL );
	imagefile = CGImageCreateWithJPEGDataProvider( provider, NULL, false,  kCGRenderingIntentDefault );
	
	// find the control
	const HIViewID kImageViewID = {'vwpc', 601};
	HIViewRef imageViewRef = NULL;
	HIViewFindByID(HIViewGetRoot(window5), 
				   kImageViewID, &imageViewRef);
	
	// set the image into the view.
	HIImageViewSetImage( imageViewRef, imagefile ); // retains the image.

	HIViewSetNeedsDisplay(imageViewRef, TRUE);
	
	DisposeHandle(selectedID);
	
	return outcome;
}


pascal void GroupListDataCallback (ControlRef browser, DataBrowserItemID itemID, DataBrowserPropertyID property, DataBrowserItemDataRef itemData, Boolean changeValue) {

	long newItemID = itemID;
	int dataIndex = newItemID - 1;
	CFOptionFlags casechk;
	casechk= kCFCompareCaseInsensitive;
	
	if (!changeValue) switch (property) {
        
		case 'GRCL':	
			
			if(dataIndex<masterGroupList.groupList.size()){
				SetDataBrowserItemDataText (itemData, masterGroupList.groupList[dataIndex].groupName);
				masterGroupList.groupList[dataIndex].tableID = newItemID;
			}
			
			break;
			
		default:
			break;
	}
}

pascal void InitializeGroupListDataBrowser () {
	const       ControlID  dbControlID  = { 'GRDV', 711 };
	SInt32      numRows;
	ControlRef  dbControl;
	DataBrowserCallbacks  dbCallbacks;
	
	GetControlByID (gGroupListWindow, &dbControlID, &dbControl);
	
	dbCallbacks.version = kDataBrowserLatestCallbacks;
	InitDataBrowserCallbacks (&dbCallbacks);
	
	dbCallbacks.u.v1.itemDataCallback =
	NewDataBrowserItemDataUPP((DataBrowserItemDataProcPtr)
							  GroupListDataCallback);
	SetDataBrowserCallbacks(dbControl, &dbCallbacks);
	
	SetAutomaticControlDragTrackingEnabledForWindow (gGroupListWindow, true);
	
	printf("POPULATING GROUP LIST.\n");
	numRows = masterGroupList.groupList.size();
	AddDataBrowserItems (dbControl, kDataBrowserNoItem, numRows,
						 NULL, kDataBrowserItemNoProperty );
}

pascal void ClearGroupListDataBrowser() {
	
	const       ControlID  dbControlID  = { 'GRDV', 711 };
	ControlRef  dbControl;
	DataBrowserCallbacks  dbCallbacks;
	
	GetControlByID (gGroupListWindow, &dbControlID, &dbControl);
	
	dbCallbacks.version = kDataBrowserLatestCallbacks;
	InitDataBrowserCallbacks (&dbCallbacks);
	
	dbCallbacks.u.v1.itemDataCallback =
	NewDataBrowserItemDataUPP((DataBrowserItemDataProcPtr)
							  GroupListDataCallback);
	
	SetDataBrowserCallbacks(dbControl, &dbCallbacks);
	
	SetAutomaticControlDragTrackingEnabledForWindow (gGroupListWindow, true);
	
	RemoveDataBrowserItems (dbControl, kDataBrowserNoItem, 0,NULL, kDataBrowserItemNoProperty);
}

pascal void CancelAddGroupCommandHandler() {
	
	resetAddGroupDialog();
}

pascal void resetAddGroupDialog() {

	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    nameField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  nameFieldControlID = { AddGroupTextSignature, AddGroupTextID }; 
	
	CFStringRef blank = CFSTR("New Group");
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gAddGroupWindow, &nameFieldControlID,               
					&nameField ); 

		
	// Reset fields
	SetControlData( nameField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);

	CFRelease(blank);
}

pascal bool AddGroupCommandHandler() {
	
	bool outcome = true;
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    nameField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  nameFieldControlID = { AddGroupTextSignature, AddGroupTextID }; 
		
	CFStringRef nameInput;
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gAddGroupWindow, &nameFieldControlID,               
					&nameField ); 
	
	// Get Data from Input Field
	GetControlData( nameField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &nameInput, NULL); 
	
	printf("Running Add Group Routine\n");
	
	// Copy group name
	CFStringRef setName = CFStringCreateCopy(NULL, nameInput);
	
	if(masterGroupList.doesGroupExist(setName)) {
		DialogRef theItem;
		DialogItemIndex itemIndex;
		
		CreateStandardAlert(kAlertCautionAlert, 
							CFSTR("That group name already exists.\n"),
							CFSTR("Please choose a unique group name.\n"),
							NULL, &theItem);
		
		RunStandardAlert (theItem, NULL, &itemIndex);
		
		resetAddGroupDialog();
		outcome = false;
		return outcome;
	}
	
	else
		masterGroupList.AddGroup(setName);
		
	// Reset Fields
	resetAddGroupDialog();
	
	// Must always do this after getting a string from interface
	CFRelease(nameInput);

	return outcome;	
}

pascal bool DeleteGroupCommandHandler() {	
	
	bool outcome = true;
	
	// Get table info
	const       ControlID  dbControlID  = { 'GRDV', 711 };
	ControlRef  dbControl;
	
	GetControlByID (gGroupListWindow, &dbControlID, &dbControl);
	
	Handle selectedID = ::NewHandle(0);
	ItemCount size;
	
	printf("Running Delete Group Routine.\n");
	
	// Get selected item handle
	GetDataBrowserItems(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, selectedID);
	
	// Get selected item ID
	GetDataBrowserItemCount(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, &size);
	
	// If no group is selected, display error message, free handle, and return
	if(size<1){
		printf("No groups selected!\n");
		outcome = false;
		
		DialogRef theItem;
		DialogItemIndex itemIndex;
		
		CreateStandardAlert(kAlertCautionAlert,  
							CFSTR("No Group Selected.\n"),  
							CFSTR("Please select a group to delete.\n"),
							NULL, &theItem); 
		
		RunStandardAlert (theItem, NULL, &itemIndex);
		
		DisposeHandle(selectedID);
		
		return outcome;
	}
	
	// Extract itemID from handle
	DataBrowserItemID removeID = selectedID[0][0];
	printf("ID: %d\n", removeID);
	
	// Display Alert
	CFStringRef removename = masterGroupList.GetNameFromID(removeID);
	
	DialogRef theItem;
	DialogItemIndex itemIndex;
	
	struct AlertStdCFStringAlertParamRec params = {kStdCFStringAlertVersionOne,
		true, false, CFSTR("OK"), CFSTR("Cancel"), NULL, kAlertStdAlertOKButton,
		kAlertStdAlertCancelButton, kWindowAlertPositionParentWindowScreen,
	NULL};
	
	CreateStandardAlert(kAlertCautionAlert,
						removename,
						CFSTR("Are you sure you want to remove this group?"),
						&params, &theItem);
	
	RunStandardAlert (theItem, NULL, &itemIndex); 
	
	switch(itemIndex){
		case kAlertStdAlertOKButton:
			// Remove specified group from database
			masterGroupList.RemoveGroup(removename);
			break;
			
		case kAlertStdAlertCancelButton:
			outcome = false;
			break;
			
		default:break;
	}
	
	DisposeHandle(selectedID);
	
	return outcome;
}

pascal DataBrowserItemID GetGroupSelection() {
	
	bool outcome = true;
	
	// Get table info
	const       ControlID  dbControlID  = { 'GRDV', 711 };
	ControlRef  dbControl;
	
	GetControlByID (gGroupListWindow, &dbControlID, &dbControl);
	
	Handle selectedID = ::NewHandle(0);
	ItemCount size;
	
	printf("Running Edit Group Routine.\n");
	
	// Get selected item handle
	GetDataBrowserItems(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, selectedID);
	
	// Get selected item ID
	GetDataBrowserItemCount(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, &size);
	
	// If no group is selected, display error message, free handle, and return
	if(size<1){
		printf("No groups selected!\n");
		outcome = false;
		
		DialogRef theItem;
		DialogItemIndex itemIndex;
		
		CreateStandardAlert(kAlertCautionAlert,
							CFSTR("No Group Selected.\n"),
							CFSTR("Please select a group to edit.\n"),
							NULL, &theItem);
		
		RunStandardAlert (theItem, NULL, &itemIndex);
		
		DisposeHandle(selectedID);
		
		return -1;
	}
	
	// Extract itemID from handle
	DataBrowserItemID editID = selectedID[0][0];
	printf("ID: %d\n", editID);
	
	// Display Alert
	CFStringRef editname = masterGroupList.GetNameFromID(editID);
	CFShow(editname);
	
	DisposeHandle(selectedID);
	
	return editID;
}

pascal void ModelListGroupDataCallback (ControlRef browser, DataBrowserItemID itemID, DataBrowserPropertyID property, DataBrowserItemDataRef itemData, Boolean changeValue) {
	
    int dataIndex = itemID - 1;
	CFOptionFlags casechk;
	casechk= kCFCompareCaseInsensitive;
	
	if (!changeValue) switch (property) {
		case nameColumn:	
			
			SetDataBrowserItemDataText (itemData, masterModelList.modelList[dataIndex].modelName);
			masterModelList.modelList[dataIndex].tableID = itemID;
			break;
			
		case makeupColumn:	
		
			SetDataBrowserItemDataText (itemData,
			masterModelList.modelList[dataIndex].makeupType);
			break;
			
		default:
			break;
    }
}

pascal void InitializeModelGroupDataBrowser () {

	const       ControlID  dbControlID  = { 'MDL2', 751 };
	SInt32      numRows;
	ControlRef  dbControl;
	DataBrowserCallbacks  dbCallbacks;
	
	GetControlByID (gEditGroupWindow, &dbControlID, &dbControl);
	
	dbCallbacks.version = kDataBrowserLatestCallbacks;
	InitDataBrowserCallbacks (&dbCallbacks);
	
	dbCallbacks.u.v1.itemDataCallback =
	NewDataBrowserItemDataUPP((DataBrowserItemDataProcPtr)
							  ModelListGroupDataCallback);
	
	SetDataBrowserCallbacks(dbControl, &dbCallbacks);
	
	SetAutomaticControlDragTrackingEnabledForWindow (gEditGroupWindow, true);
	
	printf("POPULATING LIST.\n");
	numRows = masterModelList.ReturnTotalModels();
	AddDataBrowserItems (dbControl, kDataBrowserNoItem, numRows,
						 NULL, kDataBrowserItemNoProperty );
}

pascal void ClearModelGroupDataBrowser(){
	
	const       ControlID  dbControlID  = { 'MDL2', 751 };
	ControlRef  dbControl;
	DataBrowserCallbacks  dbCallbacks;
	
	GetControlByID (gEditGroupWindow, &dbControlID, &dbControl);
	
	dbCallbacks.version = kDataBrowserLatestCallbacks;
	InitDataBrowserCallbacks (&dbCallbacks);
	
	dbCallbacks.u.v1.itemDataCallback =
		NewDataBrowserItemDataUPP((DataBrowserItemDataProcPtr)
							  ModelListGroupDataCallback);
	
	SetDataBrowserCallbacks(dbControl, &dbCallbacks);
	
	SetAutomaticControlDragTrackingEnabledForWindow (gEditGroupWindow, true);
	
	RemoveDataBrowserItems (dbControl, kDataBrowserNoItem, 0,NULL, kDataBrowserItemNoProperty);
}

pascal void GroupMemberDataCallback (ControlRef browser, DataBrowserItemID itemID, DataBrowserPropertyID property, DataBrowserItemDataRef itemData, Boolean changeValue) {
	
	int dataIndex = itemID - 1;
	CFOptionFlags casechk;
	casechk= kCFCompareCaseInsensitive;
	
	if (!changeValue) switch (property) {
        
		case nameColumn:	
			SetDataBrowserItemDataText (itemData, masterGroupList.groupList[groupIndex].modelList[dataIndex].modelName);
			masterGroupList.groupList[groupIndex].modelList[dataIndex].tableID = itemID;
            		break;
			
		case makeupColumn:	
			SetDataBrowserItemDataText (itemData, masterGroupList.groupList[groupIndex].modelList[dataIndex].makeupType);
			break;
	
        	default:
			break;
	}	
}

pascal void InitializeGroupMemberDataBrowser (UInt32 groupIndex) {
	const       ControlID  dbControlID  = { 'MDL1', 750 };
	SInt32      numRows;
	ControlRef  dbControl;
	DataBrowserCallbacks  dbCallbacks;
	
	GetControlByID (gEditGroupWindow, &dbControlID, &dbControl);
	
	dbCallbacks.version = kDataBrowserLatestCallbacks;
	InitDataBrowserCallbacks (&dbCallbacks);
	
	dbCallbacks.u.v1.itemDataCallback =
		NewDataBrowserItemDataUPP((DataBrowserItemDataProcPtr)
							  GroupMemberDataCallback);
	
	SetDataBrowserCallbacks(dbControl, &dbCallbacks);
	
	SetAutomaticControlDragTrackingEnabledForWindow (gEditGroupWindow, true);
	
	printf("POPULATING LIST.\n");
	numRows = masterGroupList.groupList[groupIndex].modelList.size();
	AddDataBrowserItems (dbControl, kDataBrowserNoItem, numRows,
						 NULL, kDataBrowserItemNoProperty );
}

pascal void ClearGroupMemberDataBrowser() {
	
	const       ControlID  dbControlID  = { 'MDL1', 750 }; 
	ControlRef  dbControl;
	DataBrowserCallbacks  dbCallbacks;
	
	GetControlByID (gEditGroupWindow, &dbControlID, &dbControl);   
	
	dbCallbacks.version = kDataBrowserLatestCallbacks; 
	InitDataBrowserCallbacks (&dbCallbacks); 
	
	dbCallbacks.u.v1.itemDataCallback =
		NewDataBrowserItemDataUPP((DataBrowserItemDataProcPtr)
							  GroupMemberDataCallback); 

	SetDataBrowserCallbacks(dbControl, &dbCallbacks); 
	
	SetAutomaticControlDragTrackingEnabledForWindow (gEditGroupWindow, true); 
	
	RemoveDataBrowserItems (dbControl, kDataBrowserNoItem, 0,NULL, kDataBrowserItemNoProperty);
}


pascal bool AddGroupMemberCommandHandler() {
	
	bool outcome = true;
	
	// Get table info
	const       ControlID  dbControlID  = { 'MDL2', 751 }; 
	ControlRef  dbControl;
	
	GetControlByID (gEditGroupWindow, &dbControlID, &dbControl);   
	
	Handle selectedID = ::NewHandle(0);
	ItemCount size;
	
	printf("Running Add Model -> Group Routine.\n");
	
	// Get selected item handle
	GetDataBrowserItems(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, selectedID);
	
	// Get selected item ID
	GetDataBrowserItemCount(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, &size);
	
	// If no model is selected, display error message, free handle, and return
	if(size<1){
		printf("No model selected!\n");
		outcome = false;
		
		DialogRef theItem;
		DialogItemIndex itemIndex;
		
		CreateStandardAlert(kAlertCautionAlert,  
							CFSTR("No Model Selected.\n"),  
							CFSTR("Please select a model to add.\n"),
							NULL, &theItem); 
		
		RunStandardAlert (theItem, NULL, &itemIndex);
		
		DisposeHandle(selectedID);
		
		return outcome;
	}
	
	// Extract itemID from handle
	HLock( selectedID );
	DataBrowserItemID *individualItem;
	individualItem = (DataBrowserItemID*)( *selectedID );
	printf("ID2: %d\n", *individualItem);
	
	// Display Info
	CFStringRef modelname = masterModelList.GetNameFromID(*individualItem);
	CFShow(modelname);
	
	CFStringRef modelName;
	CFStringRef imageName;
	CFStringRef makeupType;
	CFStringRef race;
	CFStringRef age;
	CFStringRef segment;
	CFStringRef marital;
	CFStringRef income;
	CFStringRef orientation;
	CFStringRef hair;
	CFStringRef smile;
	CFStringRef mirror;
	
	// Sets Content
	for(int i=0; i<masterModelList.modelList.size(); i++)
		if(masterModelList.modelList[i].tableID == *individualItem){
			modelName = masterModelList.modelList[i].modelName;
			imageName = masterModelList.modelList[i].imageName;
			makeupType = masterModelList.modelList[i].makeupType;
			race = masterModelList.modelList[i].race;
			age = masterModelList.modelList[i].age;
			segment = masterModelList.modelList[i].segment;
			marital = masterModelList.modelList[i].marital;
			income = masterModelList.modelList[i].income;
			orientation = masterModelList.modelList[i].orientation;
			hair = masterModelList.modelList[i].hair;
			smile = masterModelList.modelList[i].smile;
			mirror = masterModelList.modelList[i].mirror;
			
		}
	
	// Get Group Name
	CFStringRef groupName = masterGroupList.GetNameFromID(groupID);
	
	// Add model to group
	masterGroupList.AddModelToGroup(groupName, *individualItem, modelName, imageName, makeupType, race, age, segment, 
									marital, income, orientation, hair, smile, mirror);
	
	DisposeHandle(selectedID);
	
	return outcome;
}

pascal bool DeleteGroupMemberCommandHandler() {
	
	bool outcome = true;
	
	// Get table info
	const       ControlID  dbControlID  = { 'MDL1', 750 }; 
	ControlRef  dbControl;
	
	GetControlByID (gEditGroupWindow, &dbControlID, &dbControl);   
	
	Handle selectedID = ::NewHandle(0);
	ItemCount size;
	
	printf("Running Remove Model -> Group Routine.\n");
	
	// Get selected item handle
	GetDataBrowserItems(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, selectedID);
	
	// Get selected item ID
	GetDataBrowserItemCount(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, &size);
	
	// If no model is selected, display error message, free handle, and return
	if(size<1){
		printf("No model selected!\n");
		outcome = false;
		
		DialogRef theItem;
		DialogItemIndex itemIndex;
		
		CreateStandardAlert(kAlertCautionAlert,  
							CFSTR("No Group Member Selected.\n"),  
							CFSTR("Please select a Group Member to remove.\n"),
							NULL, &theItem); 
		
		RunStandardAlert (theItem, NULL, &itemIndex);
		
		DisposeHandle(selectedID);
		
		return outcome;
	}
	
	// Extract itemID from handle
	HLock( selectedID );
	DataBrowserItemID *individualItem;
	individualItem = (DataBrowserItemID*)( *selectedID );
	printf("ID2: %d\n", *individualItem);
	
	// Get Group Name
	CFStringRef groupName = masterGroupList.GetNameFromID(groupID);
	
	// Remove Model from Group
	masterGroupList.RemoveModelFromGroup(groupName, *individualItem);

	DisposeHandle(selectedID);
	
	return outcome;
}

pascal void InitializeTrialGroupListDataBrowser () {

	const       ControlID  dbControlID  = { 'GRCH', 801 }; 
	SInt32      numRows;
	ControlRef  dbControl;
	DataBrowserCallbacks  dbCallbacks;
	
	GetControlByID (gNewTrialWindow, &dbControlID, &dbControl);   
	
	dbCallbacks.version = kDataBrowserLatestCallbacks; 
	InitDataBrowserCallbacks (&dbCallbacks); 
	
	dbCallbacks.u.v1.itemDataCallback =
		NewDataBrowserItemDataUPP((DataBrowserItemDataProcPtr)
							  GroupListDataCallback); 
	
	SetDataBrowserCallbacks(dbControl, &dbCallbacks); 
	
	SetAutomaticControlDragTrackingEnabledForWindow (gNewTrialWindow, true); 
	
	printf("POPULATING TRIAL GROUP LIST.\n");
	numRows = masterGroupList.groupList.size();
	AddDataBrowserItems (dbControl, kDataBrowserNoItem, numRows,
						 NULL, kDataBrowserItemNoProperty ); 
}

pascal void ClearTrialGroupListDataBrowser() {
	
	const       ControlID  dbControlID  = { 'GRCH', 801 }; 
	ControlRef  dbControl;
	DataBrowserCallbacks  dbCallbacks;
	
	GetControlByID (gNewTrialWindow, &dbControlID, &dbControl);   
	
	dbCallbacks.version = kDataBrowserLatestCallbacks; 
	InitDataBrowserCallbacks (&dbCallbacks); 
	
	dbCallbacks.u.v1.itemDataCallback =
		NewDataBrowserItemDataUPP((DataBrowserItemDataProcPtr)
							  GroupListDataCallback); 
	
	SetDataBrowserCallbacks(dbControl, &dbCallbacks); 
	
	SetAutomaticControlDragTrackingEnabledForWindow (gNewTrialWindow, true); 
	
	RemoveDataBrowserItems (dbControl, kDataBrowserNoItem, 0,NULL, kDataBrowserItemNoProperty);	
}

pascal void ResetNewTrialWindow() {
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    nameField;
	ControlHandle	 raceField;
	ControlHandle	 ageField;
	ControlHandle	 idField;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  nameFieldControlID = { userNameSignature, 
	userNameID }; 
	
	ControlID  raceFieldControlID = { userRaceSignature, 
	userRaceID }; 
	
	ControlID  ageFieldControlID = { userAgeSignature, 
	userAgeID }; 
	
	ControlID  idFieldControlID = { userIDSignature, 
	userIDID }; 
	
	CFStringRef blank = CFSTR("");
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gNewTrialWindow, &nameFieldControlID,               
					&nameField ); 
	
	GetControlByID (gNewTrialWindow, &raceFieldControlID,               
					&raceField ); 
	
	GetControlByID (gNewTrialWindow, &ageFieldControlID,               
					&ageField ); 
	
	GetControlByID (gNewTrialWindow, &idFieldControlID,               
					&idField ); 
	
	// Reset fields
	SetControlData( nameField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	SetControlData( raceField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	SetControlData( ageField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	SetControlData( idField, 0, kControlEditTextCFStringTag,  
				   sizeof (CFStringRef), &blank);
	

	// Reset Radio buttons
	HIViewID radioButtonsID = {'BTSL', 802 };
	
	HIViewRef radioButtonRef = NULL;
	OSStatus status = HIViewFindByID(HIViewGetRoot(gNewTrialWindow), 
									 radioButtonsID, &radioButtonRef);
	verify_noerr(status);
	
	status= HIViewSetValue(radioButtonRef, 1);
	verify_noerr(status);
	
	CFRelease(blank);
}

pascal int BeginNewTrialCommandHandler() {
	
	int trialNumber = 0;
	
	// Get table info
	const       ControlID  dbControlID  = { 'GRCH', 801 }; 
	ControlRef  dbControl;
	
	GetControlByID (gNewTrialWindow, &dbControlID, &dbControl);   
	
	Handle selectedID = ::NewHandle(0);
	ItemCount size;
	
	printf("Saving Group Choice.\n");
	
	// Get selected item handle
	GetDataBrowserItems(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, selectedID);
	
	// Get selected item ID
	GetDataBrowserItemCount(dbControl, kDataBrowserNoItem, false, kDataBrowserItemIsSelected, &size);
	
	// If no group is selected, display error message, free handle, and return
	if(size<1){
		printf("No group selected!\n");
		
		DialogRef theItem;
		DialogItemIndex itemIndex;
		
		CreateStandardAlert(kAlertCautionAlert,  
							CFSTR("No Group Selected.\n"),  
							CFSTR("Please select a group to use in this trial.\n"),
							NULL, &theItem); 
		
		RunStandardAlert (theItem, NULL, &itemIndex);
		
		DisposeHandle(selectedID);
		
		return 0;
	}
	
	// Extract itemID from handle
	DataBrowserItemID viewID = selectedID[0][0];
	printf("ID: %d\n", viewID);
	
	// Display Info
	
	CFStringRef groupname = masterGroupList.GetNameFromID(viewID);
	int inID = masterGroupList.GetIndexFromID(viewID);
	CFShow(groupname);
	printf("vector index: %d\n", inID);
	
	// Save group vector index
	currentTrial.SetGroupID(inID);
	
	CFStringRef userName;
	CFStringRef userRace;
	CFStringRef userAge;
	CFStringRef userID;
	
	// ControlHandle Declarations
	// ControlHandles correspond to different window elements
	ControlHandle    nameField;
	ControlHandle	 raceField;
	ControlHandle	 ageField;
	ControlHandle	 idField;
	ControlHandle	 buttonGroup;
	ControlHandle	 SexbuttonGroup;
	
	// ControlID Declarations
	// ControlIDs are the Signature (mnme) and numerical identifier (509) of different window elements
	ControlID  nameFieldControlID = { userNameSignature, 
	userNameID }; 
	
	ControlID  raceFieldControlID = { userRaceSignature, 
	userRaceID }; 
	
	ControlID  ageFieldControlID = { userAgeSignature, 
	userAgeID }; 
	
	ControlID  idFieldControlID = { userIDSignature, 
	userIDID }; 
	
	ControlID  buttonGroupControlID = { trialBatterySignature, 
	trialBatteryID }; 
	
	ControlID  sexbuttonGroupControlID = { userSexSignature, 
	userSexID }; 
	
	// Assign ControlHandles
	// GetControlByID creates the ControlHandles based on the ControlIDs
	GetControlByID (gNewTrialWindow, &nameFieldControlID,               
					&nameField ); 
	
	GetControlByID (gNewTrialWindow, &raceFieldControlID,               
					&raceField ); 
	
	GetControlByID (gNewTrialWindow, &ageFieldControlID,               
					&ageField ); 
	
	GetControlByID (gNewTrialWindow, &idFieldControlID,               
					&idField ); 
	
	GetControlByID (gNewTrialWindow, &buttonGroupControlID,               
					&buttonGroup ); 
	
	GetControlByID (gNewTrialWindow, &sexbuttonGroupControlID,               
					&SexbuttonGroup ); 
	
	
	
	// Get Data from Input Field
	GetControlData( nameField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &userName, NULL); 
	
	GetControlData( raceField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &userRace, NULL); 
	
	GetControlData( ageField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &userAge, NULL); 
	
	GetControlData( idField, 0, kControlEditTextCFStringTag,    
				   sizeof (CFStringRef), &userID, NULL); 
	
	trialNumber = GetControl32BitValue(buttonGroup);
	
	// Set Trial ID
	currentTrial.trialID = trialNumber;
	
	int userSex = GetControl32BitValue(SexbuttonGroup);
	
	
	CFStringRef setSex;
	if(userSex==1)
		setSex = CFSTR("Female");
	if(userSex==2)
		setSex = CFSTR("Male");
	
	
	printf("Saving User Information\n");
	
	// copy user name
	CFStringRef setName = CFStringCreateCopy(NULL, userName);
	
	// copy user id
	CFStringRef setID = CFStringCreateCopy(NULL, userID);
	
	// copy user race
	CFStringRef setRace = CFStringCreateCopy(NULL, userRace);
	
	// copy user age
	CFStringRef setAge = CFStringCreateCopy(NULL, userAge);
	
	
	// Save User information
	currentTrial.SetUserData(setName, setID, setAge, setRace, setSex);
	
	currentTrial.SetEnd(masterGroupList.groupList[inID].modelList.size());
		
	if(masterGroupList.groupList[inID].modelList.size()==0){
		currentTrial.ResetTrial();
		return 0;
	}
	
	currentTrial.PrintTrial();
	printf("Trial Selected: %d\n", trialNumber);
	
	
	// Must always do this after getting a string from interface
	CFRelease(userName);
	CFRelease(userRace);
	CFRelease(userAge);
	CFRelease(userID);
	
	DisposeHandle(selectedID);
	
	return trialNumber;
}

pascal void DrawBatteryACurrentModel() {
	
	// Get current model's image name
	CFStringRef imageName;
	imageName = masterGroupList.groupList[currentTrial.groupID].modelList[currentTrial.currentModel].imageName;
	
	// Convert CFStringRef to URL
	CFURLRef filenameURL = CFURLCreateWithString(kCFAllocatorDefault,imageName, NULL);
	CFShow(filenameURL);
	
	// load the image
	CGImageRef imagefile;
	CGDataProviderRef provider = CGDataProviderCreateWithURL( filenameURL );
	imagefile = CGImageCreateWithJPEGDataProvider( provider, NULL, false,  kCGRenderingIntentDefault );
	
	// find the control
	const HIViewID kImageViewID = {'TROP', 811};
	HIViewRef imageViewRef = NULL;
	HIViewFindByID(HIViewGetRoot(gBatteryAWindow), 
				   kImageViewID, &imageViewRef);
	
	// set the image into the view.
	HIImageViewSetImage( imageViewRef, imagefile );
	
	HIViewSetNeedsDisplay(imageViewRef, TRUE);
}



