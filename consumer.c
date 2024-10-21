#include "semaphore.h"

int main() {
    key_t key = ftok(STORE_PATH, 'a');
    int sem_id = init_semaphores(key);

    // 打开仓库文件
    int store_fd = open(STORE_PATH, O_RDWR);
    if (store_fd == -1) {
        perror("open");
        exit(1);
    }

    while (1) {
        // 资源P操作，确保有资源
        semaphore_p(sem_id, SEM_FULL);

        // 互斥锁P操作
        semaphore_p(sem_id, SEM_MUTEX);

        // 读取资源
        char consumed_resource;
        lseek(store_fd, 0, SEEK_SET);  // 移动到文件开头
        read(store_fd, &consumed_resource, 1);

        // 获取当前仓库内容
        int store_size = lseek(store_fd, 0, SEEK_END);
        printf("消费前：资源数量=%d, 空位数量=%d\n", store_size, STORE_CAPACITY - store_size);
        printf("消费资源：%c\n", consumed_resource);

        // 删除资源
        lseek(store_fd, 1, SEEK_SET);
        ftruncate(store_fd, store_size - 1);

        // 互斥锁V操作
        semaphore_v(sem_id, SEM_MUTEX);

        // 空位V操作，增加空位数量
        semaphore_v(sem_id, SEM_EMPTY);

        printf("消费后：资源数量=%d, 空位数量=%d\n", store_size - 1, STORE_CAPACITY - store_size + 1);

        // 间隔2秒
        sleep(2);
    }

    close(store_fd);
    return 0;
}

