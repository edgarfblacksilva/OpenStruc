#include "openStruc.h"
// the NumberOfErrorMesages variable is defined in openStruct.h
void OpenStruc::setErrorMassages()
{
    NumberOfErrorMesages = 23;
    errorMessage = new string [NumberOfErrorMesages];
#if defined (ENGLISH)
    errorMessage[0] = "    Integer Expected: Number of ";
    errorMessage[1] = "joints at line ";
    errorMessage[2] = "elements at line ";
    errorMessage[3] = "Please, define materials properties before section types\n";
    errorMessage[4] = "Please, define the number of nodes before setting the coordinates\n";
    errorMessage[5] = "Please, define the number of supported nodes before setting the node`s constraints\n";
    errorMessage[6] = "Please, define the number of elements before setting the elements`s incidences\n";
    errorMessage[7] = "Please, define the number of materials before defining its properties\n";
    errorMessage[8] = "Please, define the number of section types before defining them\n";
    errorMessage[9] = "Please, define the number of number of elements and section types before defining elements\n";
    errorMessage[10] = "Non-existing section type at line ";
    errorMessage[11] = "Command not recognized at line ";
    errorMessage[12] = "Integer number expected at line  ";
    errorMessage[13] = "Floating point number Expected at line  ";
    errorMessage[14] = "Integer number out of range at line  ";
    errorMessage[15] = "Number of load cases must be one or more.";
    errorMessage[16] = "Incorrect Structural Type at line ";
    errorMessage[17] = "Unknown element load type at line ";
    errorMessage[18] = "Load direction not allowed in this structural type. Problem in line ";
    errorMessage[19] = "Length and position of distributed load (la + lb) larger than element length.";
    errorMessage[20] = "Incorrect temperature gradient for this type of structure in line ";
    errorMessage[21] = "No list was found at line ";
    errorMessage[22] = "Some Elements require secType. Look in line ";
    
//    errorMessage[] = "";
#elif defined (ESPANOL)
    errorMessage[0] = "    Esperado un Numero entero: Numero de ";
    errorMessage[1] = "juntas, en la linea ";
    errorMessage[2] = "elementos, en la linea ";
    errorMessage[3] = "Por favor, defina las propiedades de los materials anted de definit las secciones typos\n";
    errorMessage[4] = "Por favor, defina el numero de nodos antes de definir sus coordenadas\n";
    errorMessage[5] = "Por favor, defina el numero de nodos restringidos antes de definir sus restricciones\n";
    errorMessage[6] = "Por favor, defina el numero de miembros antes de definir las incidencias\n";
    errorMessage[7] = "Por favor, defina el numero de materiales antes de definir sus propiedades\n";
    errorMessage[8] = "Por favor, defina el numero de tipos de secciones antes de definirlos\n";
    errorMessage[9] = "Por favor, defina el numero de numero de miembros y tipos de secciones antes de definir los elementos\n";
    errorMessage[10] = "Tipo de Secccion no existente en linea ";
    errorMessage[11] = "Comando no reconocido en la lina ";
    errorMessage[12] = "Esperado un numero entero en la linea  ";
    errorMessage[13] = "Esperado un numero real en la lina  ";
    errorMessage[14] = "Numero entero fuera de rango en la linea  ";
    errorMessage[15] = "Numero de casos de carga debe ser uno o mas.";
    errorMessage[16] = "Tipo estructural incorrecto en la linea ";
    errorMessage[17] = "Tipo de elemento desconocido en la linea ";
    errorMessage[18] = "Direccion de Carga no permitida en este tipo estructural . Problema en linea ";
    errorMessage[19] = "Longitud y posicion de carga distribuida (la + lb) mayor que la longitud del elemento";
    errorMessage[20] = "Gradiente de temperatura incorrecto para este tipo de estructura en la linea ";    
    errorMessage[21] = "Lista no encontrada en la linea ";
    errorMessage[22] = "Algunos elementos requieren definir secType. Revise linea ";
    
#endif    
} // end of OpenStruc::setErrorMasages()//
