#include "win32util.h"

unsigned long long fileTimeToInt64(const FILETIME & ft) {
    unsigned long long time = (((unsigned long long)(ft.dwHighDateTime))<<32)
                               |(unsigned long long)ft.dwLowDateTime;
    return time;
}

void initializeCPUCounters(HCOUNTER* processorCounters,HANDLE event,PDH_HQUERY* query)
{
   PDH_STATUS status = ERROR_SUCCESS;
   LPTSTR counterList = NULL;
   DWORD counterListSize = 0;
   LPTSTR instanceList = NULL;
   DWORD instanceListSize = 0;
   LPTSTR thisInstance = NULL;

   event = CreateEvent(NULL, FALSE, FALSE, TEXT("MyEvent"));

   // Determine the required buffer size for the data.
   status = PdhEnumObjectItems (NULL,                   // real time source
                                   NULL,                   // local machine
                                   TEXT("Processor"),        // object to enumerate
                                   counterList,    // pass NULL and 0
                                   &counterListSize,     // to get length required
                                   instanceList,   // buffer size
                                   &instanceListSize,    //
                                   PERF_DETAIL_WIZARD,     // counter detail level
                                   0);
   if(status = PDH_MORE_DATA)
   {
       counterList = (LPTSTR)malloc(counterListSize * sizeof(TCHAR));
       instanceList = (LPTSTR)malloc (instanceListSize * sizeof(TCHAR));

       // Determine the required buffer size for the data.
       status = PdhEnumObjectItems (NULL,                   // real time source
                                       NULL,                   // local machine
                                       TEXT("Processor"),        // object to enumerate
                                       counterList,    // pass NULL and 0
                                       &counterListSize,     // to get length required
                                       instanceList,   // buffer size
                                       &instanceListSize,    //
                                       PERF_DETAIL_WIZARD,     // counter detail level
                                       0);

       int numberOfCounters = 0;
       if(status == ERROR_SUCCESS)
       {
           _tprintf(_TEXT("Enumerating Processor Counters ... "));

           // get the total number of processor counters
           for(thisInstance = instanceList;
               *thisInstance != 0;  thisInstance += lstrlen(thisInstance) + 1)
           {
               if(_tcscmp(thisInstance, TEXT("_Total")))
                   numberOfCounters++;
           }

           processorCounters = new HCOUNTER[numberOfCounters];

           status = PdhOpenQuery(NULL, 0, query);

           for(int n = 0; n < numberOfCounters; n++)
           {
               TCHAR counterPath[255];
               _stprintf_s(counterPath, 255, TEXT("\\Processor(%d)\\%% Processor Time"), n);
               status = PdhAddCounter (query, counterPath, n, & processorCounters[n]);
               if(status != ERROR_SUCCESS){\
                   break;
               }
           }

           status = PdhCollectQueryData(query);
       }
   }
}
