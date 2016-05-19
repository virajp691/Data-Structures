// $Id: l8stat.c,v 1.17 2014-03-04 22:38:27-08 - - $
// USER
//    Viraj Patel (Vispatel@ucsc.edu)

// NAME
//    l8stat - stat a list of files

// SYNOPSIS
//    l8stat [filename...]

#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int exit_status = EXIT_SUCCESS;
char *program_name = NULL;
#define STD_DIR "."

void scan_file (char *filename) {
  //Create a variable for the structure for file stats
  struct stat sb;

  // Run lstat and store struct into 'sb' also check if fail
  if (lstat(filename, &sb) == -1) {
    exit_status = EXIT_FAILURE;
    fflush (NULL);
    fprintf (stderr, "Could not lstat file %s\n", filename);
    fflush (NULL);
  }else {
    // If lstat was sucessful run all this
    // Print the basic information about the file
    printf ("Filename: %s\n",filename);
    printf ("File Size:         %lld bytes\n",
            (long long)sb.st_size);
    printf ("File Mode:        %lo(octal)\n",
            (unsigned long) sb.st_mode);

    // Check if it is a systemlink and print the req info
    char sysbuff[128];
    if (readlink(filename, sysbuff, sizeof (sysbuff))!= -1) {
      printf ("System Link Value: %s\n", sysbuff);
    }

    // Store the timestamp into a usable time structure
    struct tm *filetime = localtime (&sb.st_mtime);
    time_t currtime;
    time (&currtime); // Get/stores current time
    char tbuf[128]; // buffer will become time string

    if (currtime - sb.st_mtime > 180){
    // Run strftime to store the timestamp into a string
    if (strftime (tbuf, sizeof (tbuf), "%b %e %R", filetime)==0){
      exit_status = EXIT_FAILURE;
      fflush(NULL);
      fprintf (stderr, "Failed to convert time\n");
      fflush(NULL);
    }
    }else {
      if (strftime (tbuf, sizeof (tbuf), "%b %e  %Y", filetime)==0){
        exit_status = EXIT_FAILURE;
        fflush(NULL);
      }
    }
    // print timestamp
    printf ("Last Modifed: %s\n", tbuf);
  }

  
}

int main (int argc, char **argv) {
  if (argc == 1) {
    // Use current directory
  }else {
    for (int argi = 1; argi < argc; ++argi) {
      char *filename = argv[argi];
      FILE *input = fopen (filename, "r");
      if (input != NULL) {
        scan_file (filename);
        fclose (input);
      }else {
        exit_status = EXIT_FAILURE;
        fflush (NULL);
        fprintf (stderr, "%s FILE DOES NOT EXIT\n", filename);
        fflush (NULL);
      }
    }
  }

  return exit_status;
}
