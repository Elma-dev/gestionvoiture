#include <string.h>

void AjoutClient(GtkWidget *widget,gpointer window);
void ListClient(GtkWidget *widget,gpointer window);

void modifier2(GtkWidget *widget ,gpointer window);
void Chercher2(GtkWidget *widget,gpointer entry);
void ModifierClient(int id);

void Supprimer2(GtkWidget *widget ,gpointer window);
void Chercher_Supprimer2(GtkWidget *widget,gpointer entry);
void SupprimerClient(int id);


typedef struct Client
{
     int idClient;
     char nom[20];
     char prenom[20];
     int cin;
     char adresse[15];
     int telephone;
}client;

//window variable
GtkWidget *windowrecherche;

/*************************************************************/
/********          FONCTION AJOUT CLIENTS            *********/
/*************************************************************/
void AjoutClient(GtkWidget *widget,gpointer window){
    client clients;
    FILE *fichier;
    GtkWidget *windowdialog;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget *table;
    GtkWidget *label[6];
    GtkWidget *text;
    GtkWidget *idclient,*nom,*prenom,*cin,*adresse,*telephone;


    /***creat window dialog***/
    windowdialog=gtk_dialog_new_with_buttons("Ajouter Client",GTK_WINDOW(window),GTK_DIALOG_MODAL,"Valider",GTK_RESPONSE_OK,"Annuler",GTK_RESPONSE_CANCEL,NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowdialog),400,590);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowdialog),"add.png",NULL);
    /***layout and image***/
    layout=gtk_layout_new(NULL,NULL);
    image=gtk_image_new_from_file("ajouter_client.jpg");
    gtk_layout_put(GTK_LAYOUT(layout),image,0,0);
    /***label text***/
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>IdClient </b></span>",-1,NULL,NULL,NULL);
    label[0]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[0]),TRUE);
    text=g_locale_to_utf8("<span  foreground=\"yellow\"size=\"x-large\"><b>Nom </b></span>",-1,NULL,NULL,NULL);
    label[1]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[1]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Prenom </b></span>",-1,NULL,NULL,NULL);
    label[2]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[2]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Cin </b></span>",-1,NULL,NULL,NULL);
    label[3]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[3]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Adresse </b></span>",-1,NULL,NULL,NULL);
    label[4]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[4]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Telephone </b></span>",-1,NULL,NULL,NULL);
    label[5]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[5]),TRUE);
    //free point text
    g_free(text);
    /** Entry Variable **/
    idclient=gtk_entry_new();
    nom=gtk_entry_new();
    prenom=gtk_entry_new();
    cin=gtk_entry_new();
    adresse=gtk_entry_new();
    telephone=gtk_entry_new();
    /**place Holder**/
    /*gtk_entry_set_text(GTK_ENTRY(idvoiture),"id");
    gtk_entry_set_text(GTK_ENTRY(marque),"marque");
    gtk_entry_set_text(GTK_ENTRY(Nvoiture),"Numero Voiture");
    gtk_entry_set_text(GTK_ENTRY(colour),"Colour");
    gtk_entry_set_text(GTK_ENTRY(nplace),"nombre place");
    gtk_entry_set_text(GTK_ENTRY(prix),"Prix");
    gtk_entry_set_text(GTK_ENTRY(Enloca),"Oui/Non");*/
    /**creat table and add all label**/
    table=gtk_table_new(6,2,FALSE);
    gtk_table_attach_defaults(GTK_TABLE(table),label[0],0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),label[1],0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),label[2],0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),label[3],0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),label[4],0,1,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),label[5],0,1,5,6);

    /***Add Entry**/
    // Label : Entry
    gtk_table_attach_defaults(GTK_TABLE(table),idclient,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),nom,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),prenom,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),cin,1,2,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),adresse,1,2,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),telephone,1,2,5,6);
    //just spacings
    gtk_table_set_row_spacings (GTK_TABLE (table), 6);
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
            if(gtk_entry_get_text_length(GTK_ENTRY(idclient))==0||gtk_entry_get_text_length(GTK_ENTRY(nom))==0||gtk_entry_get_text_length(GTK_ENTRY(prenom))==0||gtk_entry_get_text_length(GTK_ENTRY(cin))==0||gtk_entry_get_text_length(GTK_ENTRY(adresse))==0||gtk_entry_get_text_length(GTK_ENTRY(telephone))==0){
                GtkWidget *error=gtk_message_dialog_new(GTK_WINDOW(windowdialog),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"L'un des champs est vide !!! \n Slvp rempli touts les champs !!");
                gtk_window_set_title(GTK_WINDOW(error), "Erreur");
                gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
                gtk_dialog_run(GTK_DIALOG(error));
                gtk_widget_destroy(error);
            }
        //else all entry give it to variable struct and saved in file
            else{
                clients.idClient=atoi(gtk_entry_get_text(GTK_ENTRY(idclient)));
                clients.cin=atoi(gtk_entry_get_text(GTK_ENTRY(cin)));
                clients.telephone=atoi(gtk_entry_get_text(GTK_ENTRY(telephone)));
                strcpy(clients.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
                strcpy(clients.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)));
                strcpy(clients.adresse,gtk_entry_get_text(GTK_ENTRY(adresse)));
                gtk_widget_destroy(windowdialog);
                fichier=fopen("Clients.txt","a+");
                fprintf(fichier,"\n");
                fprintf(fichier,"%d %s %s %d %s %d",clients.idClient,clients.nom,clients.prenom,clients.cin,clients.adresse,clients.telephone);

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
/********       FONCTION AFFICHE CLIENTS           *********/
/*************************************************************/
void ListClient(GtkWidget *widget,gpointer window){
    GtkWidget *affichwindow;
    GtkListStore *listStore;
    GtkWidget *listview;
    GtkWidget *Scrollbar;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;
    GdkColor color;
    client c1;
    FILE *fp=fopen("Clients.txt","r");

    /**creat window display list**/
    affichwindow=gtk_dialog_new_with_buttons("Liste des clients",GTK_WINDOW(window),GTK_DIALOG_MODAL,NULL);
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
    listStore=gtk_list_store_new(6,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT);
    //add list store inside list view
    listview=gtk_tree_view_new_with_model(GTK_TREE_MODEL(listStore));
    //creat cell and add title
    cell=gtk_cell_renderer_text_new();
    column=gtk_tree_view_column_new_with_attributes("IdClient",cell,"text",0,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("Nom",cell,"text",1,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("Prenom",cell,"text",2,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("Cin",cell,"text",3,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("Adresse",cell,"text",4,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(listview),column);
    column=gtk_tree_view_column_new_with_attributes("Telephone",cell,"text",5,NULL);
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
            fscanf(fp,"%d %s %s %d %s %d",&c1.idClient,c1.nom,c1.prenom,&c1.cin,c1.adresse,&c1.telephone);
            printf("%d %s %s %d %s %d\n",c1.idClient,c1.nom,c1.prenom,c1.cin,c1.adresse,c1.telephone);
            gtk_list_store_append(listStore,&pIter);
            gtk_list_store_set(listStore,&pIter,0,c1.idClient,1,c1.nom,2,c1.prenom,3,c1.cin,4,c1.adresse,5,c1.telephone,-1);
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
void modifier2(GtkWidget *widget ,gpointer window){

    GtkWidget *identry;
    GtkWidget *label[2];
    GtkWidget *Button;
    GtkWidget *grid;

    windowrecherche=gtk_dialog_new_with_buttons("Recherche_Par_Id",GTK_WINDOW(window),GTK_DIALOG_MODAL,NULL);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowrecherche),"recherche.png",NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowrecherche),270,100);
    Button=gtk_button_new_with_label("Chercher");
    label[0]=gtk_label_new("IdClient:");
    label[1]=gtk_label_new("Entrer id de client qui vous modifier:");
    identry=gtk_entry_new();
    grid=gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),label[1],0,0,2,1);
    gtk_grid_attach(GTK_GRID(grid),label[0],0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),identry,1,1,3,1);
    gtk_grid_attach(GTK_GRID(grid),Button,1,2,1,1);
    gtk_grid_set_row_spacing(GTK_GRID(grid),5);
    g_signal_connect(Button,"clicked",G_CALLBACK(Chercher2),(gpointer)identry);
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowrecherche)), grid, TRUE, TRUE, 0);
    gtk_widget_show_all(windowrecherche);

}

/**fonction search inside the file**/
void Chercher2(GtkWidget *widget,gpointer entry){
    FILE *fp=fopen("Clients.txt","r");
    GtkWidget *windowmodif;
    GtkWidget *error;
    GtkWidget *layout;
    int id;
    client info;
    int b=0;
    char string[500];
    while(fgets(string,500,fp)!=NULL){
        fscanf(fp,"%d",&id);
            //if id == entry (search id)
        if(id==atoi(gtk_entry_get_text(GTK_ENTRY(entry)))){
            fscanf(fp,"%s %s %d %s %d",info.nom,info.prenom,&info.cin,info.adresse,&info.telephone);
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
        ModifierClient(id);
        gtk_widget_destroy(GTK_WIDGET(windowrecherche));
    }


}

/** function modifier (display screen for edit previous entry**/
void ModifierClient(int id){
    char stri[20];
    client cli;
    FILE *fichier;
    FILE *fichier2;
    GtkWidget *windowdialog;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget *table;
    GtkWidget *label[6];
    GtkWidget *text;
    GtkWidget *idclient,*nom,*prenom,*cin,*adresse,*telephone;


    /***creat window dialog***/
    windowdialog=gtk_dialog_new_with_buttons("Modifier client",GTK_WINDOW(windowrecherche),GTK_DIALOG_MODAL,"Valider",GTK_RESPONSE_OK,"Annuler",GTK_RESPONSE_CANCEL,NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowdialog),400,590);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowdialog),"edit.png",NULL);
    /***layout and image***/
    layout=gtk_layout_new(NULL,NULL);
    image=gtk_image_new_from_file("modi_clie.jpg");
    gtk_layout_put(GTK_LAYOUT(layout),image,0,0);
    /***label text***/
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>IdClient </b></span>",-1,NULL,NULL,NULL);
    label[0]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[0]),TRUE);
    text=g_locale_to_utf8("<span  foreground=\"yellow\"size=\"x-large\"><b>Nom </b></span>",-1,NULL,NULL,NULL);
    label[1]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[1]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Prenom </b></span>",-1,NULL,NULL,NULL);
    label[2]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[2]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Cin </b></span>",-1,NULL,NULL,NULL);
    label[3]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[3]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Adresse </b></span>",-1,NULL,NULL,NULL);
    label[4]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[4]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Telephone </b></span>",-1,NULL,NULL,NULL);
    label[5]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[5]),TRUE);
    //free point text
    g_free(text);
    /** Entry Variable **/
    idclient=gtk_entry_new();
    nom=gtk_entry_new();
    prenom=gtk_entry_new();
    cin=gtk_entry_new();
    adresse=gtk_entry_new();
    telephone=gtk_entry_new();
    /**searche line information**/
    fichier=fopen("Clients.txt","r+");
    char string[500];
    while(fgets(string,500,fichier)!=NULL){
        fscanf(fichier,"%d %s %s %d %s %d",&cli.idClient,cli.nom,cli.prenom,&cli.cin,cli.adresse,&cli.telephone);
        if(id==cli.idClient)
            break;
    }
    fclose(fichier);
    /**place Holder**/
    //itoa fonction convert int to string !=atoi
    itoa(cli.idClient,stri,10);
    gtk_entry_set_text(GTK_ENTRY(idclient),stri);
    gtk_entry_set_text(GTK_ENTRY(nom),cli.nom);
    gtk_entry_set_text(GTK_ENTRY(prenom),cli.prenom);
    gtk_entry_set_text(GTK_ENTRY(adresse),cli.adresse);
    itoa(cli.cin,stri,10);
    gtk_entry_set_text(GTK_ENTRY(cin),stri);
    itoa(cli.telephone,stri,10);
    gtk_entry_set_text(GTK_ENTRY(telephone),stri);
    /**creat table and add all label**/
    table=gtk_table_new(6,2,FALSE);
    gtk_table_attach_defaults(GTK_TABLE(table),label[0],0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),label[1],0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),label[2],0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),label[3],0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),label[4],0,1,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),label[5],0,1,5,6);
    /***Add Entry**/
    // Label : Entry
    gtk_table_attach_defaults(GTK_TABLE(table),idclient,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),nom,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),prenom,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),cin,1,2,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),adresse,1,2,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),telephone,1,2,5,6);
    //just spacings
    gtk_table_set_row_spacings (GTK_TABLE (table), 6);
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
            if(gtk_entry_get_text_length(GTK_ENTRY(idclient))==0||gtk_entry_get_text_length(GTK_ENTRY(nom))==0||gtk_entry_get_text_length(GTK_ENTRY(prenom))==0||gtk_entry_get_text_length(GTK_ENTRY(cin))==0||gtk_entry_get_text_length(GTK_ENTRY(adresse))==0||gtk_entry_get_text_length(GTK_ENTRY(telephone))==0){
                GtkWidget *error=gtk_message_dialog_new(GTK_WINDOW(windowdialog),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"L'un des champs est vide !!! \n Slvp rempli touts les champs !!");
                gtk_window_set_title(GTK_WINDOW(error), "Erreur");
                gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
                gtk_dialog_run(GTK_DIALOG(error));
                gtk_widget_destroy(error);
            }
        //else all entry give it to variable struct and saved in file
            else{
                /**get modification information entry **/
                cli.idClient=atoi(gtk_entry_get_text(GTK_ENTRY(idclient)));
                cli.cin=atoi(gtk_entry_get_text(GTK_ENTRY(cin)));
                cli.telephone=atoi(gtk_entry_get_text(GTK_ENTRY(telephone)));
                strcpy(cli.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
                strcpy(cli.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)));
                strcpy(cli.adresse,gtk_entry_get_text(GTK_ENTRY(adresse)));
                gtk_widget_destroy(windowdialog);
                /**after enter accept temp file open & add the last modification & copie content of file1 to file temp**/
                fichier2=fopen("test2.txt","w");
                fprintf(fichier2,"\n");
                fprintf(fichier2,"%d %s %s %d %s %d",cli.idClient,cli.nom,cli.prenom,cli.cin,cli.adresse,cli.telephone);
                fichier=fopen("Clients.txt","r");
                while(!feof(fichier)){
                    fscanf(fichier,"%d %s %s %d %s %d",&cli.idClient,cli.nom,cli.prenom,&cli.cin,cli.adresse,&cli.telephone);
                    if(id!=cli.idClient){
                        fprintf(fichier2,"\n");
                        fprintf(fichier2,"%d %s %s %d %s %d",cli.idClient,cli.nom,cli.prenom,cli.cin,cli.adresse,cli.telephone);
                    }
                }
                fclose(fichier2);
                fclose(fichier);
                /** remove file1 and rename temp to file1**/
                remove("Clients.txt");
                rename("test2.txt","Clients.txt");
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
void Supprimer2(GtkWidget *widget ,gpointer window){

    GtkWidget *identry;
    GtkWidget *label[2];
    GtkWidget *Button;
    GtkWidget *grid;

    windowrecherche=gtk_dialog_new_with_buttons("Recherche_Par_Id",GTK_WINDOW(window),GTK_DIALOG_MODAL,NULL);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowrecherche),"recherche.png",NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowrecherche),270,100);
    Button=gtk_button_new_with_label("Chercher");
    label[0]=gtk_label_new("IdClient:");
    label[1]=gtk_label_new("Entrer id de client qui vous supprimer:");
    identry=gtk_entry_new();
    grid=gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),label[1],0,0,2,1);
    gtk_grid_attach(GTK_GRID(grid),label[0],0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),identry,1,1,3,1);
    gtk_grid_attach(GTK_GRID(grid),Button,1,2,1,1);
    gtk_grid_set_row_spacing(GTK_GRID(grid),5);
    g_signal_connect(Button,"clicked",G_CALLBACK(Chercher_Supprimer2),(gpointer)identry);
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowrecherche)), grid, TRUE, TRUE, 0);
    gtk_widget_show_all(windowrecherche);

}

/** same function with a little of modification in supprimerVoiture**/

void Chercher_Supprimer2(GtkWidget *widget,gpointer entry){
    FILE *fp=fopen("Clients.txt","r");
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
        SupprimerClient(id);
        gtk_widget_destroy(GTK_WIDGET(windowrecherche));
    }

}
void SupprimerClient(int id){
    GtkWidget *succeswindow;
    FILE *fichier1=fopen("Clients.txt","r+");
    FILE *fichier2=fopen("test2.txt","w");
    client c;
    while(!feof(fichier1)){
        fscanf(fichier1,"%d %s %s %d %s %d",&c.idClient,c.nom,c.prenom,&c.cin,c.adresse,&c.telephone);
        if(id!=c.idClient){
            fprintf(fichier2,"\n");
            fprintf(fichier2,"%d %s %s %d %s %d",c.idClient,c.nom,c.prenom,c.cin,c.adresse,c.telephone);
        }
    }
    fclose(fichier1);
    fclose(fichier2);

    remove("Clients.txt");
    rename("test2.txt","Clients.txt");
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

