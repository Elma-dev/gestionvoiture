#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>

void Ajoutvoiture(GtkWidget *widget,gpointer window);
void ListVoiture(GtkWidget *widget,gpointer window);
void modifier(GtkWidget *widget ,gpointer window);
void Chercher(GtkWidget *widget,gpointer entry);
void ModifierVoiture(int id);
void Chercher_Supprimer(GtkWidget *widget,gpointer entry);
void SupprimerVoiture(int id);

/*************************************************************/
/********                 GLOBAL VARIABLE            *********/
/*************************************************************/
typedef struct voiture{
    gint idVoiture;
    gchar marque[15];
    gchar nomVoiture[15];
    gchar color[7];
    gint nbpalces;
    gint prixJour;
    gchar enLocation[4];
}voiture;
//window variable
GtkWidget *windowrecherche;

/*************************************************************/
/********          FONCTION AJOUT VOITURE            *********/
/*************************************************************/
void Ajoutvoiture(GtkWidget *widget,gpointer window){
    voiture tomobil;
    FILE *fichier;
    GtkWidget *windowdialog;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget *table;
    GtkWidget *label[7];
    GtkWidget *text;
    GtkWidget *idvoiture,*marque,*Nvoiture,*colour,*nplace,*prix,*Enloca;


    /***creat window dialog***/
    windowdialog=gtk_dialog_new_with_buttons("Ajouter voiture",GTK_WINDOW(window),GTK_DIALOG_MODAL,"Valider",GTK_RESPONSE_OK,"Annuler",GTK_RESPONSE_CANCEL,NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowdialog),400,590);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowdialog),"add.png",NULL);
    /***layout and image***/
    layout=gtk_layout_new(NULL,NULL);
    image=gtk_image_new_from_file("cardialg.jpg");
    gtk_layout_put(GTK_LAYOUT(layout),image,0,0);
    /***label text***/
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>IdVoiture </b></span>",-1,NULL,NULL,NULL);
    label[0]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[0]),TRUE);
    text=g_locale_to_utf8("<span  foreground=\"yellow\"size=\"x-large\"><b>Marque </b></span>",-1,NULL,NULL,NULL);
    label[1]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[1]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Nom Voiture </b></span>",-1,NULL,NULL,NULL);
    label[2]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[2]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Colour </b></span>",-1,NULL,NULL,NULL);
    label[3]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[3]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Nombre Places </b></span>",-1,NULL,NULL,NULL);
    label[4]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[4]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Prix Jour </b></span>",-1,NULL,NULL,NULL);
    label[5]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[5]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>En Location</b></span>",-1,NULL,NULL,NULL);
    label[6]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[6]),TRUE);
    //free point text
    g_free(text);
    /** Entry Variable **/
    idvoiture=gtk_entry_new();
    marque=gtk_entry_new();
    Nvoiture=gtk_entry_new();
    colour=gtk_entry_new();
    nplace=gtk_entry_new();
    prix=gtk_entry_new();
    Enloca=gtk_entry_new();

    /**creat table and add all label**/
    table=gtk_table_new(7,2,FALSE);
    gtk_table_attach_defaults(GTK_TABLE(table),label[0],0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),label[1],0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),label[2],0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),label[3],0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),label[4],0,1,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),label[5],0,1,5,6);
    gtk_table_attach_defaults(GTK_TABLE(table),label[6],0,1,6,7);
    /***Add Entry**/
    // Label : Entry
    gtk_table_attach_defaults(GTK_TABLE(table),idvoiture,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),marque,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),Nvoiture,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),colour,1,2,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),nplace,1,2,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),prix,1,2,5,6);
    gtk_table_attach_defaults(GTK_TABLE(table),Enloca,1,2,6,7);
    //just spacings
    gtk_table_set_row_spacings (GTK_TABLE (table), 5);
    gtk_table_set_col_spacings (GTK_TABLE (table), 8);
    gtk_container_set_border_width (GTK_CONTAINER (table), 5);
    // put tabel inside layout
    gtk_layout_put(GTK_LAYOUT(layout),table,0,0);
    /**Add layout in window dialoge #gtk_container_add**/
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowdialog)), layout, TRUE, TRUE, 0);
    gtk_widget_show_all(windowdialog);
    /**while for boucle all time is correct **/
    while(1){
        //If the user presses a button ok --> and the entry empty --> creat window error
          if(gtk_dialog_run(GTK_DIALOG(windowdialog))==GTK_RESPONSE_OK){
            if(gtk_entry_get_text_length(GTK_ENTRY(idvoiture))==0||gtk_entry_get_text_length(GTK_ENTRY(nplace))==0||gtk_entry_get_text_length(GTK_ENTRY(prix))==0||gtk_entry_get_text_length(GTK_ENTRY(colour))==0||gtk_entry_get_text_length(GTK_ENTRY(Enloca))==0||gtk_entry_get_text_length(GTK_ENTRY(marque))==0||gtk_entry_get_text_length(GTK_ENTRY(Nvoiture))==0){
                GtkWidget *error=gtk_message_dialog_new(GTK_WINDOW(windowdialog),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"L'un des champs est vide !!! \n Slvp rempli touts les champs !!");
                gtk_window_set_title(GTK_WINDOW(error), "Erreur");
                gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
                gtk_dialog_run(GTK_DIALOG(error));
                gtk_widget_destroy(error);
            }
        //else all entry give it to variable struct and saved in file
            else{
                tomobil.idVoiture=atoi(gtk_entry_get_text(GTK_ENTRY(idvoiture)));
                tomobil.nbpalces=atoi(gtk_entry_get_text(GTK_ENTRY(nplace)));
                tomobil.prixJour=atoi(gtk_entry_get_text(GTK_ENTRY(prix)));
                strcpy(tomobil.color,gtk_entry_get_text(GTK_ENTRY(colour)));
                strcpy(tomobil.enLocation,gtk_entry_get_text(GTK_ENTRY(Enloca)));
                strcpy(tomobil.marque,gtk_entry_get_text(GTK_ENTRY(marque)));
                strcpy(tomobil.nomVoiture,gtk_entry_get_text(GTK_ENTRY(Nvoiture)));
                gtk_widget_destroy(windowdialog);
                fichier=fopen("Voitures.txt","a+");
                fprintf(fichier,"\n");
                fprintf(fichier,"%d %s %s %s %d %d %s",tomobil.idVoiture,tomobil.marque,tomobil.nomVoiture,tomobil.color,tomobil.nbpalces,tomobil.prixJour,tomobil.enLocation);

                fclose(fichier);
                break;
            }
          }
          //if pressed Cancel the window dialog close
        else{
            gtk_widget_destroy(windowdialog);
            break;
        }
    }
}
/*************************************************************/
/********       FONCTION AFFICHE VOITURES            *********/
/*************************************************************/
void ListVoiture(GtkWidget *widget,gpointer window){
    GtkWidget *affichwindow;
    GtkListStore *listStore;
    GtkWidget *listview;
    GtkWidget *Scrollbar;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;
    GdkColor color;
    voiture v1;
    FILE *fp=fopen("Voitures.txt","r");

    /**creat window display list**/
    affichwindow=gtk_dialog_new_with_buttons("Liste des voiture",GTK_WINDOW(window),GTK_DIALOG_MODAL,NULL);
    gtk_window_set_default_size(GTK_WINDOW(affichwindow),530,590);
    gtk_window_set_position(GTK_WINDOW(affichwindow),GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(affichwindow),"forms.png",NULL);
    gtk_container_set_border_width(GTK_CONTAINER(affichwindow),10);
    //set background-color
    color.pixel=0;
    color.red=12*12;
    color.green=0*0;
    color.blue=0*0;
    gtk_widget_modify_bg(GTK_WIDGET(affichwindow),GTK_STATE_NORMAL,&color);
    /**creat list view for see all information 7 is number of column & type of data**/
    listStore=gtk_list_store_new(7,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING);
    //add list store inside list view
    listview=gtk_tree_view_new_with_model(GTK_TREE_MODEL(listStore));
    //creat cell and add title
    cell=gtk_cell_renderer_text_new();
    column=gtk_tree_view_column_new_with_attributes("IdVoiture",cell,"text",0,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("Marque",cell,"text",1,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("NomVoiture",cell,"text",2,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("Couleur",cell,"text",3,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("NbPlaces",cell,"text",4,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("PrixJour",cell,"text",5,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("EnLocation",cell,"text",6,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);

    /**scrollbar important thing's**/
    Scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(Scrollbar),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(Scrollbar),listview);

    //variable
    GtkTreeIter pIter;
    gchar str[300];
    /** while end of file : read all info in file **/
    while(fgets(str,300,fp)!=NULL){
        if(str[0]!=' '){
            fscanf(fp,"%d %s %s %s %d %d %s",&v1.idVoiture,v1.marque,v1.nomVoiture,v1.color,&v1.nbpalces,&v1.prixJour,v1.enLocation);
            printf("%d %s %s %s %d %d %s\n",v1.idVoiture,v1.marque,v1.nomVoiture,v1.color,v1.nbpalces,v1.prixJour,v1.enLocation);
            gtk_list_store_append(listStore,&pIter);
            gtk_list_store_set(listStore,&pIter,0,v1.idVoiture,1,v1.marque,2,v1.nomVoiture,3,v1.color,4,v1.nbpalces,5,v1.prixJour,6,v1.enLocation,-1);
        }
    }
    fclose(fp);
    /**add all to window display**/
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(affichwindow)), Scrollbar, TRUE, TRUE, 0);
    gtk_widget_show_all(affichwindow);

}
/*************************************************************/
/********       FONCTION Modifier VOITURES           *********/
/*************************************************************/
void modifier(GtkWidget *widget ,gpointer window){

    GtkWidget *identry;
    GtkWidget *label[2];
    GtkWidget *Button;
    GtkWidget *grid;

    windowrecherche=gtk_dialog_new_with_buttons("Recherche_Par_Id",GTK_WINDOW(window),GTK_DIALOG_MODAL,NULL);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowrecherche),"recherche.png",NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowrecherche),270,100);
    Button=gtk_button_new_with_label("Chercher");
    label[0]=gtk_label_new("IdVoiture:");
    label[1]=gtk_label_new("Entrer id de voiture qui vous modifier:");
    identry=gtk_entry_new();
    grid=gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),label[1],0,0,2,1);
    gtk_grid_attach(GTK_GRID(grid),label[0],0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),identry,1,1,3,1);
    gtk_grid_attach(GTK_GRID(grid),Button,1,2,1,1);
    gtk_grid_set_row_spacing(GTK_GRID(grid),5);
    g_signal_connect(Button,"clicked",G_CALLBACK(Chercher),(gpointer)identry);
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowrecherche)), grid, TRUE, TRUE, 0);
    gtk_widget_show_all(windowrecherche);

}

/**fonction search inside the file**/
void Chercher(GtkWidget *widget,gpointer entry){
    FILE *fp=fopen("Voitures.txt","r");
    GtkWidget *windowmodif;
    GtkWidget *error;
    GtkWidget *layout;
    int id;
    voiture info;
    int b=0;
    char string[500];
    while(fgets(string,500,fp)!=NULL){
        fscanf(fp,"%d",&id);
            //if id == entry (search id)
        if(id==atoi(gtk_entry_get_text(GTK_ENTRY(entry)))){
            fscanf(fp,"%s %s %s %d %d %s",info.marque,info.nomVoiture,info.color,&info.nbpalces,&info.prixJour,info.enLocation);
            b=1;
            break;
        }
    }
    fclose(fp);
    //b==0 error (id n'exit pas)
    if(b==0){
        error=gtk_message_dialog_new(GTK_WINDOW(windowrecherche),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"ID INCONUU!");
        gtk_window_set_title(GTK_WINDOW(error), "Erreur");
        gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
        gtk_dialog_run(GTK_DIALOG(error));
        gtk_widget_destroy(error);
    }
    else{
        ModifierVoiture(id);
        gtk_widget_destroy(GTK_WIDGET(windowrecherche));
    }


}

/** function modifier (display screen for edit previous entry**/
void ModifierVoiture(int id){
    char stri[20];
    voiture tomobil;
    FILE *fichier;
    FILE *fichier2;
    GtkWidget *windowdialog;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget *table;
    GtkWidget *label[7];
    GtkWidget *text;
    GtkWidget *idvoiture,*marque,*Nvoiture,*colour,*nplace,*prix,*Enloca;


    /***creat window dialog***/
    windowdialog=gtk_dialog_new_with_buttons("Modifier voiture",GTK_WINDOW(windowrecherche),GTK_DIALOG_MODAL,"Valider",GTK_RESPONSE_OK,"Annuler",GTK_RESPONSE_CANCEL,NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowdialog),400,590);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowdialog),"edit.png",NULL);
    /***layout and image***/
    layout=gtk_layout_new(NULL,NULL);
    image=gtk_image_new_from_file("modifier.jpg");
    gtk_layout_put(GTK_LAYOUT(layout),image,0,0);
    /***label text***/
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>IdVoiture </b></span>",-1,NULL,NULL,NULL);
    label[0]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[0]),TRUE);
    text=g_locale_to_utf8("<span  foreground=\"yellow\"size=\"x-large\"><b>Marque </b></span>",-1,NULL,NULL,NULL);
    label[1]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[1]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Nom Voiture </b></span>",-1,NULL,NULL,NULL);
    label[2]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[2]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Colour </b></span>",-1,NULL,NULL,NULL);
    label[3]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[3]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Nombre Places </b></span>",-1,NULL,NULL,NULL);
    label[4]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[4]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Prix Jour </b></span>",-1,NULL,NULL,NULL);
    label[5]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[5]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>En Location </b></span>",-1,NULL,NULL,NULL);
    label[6]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[6]),TRUE);
    //free point text
    g_free(text);
    /** Entry Variable **/
    idvoiture=gtk_entry_new();
    marque=gtk_entry_new();
    Nvoiture=gtk_entry_new();
    colour=gtk_entry_new();
    nplace=gtk_entry_new();
    prix=gtk_entry_new();
    Enloca=gtk_entry_new();
    /**searche line information**/
    fichier=fopen("Voitures.txt","r+");
    char string[500];
    while(fgets(string,500,fichier)!=NULL){
        fscanf(fichier,"%d %s %s %s %d %d %s",&tomobil.idVoiture,tomobil.marque,tomobil.nomVoiture,tomobil.color,&tomobil.nbpalces,&tomobil.prixJour,tomobil.enLocation);
        if(id==tomobil.idVoiture)
            break;
    }
    fclose(fichier);
    /**place Holder**/
    //itoa fonction convert int to string !=atoi
    itoa(tomobil.idVoiture,stri,10);
    gtk_entry_set_text(GTK_ENTRY(idvoiture),stri);
    gtk_entry_set_text(GTK_ENTRY(marque),tomobil.marque);
    gtk_entry_set_text(GTK_ENTRY(Nvoiture),tomobil.nomVoiture);
    gtk_entry_set_text(GTK_ENTRY(colour),tomobil.color);
    itoa(tomobil.nbpalces,stri,10);
    gtk_entry_set_text(GTK_ENTRY(nplace),stri);
    itoa(tomobil.prixJour,stri,10);
    gtk_entry_set_text(GTK_ENTRY(prix),stri);
    gtk_entry_set_text(GTK_ENTRY(Enloca),tomobil.enLocation);
    /**creat table and add all label**/
    table=gtk_table_new(7,2,FALSE);
    gtk_table_attach_defaults(GTK_TABLE(table),label[0],0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),label[1],0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),label[2],0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),label[3],0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),label[4],0,1,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),label[5],0,1,5,6);
    gtk_table_attach_defaults(GTK_TABLE(table),label[6],0,1,6,7);
    /***Add Entry**/
    // Label : Entry
    gtk_table_attach_defaults(GTK_TABLE(table),idvoiture,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),marque,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),Nvoiture,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),colour,1,2,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),nplace,1,2,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),prix,1,2,5,6);
    gtk_table_attach_defaults(GTK_TABLE(table),Enloca,1,2,6,7);
    //just spacings
    gtk_table_set_row_spacings (GTK_TABLE (table), 5);
    gtk_table_set_col_spacings (GTK_TABLE (table), 8);
    gtk_container_set_border_width (GTK_CONTAINER (table), 5);
    // put tabel inside layout
    gtk_layout_put(GTK_LAYOUT(layout),table,0,0);
    /**Add layout in window dialoge #gtk_container_add**/
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowdialog)), layout, TRUE, TRUE, 0);
    gtk_widget_show_all(windowdialog);
    /**while for boucle all time is correct **/
    while(1){
        //If the user presses a button ok --> and the entry empty --> creat window error
          if(gtk_dialog_run(GTK_DIALOG(windowdialog))==GTK_RESPONSE_OK){
            if(gtk_entry_get_text_length(GTK_ENTRY(idvoiture))==0||gtk_entry_get_text_length(GTK_ENTRY(nplace))==0|gtk_entry_get_text_length(GTK_ENTRY(prix))==0|gtk_entry_get_text_length(GTK_ENTRY(colour))==0|gtk_entry_get_text_length(GTK_ENTRY(Enloca))==0|gtk_entry_get_text_length(GTK_ENTRY(marque))==0|gtk_entry_get_text_length(GTK_ENTRY(Nvoiture))==0){
                GtkWidget *error=gtk_message_dialog_new(GTK_WINDOW(windowdialog),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"L'un des champs est vide !!! \n Slvp rempli touts les champs !!");
                gtk_window_set_title(GTK_WINDOW(error), "Erreur");
                gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
                gtk_dialog_run(GTK_DIALOG(error));
                gtk_widget_destroy(error);
            }
        //else all entry give it to variable struct and saved in file
            else{
                /**get modification information entry **/
                tomobil.idVoiture=atoi(gtk_entry_get_text(GTK_ENTRY(idvoiture)));
                tomobil.nbpalces=atoi(gtk_entry_get_text(GTK_ENTRY(nplace)));
                tomobil.prixJour=atoi(gtk_entry_get_text(GTK_ENTRY(prix)));
                strcpy(tomobil.color,gtk_entry_get_text(GTK_ENTRY(colour)));
                strcpy(tomobil.enLocation,gtk_entry_get_text(GTK_ENTRY(Enloca)));
                strcpy(tomobil.marque,gtk_entry_get_text(GTK_ENTRY(marque)));
                strcpy(tomobil.nomVoiture,gtk_entry_get_text(GTK_ENTRY(Nvoiture)));
                gtk_widget_destroy(windowdialog);
                /**after enter accept temp file open & add the last modification & copie content of file1 to file temp**/
                fichier2=fopen("test2.txt","w");
                fprintf(fichier2,"\n");
                fprintf(fichier2,"%d %s %s %s %d %d %s",tomobil.idVoiture,tomobil.marque,tomobil.nomVoiture,tomobil.color,tomobil.nbpalces,tomobil.prixJour,tomobil.enLocation);
                fichier=fopen("Voitures.txt","r");
                while(!feof(fichier)){
                    fscanf(fichier,"%d %s %s %s %d %d %s",&tomobil.idVoiture,tomobil.marque,tomobil.nomVoiture,tomobil.color,&tomobil.nbpalces,&tomobil.prixJour,tomobil.enLocation);
                    if(id!=tomobil.idVoiture){
                        fprintf(fichier2,"\n");
                        fprintf(fichier2,"%d %s %s %s %d %d %s",tomobil.idVoiture,tomobil.marque,tomobil.nomVoiture,tomobil.color,tomobil.nbpalces,tomobil.prixJour,tomobil.enLocation);
                    }
                }
                fclose(fichier2);
                fclose(fichier);
                /** remove file1 and rename temp to file1**/
                remove("Voitures.txt");
                rename("test2.txt","Voitures.txt");
                break;
            }
          }
          //if pressed Cancel the window dialog close
        else{
            gtk_widget_destroy(windowdialog);
            break;
        }
    }
}
/*************************************************************/
/********       FONCTION SUPPRIMER VOITURES          *********/
/*************************************************************/
void Supprimer(GtkWidget *widget ,gpointer window){

    GtkWidget *identry;
    GtkWidget *label[2];
    GtkWidget *Button;
    GtkWidget *grid;

    windowrecherche=gtk_dialog_new_with_buttons("Recherche_Par_Id",GTK_WINDOW(window),GTK_DIALOG_MODAL,NULL);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowrecherche),"recherche.png",NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowrecherche),270,100);
    Button=gtk_button_new_with_label("Chercher");
    label[0]=gtk_label_new("IdVoiture:");
    label[1]=gtk_label_new("Entrer id de voiture qui vous supprimer:");
    identry=gtk_entry_new();
    grid=gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),label[1],0,0,2,1);
    gtk_grid_attach(GTK_GRID(grid),label[0],0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),identry,1,1,3,1);
    gtk_grid_attach(GTK_GRID(grid),Button,1,2,1,1);
    gtk_grid_set_row_spacing(GTK_GRID(grid),5);
    g_signal_connect(Button,"clicked",G_CALLBACK(Chercher_Supprimer),(gpointer)identry);
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowrecherche)), grid, TRUE, TRUE, 0);
    gtk_widget_show_all(windowrecherche);

}

/** same function with a little of modification in supprimerVoiture**/

void Chercher_Supprimer(GtkWidget *widget,gpointer entry){
    FILE *fp=fopen("Voitures.txt","r");
    GtkWidget *error;
    GtkWidget *layout;
    int id;
    voiture info;
    int b=0;
    char string[500];
    while(fgets(string,500,fp)!=NULL){
        fscanf(fp,"%d",&id);
        if(id==atoi(gtk_entry_get_text(GTK_ENTRY(entry)))){
            b=1;
            break;
        }
    }
    fclose(fp);
    if(b==0){
        error=gtk_message_dialog_new(GTK_WINDOW(windowrecherche),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"ID INCONUU!");
        gtk_window_set_title(GTK_WINDOW(error), "Erreur");
        gtk_dialog_run(GTK_DIALOG(error));
        gtk_widget_destroy(error);
    }
    else{
        SupprimerVoiture(id);
        gtk_widget_destroy(GTK_WIDGET(windowrecherche));
    }

}
void SupprimerVoiture(int id){
    GtkWidget *succeswindow;
    FILE *fichier1=fopen("Voitures.txt","r+");
    FILE *fichier2=fopen("test2.txt","w");
    voiture v;
    while(!feof(fichier1)){
        fscanf(fichier1,"%d %s %s %s %d %d %s",&v.idVoiture,v.marque,v.nomVoiture,v.color,&v.nbpalces,&v.prixJour,v.enLocation);
        if(id!=v.idVoiture){
            fprintf(fichier2,"\n");
            fprintf(fichier2,"%d %s %s %s %d %d %s",v.idVoiture,v.marque,v.nomVoiture,v.color,v.nbpalces,v.prixJour,v.enLocation);
        }
    }
    fclose(fichier1);
    fclose(fichier2);

    remove("Voitures.txt");
    rename("test2.txt","Voitures.txt");
    //creat succes window
    succeswindow=gtk_message_dialog_new(GTK_WINDOW(windowrecherche),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_NONE,"Operation reussie .");
    GdkColor color;
    color.pixel=0;
    color.red=124*124;
    color.green=252*252;
    color.blue=0*0;
    gtk_widget_modify_bg(GTK_WIDGET(succeswindow),GTK_STATE_NORMAL,&color);
    gtk_window_set_icon_from_file(GTK_WINDOW(succeswindow),"checked.png",NULL);
    gtk_dialog_run(GTK_DIALOG(succeswindow));
    gtk_widget_destroy(GTK_WIDGET(succeswindow));
}


