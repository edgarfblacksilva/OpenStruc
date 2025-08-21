#include "twoDFrameJoint.h"

TwoDFrameJoint::TwoDFrameJoint(const string &filename, 
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
                       "    Joint #         X         Y  "
                       "Rdx Rdy Rrz        "
                       "Kdx        Kdy        Krz\n";
    jointMessages [1] = "    LOADS APPLIED TO THE NODES\n"
                        "    Node         Fx         Fy         Mz\n"
                        ;
                        
    jointMessages [2] = "    NODES INITIAL DISPLACEMENTS\n"
                        "    Node          Dx         Dy         Rz\n"
                        ;
                        
    jointMessages [3] = "    NODES DISPLACEMENTS\n"
                        "    Node              Dx              Dy              Rz\n"
                        ;
                        
    jointMessages [4] = "    LOADS AND/OR REACTIONS AT NODES\n"
                        "    Node          FX          FY          MZ\n"
                        ;
    jointMessages [5] = "\n    REACTIONS AT NODES FOR THE LOADS HYPOTESYS\n"
                        "    Node    Hip          Fx          Fy          Mz\n"
                        ;
                        
  #elif defined (ESPANOL)
    jointMessages [0] = "    Datos de las juntas de las estructura\n"    
                        "    Junta  #  Rdx Rdy Rrz"
                        "        X         Y         "
                        "Kdx        Kdy        Krz\n";
    jointMessages [1] = "    CARGAS APLICADAS EN LAS JUNTAS\n"
                        "    Junta        Fx         Fy         Mz\n";
                        
    jointMessages [2] = "    DESPLAZAMIENTOS INICIALES EN LAS JUNTAS\n"
                        "    Junta         Dx         Dy         Rz\n";
                        
    jointMessages [3] = "    DESPLAZAMIENTO DE LAS JUNTAS\n"
                        "    Junta             Dx              Dy              Rz\n";
                        
    jointMessages [4] = "    CARGAS Y/O REACCIONES EN LAS JUNTAS\n"
                        "    Junta         FX          FY          MZ\n"
                        ;
    jointMessages [5] = "\n    REACCIONES EN LAS JUNTAS PARA LAS HIPOTESIS DE SOLICITACIONES\n"
                        "    Junta   Hip          Fx          Fy          Mz\n"
                        ;
  #endif    
} // end of TwoDFrameJoint constructor //
