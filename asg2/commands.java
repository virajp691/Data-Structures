// $Id: commands.java,v 1.1 2014-02-04 13:48:24-08 vispatel - $
// USER
//    Viraj Patel (vispatel@ucsc.edu)

// NAME
//    commands - commands.java

// SYSNOPSIS
//    used with jroff.java

// DESCRIPTION Assignment 2
//    Sub-class for jroff.java for assignment 2

import java.util.HashMap;
import static java.lang.System.*;

class commands {
    static int pageLength = 60;
    static int topMargin = 6;
    static int lineNumber = 1;
    static int lineLength = 65;
    static int pageOffset = 10;
    static int lineIndent = 0;
    static String commandCharacter = ".";
   
    private static void command_00 (String[] words) {
    // Executing a comment does nothing.
    }

    private static void command_bp (String[] words) {
    // Enable top-of-page mode  BEGIN PAGE
    }

    private static void command_br (String[] words) {
    // Dumps paragraph
    out.print("\n");
    }

    private static void command_cc (String[] words) {
    if(words[1] == null)
        System.out.println("Invalid Command");
    else{
        commandCharacter = words[1];
    }
    }

    private static void command_in (String[] words) {
    // Add n spaces in front of every following line of output
    lineIndent = Integer.parseInt(words[1]);
    command_br(words);
    }

    private static void command_ll (String[] words) {
    if(words[1] == null || Integer.parseInt(words[1]) <= 0)
        System.out.println("Invalid Command!");
    else {
        lineLength = Integer.parseInt(words[1]);
    }
    }

    private static void command_mt (String[] words) {
    // Sets the height of the top margin to words[1]
    if(words[1] == null || Integer.parseInt(words[1]) <= 0)
        System.out.println("Invalid Command!");
    else {
        topMargin = Integer.parseInt(words[1]);
    }
    }

    private static void command_pl (String[] words) {
    // Set pageLength to the number of lines available per page.
    if(words[1] == null || Integer.parseInt(words[1]) <= 0)
        System.out.println("Invalid Command!");
    else {
        pageLength = Integer.parseInt(words[1]);
    }
    }

    private static void command_po (String[] words) {
    //set pageOffset to this number of spaces
    if(words[1] == null || Integer.parseInt(words[1]) <= 0)
        System.out.println("Invalid Command!");
    else {
        pageOffset = Integer.parseInt(words[1]);
    }
    }

    private static void command_sp (String[] words) {
    //End Paragraph
    if(words.length == 1) out.println();
    else {
        for(int i = 0; i < Integer.parseInt(words[1]); i++){
        System.out.println();
        }
    }
    }

    private static void STUB (String[] words) {
    out.printf ("%s: STUB: %s",
            auxlib.PROGNAME, auxlib.caller());
    for (String word: words) out.printf (" %s", word);
    out.printf ("%n");
    }

    public static void do_command (String[] words) {
    final String c = commandCharacter;
    switch (words[0].substring(1)) {
    case "\\\"": command_00 (words); break;
    case "bp"  : command_bp (words); break;
    case "br"  : command_br (words); break;
    case "cc"  : command_cc (words); break;
    case "in"  : command_in (words); break;
    case "ll"  : command_ll (words); break;
    case "mt"  : command_mt (words); break;
    case "pl"  : command_pl (words); break;
    case "po"  : command_po (words); break;
    case "sp"  : command_sp (words); break;
    default     : throw new IllegalArgumentException (words[0]);
    }
    }

}
