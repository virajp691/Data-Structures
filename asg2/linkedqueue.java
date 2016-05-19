// $Id: linkedqueue.java,v 1.1 2014-02-04 13:48:24-08 vispatel - $
// USER
//    Viraj Patel (vispatel@ucsc.edu)

// NAME
//    linkedqueue - linkedqueue.java

// SYSNOPSIS
//    used with jroff.java

// DESCRIPTION Assignment 2
//    Sub-class for jroff.java used for assignment 2

import java.util.NoSuchElementException;

class linkedqueue <item_t> {

    private class node{
    item_t item;
    node link;
    }

    //
    // INVARIANT:  front == null && rear == null
    //          || front != null && rear != null
    // In the latter case, following links from the node pointed 
    // at by front will lead to the node pointed at by rear.
    //
    private node front = null;
    private node rear = null;

    public boolean empty (){
    return front == null;
    }

    public void insert (item_t any) {
    // STUB: Add code here to insert an item_t into the queue.
    node tmp = new node();
    tmp.item = any;
    tmp.link = null;
    if (rear == null) front = tmp;
    else rear.link = tmp;
    rear = tmp;
    }

    public item_t remove (){
    if (empty ()) throw new NoSuchElementException ();
    // STUB: Add code for remove here.
    item_t result = front.item;
    front = front.link;
    if (front == null) rear = null;
    return result;
    }

}
