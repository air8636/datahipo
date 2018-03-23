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

}Paitent;

//Please for the love of god if you know a better way to do this please do
Paitent readPatient(int id)
{

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
	while(!eof(infile) || tempID == id )
	{
		fsetpos(infile,sizeof(Paitent)*loopcntr);
		fscanf(infile,"%d",tempID);
	}

	//If it exists we return it.
	if(tempID == id)
		fread(&temp,sizeof(struct Patient),1,infile);
	close(infile);
	return temp;
}

void writePatient(int id,struct Paitent johnSmith)
{

	FILE *outfile;
	Paitent temp;
	int tempID;
	int paitentLocation;
	int loopcntr;

	//We open the file and check for errors
	outfile = fopen("DataHipo.dat","wr");
	if(outfile == NULL)
	{
		fprintf(stderr, "\nDatabase Error");
		exit(1);
	}

	//We look for the location of the patient
	while(!eof(outfile) || tempID == id )
	{
		fsetpos(outfile,sizeof(Paitent)*loopcntr);
		fscanf(outfile,"%d",tempID);
	}

	//If it exists we write.
	if(tempID == id)
		fwrite(&johnSmith,sizeof(struct Patient),1,outfile);//I'm hoping this writes over the old patient.
	else
	{
		fseek(outfile,0,SEEK_END);
		fwrite(&johnSmith,sizeof(struct Patient),1,outfile);//If patient doesn't exist that means they are new and write eof.
	}
	close(outfile);
}

void epatientMenu(struct Patient johnSmith)
{
	char tmp[20];
	char output[120];
	char* fname = strtok(johnSmith->ptnInformation,",");
	char* lname = strtok(johnSmith->ptnInformation,",");
	char* dob = strtok(johnSmith->ptnInformation,",");
	printf("Data Hipo - Doctor Portal\n\nE-Prescription\n\n");
	printf("Patient First Name: %s",fname);
	printf("Patient Last Name: %s", lname);
	printf("Date of Birth (%d)\n",dob);

	printf("Drug:");
	scanf("%s",&output);
	printf("Dosage:");
	scanf("%s",&tmp);
	strcat(output,tmp);
	printf("Strength:");
	scanf("%s",&tmp);
	strcat(output,tmp);
	printf("Prescription Length:");
	scanf("%s",&tmp);
	strcat(output,tmp);
	printf("Prescription Quantity:");
	scanf("%s",&tmp);
	strcat(output,tmp);
	printf("Refils(Y/N):");
	scanf("%s",&tmp);
	strcat(output,tmp);
	printf("Directions:");
	scanf("%s",&tmp);
	strcat(output,tmp);
	printf("Notes:");
	scanf("%s",&tmp);
	strcat(output,tmp);
	printf("Pharmacy:");
	scanf("%s",&tmp);
	strcat(output,tmp);
	printf("Doctor Authorizing Prescription:");
	scanf("%s",&tmp);
	strcat(output,tmp);


	FILE *outfile = fopen("E-Prescription","w");
	if(outfile == NULL)
	{
		fprintf(stderr, "\nWrite to file Error");
		exit(1);
	}

	fprintf(outfile,"E-Prescription order for %s,%s\n%s",fname,lname,output);
	close(outfile);
}

void activeMedList(struct Patient johnSmith)
{
	char* fname = strtok(johnSmith->ptnInformation,",");
	char* lname = strtok(johnSmith->ptnInformation,",");
	char* dob = strtok(johnSmith->ptnInformation,",");
	char tmp[200];//We copy the string for integrity.
	char output[200];
	char name[15];
	strcpy(tmp,johnSmith->medRecord);

	char medRecord[200];
		//type,desc,medName,dosage,dateIssued,Note;
	char* tokenA = strtok(tmp,";");
	while(tokenA)
	{
		char* tokenB = strtok(tokenA,",");//Reads type onto token
		tokenB = strtok(NULL,","); //Reads desc onto token
		name = strtok(NULL,",");//Reads medName onto token
		tokenB = strtok(NULL,",");//Reads dosage onto token
		tokenB = strtok(NULL,",");//Reads dateIssued onto token
		tokenB = strtok(NULL,",");//Reads note onto token
		if(strcmp(tokenB,"Active") != 0)
			strcat(output,name + "\n");
	}
	printf("Data Hipo - Doctor/Nurse\n\nActive Medication List");
	printf("Patient First Name:%s\nPatient Last Name:%s\nPatient Date of Birth:%s\n",fname,lname,dob);
	printf("\nACTIVE MEDICATIONS\n-------------------\n%s",output);
	//function ends
}

void doctorMenu(int ptnID)
{
    int userIO = 0;
    int flag = 0;
   struct Patient patient = readPatient(ptnID);

    //Menu Options for the a user with doctor privileges.
    printf("Data Hipo - Patient Doctor Portal\n\n");
    printf("Menu: (1) Drug Interaction Checks  (2) Maintain Problem List    (3) E-Prescription\n");
    printf("      (4) Active Medication List   (5) Medication Allergy List  (6) Record Vital Signs\n");
    printf("      (7) Record Smoking Status    (8) Computerized Provider Order Entry (CPOE)\n");
    printf("      (9) Patient Information      (0) Exit\n");

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
            //Drug Interaction Checks
            //I need to make
            break;
        case(2):
            //Maintain Problem List
            //I need to make
            break;
        case(3):
            epatientMenu(patient);
            break;
        case(4):
            //Active Medacation List
            //from paitent info print all meds that have active in there notes.
            //I need to make
            break;
        case(5):
            //Medication Allergy List
            break;
        case(6):
            //Record Vital Signs
            break;
        case(7):
            //Record Smoking Status
            break;
        case(8):
            //Computerized Provider Order Entry (CPOE)
            //I need to make
            break;
        case(9):
            //Patient Information
            break;
        case(0):
            printf("Exiting.....");
    }
}


int main(void) {


	//Variables needed for runtime
	char uname[8];
	char pword[8];
	int patientID;
	int flag = 0;
	Paitent johnSmith;


	printf("Welcome to Data Hipo - Electronic Medical Record Software (EMS)\n\n\n");
	do
	{
		printf("Please enter your login information.\nUsername:");
		scanf("%8s",uname);
		printf("Password:");
		scanf("%8s",pword);
		printf("Patient#");
		scanf("%5d",patientID);//This will be passed to menu function to load patient info.

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

	printf("Thank you for using Data Hipo\nHave a nice day!");
	return 0;

}
