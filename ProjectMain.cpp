//Programmers: Lucas Reynolds | Matthew Grey
//Final Semester Project


#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>
using namespace std;


int TaskArr[100][4] = {};

int RoundRobin(int Tnum, int Pnum)
{
    int TQuanta = 0;
    int Time = 0;
    int Time2 = 0;
    int Time3 = 0;
    int LTime;
    int Tarr[100][4] = {};

    int Count;


    bool Check = false;
    bool Done = false;

    for (int x = 0; x < Tnum; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            Tarr[x][y] = TaskArr[x][y];
        }
    }
  
    for (int i = 0; i < Tnum; i++)                                                      //finding time qaunta/average exe time
        TQuanta = TQuanta + Tarr[i][1];

    TQuanta = TQuanta / Tnum;


    Count = 0;

    while (Done == false)                                                                  //keeps going until all tasks are complete
    {
        if ((Tarr[Count][1] > TQuanta) && (Tarr[Count][3] == 0))                    //If exe time is greater than time quanta
        {
            Tarr[Count][1] = Tarr[Count][1] - TQuanta;                                 //subtract time quanta from exe time
            if (Pnum == 1)                                                              //one processor
            {
                if (Tarr[Count][0] > Time)
                    Tarr[Count][2] = 1;

                Time = Time + TQuanta;

            }
            else if (Pnum == 2)                                                         //two processors
            {
                if (Time <= Time2)
                {                                                                        //chose cpu 1
                    if (Tarr[Count][0] > Time)
                        Tarr[Count][2] = 1;

                    Time = Time + TQuanta;

                }
                else                                                                     //chose cpu 2
                {
                    if (Tarr[Count][0] > Time2)
                        Tarr[Count][2] = 1;


                    Time2 = Time2 + TQuanta;

                }
            }
            else if (Pnum == 3)                                                        //three processors
            {
                if (Time <= Time2 && Time <= Time3)                                      //chose cpu 1
                {
                    if (Tarr[Count][0] > Time)
                        Tarr[Count][2] = 1;

                    Time = Time + TQuanta;

                }
                else if (Time > Time2 && Time2 <= Time3)                                //chose cpu 2
                {
                    if (Tarr[Count][0] > Time2)
                        Tarr[Count][2] = 1;

                    Time2 = Time2 + TQuanta;

                }
                else                                                                     //chose cpu 3
                {
                    if (Tarr[Count][0] > Time3)
                        Tarr[Count][2] = 1;

                    Time3 = Time3 + TQuanta;

                }

            }

        }
        else if ((Tarr[Count][1] <= TQuanta) && (Tarr[Count][3] == 0))              //else if exe time is less than or equal to time quanta
        {
            if (Pnum == 1)                                                              //one processor
            {
                if (Tarr[Count][0] > Time)
                    Tarr[Count][2] = 1;

                Time = Time + Tarr[Count][1];
            }
            else if (Pnum == 2)                                                         //two processors
            {
                if (Time <= Time2)                                                       //chose cpu 1
                {
                    if (Tarr[Count][0] > Time)
                        Tarr[Count][2] = 1;


                    Time = Time + Tarr[Count][1];
                }
                else                                                                     //chose cpu 2
                {
                    if (Tarr[Count][0] > Time2)
                        Tarr[Count][2] = 1;


                    Time2 = Time2 + Tarr[Count][1];
                }
            }
            else if (Pnum == 3)                                                        //three processors
            {
                if (Time <= Time2 && Time <= Time3)                                      //chose cpu 1
                {
                    if (Tarr[Count][0] > Time)
                        Tarr[Count][2] = 1;

                    Time = Time + Tarr[Count][1];
                }
                else if (Time > Time2 && Time2 <= Time3)                                //chose cpu 2
                {
                    if (Tarr[Count][0] > Time2)
                        Tarr[Count][2] = 1;

                    if (Tarr[Count][0] > Time2)
                        Tarr[Count][2] = 1;
                    else if (Tarr[Count][0] <= Time2)
                        Tarr[Count][2] = 0;

                    Time2 = Time2 + Tarr[Count][1];
                }
                else                                                                     //chose cpu 3
                {
                    if (Tarr[Count][0] > Time3)
                        Tarr[Count][2] = 1;


                    Time3 = Time3 + Tarr[Count][1];
                }
            }
            Tarr[Count][3] = 1;                                                        //zero out exec time
        }

       
        Check = false;
        for (int i = 0; i < Tnum; i++)                                                    //Check to see if all tasks are finished
        {
            if (Tarr[i][3] == 0)
                Check = true;
        }
        if (Check == false)
            Done = true;
        else
            Count++;

        if (Count >= Tnum)
            Count = 0;
  
    }




    for (int i = 0; i < Tnum; i++)
    {
        if (Tarr[i][2] == 1.0)
            cout << "Task " << i+1 << " did not complete deadline during Round Robin." << endl;
    }

    if (Pnum > 1)
    {
        if (Time >= Time2 && Time >= Time3)                                           //check all cpus for longest amount of time
            LTime = Time;
        else if (Time < Time2 && Time2 >= Time3)
            LTime = Time2;
        else
            LTime = Time3;
    }
    else
        LTime = Time;

    cout << "Round Robin took " << Time << " seconds" << endl;

    return LTime;
}
int EDF(int Tnum, int Pnum)
{
    int Time = 0;
    int Time2 = 0;
    int Time3 = 0;
    int LTime;
    int Lowest;
    int Tarr[100][4] = {};

    int Task = 0;
    int ChosenTime = 0;

    bool Done = false;
    bool Check = false;

    for (int x = 0; x < Tnum; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            Tarr[x][y] = TaskArr[x][y];
        }
    }

    Lowest = Tarr[0][0];

    while (Done == false)
    {
        Check = false;
        Lowest = 11;
        for (int i = 0; i < Tnum; i++)                                                   //for loop to check for earliest deadline
        {
            if ((Tarr[i][0] < Lowest) && (Tarr[i][3] == 0))                          //if current task has earlier deadline, choose it
            {
                Task = i;
                Lowest = Tarr[i][0];
            }
            else if (Tarr[i][3] == 0 )                                             //if check stays false, we are done with all tasks
                Check = true;
        }

        if (Tarr[Task][3] == 0)                                                   //if task not executed, execute it
        {
            if (Pnum == 1)                                                            //one processor
            {
                if (Tarr[Task][0] > Time)
                    Tarr[Task][2] = 1;

                Time = Time + Tarr[Task][1];
            }
            else if (Pnum == 2)                                                       //two processors
            {
                if (Time <= Time2)                                                     //chose cpu 1
                {
                    if (Tarr[Task][0] > Time)
                        Tarr[Task][2] = 1;

                    Time = Time + Tarr[Task][1];
                }
                else                                                                   //chose cpu 2
                {
                    if (Tarr[Task][0] > Time2)
                        Tarr[Task][2] = 1;

                    Time2 = Time2 + Tarr[Task][1];
                }
            }
            else if (Pnum == 3)                                                      //three processors
            {
                if (Time <= Time2 && Time <= Time3)                                    //chose cpu 1
                {
                    if (Tarr[Task][0] > Time)
                        Tarr[Task][2] = 1;

                    Time = Time + Tarr[Task][1];
                }
                else if (Time > Time2 && Time2 <= Time3)                              //chose cpu 2
                {
                    if (Tarr[Task][0] > Time2)
                        Tarr[Task][2] = 1;
                    Time2 = Time2 + Tarr[Task][1];
                }
                else                                                                   //chose cpu 3
                {
                    if (Tarr[Task][0] > Time3)
                        Tarr[Task][2] = 1;

                    Time3 = Time3 + Tarr[Task][1];
                }
            }
            Tarr[Task][3] = 1;                                                       //zero out execution time of current task
        }

        if (Check == false)
            Done = true;
    }

    for (int i = 0; i < Tnum; i++)
    {
        if (Tarr[i][2] == 1)
            cout << "Task " << i+1 << " did not complete deadline during Earliest Deadline First." << endl;
    }

    if (Pnum > 1)
    {
        if (Time >= Time2 && Time >= Time3)                                           //check all cpus for longest amount of time
            LTime = Time;
        else if (Time < Time2 && Time2 >= Time3)
            LTime = Time2;
        else
            LTime = Time3;
    }
    else
        LTime = Time;


    cout << "Earliest Deadline First took " << LTime << " seconds" << endl;


    return LTime;
}
int LST(int Tnum, int Pnum)
{
    int SlackTime[100] = {};
    int Time = 0;
    int Time2 = 0;
    int Time3 = 0;
    int LTime;
    int Lowest;
    int Tarr[100][4] = {};
    int Task = 0;
    int ChosenTime = 0;

    bool Done = false;
    bool Check = false;

    for (int x = 0; x < Tnum; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            Tarr[x][y] = TaskArr[x][y];
        }
    }

    for (int i = 0; i < Tnum; i++)                                                    //calculating all slack times of each task
    {
        SlackTime[i] = Tarr[i][0] - Tarr[i][1];
    }

    Lowest = SlackTime[0];

    while (Done == false)
    {
        Check = false;
        Lowest = 11;
        for (int i = 0; i < Tnum; i++)                                                  //for loop to check for least slack time
        {
            if ((SlackTime[i] < Lowest) && (Tarr[i][3] == 0))                       //if current task has least slack time, choose it
            {
                Task = i;
                Lowest = SlackTime[i];
            }
            else if (Tarr[i][3] == 0.00)                                             //if check stays false, we are done with all tasks
                Check = true;
        }

        if (Tarr[Task][3] == 0)                                                   //if task not executed, execute it
        {
            if (Pnum == 1)                                                            //one processor
            {
                if (Tarr[Task][0] > Time)
                    Tarr[Task][2] = 1;

                Time = Time + Tarr[Task][1];
            }
            else if (Pnum == 2)                                                       //two processors
            {
                if (Time <= Time2)                                                     //chose cpu 1
                {
                    if (Tarr[Task][0] > Time)
                        Tarr[Task][2] = 1;

                    Time = Time + Tarr[Task][1];
                }
                else                                                                   //chose cpu 2
                {
                    if (Tarr[Task][0] > Time2)
                        Tarr[Task][2] = 1;

                    Time2 = Time2 + Tarr[Task][1];
                }
            }
            else if (Pnum == 3)                                                      //three processors
            {
                if (Time <= Time2 && Time <= Time3)                                    //chose cpu 1
                {
                    if (Tarr[Task][0] > Time)
                        Tarr[Task][2] = 1;

                    Time = Time + Tarr[Task][1];
                }
                else if (Time > Time2 && Time2 <= Time3)                              //chose cpu 2
                {
                    if (Tarr[Task][0] > Time2)
                        Tarr[Task][2] = 1;
                    Time2 = Time2 + Tarr[Task][1];
                }
                else                                                                   //chose cpu 3
                {
                    if (Tarr[Task][0] > Time3)
                        Tarr[Task][2] = 1;

                    Time3 = Time3 + Tarr[Task][1];
                }
            }
            Tarr[Task][3] = 1;                                                       //zero out execution time of current task
        }
        if (Check == false)
            Done = true;
    }

    for (int i = 0; i < Tnum; i++)
    {
        if (Tarr[i][2] == 1.0)
            cout << "Task " << i+1 << " did not complete deadline during Least Slack Time." << endl;
    }
    if (Pnum > 1)
    {
        if (Time >= Time2 && Time >= Time3)                                           //check all cpus for longest amount of time
            LTime = Time;
        else if (Time < Time2 && Time2 >= Time3)
            LTime = Time2;
        else
            LTime = Time3;
    }
    else
        LTime = Time;


    cout << "Least Slack Time took " << LTime << " seconds" << endl;


    return LTime;
}

int main ()
{
 
    int RRTime;
    int EDFTime;
    int LSTTime;

    int TaskNum;
    int ProcNum;

    char TaskRand;

    bool Check = 0;


    srand (time(NULL));

    cout << "How many tasks do you want to add?" << endl;
    cin >> TaskNum;

    while(!Check)
    {
      cout << "Do you want the tasks given random periods and exection times?(Y/N)" << endl;
      cin >> TaskRand;

      if(TaskRand == 'Y' || TaskRand == 'y')                                     //create random tasks
      {
        for(int i=0; i<TaskNum; i++)
        {
          TaskArr[i][0] = rand() % 10 + 1;
          TaskArr[i][1] = rand() % 10 + 1;
          while (TaskArr[i][1] > TaskArr[i][0])
          {
              TaskArr[i][1] = rand() % 10 + 1;
          }
        }
        Check = 1;
      }
      else if (TaskRand == 'N' || TaskRand == 'n')                               //allow user to create tasks
      {
        for(int i=0; i<TaskNum; i++)
        {
          cout << "Period for Task " << i+1 << endl;
          cin >> TaskArr[i][0];
          cout << "Execution Time for Task " << i+1 << endl;
          cin >> TaskArr[i][1];
        }
        Check = 1;
      }
      else
        cout << "Incorrect input" << endl;
    }
    for (int i = 0; i < TaskNum; i++)
    {
        cout << TaskArr[i][0] << " period" << endl;
        cout << TaskArr[i][1] << " exe time" << endl;

    }
    cout << "How many processors do you want to use?(Max 3)" << endl;
    cin >> ProcNum;

    RRTime = RoundRobin(TaskNum, ProcNum);
    EDFTime = EDF(TaskNum, ProcNum);
    LSTTime = LST(TaskNum, ProcNum);

    return 0;
}
