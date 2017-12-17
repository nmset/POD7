
/*
 *	This file was automatically generated by dbusxx-xml2cpp; DO NOT EDIT!
 */

#ifndef __dbusxx__pod7_adaptor_hpp__ADAPTOR_MARSHAL_H
#define __dbusxx__pod7_adaptor_hpp__ADAPTOR_MARSHAL_H

#include <dbus-c++/dbus.h>
#include <cassert>

namespace pedal {

class event_adaptor
: public ::DBus::InterfaceAdaptor
{
public:

    event_adaptor()
    : ::DBus::InterfaceAdaptor("pedal.event")
    {
        register_method(event_adaptor, Quit, _Quit_stub);
    }

    ::DBus::IntrospectedInterface *introspect() const 
    {
        static ::DBus::IntrospectedArgument Quit_args[] = 
        {
            { 0, "", false },
            { 0, 0, 0 }
        };
        static ::DBus::IntrospectedArgument OnPedalEvent_args[] = 
        {
            { "code", "i", false },
            { 0, 0, 0 }
        };
        static ::DBus::IntrospectedMethod event_adaptor_methods[] = 
        {
            { "Quit", Quit_args },
            { 0, 0 }
        };
        static ::DBus::IntrospectedMethod event_adaptor_signals[] = 
        {
            { "OnPedalEvent", OnPedalEvent_args },
            { 0, 0 }
        };
        static ::DBus::IntrospectedProperty event_adaptor_properties[] = 
        {
            { 0, 0, 0, 0 }
        };
        static ::DBus::IntrospectedInterface event_adaptor_interface = 
        {
            "pedal.event",
            event_adaptor_methods,
            event_adaptor_signals,
            event_adaptor_properties
        };
        return &event_adaptor_interface;
    }

public:

    /* properties exposed by this interface, use
     * property() and property(value) to get and set a particular property
     */

public:

    /* methods exported by this interface,
     * you will have to implement them in your ObjectAdaptor
     */
    virtual void Quit() = 0;

public:

    /* signal emitters for this interface
     */
    void OnPedalEvent(const int32_t& arg1)
    {
        ::DBus::SignalMessage sig("OnPedalEvent");
        ::DBus::MessageIter wi = sig.writer();
        wi << arg1;
        emit_signal(sig);
    }

private:

    /* unmarshalers (to unpack the DBus message before calling the actual interface method)
     */
    ::DBus::Message _Quit_stub(const ::DBus::CallMessage &call)
    {
        ::DBus::MessageIter ri = call.reader();

        Quit();
        ::DBus::ReturnMessage reply(call);
        return reply;
    }
};

} 
#endif //__dbusxx__pod7_adaptor_hpp__ADAPTOR_MARSHAL_H
