#include "twoDTrussJoint.h"

TwoDTrussJoint::TwoDTrussJoint(const string &filename,
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
                       "  Rdx Rdy        "
                       "Kdx        Kdy\n"
                       ;
    jointMessages [1] = "    LOADS APPLIED TO THE NODES\n"
                        "    Node         Fx         Fy\n"
                        ;
                        
    jointMessages [2] = "    NODES INITIAL DISPLACEMENTS\n"
                        "    Node         Dx         Dy\n"
                        ;
                        
    jointMessages [3] = "    NODES DISPLACEMENTS\n"
                        "    Node              Dx              Dy\n"
                        ;
                        
    jointMessages [4] = "    LOADS AND/OR REACTIONS AT NODES\n"
                        "    Node          FX          FY\n"
                        ;
    
    jointMessages [5] = "\n    REACTIONS AT NODES FOR THE LOADS HYPOTESYS\n"
                        "    Node    Hip          Fx          Fy\n"
                        ;
    
                      
  #elif defined (ESPANOL)
    jointMessages [0] = "    Datos de las juntas de las estructura\n"    
                        "    Junta  #  Rdx Rdy"
                        "        X         Y         "
                        "Kdx        Kdy\n"
                        ;
    jointMessages [1] = "    CARGAS APLICADAS EN LAS JUNTAS\n"
                        "    Junta        Fx         Fy\n"
                        ;
                        
    jointMessages [2] = "    DESPLAZAMIENTOS INICIALES EN LAS JUNTAS\n"
                        "    Junta        Dx         Dy\n"
                        ;
                        
    jointMessages [3] = "    DESPLAZAMIENTO DE LAS JUNTAS\n"
                        "    Junta             Dx              Dy\n"
                        ;
                        
    jointMessages [4] = "    CARGAS Y/O REACCIONES EN LAS JUNTAS\n"
                        "    Junta         FX          FY\n"
                        ;
    jointMessages [5] = "\n    REACCIONES EN LAS JUNTAS PARA LAS HIPOTESIS DE SOLICITACIONES\n"
                        "    Junta   Hip          Fx          Fy\n"
                        ;

  #endif        
} // end of TwoDTrussJoint constructor //
