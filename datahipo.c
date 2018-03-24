/*
 ============================================================================
 Name        : datahipo.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int x = 200; //I didn't know what size to make the forms so I made it this arbitary length.

typedef struct Patient
{

	//Increment things with a comma to delimit elements
	//Use a semicolon to do a new line.
	int id;
	char ptnInformation[30];
	//fname,lname,dob,notes;
	char crntPrescriptions[200];
	//medName,dosage,dateFilled;
	char medRecord[200];
	//type,desc,medName,dosage,dateIssued,Note;
	char vtlSigns[200];
	//height,weight,age,bmi,date;
	char smkStatus[1];
	//status(y/n);
	char mdcAllergy[200];
	//medName;
	char problemList[200];
	//medName,Procedure,Illness,Vaccination,Date;

}Paitent;

//Please for the love of god if you know a better way to do this please do
Paitent readPatient(int id)
{
	//Variables
	FILE *infile;
	Paitent temp;
	int tempID;
	int paitentLocation;
	int loopcntr;

	//We open the file and check for errors
	infile = fopen("DataHipo.dat","r");
	if(infile == NULL)
	{
		fprintf(stderr, "\nDatabase Error");
		exit(1);
	}

	//We look for the location of the patient
	while(infile || tempID == id )
	{
		fsetpos(infile,sizeof(Paitent)*loopcntr);
		fscanf(infile,"%d",tempID);
	}

	//If it exists we return it.
	if(tempID == id)
		fread(&temp,sizeof(struct Patient),1,infile);
	pclose(infile);
	return temp;
}

void writePatient(int id, struct Patient johnSmith)
{
	//Variables
	FILE *outfile;
	int tempID;
	int loopcntr;

	//We open the file and check for errors
	outfile = fopen("DataHipo.dat","wr");
	if(outfile == NULL)
	{
		fprintf(stderr, "\nDatabase Error");
		exit(1);
	}

	//We look for the location of the patient
	while(outfile || tempID == id )
	{
		fsetpos(outfile,sizeof(Paitent)*loopcntr);
		fscanf(outfile,"%d",&tempID);
	}

	//If it exists we write.
	if(tempID == id)
		fwrite(&johnSmith,sizeof(struct Patient),1,outfile);//I'm hoping this writes over the old patient.
	else//If patient doesn't exist that means they are new and write eof
	{
		fseek(outfile,0,SEEK_END);
		fwrite(&johnSmith,sizeof(struct Patient),1,outfile);
	}
	pclose(outfile);//House Keeping

	//Function Ends
}

//Needs to have an addition that writes to medFiles
void epatientMenu(struct Patient johnSmith)
{
	//Variables
	char tmp[20];
	char output[120];
	char* fname = strtok(johnSmith.ptnInformation,",");
	char* lname = strtok(johnSmith.ptnInformation,",");
	char* dob = strtok(johnSmith.ptnInformation,",");

	//We print the menu Header
	printf("Data Hipo - Doctor Portal\n\nE-Prescription\n\n");
	printf("Patient First Name: %s",fname);
	printf("Patient Last Name: %s", lname);
	printf("Date of Birth (%s)\n",dob);

	//We read prescription information from the users possibly needs more error checking
	printf("Drug:");
	scanf("%s",&output[0]);
	printf("Dosage:");
	scanf("%s",&tmp[0]);
	strcat(output,tmp);
	printf("Strength:");
	scanf("%s",&tmp[0]);
	strcat(output,tmp);
	printf("Prescription Length:");
	scanf("%s",&tmp[0]);
	strcat(output,tmp);
	printf("Prescription Quantity:");
	scanf("%s",&tmp[0]);
	strcat(output,tmp);
	printf("Refills(Y/N):");
	scanf("%s",&tmp[0]);
	strcat(output,tmp);
	printf("Directions:");
	scanf("%s",&tmp[0]);
	strcat(output,tmp);
	printf("Notes:");
	scanf("%s",&tmp[0]);
	strcat(output,tmp);
	printf("Pharmacy:");
	scanf("%s",&tmp[0]);
	strcat(output,tmp);
	printf("Doctor Authorizing Prescription:");
	scanf("%s",&tmp[0]);
	strcat(output,tmp);

	//We output the data to a file as a deliverable
	FILE *outfile = fopen("E-Prescription","w");//"E-Prescription"+fname+"_"+lname
	if(outfile == NULL)
	{
		fprintf(stderr, "\nWrite to file Error");
		exit(1);
	}
	fprintf(outfile,"E-Prescription order for %s,%s\n%s",fname,lname,output);
	close(outfile);//House keeping
	//Function Ends
}

void activeMedList(struct Patient johnSmith)
{
	//Variables
	char* fname = strtok(johnSmith.ptnInformation,",");
	char* lname = strtok(johnSmith.ptnInformation,",");
	char* dob = strtok(johnSmith.ptnInformation,",");
	char userIO;
	char output[x];
	char* name;
	char tmp[x];//We copy the string for integrity.
	strcpy(tmp,johnSmith.medRecord);
	char* tokenA = strtok(tmp,";");

	printf("Data Hipo - Doctor Portal\n\nActive Medication List\n\n");
	printf("Patient First Name: %s",fname);
	printf("Patient Last Name: %s", lname);
	printf("Date of Birth (%s)\n",dob);
	printf("\nACTIVE MEDICATIONS:\n-----------------");

	//While there is still data left to read we cycle though the outer token.
	while(tokenA)
	{
		char* tokenB = strtok(tokenA,",");//Reads type onto token
		tokenB = strtok(NULL,","); //Reads desc onto token
		name = strtok(NULL,",");//Reads medName onto token
		tokenB = strtok(NULL,",");//Reads dosage onto token
		tokenB = strtok(NULL,",");//Reads dateIssued onto token
		tokenB = strtok(NULL,",");//Reads note onto token
		if(strcmp(tokenB,"Active") != 0)//If the note for the medication is correct then we append it to our output
		{
			strcat(output,name);
			strcat(output,"\n");
		}

	}

	//We print our output
	printf("Data Hipo - Doctor/Nurse\n\nActive Medication List");
	printf("Patient First Name:%s\nPatient Last Name:%s\nPatient Date of Birth:%s\n",fname,lname,dob);
	printf("\nACTIVE MEDICATIONS\n-------------------\n%s",output);

	//Exit loop
	while(strcmp(userIO,"r") != 0)
	{
		printf("Enter 'r' to return to the main menu:");
		scanf("%1s",&userIO);
	}
	//function ends
}

//This person who made this form was trash and its implementation is crap because of it.
void cpoeMenu(struct Patient johnSmith)
{
	//Variables
	char* fname = strtok(johnSmith.ptnInformation,",");
	char* lname = strtok(johnSmith.ptnInformation,",");
	char* dob = strtok(johnSmith.ptnInformation,",");
	char userIO;
	char tmp[15];
	char entry[45];
	char cpoe[x];

	//We print the header
	printf("Data Hipo - Doctor Portal\n\nComputerized Provider Order Entry (CPOE)\n\n");
	printf("Patient First Name: %s",fname);
	printf("Patient Last Name: %s", lname);
	printf("Date of Birth (%s)\n\n",dob);


	while(strcmp(userIO,"r") != 0)
	{
		//We print the menu
		printf("MENU:	(1)Add Past Medication (2) Add Current Medication (3) Add Notes\n\n");
		printf("Enter an option from the menu above:");
		//We read the users option and proceed accordingly
		scanf("%1s",userIO);
		printf("\nEnter Activity:");
		if(strcmp(userIO,"1") == 0)
		{
			scanf("%15s",&tmp[0]);
			strcat(entry, tmp);//We format to display correctly
			strcat(entry,"                               ");

		}
		else if(strcmp(userIO,"2") == 0)
		{
			scanf("%15s",&tmp[0]);
			strcat(entry,"               ");//We format to display correctly
			strcat(entry,tmp);
			strcat(entry,"                ");
		}
		else if(strcmp(userIO,"3") == 0)
		{
			scanf("%15s",&tmp[0]);
			strcat(entry, "                               ");//We format to display correctly
			strcat(entry,tmp);
		}

		printf("Activity Start Date(DDMMYYYY):");
		scanf("%8s",&tmp[0]);
		strcat(entry,tmp);
		strcat(entry,",");
		printf("Activity End Date(DDMMYYYY):");
		scanf("%8s",&tmp[0]);
		strcat(entry,tmp);
		strcat(entry,cpoe);
		strcat(entry,"\n");
		printf(cpoe);


		printf("Enter 'r' to return to the main menu:");
		scanf("%1s",&userIO);
	}

	//We output the data to a file as a deliverable
		FILE *outfile = fopen("CPOE","w");//What i want to do for file name but C is a bitch "CPOE"+fname+"_"+lname
		if(outfile == NULL)
		{
			fprintf(stderr, "\nWrite to file Error");
			exit(1);
		}
		fprintf(outfile,"CPOE for %s,%s\n%s",fname,lname,cpoe);
		close(outfile);//House keeping
		//Function Ends
}

void  maintainPrbList(struct Patient johnSmith)
{
	//Variables
		char* fname = strtok(johnSmith.ptnInformation,",");
		char* lname = strtok(johnSmith.ptnInformation,",");
		char* dob = strtok(johnSmith.ptnInformation,",");
		char userIO;
		char tmp[15];
		char entry[45];
		char prblmList[200] = "\n";

		//We print the header
		printf("Data Hipo - Doctor Portal\n\nMaintain Problems List\n\n");
		printf("Patient First Name: %s",fname);
		printf("Patient Last Name: %s", lname);
		printf("Date of Birth (%s)\n\n",dob);


		while(strcmp(userIO,"r") != 0)
		{
			//We print the menu
			printf("MENU:	(1)Add Medication (2) Add Procedure (3) Add Illness (4) Add Vaccination \n\n");
			printf("Enter an option from the menu above:");
			//We read the users option and proceed accordingly
			scanf("%1s",&userIO);
			printf("\nEnter Activity:");
			if(strcmp(userIO,"1") == 0)
			{
				scanf("%15s",&tmp[0]);
				strcat(entry,tmp);//We format to display correctly
				strcat(entry,"                                                ");

			}
			else if(strcmp(userIO,"2") == 0)
			{
				scanf("%15s",&tmp[0]);
				strcat(entry,"               ");//We format to display correctly
				strcat(entry,tmp);
				strcat(entry,"                              ");
			}
			else if(strcmp(userIO,"3") == 0)
			{
				scanf("%15s",&tmp[0]);
				strcat(entry,"                               ");//We format to display correctly
				strcat(entry,tmp);
				strcat(entry,"               ");
			}
			else if(strcmp(userIO,"4") ==0)
			{
				scanf("%15s",&tmp[0]);
				strcat(entry,"                                              ");//We format to display correctly
				strcat(entry,tmp);
			}

			printf("Activity Start Date(DDMMYYYY):");
			scanf("%8s",&tmp[0]);
			strcat(entry,tmp);
			strcat(entry,"\n");
			strcat(prblmList,entry);
			printf(prblmList);


			printf("Enter 'r' to return to the main menu:");
			scanf("%1s",&userIO);
		}
}

void doctorMenu(int ptnID)
{
    int userIO = 0;
    int flag = 0;
    struct Patient patient = readPatient(ptnID);

    //Menu Options for the a user with doctor privileges.
    printf("Data Hipo - Patient Doctor Portal\n\n");
    printf("Menu: (1) Maintain Problem List    (2) E-Prescription     (3) Active Medication List\n");
    printf("      (4) Medication Allergy List  (5) Record Vital Signs (6) Record Smoking Status\n");
    printf("      (7) Computerized Provider Order Entry (CPOE)		  (8) Patient Information\n");
    printf("      (0) Exit\n");

    //A quick while loop to verify user input
    while(flag == 0)
    {
        printf("Enter an option from the menu above:");
        scanf("%1d",&userIO);//I limit the user to only entering 1 digit, I also store the input as an int to let me use it in a switch statement.
        if(userIO < 10 && userIO >= 0)//We want our input between 0-9
            flag = 1;
    }

    switch(userIO)//Because of simplicity of the cases I felt that a switch statement suited the task
    {
        //Every case just equals a function call to allow easy modularization with other menus
        case(1):
            maintainPrbList(patient);//Need to fix an assignment problem here.
            break;
        case(2):
            epatientMenu(patient);
            break;
        case(3):
            activeMedList(patient);
            break;
        case(4):
            //Medication Allergy List
            break;
        case(5):
            //Record Vital Signs
            break;
        case(6):
            //Record Smoking Status
            break;
        case(7):
            cpoeMenu(patient);
            break;
        case(8):
            //Patient Information
            break;
        case(0):
        		writePatient(ptnID,patient);
            printf("Exiting.....");
    }
}


int main(void) {


	//Variables
	char uname[8];
	char pword[8];
	int patientID;
	int flag = 0;


	//Intro Message
	printf("Welcome to Data Hipo - Electronic Medical Record Software (EMS)\n\n\n");
	do
	{	//Loop for user login
		printf("Please enter your login information.\nUsername:");
		scanf("%8s",uname);
		printf("Password:");
		scanf("%8s",pword);
		printf("Patient#");
		scanf("%5d",&patientID);//This will be passed to menu function to load patient info.

		//We use nested if statements to check for users that area might be subject to change
		if (strcmp(uname, "admin") == 0)
		{
			if (strcmp(pword,"admin!") == 0)
			{

				// run admin menu function
				//please refer to the SDD for how the functions should operate and what the text should look like
				/*Create account
				 * Get Number of Accounts
				 * Delete Accounts					 * Write Logs
				 * View Logs
				 */
				flag = 1;
			}
		}
		else if (strcmp(uname,"doctor") == 0)
		{
			if(strcmp(pword, "doctor!") == 0)
			{
				doctorMenu(0);
				flag = 1;
			}
		}
		else if (strcmp(uname,"nurse") == 0)
		{
			if(strcmp(pword, "nurse!") == 0)
			{

				//run nurse function
				//please refer to the SDD for how the functions should operate and what the text should look like
				/*
				 * Active Mediation List
				 * Patient Information
				 * Record Vital Signs
				 * Record Smoking Status
				 */
				flag = 1;
			}
		}
		else if (strcmp(uname,"patient") == 0)
		{
			if(strcmp(pword, "patient!") == 0)
			{
				//run patient function
				//please refer to the SDD for how the functions should operate and what the text should look like
				/*
				 *Current Prescriptions
				 * Medical Records
				 * Appointments
				 */
				flag = 1;
			}
		}
		else
			printf("Invalid username or password.\n");

	}while(flag != 1);

	//Exit Message
	printf("Thank you for using Data Hipo\nHave a nice day!");
	return 0;

	//Function Ends
}
