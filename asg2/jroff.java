// $Id: jroff.java,v 1.1 2014-02-04 13:48:24-08 vispatel - $
// USER
//    Viraj Patel (vispatel@ucsc.edu)

// NAME
//    jroff - jroff.java

// SYSNOPSIS
//    jroff [filename]

// DESCRIPTION Assignment 2
//    This program is a java version of groff

import java.io.*;
import java.util.Scanner;

import static java.lang.System.*;

class jroff{
    static final String STDIN_NAME = "-";
    static boolean newPage;
   
    static void scanfile (String filename, Scanner infile) {
    linkedqueue <String> wordqueue = new linkedqueue <String> ();
    out.printf ("STUB: filename = %s%n", filename);
    newPage = true;
    while (infile.hasNextLine()) {
        String line = infile.nextLine();
         
        if(line.isEmpty())
        out.printf("%n");
         
        String[] words = line.split ("\\s+");
         
        if (words.length > 0 && words[0].startsWith
               (commands.commandCharacter)) {
        try {                          
            commands.do_command (words);
            printparagraph(wordqueue);
            System.out.println();
               
        }catch (IllegalArgumentException error) {
            auxlib.warn (filename, words[0],
                 "invalid command");
        }
        }else {
        for(String word : words)
            wordqueue.insert(word);
            
        }
    }
    }

    public static void main (String[] args) {
    //linkedqueue <String> wordqueue = new linkedqueue <String> ();
    if (args.length == 0) {
        scanfile (STDIN_NAME, new Scanner (in));
    }else {
        for (String filename : args) {
        if (filename.equals (STDIN_NAME)) {
            scanfile (STDIN_NAME, new Scanner (in));
        }else {
            try {
            Scanner scan = new Scanner (new File (filename));
            scanfile (filename, scan);
            scan.close();
            }catch (IOException error) {
            auxlib.warn (error.getMessage());
            }
        }
        }
    }
    }

    public static void printparagraph(linkedqueue<String> wordqueue){
    StringBuffer buffer = new StringBuffer(commands.lineLength);
    int lineLength = commands.lineLength;
    int charCount = 0;
    int pageLength = commands.pageLength;
    int topMargin = commands.topMargin;
    int lineNumber = commands.lineNumber;
    int pageOffset = commands.pageOffset;
    int lineIndent = commands.lineIndent;
       
    while(!wordqueue.empty()){
        String s = wordqueue.remove();
        if(lineNumber >= pageLength) newPage = true;
        if (newPage){
        for(int i = 0; i < topMargin; i++){
            System.out.println();
        }
        out.printf("\f \n\n");
        newPage = false;
        }
        if(buffer.length() == 0){
        for(int i = 0; i < pageOffset; i++){
            buffer.append(" ");
        }
        for(int j = 0; j < lineIndent; j++){
            buffer.append(" ");
        }
        buffer.append(s);
        charCount += s.length();
        }
        else {
        // if ends with period TBA(? ! ; :)
        if(buffer.charAt(buffer.length()-1) == '.'){
            charCount += 2 + s.length();
            if(charCount > lineLength){
            out.println(buffer);
            lineNumber++;
            buffer.setLength(0);
            for(int i = 0; i < pageOffset; i++){
                buffer.append(" ");
            }
            for(int j = 0; j < lineIndent; j++){
                buffer.append(" ");
            }
            buffer.append(s);
            charCount = s.length();
            }else {
            buffer.append("  "+s);
            }
        }
        // if not an sentence ending character
        else {
            charCount += 1 + s.length();
            if(charCount > lineLength){
            out.println(buffer);
            lineNumber++;
            buffer.setLength(0);
            for(int i = 0; i < pageOffset; i++){
                buffer.append(" ");
            }
            for(int j = 0; j < lineIndent; j++){
                buffer.append(" ");
            }
            buffer.append(s);
            charCount = s.length();
            }else
            buffer.append(" "+s);
        }
        }
    } //end of while loop *queue is empty
    out.print(buffer);
    }
}
