#include "myobject.h"
#include <string.h>
MyObject::MyObject()
{

}

static int find_string(const char* str, const char* substr)
{

}

void MyObject::db_connect(MyObject *sender, const char * sig, MyObject * receiver, const char *slt)
{
    int sig_idx = find_string(sender->meta.sig_names, sig);
    int slt_idx = find_string(receiver->meta.sig_names, slt);
    if (sig_idx == -1 || slt_idx == -1)
        perror("signal or slot not found!");
    else
    {
        Connection c = {receiver, slt_idx};
        sender->connections.insert(std::pair<int, Connection>(sig_idx, c));
    }
}

void MyObject::testSingal()
{
    my_emit sig1();
}

void MyObject::slot1()
{

}

void MetaObject::active(MyObject *sender, int idx)
{
    ConnectionMapIt it;
    std::pair<ConnectionMapIt, ConnectionMapIt> ret;
    ret = sender->connections.equal_range(idx);
    for (it = ret.first; it != ret.second; ++it)
    {
        Connection c = (*it).second;
        c.receiver->metacall(c.method);
    }
}

//moc_myobjcet.cpp
#include "myobject.h"
static const char sig_names[] = "sig1\n";
static const char slts_names[] = "slot1\n";
MetaObject MyObject::meta = {sig_names, slts_names};
void MyObject::sig1()
{
    MetaObject::active(this, 0);
}

void MyObject::metacall(int idx)
{
    switch (idx) {
    case 0:
        slot1();
        break;
    default:
        break;
    }
}

