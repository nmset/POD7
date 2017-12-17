/* 
 * File:   DBusPOD7Workers.h
 * Author: SET - nmset@yandex.com
 * License : GPL V2
 *
 * Created on 10 décembre 2017, 14:12
 */

#ifndef DBUSPOD7WORKERS_H
#define DBUSPOD7WORKERS_H

#include "pod7_adaptor.hpp"

/**
 * This class only enters the DBus loop in a thread.
 */
class DBusPOD7Adaptor : public pedal::event_adaptor,
public DBus::IntrospectableAdaptor,
public DBus::ObjectAdaptor
{
public:
    DBusPOD7Adaptor(DBus::Connection &connection);
    virtual ~DBusPOD7Adaptor();

    /**
     * Exits the application by sending SIGTERM.
     */
    void Quit() override;

    /**
     * Enters the DBus loop.
     * @return 
     */
    static int Entry();
private:

};

#endif /* DBUSPOD7WORKERS_H */

