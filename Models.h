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

#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>

using namespace std;

class Model{
public:
	Model();
	Model(DataBrowserItemID, CFStringRef modelname, CFStringRef imagename, CFStringRef makeuptype,
		  CFStringRef Race, CFStringRef Age, CFStringRef Segment, CFStringRef Marital, CFStringRef Income,
		  CFStringRef Orientation, CFStringRef Hair, CFStringRef Smile, CFStringRef Mirror);
	
	void PrintModels();
	
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
	bool used;
	
	DataBrowserItemID tableID;
	DataBrowserItemID grouptableID;
};

class ModelDB{
public:
	ModelDB();
	
	void AddModel(DataBrowserItemID, CFStringRef, CFStringRef, CFStringRef, CFStringRef, CFStringRef,
				  CFStringRef,CFStringRef,CFStringRef,CFStringRef,CFStringRef,CFStringRef,CFStringRef);
	void RemoveModel(DataBrowserItemID);
	void SaveModels();
	void RebuildModels();
	int ReturnTotalModels();
	void PrintDatabase();
	CFStringRef GetNameFromID(DataBrowserItemID);
	CFStringRef GetPicFromID(DataBrowserItemID);
	CFStringRef GetMakeupFromID(DataBrowserItemID);
	
	vector<Model> modelList;
	int modelTotal;
};

class Group{
public:
	Group();
	void AddModel(DataBrowserItemID, CFStringRef, CFStringRef, CFStringRef, CFStringRef, CFStringRef,
				  CFStringRef,CFStringRef,CFStringRef,CFStringRef,CFStringRef,CFStringRef,CFStringRef);
	void RemoveModel(DataBrowserItemID);
	
	CFStringRef groupName;
	DataBrowserItemID tableID;
	DataBrowserItemID grouptableID;
	
	vector<Model> modelList;
};

class Trial{
public:
	
	Trial();
	
	int trialID;
	int groupID;
	int counter;
	int currentModel;
	int trialMode;
	int end;
	
	void IncrementCounter();
	void SetGroupID(int inID);
	void SetEnd(int inEnd);
	bool isOver();
	void PrintTrial();
	void ResetTrial();
	bool isUsed(int nextMod);
	void SetACompRating(int comp);
	void SetATrustRating(int trust);
	void SetALikeRating(int like);
	void SetAAttrRating(int attr);
	void SetUserData(CFStringRef inName, CFStringRef inID, CFStringRef inAge, CFStringRef inRace, CFStringRef inSex);
	void SetUserSurveyData(CFStringRef setMarital, CFStringRef setIncome, CFStringRef setOrientation, CFStringRef setKids);
	void SetBatteryCData(int health, int dare, int attentive, int sociable, int caring, int stable, int hire, CFStringRef ageBox);
	
	// Sets currentModelID to new model
	// Returns true if new model was found, false if no new models
	bool nextModel();
	
	void SaveBatteryA();
	void SaveBatteryB();
	void SaveBatteryC();
	
	CFStringRef userName;
	CFStringRef userID;
	CFStringRef userAge;
	CFStringRef userRace;
	CFStringRef userSex;
	CFStringRef userMarital;
	CFStringRef userIncome;
	CFStringRef userOrientation;
	CFStringRef userKids;
	
	vector<vector<int> > ratings;
	
};

class Groups{
public:
	Groups(){}
	void AddGroup(CFStringRef ingroupName);
	void RemoveGroup(CFStringRef ingroupName);
	void SaveGroups();
	void RebuildGroups();
	
	void AddModelToGroup(CFStringRef, DataBrowserItemID, CFStringRef, CFStringRef, CFStringRef, CFStringRef, CFStringRef,
							   CFStringRef,CFStringRef,CFStringRef,CFStringRef,CFStringRef,CFStringRef,CFStringRef);
	void RemoveModelFromGroup(CFStringRef ingroupName, DataBrowserItemID removeID); 
	bool UniversalRemoveModelFromGroup(CFStringRef modelName, CFStringRef modelPic, CFStringRef makeupType);
	
	bool doesGroupExist(CFStringRef ingroupName);
	void PrintGroups();
	CFStringRef GetNameFromID(DataBrowserItemID checkID);
	UInt32 GetIndexFromID(DataBrowserItemID checkID);
	
	vector<Group> groupList;
};
	
Model::Model(){
	
	modelName = CFSTR("Empty");
	imageName = CFSTR("Empty");
	makeupType = CFSTR("Empty");
	race = CFSTR("Empty");
	age = CFSTR("Empty");
	segment = CFSTR("Empty");
	marital = CFSTR("Empty");
	income = CFSTR("Empty");
	orientation = CFSTR("Empty");
	hair = CFSTR("Empty");
	smile = CFSTR("Empty");
	mirror = CFSTR("Empty");
	
	used = false;
	
	tableID = -1;
	grouptableID = -1;
}

Model::Model(DataBrowserItemID inID, CFStringRef modelname, CFStringRef imagename, CFStringRef makeuptype,
			 CFStringRef Race, CFStringRef Age, CFStringRef Segment, CFStringRef Marital, CFStringRef Income,
			 CFStringRef Orientation, CFStringRef Hair, CFStringRef Smile, CFStringRef Mirror)
{
	modelName = modelname;
	imageName = imagename;
	makeupType = makeuptype;
	race = Race;
	age = Age;
	tableID = inID;
	segment = Segment;
	marital = Marital;
	income = Income;
	orientation = Orientation;
	hair = Hair;
	smile = Smile;
	mirror = Mirror;
	used = false;
	
}

void Model::PrintModels(){
	
	CFShow(modelName);
	CFShow(imageName);
	CFShow(makeupType);
	CFShow(race);	
	CFShow(age);
	CFShow(segment);
	CFShow(marital);
	CFShow(income);
	CFShow(orientation);
	CFShow(hair);
	CFShow(smile);
	CFShow(mirror);
	printf("ID: %d\n", tableID);
	printf("\n");
	
}

ModelDB::ModelDB(){
	
	modelTotal = 0;
}

void ModelDB::AddModel(DataBrowserItemID inID, CFStringRef name, CFStringRef pic, CFStringRef makeup, CFStringRef race, 
					   CFStringRef age, CFStringRef Segment, CFStringRef Marital, CFStringRef Income,
					   CFStringRef Orientation, CFStringRef Hair, CFStringRef Smile, CFStringRef Mirror)
{
	
	Model newModel(inID, name, pic, makeup, race, age, Segment, Marital, Income, Orientation, Hair, Smile, Mirror);
	
	modelList.push_back(newModel);
	
	modelTotal++;
	
}

void ModelDB::RemoveModel(DataBrowserItemID removeID){
	
	for(int i=0; i<modelList.size(); i++)
		if(modelList[i].tableID == removeID){
			printf("MODEL FOUND.\n");
			printf("REMOVING ");
			CFShow(modelList[i].modelName);
			modelList.erase(modelList.begin()+i);
			printf("I : %d \n", i);
		}
	
	printf("**************************************\n");
	for(int i=0; i<modelList.size(); i++)
		CFShow(modelList[i].modelName);
	printf("**************************************\n");
	
	
	modelTotal--;
}

void ModelDB::PrintDatabase(){
	
	for(int i=0; i<modelList.size(); i++)
		modelList[i].PrintModels();
}

CFStringRef ModelDB::GetNameFromID(DataBrowserItemID checkID){
	
	for(int i=0; i<modelList.size(); i++)
		if(modelList[i].tableID == checkID)
			return modelList[i].modelName;
	
	return CFSTR("[Model]");
}

CFStringRef ModelDB::GetPicFromID(DataBrowserItemID checkID){
	
	for(int i=0; i<modelList.size(); i++)
		if(modelList[i].tableID == checkID)
			return modelList[i].imageName;
	
	return CFSTR("[Pic]");
}

CFStringRef ModelDB::GetMakeupFromID(DataBrowserItemID checkID){
	
	for(int i=0; i<modelList.size(); i++)
		if(modelList[i].tableID == checkID)
			return modelList[i].makeupType;
	
	return CFSTR("[Makeup]");
}

int ModelDB::ReturnTotalModels(){
	
	return modelList.size();
	
}

void ModelDB::SaveModels(){
	

	fstream Output("Model_Database.dat", ios::out);
	
	Output << modelList.size() << "\n\n";
	
	for(int i=0; i<modelList.size(); i++){
		
		// copy from a CFString into a local c string
		const int kBufferSize = 256;
		char model_name[kBufferSize];
		char model_pic[kBufferSize];
		char model_makeup[kBufferSize];
		char model_race[kBufferSize];
		char model_age[kBufferSize];
		char model_segment[kBufferSize];
		char model_marital[kBufferSize];
		char model_income[kBufferSize];
		char model_orientation[kBufferSize];
		char model_hair[kBufferSize];
		char model_smile[kBufferSize];
		char model_mirror[kBufferSize];
		
		CFStringGetCString(modelList[i].modelName,model_name,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].imageName,model_pic,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].makeupType,model_makeup,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].race,model_race,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].age,model_age,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].segment,model_segment,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].marital,model_marital,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].income,model_income,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].orientation,model_orientation,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].hair,model_hair,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].smile,model_smile,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(modelList[i].mirror,model_mirror,kBufferSize, kCFStringEncodingMacRoman);
		
		Output << "#" << "\n";
		Output << model_name << "\n";
		Output << model_pic << "\n";
		Output << model_makeup << "\n";
		Output << model_race << "\n";
		Output << model_age << "\n";
		Output << model_segment << "\n";
		Output << model_marital << "\n";
		Output << model_income << "\n";
		Output << model_orientation << "\n";
		Output << model_hair << "\n";
		Output << model_smile << "\n";
		Output << model_mirror << "\n";
	}
	
	
	Output.close();
	
}

void ModelDB::RebuildModels(){
	
	fstream Input("Model_Database.dat", ios::in);
	
	if (Input.is_open())
	{
		printf("Model Database Opened.\n");
		while (! Input.eof() )
		{

			string dummy;
			getline (Input,dummy);
			
			if(dummy.compare("#") == 0){
				string model_name;
				string model_pic;
				string model_makeup;
				string model_race;
				string model_age;
				string model_segment;
				string model_marital;
				string model_income;
				string model_orientation;
				string model_hair;
				string model_smile;
				string model_mirror;
				
				getline (Input,model_name);
				getline (Input,model_pic);
				getline (Input,model_makeup);
				getline (Input,model_race);
				getline (Input,model_age);
				getline (Input,model_segment);
				getline (Input,model_marital);
				getline (Input,model_income);
				getline (Input,model_orientation);
				getline (Input,model_hair);
				getline (Input,model_smile);
				getline (Input,model_mirror);
				
				CFStringRef inName = CFStringCreateWithCString (kCFAllocatorDefault, model_name.c_str(), kCFStringEncodingUTF8);
				CFStringRef inPic = CFStringCreateWithCString (kCFAllocatorDefault, model_pic.c_str(), kCFStringEncodingUTF8);
				CFStringRef inMakeup = CFStringCreateWithCString (kCFAllocatorDefault, model_makeup.c_str(), kCFStringEncodingUTF8);
				CFStringRef inRace = CFStringCreateWithCString (kCFAllocatorDefault, model_race.c_str(), kCFStringEncodingUTF8);
				CFStringRef inAge = CFStringCreateWithCString (kCFAllocatorDefault, model_age.c_str(), kCFStringEncodingUTF8);
				CFStringRef inSegment = CFStringCreateWithCString (kCFAllocatorDefault, model_segment.c_str(), kCFStringEncodingUTF8);
				CFStringRef inMarital = CFStringCreateWithCString (kCFAllocatorDefault, model_marital.c_str(), kCFStringEncodingUTF8);
				CFStringRef inIncome = CFStringCreateWithCString (kCFAllocatorDefault, model_income.c_str(), kCFStringEncodingUTF8);
				CFStringRef inOrientation = CFStringCreateWithCString (kCFAllocatorDefault, model_orientation.c_str(), kCFStringEncodingUTF8);
				CFStringRef inHair = CFStringCreateWithCString (kCFAllocatorDefault, model_hair.c_str(), kCFStringEncodingUTF8);
				CFStringRef inSmile = CFStringCreateWithCString (kCFAllocatorDefault, model_smile.c_str(), kCFStringEncodingUTF8);
				CFStringRef inMirror = CFStringCreateWithCString (kCFAllocatorDefault, model_mirror.c_str(), kCFStringEncodingUTF8);
			
				AddModel(0, inName,  inPic,  inMakeup,  inRace, 
						 inAge,  inSegment,  inMarital,  inIncome,
						 inOrientation,  inHair,  inSmile, inMirror);
				
			}
			
			
		}
		Input.close();
	}
	
	Input.close();
	
}

Group::Group(){
	
	tableID = -1;
	groupName = CFSTR("[EMPTY]");
	
}

void Group::AddModel(DataBrowserItemID inID, CFStringRef name, CFStringRef pic, CFStringRef makeup, CFStringRef race, 
					   CFStringRef age, CFStringRef Segment, CFStringRef Marital, CFStringRef Income,
					   CFStringRef Orientation, CFStringRef Hair, CFStringRef Smile, CFStringRef Mirror) {
	
	Model newModel(inID, name, pic, makeup, race, age, Segment, Marital, Income, Orientation, Hair, Smile, Mirror);
	
	modelList.push_back(newModel);
}

void Group::RemoveModel(DataBrowserItemID removeID){
	
	for(int i=0; i<modelList.size(); i++)
		if(modelList[i].tableID == removeID){
			printf("MODEL FOUND.\n");
			printf("REMOVING ");
			CFShow(modelList[i].modelName);
			modelList.erase(modelList.begin()+i);
			printf("I : %d \n", i);
		}
}

void Groups::AddModelToGroup(CFStringRef ingroupName, DataBrowserItemID inID, CFStringRef name, CFStringRef pic, CFStringRef makeup, CFStringRef race, 
					  CFStringRef age, CFStringRef Segment, CFStringRef Marital, CFStringRef Income,
					  CFStringRef Orientation, CFStringRef Hair, CFStringRef Smile, CFStringRef Mirror) {

	for(int i=0; i<groupList.size(); i++)
		if(CFStringCompare(groupList[i].groupName, ingroupName, kCFCompareCaseInsensitive) == 0){
			groupList[i].AddModel( inID,  name,  pic,  makeup,  race, 
								    age, Segment,  Marital,  Income,
								   Orientation,  Hair,  Smile, Mirror);
		}
}

void Groups::RemoveModelFromGroup(CFStringRef ingroupName, DataBrowserItemID removeID){
	
	for(int i=0; i<groupList.size(); i++)
		if(CFStringCompare(groupList[i].groupName, ingroupName, kCFCompareCaseInsensitive) == 0)
			for(int j=0; j<groupList[i].modelList.size(); j++)
				if(groupList[i].modelList[j].tableID == removeID){
					printf("MODEL FOUND IN SPECIFIED GROUP.\n");
					printf("REMOVING ");
					CFShow(groupList[i].modelList[j].modelName);
					groupList[i].modelList.erase(groupList[i].modelList.begin()+j);
				}
	
}

bool Groups::UniversalRemoveModelFromGroup(CFStringRef modelName, CFStringRef modelPic, CFStringRef makeupType){
	
	bool removed = true;
	
	for(int i=0; i<groupList.size(); i++)
			for(int j=0; j<groupList[i].modelList.size(); j++)
				if(CFStringCompare(groupList[i].modelList[j].imageName, modelPic, kCFCompareCaseInsensitive) == 0)
					if(CFStringCompare(groupList[i].modelList[j].modelName, modelName, kCFCompareCaseInsensitive) == 0)
						if(CFStringCompare(groupList[i].modelList[j].makeupType, makeupType, kCFCompareCaseInsensitive) == 0){
							printf("MODEL FOUND IN UNIVERSAL SEARCH.\n");
							printf("REMOVING ");
							CFShow(groupList[i].modelList[j].modelName);
							groupList[i].modelList.erase(groupList[i].modelList.begin()+j);
							return removed;
						}
	removed = false;
	return removed;
}
	


void Groups::AddGroup(CFStringRef ingroupName){
	
	Group newGroup;
	newGroup.groupName = ingroupName;
	
	groupList.push_back(newGroup);
}

void Groups::RemoveGroup(CFStringRef ingroupName){
	
	for(int i=0; i<groupList.size(); i++)
		if(CFStringCompare(groupList[i].groupName, ingroupName, kCFCompareCaseInsensitive) == 0){
			printf("GROUP FOUND.\n");
			printf("REMOVING ");
			CFShow(groupList[i].groupName);
			groupList.erase(groupList.begin()+i);
		}
}

bool Groups::doesGroupExist(CFStringRef ingroupName){
	
	for(int i=0; i<groupList.size(); i++)
		if(CFStringCompare(groupList[i].groupName, ingroupName, kCFCompareCaseInsensitive) == 0)
			return true;
	
	return false;
}

CFStringRef Groups::GetNameFromID(DataBrowserItemID checkID){
	
	
	for(int i=0; i<groupList.size(); i++)
		if(groupList[i].tableID == checkID)
			return groupList[i].groupName;
	
	return CFSTR("[Group]");
}

UInt32 Groups::GetIndexFromID(DataBrowserItemID checkID){
	
	
	for(int i=0; i<groupList.size(); i++)
		if(groupList[i].tableID == checkID)
			return i;
	
	return -1;
}

void Groups::PrintGroups(){
	printf("Printing Groups.\n");
	for(int i=0; i<groupList.size(); i++){
		CFShow(groupList[i].groupName);
		for(int j=0; j<groupList[i].modelList.size(); j++)
			CFShow(groupList[i].modelList[j].modelName);
	}
}
	
void Groups::SaveGroups(){
	
	fstream Output("Group_Database.dat", ios::out);
	
	for(int j=0; j<groupList.size(); j++)
	for(int i=0; i<groupList[j].modelList.size(); i++){
		
		// copy from a CFString into a local c string
		const int kBufferSize = 256;
		char group_name[kBufferSize];
		char model_name[kBufferSize];
		char model_pic[kBufferSize];
		char model_makeup[kBufferSize];
		char model_race[kBufferSize];
		char model_age[kBufferSize];
		char model_segment[kBufferSize];
		char model_marital[kBufferSize];
		char model_income[kBufferSize];
		char model_orientation[kBufferSize];
		char model_hair[kBufferSize];
		char model_smile[kBufferSize];
		char model_mirror[kBufferSize];
		
		CFStringGetCString(groupList[j].groupName, group_name, kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].modelName,model_name,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].imageName,model_pic,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].makeupType,model_makeup,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].race,model_race,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].age,model_age,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].segment,model_segment,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].marital,model_marital,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].income,model_income,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].orientation,model_orientation,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].hair,model_hair,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].smile,model_smile,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(groupList[j].modelList[i].mirror,model_mirror,kBufferSize, kCFStringEncodingMacRoman);
		
		Output << "#" << "\n";
		Output << group_name << "\n";
		Output << model_name << "\n";
		Output << model_pic << "\n";
		Output << model_makeup << "\n";
		Output << model_race << "\n";
		Output << model_age << "\n";
		Output << model_segment << "\n";
		Output << model_marital << "\n";
		Output << model_income << "\n";
		Output << model_orientation << "\n";
		Output << model_hair << "\n";
		Output << model_smile << "\n";
		Output << model_mirror << "\n";
	}
	
	Output.close();	
}

void Groups::RebuildGroups(){
	
	fstream Input("Group_Database.dat", ios::in);
	
	if (Input.is_open())
	{
		printf("Group Database Opened.\n");
		while (! Input.eof() )
		{
			
			string dummy;
			getline (Input,dummy);
			
			if(dummy.compare("#") == 0){
				string group_name;
				string model_name;
				string model_pic;
				string model_makeup;
				string model_race;
				string model_age;
				string model_segment;
				string model_marital;
				string model_income;
				string model_orientation;
				string model_hair;
				string model_smile;
				string model_mirror;
				
				getline (Input, group_name);
				getline (Input,model_name);
				getline (Input,model_pic);
				getline (Input,model_makeup);
				getline (Input,model_race);
				getline (Input,model_age);
				getline (Input,model_segment);
				getline (Input,model_marital);
				getline (Input,model_income);
				getline (Input,model_orientation);
				getline (Input,model_hair);
				getline (Input,model_smile);
				getline (Input,model_mirror);
				
				CFStringRef inGroup = CFStringCreateWithCString(kCFAllocatorDefault, group_name.c_str(), kCFStringEncodingUTF8);
				CFStringRef inName = CFStringCreateWithCString (kCFAllocatorDefault, model_name.c_str(), kCFStringEncodingUTF8);
				CFStringRef inPic = CFStringCreateWithCString (kCFAllocatorDefault, model_pic.c_str(), kCFStringEncodingUTF8);
				CFStringRef inMakeup = CFStringCreateWithCString (kCFAllocatorDefault, model_makeup.c_str(), kCFStringEncodingUTF8);
				CFStringRef inRace = CFStringCreateWithCString (kCFAllocatorDefault, model_race.c_str(), kCFStringEncodingUTF8);
				CFStringRef inAge = CFStringCreateWithCString (kCFAllocatorDefault, model_age.c_str(), kCFStringEncodingUTF8);
				CFStringRef inSegment = CFStringCreateWithCString (kCFAllocatorDefault, model_segment.c_str(), kCFStringEncodingUTF8);
				CFStringRef inMarital = CFStringCreateWithCString (kCFAllocatorDefault, model_marital.c_str(), kCFStringEncodingUTF8);
				CFStringRef inIncome = CFStringCreateWithCString (kCFAllocatorDefault, model_income.c_str(), kCFStringEncodingUTF8);
				CFStringRef inOrientation = CFStringCreateWithCString (kCFAllocatorDefault, model_orientation.c_str(), kCFStringEncodingUTF8);
				CFStringRef inHair = CFStringCreateWithCString (kCFAllocatorDefault, model_hair.c_str(), kCFStringEncodingUTF8);
				CFStringRef inSmile = CFStringCreateWithCString (kCFAllocatorDefault, model_smile.c_str(), kCFStringEncodingUTF8);
				CFStringRef inMirror = CFStringCreateWithCString (kCFAllocatorDefault, model_mirror.c_str(), kCFStringEncodingUTF8);
			
				if(! doesGroupExist(inGroup))
					AddGroup(inGroup);
				
				AddModelToGroup(inGroup, 0, inName,  inPic,  inMakeup,  inRace, 
						 inAge,  inSegment,  inMarital,  inIncome,
						 inOrientation,  inHair,  inSmile, inMirror);
				
			}
			
			
		}

		Input.close();
	}
	
	Input.close();
}


// -----------------------------------------------------------------------------------------//

Groups						masterGroupList;

Trial::Trial(){
	
	trialID = 0;
	groupID = -1;
	counter = 0;
	currentModel = 0;
	trialMode = 0;
	end = 0;
	
	userName = CFSTR("[Empty]");
	userID = CFSTR("[Empty]");
	userAge = CFSTR("[Empty]");
	userRace = CFSTR("[Empty]");
	userSex = CFSTR("[Empty]");
	userMarital = CFSTR("[Empty]");
	userIncome = CFSTR("[Empty]");
	userOrientation = CFSTR("[Empty]");
	userKids = CFSTR("[Empty]");
	
}

void Trial::IncrementCounter(){
	
	counter++;
}

void Trial::SetGroupID(int inID){
	
	groupID = inID;	
}

void Trial::SetEnd(int inEnd){
	
	end = inEnd;
	
	for(int i=0; i<end; i++)
		ratings.push_back(vector <int>());	
}

bool Trial::isOver(){
	
	if (counter>=end)
		return true;
	
	return false;
}

void Trial::SetUserData(CFStringRef inName, CFStringRef inID, CFStringRef inAge, CFStringRef inRace, CFStringRef inSex){
	
	userName = inName;
	userID = inID;
	userAge = inAge;
	userRace = inRace;
	userSex = inSex;
}

void Trial::SetUserSurveyData(CFStringRef setMarital, CFStringRef setIncome, CFStringRef setOrientation, CFStringRef setKids){
	
	userMarital = setMarital;
	userIncome = setIncome;
	userOrientation = setOrientation;
	userKids = setKids;
}

void Trial::PrintTrial(){
	
	CFShow(userName);
	CFShow(userRace);
	CFShow(userAge);
	CFShow(userID);
	
	printf("Group Vector Index: %d\n", groupID);
	printf("Current Counter: %d\n", counter);
	printf("End Counter: %d\n", end);
	printf ("Trial Number: %d\n", trialID);
	
	printf("****Ratings****\n");
	
	for(int i=0; i<ratings.size(); i++){
		printf("\no ");
		for(int j=0; j<ratings[i].size(); j++)
			printf("%d ", ratings[i][j]);
	}
	
	printf("\n********\n");
}

void Trial::SetACompRating(int comp){
	
	ratings[currentModel].push_back(comp);
}

void Trial::SetATrustRating(int trust){
	
	ratings[currentModel].push_back(trust);
}

void Trial::SetALikeRating(int like){
	
	ratings[currentModel].push_back(like);
}

void Trial::SetAAttrRating(int attr){
	
	ratings[currentModel].push_back(attr);
}

void Trial::SaveBatteryA(){

	fstream Output("Ratings_Trial_A.xls", ios::out | fstream::app);
	
	Output << "\n";
	
	// Header
	Output << "Rater ID" << "\t";
	Output << "Rater Race" << "\t";
	Output << "Rater Age" << "\t";
	Output << "Rater Sex" << "\t";
	Output << "Rater Marital" << "\t";
	Output << "Rater Income" << "\t";
	Output << "Rater Orientation" << "\t";
	Output << "Rater has Child?" << "\t";
	Output << "Model Name" << "\t";
	Output << "Model Makeup" << "\t";
	Output << "Model Race" << "\t";
	Output << "Model Age" << "\t";
	Output << "Model Segment Type" << "\t";
	Output << "Model Marital Status" << "\t";
	Output << "Model Income" << "\t";
	Output << "Model Orientation" << "\t";
	Output << "Model Hair" << "\t";
	Output << "Model Smile" << "\t";
	Output << "Model Mirror" << "\t";
	Output << "Competence Score" << "\t";
	Output << "Trust Score" << "\t";
	Output << "Likability Score" << "\t";
	Output << "Attractiveness Score" << "\t";
	Output << "\n";
	
	// for every model...
	for(int j=0; j<ratings.size(); j++){
		
		const int kBufferSize = 256;
		
		// Output Rater Information
		char rater_id[kBufferSize];
		char rater_race[kBufferSize];
		char rater_age[kBufferSize];
		char rater_sex[kBufferSize];
		char rater_marital[kBufferSize];
		char rater_income[kBufferSize];
		char rater_orientation[kBufferSize];
		char rater_kids[kBufferSize];
		
		CFStringGetCString(userID, rater_id, kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userRace,rater_race,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userAge,rater_age,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userSex,rater_sex,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userMarital,rater_marital,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userIncome,rater_income,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userOrientation,rater_orientation,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userKids,rater_kids,kBufferSize, kCFStringEncodingMacRoman);
		
		Output << rater_id << "\t";
		Output << rater_race << "\t";
		Output << rater_age << "\t";
		Output << rater_sex << "\t";
		Output << rater_marital << "\t";
		Output << rater_income << "\t";
		Output << rater_orientation << "\t";
		Output << rater_kids << "\t";

		// Output Model Information
		// copy from a CFString into a local c string
		char model_name[kBufferSize];
		char model_makeup[kBufferSize];
		char model_race[kBufferSize];
		char model_age[kBufferSize];
		char model_segment[kBufferSize];
		char model_marital[kBufferSize];
		char model_income[kBufferSize];
		char model_orientation[kBufferSize];
		char model_hair[kBufferSize];
		char model_smile[kBufferSize];
		char model_mirror[kBufferSize];
			
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].modelName,model_name,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].makeupType,model_makeup,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].race,model_race,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].age,model_age,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].segment,model_segment,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].marital,model_marital,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].income,model_income,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].orientation,model_orientation,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].hair,model_hair,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].smile,model_smile,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].mirror,model_mirror,kBufferSize, kCFStringEncodingMacRoman);
		
		Output << model_name << "\t";
		Output << model_makeup << "\t";
		Output << model_race << "\t";
		Output << model_age << "\t";
		Output << model_segment << "\t";
		Output << model_marital << "\t";
		Output << model_income << "\t";
		Output << model_orientation << "\t";
		Output << model_hair << "\t";
		Output << model_smile << "\t";
		Output << model_mirror << "\t";
		
		// Output Ratings
		for(int i=0; i<ratings[j].size(); i++)
			Output << ratings[j][i] << "\t";
		
		Output << "\n";
	}
	
	Output.close();
}

void Trial::SaveBatteryB(){
	
	fstream Output("Ratings_Trial_B.xls", ios::out | fstream::app);
	
	Output << "\n";
	
	// Header
	Output << "Rater ID" << "\t";
	Output << "Rater Race" << "\t";
	Output << "Rater Age" << "\t";
	Output << "Rater Sex" << "\t";
	Output << "Rater Marital" << "\t";
	Output << "Rater Income" << "\t";
	Output << "Rater Orientation" << "\t";
	Output << "Rater has Child?" << "\t";
	Output << "Model Name" << "\t";
	Output << "Model Makeup" << "\t";
	Output << "Model Race" << "\t";
	Output << "Model Age" << "\t";
	Output << "Model Segment Type" << "\t";
	Output << "Model Marital Status" << "\t";
	Output << "Model Income" << "\t";
	Output << "Model Orientation" << "\t";
	Output << "Model Hair" << "\t";
	Output << "Model Smile" << "\t";
	Output << "Model Mirror" << "\t";
	Output << "Competence Score" << "\t";
	Output << "Trust Score" << "\t";
	Output << "Likability Score" << "\t";
	Output << "Attractiveness Score" << "\t";
	Output << "\n";
	
	// for every model...
	for(int j=0; j<ratings.size(); j++){
		
		const int kBufferSize = 256;
		
		// Output Rater Information
		char rater_id[kBufferSize];
		char rater_race[kBufferSize];
		char rater_age[kBufferSize];
		char rater_sex[kBufferSize];
		char rater_marital[kBufferSize];
		char rater_income[kBufferSize];
		char rater_orientation[kBufferSize];
		char rater_kids[kBufferSize];
		
		CFStringGetCString(userID, rater_id, kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userRace,rater_race,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userAge,rater_age,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userSex,rater_sex,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userMarital,rater_marital,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userIncome,rater_income,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userOrientation,rater_orientation,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userKids,rater_kids,kBufferSize, kCFStringEncodingMacRoman);
		
		Output << rater_id << "\t";
		Output << rater_race << "\t";
		Output << rater_age << "\t";
		Output << rater_sex << "\t";
		Output << rater_marital << "\t";
		Output << rater_income << "\t";
		Output << rater_orientation << "\t";
		Output << rater_kids << "\t";
		
		// Output Model Information
		// copy from a CFString into a local c string
		char model_name[kBufferSize];
		char model_makeup[kBufferSize];
		char model_race[kBufferSize];
		char model_age[kBufferSize];
		char model_segment[kBufferSize];
		char model_marital[kBufferSize];
		char model_income[kBufferSize];
		char model_orientation[kBufferSize];
		char model_hair[kBufferSize];
		char model_smile[kBufferSize];
		char model_mirror[kBufferSize];
		
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].modelName,model_name,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].makeupType,model_makeup,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].race,model_race,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].age,model_age,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].segment,model_segment,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].marital,model_marital,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].income,model_income,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].orientation,model_orientation,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].hair,model_hair,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].smile,model_smile,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].mirror,model_mirror,kBufferSize, kCFStringEncodingMacRoman);
		
		Output << model_name << "\t";
		Output << model_makeup << "\t";
		Output << model_race << "\t";
		Output << model_age << "\t";
		Output << model_segment << "\t";
		Output << model_marital << "\t";
		Output << model_income << "\t";
		Output << model_orientation << "\t";
		Output << model_hair << "\t";
		Output << model_smile << "\t";
		Output << model_mirror << "\t";
		
		
		// Output Ratings
		for(int i=0; i<ratings[j].size(); i++)
			Output << ratings[j][i] << "\t";
		
		Output << "\n";
	}
	
	Output.close();
}

void Trial::SaveBatteryC(){
	
	fstream Output("Ratings_Trial_C.xls", ios::out | fstream::app);
	
	Output << "\n";
	
	// Header
	Output << "Rater ID" << "\t";
	Output << "Rater Race" << "\t";
	Output << "Rater Age" << "\t";
	Output << "Rater Sex" << "\t";
	Output << "Rater Marital" << "\t";
	Output << "Rater Income" << "\t";
	Output << "Rater Orientation" << "\t";
	Output << "Rater has Child?" << "\t";
	Output << "Model Name" << "\t";
	Output << "Model Makeup" << "\t";
	Output << "Model Race" << "\t";
	Output << "Model Age" << "\t";
	Output << "Model Segment Type" << "\t";
	Output << "Model Marital Status" << "\t";
	Output << "Model Income" << "\t";
	Output << "Model Orientation" << "\t";
	Output << "Model Hair" << "\t";
	Output << "Model Smile" << "\t";
	Output << "Model Mirror" << "\t";
	Output << "Health Score" << "\t";
	Output << "Daring Score" << "\t";
	Output << "Attentive Score" << "\t";
	Output << "Sociable Score" << "\t";
	Output << "Caring Score" << "\t";
	Output << "Stable Score" << "\t";
	Output << "Would Hire Score" << "\t";
	Output << "Guessed Age" << "\t";
	Output << "\n";
	
	// for every model...
	for(int j=0; j<ratings.size(); j++){
		
		const int kBufferSize = 256;
		
		// Output Rater Information
		char rater_id[kBufferSize];
		char rater_race[kBufferSize];
		char rater_age[kBufferSize];
		char rater_sex[kBufferSize];
		char rater_marital[kBufferSize];
		char rater_income[kBufferSize];
		char rater_orientation[kBufferSize];
		char rater_kids[kBufferSize];
		
		CFStringGetCString(userID, rater_id, kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userRace,rater_race,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userAge,rater_age,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userSex,rater_sex,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userMarital,rater_marital,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userIncome,rater_income,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userOrientation,rater_orientation,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(userKids,rater_kids,kBufferSize, kCFStringEncodingMacRoman);
		
		Output << rater_id << "\t";
		Output << rater_race << "\t";
		Output << rater_age << "\t";
		Output << rater_sex << "\t";
		Output << rater_marital << "\t";
		Output << rater_income << "\t";
		Output << rater_orientation << "\t";
		Output << rater_kids << "\t";
		
		// Output Model Information
		// copy from a CFString into a local c string
		char model_name[kBufferSize];
		char model_makeup[kBufferSize];
		char model_race[kBufferSize];
		char model_age[kBufferSize];
		char model_segment[kBufferSize];
		char model_marital[kBufferSize];
		char model_income[kBufferSize];
		char model_orientation[kBufferSize];
		char model_hair[kBufferSize];
		char model_smile[kBufferSize];
		char model_mirror[kBufferSize];
		
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].modelName,model_name,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].makeupType,model_makeup,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].race,model_race,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].age,model_age,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].segment,model_segment,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].marital,model_marital,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].income,model_income,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].orientation,model_orientation,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].hair,model_hair,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].smile,model_smile,kBufferSize, kCFStringEncodingMacRoman);
		CFStringGetCString(masterGroupList.groupList[groupID].modelList[j].mirror,model_mirror,kBufferSize, kCFStringEncodingMacRoman);
		
		Output << model_name << "\t";
		Output << model_makeup << "\t";
		Output << model_race << "\t";
		Output << model_age << "\t";
		Output << model_segment << "\t";
		Output << model_marital << "\t";
		Output << model_income << "\t";
		Output << model_orientation << "\t";
		Output << model_hair << "\t";
		Output << model_smile << "\t";
		Output << model_mirror << "\t";
		
		// Output Ratings
		for(int i=0; i<ratings[j].size(); i++)
			Output << ratings[j][i] << "\t";
		
		Output << "\n";
	}
	
	Output.close();
}

void Trial::ResetTrial(){
	
	if(groupID != -1){
		for(int j=0; j<masterGroupList.groupList[groupID].modelList.size(); j++)
			masterGroupList.groupList[groupID].modelList[j].used = false;
	}
	
	trialID = 0;
	groupID = -1;
	counter = 0;
	trialMode = 0;
	currentModel = 0;
	end = 0;
	
	userName = CFSTR("[Empty]");
	userID = CFSTR("[Empty]");
	userAge = CFSTR("[Empty]");
	userRace = CFSTR("[Empty]");
		
	for(int i=0; i<ratings.size(); i++)
		ratings[i].clear();
		
	ratings.clear();
}

// Sets currentModelID to new model
// Returns true if new model was found, false if no new models
bool Trial::nextModel(){
	
	int timeout = 0;
	int size = masterGroupList.groupList[groupID].modelList.size();
	float nextMod = rand() % size;
	
	while(isUsed(nextMod)){
		
		nextMod = rand() % size;
		timeout++;
		
		if(timeout>20000){
			return false;
		}
	}
	
	// Set currentModel to nextMod
	currentModel = nextMod;
	masterGroupList.groupList[groupID].modelList[currentModel].used = true;
	
	printf("Current Model: %d\n", currentModel);
	return true;	
}
		
bool Trial::isUsed(int nextModel){
	
	if(masterGroupList.groupList[groupID].modelList[nextModel].used == false)
		return false;
	
	return true;
}


void Trial::SetBatteryCData(int health, int dare, int attentive, int sociable, int caring, int stable, int hire, CFStringRef ageBox){
	
	// set the test int at 50
	int inAge = 50;
	
	// convert the test int to test string
	CFStringRef testString = CFStringCreateWithFormat(kCFAllocatorDefault, NULL, CFSTR("%u"), inAge);
	
	
	// while (test string is not equal to ageBox)
	while(CFStringCompare(ageBox, testString, 0)!=0){
		
		// get result of test string, agebox comparison
		int compResult = CFStringCompare(ageBox, testString, 0);
	
		// if agebox is less, decrement test string
		if(compResult < 0)
			inAge--;
		else if (compResult > 0)
			inAge++;
	
		// convert inAge to testString
		testString = CFStringCreateWithFormat(kCFAllocatorDefault, NULL, CFSTR("%u"), inAge);
	}

	printf("AGE: %d\n", inAge);
	
	ratings[currentModel].push_back(health);
	ratings[currentModel].push_back(dare);
	ratings[currentModel].push_back(attentive);
	ratings[currentModel].push_back(sociable);
	ratings[currentModel].push_back(caring);
	ratings[currentModel].push_back(stable);
	ratings[currentModel].push_back(hire);
	ratings[currentModel].push_back(inAge);
}









