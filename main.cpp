/* 
 * File:   main.cpp
 * Author: Saleem Edah-Tally - nmset@yandex.com
 * License : GPL V2
 *
 * Created on 9 décembre 2017, 19:04
 */

#include "globals.h"
#include "DBusPOD7Workers.h"
#include <iostream>
#include <signal.h>
#include <sstream>
#include <boost/program_options.hpp>
#include <hidapi/hidapi.h>

using namespace std;
namespace po = boost::program_options;

string g_deviceFile = "";
bool g_verbose = false;
hid_device * g_device;
DBus::BusDispatcher g_dispatcher;

/*
 * For USB HIDRAW pedals only.
 * Tested with the 
 * - VEC USB foot pedal
 * - Olympus RS-28 foot pedal
 */

void signalhandler(int sn)
{
    if (g_verbose)
        cout << "_(Application signaled to exit.)" << endl;
    hid_close(g_device);
    hid_exit();
    exit(0);
}

/**
 * List available hidraw devices
 * @return 
 */
bool ListDevices()
{
    if (hid_init() != 0)
    {
        cout << _("Can't initialize HID library.") << endl;
        return false;
    }
    hid_device_info * devices;
    devices = hid_enumerate(0, 0);
    if (devices == NULL)
    {
        if (g_verbose)
            cout << _("No hidraw devices found.") << endl;
    }
    else
    {
        // ex : /dev/hidraw0 : Logitech, USB Optical Mouse, 46d:c05b
        while (devices != NULL)
        {
            // https://stackoverflow.com/questions/20034297/decimal-to-hex-conversion-c-built-in-function
            stringstream ssVendor, ssProduct;
            ssVendor << hex << devices->vendor_id;
            string vendor(ssVendor.str());
            ssProduct << hex << devices->product_id;
            string product(ssProduct.str());
            cout << devices->path << _SPACE_ << _COLON_ << _SPACE_;
            wcout << devices->manufacturer_string << _COMMA_ << _SPACE_
                    << devices->product_string << _COMMA_ << _SPACE_
                    << vendor.c_str() << _COLON_ << product.c_str() << endl;
            devices = devices->next;
        }
    }
    hid_free_enumeration(devices);
    hid_exit();
    return true;
}

/**
 * Parse command line
 * @param argc
 * @param argv
 * @return 
 */
bool ManageParams(int argc, char** argv)
{
    try
    {
        po::options_description desc(_ABOUT_);
        desc.add_options()
                ("help,h", _("Print help messages."))
        /*
         * Use an udev rule to identify the hidraw device  :
         * Ex : 
         * cat /etc/udev/rules.d/99-vec.rules
         * KERNEL=="hidraw[0-9]*", SYMLINK+="hidraw-vec", ATTRS{idVendor}=="05f3", ATTRS{idProduct}=="00ff",  MODE="0660", GROUP="transcript"
         * Using /dev/hidraw-vec better control better control.
         */
                ("device,d", po::value<string>(&g_deviceFile), _("hidraw pedal device file (/dev/<file>)."))
                ("list,l", _("List hidraw devices."))
                ("verbose,v", _("Show some messages on stdout, namely, signaled pedal codes."));

        po::variables_map vm;
        po::variables_map vmc;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);
            if (vm.count("help"))
            {
                cout << desc << endl;
                return false;
            }
            po::notify(vm);
            if (vm.count("verbose"))
            {
                g_verbose = true;
            }
            if (vm.count("list"))
            {
                ListDevices();
                return false;
            }
        }
        catch (po::error& eb)
        {
            cerr << _("Error : ") << eb.what() << endl;
            return false;
        }
    }
    catch (exception& e)
    {
        cerr << _("Error : ") << e.what() << endl;
        return false;
    }

    return true;
}

/*
 * 
 */
int main(int argc, char** argv)
{
    setlocale (LC_ALL, "");
    bindtextdomain (_APPNAME_, "/usr/local/share/locale"); // containing fr/LC_MESSAGES/
    textdomain (_APPNAME_);
    
    if (!ManageParams(argc, argv))
        return 0;
    signal(SIGINT, signalhandler);
    signal(SIGTERM, signalhandler);
    if (hid_init() != 0)
    {
        cout << _("Can't initialize HID library.") << endl;
        return 0;
    }
    g_device = hid_open_path(g_deviceFile.c_str());
    if (!g_device)
    {
        cout << _("Can't open ") << g_device << _DOT_ << endl;
        hid_exit();
        return 0;
    }
    // We want to always listen to pedal events
    hid_set_nonblocking(g_device, 0);
    const unsigned short bsz = 256;
    unsigned char b[bsz];
    unsigned short code = 0;
    int nbRead = 0;

    DBus::_init_threading();
    DBus::default_dispatcher = &g_dispatcher;
    DBus::Connection bus = DBus::Connection::SessionBus();
    bus.request_name("pedal.event");
    // The DBus adaptor will send messages over the bus
    DBusPOD7Adaptor adaptor(bus);

    while (true)
    {
        nbRead = hid_read(g_device, b, bsz);
        if (nbRead == -1) break; // cable pulled off
        for (unsigned short i = 0; i < nbRead; i++)
        {
            if (g_verbose)
                cout << (unsigned short) b[i] << _SPACE_;
            code += (unsigned short) b[i];
        }
        if (g_verbose)
            cout << endl;
        // Post the event code
        adaptor.OnPedalEvent(code);
        if (g_verbose)
            cout << code << endl;
        code = 0;
    }

    if (g_verbose)
        cout << _("Application exit.") << endl;
    hid_close(g_device);
    hid_exit();
    return 0;
}

