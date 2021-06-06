#include <string.h>
typedef struct information{
    char nom[1000];
    char prenom[1000];
    char marque[1000];
    char nom_voiture[1000];
    char coleur[1000];
}info;
typedef struct noeudclient{
    char nom[20];
    char prenom[20];
    struct noeudclient *next;
}noeud;

typedef struct noeudvoiture{
    char nomVoiture[15];
    char color[7];
    char marque[15];
    char enLocation[4];
    struct noeudvoiture *next;
}noeudvoi;

typedef struct{
    int j,m,a;
}date;
typedef struct contratLocation
{
     float numContrat;
     int idVoiture;
     int idClient;
     date debut;
     date fin;
     int cout;
} contrat;
//variable
GtkWidget *windowsucces;
info form;
GtkWidget *entry[2];
GtkWidget *windowrecherche2;

void ContratWindow(GtkWidget *widget ,gpointer windowloca);
void freenoeud(noeud *head);
noeud *append(noeud *head,client cli);
noeudvoi *app(noeud* tete,voiture voi);
int recherche_client(info form);
int recherche_voiture(info form);
void Modifier_Enlocation(info select);
void Retourner_Voiture(GtkWidget *widget,gpointer wind);
void entry_len();
void Supprimer_contrat(double N_contrat);
void Enlocation_non(int);
void modifierloca(GtkWidget *widget ,gpointer window);
void ChercherContrat(GtkWidget *widget,gpointer entry);
void modifierwindow(float numcontrat);
void ChercherContrat2(GtkWidget *widget,gpointer entry);
void Suprimaloca(GtkWidget *widget ,gpointer window);
void affiche_contrat(contrat ser);
void ChercherContrat3(GtkWidget *widget,gpointer entry);
void visualiser(GtkWidget *widget,gpointer window);


void Louer_Voiture(GtkWidget *widget , gpointer window){

    GtkWidget *windowinfo;
    GtkWidget *layout;
    GtkWidget *image;
    GtkWidget *label[5];
    GtkWidget *text;
    GtkWidget *Nom,*Prenom,*Marque,*N_voi,*Coleur;
    GtkWidget *table;


    windowinfo=gtk_dialog_new_with_buttons("informations",GTK_WINDOW(window),GTK_DIALOG_MODAL,"Valider",GTK_RESPONSE_OK,"Annuler",GTK_RESPONSE_CANCEL,NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowinfo),400,590);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowinfo),"ajouter-c.png",NULL);


    image=gtk_image_new_from_file("Louer.jpg");

    layout=gtk_layout_new(NULL,NULL);
    gtk_layout_put(GTK_LAYOUT(layout),image,0,0);

    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Nom </b></span>",-1,NULL,NULL,NULL);
    label[0]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[0]),1);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Prenom </b></span>",-1,NULL,NULL,NULL);
    label[1]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[1]),1);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Marque Voiture </b></span>",-1,NULL,NULL,NULL);
    label[2]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[2]),1);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Nom Voiture </b></span>",-1,NULL,NULL,NULL);
    label[3]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[3]),1);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Coleur </b></span>",-1,NULL,NULL,NULL);
    label[4]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[4]),1);

    g_free(text);

    /***Creat entry***/
     Nom=gtk_entry_new();
     Prenom=gtk_entry_new();
     Marque=gtk_entry_new();
     N_voi=gtk_entry_new();
     Coleur=gtk_entry_new();

     /***Creat table ***/
     table=gtk_table_new(5,2,FALSE);
     gtk_table_attach_defaults(GTK_TABLE(table),label[0],0,1,0,1);
     gtk_table_attach_defaults(GTK_TABLE(table),label[1],0,1,1,2);
     gtk_table_attach_defaults(GTK_TABLE(table),label[2],0,1,2,3);
     gtk_table_attach_defaults(GTK_TABLE(table),label[3],0,1,3,4);
     gtk_table_attach_defaults(GTK_TABLE(table),label[4],0,1,4,5);

     gtk_table_attach_defaults(GTK_TABLE(table),Nom,1,2,0,1);
     gtk_table_attach_defaults(GTK_TABLE(table),Prenom,1,2,1,2);
     gtk_table_attach_defaults(GTK_TABLE(table),Marque,1,2,2,3);
     gtk_table_attach_defaults(GTK_TABLE(table),N_voi,1,2,3,4);
     gtk_table_attach_defaults(GTK_TABLE(table),Coleur,1,2,4,5);
     //set spacw and border with cell;
     gtk_container_set_border_width(GTK_CONTAINER(table),5);
     gtk_table_set_row_spacings(GTK_TABLE(table),8);
     gtk_table_set_col_spacings(GTK_TABLE(table),8);

     /*** add table inside layout***/
     gtk_layout_put(GTK_LAYOUT(layout),table,0,0);
     gtk_box_pack_start((GtkBox*)(GtkDialog*)(gtk_dialog_get_content_area(windowinfo)),layout,TRUE,TRUE,0);
     gtk_widget_show_all(windowinfo);

        int h=0;
     while(1){
        if(gtk_dialog_run(GTK_DIALOG(windowinfo))==GTK_RESPONSE_OK){
            if(gtk_entry_get_text_length(GTK_ENTRY(Nom))==0||gtk_entry_get_text_length(GTK_ENTRY(Prenom))==0||gtk_entry_get_text_length(GTK_ENTRY(N_voi))==0||gtk_entry_get_text_length(GTK_ENTRY(Marque))==0||gtk_entry_get_text_length(GTK_ENTRY(Coleur))==0){
                GtkWidget *error=gtk_message_dialog_new(GTK_WINDOW(windowinfo),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"L'un des champs est vide !!! \n Slvp rempli touts les champs !!");
                gtk_window_set_title(GTK_WINDOW(error), "Erreur");
                gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
                gtk_dialog_run(GTK_DIALOG(error));
                gtk_widget_destroy(error);
            }else{
                strcpy(form.nom,gtk_entry_get_text(GTK_ENTRY(Nom)));
                strcpy(form.prenom,gtk_entry_get_text(GTK_ENTRY(Prenom)));
                strcpy(form.marque,gtk_entry_get_text(GTK_ENTRY(Marque)));
                strcpy(form.nom_voiture,gtk_entry_get_text(GTK_ENTRY(N_voi)));
                strcpy(form.coleur,gtk_entry_get_text(GTK_ENTRY(Coleur)));
                if(recherche_client(form)){
                    if(recherche_voiture(form)==1){
                        gtk_widget_destroy(GTK_WINDOW(windowinfo));
                        h=1;
                        break;
                    }
                    else if(recherche_voiture(form)==2){
                        gtk_widget_destroy(GTK_WINDOW(windowinfo));
                        h=2;
                        break;
                    }
                    else{
                        gtk_widget_destroy(GTK_WINDOW(windowinfo));
                        h=3;
                        break;
                    }
                }
                else{
                    h=4;
                    gtk_widget_destroy(GTK_WINDOW(windowinfo));
                    break;
                }
            }
        }
        else{
            gtk_widget_destroy(windowinfo);
            break;
        }
     }

     if(h==2){
        windowsucces=gtk_dialog_new_with_buttons("valide",GTK_WINDOW(window),GTK_DIALOG_MODAL,NULL);
        gtk_window_set_default_size(GTK_WINDOW(windowsucces),270,80);
        gtk_window_set_icon_from_file(GTK_WINDOW(windowsucces),"checked.png",NULL);
        GtkWidget *button=gtk_button_new_with_label("Valider!");
        GtkWidget *textlabel=gtk_label_new("\tClicker button valider pour cree contrat.");
        GtkWidget *grid=gtk_grid_new();
        gtk_grid_attach(GTK_GRID(grid),textlabel,0,0,2,1);
        gtk_grid_attach(GTK_GRID(grid),button,1,2,1,1);
        gtk_grid_set_row_spacing(GTK_GRID(grid),5);
        g_signal_connect(button,"clicked",G_CALLBACK(ContratWindow),window);
        gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowsucces)), grid, TRUE, TRUE, 0);
        gtk_widget_show_all(windowsucces);
     }
     else if(h==1){
        windowsucces=gtk_dialog_new_with_buttons("ERREUR",GTK_WINDOW(window),GTK_DIALOG_MODAL,"Valide",GTK_RESPONSE_OK,NULL);
        gtk_window_set_default_size(GTK_WINDOW(windowsucces),270,80);
        gtk_window_set_icon_from_file(GTK_WINDOW(windowsucces),"error.png",NULL);
        GtkWidget *textlabel=gtk_label_new("\tLa voiture n\'est pas disponible.");
        gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowsucces)), textlabel, TRUE, TRUE, 0);
        gtk_widget_show_all(windowsucces);
        if(gtk_dialog_run(GTK_DIALOG(windowsucces))==GTK_RESPONSE_OK)
            gtk_widget_destroy(windowsucces);
     }
     else if(h==3){
        windowsucces=gtk_dialog_new_with_buttons("ERREUR",GTK_WINDOW(window),GTK_DIALOG_MODAL,"Valide",GTK_RESPONSE_OK,NULL);
        gtk_window_set_default_size(GTK_WINDOW(windowsucces),270,80);
        gtk_window_set_icon_from_file(GTK_WINDOW(windowsucces),"error.png",NULL);
        GtkWidget *textlabel=gtk_label_new("\tla voiture demandee n existe pas.");
        gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowsucces)), textlabel, TRUE, TRUE, 0);
        gtk_widget_show_all(windowsucces);
        if(gtk_dialog_run(GTK_DIALOG(windowsucces))==GTK_RESPONSE_OK)
            gtk_widget_destroy(windowsucces);
     }
     else if(h==4){
        windowsucces=gtk_dialog_new_with_buttons("ERREUR",GTK_WINDOW(window),GTK_DIALOG_MODAL,"Valide",GTK_RESPONSE_OK,NULL);
        gtk_window_set_default_size(GTK_WINDOW(windowsucces),270,80);
        gtk_window_set_icon_from_file(GTK_WINDOW(windowsucces),"error.png",NULL);
        GtkWidget *textlabel=gtk_label_new("le client n'est pas exist dans la liste des clients!\nSvp Ajouter ce client dans Gestion des clients...");
        gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowsucces)), textlabel, TRUE, TRUE, 0);
        gtk_widget_show_all(windowsucces);
        if(gtk_dialog_run(GTK_DIALOG(windowsucces))==GTK_RESPONSE_OK)
            gtk_widget_destroy(windowsucces);
     }

}

int recherche_client(info form){
    FILE *fp=fopen("Clients.txt","r");
    client cli;
    noeud *head=NULL,*p;
    while(!feof(fp)){
        fscanf(fp,"%d %s %s %d %s %d",&cli.idClient,cli.nom,cli.prenom,&cli.cin,cli.adresse,&cli.telephone);
        head=append(head,cli);
    }
    fclose(fp);
    p=head;
    while(p!=NULL){
        if(strcmp(p->prenom,form.prenom)==0&&strcmp(p->nom,form.nom)==0){
            return 1;
        }
        p=p->next;
    }
    freenoeud(head);
    return 0;
}

noeud *append(noeud *head,client cli){
    noeud *element=(noeud*)malloc(sizeof(noeud));
    strcpy(element->nom,cli.nom);
    strcpy(element->prenom,cli.prenom);
    element->next=head;
    return element;
}
void freenoeud(noeud *head){
    noeud *p=head;
    while(head){
        p=head;
        head=head->next;
        free(p);
    }
}

int recherche_voiture(info form){
    FILE *fp=fopen("Voitures.txt","r");
    voiture voi;
    noeudvoi *head=NULL,*p;
    while(!feof(fp)){
        fscanf(fp,"%d %s %s %s %d %d %s",&voi.idVoiture,voi.marque,voi.nomVoiture,voi.color,&voi.nbpalces,&voi.prixJour,voi.enLocation);
        head=app(head,voi);
    }
    fclose(fp);
    p=head;
    while(p!=NULL){
        printf("%s|%s|%s|%s ->",p->nomVoiture,p->marque,p->color,p->enLocation);
        if(strcmp(p->nomVoiture,form.nom_voiture)==0&&strcmp(p->color,form.coleur)==0&&strcmp(p->marque,form.marque)==0){
            if(strcmp(p->enLocation,"oui")==0)
                return 1;
            else
                return 2;
        }
        p=p->next;
    }
    freenoeud(head);
    return 0;
}

noeudvoi *app(noeud* tete,voiture voi){
    noeudvoi *element=(noeudvoi*)malloc(sizeof(noeudvoi));
    strcpy(element->nomVoiture,voi.nomVoiture);
    strcpy(element->marque,voi.marque);
    strcpy(element->color,voi.color);
    strcpy(element->enLocation,voi.enLocation);
    element->next=tete;
    return element;
}


void ContratWindow(GtkWidget *widget ,gpointer windowloca){
    GtkWidget *windowcontrat;
    GtkWidget *label[6];
    GtkWidget *text;
    GtkWidget *image;
    GtkWidget *table;
    GtkWidget *layout;
    FILE *filecontrat;
    GtkWidget *numcontrat,*idvoiture,*idclient,*debut,*fin,*cout;
    contrat perso;

    gtk_widget_destroy(GTK_WIDGET(windowsucces));

    windowcontrat=gtk_dialog_new_with_buttons("Cree Contrat",GTK_WINDOW(windowloca),GTK_DIALOG_MODAL,"Valider",GTK_RESPONSE_OK,"Annuler",GTK_RESPONSE_CANCEL,NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowcontrat),400,590);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowcontrat),"ajoute-c.png",NULL);

    image=gtk_image_new_from_file("cree.jpg");

    layout=gtk_layout_new(NULL,NULL);
    gtk_layout_put(GTK_LAYOUT(layout),image,0,0);

    numcontrat=gtk_entry_new();
    idvoiture=gtk_entry_new();
    idclient=gtk_entry_new();
    debut=gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(debut),"jj/mm/aaaa");
    fin=gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(fin),"jj/mm/aaaa");
    cout=gtk_entry_new();

    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Numero Contrat </b></span>",-1,NULL,NULL,NULL);
    label[0]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[0]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>IdVoiture </b></span>",-1,NULL,NULL,NULL);
    label[1]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[1]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>IdClient </b></span>",-1,NULL,NULL,NULL);
    label[2]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[2]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Date de Debut </b></span>",-1,NULL,NULL,NULL);
    label[3]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[3]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Date de fin </b></span>",-1,NULL,NULL,NULL);
    label[4]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[4]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Cout </b></span>",-1,NULL,NULL,NULL);
    label[5]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[5]),TRUE);


    table=gtk_table_new(6,2,FALSE);
    gtk_table_attach_defaults(GTK_TABLE(table),label[0],0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),label[1],0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),label[2],0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),label[3],0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),label[4],0,1,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),label[5],0,1,5,6);

    gtk_table_attach_defaults(GTK_TABLE(table),numcontrat,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),idvoiture,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),idclient,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),debut,1,2,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),fin,1,2,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),cout,1,2,5,6);

    gtk_table_set_row_spacings(GTK_TABLE(table),6);
    gtk_table_set_col_spacings(GTK_TABLE(table),8);
    gtk_container_set_border_width(GTK_CONTAINER(table),5);


    gtk_layout_put(GTK_LAYOUT(layout),table,0,0);

    gtk_box_pack_start((GtkBox*)(GtkDialog*)(gtk_dialog_get_content_area(windowcontrat)),layout,TRUE,TRUE,0);

    gtk_widget_show_all(windowcontrat);

    while(1){
        if(gtk_dialog_run(GTK_DIALOG(windowcontrat))==GTK_RESPONSE_OK){

            if(gtk_entry_get_text_length(GTK_ENTRY(numcontrat))==0||gtk_entry_get_text_length(GTK_ENTRY(idvoiture))==0||gtk_entry_get_text_length(GTK_ENTRY(idclient))==0||gtk_entry_get_text_length(GTK_ENTRY(debut))==0||gtk_entry_get_text_length(GTK_ENTRY(fin))==0||gtk_entry_get_text_length(GTK_ENTRY(cout))==0){
                GtkWidget *error=gtk_message_dialog_new(GTK_WINDOW(windowcontrat),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"L'un des champs est vide !!! \n Slvp rempli touts les champs !!");
                gtk_window_set_title(GTK_WINDOW(error), "Erreur");
                gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
                gtk_dialog_run(GTK_DIALOG(error));
                gtk_widget_destroy(error);
            }
            else{
                perso.numContrat=atof(gtk_entry_get_text(GTK_ENTRY(numcontrat)));
                perso.cout=atoi(gtk_entry_get_text(GTK_ENTRY(cout)));
                perso.idClient=atoi(gtk_entry_get_text(GTK_ENTRY(idclient)));
                perso.idVoiture=atoi(gtk_entry_get_text(GTK_ENTRY(idvoiture)));
                char DATE[10];
                char j[3];
                char m[3];
                char a[5];
                strcpy(DATE,gtk_entry_get_text(GTK_ENTRY(debut)));
                j[0]=DATE[0];j[1]=DATE[1];j[2]='\0';m[0]=DATE[3];m[1]=DATE[4];m[2]='\0';a[0]=DATE[6];a[1]=DATE[7];a[2]=DATE[8];a[3]=DATE[9];a[4]='\0';

                perso.debut.j=atoi(j);
                perso.debut.m=atoi(m);
                perso.debut.a=atoi(a);

                strcpy(DATE,gtk_entry_get_text(GTK_ENTRY(fin)));
                j[0]=DATE[0];j[1]=DATE[1];j[2]='\0';m[0]=DATE[3];m[1]=DATE[4];m[2]='\0';a[0]=DATE[6];a[1]=DATE[7];a[2]=DATE[8];a[3]=DATE[9];a[4]='\0';

                perso.fin.j=atoi(j);
                perso.fin.m=atoi(m);
                perso.fin.a=atoi(a);
                gtk_widget_destroy(windowcontrat);
                filecontrat=fopen("ContratsLocations.txt","a+");
                fprintf(filecontrat,"\n");
                fprintf(filecontrat,"%.2f %d %d %d/%d/%d %d/%d/%d %d",perso.numContrat,perso.idVoiture,perso.idClient,perso.debut.j,perso.debut.m,perso.debut.a,perso.fin.j,perso.fin.m,perso.fin.a,perso.cout);
                fclose(filecontrat);
                Modifier_Enlocation(form);
                break;

                }
        }
        else{
            gtk_widget_destroy(windowcontrat);
            break;
        }
    }
}

void Modifier_Enlocation(info select){
    FILE *fp=fopen("Voitures.txt","a+");
    voiture ser;
    FILE *fp2=fopen("help.txt","w");
    while(!feof(fp)){
        fscanf(fp,"%d %s %s %s %d %d %s",&ser.idVoiture,ser.marque,ser.nomVoiture,ser.color,&ser.nbpalces,&ser.prixJour,ser.enLocation);
        printf("%d %s %s %s %d %d %s\n",ser.idVoiture,ser.marque,ser.nomVoiture,ser.color,ser.nbpalces,ser.prixJour,ser.enLocation);
        fprintf(fp2,"\n");
        if(strcmp(ser.nomVoiture,select.nom_voiture)==0&&strcmp(ser.marque,select.marque)==0&&strcmp(ser.color,select.coleur)==0){
            strcpy(ser.enLocation,"oui");
        }
        fprintf(fp2,"%d %s %s %s %d %d %s",ser.idVoiture,ser.marque,ser.nomVoiture,ser.color,ser.nbpalces,ser.prixJour,ser.enLocation);
    }
    fclose(fp);
    fclose(fp2);
    remove("Voitures.txt");
    rename("help.txt","Voitures.txt");
}

void Retourner_Voiture(GtkWidget *widget,gpointer wind){
    GtkWidget *label[2];
    GtkWidget *windowfo;
    GtkWidget *grid;
    GtkWindow *button;

    label[0]=gtk_label_new("IdVoiture ");
    label[1]=gtk_label_new("NumContrat ");

    entry[0]=gtk_entry_new();
    entry[1]=gtk_entry_new();

    windowfo=gtk_dialog_new_with_buttons("valide",GTK_WINDOW(wind),GTK_DIALOG_MODAL,NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowfo),290,90);
    gtk_window_set_title(GTK_WINDOW(windowfo),"Retourner Voiture");
    gtk_window_set_icon_from_file(GTK_WINDOW(windowfo),"return.png",NULL);

    button=gtk_button_new_with_label("Valider!");
    grid=gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),label[0],0,0,1,1);
    gtk_grid_attach(GTK_GRID(grid),entry[0],1,0,1,1);
    gtk_grid_attach(GTK_GRID(grid),label[1],0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),entry[1],1,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),button,1,2,1,1);

    gtk_grid_set_row_spacing(GTK_GRID(grid),5);
    gtk_grid_set_column_spacing(GTK_GRID(grid),5);


    g_signal_connect(button,"clicked",G_CALLBACK(entry_len),(gpointer)windowfo);
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowfo)), grid, TRUE, TRUE, 0);
    gtk_widget_show_all(windowfo);
}

void entry_len(GtkWidget *widget,gpointer window){
    int idvoiture;
    double numcontrat;

    if(gtk_entry_get_text_length(GTK_ENTRY(entry[0]))==0||gtk_entry_get_text_length(GTK_ENTRY(entry[1]))==0){
        GtkWidget *error=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"L'un des champs est vide !!! \n Slvp rempli touts les champs !!");
        gtk_window_set_title(GTK_WINDOW(error), "Erreur");
        gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
        gtk_dialog_run(GTK_DIALOG(error));
        gtk_widget_destroy(error);
    }
    else{
        idvoiture=atoi(gtk_entry_get_text(entry[0]));
        numcontrat=atof(gtk_entry_get_text(entry[1]));
        printf("%d %.2lf",idvoiture,numcontrat);
        Enlocation_non(idvoiture);
        Supprimer_contrat(numcontrat);
        gtk_widget_destroy(GTK_WIDGET(window));
    }

}

void Enlocation_non(int idvoiture){
    FILE *fp=fopen("Voitures.txt","a+");
    voiture ser;
    FILE *fp2=fopen("help.txt","w");
    while(!feof(fp)){
        fscanf(fp,"%d %s %s %s %d %d %s",&ser.idVoiture,ser.marque,ser.nomVoiture,ser.color,&ser.nbpalces,&ser.prixJour,ser.enLocation);
        fprintf(fp2,"\n");
        if(idvoiture==ser.idVoiture){
            strcpy(ser.enLocation,"non");
        }
        fprintf(fp2,"%d %s %s %s %d %d %s",ser.idVoiture,ser.marque,ser.nomVoiture,ser.color,ser.nbpalces,ser.prixJour,ser.enLocation);
    }
    fclose(fp);
    fclose(fp2);
    remove("Voitures.txt");
    rename("help.txt","Voitures.txt");
}

void Supprimer_contrat(double N_contrat){
    FILE *fp=fopen("ContratsLocations.txt","r");
    FILE *fp2=fopen("help2.txt","w");
    char t1[30];
    char t2[30];
    contrat ser;
    while(!feof(fp)){
        fscanf(fp,"%f %d %d %s %s %d",&ser.numContrat,&ser.idVoiture,&ser.idClient,t1,t2,&ser.cout);
        if(N_contrat!=ser.numContrat){
            fprintf(fp2,"\n");
            fprintf(fp2,"%f %d %d %s %s %d",ser.numContrat,ser.idVoiture,ser.idClient,t1,t2,ser.cout);
        }
    }
    fclose(fp);
    fclose(fp2);
   remove("ContratsLocations.txt");
   rename("help2.txt","ContratsLocations.txt");

}



void modifierloca(GtkWidget *widget ,gpointer window){

    GtkWidget *Numcont;
    GtkWidget *label[2];
    GtkWidget *Button;
    GtkWidget *grid;

    windowrecherche2=gtk_dialog_new_with_buttons("Recherche_Par_NumContrat",GTK_WINDOW(window),GTK_DIALOG_MODAL,NULL);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowrecherche2),"recherche.png",NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowrecherche2),270,100);
    Button=gtk_button_new_with_label("Chercher");
    label[0]=gtk_label_new("Numero Contrat");
    label[1]=gtk_label_new("Entrer Numero de contrat qui vous modifier:");
    Numcont=gtk_entry_new();
    grid=gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),label[1],0,0,2,1);
    gtk_grid_attach(GTK_GRID(grid),label[0],0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),Numcont,1,1,3,1);
    gtk_grid_attach(GTK_GRID(grid),Button,1,2,1,1);
    gtk_grid_set_row_spacing(GTK_GRID(grid),5);
    g_signal_connect(Button,"clicked",G_CALLBACK(ChercherContrat),(gpointer)Numcont);
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowrecherche2)), grid, TRUE, TRUE, 0);
    gtk_widget_show_all(windowrecherche2);

}

/**search inside the file LocationVoitures**/

void ChercherContrat(GtkWidget *widget,gpointer entry){
    FILE *fp=fopen("ContratsLocations.txt","r");
    GtkWidget *windowmodif;
    GtkWidget *error;
    GtkWidget *layout;
    char t1[30];
    char t2[30];
    contrat ser;
    int b=0;
    char string[500];
    while(fgets(string,500,fp)!=NULL){
        fscanf(fp,"%f",&ser.numContrat);
        if(ser.numContrat==atof(gtk_entry_get_text(GTK_ENTRY(entry)))){
            fscanf(fp,"%f %d %d %s %s %d",&ser.numContrat,&ser.idVoiture,&ser.idClient,t1,t2,&ser.cout);
            b=1;
            break;
        }
    }
    fclose(fp);
    //b==0 error (id n'exit pas)
    if(b==0){
        error=gtk_message_dialog_new(GTK_WINDOW(windowrecherche2),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"Numero de contrat INCONUU!");
        gtk_window_set_title(GTK_WINDOW(error), "Erreur");
        gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
        gtk_dialog_run(GTK_DIALOG(error));
        gtk_widget_destroy(error);
    }
    else{
        modifierwindow(atof(gtk_entry_get_text(GTK_ENTRY(entry))));
        gtk_widget_destroy(GTK_WIDGET(windowrecherche2));
    }
}


/** function modifier (display screen for edit previous entry**/

void modifierwindow(float numcon){
    printf("%f",numcon);
    GtkWidget *windowcontrat;
    GtkWidget *label[6];
    GtkWidget *text;
    GtkWidget *image;
    GtkWidget *table;
    GtkWidget *layout;
    FILE *filecontrat;
    GtkWidget *numcontrat,*idvoiture,*idclient,*debut,*fin,*cout;
    contrat perso;
    char t1[30];
    char t2[30];
    char stri[20];

    windowcontrat=gtk_dialog_new_with_buttons("Modifier Contrat",GTK_WINDOW(windowrecherche2),GTK_DIALOG_MODAL,"Valider",GTK_RESPONSE_OK,"Annuler",GTK_RESPONSE_CANCEL,NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowcontrat),400,590);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowcontrat),"edit.png",NULL);

    image=gtk_image_new_from_file("modifier_c.jpg");

    layout=gtk_layout_new(NULL,NULL);
    gtk_layout_put(GTK_LAYOUT(layout),image,0,0);

    numcontrat=gtk_entry_new();
    idvoiture=gtk_entry_new();
    idclient=gtk_entry_new();
    debut=gtk_entry_new();
    fin=gtk_entry_new();
    cout=gtk_entry_new();

    /**searche line information**/
    filecontrat=fopen("ContratsLocations.txt","r+");
    char string[500];
    while(fgets(string,500,filecontrat)!=NULL){
        fscanf(filecontrat,"%f %d %d %s %s %d",&perso.numContrat,&perso.idVoiture,&perso.idClient,t1,t2,&perso.cout);
        if(numcon==perso.numContrat)
            break;
    }
    fclose(filecontrat);

    /**entry placeholder**/
    itoa(perso.numContrat,stri,10);
    gtk_entry_set_text(GTK_ENTRY(numcontrat),stri);
    itoa(perso.idVoiture,stri,10);
    gtk_entry_set_text(GTK_ENTRY(idvoiture),stri);
    itoa(perso.idClient,stri,10);
    gtk_entry_set_text(GTK_ENTRY(idclient),stri);
    gtk_entry_set_text(GTK_ENTRY(debut),t1);
    gtk_entry_set_text(GTK_ENTRY(fin),t2);
    itoa(perso.cout,stri,10);
    gtk_entry_set_text(GTK_ENTRY(cout),stri);
    /***********************/

    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Numero Contrat </b></span>",-1,NULL,NULL,NULL);
    label[0]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[0]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>IdVoiture </b></span>",-1,NULL,NULL,NULL);
    label[1]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[1]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>IdClient </b></span>",-1,NULL,NULL,NULL);
    label[2]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[2]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Date de Debut </b></span>",-1,NULL,NULL,NULL);
    label[3]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[3]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Date de fin </b></span>",-1,NULL,NULL,NULL);
    label[4]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[4]),TRUE);
    text=g_locale_to_utf8("<span foreground=\"yellow\"size=\"x-large\"><b>Cout </b></span>",-1,NULL,NULL,NULL);
    label[5]=gtk_label_new(text);
    gtk_label_set_use_markup(GTK_LABEL(label[5]),TRUE);


    table=gtk_table_new(6,2,FALSE);
    gtk_table_attach_defaults(GTK_TABLE(table),label[0],0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),label[1],0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),label[2],0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),label[3],0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),label[4],0,1,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),label[5],0,1,5,6);

    gtk_table_attach_defaults(GTK_TABLE(table),numcontrat,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),idvoiture,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),idclient,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),debut,1,2,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),fin,1,2,4,5);
    gtk_table_attach_defaults(GTK_TABLE(table),cout,1,2,5,6);

    gtk_table_set_row_spacings(GTK_TABLE(table),6);
    gtk_table_set_col_spacings(GTK_TABLE(table),8);
    gtk_container_set_border_width(GTK_CONTAINER(table),5);


    gtk_layout_put(GTK_LAYOUT(layout),table,0,0);

    gtk_box_pack_start((GtkBox*)(GtkDialog*)(gtk_dialog_get_content_area(windowcontrat)),layout,TRUE,TRUE,0);

    gtk_widget_show_all(windowcontrat);

    while(1){
        if(gtk_dialog_run(GTK_DIALOG(windowcontrat))==GTK_RESPONSE_OK){

            if(gtk_entry_get_text_length(GTK_ENTRY(numcontrat))==0||gtk_entry_get_text_length(GTK_ENTRY(idvoiture))==0||gtk_entry_get_text_length(GTK_ENTRY(idclient))==0||gtk_entry_get_text_length(GTK_ENTRY(debut))==0||gtk_entry_get_text_length(GTK_ENTRY(fin))==0||gtk_entry_get_text_length(GTK_ENTRY(cout))==0){
                GtkWidget *error=gtk_message_dialog_new(GTK_WINDOW(windowcontrat),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"L'un des champs est vide !!! \n Slvp rempli touts les champs !!");
                gtk_window_set_title(GTK_WINDOW(error), "Erreur");
                gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
                gtk_dialog_run(GTK_DIALOG(error));
                gtk_widget_destroy(error);
            }
            else{
                perso.numContrat=atof(gtk_entry_get_text(GTK_ENTRY(numcontrat)));
                perso.cout=atoi(gtk_entry_get_text(GTK_ENTRY(cout)));
                perso.idClient=atoi(gtk_entry_get_text(GTK_ENTRY(idclient)));
                perso.idVoiture=atoi(gtk_entry_get_text(GTK_ENTRY(idvoiture)));
                char DATED[30],DATEF[30];
                strcpy(DATED,gtk_entry_get_text(GTK_ENTRY(debut)));
                strcpy(DATEF,gtk_entry_get_text(GTK_ENTRY(fin)));
                gtk_widget_destroy(windowcontrat);
                /**after enter accept temp file open & add the last modification & copie content of file1 to file temp**/
                FILE *fichier2=fopen("test2.txt","w");
                fprintf(fichier2,"\n");
                fprintf(fichier2,"%.2f %d %d %s %s %d",perso.numContrat,perso.idVoiture,perso.idClient,DATED,DATEF,perso.cout);
                filecontrat=fopen("ContratsLocations.txt","r");
                while(!feof(filecontrat)){
                     fscanf(filecontrat,"%f %d %d %s %s %d",&perso.numContrat,&perso.idVoiture,&perso.idClient,t1,t2,&perso.cout);
                    if(numcon!=perso.numContrat){
                        fprintf(fichier2,"\n");
                        fprintf(fichier2,"%.2f %d %d %s %s %d",perso.numContrat,perso.idVoiture,perso.idClient,t1,t2,perso.cout);
                    }
                }
                fclose(filecontrat);
                fclose(fichier2);
                remove("ContratsLocations.txt");
                rename("test2.txt","ContratsLocations.txt");
                break;

                }
        }
        else{
            gtk_widget_destroy(windowcontrat);
            break;
        }
    }
}

void Suprimaloca(GtkWidget *widget ,gpointer window){

    GtkWidget *Numcont;
    GtkWidget *label[2];
    GtkWidget *Button;
    GtkWidget *grid;

    windowrecherche2=gtk_dialog_new_with_buttons("Recherche_Par_NumContrat",GTK_WINDOW(window),GTK_DIALOG_MODAL,NULL);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowrecherche2),"recherche.png",NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowrecherche2),270,100);
    Button=gtk_button_new_with_label("Chercher");
    label[0]=gtk_label_new("Numero Contrat");
    label[1]=gtk_label_new("Entrer Numero de contrat qui vous Supprimer:");
    Numcont=gtk_entry_new();
    grid=gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),label[1],0,0,2,1);
    gtk_grid_attach(GTK_GRID(grid),label[0],0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),Numcont,1,1,3,1);
    gtk_grid_attach(GTK_GRID(grid),Button,1,2,1,1);
    gtk_grid_set_row_spacing(GTK_GRID(grid),5);
    g_signal_connect(Button,"clicked",G_CALLBACK(ChercherContrat2),(gpointer)Numcont);
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowrecherche2)), grid, TRUE, TRUE, 0);
    gtk_widget_show_all(windowrecherche2);

}

void ChercherContrat2(GtkWidget *widget,gpointer entry){
    FILE *fp=fopen("ContratsLocations.txt","r");
    GtkWidget *windowmodif;
    GtkWidget *error;
    GtkWidget *layout;
    char t1[30];
    char t2[30];
    contrat ser;
    int b=0;
    char string[500];
    while(fgets(string,500,fp)!=NULL){
        fscanf(fp,"%f",&ser.numContrat);
        if(ser.numContrat==atof(gtk_entry_get_text(GTK_ENTRY(entry)))){
            fscanf(fp,"%f %d %d %s %s %d",&ser.numContrat,&ser.idVoiture,&ser.idClient,t1,t2,&ser.cout);
            b=1;
            break;
        }
    }
    fclose(fp);
    //b==0 error (id n'exit pas)
    if(b==0){
        error=gtk_message_dialog_new(GTK_WINDOW(windowrecherche2),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"Numero de contrat INCONUU!");
        gtk_window_set_title(GTK_WINDOW(error), "Erreur");
        gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
        gtk_dialog_run(GTK_DIALOG(error));
        gtk_widget_destroy(error);
    }
    else{
        Supprimer_contrat(atof(gtk_entry_get_text(GTK_ENTRY(entry))));
        gtk_widget_destroy(GTK_WIDGET(windowrecherche2));
    }
}

void visualiser(GtkWidget *widget,gpointer window){
    GtkWidget *Numcont;
    GtkWidget *label[2];
    GtkWidget *Button;
    GtkWidget *grid;

    windowrecherche2=gtk_dialog_new_with_buttons("Recherche_Par_NumContrat",GTK_WINDOW(window),GTK_DIALOG_MODAL,NULL);
    gtk_window_set_icon_from_file(GTK_WINDOW(windowrecherche2),"recherche.png",NULL);
    gtk_window_set_default_size(GTK_WINDOW(windowrecherche2),270,100);
    Button=gtk_button_new_with_label("Chercher");
    label[0]=gtk_label_new("Numero Contrat");
    label[1]=gtk_label_new("Entrer Numero de votre contrat:");
    Numcont=gtk_entry_new();
    grid=gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid),label[1],0,0,2,1);
    gtk_grid_attach(GTK_GRID(grid),label[0],0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),Numcont,1,1,3,1);
    gtk_grid_attach(GTK_GRID(grid),Button,1,2,1,1);
    gtk_grid_set_row_spacing(GTK_GRID(grid),5);
    g_signal_connect(Button,"clicked",G_CALLBACK(ChercherContrat3),(gpointer)Numcont);
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windowrecherche2)), grid, TRUE, TRUE, 0);
    gtk_widget_show_all(windowrecherche2);

}

void ChercherContrat3(GtkWidget *widget,gpointer entry){
    FILE *fp=fopen("ContratsLocations.txt","r");
    GtkWidget *error;
    GtkWidget *layout;
    char t1[30];
    char t2[30];
    contrat ser;
    int b=0;
    char string[500];
    while(fgets(string,500,fp)!=NULL){
        fscanf(fp,"%f",&ser.numContrat);
        if(ser.numContrat==atof(gtk_entry_get_text(GTK_ENTRY(entry)))){
            fscanf(fp,"%f %d %d %s %s %d",&ser.numContrat,&ser.idVoiture,&ser.idClient,t1,t2,&ser.cout);
            b=1;
            break;
        }
    }
    fclose(fp);
    //b==0 error (id n'exit pas)
    if(b==0){
        error=gtk_message_dialog_new(GTK_WINDOW(windowrecherche2),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"Numero de contrat INCONUU!");
        gtk_window_set_title(GTK_WINDOW(error), "Erreur");
        gtk_window_set_icon_from_file(GTK_WINDOW(error),"error.png",NULL);
        gtk_dialog_run(GTK_DIALOG(error));
        gtk_widget_destroy(error);
    }
    else{
        affiche_contrat(ser);
        //gtk_widget_destroy(GTK_WIDGET(windowrecherche2));
    }
}

void affiche_contrat(contrat ser){
    GtkWidget *windownew=gtk_dialog_new_with_buttons("contrat",GTK_WINDOW(windowrecherche2),GTK_DIALOG_MODAL,NULL);
    gtk_window_set_default_size(GTK_WINDOW(windownew),450,100);
    GtkWidget *image=gtk_image_new_from_file("utilisateur.png");
    GtkWidget *label[6];
    char str[100];
    gcvt(ser.numContrat,6,str);
    label[0]=gtk_label_new(str);
    itoa(ser.idClient,str,10);
    label[1]=gtk_label_new(str);
    itoa(ser.idVoiture,str,10);
    label[2]=gtk_label_new(str);
    itoa(ser.debut.a,str,10);
    label[3]=gtk_label_new("abdeljalil");
    itoa(ser.fin.a,str,100);
    label[4]=gtk_label_new("elma");
    itoa(ser.cout,str,100);
    label[5]=gtk_label_new("elmajjodi");

    GtkWidget *tab=gtk_table_new(6,7,FALSE);
    gtk_table_attach_defaults(GTK_TABLE(tab),image,0,3,0,6);
    gtk_table_attach_defaults(GTK_TABLE(tab),label[0],3,7,0,1);
    gtk_table_attach_defaults(GTK_TABLE(tab),label[1],3,7,1,2);
    gtk_table_attach_defaults(GTK_TABLE(tab),label[2],3,7,2,3);
    gtk_table_attach_defaults(GTK_TABLE(tab),label[3],3,7,3,4);
    gtk_table_attach_defaults(GTK_TABLE(tab),label[4],3,7,4,5);
    gtk_table_attach_defaults(GTK_TABLE(tab),label[5],3,7,5,6);
    gtk_box_pack_start((GtkBox *) (GtkDialog *) (gtk_dialog_get_content_area(windownew)), tab, TRUE, TRUE, 0);
    gtk_widget_show_all(windownew);
}

