//20358446 - Nathan Betts
// Software Engineering Project 1 Midterm.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//declartion of struct for all song data
struct album
{
  char artist[30];
  char song[50][50];
  int songMins[20];
  int songSecs[20];
};

// function prototypes
void userInput();

void sortArt(struct album data[],int numArt);

void sortSong(struct album data[],int numSongs,int numArt);

void randomPlaylist(struct album data[],int numSongs[],int numArt);

void extractTime(struct album data[],int i,int j);

int isSubstring(char allData[]);
int stringPresent(char songsPlayed[][50],struct album data[],int i,int playArt,int playSong);
int getOccurance(int artistFreq[],int numArt);


void fileInput();

int main()
{
  int choice;

//printing menu of choices for the user
printf("------------------Music Management System---------------\n\n");
printf(" Welcome! How would you like to enter your Music?\n");
printf("\n1. User \n\n");
printf("2. File\n\n");
printf("0. Exit\n\n");
printf("-----------------------------------------------------\n\n");
//scan their decision into choice
printf("\nPlease enter your Choice:");
scanf("%d",&choice);


switch(choice)
  {
  case 1: userInput();
  break;

  case 2: fileInput();
  break;

  case 0: exit(0);
  }
}
//------------------------------------------------------------------------------------------------------------------------------------

void userInput()
{
int numArt=0;
int totalSongs=0;
int i=0,j=0;
int numSongs=0;
int numberOfSongs[20];
//asks the user for the bounds of the outer loop
printf("\nHow Many Artists Would you like Enter?\n");

scanf("%d", &numArt);
fflush(stdin);
struct album data[numArt];
//loop over for numArt getting names
  for(i=0;i<numArt;i++)
  {
    fflush(stdin);
  printf("\nEnter Artist Name:");
//flush the standard input to clear it after every scanf
  scanf("%[^\n]s",&data[i].artist);
  fflush(stdin);
//read in number of artistes then for each ask how mnay songs and loop ovber that number and feed data into struct
  printf("\nHow Many Songs for that artist would you like Enter? ");
  scanf("%d", &numSongs);
  fflush(stdin);
    for(j=0;j<numSongs;j++)
      {
        numberOfSongs[i] = numSongs;
        fflush(stdin);
        printf("\nEnter the Name of the Song: ");
        scanf("%[^\n]s",&data[i].song[j]);
        fflush(stdin);
        printf("\nEnter the Minutes and Seconds of the Length of the Song: ");
        scanf("%d %d",&data[i].songMins[j],&data[i].songSecs[j]);
      }
}

//sort the Artists alphabeticlally
sortArt(data,numArt);

//sort the corresponding songs aplhabetically
for(i=0;i<numArt;i++){
    sortSong(data,numberOfSongs[i],numArt);
}
//print out the sorted artists and their songs
for(i=0;i<numArt;i++)
{
  printf("\n%s",data[i].artist);
    for(j=0;j<numberOfSongs[i];j++)
      {
        printf(" \n-%s***%d:%d",data[i].song[j],data[i].songMins[j],data[i].songSecs[j]);
      }
      printf("\n");
}
//create the randomised playlist
randomPlaylist(data,numberOfSongs,numArt);

}


//------------------------------------------------------------------------------------------------------------------------------------
void sortArt(struct album data[],int numArt)
{
  struct album temp[numArt];
  int i, j;
//loop over the artists and compare the current position to the next one,and if its comparison is greater than 0 meaning more alphabeticlally precende swap them
      for(i = 0; i <  numArt; i++)
      {
          for(j = i + 1; j < numArt; j++)
          {

              if(strcmp(data[i].artist, data[j].artist) > 0){
                temp[i] = data[i];
                data[i]= data[j];
                data[j] = temp[i];
              }
          }
      }
  }
//------------------------------------------------------------------------------------------------------------------------------------
void sortSong(struct album data[],int numSongs,int numArt)
{
  int i, j,a;
      char temp[100];
      int tempMinutes;
      int tempSeconds;
      //using same logic as sortArt exept with another outer loop for the number of artists sort each of the songs , while copying withit the songs runtime
      for(a = 0; a <  numArt; ++a)
      {
        for(i = 0; i < numSongs; ++i)
          {
            for(j = i + 1; j < numSongs; j++)
              {
              if(strcmp(data[a].song[i], data[a].song[j]) > 0)
              {
                  strcpy(temp, data[a].song[i]);
                  tempMinutes = data[a].songMins[i];
                  tempSeconds = data[a].songSecs[i];
                  strcpy(data[a].song[i], data[a].song[j]);
                  data[a].songMins[i] = data[a].songMins[j];
                    data[a].songSecs[i] = data[a].songSecs[j];
                  strcpy(data[a].song[j], temp);
                  data[a].songMins[j] = tempMinutes;
                  data[a].songSecs[j] = tempSeconds;
              }
          }
      }
    }
  }

  //------------------------------------------------------------------------------------------------------------------------------------
  int stringPresent(char songsPlayed[][50],struct album data[],int i,int playArt,int playSong) {
      int pch;
// function to see if a song has already been played buy checking if its an elemtn in the songsPLayed array
      for(i=0;i<50;i++)
      {
          pch=strcmp(songsPlayed[i],data[playArt].song[playSong]);

          if (pch==0)
          {
          return 1;
          }
      }

      return 0;
  }

//------------------------------------------------------------------------------------------------------------------------------------
  void randomPlaylist(struct album data[],int numSongs[],int numArt)
  {
    int playSong=0,playArt=0;
    int runtimeMinutes=0;
    int runtimeSeconds=0;
    int j=0;
    int i=0;
    int k=0;
    int b=0;
    int num_occur;
    int result;
    int artistFreq[20];
    int artistRecent[20];
    char songsPlayed[50][50];
    //calling of srand for the randomising
    srand(time(NULL));

printf("Randomised Playlist:\n");
for(i=0;i<20;i++)
{
  //set artist frequency to 0
artistFreq[i]=0;

}
//while the total runtime of the playlsit isnt over 60
    while(runtimeMinutes <= 60)
    {
    //using the rand function and the artist and numSongs as paramters select a random song
      playArt =  rand() % numArt;
      playSong = rand() % numSongs[playArt];
//call the string present function to make sure the same song hasnt been played already
    result =  stringPresent(songsPlayed,data,i,playArt,playSong);

    num_occur = getOccurance(artistFreq,playArt);

if(artistFreq[k] != artistFreq[k-2] && result != 1){// && num_occur == 1){

if(  (runtimeMinutes + data[playArt].songMins[playSong] <= 60)){
  //if adding the next song to the totalruntim doesnt push total runtime over 60 add the random song's time to total time
      runtimeMinutes += data[playArt].songMins[playSong];
      runtimeSeconds += data[playArt].songSecs[playSong];
      //add the artist to the artist frequency
      artistFreq[b] = playArt;
      b++;
      //copy the song into the songsplayed array
      strcpy(songsPlayed[i],data[playArt].song[playSong]);
      i++;
//increase the index for the songs array
}
else{
  //if runtime is over 60 break
  break;
}
//deals with seconds going over 60, if so add 1 to minutes and minus 60 from seconds
      if(runtimeSeconds >= 60)
      {
          runtimeSeconds = runtimeSeconds-60;
          runtimeMinutes++;
      }
      artistRecent[j] = playArt;
      j++;
      //print out random artist and random song from them
      printf("%s -'%s'***%d:%d\n",data[playArt].artist,data[playArt].song[playSong],data[playArt].songMins[playSong],data[playArt].songSecs[playSong]);
     }
   }
//after the loop is done print total duration
    printf("\nTotal Duration: %d:%d\n\n", runtimeMinutes,runtimeSeconds);
  }

//------------------------------------------------------------------------------------------------------------------------------------
  int isSubstring(char allData[]){
//function to see if *** is present in string to seperate the artists from the songs
    char search[20];
    int c1=0,c2=0,i,j,flg;
    strcpy(search,"***");

    while (allData[c1]!='\0')
      c1++;
                  c1--;

    while (search[c2]!='\0')
      c2++;
                  c2--;
//loop over the string and see if search string is presnt in string
    for(i=0;i<=c1-c2;i++)
    {
      for(j=i;j<i+c2;j++)
      {
        flg=1;
        if (allData[j]!=search[j-i])
        {
          flg=0;
           break;
        }
      }
      if (flg==1)
        break;
    }
    if (flg==1)

      return 1;
    else
      return 0;
  }

//------------------------------------------------------------------------------------------------------------------------------------
int getOccurance(int artistFreq[],int numArt)
{

int numArtOccurnaces =0;
int i =0;

for(i=0;i<20;i++)
{
  if(artistFreq[i]=numArt)
  {
  numArtOccurnaces++;
  }
}
if(numArtOccurnaces<3)
{
  return 1;
}
else
{
  return -1;
}

}

//------------------------------------------------------------------------------------------------------------------------------------
void fileInput()
{
   FILE *fptr = NULL;
   char fname[100];
   char allData[100][100] ={0};
   int i=0,q=0,j=0,x=0;
   char artist[30][30];
   int allDataLength=0;
   int numArt=0;
   int Songs=0;
   int flag=0;
   char content[30];
   int numSongs[10];
   int c,result,result2,counter=0;
   char song[40][60];
//scan file name in and check that it opens if not ask again
  printf("Enter  the file name:\n ");

  scanf("%s", &fname);

  fptr = fopen(fname, "r");
  c = fgetc(fptr);
  if (fptr == NULL)
      {
          printf("\nError, Unable to open the file for reading\n");
          printf("Enter  the file name:\n ");
          scanf("%s", &fname);
          fflush(stdin);
            }

    struct album data[50];

    j=0;
    i=0;
    Songs=0;
    //while the end of file hasnt been reached read in line by line
    while((fgets(allData[i],200,fptr))!=NULL)
    {
      //see's if *** is present
        result = isSubstring(allData[i]);
        if(result != 1)
        {
          //if its not present then its an artist , fill the struct
            strcpy(data[j].artist,allData[i]);
            //set index for that artists songs to 0
            x = 0;
            Songs=0;
            numArt++;
            //increase the number of artists
        }

        else if((strcmp(allData[i],"\n")!= 0) && (result == 1)){
              //checks to make sure its not a new line then its a song add it to struct and increase x index until next artist
            strcpy(data[j].song[x],allData[i]);
            Songs++;
            x++;
        }
        else{
          //otherwise its a new line, so add the number of songs to numSongs array then increase the index for the next artist
            numSongs[j] = Songs ;
            j++;
        }

        allDataLength++;
        i++;
    }
//loops over the artists and their songs and extracts the time into the struct form file input
    for(i=0;i<numArt;i++){
      for(j=0;j<numSongs[i];j++){
        extractTime(data,i,j);

      }
    }
printf("\n");
//create a randomised playlist and print it out
  randomPlaylist(data,numSongs,numArt);
  //loop overt the struct and sort the songs aplhabeticallt
    for(i=0;i<numArt;i++){
        sortSong(data,numSongs[i],numArt);

    }
//sort the artists and copy the sorted songs with them
    sortArt(data,numArt);
//print out sorted artsits and their songs
    printf("Sorted list of artistes and songs:\n\n");
    for(i=0;i<numArt;i++){
        printf("%s", data[i].artist);
        for(q=0;q<10;q++){
          //dont print new line characters
            if(strlen(data[i].song[q]) != 0) {
                printf(" -%s***%d:%d \n", data[i].song[q],data[i].songMins[q],data[i].songSecs[q]);
            }
        }
          printf("\n");
    }

    fclose(fptr);
}
//------------------------------------------------------------------------------------------------------------------------------------
void extractTime(struct album data[],int i,int j){
//function to extract the minute sand seconds from file input
  const char s[] = "***";
  char allSongs[20][20];
  char *token;
  int index=0;
//using strtok break the string by the presence of *** in it then the next data is the minutes and seconds in format MM:ss
  token = strtok(data[i].song[j], s);

  while( token != NULL ) {
  strcpy(allSongs[index] ,token );
     token = strtok(NULL, s);
     index++;
  }
  //scan the times into the structs.
  sscanf(allSongs[1],"%d:%d",&data[i].songMins[j],&data[i].songSecs[j]);
}
