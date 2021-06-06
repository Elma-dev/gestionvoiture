#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "Men_fun.h"


/*************************************************************/
/********                    MENU FONCTION           *********/
/*************************************************************/

void MENU(GtkWidget *widget,gpointer window){
    /**close previous window (menu)**/
    gtk_window_close(GTK_WINDOW(window));

    /**Variables widget**/
     GtkWidget *wind2;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget **button;
    GtkWidget *table;

    /**creat window**/
    wind2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(wind2), 1000, 500);
    gtk_window_set_position(GTK_WINDOW(wind2), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(wind2),FALSE);
    gtk_window_set_title(GTK_WINDOW(wind2),"Gestion voiture MENU");
    gtk_window_set_icon_from_file(GTK_WINDOW(wind2),"logo.png",NULL);

    /**creat layout**/
    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (wind2), layout);
    gtk_widget_show(layout);

    /**creat image and put it in layout**/
    image = gtk_image_new_from_file("\Menu2.jpg");
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

    /**creat button and add event**/
    button=(GtkWidget**)malloc(4*sizeof(GtkWidget));
    //add elemnt and event
    button[0]=gtk_button_new_with_label("Location");
    button[1]=gtk_button_new_with_label("Gestion voitures");
    button[2]=gtk_button_new_with_label("Gestion client");
    button[3]=gtk_button_new_with_label("Quitter");
    g_signal_connect(button[0],"clicked",G_CALLBACK(LocationVoitures),(gpointer)wind2);
    g_signal_connect(button[1],"clicked",G_CALLBACK(GestionVoitures),(gpointer)wind2);
    g_signal_connect(button[2],"clicked",G_CALLBACK(GestionClient),(gpointer)wind2);
    g_signal_connect(button[3],"clicked",G_CALLBACK(Quitter),(gpointer)wind2);

    /**Creat Table**/
    table=gtk_table_new(1,10,2);
    //add elemnts

    gtk_table_attach(GTK_TABLE(table),button[0],0,3,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[1],3,6,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[2],6,9,6,7,GTK_FILL,GTK_FILL,10,0);
    gtk_table_attach(GTK_TABLE(table),button[3],9,10,6,7,GTK_FILL,GTK_FILL,10,0);
    //ser col spacings
    gtk_table_set_col_spacings(GTK_TABLE(table),10);
    //put in layout
    gtk_layout_put(GTK_LAYOUT(layout), table, 0, 0);

    /**show your work**/
    gtk_widget_show_all(wind2);

}

int main(int argc,char **argv)
{
    gtk_init(&argc,&argv);

    /*************************************************************/
    /********                    CREAT WINDOW            *********/
    /*************************************************************/


    GtkWidget *win1=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win1),"Gestion de location de voitures ");
    gtk_window_set_default_size(GTK_WINDOW(win1),1000,500);
    gtk_window_set_resizable(GTK_WINDOW(win1),FALSE);
    gtk_window_set_position(GTK_WINDOW(win1),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(win1),40);
    gtk_window_set_icon_from_file(GTK_WINDOW(win1),"logo.png",NULL);
    GdkColor color;
    color.pixel=0;
    color.red=255*255;
    color.green=244*244;
    color.blue=203*203;
    gtk_widget_modify_bg(GTK_WIDGET(win1),GTK_STATE_NORMAL,&color);


    /*************************************************************/
    /********                    CREAT LABEL             *********/
    /*************************************************************/

    GtkWidget **label=(GtkWidget**)malloc(4*sizeof(GtkWidget));
    gchar *text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>ELMAJJODI Abdeljalil</b></span>\n <span face=\"Verdana\" foreground=\"#39b500\" size=\"x-large\">SMI4\n2020|2021</span>\n", -1, NULL, NULL, NULL);
    label[0]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[0]),TRUE);
    gtk_label_set_justify(GTK_LABEL(label[0]),GTK_JUSTIFY_LEFT);

    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>Pr.ELOUAFDI Fouad</b></span>\n <span face=\"Verdana\" foreground=\"#344ceb\" size=\"x-large\">Faculté des sciences d'Agadir\nDépartement Informatique</span>\n", -1, NULL, NULL, NULL);
    label[1]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[1]),TRUE);
    gtk_label_set_justify(GTK_LABEL(label[1]),GTK_JUSTIFY_LEFT);

    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#424245\" size=\"xx-large\"><b>Mini-Projet en Langage C</b></span>\n <span face=\"Verdana\" foreground=\"#727273\" size=\"x-large\">Gestion de location de voitures</span>\n", -1, NULL, NULL, NULL);
    label[2]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[2]),TRUE);
    gtk_label_set_justify(GTK_LABEL(label[2]),GTK_JUSTIFY_LEFT);

    text=g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#E412C8\" size=\"xx-large\"><b>MASSOUAD Nouhaila</b></span>\n <span face=\"Verdana\" foreground=\"#39b500\" size=\"x-large\">SMI4\n2020|2021</span>\n", -1, NULL, NULL, NULL);
    label[3]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[3]),TRUE);
    gtk_label_set_justify(GTK_LABEL(label[3]),GTK_JUSTIFY_LEFT);

    g_free(text);



    /*************************************************************/
    /********                    CREAT BUTTON             ********/
    /*************************************************************/

    GtkWidget *button=gtk_button_new_with_label("Clicker ici");
    g_signal_connect(button,"clicked",G_CALLBACK(MENU),(gpointer)win1);


    /*************************************************************/
    /********                    CREAT BOX               *********/
    /*************************************************************/
    GtkWidget *box=gtk_box_new(0,5);
    gtk_box_pack_start(GTK_BOX(box),button,0,0,0);
    gtk_box_pack_start(GTK_BOX(box),label[0],0,0,0);
    gtk_box_pack_start(GTK_BOX(box),label[3],0,0,10);
    gtk_box_pack_start(GTK_BOX(box),label[1],0,0,10);
    gtk_box_pack_start(GTK_BOX(box),label[2],0,0,0);
    gtk_container_add(GTK_CONTAINER(win1),box);

    /*************************************************************/
    /********                   SHOW THE WINDOW          *********/
    /*************************************************************/
    gtk_widget_show_all(win1);
    gtk_main();

    return 0;
}
