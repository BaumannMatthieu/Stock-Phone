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

// Callback
void detruireFenetre(GtkWidget *_Widget, gpointer _Data);

int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);

    struct FenetrePrincipale* mainFenetre = creerFenetrePrincipale();

    g_signal_connect(G_OBJECT(mainFenetre->fenetre), "destroy", G_CALLBACK(detruireFenetre), NULL);

    gtk_main();

    return EXIT_SUCCESS;
}

// Callback : destruction de fenetre principale
void detruireFenetre(GtkWidget *_Widget, gpointer _Data)
{
    gtk_main_quit();
}
