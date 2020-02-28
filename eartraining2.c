///////////////////////////////////////////////////////////////////////////////
// eartraining2.c
// by Sheng Kris Chen
///////////////////////////////////////////////////////////////////////////////
// This program is to test or train human absolute pitch dictation 
// using random generator to get the random pitch(es)
// with a self-assessment service provided in order to improve hearing
///////////////////////////////////////////////////////////////////////////////
// to compile and run: gcc -o eartraining2 eartraining2.c && ./eartraining2
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

//Get the random number from 1 - 12
int generate_random_number();

int main()
{
	
	printf("\n\t====================================================\n\n");
	printf("\t====== Welcome To The Ear Training Boot Camp! ======");
	printf("\n\n\t====================================================\n");
	printf("\nThis program will test and train your absolute pitch dictation!");
    printf("\n\nPress ENTER key to begin!");
    getchar(); 
    
    //Seed the random number generator with system clock
	srand((unsigned)time(0));
	int notenum, tempo, wave, i, pitch, key=1;
	float volume;
	char temp[500]; 
	char answer[500]; 
	char userin[500]; 
	
	while(key != '0')
	{
		temp[0] = '\0';
		answer[0] = '\0';
		userin[0] = '\0';
		
		printf("\n\nPlease type the number (integer) of note(s) you want to hear: ");
		scanf("%d", &notenum);
		
		printf("\n\nPlease give a tempo (integer) in beats per minute: ");
		scanf("%d", &tempo);
		
		printf("\n\nPlease choose a timbre (integer) from the following:\n1. Sine Wave\n2. Sawtooth Wave\n");
		scanf("%d", &wave);
		
		printf("\n\nPlease choose the volume (float) from 0 - 10: ");
		scanf("%f", &volume);

			FILE *csdfile;
			csdfile = fopen("eartraining.csd","w");	
			fprintf(csdfile,"<CsoundSynthesizer>\n");
  			fprintf(csdfile,"<CsInstruments>\n");
  			fprintf(csdfile,"sr = 44100\n");
  			fprintf(csdfile,"ksmps = 4410\n");
  			fprintf(csdfile,"nchnls = 1\n");
  			fprintf(csdfile,"0dbfs = 10\n");
			fprintf(csdfile,"gisine ftgen 1, 0, 4096, 10, 1\n");
			fprintf(csdfile,"gisaw ftgen 2, 0, 4096, 7, -1, 4096, 1\n");
  			fprintf(csdfile,"instr 1\n");
  			fprintf(csdfile,"kenv linen %f, .01, p3, .02\n", volume);
  			fprintf(csdfile,"aout oscil kenv, p4, p5\n");
  			fprintf(csdfile,"out aout\n");
  			fprintf(csdfile,"endin\n");
  			fprintf(csdfile,"</CsInstruments>\n");
  			fprintf(csdfile,"<CsScore>\n");
  			fprintf(csdfile, "t 0 %d\n", tempo);
  			
  			for(i = 0; i < notenum; i++)
			{
				pitch = generate_random_number();
				sprintf(temp, "%d.", pitch);
				strcat(answer, temp);
				
				//Convert to Hertz from C4 - B4
			   	switch (pitch)
   				{
   				case 1: pitch = 262;
   				break;
   		
   				case 2: pitch = 278;
   				break;
   		
   				case 3: pitch = 294;
   				break;
   		
   				case 4: pitch = 311;
   				break;
   		
   				case 5: pitch = 330;
   				break;
   		
   				case 6: pitch = 349;
   				break;
   		
   				case 7: pitch = 370;
   				break;
   		
   				case 8: pitch = 392;
   				break;
   		
   				case 9: pitch = 415;
   				break;
   		
   				case 10: pitch = 440;
   				break;
   		
   				case 11: pitch = 466;
   				break;
   		
   				case 12: pitch = 494;
   				break;
   				}	
				
				fprintf(csdfile, "i1 0 1 %d %d\n", pitch, wave);
				fprintf(csdfile, "s\nf0 .5\ns\n");
			}
				
			fprintf(csdfile, "</CsScore>\n");
			fprintf(csdfile, "</CsoundSynthesizer>\n");
			fclose(csdfile);
			
		//Play Csound file in Terminal

		printf("\n==================================================\n\n");
		system("csound -odac -m 0 -d eartraining.csd");
		
		printf("\nPlease use the numbers from below to match what you have heard:");
		printf("\n==================================\n");
		printf("\t1=C \t2=C# \t3=D \n\t4=D# \t5=E \t6=F \n\t7=F# \t8=G \t9=G# \n\t10=A \t11=A# \t12=B");
		printf("\n==================================\n");
		printf("Please type the number followed by a period (.): ");
		scanf("%s", userin);
		
		if(strcmp(answer, userin) == 0)
		{
			printf("\n==================================\n");
			printf("\tCorrect!");
			printf("\n==================================\n");
		}
		else
		{
			printf("\nIncorrect!");
			printf("\n==================================\n");
			printf("\tThe answer is %s", answer);
			printf("\n==================================\n");
			printf("\t1=C \t2=C# \t3=D \n\t4=D# \t5=E \t6=F \n\t7=F# \t8=G \t9=G# \n\t10=A \t11=A# \t12=B");
			printf("\n==================================\n");
			
		}

	printf("Press ENTER key to continue or 0 to quit:");
    getchar(); 	
    key = getchar();
    }
	
	printf("\n\n\n\t==========THE END==========\n\n\n");
	return 0;
}



//Get the random number from 1 - 12
int generate_random_number()
{
   int randomnumber;
   randomnumber = (rand() % 12) + 1;
   return randomnumber;
}
