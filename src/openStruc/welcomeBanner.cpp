#include "openStruc.h"

void OpenStruc::welcomeBanner(ostream &myout) 
{
    auto *welcomeMessage = new string [8];

#if defined (ENGLISH)
    welcomeMessage[0] = "    OpenStruc      Version: ";
    welcomeMessage[1] = "    Last Modified: Tue 05 Aug 2025 11:46:31 AM CST\n";
    welcomeMessage[2] = "    System: Linux\n\n";
    welcomeMessage[3] = "    Copyright (C) 2024\n";
    welcomeMessage[4] = "    Edgar F. Black\n\n";
    welcomeMessage[5] = "    Send comments and requests for help to:\n";
    welcomeMessage[6] = "    edgarfblack@gmail.com\n\n";
    welcomeMessage[7] = "    POL: ObjectScan - Version ";
#elif defined (ESPANOL)
    welcomeMessage[0] = "    OpenStruc  Versión: ";
    welcomeMessage[1] = "    Ultima Modificación: Martes 05 Aug 2025 11:46:31 AM CST\n";
    welcomeMessage[2] = "    Systema: Linux\n\n";
    welcomeMessage[3] = "    Copyright (C) 2024\n";
    welcomeMessage[4] = "    Edgar F. Black\n\n";
    welcomeMessage[5] = "    Enviar comentarios y solicitudes de ayuda a:\n";
    welcomeMessage[6] = "    edgarfblack@gmail.com\n\n";
    welcomeMessage[7] = "    POL: ObjectScan - Versión ";
#endif    

    myout << welcomeMessage[0] << getOpenStrucVersion();
    myout << welcomeMessage[1];
    myout << welcomeMessage[2];
    myout << welcomeMessage[3];
    myout << welcomeMessage[4];
    myout << welcomeMessage[5];
    myout << welcomeMessage[6];
    myout << welcomeMessage[7] << getObjectScanVersion() << "\n\n";

    delete [] welcomeMessage;
} // end of OpenStruc::welcomeBanner() //
