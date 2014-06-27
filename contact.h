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

#ifndef CONTACT_H
#define CONTACT_H

struct liste;

struct Annuaire
{
    struct liste* contacts;
};

struct Contact
{
    int id;
    char nom[100];
    char prenom[100];
    char adresse[100];
    char numero_tel[100];
};

struct Contact* creerContact(const int _id, const char* _nom, const char* _prenom, const char* _numero_tel, const char* _adresse);
struct Annuaire* creerAnnuaire();

void trierContactsNoms(struct liste* _contacts);
void trierContactsID(struct liste* _contacts);

struct liste* rechercherContactID(const size_t id, struct liste* _contacts);
struct liste* rechercherContactNom(const char* occurence, struct liste* _contacts);

int compareChar(size_t lettre, const char* comparant, const char* compare);

int memeContact(const struct Contact* _contact, const struct liste* _liste_contacts);

#endif
