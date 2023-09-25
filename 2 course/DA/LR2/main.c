#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//  Библиотека красно-черного дерева

enum rbt_colors {RED, BLACK};

#define LENGTH_TEXT_KEY 256
#define RESET "\033[0m"
#define RED_COLOR "\033[0;31m"

typedef struct rbtree {
    struct rbtree *parent;
    struct rbtree *right;
    struct rbtree *left;
    enum rbt_colors color;
    char key[LENGTH_TEXT_KEY + 1];
    unsigned long long int number;
} rbt;

rbt* RbtCreate(rbt *root, char key[], unsigned long long int number);
rbt* RbtAdd(rbt *root, char key[], unsigned long long int number);
rbt* RbtSearch(rbt *root, char key[]);
rbt* RbtDelete(rbt *root, char key[]);
rbt* RbtReturnRoot(rbt *n);
void RbtPrint(rbt *root);
rbt* RbtFreeTree(rbt *root);

rbt* Grandparent(rbt *n);
rbt* Uncle(rbt *n);
rbt* Sibling(rbt *n);

void RotateLeft(rbt *n);
void RotateRight(rbt *n);

void InsertCase1(rbt *n);
void InsertCase2(rbt *n);
void InsertCase3(rbt *n);
void InsertCase4(rbt *n);
void InsertCase5(rbt *n);

bool IsLeaf(rbt *n);
void ReplaceNode(rbt* n, rbt* child);
rbt* SearchMinRight(rbt *n);
void SwapKeys(rbt *n1, rbt *n2);
rbt* DeleteOneOrNoChild(rbt *n);
rbt* DeleteTwoChild(rbt *n);

void DeleteCase1(rbt *n);
void DeleteCase2(rbt *n);
void DeleteCase3(rbt *n);
void DeleteCase4(rbt *n);
void DeleteCase5(rbt *n);
void DeleteCase6(rbt *n);

rbt* RbtReturnRoot(rbt *n) {

    if (n == NULL) {
        return NULL;
    }
    
    if (n -> parent == NULL) {
        return n;
    }
    
    return RbtReturnRoot(n -> parent);
    
}

rbt* RbtCreate(rbt *root, char key[], unsigned long long int number) {
    
    rbt *tmp = malloc(sizeof(rbt));
    tmp -> parent = NULL;
    tmp -> left = NULL;
    tmp -> right = NULL;
    tmp -> color = RED;
    memset(tmp -> key, '\0', LENGTH_TEXT_KEY + 1);
    for (int i = 0; i < LENGTH_TEXT_KEY; i++) {
        tmp -> key[i] = key[i];
    }
    tmp -> number = number;
    root = tmp;
    
    InsertCase1(root);
    
    return RbtReturnRoot(root);
    
}

rbt* RbtAdd(rbt *root, char key[], unsigned long long int number) {
    
    rbt *tmp = malloc(sizeof(rbt));
    tmp -> left = NULL;
    tmp -> right = NULL;
    tmp -> color = RED;
    memset(tmp -> key, '\0', LENGTH_TEXT_KEY + 1);
    for (int i = 0; i < LENGTH_TEXT_KEY; i++) {
        tmp -> key[i] = key[i];
    }
    tmp -> number = number;
    
    rbt *cur_rbt = root;
    rbt *final_rbt = NULL;
    while (cur_rbt != NULL) {
        final_rbt = cur_rbt;
        if (strcmp(key, cur_rbt -> key) < 0) {
            cur_rbt = cur_rbt -> left;
        } else {
            cur_rbt = cur_rbt -> right;
        }
    }
    tmp -> parent = final_rbt;
    
    if (strcmp(key, final_rbt -> key) < 0) {
        free(final_rbt -> left);
        final_rbt -> left = tmp;
    } else {
        free(final_rbt -> right);
        final_rbt -> right = tmp;
    }
    
    InsertCase1(tmp);
    
    return RbtReturnRoot(root);
    
}

rbt* RbtSearch(rbt *root, char key[]) {
    
    if ((root == NULL) || (strcmp(root -> key, key) == 0)) {
        return root;
    }
    
    if (strcmp(key, root -> key) < 0) {
        return RbtSearch(root -> left, key);
    } else {
        return RbtSearch(root -> right, key);
    }
    
}

rbt* RbtDelete(rbt *root, char key[]) {
    
    rbt *n_deleted = RbtSearch(root, key);
    
    if (n_deleted -> left != NULL && n_deleted -> right != NULL) {
        root = DeleteTwoChild(n_deleted);
    } else {
        root = DeleteOneOrNoChild(n_deleted);
    }
    
    return root;
    
}

void RbtPrint(rbt *root) {
    
    if (root == NULL) {
        printf("null; ");
        return;
    }
    
    if (root -> color == RED) {
        printf("%s%s-%llu-r; %s", RED_COLOR, root -> key, root -> number, RESET);
        // printf("%s-%llu-r; ", root -> key, root -> number);
    } else {
        printf("%s-%llu-b; ", root -> key, root -> number);
    }
    
    RbtPrint(root -> left);
    RbtPrint(root -> right);
    
}

rbt* RbtFreeTree(rbt *root) {
    
    if (root == NULL) {
        return NULL;
    }
    
    RbtFreeTree(root -> left);
    RbtFreeTree(root -> right);
    free(root);
    
    return NULL;
    
}

rbt* Grandparent(rbt *n) {
    
	if ((n != NULL) && (n -> parent != NULL)) {
        return n -> parent -> parent;
    } else {
        return NULL;
    }
    
}

rbt* Uncle(rbt *n) {
    
	rbt *g = Grandparent(n);
    
	if (g == NULL) {
        return NULL;
    }
    
	if (n -> parent == g -> left) {
        return g -> right;
    } else {
        return g -> left;
    }
    
}

void RotateLeft(rbt *n) {
    
    rbt *tmp = n -> right;
    tmp -> parent = n -> parent;
    if (n -> parent != NULL) {
        if (n -> parent -> left == n) {
            n -> parent -> left = tmp;
        } else {
            n -> parent -> right = tmp;
        }
    }
    n -> right = tmp -> left;
    if (tmp -> left != NULL) {
        tmp -> left -> parent = n;
    }
    n -> parent = tmp;
    tmp -> left = n;
    
}

void RotateRight(rbt *n) {
    
    rbt *tmp = n -> left;
    tmp -> parent = n -> parent;
    if (n -> parent != NULL) {
        if (n -> parent -> left == n) {
            n -> parent -> left = tmp;
        } else {
            n -> parent -> right = tmp;
        }
    }
    n -> left = tmp -> right;
    if (tmp -> right != NULL) {
        tmp -> right -> parent = n;
    }
    n -> parent = tmp;
    tmp -> right = n;
    
}

void InsertCase1(rbt *n) {
    
	if (n -> parent == NULL) {
        n -> color = BLACK;
    } else {
        InsertCase2(n);
    }
    
}

void InsertCase2(rbt *n) {
    
	if (n -> parent -> color == RED) {
        InsertCase3(n);
    }
    
}

void InsertCase3(rbt *n) {
    
	rbt *u = Uncle(n); 
    rbt *g;
	if ((u != NULL) && (u -> color == RED)) {
		n -> parent -> color = BLACK;
		u -> color = BLACK;
		g = Grandparent(n);
		g -> color = RED;
		InsertCase1(g);
	} else {
        InsertCase4(n);
    }
    
}

void InsertCase4(rbt *n) {
    
	rbt *g = Grandparent(n);
	if ((n == n -> parent -> right) && (n -> parent == g -> left)) {
		RotateLeft(n -> parent);
		n = n -> left;
	} else if ((n == n -> parent -> left) && (n -> parent == g -> right)) {
		RotateRight(n -> parent);
		n = n -> right;
	}
    
	InsertCase5(n);
    
}

void InsertCase5(rbt *n) {
    
	rbt *g = Grandparent(n);
	n -> parent -> color = BLACK;
	g -> color = RED;
	if ((n == n -> parent -> left) && (n -> parent == g -> left)) {
		RotateRight(g);
	} else {
        RotateLeft(g);
    }
    
}

bool IsLeaf(rbt *n) {
    return n == NULL;
}

rbt* Sibling(rbt *n) {
    
    if (n == n -> parent -> left) {
        return n -> parent -> right;
    } else {
        return n -> parent -> left;
    }
    
}

void ReplaceNode(rbt* n, rbt* child) {

    if (child != NULL) {
        child -> parent = n -> parent;
    }
    
    if (n -> parent != NULL) {
        if (n == n -> parent -> left) {
            n -> parent -> left = child;
        } else {
            n -> parent -> right = child;
        }
    }
    
}

rbt* SearchMinRight(rbt *n) {
    
    rbt *min_right = n -> right;
    rbt *cur_rbt = n -> right;
    while (cur_rbt != NULL) {
        min_right = cur_rbt;
        cur_rbt = cur_rbt -> left;
    }
    
    return min_right;
    
}

void SwapKeys(rbt *n1, rbt *n2) {
    
    char tmp_key[LENGTH_TEXT_KEY + 1];
    memset(tmp_key, '\0', LENGTH_TEXT_KEY + 1);
    for (int i = 0; i < LENGTH_TEXT_KEY; i++) {
        tmp_key[i] = n1 -> key[i];
    }
    unsigned long long int tmp_number = n1 -> number;
    
    memset(n1 -> key, '\0', LENGTH_TEXT_KEY + 1);
    for (int i = 0; i < LENGTH_TEXT_KEY; i++) {
        n1 -> key[i] = n2 -> key[i];
    }
    n1 -> number = n2 -> number;
    
    memset(n2 -> key, '\0', LENGTH_TEXT_KEY + 1);
    for (int i = 0; i < LENGTH_TEXT_KEY; i++) {
        n2 -> key[i] = tmp_key[i];
    }
    n2 -> number = tmp_number;
    
}

rbt* DeleteOneOrNoChild(rbt *n) {
    
    rbt *child;
    if (IsLeaf(n -> right)) {
        child = n -> left;
    } else {
        child = n -> right;
    }

    rbt* parent = n -> parent;
    bool left_n = false;
    if (parent != NULL) {
        if (n == parent -> left) {
            left_n = true;
        }
    }
    
	ReplaceNode(n, child);
    
	if (n -> color == BLACK) {
        if (child != NULL) {
            if (child -> color == RED) {
                child -> color = BLACK;
            } else {
                DeleteCase1(child);
            }
        } else {
            rbt *child = malloc(sizeof(rbt));
            child -> parent = parent;
            child -> color = BLACK;
            memset(child -> key, '\0', LENGTH_TEXT_KEY + 1);
            child -> number = -1;
            if (parent != NULL) {
                if (left_n) {
                    parent -> left = child;
                } else {
                    parent -> right = child;
                }
            }
            DeleteCase1(child);
            free(child);
            child = NULL;
            if (parent != NULL) {
                if (left_n) {
                    parent -> left = NULL;
                } else {
                    parent -> right = NULL;
                }
            }
        }
	}
    
	free(n);

    if (child == NULL) {
        return RbtReturnRoot(parent);
    }
    
    return RbtReturnRoot(child);
    
}

rbt* DeleteTwoChild(rbt *n) {
    
    rbt *min_right = SearchMinRight(n);
    
    SwapKeys(n, min_right);
    
    return DeleteOneOrNoChild(min_right);
    
}

void DeleteCase1(rbt *n) {
    
    if (n -> parent != NULL) {
        DeleteCase2(n);
    }
    
}

void DeleteCase2(rbt *n) {
    
    rbt *s = Sibling(n);
	if (s -> color == RED) {
		n -> parent -> color = RED;
		s -> color = BLACK;
		if (n == n -> parent -> left) {
            RotateLeft(n -> parent);
        } else {
            RotateRight(n -> parent);
        }
	}
    
	DeleteCase3(n);
    
}

void DeleteCase3(rbt *n) {
    
    rbt *s = Sibling(n);
	if ((n -> parent -> color == BLACK) && (s -> color == BLACK) && ((s -> left == NULL) || (s -> left -> color == BLACK)) && ((s -> right == NULL) || (s -> right -> color == BLACK))) {
		s -> color = RED;
		DeleteCase1(n -> parent);
	} else {
        DeleteCase4(n);
    }

}

void DeleteCase4(rbt *n) {
    
    rbt *s = Sibling(n);
	if ((n -> parent -> color == RED) && (s -> color == BLACK) && ((s -> left == NULL) || (s -> left -> color == BLACK)) && (s -> right == NULL || s -> right -> color == BLACK)) {
		s -> color = RED;
		n -> parent -> color = BLACK;
	} else {
        DeleteCase5(n);
    }
    
}

void DeleteCase5(rbt *n) {
    
    rbt *s = Sibling(n);
	if (s -> color == BLACK) {
		if ((s -> left != NULL) && ((n == n -> parent -> left) && ((s -> right == NULL) || (s -> right -> color == BLACK)) && (s -> left -> color == RED))) {
			s -> color = RED;
			s -> left -> color = BLACK;
			RotateRight(s);
		} else if ((s -> right != NULL) && ((n == n -> parent -> right) && ((s -> left == NULL) || (s -> left -> color == BLACK)) && (s -> right -> color == RED))) {
			s -> color = RED;
			s -> right -> color = BLACK;
			RotateLeft(s);
		}
	}
    
	DeleteCase6(n);
    
}

void DeleteCase6(rbt *n) {
    
    rbt *s = Sibling(n);
	s -> color = n -> parent -> color;
    n -> parent -> color = BLACK;
	if (n == n -> parent -> left) {
        s -> right -> color = BLACK;
		RotateLeft(n -> parent);
	} else {
        if (s -> left != NULL) {
            s -> left -> color = BLACK;
        }
		RotateRight(n -> parent);
	}
    
}





//  Библиотека парсинга строки

#define LENGTH_STR 65535
#define LENGTH_PATH 256

typedef struct {
    char key[LENGTH_TEXT_KEY + 1];
    unsigned long long int number;
} pair;

rbt* Loop(rbt *root);

void BinSaveRbtree(rbt *root, char path[]);
void DfsSave(rbt *root, FILE *file);
rbt* BinLoadRbtree(rbt *root, char path[]);
rbt* AddRbtree(rbt *root, char string[]);
rbt* DeleteRbtree(rbt *root, char string[]);
void SearchRbtree(rbt *root, char string[]);

char LetterLower(char letter) {
    return letter + 32;
}

void StringLower(char string[]) {
    int i = 0;
    while (string[i] != '\0') {
        if (65 <= string[i] && string[i] <= 90) {
            string[i] = LetterLower(string[i]);
        }
        i++;
    }
}

void DfsSave(rbt *root, FILE *file) {
    
    if (root == NULL) {
        return;
    }
    
    pair data;
    for (int i = 0; i < LENGTH_TEXT_KEY; i++) {
        data.key[i] = root -> key[i];
    }
    data.number = root -> number;
    fwrite(&data, sizeof(data), 1, file);
    
    DfsSave(root -> left, file);
    DfsSave(root -> right, file);
        
}

void BinSaveRbtree(rbt *root, char path[]) {
    
    char file_name[LENGTH_PATH];
    memset(file_name, '\0', LENGTH_PATH);
    int i_file_name = 0;
    int i_path = 7;
    while (path[i_path] != '\0') {
        file_name[i_file_name] = path[i_path];
        i_path++;
        i_file_name++;
    }
    
    FILE *file;
    file = fopen(file_name, "w");
    
    if (root != NULL && file != NULL) {
        DfsSave(root, file);
    }

    if (file != NULL) {
        fclose(file);
    }

    printf("OK\n");
    
}

rbt* BinLoadRbtree(rbt *root, char path[]) {
    
    char file_name[LENGTH_PATH];
    memset(file_name, '\0', LENGTH_PATH);
    int i_file_name = 0;
    int i_path = 7;
    while (path[i_path] != '\0') {
        file_name[i_file_name] = path[i_path];
        i_path++;
        i_file_name++;
    }
    
    FILE *file;
    file = fopen(file_name, "r");

    if (root != NULL) {
        root = RbtFreeTree(root);
    }

    if (file != NULL) {
        if (getc(file) != EOF) {
            fseek(file, 0, 0);
            pair data; 
            fread(&data, sizeof(data), 1, file);
            root = RbtCreate(root, data.key, data.number);
            while(fread(&data, sizeof(data), 1, file) == 1) {
                root = RbtAdd(root, data.key, data.number);
            }
        }
        fclose(file);
    }
    
    printf("OK\n");
    
    return root;
    
}

rbt* AddRbtree(rbt *root, char string[]) {
    
    char key[LENGTH_TEXT_KEY + 1];
    memset(key, '\0', LENGTH_TEXT_KEY + 1);
    int i_key = 0;
    int i_string = 2;
    while (string[i_string] != ' ') {
        key[i_key] = string[i_string];
        i_string++;
        i_key++;
    }
    
    char num[25];
    memset(num, '\0', 25);
    int i_num = 0;
    i_string++;
    while (string[i_string] != '\0') {
        num[i_num] = string[i_string];
        i_string++;
        i_num++;
    }
    unsigned long long int number;
    number = strtoull(num, NULL, 0);
    
    rbt *tmp = RbtSearch(root, key);
    
    if (root == NULL) {
        root = RbtCreate(root, key, number);
        printf("OK\n");
    } else {
        if (tmp != NULL) {
            printf("Exist\n");
        } else {
            root = RbtAdd(root, key, number);
            printf("OK\n");
        }
    }
    
    return root;
    
}

rbt* DeleteRbtree(rbt *root, char string[]) {
    
    char key[LENGTH_TEXT_KEY + 1];
    memset(key, '\0', LENGTH_TEXT_KEY + 1);
    int i_key = 0;
    int i_string = 2;
    while (string[i_string] != '\0') {
        key[i_key] = string[i_string];
        i_string++;
        i_key++;
    }
    
    rbt *tmp = RbtSearch(root, key);
    
    if (tmp == NULL) {
        printf("NoSuchWord\n");
    } else {
        root = RbtDelete(root, key);
        printf("OK\n");
    }
    
    return root;
    
}

void SearchRbtree(rbt *root, char string[]) {
    
    char key[LENGTH_TEXT_KEY + 1];
    memset(key, '\0', LENGTH_TEXT_KEY + 1);
    int i_key = 0;
    while (string[i_key] != '\0') {
        key[i_key] = string[i_key];
        i_key++;
    }
    
    rbt *tmp = RbtSearch(root, key);
    
    if (tmp == NULL) {
        printf("NoSuchWord\n");
    } else {
        printf("OK: %llu\n", tmp -> number);
    }
    
}

static void pars_question(char string[]) {
    int i = 2;
    while (string[i - 2] != '\0') {
        string[i - 2] = string[i];
        i++;
    }
}

rbt* Loop(rbt *root) {
    
    char c;
    char string[LENGTH_STR];
    memset(string, '\0', LENGTH_STR);
    int i_string = 0;
    
    while ((c = getchar()) != EOF) {
        if (c != '\n') {
            string[i_string] = c;
            i_string++;
        } else {
            StringLower(string);
            if (strstr(string, "! save") != NULL) {
                BinSaveRbtree(root, string);
            } else if (strstr(string, "! load") != NULL) {
                root = BinLoadRbtree(root, string);
            } else if (strstr(string, "+") != NULL) {
                root = AddRbtree(root, string);
            } else if (strstr(string, "-") != NULL) {
                root = DeleteRbtree(root, string);
            } else if (strstr(string, "?") != NULL) {
                SearchRbtree(root, "?");
                pars_question(string);
                SearchRbtree(root, string);
            } else {
                SearchRbtree(root, string);
            }
            memset(string, '\0', LENGTH_STR);
            i_string = 0;
            // RbtPrint(root);
            // printf("\n");
        }
    }

    root = RbtFreeTree(root);
    
    return root;
    
}





int main() {
    
    rbt *root = NULL;

    root = Loop(root);
    
}
