

#include <iostream>
#include <time.h>
#include "RoundRobin.h"
using namespace std;


double RoundRobin(int Tnum, int Pnum)
{
  double TQuanta = 0;
  double Time = 0;
  double Time2 = 0;
  double Time3 = 0;
  double LTime;
  double Tarr[100][3];

  int Count;
  int ChosenTime;

  bool Check = false;
  bool Done = false;

  for (int x = 0; x < 50; x++)
  {
      for (int y = 0; y < 50; y++)
      {
          Tarr[x][y] = TaskArr[x][y];
      }
  }

  for(int i=0; i<Tnum; i++)                                                      //finding time qaunta/average exe time
    TQuanta = TQuanta + Tarr[i][1];

  TQuanta = TQuanta / Tnum;


  Count = 0;

  while (!Done)                                                                  //keeps going until all tasks are complete
  {
    if((Tarr[Count][1] > TQuanta) && (Tarr[Count][1] != 0.0))                    //If exe time is greater than time quanta
    {
        Tarr[Count][1] = Tarr[Count][1] - TQuanta;                                 //subtract time quanta from exe time
      if(Pnum == 1)                                                              //one processor
      {
        Time = Time + TQuanta;
        ChosenTime = 1;
      }
      else if(Pnum == 2)                                                         //two processors
      {
        if (Time <= Time2)
        {                                                      //chose cpu 1
          Time = Time + TQuanta;
          ChosenTime = 1;
        }
        else                                                                     //chose cpu 2
        {
          Time2 = Time2 + TQuanta;
          ChosenTime = 2;
        }
      }
      else if (Pnum == 3)                                                        //three processors
      {
        if (Time <= Time2 && Time <= Time3)                                      //chose cpu 1
        {
          Time = Time + TQuanta;
          ChosenTime = 1;
        }
        else if (Time > Time2 && Time2 <= Time3)                                //chose cpu 2
        {
          Time2 = Time2 + TQuanta;
          ChosenTime = 2;
        }
        else                                                                     //chose cpu 3
        {
            Time3 = Time3 + TQuanta;
          ChosenTime = 3;
        }
      }

    }
    else if((Tarr[Count][1] <= TQuanta) && (Tarr[Count][1] != 0.0))              //else if exe time is less than or equal to time quanta
    {
      if(Pnum == 1)                                                              //one processor
      {
        Time = Time + Tarr[Count][1];
        ChosenTime = 1;
      }
      else if(Pnum == 2)                                                         //two processors
      {
        if (Time <= Time2)                                                       //chose cpu 1
        {
          Time = Time + Tarr[Count][1];
          ChosenTime = 1;
        }
        else                                                                     //chose cpu 2
        {
          Time2 = Time2 + Tarr[Count][1];
          ChosenTime = 2;
        }
      }
      else if (Pnum == 3)                                                        //three processors
      {
        if (Time <= Time2 && Time <= Time3)                                      //chose cpu 1
        {
          Time = Time + Tarr[Count][1];
          ChosenTime = 1;
        }
        else if (Time > Time2 && Time2 <= Time3)                                //chose cpu 2
        {
          Time2 = Time2 + Tarr[Count][1];
          ChosenTime = 2;
        }
        else                                                                     //chose cpu 3
        {
          Time3 = Time3 + Tarr[Count][1];
          ChosenTime = 3;
        }
      }
      Tarr[Count][1] = 0;                                                        //zero out exec time
    }

    if(ChosenTime == 1)                                                          //if used cpu 1, check to see if it passed deadline
    {
      if (Tarr[Count][0] > Time)
        Tarr[Count][2] = 1;
      else if(Tarr[Count][0] <= Time)
          Tarr[Count][2] = 0;
    }
    else if(ChosenTime == 2)                                                     //if used cpu 2, check to see if it passed deadline
    {
      if (Tarr[Count][0] > Time2)
          Tarr[Count][2] = 1;
      else if(Tarr[Count][0] <= Time2)
          Tarr[Count][2] = 0;
    }
    else if(ChosenTime == 3)                                                     //if used cpu 3, check to see if it passed deadline
    {
      if (Tarr[Count][0] > Time3)
          Tarr[Count][2] = 1;
      else if(Tarr[Count][0] <= Time3)
          Tarr[Count][2] = 0;
    }
    if(Check == false)
      Done = true;
  }


    Check = false;
    for(int i=0; i<Tnum; i++)                                                    //Check to see if all tasks are finished
    {
      if(Tarr[i][1] != 0.0)
        Check = true;
    }
    if(Check = false)
      Done = true;

     Count++;
     if(Count >= Tnum)
      Count = 0;
  
  for(int i=0; i<Tnum; i++)
  {
    if(Tarr[i][2] == 1.0)
      cout << "Task "  << i << " did not complete deadline during Round Robin." << endl;
  }

  if(Time >= Time2 && Time >= Time3)                                           //check all cpus for longest amount of time
    LTime = Time;
  else if(Time < Time2 && Time2 >= Time3)
    LTime = Time2;
  else
    LTime = Time3;

  cout << "During Round Robin, it took all tasks " << Time << " to finish" << endl;

  return LTime;
}
