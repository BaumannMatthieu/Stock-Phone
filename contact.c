/* Stock Phone
Copyright (C) 2012 BAUMANN Matthieu

Stock Phone is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contact.h"
#include "liste.h"

struct Contact* creerContact(const int _id, const char* _nom, const char* _prenom, const char* _numero_tel, const char* _adresse)
{
    struct Contact *nouveauContact = (struct Contact*)malloc(sizeof(struct Contact));

    strcpy(nouveauContact->nom, _nom);
    strcpy(nouveauContact->prenom, _prenom);
    strcpy(nouveauContact->numero_tel, _numero_tel);
    strcpy(nouveauContact->adresse, _adresse);
    nouveauContact->id = _id;

    return nouveauContact;
}

struct Annuaire* creerAnnuaire()
{
    struct Annuaire *nouvelAnnuaire = (struct Annuaire*)malloc(sizeof(struct Annuaire));
    nouvelAnnuaire->contacts = NULL;

    return nouvelAnnuaire;
}

void trierContactsNoms(struct liste* _contacts)
{
    size_t i = 0;
    size_t lettre = 0, min = 0;

    struct liste* current = _contacts;
    struct Contact* contactMin;


    for(size_t j = 0; j < taille(_contacts); j++)
    {
        contactMin = (struct Contact*)(donner(_contacts, i)->var);

        for(size_t k = i; k < taille(_contacts); k++)
        {
            if(k == i)
                min = i;

            if(compareChar(lettre, ((struct Contact*)(current->var))->nom, contactMin->nom))
            {
                contactMin = (struct Contact*)current->var;
                min = k;
            }

            current = current->suivant;
        }
        swap(_contacts, min, i);
        i++;

        current = donner(_contacts, i);
    }
}

void trierContactsID(struct liste* _contacts)
{
    size_t i = 0, min = 0;

    struct liste* current = _contacts;
    struct Contact* contactMin;

    for(size_t j = 0; j < taille(_contacts); j++)
    {
        contactMin = (struct Contact*)(donner(_contacts, i)->var);

        for(size_t k = i; k < taille(_contacts); k++)
        {
            if(k == i)
                min = i;

            if(((struct Contact*)(current->var))->id < contactMin->id)
            {
                contactMin = (struct Contact*)current->var;
                min = k;
            }

            current = current->suivant;
        }

        swap(_contacts, min, i);
        i++;

        current = donner(_contacts, i);
    }
}

struct liste* rechercherContactID(const size_t id, struct liste* _contacts)
{
    struct liste* current = _contacts;
    struct liste* find_id = NULL;

    for(size_t t = 0; t < taille(_contacts); t++)
    {
        struct Contact current_contact = *((struct Contact*)current->var);

        int* current_contact_id = (int*)malloc(sizeof(int));
        *current_contact_id = t;

        if(current_contact.id == (id + 1))
        {
            if(find_id == NULL)
            {
                find_id = creerListeEntier(current_contact_id);
            }
            else
            {
                ajouter(&find_id, current_contact_id);
            }
        }

        current = current->suivant;

        current_contact_id = NULL;
        free(current_contact_id);
    }

    return find_id;
}

struct liste* rechercherContactNom(const char* occurence, struct liste* _contacts)
{
    struct liste* current = _contacts;
    struct liste* find_nom = NULL;

    for(size_t t = 0; t < taille(_contacts); t++)
    {
        struct Contact current_contact = *((struct Contact*)current->var);
        int* current_contact_nom = (int*)malloc(sizeof(int));
        *current_contact_nom = t;

        if(strstr(current_contact.nom, occurence) != NULL)
        {
            if(find_nom == NULL)
            {
                find_nom = creerListeEntier(current_contact_nom);
            }
            else
            {
                ajouter(&find_nom, current_contact_nom);
            }
        }

        current = current->suivant;

        current_contact_nom = NULL;
        free(current_contact_nom);
    }

    return find_nom;
}

int compareChar(size_t lettre, const char* comparant, const char* compare)
{
    if(comparant[lettre] < compare[lettre])
    {
        return 1;
    }
    else if(comparant[lettre] > compare[lettre])
    {
        return 0;
    }
    else if(comparant[lettre] == compare[lettre])
    {
        size_t longueurChaine = strlen(compare);

        if(strlen(comparant) < longueurChaine)
            longueurChaine = strlen(comparant);

        if(lettre < longueurChaine)
        {
            return compareChar(lettre + 1, comparant, compare);
        }
        else
        {
            return 0;
        }
    }

    return -1;
}

int memeContact(const struct Contact* _contact, const struct liste* _liste_contacts)
{
    while(_liste_contacts != NULL)
    {
        struct Contact contact_current = *((struct Contact*)(_liste_contacts->var));

        if(strcmp(contact_current.nom, _contact->nom) == 0 && strcmp(contact_current.prenom, _contact->prenom) == 0)
        {
            return 1; // Retourne 1 si le contact est présent dans la liste par son nom + prenom
        }
        else if(strcmp(contact_current.numero_tel, _contact->numero_tel) == 0)
        {
            return 2; // Retourne 2 si le contact est déjà présent dans la liste par son numéro de téléphone !
        }
        else if(strcmp(contact_current.adresse, _contact->adresse) == 0)
        {
            return 3;
        }

        _liste_contacts = _liste_contacts->suivant;
    }

    return 0; // Retourne 0 si le contact n'est pas présent dans la liste
}


