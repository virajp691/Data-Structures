// $Id: queue.java,v 1.1 2014-02-16 16:07:32-08 vispatel - $

import java.util.Iterator;
import java.util.NoSuchElementException;

class queue <item_t> implements Iterable <item_t> {

    private class node {
    item_t item;
    node link;
    }
    private node head = null;
    private node tail = null;

    public boolean isempty () {
    if(head == null) return true;      
    return false;
    }

    public void insert (item_t newitem) {
    node tmp = new node();
    tmp.item = newitem;
    tmp.link = null;
    if (tail == null) head = tmp;
    else tail.link = tmp;
    tail = tmp;
    }

    public Iterator <item_t> iterator () {
    return new itor ();
    }

    class itor implements Iterator <item_t> {
    node next = head;
    public boolean hasNext () {
        return next != null;
    }
    public item_t next () {
        if (! hasNext ()) throw new NoSuchElementException ();
        item_t result = next.item;
        next = next.link;
        return result;
    }
    public void remove () {
        if(isempty()) throw new NoSuchElementException();
        head = head.link;
        if(head == null) tail = null;
         
    }
    }

}
