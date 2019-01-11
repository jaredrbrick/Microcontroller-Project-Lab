const int led1Pin =  P2_6;
const int led2Pin = P2_7;
const int spot[9] = {P1_0, P1_1, P1_2, P1_3, P1_4,P1_5,P2_0,P2_1,P2_2};
int board[9]={0,0,0,0,0,0,0,0,0};
int Player=1;
int winner=0;
int boardupdated=0;
int turn=1;
int test;
int p;
const int binout[4]= {P1_7, P1_6, P2_5, P2_4};
void setup()
{
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  for (int j=0; j<9; j++)
  {
    pinMode(spot[j], INPUT_PULLUP);
    attachInterrupt(spot[j], blink, FALLING);
    if (j<4)
        {
            pinMode(binout[j], OUTPUT);
        }
    board[j]=0;
  }
  //Flash lights to confirm everything is working
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  //digitalWrite(binout[0],HIGH);
  // digitalWrite(binout[1],HIGH);
  // digitalWrite(binout[2],HIGH);
  // digitalWrite(binout[3],HIGH);
  // delay(2000);
   digitalWrite(binout[0],LOW);
     digitalWrite(binout[1],LOW);
     digitalWrite(binout[2],LOW);
     digitalWrite(binout[3],LOW);
}

void loop()
{
    p= isWinner();

    if (p==1) //Player 1 Wins
    {
        digitalWrite(led1Pin,HIGH);
        delay(100000);
    }
    if (p==2) //Player 2 Wins
    {
        digitalWrite(led2Pin,HIGH);
        delay(100000);
    }
    if (p==3) //Tie
    {
        digitalWrite(led1Pin,HIGH);
        digitalWrite(led2Pin,HIGH);
        delay(100000);
    }



  while(Player==1)
  {
    delay(1000);
    digitalWrite(led1Pin,HIGH);
    delay(1000);
    digitalWrite(led1Pin,LOW);
  }

  if(Player==2) //Crane's Turn
  {
      test=algorithm();

      //Blink it
            digitalWrite(binout[0],HIGH);
            digitalWrite(binout[1],HIGH);
            digitalWrite(binout[2],HIGH);
            digitalWrite(binout[3],HIGH);
            delay(200); //Gives time for crane to see signal
            digitalWrite(binout[0],LOW);
            digitalWrite(binout[1],LOW);
            digitalWrite(binout[2],LOW);
            digitalWrite(binout[3],LOW);

      if (test==1) //0001
      {
          digitalWrite(binout[3],HIGH);
      }
      if (test==2) //0010
      {
          digitalWrite(binout[2],HIGH);
      }
      if (test==3) //0011
      {
          digitalWrite(binout[3],HIGH);
          digitalWrite(binout[2],HIGH);
      }
      if (test==4) //0100
      {
          digitalWrite(binout[1],HIGH);
      }
      if (test==5) //0101
      {
          digitalWrite(binout[3],HIGH);
          digitalWrite(binout[1],HIGH);
      }
      if (test==6) //0110
      {
          digitalWrite(binout[1],HIGH);
          digitalWrite(binout[2],HIGH);
      }
      if (test==7) //0111
      {
          digitalWrite(binout[1],HIGH);
          digitalWrite(binout[2],HIGH);
          digitalWrite(binout[3],HIGH);
      }
      if (test==8) //1000
      {
          digitalWrite(binout[0],HIGH);
      }
      if (test==9) //1001
      {
          digitalWrite(binout[0],HIGH);
          digitalWrite(binout[3],HIGH);
      }



      delay(10000); //Gives time for crane to see signal
      digitalWrite(binout[0],LOW);
      digitalWrite(binout[1],LOW);
      digitalWrite(binout[2],LOW);
      digitalWrite(binout[3],LOW);
    }
  while(Player==2)
  {
    delay(1000);
    digitalWrite(led2Pin,HIGH);
    delay(1000);
    digitalWrite(led2Pin,LOW);
  }


  for (int j=0; j<9; j++)    detachInterrupt(spot[j]);
  delay(250); //Change this variable if there are detection issues

  for(int k=0; k<9; k++)
  {
   if (board[k]==1||board[k]==2) //Do we know about this ball
     {
       //If we do, do nothing
     }
   else if (digitalRead(spot[k])==LOW) //There is a ball in the spot
   {
       if(Player==3)
       {
         board[k]=1;
         boardupdated=1;
       }
       else if(Player==4)
       {
         board[k]=2;
         boardupdated=1;
       }
       if(Player==5) //Sometimes the interrupt gets called twice
       {
                board[k]=1;
                boardupdated=1;
       }
   }
  }

  if (boardupdated==1)
  {
    boardupdated=0;
    turn++;
    if(Player==3) Player=2;
    else if (Player==4) Player=1;
    if(Player==5) Player=2;
  }

  else {Player= Player-2;}

  for (int j=0; j<9; j++)
  {
    if (board[j]==0) attachInterrupt(spot[j], blink, FALLING);
  }

}

void blink()
{
  if(Player==1)
  {
      Player=3;
  }
  if(Player==2)
  {
      Player=4;
  }
}

int isWinner()
{
    if ((board[0]==1) && (board[1]==1) && (board[2]==1)) return 1;

    if ((board[0]==2) && (board[1]==2) && (board[2]==2) ) return 2;

    //3 4 5

    if ((board[3]==1) && (board[4]==1) && (board[5]==1) ) return 1;

    if ((board[3]==2) && (board[4]==2) && (board[5]==2) ) return 2;

    //6 7 8

    if ((board[6]==1) && (board[7]==1) && (board[8]==1) ) return 1;

    if ((board[6]==2) && (board[7]==2) && (board[8]==2) ) return 2;

    //Vertical Ways

    //0 3 6

    if ((board[0]==1) && (board[3]==1) && (board[6]==1) ) return 1;

    if ((board[0]==2) && (board[3]==2) && (board[6]==2 )) return 2;

    //1 4 7

    if ((board[1]==1) && (board[4]==1) && (board[7]==1) ) return 1;

    if ((board[1]==2) && (board[4]==2) && (board[7]==2)) return 2;

    //2 5 8

    if ((board[2]==1) && (board[5]==1) && (board[8]==1) ) return 1;

    if ((board[2]==2) && (board[5]==2) && (board[8]==2) ) return 2;

    //Diagonal Ways

    //0 4 8
    if ((board[0]==1) && (board[4]==1) && (board[8]==1) ) return 1;

    if ((board[0]==2) && (board[4]==2) && (board[8]==2) ) return 2;

    //2 4 6
    if ((board[2]==1) && (board[4]==1) && (board[6]==1) ) return 1;

    if ((board[2]==2) && (board[4]==2) && (board[6]==2) ) return 2;

    //For ties
    if (((board[0]==1)||(board[0]==2))&&((board[1]==1)||(board[1]==2))&&((board[2]==1||(board[2]==2))&&(board[3]==1||(board[3]==2))&&((board[4]==1)||(board[4]==2))&&((board[5]==1)||(board[5]==2))&&(board[6]==1||(board[6]==2))&&(board[7]==1||(board[7]==2))&&(board[8]==1||(board[8]==2))))
   {
     return 3;
   }
   else return 4;
}

int algorithm()
{
        //First let's see if we can win
        if ((board[0]==2) && (board[1]==2) && (board[2]==0) ) return 3;
        if ((board[0]==2) && (board[1]==0) && (board[2]==2) ) return 2;
        if ((board[0]==0) && (board[1]==2) && (board[2]==2) ) return 1;

        //3 4 5

        if ((board[3]==2) && (board[4]==2) && (board[5]==0) ) return 6;
        if ((board[3]==2) && (board[4]==0) && (board[5]==2) ) return 5;
        if ((board[3]==0) && (board[4]==2) && (board[5]==2) ) return 4;

        //6 7 8

        if ((board[6]==2) && (board[7]==2) && (board[8]==0) ) return 9;
        if ((board[6]==2) && (board[7]==0) && (board[8]==2) ) return 8;
        if ((board[6]==0) && (board[7]==2) && (board[8]==2) ) return 7;

        //Vertical Ways

        //0 3 6

        if ((board[0]==2) && (board[3]==2) && (board[6]==0)) return 7;
        if ((board[0]==2) && (board[3]==0) && (board[6]==2)) return 4;
        if ((board[0]==0) && (board[3]==2) && (board[6]==2)) return 1;

        //1 4 7

        if ((board[1]==2) && (board[4]==2) && (board[7]==0)) return 8;
        if ((board[1]==2) && (board[4]==0) && (board[7]==2)) return 5;
        if ((board[1]==0) && (board[4]==2) && (board[7]==2)) return 2;

        //2 5 8

        if ((board[2]==2) && (board[5]==2) && (board[8]==0)) return 9;
        if ((board[2]==2) && (board[5]==0) && (board[8]==2)) return 6;
        if ((board[2]==0) && (board[5]==2) && (board[8]==2)) return 3;

        //Diagonal Ways

        //0 4 8

        if ((board[0]==2) && (board[4]==2) && (board[8]==0) ) return 9;
        if ((board[0]==2) && (board[4]==0) && (board[8]==2) ) return 5;
        if ((board[0]==0) && (board[4]==2) && (board[8]==2) ) return 1;

        //2 4 6

        if ((board[2]==2) && (board[4]==2) && (board[6]==0) ) return 7;
        if ((board[2]==2) && (board[4]==0) && (board[6]==2) ) return 5;
        if ((board[2]==0) && (board[4]==2) && (board[6]==2) ) return 3;





   int bs=35;
   if (turn==2)
   {



     if (board[4]==0)//Take the middle if it's open
       {
         bs=5;
       }
     else //Or take a corner
       {
         bs=7;
       }
   }
   else
   {
       //Fork blocking Code... Thanks google
                 if ((board[7]==1) && (board[3]==1) && (board[6]==0) ) bs=7;
                 if ((board[3]==1) && (board[1]==1) && (board[0]==0) ) bs=1;
                 if ((board[1]==1) && (board[5]==1) && (board[2]==0) ) bs=3;
                 if ((board[5]==1) && (board[7]==1) && (board[8]==0) ) bs=9;

                 if (board[8]==1 && board[1]==1 && board[2]==0) bs=3;
                 if (board[6]==1 && board[1]==1 && board[0]==0) bs=1;
                 if (board[5]==1 && board[6]==1 && board[8]==0) bs=9;
                 if (board[5]==1 && board[0]==1 && board[2]==0) bs=3;
                 if (board[7]==1 && board[2]==1 && board[8]==0) bs=9;
                 if (board[7]==1 && board[0]==1 && board[6]==0) bs=7;
                 if (board[3]==1 && board[8]==1 && board[6]==0) bs=7;
                 if (board[3]==1 && board[2]==1 && board[0]==0) bs=1;
       if(board[4]==1)
       {
             if (board[8]==1 && board[0]==0) return 1;
              else if (board[7]==1 && board[1]==0) return 2;
              else if (board[6]==1 && board[2]==0) return 3;
              else if (board[5]==1 && board[3]==0) return 4;
              else if (board[3]==1 && board[5]==0) return 6;
              else if (board[2]==1 && board[6]==0) return 7;
              else if (board[1]==1 && board[7]==0) return 8;
              else if (board[0]==1 && board[8]==0) return 9;
       }
      if (board[7]==1)
      {
        if (board[8]==1) bs=7;
        else if(board[6]==1) bs=9;
      }
      else if(board[3]==1)
      {
        if (board[6]==1) bs=1;
        else if(board[0]==1) bs=7;
      }
      else if(board[1]==1)
      {
        if (board[0]==1) bs=3;
        else if(board[2]==1) bs=1;
      }
      else if(board[5]==1)
      {
        if (board[8]==1) bs=3;
        else if(board[2]==1) bs=9;
      }

      if (board[8]==1 && board[6]==1)
      {
        if (board[7]==0) bs=8;
      }
      if(board[6]==1 && board[0]==1)
      {
        if (board[3]==0) bs=4;
      }
      if(board[0]==1 && board[2]==1)
      {
        if (board[1]==0) bs=2;
      }
      if(board[8]==1 && board[2]==1)
      {
        if (board[5]==0) bs=6;
      }

   }




   while(board[bs-1]!=0||bs==35)
      {
        bs=random(1, 10);
      }
   return bs;
}
