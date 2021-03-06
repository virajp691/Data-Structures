//$Id: crpn.c,v 1.1 2014-01-27 09:55:42-08 vispatel - $
// Viraj Patel (vispatel@ucsc.edu)

// NAME
//    crpn - RPN Calculator

// SYNOPSIS
//    crpn

// DESCRIPTION
//    This program is a replication of the java version
//    of a Reverse Polish notation calculator.

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

int exit_status = EXIT_SUCCESS;
#define EMPTY (-1)
#define SIZE 16

typedef struct stack stack;
struct stack {
   int top;
   double numbers[SIZE];
};

void bad_operator (const char *oper) {
   fflush (NULL);
   fprintf (stderr, "oper=\"%s\"\n", oper);
   fflush (NULL);
   exit_status = EXIT_FAILURE;
}

void push (stack *the_stack, double number) {
//   printf ("the_stack=%p, top=%d, number=%.15g\n",
//            the_stack, the_stack->top, number);
   if ((the_stack->top) >= SIZE -1) {
     printf("%f: stack overflow\n", number);
   }else {
     the_stack->numbers[++the_stack->top] = number;
   }
}

void do_binop (stack *the_stack, char oper) {
  //printf ("the_stack=%p, top=%d, oper='%c'\n",
  //the_stack, the_stack->top, oper);

   if (the_stack->top < 1) {
      printf ("'%c': stack underflow", oper);
   }else {
      double right = the_stack->numbers[the_stack->top--];
      double left  = the_stack->numbers[the_stack->top--];
      switch (oper) {
      case '+': push (the_stack, left + right); break;
      case '-': push (the_stack, left - right); break;
      case '*': push (the_stack, left * right); break;
      case '/': push (the_stack, left / right); break;
      }
   }
}

void do_print (stack *the_stack) {
  //printf ("the_stack=%p, top=%d\n", the_stack, the_stack->top);
   if (the_stack->top == EMPTY) {
      printf ("stack is empty\n");
   }else {
      for (int pos = 0; pos <= the_stack->top; ++pos) {
        printf ("%f\n",the_stack->numbers[pos]);
      }
   }
}

void do_clear (stack *the_stack) {
  //printf ("the_stack=%p, top=%d\n", the_stack, the_stack->top);
   the_stack->top = EMPTY;
}

void do_operator (stack *the_stack, const char *oper) {
  // printf ("the_stack=%p, top=%d, oper=\"%s\"\n",
  //         the_stack, the_stack->top, oper);

     switch (*oper) {
     case '+': do_binop (the_stack, '+'); break;
     case '-': do_binop (the_stack, '-'); break;
     case '*': do_binop (the_stack, '*'); break;
     case '/': do_binop (the_stack, '/'); break;
     case ';': do_print (the_stack); break;
     case '@': do_clear (the_stack); break;
     default : bad_operator (oper); break;
     }
}


int main (int argc, char **argv) {
   if (argc != 1) {
      fprintf (stderr, "Usage: %s\n", basename (argv[0]));
      fflush (NULL);
      exit (EXIT_FAILURE);
   }
   stack the_stack;
   the_stack.top = EMPTY;
   char buffer[1024];
   for (;;) {
      int scanrc = scanf ("%1023s", buffer);
      if (scanrc == EOF) break;
      assert (scanrc == 1);
      if (buffer[0] == '#') {
         scanrc = scanf ("%1023[^\n]", buffer);
         continue;
      }
      char *endptr;
      double number = strtod (buffer, &endptr);
      if (*endptr == '\0') {
         push (&the_stack, number);
      }else if (buffer[1] != '\0') {
         bad_operator (buffer);
      }else {
         do_operator (&the_stack, buffer);
      }
   }
   return exit_status;
}

