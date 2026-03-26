#include <stdio.h>
#include <string.h>

typedef struct {
    char id[10], name[50];
    int quantity;
    double price;
} Item;

typedef struct {
    int log_id, quantity;
    char type[15], item_id[10];
} AuditLog;


Item warehouse[100];
AuditLog logs[500];
int item_count = 0;
int log_count = 0;
int global_log_id = 1;

int find_item(char *id) {
    for (int i = 0; i < item_count; i++) {
    if (strcmp(warehouse[i].id, id) == 0 ) return i;
    }
    return -1;
}

void add_log(char *type, char *item_id, int qty) {
    logs[log_count].log_id = global_log_id++;
    strcpy(logs[log_count].type, type);
    strcpy(logs[log_count].item_id, item_id);
    logs[log_count].quantity = qty ;
    log_count++;
}


int main() {
    char input[256];
    while (1) {
    if (fgets(input, sizeof(input), stdin) == NULL) break;

        input[strcspn(input, "\r\n")] = 0;
        if (strcmp(input, "---") == 0) break;
        
        char *command = strtok(input, "#");
        if (command = NULL) continue;

        if(strcmp(command, "receive") == 0 ) {
        char *id = strtok(NULL, "#");
        char *name = strtok(NULL, "#");
        char *qty_str = strtok(NULL, "#");
        char *price_str = strtok(NULL, "#");

        if (id && name && qty_str && price_str) {
            int idx = find_item(id) ;
            if (idx == -1) {
                strcpy(warehouse[item_count].id, id);
                strcpy(warehouse[item_count].name, name);
                warehouse[item_count].quantity = atoi(qty_str);
                warehouse[item_count].price = atof(price_str);
                item_count++;
            } else {
                warehouse[idx].quantity += atoi(qty_str);
            }
            add_log("receive", id, atoi (qty_str));
        }
     }
     else if (strcmp(command, "restock") == 0) {
        char *id = strtok(NULL, "#");
        char *qty_str = strtok(NULL, "#");
        if (id && qty_str) {
            int qty = atoi (qty_str);
            int idx = find_item (id);

            if (idx != -1 && qty > 0 && warehouse [idx].quantity >= qty) {
                warehouse [idx].quantity -= qty ; 
                add_log("ship", id, qty);
            }
        }
    }
    else if (strcmp(command, "restock") == 0) {
            char *id = strtok(NULL, "#");
            char *qty_str = strtok(NULL, "#");
            if (id && qty_str) {
                int qty = atoi(qty_str);
                int idx = find_item(id);
                if (idx != -1 && qty > 0) {
                    warehouse[idx].quantity += qty;
                    add_log("restock", id, qty);
                }
            }
        } 
        else if (strcmp(command, "report") == 0) {
            for (int i = 0; i < item_count; i++) {
                printf("%s|%s|%d|%.1f\n", warehouse[i].id, warehouse[i].name, 
                       warehouse[i].quantity, warehouse[i].price);
            }
        } 
                else if (strcmp(command, "audit") == 0) {
            char *id = strtok(NULL, "#");
            if (id) {
                int idx = find_item(id);
                if (idx != -1) {
 
                    printf("%s|%s|%d|%.1f\n", warehouse[idx].id, warehouse[idx].name, 
                           warehouse[idx].quantity, warehouse[idx].price);
           
                    for (int j = 0; j < log_count; j++) {
                        if (strcmp(logs[j].item_id, id) == 0) {
                            printf("%d|%s|%d\n", logs[j].log_id, logs[j].type, logs[j].quantity);
                        }
                    }
                }
            }
        }
    }

    return 0;
}