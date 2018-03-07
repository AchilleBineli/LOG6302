//
//  AttaqueMagiqueConfusion.cpp
//  TD4
//
//  Created by Achille Bineli on 2016-10-26.
//  Copyright © 2016 Achille Bineli. All rights reserved.
//

#include "AttaqueMagiqueConfusion.h"

//Constructeur par défaut d'une attaque magique de confusion
AttaqueMagiqueConfusion::AttaqueMagiqueConfusion():AttaqueMagique(2)
{
}

//Constructeur par paramètre d'une attaque magique de confusion
AttaqueMagiqueConfusion::AttaqueMagiqueConfusion(int duree):AttaqueMagique(duree)
{
}

//Destructeur par défaut d'une attaque magique de confusion
AttaqueMagiqueConfusion::~AttaqueMagiqueConfusion(){}

//Méthode pour obtenir le type de l'attaque
string AttaqueMagiqueConfusion::obtenirTypeAttaque() const
{
    return typeid(*this).name();
}

//Méthode pour appliquer la méthode magique de confusion
void AttaqueMagiqueConfusion::appliquerAttaque(Creature& creature)
{
    unsigned int prob=rand()%3;
    if (duree_>0)
    {
        if(prob==0) // cas  probabilite = 0 (1/2 des cas
        {
            if (creature.obtenirEnergie()>=5)
                creature.modifierEnergie(creature.obtenirEnergie()-2);
        }
        duree_--;        
    }
}

//Méthode qui indique si l'effet est terminé
bool AttaqueMagiqueConfusion::estFini()const
{
    if(duree_==0)
        return true;
    return false;
}