// $Id: jxref.java,v 1.3 2014-11-17 20:26:50-08 - - $
// USER:
//    Viraj Patel (vispatel@ucsc.edu)
// NAME
//    JXREF
// SYNOPSIS
//    jxref [-df] [filename...]

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class jxref {
    static final String STDIN_NAME = "-";
    static boolean debugFormat;
    static boolean ignoreCase;

    static class printer implements visitor <String, queue <Integer>> {
        public void visit (String key, queue <Integer> value) {
            out.printf("%s %d\n",key,value);
        }
    }

    static void xref_file (String filename, Scanner scan) {
        treemap <String, queue <Integer>> map =
            new treemap <String, queue <Integer>> ();
        for (int linenr = 1; scan.hasNextLine (); ++linenr) {
            for (String word: scan.nextLine().split ("\\W+")) {         
                if (ignoreCase)
                    word.toLowerCase();
                    queue<Integer> queue;
                if(map.get(word)!= null){
                queue = map.get(word);
                queue.insert(linenr);
                }else {
                 queue = new queue<Integer>();
                    queue.insert(linenr);
                    map.put(word, queue);
                }

                if (word.matches ("^\\d*$")) continue;
                out.printf ("%s: %d: %s%n", filename, linenr, word);
            }
        }
        visitor <String, queue <Integer>> print_fn = new printer ();
        if(debugFormat) map.debug_dump();
        else map.do_visit (print_fn);

    }

    public static void main (String[] args) {
        if (args.length == 0) {
            xref_file (STDIN_NAME, new Scanner (in));
        }else {
            for (int argi = 0; argi < args.length; ++argi) {
                String filename = args[argi];
                if(args[0].charAt(0) == '-'){
                    getOptions(filename);
                }            
                else if (filename.equals (STDIN_NAME)) {
                    xref_file (STDIN_NAME, new Scanner (in));
                }else {
                    try {
            Scanner scan = new Scanner (new File (filename));
            xref_file (filename, scan);
            scan.close ();
            }catch (IOException error) {
            auxlib.warn (error.getMessage ());
            }
        }
        }
    }
    auxlib.exit ();
    }

    static void getOptions(String arg){
    for(int i = 1; i < arg.length(); i++){
        char opt = arg.charAt(i);
        if(opt == 'd')
        debugFormat = true;
        else if(opt == 'f')
        ignoreCase = true;
        else{
        auxlib.warn("Bad Option"+opt);
        }
    }
    }
}
