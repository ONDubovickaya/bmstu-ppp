#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 24

// функция, которая будет использоваться для редукции
// суммируются только эл-ты, кратные 13 (иначе эл-т заменяется нулём)
void custom_reduce(void *bufIn, void *bufOut, int *len, MPI_Datatype *datatype) {
    int *in = bufIn;
    int *out = bufOut;

    int x, y;
    for (size_t i = 0; i < *len; i++)
    {
        x = *in;
        y = *out;

        if (x % 13 != 0) {
            x = 0;
        }

        if (y % 13 != 0) {
            y = 0;
        }

        *out = x + y;

        in++;
        out++;
    }
}

int main(int argc, char ** argv) {
    int myrank, nprocs, len, i;
    char name[MPI_MAX_PROCESSOR_NAME];
    int *send_buf, *recv_buf, *reduce_buf;

    MPI_Init(&argc, &argv);

    // создание пользовательской операции
    // 1 указывает, что операция яв-ся коллективной
    MPI_Op op;
    MPI_Op_create(custom_reduce, 1, &op);

    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Get_processor_name(name, &len);

    printf("Hello from processor %s[%d] %d of %d\n", name, len, myrank, nprocs);

    // если кол-во процессов меньше 2, то завершаем работу программы
    if (nprocs < 2) {
        printf("[ERROR] nprocs < 2 --> too small set of processors!\n");
        MPI_Finalize();
        return 1;
    }

    // для send_buf выделяем память только в процессе с номером 1
    // там же его заполняем значениями
    if (myrank == 1) {
        send_buf = (int*)malloc(sizeof(int) * (SIZE * nprocs));

        // заполняем массив
        for (i = 0; i < SIZE * nprocs; i++) {
            send_buf[i] = i + 1;
        }

        // для каждого процесса выводим первые 2 и последний эл-ты того массива, который будет ему отправляться
        for (i = 0; i < nprocs; i++) {
            printf("procs[%d]    send_buf[%d] : %8d %8d       ... %8d\n", myrank, i,
                   send_buf[i * SIZE], send_buf[i * SIZE + 1], send_buf[(i + 1) * SIZE - 1]);
        }
        printf("\n");

    } else {
        send_buf = NULL;
    }

    // все процессы выделяют память для recv_buf
    recv_buf = (int*)malloc(sizeof(int) * (SIZE));

    // распределение данных из send_buf между всеми процессами
    // каждый процесс получит SIZE эл-тов в свой recv_buf
    MPI_Scatter(send_buf, SIZE, MPI_INT,
                recv_buf, SIZE, MPI_INT,
                1, MPI_COMM_WORLD);

    // вывод всех эл-тов полученных соответствующим процессом
    printf("procs[%d] received: ", myrank);
    for (i = 0; i < SIZE; i++) {
        printf("%d ", recv_buf[i]);
    }
    printf("\n\n");

    // для reduce_buf выделяем память только в процессе под номером 0
    if (myrank == 0) {
        reduce_buf = (int*)malloc(SIZE * sizeof(int));
    } else {
        reduce_buf = NULL;
    }

    // выполняем операцию редукции, используя созданную пользовательскую операцию op
    // р-т записывается в reduce_buf процесса 0
    MPI_Reduce(recv_buf, reduce_buf, SIZE, MPI_INT, op, 0, MPI_COMM_WORLD);

    // для процесса 0 выводим все эл-ты из reduce_buf
    if (myrank == 0) {
        printf("[RESULT] Reduce result (on procs[%d]): ", myrank);

        for (i = 0; i < SIZE; i++) {
            printf("%d ", reduce_buf[i]);
        }
        printf("\n\n");
    }

    MPI_Finalize();
    return 0;
}
