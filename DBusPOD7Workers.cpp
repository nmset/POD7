/* 
 * File:   DBusPOD7Workers.cpp
 * Author: Saleem Edah-Tally - nmset@yandex.com
 * License : GPL V2
 * 
 * Created on 10 décembre 2017, 14:12
 */

#include "DBusPOD7Workers.h"
#include <signal.h>
#include <thread>

using namespace std;

DBusPOD7Adaptor::DBusPOD7Adaptor(DBus::Connection &connection)
: DBus::ObjectAdaptor(connection, "/pedal/event")
{
    thread t(Entry);
    t.detach();
}

DBusPOD7Adaptor::~DBusPOD7Adaptor()
{
    DBus::default_dispatcher->leave();
}

void DBusPOD7Adaptor::Quit()
{
    // Handled in main.cpp
    raise(SIGTERM);
}

int DBusPOD7Adaptor::Entry()
{
    DBus::default_dispatcher->enter(); // IS BLOCKING
    return 0;
}
