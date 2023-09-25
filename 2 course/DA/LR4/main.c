#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>





// Библиотека trie.h

typedef struct queue_trie queue_trie;
typedef struct queue_chr queue_chr;
typedef struct queue_int queue_int;

typedef struct trie {
    queue_trie *children;
    queue_chr *word;
    queue_int *pattern_idx;
    queue_int *pattern_num_words;
    struct trie *fail;
    struct trie *exit;
} trie;





// Библиотека qtrie.c

#define POOL_SIZE 64
#define K_SIZE 2

struct queue_trie {
    trie **buf;
    long long pool_size;
    long long size;
    long long first;
    long long last;
};

void QtrieInit(queue_trie *q);
void QtrieDestroy(queue_trie *q);

long long QtrieGetSize(queue_trie *q);

trie* QtriePopFront(queue_trie *q);
trie* QtrieGet(queue_trie *q, long long idx);
bool QtriePushBack(queue_trie *q, trie *node);

bool QtrieIsEmpty(queue_trie *q);

void QtrieInit(queue_trie *q) {
    
    q -> buf = (trie **)calloc(POOL_SIZE, sizeof(trie*));
    q -> pool_size = POOL_SIZE;
    q -> size = 0;
    q -> first = 0;
    q -> last = 0;
    
}

void QtrieDestroy(queue_trie *q) {
    
    free(q -> buf);
    q -> buf = NULL;
    q -> pool_size = 0;
    q -> size = 0;
    q -> first = 0;
    q -> last = 0;
    
}

long long QtrieGetSize(queue_trie *q) {
    return q -> size;
}

trie* QtriePopFront(queue_trie *q) {
    
    trie *node = q -> buf[q -> first];
    q -> buf[q -> first] = NULL;
    q -> first++;
    q -> size--;
    
    return node;
    
}

trie* QtrieGet(queue_trie *q, long long idx) {
    return q -> buf[idx];
}

bool QtriePushBack(queue_trie *q, trie *node) {
    
    if (q -> last >= q -> pool_size) {
        trie **new_buf = (trie **)realloc(q -> buf, sizeof(trie*) * q -> pool_size * K_SIZE);
        if (new_buf == NULL) {
            return false;
        }
        q -> buf = new_buf;
        q -> pool_size = q -> pool_size * K_SIZE;
    }
    q -> buf[q -> last] = node;
    q -> last++;
    q -> size++;
    
    return true;
    
}

bool QtrieIsEmpty(queue_trie *q) {
    return q -> size <= 0;
}





// Библиотека qchr.c

struct queue_chr {
    char *buf;
    long long pool_size;
    long long size;
    long long first;
    long long last; 
};

void QchrInit(queue_chr *q);
void QchrDestroy(queue_chr *q);

long long QchrGetSize(queue_chr *q);

char QchrPopFront(queue_chr *q);
char QchrGet(queue_chr *q, long long idx);
bool QchrPushBack(queue_chr *q, char val);

bool QchrIsEmpty(queue_chr *q);

void QchrInit(queue_chr *q) {
    
    q -> buf = (char *)calloc(POOL_SIZE, sizeof(char));
    q -> pool_size = POOL_SIZE;
    q -> size = 0;
    q -> first = 0;
    q -> last = 0;
    
}

void QchrDestroy(queue_chr *q) {
    
    free(q -> buf);
    q -> buf = NULL;
    q -> pool_size = 0;
    q -> size = 0;
    q -> first = 0;
    q -> last = 0;
    
}

long long QchrGetSize(queue_chr *q) {
    return q -> size;
}

char QchrPopFront(queue_chr *q) {

    char val = q -> buf[q -> first];
    q -> buf[q -> first] = '\0';
    q -> first++;
    q -> size--;
    
    return val;
    
}

char QchrGet(queue_chr *q, long long idx) {
    return q -> buf[idx];
}

bool QchrPushBack(queue_chr *q, char val) {
    
    if (q -> last >= q -> pool_size) {
        char *new_buf = (char *)realloc(q -> buf, sizeof(char) * q -> pool_size * K_SIZE);
        if (new_buf == NULL) {
            return false;
        }
        q -> buf = new_buf;
        q -> pool_size = q -> pool_size * K_SIZE;
    }
    q -> buf[q -> last] = val;
    q -> last++;
    q -> size++;
    
    return true;
    
}

bool QchrIsEmpty(queue_chr *q) {
    return q -> size <= 0;
}





// Библиотека qint.c

struct queue_int {
    long long *buf;
    long long pool_size;
    long long size;
    long long last;
    long long first;
};

void QintInit(queue_int *q);
void QintDestroy(queue_int *q);

long long QintGetSize(queue_int *q);

long long QintPopFront(queue_int *q);
long long QintGet(queue_int *q, long long idx);
bool QintPushBack(queue_int *q, long long val);

bool QintIsEmpty(queue_int *q);

void QintInit(queue_int *q) {
    
    q -> buf = (long long *)calloc(POOL_SIZE, sizeof(long long));
    q -> pool_size = POOL_SIZE;
    q -> size = 0;
    q -> first = 0;
    q -> last = 0;
    
}

void QintDestroy(queue_int *q) {
    
    free(q -> buf);
    q -> buf = NULL;
    q -> pool_size = 0;
    q -> size = 0;
    q -> first = 0;
    q -> last = 0;
    
}

long long QintGetSize(queue_int *q) {
    return q -> size;
}

long long QintPopFront(queue_int *q) {
    
    long long val = q -> buf[q -> first];
    q -> buf[q -> first] = 0;
    q -> first++;
    q -> size--;
    
    return val;
    
}

long long QintGet(queue_int *q, long long idx) {
    return q -> buf[idx];
}

bool QintPushBack(queue_int *q, long long val) {
    
    if (q -> last >= q -> pool_size) {
        long long *new_buf = (long long *)realloc(q -> buf, sizeof(long long) * q -> pool_size * K_SIZE);
        if (new_buf == NULL) {
            return false;
        }
        q -> buf = new_buf;
        q -> pool_size = q -> pool_size * K_SIZE;
    }
    q -> buf[q -> last] = val;
    q -> size++;
    q -> last++;
    
    return true;
    
}

bool QintIsEmpty(queue_int *q) {
    return q -> size <= 0;
}





// Библиотека aho_korasick.c

#define WORD_LENGTH 16

trie* Create();
void Insert(trie *root, queue_chr *pattern, long long pattern_idx);
void BuildFail(trie *root);
void Search(trie *root, queue_chr *text, queue_int *numbers_text);
void Destroy(trie *root);

void DFS(trie *root);

void DFS(trie *root) {
    
    printf("Вершина: %s.\npatter_idx = ", root -> word -> buf);
    for (long long i = 0; i < QintGetSize(root -> pattern_idx); i++) {
        printf("%lld ", QintGet(root -> pattern_idx, i));
    }
    printf("\npattern_num_words = ");
    for (long long i = 0; i < QintGetSize(root -> pattern_num_words); i++) {
        printf("%lld ", QintGet(root -> pattern_num_words, i));
    }
    printf("\nВедет в вершины: ");
    for (long long i = 0; i < QtrieGetSize(root -> children); i++) {
        printf("%s ", QtrieGet(root -> children, i) -> word -> buf);
    }
    printf("\nfail -> %s.\n", root -> fail -> word -> buf);
    if (root -> exit != NULL) {
        printf("exit -> %s.\n", root -> exit -> word -> buf);
    } else {
        printf("exit -> NULL.\n\n");
    }
    
    for (long long i = 0; i < QtrieGetSize(root -> children); i++) {
        DFS(QtrieGet(root -> children, i));
    }
    
}

trie* Create() {
    
    trie *root = (trie *)calloc(1, sizeof(trie));
    queue_trie *qt = (queue_trie *)calloc(1, sizeof(queue_trie));
    QtrieInit(qt);
    root -> children = qt;
    queue_chr *qc = (queue_chr *)calloc(1, sizeof(queue_chr));
    QchrInit(qc);
    root -> word = qc;
    queue_int *qi1 = (queue_int *)calloc(1, sizeof(queue_int));
    QintInit(qi1);
    root -> pattern_idx = qi1;
    queue_int *qi2 = (queue_int *)calloc(1, sizeof(queue_int));
    QintInit(qi2);
    root -> pattern_num_words = qi2;
    root -> fail = NULL;
    root -> exit = NULL;
    
    return root;
    
}

void Insert(trie *root, queue_chr *pattern, long long pattern_idx) {
    
    trie *cur = root;
    long long pattern_len = 0;
    long long num_words = 0;
    char word[WORD_LENGTH + 1];
    long long i_word;
    long long idx;
    while (!QchrIsEmpty(pattern)) {
        memset(word, '\0', WORD_LENGTH + 1);
        i_word = 0;
        char c = QchrPopFront(pattern);
        pattern_len++;
        while (c != ' ') {
            word[i_word] = c;
            i_word++;
            c = QchrPopFront(pattern);
            pattern_len++;
        }
        idx = -1;
        for (long long i = 0; i < QtrieGetSize(cur -> children); i++) {
            if (strcmp(word, QtrieGet(cur -> children, i) -> word -> buf) == 0) {
                idx = i;
                break;
            }
        }
        trie *tmp = NULL;
        if (idx == -1) {
            tmp = Create();
            i_word = 0;
            while (word[i_word] != '\0') {
                QchrPushBack(tmp -> word, word[i_word]);
                i_word++;
            }
            QtriePushBack(cur -> children, tmp);
            cur = tmp;
        } else {
            cur = QtrieGet(cur -> children, idx);
        }
        num_words++;
    }
    
    QintPushBack(cur -> pattern_idx, pattern_idx);
    QintPushBack(cur -> pattern_num_words, num_words);
    
}

void BuildFail(trie *root) {
    
    root -> fail = root;
    root -> exit = NULL;

    queue_trie queue;
    QtrieInit(&queue);

    for (long long i = 0; i < QtrieGetSize(root -> children); i++) {
        root -> children -> buf[i] -> fail = root;
        root -> children -> buf[i] -> exit = NULL;
        QtriePushBack(&queue, root -> children -> buf[i]);
    }

    while (!QtrieIsEmpty(&queue)) {
        trie *cur = QtriePopFront(&queue);
        for (long long i = 0; i < QtrieGetSize(cur -> children); i++) {
            trie *fail = cur -> fail;
            long long idx = -1;
            for (long long j = 0; j < QtrieGetSize(fail -> children); j++) {
                if (strcmp(QtrieGet(fail -> children, j) -> word -> buf, QtrieGet(cur -> children, i) -> word -> buf) == 0) {
                    idx = j;
                    break;
                }
            }
            while (fail != root && idx == -1) {
                fail = fail -> fail;
                idx = -1;
                for (long long j = 0; j < QtrieGetSize(fail -> children); j++) {
                    if (strcmp(QtrieGet(fail -> children, j) -> word -> buf, QtrieGet(cur -> children, i) -> word -> buf) == 0) {
                        idx = j;
                        break;
                    }
                }
            }
            if (idx != -1) {
                fail = fail -> children -> buf[idx];
            }
            cur -> children -> buf[i] -> fail = fail;
            if (QintGetSize(fail -> pattern_idx) != 0) {
                cur -> children -> buf[i] -> exit = fail;
            } else {
                cur -> children -> buf[i] -> exit = fail -> exit;
            }
            QtriePushBack(&queue, cur -> children -> buf[i]);
        }
    }

    QtrieDestroy(&queue);
    
}

void Search(trie *root, queue_chr *text, queue_int *numbers_text) {
    
    trie *cur = root;
    long long idx_word = 1;
    char word[WORD_LENGTH + 1];
    long long i_word;
    char c;
    while (!QchrIsEmpty(text)) {
        memset(word, '\0', WORD_LENGTH + 1);
        i_word = 0;
        c = QchrPopFront(text);  //  Сделать обработку разделителей
        while (c != ' ' && c != '\n' && c != EOF) {
            word[i_word] = c;
            i_word++;
            c = QchrPopFront(text);
        }
        long long idx = -1;
        for (long long i = 0; i < QtrieGetSize(cur -> children); i++) {
            if (strcmp(word, QtrieGet(cur -> children, i) -> word -> buf) == 0) {
                idx = i;
                break;
            }
        }
        while (idx == -1 && cur != root) {
            cur = cur -> fail;
            idx = -1;
            for (long long i = 0; i < QtrieGetSize(cur -> children); i++) {
                if (strcmp(word, QtrieGet(cur -> children, i) -> word -> buf) == 0) {
                    idx = i;
                    break;
                }
            }
        }
        if (idx != -1) {
            cur = cur -> children -> buf[idx];
        } else {
            cur  = root;
        }
        trie *tmp = cur;
        while (tmp != root) {
            if (QintGetSize(tmp -> pattern_idx) != 0) {
                for (long long i = 0; i < QintGetSize(tmp -> pattern_idx); i++) {
                    long long string_idx = QintGet(numbers_text, 2 * (idx_word - QintGet(tmp -> pattern_num_words, i) + 1 - 1));
                    long long word_idx = QintGet(numbers_text, (2 * (idx_word - QintGet(tmp -> pattern_num_words, i) + 1 - 1)) + 1);
                    printf("%lld, %lld, %lld\n", string_idx, word_idx, QintGet(tmp -> pattern_idx, i));
                }
            }
            tmp = tmp -> exit;
            if (tmp == NULL) {
                break;
            }
        }
        if (c == ' ' || c == '\n') {
            idx_word++;
        }
    }
    
}

void Destroy(trie *root) {

    for (long long i = 0; i < QtrieGetSize(root -> children); i++) {
        Destroy(QtrieGet(root -> children, i));
    }

    QtrieDestroy(root -> children);
    free(root -> children);
    QchrDestroy(root -> word);
    free(root -> word);
    QintDestroy(root -> pattern_idx);
    free(root -> pattern_idx);
    QintDestroy(root -> pattern_num_words);
    free(root -> pattern_num_words);
    root -> fail = NULL;
    root -> exit = NULL;
    free(root);

}





// Библиотека io_handler.c

typedef enum {
    STATE_NOT_SIMBOL,  // 0
    STATE_PATTERN,  // 1
    STATE_TEXT,  // 2
    STATE_WORD,  // 3
    STATE_SPACE,  // 4
} state;

void Loop();

bool IsSeparator(char c);
char LetterLower(char c);

bool IsSeparator(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

char LetterLower(char letter) {
    
    if (41 <= letter && letter <= 90) {
        return letter + 32;
    }
    
    return letter;
    
}

void Loop() {
    
    queue_chr patterns;
    QchrInit(&patterns);
    queue_chr text;
    QchrInit(&text);
    queue_int numbers_text;
    QintInit(&numbers_text);
    long long string_idx = 1;
    long long word_idx = 1;
    char c;
    state s = STATE_NOT_SIMBOL;
    while ((c = getchar()) != EOF) {
        c = LetterLower(c);
        if (s == STATE_NOT_SIMBOL && c != '\n' && c != ' ') {
            s = STATE_PATTERN;
            QchrPushBack(&patterns, c);
        } else if (s == STATE_NOT_SIMBOL && c != '\n' && c == ' ') {
            
        } else if (s == STATE_NOT_SIMBOL) {
            s = STATE_TEXT;
        } else if (s == STATE_PATTERN && c == '\n') {
            s = STATE_NOT_SIMBOL;
            QchrPushBack(&patterns, ' ');
            QchrPushBack(&patterns, '#');
        } else if (s == STATE_PATTERN && (c == ' ' || c == '\t')) {
            s = STATE_SPACE;
            QchrPushBack(&patterns, ' ');
        } else if (s == STATE_PATTERN) {
            QchrPushBack(&patterns, c);
        } else if (s == STATE_SPACE && (c == ' ' || c == '\t')) {
            
        } else if (s == STATE_SPACE && c == '\n') {
            s = STATE_NOT_SIMBOL;
            QchrPushBack(&patterns, '#');
        } else if (s == STATE_SPACE) {
            s = STATE_PATTERN;
            QchrPushBack(&patterns, c);
        } else if (s == STATE_TEXT && !IsSeparator(c)) {
            s = STATE_WORD;
            QchrPushBack(&text, c);
            QintPushBack(&numbers_text, string_idx);
            QintPushBack(&numbers_text, word_idx);
        } else if (s == STATE_TEXT) {
            if (c == '\n') {
                string_idx++;
                word_idx = 1;
            }
        } else if (s == STATE_WORD && IsSeparator(c)) {
            s = STATE_TEXT;
            QchrPushBack(&text, c);
            word_idx++;
            if (c == '\n') {
                string_idx++;
                word_idx = 1;
            }
        } else if (s == STATE_WORD) {
            QchrPushBack(&text, c);
        }
    }

    c = QchrGet(&text, QchrGetSize(&text) - 1);
    if (!IsSeparator(c)) {
        QchrPushBack(&text, ' ');
    }

    trie *root = NULL;
    root = Create();
    queue_chr pattern;
    QchrInit(&pattern);
    long long pattern_idx = 1;
    s = STATE_NOT_SIMBOL;
    while (!QchrIsEmpty(&patterns)) {
        c = QchrPopFront(&patterns);
        if (s == STATE_NOT_SIMBOL && c != '#') {
            s = STATE_PATTERN;
            QchrPushBack(&pattern, c);
        } else if (s == STATE_PATTERN && c != '#') {
            QchrPushBack(&pattern, c);
        } else if (s == STATE_PATTERN) {
            s = STATE_NOT_SIMBOL;
            Insert(root, &pattern, pattern_idx);
            pattern_idx++;
            QchrDestroy(&pattern);
            QchrInit(&pattern);
        }
    }

    BuildFail(root);

    // DFS(root);

    Search(root, &text, &numbers_text);

    QchrDestroy(&patterns);
    QchrDestroy(&text);
    QchrDestroy(&pattern);
    QintDestroy(&numbers_text);
    Destroy(root);
    
}

int main(void) {
    
    Loop();

    return 0;
    
}
