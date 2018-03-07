//
//  AttaqueMagique.h
//  TD4
//
//  Created by Achille Bineli on 2016-10-26.
//  Copyright © 2016 Achille Bineli. All rights reserved.
//

#ifndef AttaqueMagique_h
#define AttaqueMagique_h

#include <iostream>
#include "Creature.h"
//#include <typeinfo>

using namespace std;
class AttaqueMagique
{
public:
    
	//Constructeur par paramètre de AttaqueMagique
    AttaqueMagique(unsigned int duree)
    {
        duree_=duree;
    };
    
	//Destructeur d'une attaque magique
    ~AttaqueMagique(){};
    
	//Méthode pour obtenir la duree
    unsigned int obtenirDuree()const
    {
        return duree_;
    };
    
	//Méthode pour modifier la duree
    void modifierDuree(unsigned int duree)
    {
        duree_=duree;
    };
    
	//Méthode pour obtenir le type de l'attaque
    virtual string obtenirTypeAttaque() const
    {
        return typeid(*this).name();
        
    };
    
	//Méthode pour appliquer l'attaque à une creature
    virtual void appliquerAttaque(Creature& creature)=0;
    
    virtual bool estFini()
    {
        return true;

    };
    
	//Opérateur <<
    friend ostream& operator<<(ostream& sortie, const AttaqueMagique & attaqueMagique)
    {
        sortie << "attaque magique de type "<< attaqueMagique.obtenirTypeAttaque() << " qui a une duree de " << attaqueMagique.duree_ <<endl;
        return sortie;
    };
        
protected:
    unsigned int duree_;
    
};

#endif /* AttaqueMagique_h */
