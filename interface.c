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
#include <gtk/gtk.h>
#include "string.h"

#include "liste.h"
#include "contact.h"
#include "interface.h"

/* Fonctions de création de l'interface */
struct FenetrePrincipale* creerFenetrePrincipale()
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)malloc(sizeof(struct FenetrePrincipale));
    /* Création de la  fenetre */
    fenetreMain->fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(fenetreMain->fenetre), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(fenetreMain->fenetre), "Stock Phone");
    gtk_window_set_default_size(GTK_WINDOW(fenetreMain->fenetre), 640, 512);

    fenetreMain->VBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(fenetreMain->fenetre), fenetreMain->VBox);

    /* Création de la Toolbar */

    fenetreMain->toolbar = gtk_toolbar_new();
    gtk_box_pack_start(GTK_BOX(fenetreMain->VBox), fenetreMain->toolbar, FALSE, FALSE, 0);

    /*GtkWidget* gtk_toolbar_insert_stock (GtkToolbar *toolbar, const gchar *stock_id, const char *tooltip_text, const char *tooltip_private_text,
      GtkSignalFunc callback, gpointer user_data, gint position);*/

    gtk_toolbar_insert_stock (GTK_TOOLBAR(fenetreMain->toolbar), GTK_STOCK_NEW, "Nouveau", NULL, G_CALLBACK(call_nouvelAnnuaire), fenetreMain, -1);

    gtk_toolbar_append_space(GTK_TOOLBAR(fenetreMain->toolbar));

    gtk_toolbar_insert_stock (GTK_TOOLBAR(fenetreMain->toolbar), GTK_STOCK_ADD, "Ajouter", NULL, G_CALLBACK(call_ajouterContact), fenetreMain, -1);
    gtk_toolbar_insert_stock (GTK_TOOLBAR(fenetreMain->toolbar), GTK_STOCK_REMOVE, "Supprimmer", NULL, G_CALLBACK(call_supprimmerContact), fenetreMain, -1);
    gtk_toolbar_insert_stock (GTK_TOOLBAR(fenetreMain->toolbar), GTK_STOCK_EDIT, "Modifier", NULL, G_CALLBACK(call_modifierContact), fenetreMain, -1);

    gtk_toolbar_append_space(GTK_TOOLBAR(fenetreMain->toolbar));

    gtk_toolbar_insert_stock (GTK_TOOLBAR(fenetreMain->toolbar), GTK_STOCK_FIND, "Rechercher", NULL, G_CALLBACK(call_rechercherContact), fenetreMain, -1);
    gtk_toolbar_insert_stock (GTK_TOOLBAR(fenetreMain->toolbar), GTK_STOCK_SORT_ASCENDING, "Trier", NULL, G_CALLBACK(call_trierContact), fenetreMain, -1);

    gtk_toolbar_append_space(GTK_TOOLBAR(fenetreMain->toolbar));

    gtk_toolbar_insert_stock (GTK_TOOLBAR(fenetreMain->toolbar), GTK_STOCK_SAVE, "Sauvegarder", NULL, G_CALLBACK(call_saveFileSelection), fenetreMain, -1);
    gtk_toolbar_insert_stock (GTK_TOOLBAR(fenetreMain->toolbar), GTK_STOCK_OPEN, "Charger", NULL, G_CALLBACK(call_loadFileSelection), fenetreMain, -1);

    gtk_toolbar_append_space(GTK_TOOLBAR(fenetreMain->toolbar));
    gtk_toolbar_insert_stock (GTK_TOOLBAR(fenetreMain->toolbar), GTK_STOCK_ABOUT, "A propos", NULL, G_CALLBACK(call_aPropos), fenetreMain, -1);
    gtk_toolbar_insert_stock (GTK_TOOLBAR(fenetreMain->toolbar), GTK_STOCK_QUIT, "Quitter", NULL, G_CALLBACK(call_quitterAnnuaire), fenetreMain, -1);

    /* Fin Toolbar */

    /* Création du modéle de la liste */

    fenetreMain->list = gtk_list_store_new(N_COLONNES, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING);
    fenetreMain->model = NULL;

    /* Creation de la vue */

    fenetreMain->treeView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(fenetreMain->list));

    /* Creation des colonnes */

    fenetreMain->cellRenderer = gtk_cell_renderer_text_new(); // Pour afficher du texte
    fenetreMain->column = gtk_tree_view_column_new_with_attributes("ID", fenetreMain->cellRenderer, "text", COLONNE_ID, NULL); // creation de la 1ere colonne
    gtk_tree_view_append_column(GTK_TREE_VIEW(fenetreMain->treeView), fenetreMain->column); // ajout de la colonne à la vue

    fenetreMain->cellRenderer = gtk_cell_renderer_text_new(); // Pour afficher du texte
    fenetreMain->column = gtk_tree_view_column_new_with_attributes("nom", fenetreMain->cellRenderer, "text", COLONNE_NOM, NULL); // creation de la 1ere colonne
    gtk_tree_view_append_column(GTK_TREE_VIEW(fenetreMain->treeView), fenetreMain->column); // ajout de la colonne à la vue

    fenetreMain->cellRenderer = gtk_cell_renderer_text_new(); // Pour afficher du texte
    fenetreMain->column = gtk_tree_view_column_new_with_attributes("prenom", fenetreMain->cellRenderer, "text", COLONNE_PRENOM, NULL); // creation de la 1ere colonne
    gtk_tree_view_append_column(GTK_TREE_VIEW(fenetreMain->treeView), fenetreMain->column); // ajout de la colonne à la vue

    fenetreMain->cellRenderer = gtk_cell_renderer_text_new(); // Pour afficher du texte
    fenetreMain->column = gtk_tree_view_column_new_with_attributes("numero", fenetreMain->cellRenderer, "text", COLONNE_NUMERO, NULL); // creation de la 1ere colonne
    gtk_tree_view_append_column(GTK_TREE_VIEW(fenetreMain->treeView), fenetreMain->column); // ajout de la colonne à la vue

    fenetreMain->cellRenderer = gtk_cell_renderer_text_new(); // Pour afficher du texte
    fenetreMain->column = gtk_tree_view_column_new_with_attributes("adresse", fenetreMain->cellRenderer, "text", COLONNE_ADRESSE, NULL); // creation de la 1ere colonne
    gtk_tree_view_append_column(GTK_TREE_VIEW(fenetreMain->treeView), fenetreMain->column); // ajout de la colonne à la vue

    /* Ajout de la vue a la fenetre */

    fenetreMain->scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(fenetreMain->VBox), fenetreMain->scrollbar, TRUE, TRUE, 0);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(fenetreMain->scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(fenetreMain->scrollbar), fenetreMain->treeView);

    /* D'autres signaux propres à la fenetre principale */

    g_signal_connect(G_OBJECT(fenetreMain->treeView), "row-activated", G_CALLBACK(call_selectionContact), fenetreMain);

    /* Affichage des widgets */

    gtk_widget_show_all(fenetreMain->fenetre);

    /* Creation d'un nouvel annuaire téléphonique */

    fenetreMain->monAnnuaire = creerAnnuaire("/home/baumann/Bureau/Matthieu/agenda_telephonique/annuaire_telephonique.txt");

    return fenetreMain;
}

struct FenetreAjout* creerFenetreAjout(struct FenetrePrincipale* _parent)
{
    struct FenetreAjout* fenetreAjout = (struct FenetreAjout*)malloc(sizeof(struct FenetreAjout));

    /*GtkWidget* gtk_dialog_new_with_buttons(const gchar *title, GtkWindow *parent, GtkDialogFlags flags, const gchar *first_button_text, ...);*/

    fenetreAjout->dialog = gtk_dialog_new_with_buttons("Ajouter un contact", GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_STOCK_ADD, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_default_size(GTK_WINDOW(fenetreAjout->dialog), 250, 150);

    for(size_t t = 0; t < N_ENTRY; t++)
    {
        fenetreAjout->entrys[t] = gtk_entry_new_with_max_length(100);
    }

    fenetreAjout->labels[ENTRY_NOM] = gtk_label_new("Le nom de votre contact :");
    fenetreAjout->labels[ENTRY_PRENOM] = gtk_label_new("Le prénom de votre contact :");
    fenetreAjout->labels[ENTRY_NUMERO] = gtk_label_new("Le numéro de téléphone de votre contact :");
    fenetreAjout->labels[ENTRY_ADRESSE] = gtk_label_new("L'adresse de votre contact :");

    for(size_t t = 0; t < N_ENTRY; t++)
    {
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(fenetreAjout->dialog)->vbox), fenetreAjout->labels[t], FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(fenetreAjout->dialog)->vbox), fenetreAjout->entrys[t], FALSE, FALSE, 0);
    }

    /* Affichage des elements de la boite de dialogue */
    gtk_widget_show_all(GTK_DIALOG(fenetreAjout->dialog)->vbox);

    int gtk_dialog_afficher = TRUE;

    while(gtk_dialog_afficher)
    {
        switch(gtk_dialog_run(GTK_DIALOG(fenetreAjout->dialog)))
        {
            case GTK_RESPONSE_OK:
            {
                /* Récupération des donnes entrées */

                const gchar* donnees[N_ENTRY];

                for(size_t t = 0; t < N_ENTRY; t++)
                {
                    donnees[t] = gtk_entry_get_text(GTK_ENTRY(fenetreAjout->entrys[t]));
                }

                struct Contact* nouveauContact = creerContact((taille(_parent->monAnnuaire->contacts) + 1), (const char*)donnees[ENTRY_NOM], (const char*)donnees[ENTRY_PRENOM], (const char*)donnees[ENTRY_NUMERO], (const char*)donnees[ENTRY_ADRESSE]);

                if(strcmp(donnees[ENTRY_NUMERO], "") == 0 || strcmp(donnees[ENTRY_NOM], "") == 0)
                {
                    fenetreAjout->messageBoxEmpty = gtk_message_dialog_new(GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Un contact doit être obligatoirement muni d'un numéro de téléphone ainsi que d'un nom");

                    if(gtk_dialog_run(GTK_DIALOG(fenetreAjout->messageBoxEmpty)) == GTK_RESPONSE_CLOSE)
                    {
                        // Rien
                    }

                    gtk_widget_destroy(fenetreAjout->messageBoxEmpty);
                }
                else if(strlen(donnees[ENTRY_NUMERO]) != 10 || convertChaineEntier(donnees[ENTRY_NUMERO]) == -1)
                {
                    fenetreAjout->messageBoxNoGoodPhone = gtk_message_dialog_new(GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Votre téléphone doit être composé de 10 chiffres");

                    if(gtk_dialog_run(GTK_DIALOG(fenetreAjout->messageBoxNoGoodPhone)) == GTK_RESPONSE_CLOSE)
                    {
                        // Rien
                    }

                    gtk_widget_destroy(fenetreAjout->messageBoxNoGoodPhone);
                }
                else if(memeContact(nouveauContact, _parent->monAnnuaire->contacts) == 1)
                {
                    fenetreAjout->messageBoxName = gtk_message_dialog_new(GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Le contact que vous avez saisi existe déjà !");

                    if(gtk_dialog_run(GTK_DIALOG(fenetreAjout->messageBoxName)) == GTK_RESPONSE_CLOSE)
                    {
                        // Rien
                    }

                    gtk_widget_destroy(fenetreAjout->messageBoxName);
                }
                else if(memeContact(nouveauContact, _parent->monAnnuaire->contacts) == 3)
                {
                    fenetreAjout->messageBoxAdresse = gtk_message_dialog_new(GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_YES_NO, "L'adresse du contact que vous avez saisi a déjà été identifiée pour un autre contact, souhaitez-vous réellement ajouter ce contact ?");

                    switch(gtk_dialog_run(GTK_DIALOG(fenetreAjout->messageBoxAdresse)))
                    {
                        case GTK_RESPONSE_YES:
                        {
                            ajouterContact(_parent, nouveauContact);
                            gtk_dialog_afficher = FALSE;
                        }
                        break;
                        case GTK_RESPONSE_NO:
                        break;
                        default:
                        break;
                    }

                    gtk_widget_destroy(fenetreAjout->messageBoxAdresse);
                }
                else if(memeContact(nouveauContact, _parent->monAnnuaire->contacts) == 2)
                {
                    fenetreAjout->messageBoxTel = gtk_message_dialog_new(GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Le numéro que vous avez saisi est déjà répertorié dans la base de données !");

                    if(gtk_dialog_run(GTK_DIALOG(fenetreAjout->messageBoxTel)) == GTK_RESPONSE_CLOSE)
                    {
                        // Rien
                    }

                    gtk_widget_destroy(fenetreAjout->messageBoxTel);
                }
                else
                {
                    /* Ajout des donnees dans l'annuaire téléphonique */

                    ajouterContact(_parent, nouveauContact);

                    gtk_dialog_afficher = FALSE;
                }
            }
            break;
            case GTK_RESPONSE_CANCEL:
                gtk_dialog_afficher = FALSE;
            break;
            default:
            break;
        }
    }

    gtk_widget_destroy(GTK_WIDGET(fenetreAjout->dialog));

    return fenetreAjout;
}

struct FenetreModifier* creerFenetreModifier(struct FenetrePrincipale* _parent)
{
    struct FenetreModifier* fenetreModifiee = (struct FenetreModifier*)malloc(sizeof(struct FenetreModifier));

    if(_parent->path_selection == NULL)
    {
        fenetreModifiee->messageBoxNoSelection = gtk_message_dialog_new(GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Aucun contact a été sélectionné.");

        if(gtk_dialog_run(GTK_DIALOG(fenetreModifiee->messageBoxNoSelection)) == GTK_RESPONSE_CLOSE)
        {
            // Rien
        }

        gtk_widget_destroy(fenetreModifiee->messageBoxNoSelection);
    }
    else
    {
        size_t row_selected_id = strtol(gtk_tree_path_to_string(_parent->path_selection), NULL, 10);
        struct Contact* contact_modif = ((struct Contact*)(donner(_parent->monAnnuaire->contacts, row_selected_id)->var));

        /*GtkWidget* gtk_dialog_new_with_buttons(const gchar *title, GtkWindow *parent, GtkDialogFlags flags, const gchar *first_button_text, ...);*/

        fenetreModifiee->dialog = gtk_dialog_new_with_buttons("Modifier un contact", GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_STOCK_ADD, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
        gtk_window_set_default_size(GTK_WINDOW(fenetreModifiee->dialog), 250, 150);

        for(size_t t = 0; t < N_ENTRY; t++)
        {
            fenetreModifiee->entrys[t] = gtk_entry_new_with_max_length(100);
        }

        gtk_entry_set_text(GTK_ENTRY(fenetreModifiee->entrys[ENTRY_NOM]), contact_modif->nom);
        gtk_entry_set_text(GTK_ENTRY(fenetreModifiee->entrys[ENTRY_PRENOM]), contact_modif->prenom);
        gtk_entry_set_text(GTK_ENTRY(fenetreModifiee->entrys[ENTRY_NUMERO]), contact_modif->numero_tel);
        gtk_entry_set_text(GTK_ENTRY(fenetreModifiee->entrys[ENTRY_ADRESSE]), contact_modif->adresse);

        fenetreModifiee->labels[ENTRY_NOM] = gtk_label_new("Le nom de votre contact :");
        fenetreModifiee->labels[ENTRY_PRENOM] = gtk_label_new("Le prénom de votre contact :");
        fenetreModifiee->labels[ENTRY_NUMERO] = gtk_label_new("Le numéro de téléphone de votre contact :");
        fenetreModifiee->labels[ENTRY_ADRESSE] = gtk_label_new("L'adresse de votre contact :");

        for(size_t t = 0; t < N_ENTRY; t++)
        {
            gtk_box_pack_start(GTK_BOX(GTK_DIALOG(fenetreModifiee->dialog)->vbox), fenetreModifiee->labels[t], FALSE, FALSE, 0);
            gtk_box_pack_start(GTK_BOX(GTK_DIALOG(fenetreModifiee->dialog)->vbox), fenetreModifiee->entrys[t], FALSE, FALSE, 0);
        }

        /* Affichage des elements de la boite de dialogue */
        gtk_widget_show_all(GTK_DIALOG(fenetreModifiee->dialog)->vbox);

        switch(gtk_dialog_run(GTK_DIALOG(fenetreModifiee->dialog)))
        {
            case GTK_RESPONSE_OK:
            {
                /* Récupération des donnes entrées */

                const gchar* donnees[N_ENTRY];

                for(size_t t = 0; t < N_ENTRY; t++)
                {
                    donnees[t] = gtk_entry_get_text(GTK_ENTRY(fenetreModifiee->entrys[t]));
                }

                /* Modification de l'annuaire */

                strcpy(contact_modif->nom, donnees[ENTRY_NOM]);
                strcpy(contact_modif->prenom, donnees[ENTRY_PRENOM]);
                strcpy(contact_modif->numero_tel, donnees[ENTRY_NUMERO]);
                strcpy(contact_modif->adresse, donnees[ENTRY_ADRESSE]);

                updateGtkListStore(_parent->monAnnuaire, _parent->list);

            }
            break;
            case GTK_RESPONSE_CANCEL:
            break;
            default:
            break;
        }

        gtk_widget_destroy(GTK_WIDGET(fenetreModifiee->dialog));
    }

    return fenetreModifiee;
}

struct FenetreAPropos* creerFenetreAPropos(struct FenetrePrincipale* _parent)
{
    struct FenetreAPropos* fenetreAPropos = (struct FenetreAPropos*)malloc(sizeof(struct FenetreAPropos));

    fenetreAPropos->dialog = gtk_dialog_new_with_buttons("A propos de Stock Phone", GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
    gtk_window_set_default_size(GTK_WINDOW(fenetreAPropos->dialog), 300, 100);

    fenetreAPropos->label = gtk_label_new("Programme : Stock Phone\nAnnée : 2012\nLicence : GNU GPL\nConcepteur : BAUMANN Matthieu\nLangage et librairie : C/GTK+");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(fenetreAPropos->dialog)->vbox), fenetreAPropos->label, FALSE, FALSE, 0);

    /* Affichage des elements de la boite de dialogue */
    gtk_widget_show_all(GTK_DIALOG(fenetreAPropos->dialog)->vbox);

    /* Affichage de la boite de dialogue */
    switch(gtk_dialog_run(GTK_DIALOG(fenetreAPropos->dialog)))
    {
        case GTK_RESPONSE_OK:
        break;
        default:
        break;
    }

    gtk_widget_destroy(GTK_WIDGET(fenetreAPropos->dialog));

    return fenetreAPropos;
}

struct FenetreTri* creerFenetreTri(struct FenetrePrincipale* _parent)
{
    struct FenetreTri* fenetreTri = (struct FenetreTri*)malloc(sizeof(struct FenetreTri));

    /*GtkWidget* gtk_dialog_new_with_buttons(const gchar *title, GtkWindow *parent, GtkDialogFlags flags, const gchar *first_button_text, ...);*/

    fenetreTri->dialog = gtk_dialog_new_with_buttons("Trier vos contacts", GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_default_size(GTK_WINDOW(fenetreTri->dialog), 300, 50);

    fenetreTri->radio_buttons[RADIO_TRI_ID] = gtk_radio_button_new_with_label(NULL, "par ID");
    fenetreTri->radio_buttons[RADIO_TRI_NOM] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(fenetreTri->radio_buttons[RADIO_TRI_ID]), "par Nom");

    for(size_t t = 0; t < N_RADIOS_BOUTONS; t++)
    {
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(fenetreTri->dialog)->vbox), fenetreTri->radio_buttons[t], FALSE, FALSE, 0);
    }

    /* Affichage des elements de la boite de dialogue */
    gtk_widget_show_all(GTK_DIALOG(fenetreTri->dialog)->vbox);

    /* Affichage de la boite de dialogue */
    switch(gtk_dialog_run(GTK_DIALOG(fenetreTri->dialog)))
    {
        case GTK_RESPONSE_OK:
        {
            /* Recuperation de nos radios_boutons pour examination */
            if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(fenetreTri->radio_buttons[RADIO_TRI_ID])))
            {
                trierContactsID(_parent->monAnnuaire->contacts);
            }
            else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(fenetreTri->radio_buttons[RADIO_TRI_NOM])))
            {
                trierContactsNoms(_parent->monAnnuaire->contacts);
            }

            updateGtkListStore(_parent->monAnnuaire, _parent->list);
        }
        break;
        case GTK_RESPONSE_CANCEL:
        break;
        default:
        break;
    }

    gtk_widget_destroy(GTK_WIDGET(fenetreTri->dialog));

    return fenetreTri;
}

struct FenetreRecherche* creerFenetreRecherche(struct FenetrePrincipale* _parent)
{
    struct FenetreRecherche* fenetreRecherche = (struct FenetreRecherche*)malloc(sizeof(struct FenetreRecherche));

    /*GtkWidget* gtk_dialog_new_with_buttons(const gchar *title, GtkWindow *parent, GtkDialogFlags flags, const gchar *first_button_text, ...);*/

    fenetreRecherche->dialog = gtk_dialog_new_with_buttons("Rechercher un contact", GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_default_size(GTK_WINDOW(fenetreRecherche->dialog), 300, 150);

    fenetreRecherche->frames[0] = gtk_frame_new("Quel Recherche ?");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(fenetreRecherche->dialog)->vbox), fenetreRecherche->frames[0], FALSE, FALSE, 0);
    fenetreRecherche->frames[1] = gtk_frame_new("Votre Recherche :");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(fenetreRecherche->dialog)->vbox), fenetreRecherche->frames[1], FALSE, FALSE, 0);

    /* Insertion widget dans frame "quel recherche" */
    fenetreRecherche->VBoxFrame = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(fenetreRecherche->frames[0]), fenetreRecherche->VBoxFrame);

    fenetreRecherche->radio_buttons[RECHERCHE_ID] = gtk_radio_button_new_with_label(NULL, "par ID");
    fenetreRecherche->radio_buttons[RECHERCHE_NOM] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(fenetreRecherche->radio_buttons[RECHERCHE_ID]), "par Nom");

    gtk_box_pack_start(GTK_BOX(fenetreRecherche->VBoxFrame), fenetreRecherche->radio_buttons[RECHERCHE_ID], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(fenetreRecherche->VBoxFrame), fenetreRecherche->radio_buttons[RECHERCHE_NOM], FALSE, FALSE, 0);

    /* Insertion widget dans frame "recherche" */
    fenetreRecherche->VBoxFrame = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(fenetreRecherche->frames[1]), fenetreRecherche->VBoxFrame);

    fenetreRecherche->labels[RECHERCHE_ID] = gtk_label_new("par ID :");
    fenetreRecherche->labels[RECHERCHE_NOM] = gtk_label_new("par Nom :");
    fenetreRecherche->entrys[RECHERCHE_ID] = gtk_entry_new();
    fenetreRecherche->entrys[RECHERCHE_NOM] = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(fenetreRecherche->entrys[RECHERCHE_NOM]), 0);

    gtk_box_pack_start(GTK_BOX(fenetreRecherche->VBoxFrame), fenetreRecherche->labels[RECHERCHE_ID], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(fenetreRecherche->VBoxFrame), fenetreRecherche->entrys[RECHERCHE_ID], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(fenetreRecherche->VBoxFrame), fenetreRecherche->labels[RECHERCHE_NOM], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(fenetreRecherche->VBoxFrame), fenetreRecherche->entrys[RECHERCHE_NOM], FALSE, FALSE, 0);

    GSList* liste_id = NULL;
    GSList* liste_nom = NULL;
    liste_id = g_slist_append(liste_id, fenetreRecherche->entrys[RECHERCHE_ID]);
    liste_id = g_slist_append(liste_id, fenetreRecherche->entrys[RECHERCHE_NOM]);

    g_signal_connect(G_OBJECT(fenetreRecherche->radio_buttons[RECHERCHE_ID]), "clicked", G_CALLBACK(call_toggelRadioRecherche), liste_id);

    liste_nom = g_slist_append(liste_nom, fenetreRecherche->entrys[RECHERCHE_NOM]);
    liste_nom = g_slist_append(liste_nom, fenetreRecherche->entrys[RECHERCHE_ID]);

    g_signal_connect(G_OBJECT(fenetreRecherche->radio_buttons[RECHERCHE_NOM]), "clicked", G_CALLBACK(call_toggelRadioRecherche), liste_nom);

    /* Affichage des elements de la boite de dialogue */
    gtk_widget_show_all(GTK_DIALOG(fenetreRecherche->dialog)->vbox);

    /* Affichage de la boite de dialogue */
    int gtk_dialog_afficher = TRUE;

    while(gtk_dialog_afficher != FALSE)
    {
        switch(gtk_dialog_run(GTK_DIALOG(fenetreRecherche->dialog)))
        {
            case GTK_RESPONSE_OK:
            {
                GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(_parent->treeView));
                GtkTreePath* path_selection = NULL;

                struct liste* find = NULL;

                /* Recuperation de nos radios_boutons pour examination */
                if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(fenetreRecherche->radio_buttons[RADIO_TRI_ID])))
                {
                    const char* result_entry_id_string = gtk_entry_get_text(GTK_ENTRY(fenetreRecherche->entrys[RECHERCHE_ID]));
                    const long result_entry_id = convertChaineEntier(result_entry_id_string);

                    if(result_entry_id == -1) // Si l'entree a comportee des lettres
                    {
                        // Affichage d'une MessageBox indiquant l'erreur
                        /*GtkWidget* gtk_message_dialog_new (GtkWindow *parent, GtkDialogFlags flags, GtkMessageType type, GtkButtonsType buttons, const gchar *message_format, ...);*/
                        fenetreRecherche->messageBoxLettreID = gtk_message_dialog_new(GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Votre id comporte des caracteres non valables (chiffres uniquement)");

                        if(gtk_dialog_run(GTK_DIALOG(fenetreRecherche->messageBoxLettreID)) == GTK_RESPONSE_CLOSE)
                        {
                            // Rien
                        }

                        gtk_widget_destroy(fenetreRecherche->messageBoxLettreID);
                        //g_print("Votre id comporte des caracteres non valables (chiffres uniquement)\n");
                    }
                    else // Sinon
                    {
                        find = rechercherContactID((result_entry_id - 1), _parent->monAnnuaire->contacts);

                        if(find == NULL) // Si l'id n'a pas ete trouve
                        {
                            // Affichage d'une MessageBox indiquant l'erreur
                            /*GtkWidget* gtk_message_dialog_new (GtkWindow *parent, GtkDialogFlags flags, GtkMessageType type, GtkButtonsType buttons, const gchar *message_format, ...);*/
                            char str_messageBoxNoFindID[150];

                            sprintf(str_messageBoxNoFindID, "Votre base de données compte %d contacts, veuillez entrer un numéro d'ID entre 1 et %d", (const int)taille(_parent->monAnnuaire->contacts), (const int)taille(_parent->monAnnuaire->contacts));
                            fenetreRecherche->messageBoxNoFindID = gtk_message_dialog_new(GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, str_messageBoxNoFindID, NULL);
                            //gtk_window_set_title(GTK_WINDOW(fenetreRecherche->messageBoxNoFindID), "Erreur : ID non répertorié");

                            if(gtk_dialog_run(GTK_DIALOG(fenetreRecherche->messageBoxNoFindID)) == GTK_RESPONSE_CLOSE)
                            {
                                // Rien
                            }

                            gtk_widget_destroy(fenetreRecherche->messageBoxNoFindID);
                        }
                        else
                        {
                            char res[1];
                            sprintf(res, "%d", *((int*)find->var));

                            path_selection = gtk_tree_path_new_from_string(res);
                            gtk_dialog_afficher = FALSE;
                        }
                    }
                }
                else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(fenetreRecherche->radio_buttons[RADIO_TRI_NOM])))
                {
                    const char* result_entry_nom_string = gtk_entry_get_text(GTK_ENTRY(fenetreRecherche->entrys[RECHERCHE_NOM]));

                    find = rechercherContactNom(result_entry_nom_string, _parent->monAnnuaire->contacts);

                    /* Mise à jour de l'annuaire pour l'affichage des contacts retrouves en 1ere place !*/
                    struct liste* current = find;
                    size_t inc = 0;

                    while(current != NULL)
                    {
                        const int find_row_current = *((int*)(current->var));

                        swap(_parent->monAnnuaire->contacts, inc, find_row_current);

                        current = current->suivant;
                        inc++;
                    }
                    /* Fin Mise à jour */

                    if(find == NULL) // Si l'nom n'a pas ete trouve
                    {
                        // Affichage d'une MessageBox indiquant l'erreur
                        /*GtkWnomget* gtk_message_dialog_new (GtkWindow *parent, GtkDialogFlags flags, GtkMessageType type, GtkButtonsType buttons, const gchar *message_format, ...);*/
                        fenetreRecherche->messageBoxNoFindNom = gtk_message_dialog_new(GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Aucuns contacts n'a été retrouvé");
                        //gtk_window_set_title(GTK_WINDOW(fenetreRecherche->messageBoxNoFindnom), "Erreur : nom non répertorié");

                        if(gtk_dialog_run(GTK_DIALOG(fenetreRecherche->messageBoxNoFindNom)) == GTK_RESPONSE_CLOSE)
                        {
                            // Rien
                        }

                        gtk_widget_destroy(fenetreRecherche->messageBoxNoFindNom);
                    }
                    else
                    {
                        char res[1];
                        char message_dialog_find_noms[150];
                        sprintf(message_dialog_find_noms, "%d contacts ont été retrouvées !", (int)taille(find));

                        sprintf(res, "%d", *((int*)find->var));

                        path_selection = gtk_tree_path_new_from_string(res);

                        // Affichage d'une MessageBox : Contact trouves !
                        //fenetreRecherche->messageBoxFindNom = gtk_message_dialog_new(GTK_WINDOW(_parent->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, (const gchar*)message_dialog_find_noms);
                        //gtk_window_set_title(GTK_WINDOW(fenetreRecherche->messageBoxNoFindnom), "Erreur : nom non répertorié");

                        //if(gtk_dialog_run(GTK_DIALOG(fenetreRecherche->messageBoxFindNom)) == GTK_RESPONSE_CLOSE)
                        //{
                            // Rien
                        //}

                        //gtk_widget_destroy(fenetreRecherche->messageBoxFindNom);

                        gtk_dialog_afficher = FALSE;
                    }
                }

                updateGtkListStore(_parent->monAnnuaire, _parent->list);

                if(path_selection != NULL)
                {
                    gtk_tree_selection_select_path(selection, path_selection);
                }
            }
            break;
            case GTK_RESPONSE_CANCEL:
            {
                gtk_dialog_afficher = FALSE;
            }
            break;
            default:
            break;
        }
    }

    gtk_widget_destroy(GTK_WIDGET(fenetreRecherche->dialog));

    return fenetreRecherche;
}

/* Fonctions de traitements */

void ajouterContact(struct FenetrePrincipale* _parent, struct Contact* nouveauContact)
{
    if(taille(_parent->monAnnuaire->contacts) == 0) // Si mon annuaire est vide
    {
        _parent->monAnnuaire->contacts = creerListeDeContact(nouveauContact);
    }
    else
    {
        ajouter(&_parent->monAnnuaire->contacts, nouveauContact);
    }

    /* Ajout des donnees dans la GTreeViewList */
    GtkTreeIter iter;
    gtk_list_store_append(_parent->list, &iter);
    gtk_list_store_set(_parent->list, &iter, COLONNE_ID, nouveauContact->id, COLONNE_NOM, nouveauContact->nom, COLONNE_PRENOM, nouveauContact->prenom, COLONNE_NUMERO, nouveauContact->numero_tel, COLONNE_ADRESSE, nouveauContact->adresse, -1);
}

void updateGtkListStore(const struct Annuaire* _annuaire, GtkListStore* _list)
{
    gtk_list_store_clear(_list);

    struct liste* current = _annuaire->contacts;

    while(current != NULL)
    {
        GtkTreeIter iter;
        struct Contact current_contact = *((struct Contact*)(current->var));

        gtk_list_store_append(_list, &iter);
        gtk_list_store_set(_list, &iter, COLONNE_ID, current_contact.id, COLONNE_NOM, current_contact.nom, COLONNE_PRENOM, current_contact.prenom, COLONNE_NUMERO, current_contact.numero_tel, COLONNE_ADRESSE, current_contact.adresse, -1);

        current = current->suivant;
    }

    free(current);
}

const long convertChaineEntier(const char* str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        if(str[i] >= 58 || str[i] <= 47)
        {
            return -1;
        }
    }

    return strtol(str, NULL, 10);
}

struct Annuaire* chargerAnnuaire(const char* nomFichier)
{
    struct Annuaire* monAnnuaire = creerAnnuaire("/home/baumann/Bureau/Matthieu/agenda_telephonique/annuaire_telephonique.txt");
    int tailleAnnuaire = 0;

    FILE* file_load = fopen(nomFichier, "r+");

    if(file_load != NULL)
    {
        if(fscanf(file_load, "%d\n", &(tailleAnnuaire)) == EOF)
            exit(EXIT_FAILURE);

        for(size_t i = 0; i < tailleAnnuaire; i++)
        {
            int idContact = 0;
            char nomContact[200], prenomContact[200], numero_telContact[200], adresseContact[200];

            if(fscanf(file_load, "%d  %s  %s  %s  %s\n", &idContact, nomContact, prenomContact, numero_telContact, adresseContact) == EOF)
                exit(EXIT_FAILURE);

            if(monAnnuaire->contacts == NULL)
            {
                monAnnuaire->contacts = creerListeDeContact(creerContact(idContact, nomContact, prenomContact, numero_telContact, adresseContact));
            }
            else
            {
                ajouter(&monAnnuaire->contacts, creerContact(idContact, nomContact, prenomContact, numero_telContact, adresseContact));
            }
        }
    }
    else
    {
        fprintf(stderr, "Fichier inexistant\n");
    }

    fclose(file_load);

    /* Enlever les underscore */

    struct liste* current = monAnnuaire->contacts;

    while(current != NULL)
    {
        struct Contact* contact_current = ((struct Contact*)(current->var));

        strcpy(contact_current->nom, setSpace(contact_current->nom));
        strcpy(contact_current->prenom, setSpace(contact_current->prenom));
        strcpy(contact_current->adresse, setSpace(contact_current->adresse));

        current = current->suivant;

    }

    free(current);

    /* Fin enlever les underscore */

    return monAnnuaire;
}

void sauvegarderAnnuaire(struct Annuaire* _annuaire, const char* nomFichier)
{
    char buffer[5000], chaineContact[200], chaineNombreContacts[10];

    /* Ajout des underscore pour éviter les erreurs de chargement du aux fsanf */

    struct liste* current = _annuaire->contacts;

    while(current != NULL)
    {
        struct Contact* contact_current = ((struct Contact*)(current->var));

        strcpy(contact_current->nom, replaceSpace(contact_current->nom));
        strcpy(contact_current->prenom, replaceSpace(contact_current->prenom));
        strcpy(contact_current->adresse, replaceSpace(contact_current->adresse));

        current = current->suivant;

    }

    /* Fin sécuriser les fscanf */

    strcpy(chaineNombreContacts, "");
    strcpy(buffer, "");
    strcpy(chaineContact, "");

    sprintf(chaineNombreContacts, "%d\n", (int)taille(_annuaire->contacts));
    strcat(buffer, chaineNombreContacts);

    current = _annuaire->contacts;

    while(current != NULL)
    {
        sprintf(chaineContact, "%d  %s  %s  %s  %s\n", ((struct Contact*)(current->var))->id, ((struct Contact*)(current->var))->nom, ((struct Contact*)(current->var))->prenom, ((struct Contact*)(current->var))->numero_tel, ((struct Contact*)(current->var))->adresse);
        strcat(chaineContact, "\0");

        strcat(buffer, chaineContact);

        current = current->suivant;
    }

    strcat(buffer, "\0");

    ecrireFichier(buffer, nomFichier);

    /* Enlever les underscore */

    current = _annuaire->contacts;

    while(current != NULL)
    {
        struct Contact* contact_current = ((struct Contact*)(current->var));

        strcpy(contact_current->nom, setSpace(contact_current->nom));
        strcpy(contact_current->prenom, setSpace(contact_current->prenom));
        strcpy(contact_current->adresse, setSpace(contact_current->adresse));

        current = current->suivant;
    }

    free(current);

    /* Fin enlever les underscore */
}

void ecrireFichier(const char* str, const char* nomFichier)
{
    FILE* fichier = fopen(nomFichier, "w+");

    if(fichier != NULL)
    {
        fputs(str, fichier);
    }
    else
    {
        fprintf(stderr, "Fichier de sauvegarde inexistant\n");
    }

    fclose(fichier);
}

const char* replaceSpace(char* str)
{
    for(size_t t = 0; t < strlen(str); t++)
    {
        if(str[t] == ' ')
        {
            str[t] = '_';
        }
    }

    return str;
}

const char* setSpace(char* str)
{
    for(size_t t = 0; t < strlen(str); t++)
    {
        if(str[t] == '_')
        {
            str[t] = ' ';
        }
    }

    return str;
}

/* Fonctions Callbacks */

void call_loadFileSelection(GtkWidget* _widgetActive, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;
    GtkWidget *selection;
    GSList* list_data = NULL;

    selection = gtk_file_selection_new("Sélectionner un fichier");
    gtk_widget_show(selection);

    //On interdit l'utilisation des autres fenetres.
    gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
    // Creer GSList : selection + fenetre_principale
    list_data = g_slist_append(list_data, selection);
    list_data = g_slist_append(list_data, fenetreMain);

    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(call_loadRecupererChemin), list_data);
    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}

void call_loadRecupererChemin(GtkWidget* _widgetActive, gpointer _data)
{
    GSList* list_data = (GSList*)_data;
    GtkWidget* file_selection = GTK_WIDGET(list_data->data);
    list_data = (GSList*)g_list_next(list_data);
    struct FenetrePrincipale* fenetreMain = ((struct FenetrePrincipale*)(list_data->data));

    const gchar* chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION(file_selection));
    fenetreMain->monAnnuaire = chargerAnnuaire(chemin);

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Fichier chargé :\n%s", chemin);

    gtk_dialog_run(GTK_DIALOG(dialog));

    updateGtkListStore(fenetreMain->monAnnuaire, fenetreMain->list);

    gtk_widget_destroy(dialog);
    gtk_widget_destroy(file_selection);
}

void call_saveFileSelection(GtkWidget* _widgetActive, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;
    GtkWidget *selection;
    GSList* list_data = NULL;

    selection = gtk_file_selection_new("Sélectionner un fichier");
    gtk_widget_show(selection);

    //On interdit l'utilisation des autres fenetres.
    gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
    // Creer GSList : selection + fenetre_principale
    list_data = g_slist_append(list_data, selection);
    list_data = g_slist_append(list_data, fenetreMain);

    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(call_saveRecupererChemin), list_data);
    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);

    gtk_dialog_run(GTK_DIALOG(selection));
}

void call_saveRecupererChemin(GtkWidget* _widgetActive, gpointer _data)
{
    GSList* list_data = (GSList*)_data;
    GtkWidget* file_selection = GTK_WIDGET(list_data->data);
    list_data = (GSList*)g_list_next(list_data);
    struct FenetrePrincipale* fenetreMain = ((struct FenetrePrincipale*)(list_data->data));

    const gchar* chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION(file_selection));
    sauvegarderAnnuaire(fenetreMain->monAnnuaire, chemin);

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Fichier sauvegardé :\n%s", chemin);

    gtk_dialog_run(GTK_DIALOG(dialog));

    updateGtkListStore(fenetreMain->monAnnuaire, fenetreMain->list);

    gtk_widget_destroy(dialog);
    gtk_widget_destroy(file_selection);
}

void call_trierContact(GtkWidget* _widgetActive, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;

    if(creerFenetreTri(fenetreMain) == NULL)
    {
        g_print("error");
        exit(EXIT_FAILURE);
    }
}

void call_ajouterContact(GtkWidget* _widgetActive, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;

    if(creerFenetreAjout(fenetreMain) == NULL)
        exit(EXIT_FAILURE);
}

void call_nouvelAnnuaire(GtkWidget* _widgetActive, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;

    GtkWidget* messageBoxSave = gtk_message_dialog_new(GTK_WINDOW(fenetreMain->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, "Souhaitez-vous sauvegarder votre agenda actuel avant de le fermer et d'en créer un autre ?");
    gtk_window_set_title(GTK_WINDOW(messageBoxSave), "Création d'un nouvel agenda téléphonique");

    switch(gtk_dialog_run(GTK_DIALOG(messageBoxSave)))
    {
        case GTK_RESPONSE_YES:
        {
            call_saveFileSelection(NULL, fenetreMain);
        }
        break;
        case GTK_RESPONSE_NO:
        break;
        default:
        break;
    }

    if(fenetreMain->monAnnuaire->contacts != NULL) // Si la liste de contacts est vide
    {
        fenetreMain->monAnnuaire->contacts = creerListeDeContact((struct Contact*)(fenetreMain->monAnnuaire->contacts->var));
        supprimmer(&fenetreMain->monAnnuaire->contacts, 0);
    }

    updateGtkListStore(fenetreMain->monAnnuaire, fenetreMain->list);

    gtk_widget_destroy(messageBoxSave);
}

void call_quitterAnnuaire(GtkWidget* _widgetActive, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;

    GtkWidget* messageBoxSave = gtk_message_dialog_new(GTK_WINDOW(fenetreMain->fenetre), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, "Souhaitez-vous sauvegarder votre agenda actuel avant de le fermer et d'en créer un autre ?");
    gtk_window_set_title(GTK_WINDOW(messageBoxSave), "Quitter Stock Phone");

    switch(gtk_dialog_run(GTK_DIALOG(messageBoxSave)))
    {
        case GTK_RESPONSE_YES:
        {
            call_saveFileSelection(NULL, fenetreMain);
        }
        break;
        case GTK_RESPONSE_NO:
        break;
        default:
        break;
    }

    if(fenetreMain->monAnnuaire->contacts != NULL) // Si la liste de contacts est vide
    {
        fenetreMain->monAnnuaire->contacts = creerListeDeContact((struct Contact*)(fenetreMain->monAnnuaire->contacts->var));
        supprimmer(&fenetreMain->monAnnuaire->contacts, 0);
    }

    updateGtkListStore(fenetreMain->monAnnuaire, fenetreMain->list);

    gtk_widget_destroy(messageBoxSave);

    gtk_main_quit();
}

void call_modifierContact(GtkWidget* _widgetActive, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;

    if(creerFenetreModifier(fenetreMain) == NULL)
        exit(EXIT_FAILURE);
}

void call_rechercherContact(GtkWidget* _widgetActive, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;

    if(creerFenetreRecherche(fenetreMain) == NULL)
        exit(EXIT_FAILURE);
}

void call_aPropos(GtkWidget* _widgetActive, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;

    if(creerFenetreAPropos(fenetreMain) == NULL)
        exit(EXIT_FAILURE);
}

void call_supprimmerContact(GtkWidget* _widgetActive, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;

    if(fenetreMain->model != NULL)
    {
        /* Suppression de la ligne dans la GtkTreeList */
        gtk_list_store_remove(GTK_LIST_STORE(fenetreMain->model), &(fenetreMain->iter_selection));

        /* Suppression dans l'annuaire */
        size_t row_selected_id = strtol(gtk_tree_path_to_string(fenetreMain->path_selection), NULL, 10);
        struct liste* liste_current = fenetreMain->monAnnuaire->contacts;

        supprimmer(&fenetreMain->monAnnuaire->contacts, row_selected_id);

        if(taille(fenetreMain->monAnnuaire->contacts) != 0) // Si la liste n'est pas vide
        {
            for(size_t t = 0; t < taille(fenetreMain->monAnnuaire->contacts); t++)
            {
                struct Contact* contact_current = ((struct Contact*)liste_current->var);

                if(contact_current->id > (row_selected_id + 1))
                    contact_current->id = contact_current->id - 1;

                liste_current = liste_current->suivant;

                contact_current = NULL;
                free(contact_current);
            }

            free(liste_current);

            /* Mise à jour de la GtkTreeList en fonction de l'annuaire */
            updateGtkListStore(fenetreMain->monAnnuaire, fenetreMain->list);
        }
    }

    fenetreMain->model = NULL;

    /* Suppression de notre contact dans l'annuaire */

}

void call_toggelRadioRecherche(GtkWidget* _widgetActive, gpointer _entry)
{
    GSList* liste_entrys = (GSList*)_entry;

    gtk_editable_set_editable(GTK_EDITABLE(GTK_ENTRY(liste_entrys->data)), 1);

    liste_entrys = (GSList*)g_list_next(liste_entrys);
    gtk_editable_set_editable(GTK_EDITABLE(GTK_ENTRY(liste_entrys->data)), 0);
    gtk_entry_set_text(GTK_ENTRY(liste_entrys->data), "");

}

void call_selectionContact(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer _fenetrePrincipale)
{
    struct FenetrePrincipale* fenetreMain = (struct FenetrePrincipale*)_fenetrePrincipale;

    GtkTreeSelection* selection = gtk_tree_view_get_selection(treeview);

    if(gtk_tree_selection_get_selected (selection, &fenetreMain->model, &(fenetreMain->iter_selection)))
    {
        fenetreMain->path_selection = gtk_tree_path_copy(path);
    }
}

