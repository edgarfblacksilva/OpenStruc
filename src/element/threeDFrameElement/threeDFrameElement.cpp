#include "threeDFrameElement.h"

ThreeDFrameElement::ThreeDFrameElement(const string &filename,
                                             intPos &DofPerElement,
                                       const intPos &siae) :  Element(filename)                                             
{
    secctionsInsideAnElement = siae;
    DofPerElement=dofPerElement;    
    totalNumberOfForces = (secctionsInsideAnElement+2)*(dofPerElement/2);
    forcesInElement = new real [totalNumberOfForces+1];
    sizeOfElementForcesRecord = (totalNumberOfForces+1)*sizeof(real);
    sizeOfElementRecord=static_cast<intPos>(sizeof(*this));
  #if defined (ENGLISH)
    elementMessages[0] = "    Data of the Structure's Elements\n"
                         "    Element #  Joint I Joint J  Length       Area       Ixx        Iyy        Izz   Cixy   Cjxy    Cxy  Cixz   Cjxz    Cxz  Cn=Ct  Mat. Type\n"
                         ;
    elementMessages[1] = "    LOADS AND TEMPERATURE VARIATIONS IN MEMBERS (local oXYZ system of reference).\n"
                         ;
    elementMessages[2] = "    PRIMARY FORCES AT ELEMENTS ENDS\n"
                         "    Element # Node             N           Vy           Vz            T           My           Mz\n"
                         ;
    
    elementMessages[3] = "    FORCES AT ELEMENTS SECTIONS\n"
                         "    Element  Node       x          N         Vy         Vz          T         My         Mz\n"
                         ;
                       
    elementMessages[4] = "\n    FORCES IN ELEMENT SECTIONS FOR THE LOADS HYPOTESTS\n"
                         ;
    elementMessages[5] = "    Element       x        Hip           N          Vy          Vz           T          My          Mz\n"
                         ;
  #elif defined (ESPANOL)
    elementMessages[0] = "    Datos de los elmentos de la estructura\n"
                         "Elemento # Junta I Junta J Longitud      Area       Ixx        Iyy        Izz   Cixy   Cjxy    Cxy  Cixz   Cjxz    Cxz  Cn=Ct  Material #\n"
                         ;
    elementMessages[1] = "    CARGAS Y VARIACIONES DE TEMPERATURA EN LOS MIEMBROS (referidas al systema local oxyz).\n"
                         ;
    elementMessages[2] = "    FUERZAS PRIMARIAS EN LOS EXTREMOS DE LOS ELEMENTOS\n"
                         "    Elemento # Node             N           Vy           Vz            T           My           Mz\n"
                         ;
    elementMessages[3] = "    FUERZAS EN LAS SECCIONES DE LOS MIEMBROS\n"
                         "    Miembro Junta       x          N         Vy         Vz          T         My         Mz\n"
                         ;
    elementMessages[4] = "\n    FUERZAS EN LAS SECCIONES DE LOS MIEMBROS PARA LAS HIPOTESIS DE SOLICITACIONES\n"
                         ;
    elementMessages[5] = "    Miembro       x        Hip          N           Vy          Vz           T          My          Mz\n"
                         ;
  #endif    
} // end of ThreeDFrameElement::ThreeDFrameElement() constructor //

ThreeDFrameElement::ThreeDFrameElement(const string &filename) : Element (filename) 
{
    sizeOfElementRecord=static_cast<intPos>(sizeof(*this));
} // end of ThreeDFrameElement::ThreeDFrameElement() constructor //
