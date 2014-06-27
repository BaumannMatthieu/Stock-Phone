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

#ifndef INTERFACE_H
#define INTERFACE_H

struct Annuaire;

struct FenetrePrincipale
{
    /* Fenetre */
    GtkWidget* fenetre;
    GtkWidget* VBox;

    /* Tree View Liste */
    GtkListStore* list;
    GtkWidget* treeView;
    GtkTreeViewColumn *column;
    GtkCellRenderer *cellRenderer;
    GtkWidget* scrollbar;
    GtkTreeModel* model;

    /* Tree View Selection */

    GtkTreeIter iter_selection;
    GtkTreePath* path_selection;

    /* Toolbar */

    GtkWidget* toolbar;

    /* Agenda */

    struct Annuaire* monAnnuaire;
};

struct FenetreAjout
{
    /* Fenetre */

    GtkWidget* dialog;

    /* Widgets */

    GtkWidget* entrys[4];
    GtkWidget* labels[4];

    /* Boites de Dialogues */

    GtkWidget* messageBoxEmpty;
    GtkWidget* messageBoxNoGoodPhone;
    GtkWidget* messageBoxTel;
    GtkWidget* messageBoxName;
    GtkWidget* messageBoxAdresse;
};

struct FenetreAPropos
{
    /* Fenetre */

    GtkWidget* dialog;

    /* Widgets */

    GtkWidget* label;
};

struct FenetreModifier
{
    /* Fenetre */

    GtkWidget* dialog;

    /* Widgets */

    GtkWidget* entrys[4];
    GtkWidget* labels[4];

    /* Boites de Dialogues */

    GtkWidget* messageBoxNoSelection;
};

struct FenetreTri
{
    /* Fenetre */

    GtkWidget* dialog;

    /* Widgets */

    GtkWidget* radio_buttons[2];
};

struct FenetreRecherche
{
    /* Fenetre */

    GtkWidget* dialog;

    /* Widgets */

    GtkWidget* radio_buttons[2];
    GtkWidget* entrys[2];
    GtkWidget* labels[2];
    GtkWidget* frames[2];
    GtkWidget* VBoxFrame;

    /* Boites de dialogues */

    GtkWidget* messageBoxLettreID;
    GtkWidget* messageBoxNoFindID;
    GtkWidget* messageBoxFindID;

    GtkWidget* messageBoxNoFindNom;
    GtkWidget* messageBoxFindNom;
};

enum
{
    RECHERCHE_ID,
    RECHERCHE_NOM,
    N_RECHERCHE
};

enum
{
    RADIO_TRI_ID,
    RADIO_TRI_NOM,
    N_RADIOS_BOUTONS
};

enum
{
    ENTRY_NOM,
    ENTRY_PRENOM,
    ENTRY_NUMERO,
    ENTRY_ADRESSE,
    N_ENTRY
};

enum
{
    COLONNE_ID,
    COLONNE_NOM,
    COLONNE_PRENOM,
    COLONNE_NUMERO,
    COLONNE_ADRESSE,
    N_COLONNES
};

/* Fonction de creation d'interface */
struct FenetrePrincipale* creerFenetrePrincipale();
struct FenetreModifier* creerFenetreModifier(struct FenetrePrincipale* _parent);
struct FenetreAjout* creerFenetreAjout(struct FenetrePrincipale* _parent);
struct FenetreTri* creerFenetreTri(struct FenetrePrincipale* _parent);
struct FenetreRecherche* creerFenetreRecherche(struct FenetrePrincipale* _parent);
struct FenetreAPropos* creerFenetreAPropos(struct FenetrePrincipale* _parent);

/* Fonctions de traitement */
void ajouterContact(struct FenetrePrincipale* _parent, struct Contact* nouveauContact);

void updateGtkListStore(const struct Annuaire* _annuaire, GtkListStore* _list);
const long convertChaineEntier(const char* str);

void ecrireFichier(const char* str, const char* nomFichier);
struct Annuaire* chargerAnnuaire(const char* nomFichier);
void sauvegarderAnnuaire(struct Annuaire* _annuaire, const char* nomFichier);

const char* replaceSpace(char* str);
const char* setSpace(char* str);


/* Fonction callbacks */
void call_ajouterContact(GtkWidget* _widgetActive, gpointer _fenetrePrincipale);
void call_modifierContact(GtkWidget* _widgetActive, gpointer _fenetrePrincipale);
void call_toggelRadioRecherche(GtkWidget* _widgetActive, gpointer _entry);
void call_trierContact(GtkWidget* _widgetActive, gpointer _fenetrePrincipale);
void call_rechercherContact(GtkWidget* _widgetActive, gpointer _fenetrePrincipale);
void call_supprimmerContact(GtkWidget* _widgetActive, gpointer _fenetrePrincipale);
void call_selectionContact(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer _fenetrePrincipale);
void call_nouvelAnnuaire(GtkWidget* _widgetActive, gpointer _fenetrePrincipale);
void call_quitterAnnuaire(GtkWidget* _widgetActive, gpointer _fenetrePrincipale);
void call_aPropos(GtkWidget* _widgetActive, gpointer _fenetrePrincipale);

/* Chargement */
void call_loadFileSelection(GtkWidget* _widgetActive, gpointer _fenetrePrincipale);
void call_loadRecupererChemin(GtkWidget* _widgetActive, gpointer _data);

/* Sauvegarde */
void call_saveFileSelection(GtkWidget* _widgetActive, gpointer _fenetrePrincipale);
void call_saveRecupererChemin(GtkWidget* _widgetActive, gpointer _data);


#endif
