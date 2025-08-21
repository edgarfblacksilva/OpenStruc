# include "gridJoint.h"

GridJoint::GridJoint(const string &filename,                            
                           intPos &DofPerJoint, 
                           intPos &CoordPerJoint) : Joint(filename)
                           
{    
    DofPerJoint = dofPerJoint;
    CoordPerJoint = coordPerJoint;

    sizeOfJointRecord          = static_cast<intPos>(sizeof(*this));
    sizeOfJointReactionsRecord = sizeof(real)*dofPerJoint;
    jointReactionsRecord       = new real [dofPerJoint];
  #if defined (ENGLISH)
    jointMessages [0] = "    Data of the Structure's Nodes\n"               
                       "    Joint #         X         Y"
                       "  Rdz Rrx Rry        "
                       "Kdz        Krx        Kry\n"
                       ;
    jointMessages [1] = "    LOADS APPLIED TO THE NODES\n"
                        "    Node         Fz         Mx         My\n"
                        ;
                        
    jointMessages [2] = "    NODES INITIAL DISPLACEMENTS\n"
                        "    Node         Dz         Rx         Ry\n"
                        ;
                        
    jointMessages [3] = "    NODES DISPLACEMENTS\n"
                        "    Node              Dz              Rx              Ry\n"
                        ;
                        
    jointMessages [4] = "    LOADS AND/OR REACTIONS AT NODES\n"
                        "    Node          FZ          MX          MY\n"
                        ;
    jointMessages [5] = "\n    REACTIONS AT NODES FOR THE LOADS HYPOTESYS\n"
                        "    Node    Hip          Fz          Mx          My\n"
                        ;
  #elif defined (ESPANOL)
    jointMessages [0] = "    Datos de las juntas de las estructura\n"    
                        "    Junta  # Rdz Rrx Rry"
                        "        X         Y         "
                        "Kdz        Krx        Kry\n";
    jointMessages [1] = "    CARGAS APLICADAS EN LAS JUNTAS\n"
                        "    Junta         Fz        Mx         My\n"
                        ;
                        
    jointMessages [2] = "    DESPLAZAMIENTOS INICIALES EN LAS JUNTAS\n"
                        "    Junta        Dz         Rx         Ry\n"
                        ;
                        
    jointMessages [3] = "    DESPLAZAMIENTO DE LAS JUNTAS\n"
                        "    Junta              Dz              Rx              Ry\n"
                        ;
                        
    jointMessages [4] = "    CARGAS Y/O REACCIONES EN LAS JUNTAS\n"
                        "    Junta         FZ          MX          MY\n"
                        ;
    jointMessages [5] = "\n    REACCIONES EN LAS JUNTAS PARA LAS HIPOTESIS DE SOLICITACIONES\n"
                        "    Junta   Hip          Fz          Mx          My\n"
                        ;
  #endif    

} // end of GridJoint constructor //
