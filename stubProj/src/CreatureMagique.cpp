//
//  CreatureMagique.cpp
//  TD4
//
//  Created by Achille Bineli on 2016-10-26.
//  Copyright © 2016 Achille Bineli. All rights reserved.
//

#include "CreatureMagique.h"

//Constructeur par défaut pour une creature magique
CreatureMagique::CreatureMagique():Creature()
{
    bonus_=0;
    attaqueMagique_=nullptr;
}

//Constructeur par paramètre pour une creature magique
CreatureMagique::CreatureMagique (unsigned int bonus, const Creature& creature):Creature(creature)
{
    bonus_=bonus;
    attaqueMagique_=nullptr;
}

//Destructeur pour une creature magique
CreatureMagique::~CreatureMagique()
{
    attaqueMagique_=nullptr;
}


//constructeur par copie
CreatureMagique::CreatureMagique (const CreatureMagique& creatureMagique)
{
    bonus_=creatureMagique.bonus_;
    *attaqueMagique_=*(creatureMagique.attaqueMagique_);
    
    

}

//operteur egal d'une creature magique
CreatureMagique& CreatureMagique::operator=(const CreatureMagique& creatureMagique)
{
    if(this!=&creatureMagique)
    {
        this->bonus_= creatureMagique.bonus_;
        *(this->attaqueMagique_)=*creatureMagique.attaqueMagique_;
    }
    return *this;
}

//Méthode l'attaque d'une creature magique
AttaqueMagique* CreatureMagique::obtenirAttaqueMagique()const
{
    return attaqueMagique_;
}

//Méthode pour obtenir le bonus d'une creature magique
unsigned int CreatureMagique::obtenirBonus() const
{
    return bonus_;
}

//Méthode pour modifier le bonus d'une creature magique
void CreatureMagique::modifierBonus(unsigned int bonus)
{
    bonus_=bonus;
}

//Méthode pour modifier l'attaque d'une creature magique
void CreatureMagique::modfierAttaqueMagique(const AttaqueMagique & attaqueMagique)
{
    *attaqueMagique_=attaqueMagique;
}

//Méthode pour obtenir le type de la creature
string  CreatureMagique::obtenirTypeCreature()const
{
    return typeid(*this).name();
}

//Méthode pour attaquer avec une creature magique
void CreatureMagique::attaquer(const Pouvoir& pouvoir,Creature& creature)
{
    if((bonus_+pointDeVie_)<pointDeVieTotal_)
        pointDeVie_+=bonus_;
    if(attaqueMagique_!=nullptr)
    {
        if(!(attaqueMagique_->estFini()))
        {
             attaqueMagique_->appliquerAttaque(creature);
        }
    }
    
    Creature::attaquer(pouvoir, creature);
    
}

//Méthode pour apprendre une attaque magique à une creature
void CreatureMagique::apprendreAttaqueMagique(const AttaqueMagique& attaqueMagique)
{
    if(typeid(attaqueMagique)==typeid(AttaqueMagiqueConfusion))
    {
        attaqueMagique_=new AttaqueMagiqueConfusion(attaqueMagique.obtenirDuree());
    }
    if(typeid(attaqueMagique)==typeid(AttaqueMagiquePoison))
    {
        attaqueMagique_= new AttaqueMagiquePoison(attaqueMagique.obtenirDuree());
    }
}

//Méthode pour oublier une attaque magique
void CreatureMagique::oublierAttaqueMagique()
{
    attaqueMagique_=nullptr;
    
}

//Opérateur <<
ostream& operator<<(ostream & sortie, const CreatureMagique& creatureMagique)
{
    sortie << (Creature&) creatureMagique;
    sortie << *(creatureMagique.attaqueMagique_)<<endl;
    return sortie;
    
}