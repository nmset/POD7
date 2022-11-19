/* 
 * File:   globals.h
 * Author: Saleem Edah-Tally - nmset@yandex.com
 * License : GPL V2
 *
 * Created on 9 décembre 2017, 21:03
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <libintl.h>
#include <string>
using namespace std;

//https://www.labri.fr/perso/fleury/posts/programming/a-quick-gettext-tutorial.html
#define _(STRING) gettext(STRING)


#define _APPNAME_ "POD7" // Pedal events Over DBus
#define _APP_DESCRIPTION_ "Send pedal events over DBus"
#define _VERSION_ "2"
#define _AUTHOR_ "Saleem Edah-Tally - nmset@yandex.com"
#define _ABOUT_ string(_APPNAME_) + string(" - version ") + string(_VERSION_) \
        + string(" - ") + string(_APP_DESCRIPTION_) + _DOT_ \
        + string("\nAuthor : ") + string(_AUTHOR_) \
        + string("\nLicense : GPL v2")

#define _DOT_ "."
#define _SPACE_ " "
#define _COMMA_ ","
#define _COLON_ ":"

#endif /* GLOBALS_H */

