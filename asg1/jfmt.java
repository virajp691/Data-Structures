// Viraj Patel (vispatel@ucsc.edu)
// $Id: jfmt.java,v 1.2 2013-09-24 14:38:16-07 - - $
//
// NAME
//   jfmt -simple java text formatter
// SYNOPSIS
//   jfmt [-width] [filename...]
// DESCRIPTION
// Starter code for the jfmt utility.  This program is similar
// to the example code jcat.java, which iterates over all of its
// input files, except that this program shows how to use
// String.split to extract non-whitespace sequences of characters
// from each line.
//

import java.io.*;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import static java.lang.System.*;

class jfmt {
   // Static variables keeping the general status of the program.
   public static final String JAR_NAME = get_jarname();
   public static final int EXIT_SUCCESS = 0;
   public static final int EXIT_FAILURE = 1;
   public static int exit_status = EXIT_SUCCESS;
    static int lineLength;

   // A basename is the final component of a pathname.
   // If a java program is run from a jar, the classpath is the
   // pathname of the jar.
   static String get_jarname() {
      String jarpath = getProperty ("java.class.path");
      int lastslash = jarpath.lastIndexOf ('/');
      if (lastslash < 0) return jarpath;
      return jarpath.substring (lastslash + 1);
   }


   // Formats a single file.
   static void format (Scanner infile) {
      List<String> words = new LinkedList<String>();
      // Read each line from the opened file, one after the other.
      // Stop the loop at end of file.
      while(infile.hasNextLine()) {
         String line = infile.nextLine();

         // Split the line into words around white space and iterate
         // over the words.
         for (String word: line.split ("\\s+")) {

            // Skip an empty word if such is found.
            if (word.length() == 0) continue;
            // Append the word to the end of the linked list.
            words.add (word);

         }
      }
      print_paragraph(words);
   }

    public static void print_paragraph(List<String> words) {
        out.println();
        int charCount = 0;
        for(String word : words) {
            if(charCount == 0) {
                out.printf("%s",word);
                charCount = word.length();
            }else {
                charCount += 1 + word.length();
                if(charCount > lineLength) {
                    out.printf("%n%s",word);
                    charCount = word.length();
                }else {
                    out.printf(" %s",word);
                }
            }
        }
        if(charCount > 0) out.println();
    }


   // Main function scans arguments and opens/closes files.
   public static void main (String[] args) {
      if (args.length == 0) {
         // There are no filenames given on the command line.
         out.printf ("FILE: -%n");
         format (new Scanner (in));
      }else {
         // Iterate over each filename given on the command line.
         for (int argix = 0; argix < args.length; ++argix) {
            String filename = args[argix];
            if (args[argix].charAt(0) == '-') {
               lineLength = Integer.parseInt(args[argix].substring(1));
            }else {
               // Open the file and read it, or error out.
               try {
                  Scanner infile = new Scanner (new File (filename));
                  out.printf ("FILE: %s%n", filename);
                  format (infile);
                  infile.close();
               }catch (IOException error) {
                  exit_status = EXIT_FAILURE;
                  err.printf ("%s: %s%n", JAR_NAME,
                              error.getMessage());
               }
            }
         }
      }
      exit (exit_status);
   }

}
