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

WindowRef					window;			// main window
WindowRef					window2;		// model list window
WindowRef					window3;		// add model window
WindowRef					window4;		// error adding model window
WindowRef					window5;		// view model window

WindowRef					gGroupListWindow;	// group list window
WindowRef					gAddGroupWindow;	// add group window
WindowRef					gEditGroupWindow;	// edit group window

WindowRef					gNewTrialWindow; 	// new trial window
WindowRef					gBatteryAWindow; 	// battery a window
WindowRef					gBatteryAWindow1; 	// battery a rating1
WindowRef					gBatteryAWindow2; 	// battery a rating2
WindowRef					gBatteryAWindow3; 	// battery a rating3
WindowRef					gBatteryAWindow4; 	// battery a rating4

WindowRef					gTargetAlertWindow;
WindowRef					gBatteryBPictureWindow;	// battery b display window
WindowRef					gBatteryBRatingWindow;

WindowRef					gSurveyWindow;
WindowRef					gBatteryCWindow;

#define NextModel 'NXMD'
#define NextModelB 'NXMB'

#define NextBatteryC 'NXBC'
#define BCHealthySignature 'BCHY'
#define BCHealthyID 901
#define BCDaringSignature 'BCDA'
#define BCDaringID 902
#define BCAttentiveSignature 'BCCO'
#define BCAttentiveID 903
#define BCSociableSignature 'BCSO'
#define BCSociableID 904
#define BCCaringSignature 'BCCA'
#define BCCaringID 905
#define BCStableSignature 'BCSA'
#define BCStableID 906
#define BCHireSignature 'BCFH'
#define BCHireID 907
#define BCAgeSignature 'BCAG'
#define BCAgeID 908

#define SurveyMaritalSignature 'usms'
#define SurveyMaritalID 450
#define SurveyIncomeSignature 'usin'
#define SurveyIncomeID 451
#define SurveyOrientationSignature 'usor'
#define SurveyOrientationID 452
#define SurveyChildrenSignature 'usch'
#define SurveyChildrenID 453

#define CompetenceSignatureB 'CMPB'
#define CompetenceIDB 822
#define LikeSignatureB 'LIKB'
#define LikeIDB 823
#define AttractiveSignatureB 'ATRB'
#define AttractiveIDB 824
#define TrustSignatureB 'TRSB'
#define TrustIDB 825

#define CompetenceSignature 'CPSL'
#define CompetenceID 815
#define LikeSignature 'LKSL'
#define LikeID 816
#define AttractiveSignature 'ATSL'
#define AttractiveID 817
#define TrustSignature 'TRSL'
#define TrustID 818

#define BeginTrial 'BGTR'
#define CancelTrial 'CNTR'

#define trialBatterySignature 'BTSL'
#define trialBatteryID 802
#define userNameSignature 'USNM'
#define userNameID 803
#define userRaceSignature 'USRC'
#define userRaceID 804
#define userAgeSignature 'USAG'
#define userAgeID 805
#define userIDSignature 'USID'
#define userIDID 806
#define userSexSignature 'USSX'
#define userSexID 807

#define ConfirmAddGroup 'AGOK'
#define CancelAddGroup 'AGCL'
#define AddGroupTextSignature 'gnbx'
#define AddGroupTextID 712

#define AddGrouptoList 'addg'
#define EditGroupinList 'edtg'
#define DeleteGroupfromList 'delg'
#define CloseGroupList 'glcl'

#define AddToGroupButton 'amtg'
#define DeleteFromGroupButton 'dmfg'
#define DoneWithEditGroup 'dweg'

#define StartTrial1 'strt'
#define EditModelList 'modl'
#define AddModelToList 'addm'
#define DeleteModelFromList 'delm'
#define FinishedWithWindow 'mlcl'
#define ConfirmAddModel 'admo'
#define CancelAddModel 'cncl'
#define ClearAlert 'cnc1'
#define GetPictureName 'oppc'
#define ViewModel 'vwmd'
#define CloseViewModel 'clvw'
#define EditGroupList 'trls'
#define CloseSurvey 'dnwt'

#define nameFieldSignature 'mnme'
#define nameFieldID 509
#define raceFieldSignature 'race'
#define raceFieldID 505
#define ageFieldSignature 'ageg'
#define ageFieldID 506
#define makeupFieldSignature 'mktp'
#define makeupFieldID 507
#define pictureFieldSignature 'mpnm'
#define pictureFieldID 508
#define segmentFieldSignature 'sgcl'
#define segmentFieldID 512
#define maritalFieldSignature 'msts'
#define maritalFieldID 513
#define incomeFieldSignature 'inlv'
#define incomeFieldID 514
#define orientationFieldSignature 'sott'
#define orientationFieldID 515
#define hairFieldSignature 'hrty'
#define hairFieldID 516
#define smileFieldSignature 'smyn'
#define smileFieldID 517
#define mirrorFieldSignature 'mrck'
#define mirrorFieldID 518

#define viewnameFieldSignature 'vw01'
#define viewnameFieldID 600
#define viewraceFieldSignature 'vw02'
#define viewraceFieldID 602
#define viewageFieldSignature 'vw03'
#define viewageFieldID 603
#define viewmakeupFieldSignature 'vw04'
#define viewmakeupFieldID 604
#define viewpictureFieldSignature 'vwpc'
#define viewpictureFieldID 601
#define viewsegmentFieldSignature 'vw05'
#define viewsegmentFieldID 605
#define viewmaritalFieldSignature 'vw06'
#define viewmaritalFieldID 606
#define viewincomeFieldSignature 'vw07'
#define viewincomeFieldID 607
#define vieworientationFieldSignature 'vw08'
#define vieworientationFieldID 608
#define viewhairFieldSignature 'vw09'
#define viewhairFieldID 609
#define viewsmileFieldSignature 'vw10'
#define viewsmileFieldID 610
#define viewmirrorFieldSignature 'vw11'
#define viewmirrorFieldID 611

#define nameColumn 'nfld'
#define raceColumn 'rfld'
#define ageColumn 'afld'
#define makeupColumn 'mfld'

