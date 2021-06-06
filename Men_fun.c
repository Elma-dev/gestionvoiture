
#include "Men_fun.h"
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

void MENU(GtkWidget *widget,gpointer buttonclick);
void LocationVoitures(GtkWidget *widget,gpointer windo);
void Quitter(GtkWidget *widget, gpointer window);
void GestionVoitures(GtkWidget *widget,gpointer windo);
void GestionClient(GtkWidget *widget,gpointer windo);

/*************************************************************/
/********               Quitter FONCTION             *********/
/*************************************************************/
void Quitter(GtkWidget *widget, gpointer window){
    /**creat confirm window**/
    GtkWidget *msg=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"voulez vous vraiment quitter ce programe !!??");
    gtk_window_set_title(GTK_WINDOW(window),"Quitter!");
    gtk_dialog_run(GTK_DIALOG(msg));
    if(gtk_dialog_run(GTK_DIALOG(msg))==GTK_RESPONSE_YES)
            gtk_main_quit();

    else
        gtk_widget_destroy(msg);

}

/*************************************************************/
/********         LOCATION VOITURE FONCTION          *********/
/*************************************************************/
void LocationVoitures(GtkWidget *widget,gpointer windo){
    /**close previous window (menu)**/
    gtk_window_close(GTK_WINDOW(windo));
    /**Variables widget**/
     GtkWidget *window;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget **button;
    GtkWidget *label;
    GtkWidget *table;

    /**creat window**/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 500);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    /**creat layout**/
    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window), layout);
    gtk_widget_show(layout);
    /**creat image and put it in layout**/
    image = gtk_image_new_from_file("\car3.jpg");
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

    /**creat button and add event**/
    button=(GtkWidget**)malloc(6*sizeof(GtkWidget));
    //add elemnt and event
    button[0]= gtk_button_new_with_label("Visualiser contrat");
    g_signal_connect(button[0],"clicked",G_CALLBACK(gtk_main_quit),NULL);
    button[1]= gtk_button_new_with_label("Louer voiture");
    g_signal_connect(button[1],"clicked",G_CALLBACK(gtk_main_quit),NULL);
    button[2]= gtk_button_new_with_label("Retourner Voiture");
    g_signal_connect(button[2],"clicked",G_CALLBACK(gtk_main_quit),NULL);
    button[3]= gtk_button_new_with_label("Modifier contrat");
    g_signal_connect(button[3],"clicked",G_CALLBACK(gtk_main_quit),NULL);
    button[4]= gtk_button_new_with_label("Supprimer contrat");
    g_signal_connect(button[4],"clicked",G_CALLBACK(gtk_main_quit),NULL);
    button[5]= gtk_button_new_with_label("Retour");
    g_signal_connect(button[5],"clicked",G_CALLBACK(MENU),window);
    /**Creat Table**/
    table=gtk_table_new(1,11,2);
    //add elemnts
    gtk_table_attach(GTK_TABLE(table),button[0],0,2,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[1],2,4,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[2],4,6,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[3],6,8,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[4],8,10,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[5],10,11,6,7,GTK_FILL,GTK_FILL,10,0);
    //set col space
    gtk_table_set_col_spacings(GTK_TABLE(table),2);
    //put in layout
    gtk_layout_put(GTK_LAYOUT(layout), table, 0, 0);

    /**show your work**/
    gtk_widget_show_all(window);

}
/*************************************************************/
/********         GESTION VOITURE FONCTION          *********/
/*************************************************************/
void GestionVoitures(GtkWidget *widget,gpointer windo){
    /**close previous window (menu)**/
    gtk_window_close(GTK_WINDOW(windo));

    /**Variables widget**/
     GtkWidget *window;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget **button;
    GtkWidget *label;
    GtkWidget *table;

    /**creat window**/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 500);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    /**creat layout**/
    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window), layout);
    gtk_widget_show(layout);

    /**creat image and put it in layout**/
    image = gtk_image_new_from_file("\car5.jpg");
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

    /**creat button and add event**/
    button=(GtkWidget**)malloc(5*sizeof(GtkWidget));
    //add elemnt and event
    button[0]=gtk_button_new_with_label("Liste des voitures");
    g_signal_connect(button[0],"clicked",G_CALLBACK(ListVoiture),(gpointer)window);
    button[1]=gtk_button_new_with_label("Ajouter voiture");
    g_signal_connect(button[1],"clicked",G_CALLBACK(Ajoutvoiture),(gpointer)window);
    button[2]=gtk_button_new_with_label("Modifier voiture");
    g_signal_connect(button[2],"clicked",G_CALLBACK(modifier),(gpointer)window);
    button[3]=gtk_button_new_with_label("Supprimer voiture");
    g_signal_connect(button[3],"clicked",G_CALLBACK(Supprimer),(gpointer)window);
    button[4]=gtk_button_new_with_label("Retour");
    g_signal_connect(button[4],"clicked",G_CALLBACK(MENU),window);

    /**Creat Table**/
    table=gtk_table_new(1,9,2);
    //add elemnts
    gtk_table_attach(GTK_TABLE(table),button[0],0,2,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[1],2,4,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[2],4,6,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[3],6,8,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[4],8,9,6,7,GTK_FILL,GTK_FILL,10,0);
    //set col space
    gtk_table_set_col_spacings(GTK_TABLE(table),24);
    //put in layout
    gtk_layout_put(GTK_LAYOUT(layout), table, 0, 0);

    /**show your work**/
    gtk_widget_show_all(window);

}


/*************************************************************/
/********         GESTION CLIENT FONCTION          *********/
/*************************************************************/

void GestionClient(GtkWidget *widget,gpointer windo){
    /**close previous window (menu)**/
    gtk_window_close(GTK_WINDOW(windo));

    /**Variables widget**/
     GtkWidget *window4;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget **button;
    GtkWidget *label;
    GtkWidget *table;

    /**creat window**/
    window4 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window4), 1000, 500);
    gtk_window_set_position(GTK_WINDOW(window4), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window4),FALSE);

    /**creat layout**/
    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window4), layout);
    gtk_widget_show(layout);

    /**creat image and put it in layout**/
    image = gtk_image_new_from_file("car7.jpg");
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

    /**creat button and add event**/
    button=(GtkWidget**)malloc(5*sizeof(GtkWidget));
    //add elemnt and event
    button[0]=gtk_button_new_with_label("Liste des clients");
    g_signal_connect(button[0],"clicked",G_CALLBACK(gtk_main_quit),NULL);
    button[1]=gtk_button_new_with_label("Ajouter client");
    g_signal_connect(button[1],"clicked",G_CALLBACK(gtk_main_quit),NULL);
    button[2]=gtk_button_new_with_label("Modifier client");
    g_signal_connect(button[2],"clicked",G_CALLBACK(gtk_main_quit),NULL);
    button[3]=gtk_button_new_with_label("Supprimer client");
    g_signal_connect(button[3],"clicked",G_CALLBACK(gtk_main_quit),NULL);
    button[4]=gtk_button_new_with_label("Retour");
    g_signal_connect(button[4],"clicked",G_CALLBACK(MENU),window4);

    /**Creat Table**/
    table=gtk_table_new(1,9,2);
    //add elemnts
    gtk_table_attach(GTK_TABLE(table),button[0],0,2,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[1],2,4,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[2],4,6,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[3],6,8,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[4],8,9,6,7,GTK_FILL,GTK_FILL,10,0);
    //set col space
    gtk_table_set_col_spacings(GTK_TABLE(table),24);
    //put in layout
    gtk_layout_put(GTK_LAYOUT(layout), table, 0, 0);

    /**show your work**/
    gtk_widget_show_all(window4);

}

