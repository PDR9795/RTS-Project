

#include <iostream>
#include <time.h>
#include "LST.h"
using namespace std;


double LST(int Tnum, int Pnum)
{
    double SlackTime[100];
    double Time = 0;
    double Time2 = 0;
    double Time3 = 0;
    double LTime;
    double Lowest;
    double Tarr[100][3];

    int Task = 0;
    int ChosenTime;

    bool Done = false;
    bool Check = false;

    for (int x = 0; x < 50; x++)
    {
        for (int y = 0; y < 50; y++)
        {
            Tarr[x][y] = TaskArr[x][y];
        }
    }

    for(int i=0; i<Tnum; i++)                                                    //calculating all slack times of each task
      SlackTime[i] = Tarr[i][0] - Tarr[i][1];

    Lowest = SlackTime[0];

    while(!Done)
    {
      Check = false;
      for(int i=0; i<Tnum; i++)                                                  //for loop to check for least slack time
      {
        if((SlackTime[i] < Lowest) && (Tarr[i][1] > 0.00))                       //if current task has least slack time, choose it
        {
          Task = i;
          Lowest = SlackTime[i];
        }
        else if (Tarr[i][1] <= 0.00)                                             //if check stays false, we are done with all tasks
          Check = true;
      }

      if(Tarr[Task][1] > 0.00)                                                   //if task not executed, execute it
      {
        if(Pnum == 1)                                                            //one processor
        {
          Time = Time + Tarr[Task][1];
          ChosenTime = 1;
        }
        else if(Pnum == 2)                                                       //two processors
        {
          if (Time <= Time2)                                                     //chose cpu 1
          {
            Time = Time + Tarr[Task][1];
            ChosenTime = 1;
          }
          else                                                                   //chose cpu 2
          {
            Time2 = Time2 + Tarr[Task][1];
            ChosenTime = 2;
          }
        }
        else if (Pnum == 3)                                                      //three processors
        {
          if (Time <= Time2 && Time <= Time3)                                    //chose cpu 1
          {
            Time = Time + Tarr[Task][1];
            ChosenTime = 1;
          }
          else if (Time > Time2 && Time2 <= Time3)                              //chose cpu 2
          {
            Time2 = Time2 + Tarr[Task][1];
            ChosenTime = 2;
          }
          else                                                                   //chose cpu 3
          {
            Time3 = Time3 + Tarr[Task][1];
            ChosenTime = 3;
          }
        }
        Tarr[Task][1] = 0;                                                       //zero out execution time of current task
      }
      if(ChosenTime == 1)                                                        //if used cpu 1, check to see if it passed deadline
      {
        if (Tarr[Task][0] > Time)
            Tarr[Task][2] = 1;
        else if(Tarr[Task][0] <= Time)
            Tarr[Task][2] = 0;
      }
      else if(ChosenTime == 2)                                                   //if used cpu 2, check to see if it passed deadline
      {
        if (Tarr[Task][0] > Time2)
            Tarr[Task][2] = 1;
        else if(Tarr[Task][0] <= Time2)
            Tarr[Task][2] = 0;
      }
      else if(ChosenTime == 3)                                                   //if used cpu 3, check to see if it passed deadline
      {
        if (Tarr[Task][0] > Time3)
            Tarr[Task][2] = 1;
        else if(Tarr[Task][0] <= Time3)
            Tarr[Task][2] = 0;
      }
      if(Check == false)
        Done = true;
    }

    for(int i=0; i<Tnum; i++)
    {
      if(Tarr[i][2] == 1.0)
        cout << "Task "  << i << " did not complete deadline during Earliest Deadline First." << endl;
    }

    if(Time >= Time2 && Time >= Time3)                                           //check all cpus for longest amount of time
      LTime = Time;
    else if(Time < Time2 && Time2 >= Time3)
      LTime = Time2;
    else
      LTime = Time3;

    cout << "During Earliest Deadline First, it took all tasks " << LTime << " to finish" << endl;


    return LTime;
}
