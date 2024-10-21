#include "semaphore.h"

int main() {
    key_t key = ftok(STORE_PATH, 'a');
    int sem_id = init_semaphores(key);

    // 打开仓库文件
    int store_fd = open(STORE_PATH, O_CREAT | O_RDWR, 0666);
    if (store_fd == -1) {
        perror("open");
        exit(1);
    }

    // 资源生成循环
    char resource[] = "1234567890";
    int i = 0;

    while (1) {
        // 空位P操作，确保有空位
        semaphore_p(sem_id, SEM_EMPTY);

        // 互斥锁P操作
        semaphore_p(sem_id, SEM_MUTEX);

        int store_size = lseek(store_fd, 0, SEEK_END);
        printf("生产前：资源数量=%d, 空位数量=%d\n", store_size, STORE_CAPACITY - store_size);
        // 写入新资源到仓库
        lseek(store_fd, 0, SEEK_END);  // 移动到文件末尾
        write(store_fd, &resource[i], 1);
        printf("生产资源：%c\n", resource[i]);
        i = (i + 1) % 10;

        // 获取当前仓库内容
        printf("生产后：资源数量=%d, 空位数量=%d\n", store_size + 1, STORE_CAPACITY - store_size - 1);
        // 互斥锁V操作
        semaphore_v(sem_id, SEM_MUTEX);

        // 资源V操作，增加资源数量
        semaphore_v(sem_id, SEM_FULL);

        // 间隔1秒
        sleep(1);
    }

    close(store_fd);
    return 0;
}

