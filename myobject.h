#ifndef MYOBJECT_H
#define MYOBJECT_H
#include <map>
#define my_slots
#define my_signals protected
#define my_emit

class MyObject;
struct MetaObject
{
    const char* sig_names;
    const char* slts_names;
    static void active(MyObject* sender, int idx);
};

struct Connection
{
    MyObject* receiver;
    int method;
};

typedef std::multimap<int, Connection> ConnectionMap;
typedef std::multimap<int, Connection>::iterator ConnectionMapIt;

class MyObject
{
    static MetaObject meta;
    void metacall(int idx);
public:
    MyObject();
    static void db_connect(MyObject*, const char* , MyObject*, const char*);
    void testSingal();
public my_slots:
    void slot1();
my_signals:
    void sig1();
    friend class MetaObject;
private:
    ConnectionMap connections;
};

#endif // MYOBJECT_H
