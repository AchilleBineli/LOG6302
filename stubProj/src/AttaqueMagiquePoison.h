//
//  AttaqueMagiquePoison.h
//  TD4
//
//  Created by Achille Bineli on 2016-10-26.
//  Copyright © 2016 Achille Bineli. All rights reserved.
//

#ifndef AttaqueMagiquePoison_h
#define AttaqueMagiquePoison_h

#include <iostream>
#include <stdlib.h> 
#include "AttaqueMagique.h"
#include "CreatureMagique.h"
using namespace std;

class AttaqueMagiquePoison :public AttaqueMagique
{
public:
    
    AttaqueMagiquePoison();
    AttaqueMagiquePoison(int duree);
    ~AttaqueMagiquePoison();
    virtual string obtenirTypeAttaque() const ;
    virtual void appliquerAttaque(Creature& creature) ;
    virtual bool estFini()const ;
    
private:
  
};

#endif /* AttaqueMagiquePoison_h */