//
//  CreatureMagique.h
//  TD4
//
//  Created by Achille Bineli on 2016-10-26.
//  Copyright © 2016 Achille Bineli. All rights reserved.
//

#ifndef CreatureMagique_h
#define CreatureMagique_h

#include "Creature.h"
#include "AttaqueMagique.h"
#include "AttaqueMagiqueConfusion.h"
#include "AttaqueMagiquePoison.h"

class CreatureMagique: public Creature
{
public:
    //Constructeurs
    CreatureMagique();
    CreatureMagique (unsigned int duree, const Creature& creature);
    CreatureMagique (const CreatureMagique& creatureMagique); //constructeur de copie
    virtual ~CreatureMagique();
    
    CreatureMagique& operator=(const CreatureMagique& creatureMagique);//operateur=
    
    //Acesseurs
    AttaqueMagique* obtenirAttaqueMagique()const ;
    unsigned int obtenirBonus() const;
    
    
    //Modificateurs
    void modifierBonus(unsigned int bonus);
    void modfierAttaqueMagique(const AttaqueMagique & attaqueMagique);
    
    //Methodes supplémentaires
    virtual string  obtenirTypeCreature() const;
    virtual void attaquer(const Pouvoir& pouvoir,Creature& creature);
    void apprendreAttaqueMagique(const AttaqueMagique& attaqueMagique);
    void oublierAttaqueMagique();
    
    friend ostream& operator<<(ostream & sortie, const CreatureMagique& creatureMagique);
    
    
private:
    AttaqueMagique * attaqueMagique_;
    unsigned int bonus_ ;
    
protected:
    
    
};

#endif /* CreatureMagique_h */
