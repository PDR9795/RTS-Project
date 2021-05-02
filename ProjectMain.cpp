//Programmer: Lucas Reynolds | Matthew Grey
//File: Main file
//Desc:


#include <iostream>
#include <time.h>
#include "RoundRobin.h"
#include "EDF.h"
#include "LST.h"
using namespace std;

double TaskArr[100][3];

int main ()
{
 
    double RRTime;
    double EDFTime;
    double LSTTime;

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
        }
        Check = 1;
      }
      else if (TaskRand == 'N' || TaskRand == 'n')                               //allow user to create tasks
      {
        for(int i=0; i<TaskNum; i++)
        {
          cout << "Period for Task " << i << endl;
          cin >> TaskArr[i][0];
          cout << "Deadline for Task " << i << endl;
          cin >> TaskArr[i][1];
        }
        Check = 1;
      }
      else
        cout << "Incorrect input" << endl;
    }

    cout << "How many processors do you want to use?(Max 3)" << endl;
    cin >> ProcNum;

    RRTime = RoundRobin(TaskNum, ProcNum);
    EDFTime = EDF(TaskNum, ProcNum);
    LSTTime = LST(TaskNum, ProcNum);

    if(RRTime >= EDFTime && RRTime >= LSTTime)
      cout << "Round Robin was the best scheduler" << endl;
    else if(RRTime < EDFTime && EDFTime >= LSTTime)
      cout << "Earliest Deadline First was the best scheduler" << endl;
    else
      cout << "Least Slack Time was the best scheduler" << endl;

    return 0;
}
