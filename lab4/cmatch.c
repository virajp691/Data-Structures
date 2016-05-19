// $Id: cmatch.c,v 1.9 2014-02-10 09:58:19-08 vispatel - $
// USER
//    Viraj Patel (vispatel@ucsc.edu)

// NAME
//    cmatch - print matching lines from files

// SYNOPSIS
//    cmatch [-iln] string [filename...]

// DESCRIPTION
// cmatch searches the named input ﬁles for lines
// containing the string. By default the matching
// lines are printed. If more than one ﬁle is
// speciﬁed, lines of output are preceded by the
// ﬁlename.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

int exit_status = EXIT_SUCCESS;
char *program_name = NULL;
#define STDIN_NAME "-"

typedef struct options {
  bool ignore_case;
  bool filenames_only;
  bool number_lines;
}options;

void scan_options (int argc, char **argv, options *opts) {
  opts->ignore_case = false;
  opts->filenames_only = false;
  opts->number_lines = false;
  opterr = false;

  for(;;) {
    int opt = getopt (argc, argv, "ilm");
    if (opt == -1) break;
    switch (opt) {
    case 'i':
      opts->ignore_case = true;
      break;
    case 'l':
      opts->filenames_only = true;
      break;
    case 'm':
      opts->number_lines = true;
      break;
    default:
      exit_status = EXIT_FAILURE;
      fflush(NULL);
      fprintf(stderr, "%s: -%c: invalid option\n",
	      program_name, optopt);
      break;
    }
  }
}

void match (FILE *input, char *filename, char *string) {
  char buffer[1024];
  printf("FILE %s:\n",filename);
  for (int linenr = 1;; linenr++){
    char *buf = fgets (buffer, sizeof buffer, input);
    if (buf == NULL) break;
    char *ret = strstr(buf, string);
    printf ("Matched: %s\n", ret);
  }
}

int main(int argc, char **argv) {
  program_name = basename(argv[0]);
  options opts;
  char* string;
  if(argc == 1){
    match (stdin, STDIN_NAME, string);
  }else {
    for(int argi = 1; argi < argc; ++argi) {
      char *filename  = argv[argi];
      if (filename[0] == '-'){
        scan_options(argc, argv, &opts);
      }
      else if(strcmp (filename, STDIN_NAME) == 0){
        match (stdin, STDIN_NAME, string);
      }else {
        FILE *input = fopen (filename, "r");
        char *string;
        if(input != NULL) {
          match (input, filename, string);
          fclose (input);
        }else {
          exit_status = EXIT_FAILURE;
          fflush(NULL);
          fprintf (stderr, "%s: %s: %s\n", program_name,
                   filename, strerror(errno));
          fflush(NULL);
        }
      }
    }
  }
  return exit_status;
}
