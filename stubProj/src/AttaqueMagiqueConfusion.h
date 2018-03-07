//
//  AttaqueMagiqueConfusion.h
//  TD4
//
//  Created by Achille Bineli on 2016-10-26.
//  Copyright © 2016 Achille Bineli. All rights reserved.
//

#ifndef AttaqueMagiqueConfusion_h
#define AttaqueMagiqueConfusion_h


#include <iostream>
#include <stdlib.h>
#include "AttaqueMagique.h"
using namespace std;

class AttaqueMagiqueConfusion :public AttaqueMagique
{
public:
    
    AttaqueMagiqueConfusion();
    AttaqueMagiqueConfusion(int duree);
    ~AttaqueMagiqueConfusion();
    virtual string obtenirTypeAttaque() const ;
    virtual void appliquerAttaque(Creature& creature) ;
    virtual  bool estFini()const ;
    
};

#endif /* AttaqueMagiqueConfusion_h */