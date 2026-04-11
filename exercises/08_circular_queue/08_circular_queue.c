#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

int main() {
    Queue q;
    int total_people = 50;
    int report_interval = 5;
    // 初始化队列
    q.head = 0;
    q.tail = 0;
    q.count = 0;
    // 将人加入队列
    for (int i = 1; i <= total_people; i++) {
        q.data[q.tail].id = i;
        q.tail = (q.tail + 1) % MAX_PEOPLE;
        q.count++;
    }
    // 模拟报数和淘汰（约瑟夫环）
    int current_count = 0;
    while (q.count > 1) {
        current_count++;
        if (current_count == report_interval) {
            // 报到指定数字，队头淘汰
            printf("淘汰: %d\n", q.data[q.head].id);
            q.head = (q.head + 1) % MAX_PEOPLE;
            q.count--;
            current_count = 0;
        } else {
            // 未淘汰则队头重新入队到队尾
            People p = q.data[q.head];
            q.head = (q.head + 1) % MAX_PEOPLE;
            q.data[q.tail] = p;
            q.tail = (q.tail + 1) % MAX_PEOPLE;
        }
    }

    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}