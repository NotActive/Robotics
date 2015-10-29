#define MAX_FILESZ  5000   // maximum file size allowed

/* This program will create a data log file with :
   millseconds; counter
   for  a duration of 10 seconds with .5 second interval

   NOTE: Thinks to think about :
   1) need to have reference point along the data you log. e.g.: encoder; sonar value
   2) need to think how min and max number of data points.
     e.g.1:
     probe interval:  1 per 500 msec
           duration: 10 seconds maximum
           each data points size (including EOL): 15 bytes
           i.e. you will get only 20 data points, and need only 300 bytes
     you must think about will this be sufficent or too many.

     e.g.2:
     probe interval:  1 per 20 msec
           duration: 10 seconds maximum
           each data points size (including EOL): 9 bytes
           i.e. you will get only 500 data points
                actual file size needed = 4500 bytes
*/

task main()
{ int nbytes=0, dist=0;
	char sFileName[15];
  string str;
  short nFileSize = MAX_FILESZ;  // to restrict the file size

#if defined(NXT)
  TFileHandle fp;              // to store file handler
  TFileIOResult result;        // to store status
#else
  long fp;
#endif

  clearTimer(T1);
  time1(T1) = 0;

  // create a file name based on the current System time
  sprintf(sFileName,"log%d.txt", nSysTime/1000);

#if defined(NXT)
  Delete(sFileName, result);
  OpenWrite(fp, result, sFileName, nFileSize);
#else
	 fp = fileOpenWrite(sFileName);
#endif

	while (time1(T1)<10000 &&  nbytes < MAX_FILESZ)
  {
  	++dist;
    sprintf(str, "%6d;%d\r\n",  time1(T1), dist);
    // write the distance followed by end of line ascii code

#if defined(NXT)
    WriteText(fp, result, str);
#else
    fileWriteData(fp, str, strlen(str));
#endif
    nbytes = nbytes + sizeof(dist)+9;
    scrollText("%s", str);
    wait1Msec(500);
  }

#if defined(NXT)
	Close(fp, result);
#else
  fileClose(fp);
#endif

}
