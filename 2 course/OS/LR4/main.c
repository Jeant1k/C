#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>
#include <semaphore.h>
// #include <libexplain/libexplain.h>
#include "parser.h"

int main(int argc, char *argv[]) {
    
    int arg_len = strlen(argv[1]); 
    if (argc != 2) {
		printf("Количество аргументов задано неверно!\n");
		return 2;
	}
    if (arg_len > 255) {
        printf("Длина файла задана неверно!\n");
		return 3;
    }

    sem_t *sem;
    
    int fd_for_input = open("back1.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	struct stat sb;
	ftruncate(fd_for_input , 5000 * sizeof(char));
	if (fstat(fd_for_input, &sb) ==  -1) {
		perror("Не удалось узнать длинну файла \n");
	}
	char *file_mem =  mmap(NULL, sb.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd_for_input, 0);

    
    int id = fork();
    if (id == -1) {
        printf("Произошла ошибка с fork\n");
        return 2;
    }
    if (id == 0) {
        execl("./Child.out", "./Child.out", argv[1], NULL);
    } else {
        queue_dbl q;
        qdbl_init(&q);
        printf("Введите массив чисел: ");
        q = parser();
        int i = 0;
        while (qdbl_get_size(&q) != 0) {
            double el = qdbl_pop_front(&q);
            printf("Попнули элемент %lf\n", el);
            char buf[1000];
            sprintf(buf, "%lf", el);
            printf("Получили строку %s\n", buf);
            int j = 0;
            while (buf[j] != '\0') {
                file_mem[i] = buf[j];
                i++;
                j++;
            }
            file_mem[i] = ' ';
            i++;
        }
        // file_mem[0] = 'b';
        msync(file_mem, sb.st_size, MS_SYNC| MS_INVALIDATE);
        if ((sem = sem_open("/my_name", 0)) == SEM_FAILED ) {
            perror("sem_open");
            return 1;
        }
        sem_post(sem);
    }
}
