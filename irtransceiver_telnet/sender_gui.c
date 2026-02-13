#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h> // für Threads

#define MAX_SHOWS 128
#define BUFFER_SIZE 256

typedef struct {
    char channelName[50];
    char time[20];
    char showName[100];
    char genre[30];
} Show;

Show shows[MAX_SHOWS];
int show_count = 0;


char* format_channel_name(const char *channelName) {
    static char formatted_name[50];
    int j = 0;

    for (int i = 0; channelName[i] != '\0'; i++) {
        if (channelName[i] == ' ') {
            formatted_name[j++] = '_';
        } else if (channelName[i] == '.') {
            formatted_name[j++] = '_';
        } else {
            formatted_name[j++] = toupper(channelName[i]);
        }
    }
    formatted_name[j] = '\0';

    return formatted_name;
}

void parse_output(const char *output) {
    char *line = strtok((char *)output, "\n");
    while (line != NULL && show_count < MAX_SHOWS) {
        sscanf(line, "Channel: %49[^,], Time: %19[^,], Show: %99[^,], Genre: %29[^,\n]",
               shows[show_count].channelName,
               shows[show_count].time,
               shows[show_count].showName,
               shows[show_count].genre);
        show_count++;
        line = strtok(NULL, "\n");
    }
}

void on_item_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    GtkTreeIter iter;
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gchar *selected_channel;
        gtk_tree_model_get(model, &iter, 0, &selected_channel, -1);
        printf("Ausgewählter Sender: %s\n", selected_channel);

        char *formatted_channel_name = format_channel_name(selected_channel);
        char command[BUFFER_SIZE];
        snprintf(command, sizeof(command), "bash irsend.sh _%s", formatted_channel_name);
        system(command);
        g_free(selected_channel);
    }
}

void apply_css(GtkWidget *widget, const char *css) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}

void on_button1_clicked(GtkWidget *widget, gpointer data) {
    g_print("Button 1 wurde geklickt!\n");
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "bash irsend.sh KEY_INFO");
    system(command);
}

void on_button2_clicked(GtkWidget *widget, gpointer data) {
    g_print("Button 2 wurde geklickt!\n");
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "bash irsend.sh _VOLUME 50 20");
    system(command);
}


void on_button4_clicked(GtkWidget *widget, gpointer data) {
    g_print("Button 4 wurde geklickt!\n");
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "bash irsend.sh _VOLUME 50 20");
    system(command);
}

void on_button5_clicked(GtkWidget *widget, gpointer data) {
    g_print("Button 5 wurde geklickt!\n");
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "bash irsend.sh KEY_VOLDOWN KEY_VOLDOWN KEY_VOLDOWN KEY_VOLDOWN KEY_VOLDOWN");
    system(command);
}

void on_button6_clicked(GtkWidget *widget, gpointer data) {
    g_print("Button 6 wurde geklickt!\n");
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "bash irsend.sh KEY_MUTE");
    system(command);
}

// Funktion, um Daten nach dem Fensteraufbau asynchron zu laden
void *load_data(void *arg) {
    GtkListStore *list_store = (GtkListStore *)arg;

    // PHP-Ausgabe parsen (wie vorher)
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char output[BUFFER_SIZE * MAX_SHOWS] = "";

    fp = popen("php tvmovie.php", "r");
    if (fp == NULL) {
        fprintf(stderr, "Fehler beim Ausführen des PHP-Skripts.\n");
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(output, buffer);
    }
    pclose(fp);
    parse_output(output);

    // Daten zur Liste hinzufügen
    for (int i = 0; i < show_count; i++) {
        gtk_list_store_insert_with_values(list_store, NULL, -1,
                                          0, shows[i].channelName,
                                          1, shows[i].time,
                                          2, shows[i].showName,
                                          3, shows[i].genre,
                                          -1);
    }

    return NULL;
}

GtkListStore *list_store;

void on_button3_clicked(GtkWidget *widget, gpointer data) {
    g_print("Button 3 wurde geklickt!\n");
    // Daten in separatem Thread laden, um GUI nicht zu blockieren
    pthread_t data_thread;
    pthread_create(&data_thread, NULL, load_data, list_store);
    pthread_detach(data_thread); // Thread läuft im Hintergrund weiter
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Fenster erstellen
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sender Auswahl");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    // CSS anwenden
    //const char *css_data = "* { font-size: 10px; }"; // Schriftgröße auf 10px setzen
const char *css_data = 
    "* { font-size: 10px; }"
    "* {"
    "    border-radius: 15px;"
    "    background-color: #5F9EA0;"
    "    color: white;"
    "    padding: 5px 10px;"
    "    border: none;"
    "    transition: background-color 0.3s ease;"
    "}"
    "*:hover {"
    "    background-color: #4682B4;"
    "}";

const char *css_data2 = 
    "* { font-size: 10px; }" // Allgemeine Schriftgröße
    "* {"
    "    background-color: #5F9EA0;"
    "    color: #333333;"
    "}"
    "*:hover {"
    "    background-color: #B0C4DE;"
    "}"
    "header {"
    "    background-color: #5F9EA0;"
    "    color: white;"
    "    font-weight: bold;"
    "}"
    "cellrenderertext {"
    "    padding: 5px;"
    "    border-radius: 5px;"
    "}";


    // Hauptbox
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // Zwei zusätzliche Buttons oberhalb der Tabelle
    GtkWidget *button_box_top = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), button_box_top, FALSE, FALSE, 0);

    GtkWidget *button3 = gtk_button_new_with_label("Neu Laden");
    GtkWidget *button4 = gtk_button_new_with_label("Button 4");
    gtk_box_pack_start(GTK_BOX(button_box_top), button3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box_top), button4, TRUE, TRUE, 0);

    // Scrollbar
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_box_pack_start(GTK_BOX(main_box), scrolled_window, TRUE, TRUE, 0);

    // Tabelle
    list_store = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    const gchar *titles[] = {"Sender", "Startzeit", "Sendung", "Kategorie"};
    for (int i = 0; i < 4; i++) {
        GtkTreeViewColumn *column = gtk_tree_view_column_new();
        gtk_tree_view_column_set_title(column, titles[i]);
        gtk_tree_view_column_pack_start(column, renderer, TRUE);
        gtk_tree_view_column_add_attribute(column, renderer, "text", i);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }

    g_signal_connect(treeview, "row-activated", G_CALLBACK(on_item_activated), NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), treeview);

    // Zwei weitere Buttons unterhalb der vorhandenen Buttons
    GtkWidget *button_box_bottom = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), button_box_bottom, FALSE, FALSE, 0);

    GtkWidget *button5 = gtk_button_new_with_label("Volume -5");
    GtkWidget *button6 = gtk_button_new_with_label("MUTE");
    gtk_box_pack_start(GTK_BOX(button_box_bottom), button5, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box_bottom), button6, TRUE, TRUE, 0);

    // Button Panel
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), button_box, FALSE, FALSE, 0);

    GtkWidget *button1 = gtk_button_new_with_label(" INFO");
    GtkWidget *button2 = gtk_button_new_with_label("VOLUME 20%");
    gtk_box_pack_start(GTK_BOX(button_box), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box), button2, TRUE, TRUE, 0);

    // Signalverbindungen hinzufügen
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button2_clicked), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(on_button3_clicked), NULL);
    g_signal_connect(button4, "clicked", G_CALLBACK(on_button4_clicked), NULL);
    g_signal_connect(button5, "clicked", G_CALLBACK(on_button5_clicked), NULL);
    g_signal_connect(button6, "clicked", G_CALLBACK(on_button6_clicked), NULL);




    apply_css(window, css_data);
    apply_css(button1, css_data);
    apply_css(button2, css_data);
    apply_css(button3, css_data);
    apply_css(button4, css_data);
    apply_css(button5, css_data);
    apply_css(button6, css_data);

    apply_css(treeview, css_data2);

    // Label mit Info
    GtkWidget *info_label = gtk_label_new("Zusätzliche Informationen...");
    gtk_box_pack_start(GTK_BOX(main_box), info_label, FALSE, FALSE, 5);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

    // Daten in separatem Thread laden, um GUI nicht zu blockieren
    pthread_t data_thread;
    pthread_create(&data_thread, NULL, load_data, list_store);
    pthread_detach(data_thread); // Thread läuft im Hintergrund weiter

    gtk_main();
    return 0;
}