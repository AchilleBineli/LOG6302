//
//  AttaqueMagiquePoison.cpp
//  TD4
//
//  Created by Achille Bineli on 2016-10-26.
//  Copyright © 2016 Achille Bineli. All rights reserved.
//

#include "AttaqueMagiquePoison.h"

//Constructeur par défaut d'une Attaque magique de poison
AttaqueMagiquePoison::AttaqueMagiquePoison():AttaqueMagique(2)
{
}

//Constructeur par paramètre d'une attaque magique de poison
AttaqueMagiquePoison::AttaqueMagiquePoison(int duree):AttaqueMagique(duree)
{
}

//Destructeur d'une attaque magique de poison
AttaqueMagiquePoison::~AttaqueMagiquePoison(){}

//Méthode pour obtenir le type de l'attaque
string AttaqueMagiquePoison::obtenirTypeAttaque() const
{
    return typeid(*this).name();
}

//Méthode pour appliquer l'attaque magique de poison
void AttaqueMagiquePoison::appliquerAttaque(Creature& creature)
{
    unsigned int prob=rand()%3;
    if (duree_>0)
    {
        if(prob!=0) // cas  probabilite = 1 ou 2
        {
            if (creature.obtenirEnergie()>=5)
                creature.modifierEnergie(creature.obtenirEnergie()-2);
        }
        duree_--;
        
    }
}

//Fonction qui indique si l'effet de poison est terminé
bool AttaqueMagiquePoison::estFini()const
{
    if(duree_==0)
        return true;
    return false;
}