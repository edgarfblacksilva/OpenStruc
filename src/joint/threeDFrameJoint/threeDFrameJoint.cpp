#include "threeDFrameJoint.h"

 intPos coordPerJoint;
 intPos dofPerJoint;

ThreeDFrameJoint::ThreeDFrameJoint(const string &filename,                                          
                                         intPos &DofPerJoint, 
                                         intPos &CoordPerJoint) :  Joint(filename)
{    
    DofPerJoint = dofPerJoint;
    CoordPerJoint = coordPerJoint;
    
    sizeOfJointRecord          = static_cast<intPos>(sizeof(*this));
    sizeOfJointReactionsRecord = sizeof(real)*dofPerJoint;
    jointReactionsRecord       = new real [dofPerJoint];
  #if defined (ENGLISH)


  
    jointMessages [0] = "    Data of the Structure's Nodes\n"
                       "    Joint #         X         Y         Z  "
                       "Rdx Rdy Rdz Rrx Rry Rrz        "
                       "Kdx        Kdy        Kdz        Krx        Kry        Krz\n"
                       ;
                       
    jointMessages [1] = "    LOADS APPLIED TO THE NODES\n"
                        "    Node         Fx         Fy         Fz         Mx         My         Mz\n"
                        ;
                        
    jointMessages [2] = "    NODES INITIAL DISPLACEMENTS\n"
                        "    Node         Dx         Dy         Dz         Rx         Ry         Rz\n"
                        ;
                        
    jointMessages [3] = "    NODES DISPLACEMENTS\n"
                        "    Node              Dx              Dy              Dz              Rx              Ry              Rz\n"
                        ;
                        
    jointMessages [4] = "    LOADS AND/OR REACTIONS AT NODES\n"
                        "    Node          FX          FY          FZ          MX          MY          MZ\n"
                        ;    
    jointMessages [5] = "\n    REACTIONS AT NODES FOR THE LOADS HYPOTESYS\n"
                        "    Node    Hip          Fx          Fy          Fz          Mx          My          Mz\n"
                        ;
    
  #elif defined (ESPANOL)
    jointMessages [0] = "    Datos de las juntas de las estructura  --- Rigid  Supports --- ----------------------- Elastic  Supports -----------------------\n"    
                        "    Junta  #        X         Y         Z  "
                        "Rdx Rdy Rdz Rrx Rry Rrz        "
                        "Kdx        Kdy        Kdz        Krx        Kry        Krz\n"
                        ;
    jointMessages [1] = "    CARGAS APLICADAS EN LAS JUNTAS\n"
                        "    Junta        Fx         Fy         Fz         Mx         My         Mz\n"
                        ;
                        
    jointMessages [2] = "    DESPLAZAMIENTOS INICIALES EN LAS JUNTAS\n"
                        "    Junta        Dx         Dy         Dz         Rx         Ry         Rz\n"
                        ;
                        
    jointMessages [3] = "    DESPLAZAMIENTO DE LAS JUNTAS\n"
                        "    Junta             Dx              Dy              Dz              Rx              Ry              Rz\n"
                        ;
                        
    jointMessages [4] = "    CARGAS Y/O REACCIONES EN LAS JUNTAS\n"
                         "    Junta         FX          FY          FZ          MX          MY          MZ\n"
                         ;
    jointMessages [5] = "\n    REACCIONES EN LAS JUNTAS PARA LAS HIPOTESIS DE SOLICITACIONES\n"
                        "    Junta   Hip          Fx          Fy          Fz          Mx          My          Mz\n"
                        ;
  #endif    
} // end of ThreeDFrameJoint constructor //
