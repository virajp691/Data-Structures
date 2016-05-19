// $Id: visitor.java,v 1.1 2014-02-16 16:07:32-08 vispatel - $

interface visitor <key_t, value_t> {
    public void visit (key_t key, value_t value);
}
