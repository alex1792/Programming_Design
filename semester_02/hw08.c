#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024
#define MAP_CAP_BITS 5

/* ============ 型別定義 ============ */
/* Map Entry (i.e., Key-Value Pair) */
typedef struct entry
{
    char *key;
    int value;

    /*
     * 因碰撞解決方案採：Separate Chaining，
     * 需維護指向下一筆 Entry 之指標
     */
    struct entry *next;
} Entry;

/* Hash Map (i.e., Hash Table) */
typedef struct
{
    /*
     * 指向「所有條目」的指標 (i.e., 桶子們)，
     * 以抽象化的角度審視，也可將其命名為 "table"，
     * 意指雜湊表的「表格」實體
     */
    Entry *buckets;

    size_t capacity; // 桶子數 (i.e., 表格列數)
    size_t size;     // 已插入的條目數 (初始為 0)
} HashMap;

/* ============ 已完成 ============= */
/**
 * map_init - 初始化 HashMap (i.e., 分配雜湊表空間、設置相關屬性至初始值)
 * @map: 欲初始化之 HashMap
 * @cap_bits: 欲初始化之雜湊表大小 (log2)
 * @return 0 表示成功, -1 表示失敗
 */
int map_init(HashMap *map, unsigned int cap_bits);

/**
 * map_entries - 取得 HashMap 中所有「已插入」的條目
 * @map: 欲操作之 HashMap
 * @entries: 「指向 (Entry *) 之指標」的位址
 * @return 0 表示成功, -1 表示失敗
 */
int map_entries(HashMap *map, Entry ***entries);

/* ============ 未完成 ============= */
/**
 * entry_cmp - 用於 qsort 的比較函式
 *
 *             hint:
 *             就像欲排序 int *arr 時， a, b 需轉型為 (int *)，
 *             方能解參考 (dereference) 取出其整數值。
 *
 *             現在，排序目標之型別： Entry **entries
 *             請思考 a, b 該如何正確轉型
 *
 */
int entry_cmp(const void *a, const void *b)
{
    const Entry *c = *((Entry **)a);
    const Entry *d = *((Entry **)b);
    if (d->value > c->value)
        return 1;
    else if (d->value < c->value)
        return -1;
    else
        return strcmp(c->key, d->key);
}

/**
 * my_hash_function - 設計一個雜湊函式
 * @key: 雜湊函式的輸入鍵
 * @return 雜湊值 (hash value)
 */
size_t my_hash_function(const char *key)
{
    // int len = strlen(key);
    unsigned int ret = 0;
    int len = strlen(key);
    for (int i = 0; i < len; i++)
    {
        ret = ret * 32 + key[i];
    }
    return ret;
}
/**
 * map_idx - 根據 key 計算雜湊值，並回傳用於雜湊表的索引值 (Index)，
 *           (i.e., 第 i 個桶子 = 表格的第 i 列)
 *
 *           hint:
 *           內部應呼叫 my_hash_function
 *
 * @map: 欲操作之 HashMap
 * @key: 鍵
 * @return 根據 `key` 所計算出的雜湊表索引 (Index)
 */
size_t map_idx(HashMap *map, const char *key)
{
    int ret = my_hash_function(key) % (map->capacity);
    return ret;
}

/**
 * map_put - 新增條目 <key, value> 至 HashMap 中
 *
 *           hint：
 *           使用 `map_idx` 計算索引值，以找到插入的目標桶 (bucket)：
 *
 *              case 1: 桶子為空，將 strdup(key) 及 value 置於桶中。
 *
 *              case 2: 桶子非空，但該桶子或其鏈結串列上存在
 *                      與「欲插入之 `key`」相同的「鍵」，
 *                      則以「欲插入之 `value`」取代舊值。
 *                      (注意：此 case 中並無 (也不應該) 呼叫 strdup)
 *
 *              case 3: 桶子非空，但該桶子或其鏈結串列上皆「不」存在
 *                      與「欲插入之 `key`」相同的「鍵」，
 *                      則分配 (i.e., malloc) 一個 Entry，
 *                      並將 strdup(key) 及 value 置於其中，
 *                      最後將此 Entry 插入至鏈結串列 (頭或尾隨意)。
 *
 * @map: 欲操作之 HashMap
 * @key: 鍵
 * @value: 值
 * @return 0 表示成功, -1 表示失敗
 */
int map_put(HashMap *map, const char *key, int value)
{
    if (strlen(key) == 0)
        return 0;
    int idx = map_idx(map, key);
    //  case 1:桶子為空
    if (map->buckets[idx].key == NULL)
    {
        map->buckets[idx].key = strdup(key);
        map->buckets[idx].value = 1;
        map->buckets[idx].next = NULL;
        map->size++;
    }
    //  case 2、3:桶子有東西 做traversal
    else
    {
        Entry *tmp = &(map->buckets[idx]);
        while (tmp->next != NULL)
        {
            if (strcmp(tmp->key, key) == 0)
            {
                // printf("same!\n");
                tmp->value++;
                return 0;
            }
            tmp = tmp->next;
        }
        if (strcmp(tmp->key, key) == 0)
        {
            tmp->value++;
            return 0;
        }
        Entry *tail = malloc(sizeof(Entry));
        tail->key = strdup(key);
        tail->value = 1;
        tail->next = NULL;
        tmp->next = tail;
        map->size++;
        return 0;
    }
    return 0;
}

/**
 * map_get - 根據 `key`，取得已插入至 HashMap 的對應「值」之「位址」
 *
 *           hint:
 *           參照 `map_put` 方法進行搜尋
 *
 * @map: 欲操作之 HashMap
 * @key: 鍵
 * @return 對應「值」之「位址」，若不存在該條目則回傳 NULL
 */
int *map_get(HashMap *map, const char *key)
{
    int idx = map_idx(map, key);
    if (map->buckets[idx].key == NULL)
        return NULL;
    else
    {
        Entry *tmp = &(map->buckets[idx]);
        // printf("tmp:\t%s\n", tmp->key);
        while (tmp->next != NULL)
        {
            if (strcmp(tmp->key, key) == 0)
                return &tmp->value;
            tmp = tmp->next;
        }
        if (strcmp(tmp->key, key) == 0)
            return &tmp->value;
        return NULL;
    }
}
/**
 * map_destroy - 釋放 HashMap 所有相關資源，包含：
 *               @ 接在桶子後方的鏈結串列之節點
 *               @ 每個條目的 key
 *               @ 整張雜湊表
 *
 * @map: 欲操作之 HashMap
 */
void map_destroy(HashMap *map)
{
    Entry *tmp, *prev;
    for (int i = 0; i < 32; i++)
    {
        prev = map->buckets + i;
        // printf("prev1:\t%s\n", prev->key);
        if (prev->key == NULL)
        {
            // free(prev);
            continue;
        }
        int cnt = 0;
        while (prev)
        {
            // printf("prev:\t%s\n", prev->key);
            // printf("prev next: %x\n", prev->next);
            // prev = &(map->buckets[i]);
            tmp = prev->next; //這邊有問題
            // printf("tmp pointer: %x\n", tmp);
            // printf("tmp:\t%s\n", tmp->key);
            free(prev->key);
            if (cnt != 0)
                free(prev);
            prev = tmp;
            cnt++;
        }
    }
    free(map->buckets);
}

int main()
{
    /* =================== INITIALIZE =================== */
    HashMap map;
    if (map_init(&map, MAP_CAP_BITS) < 0)
        fprintf(stderr, "map_init error\n");

    /* ================== INPUT TERMS =================== */
    char buf[BUF_SIZE];
    while (fgets(buf, BUF_SIZE, stdin))
    {
        /* 去除輸入後方「可能」的換行字元 */
        buf[strcspn(buf, "\r\n")] = '\0';

        /* 目前是否欲對 term 作遞減 */
        const _Bool decrease = (*buf == '-');

        char *term;
        int increment; // 增量值

        if (decrease)
        {
            term = buf + 1;
            increment = -1;
        }
        else
        {
            term = buf;
            increment = 1;
        }
        // printf("string:\t%s\nlen:\t%ld\n", term, strlen(term));
        /* 根據 term 取得對應的值「位址」 */
        int *value = map_get(&map, term);

        if (value)
            (*value) += increment; // 根據增量值，修改 term count
        else if (!decrease)        // 若未插入過該 term，且不為遞減模式
            map_put(&map, term, 1);
    }
    /*printf("start!\n");
    for (int i = 0; i < 32; i++)
    {
        Entry * tmp = &(map.buckets[i]);
        printf("%d\t", i);
        while(tmp)
        {
            printf("%s\t%d", tmp->key, tmp->value);
            tmp = tmp->next;
        }
        printf("\n");
    }
    printf("end\n");*/

    /* =============== OUTPUT TERM COUNT ================ */
    {
        const size_t size = map.size;
        // printf("size:\t%ld\n", size);
        Entry **entries;
        if (map_entries(&map, &entries) < 0) // 取得所有條目
            fprintf(stderr, "map_entries error\n");

        /* 根據 entry_cmp 排序*/
        qsort(entries, size, sizeof(Entry *), entry_cmp);

        // printf("success\n");
        /* 按照排序結果依序輸出*/
        for (size_t i = 0; i < size; i++)
        {
            Entry *e = entries[i];
            const char *term = e->key;
            const int count = e->value;
            printf("%d %s\n", count, term);
        }

        /* 釋放條目指標空間 */
        free(entries);
    }

    /* =================== TERMINATE ==================== */
    map_destroy(&map);
}

int map_init(HashMap *map, unsigned int cap_bits)
{
    const size_t capacity = 1u << cap_bits;         // 計算 2 的 cap_bts 次方
    map->buckets = calloc(capacity, sizeof(Entry)); // 分配「全為 0」的空間
    map->capacity = capacity;
    map->size = 0;

    return -(map->buckets == NULL);
}

int map_entries(HashMap *map, Entry ***entries)
{
    Entry *table = map->buckets;
    const size_t capacity = map->capacity;
    size_t size = map->size;

    /* 若目前雜湊表無任何元素，則回傳 0 */
    if (!size)
    {
        *entries = NULL;
        return 0;
    }

    /* 否則，根據目前元素數量分配空間 */
    Entry **ret = malloc(size * sizeof(Entry *));
    if (!ret)
        return -1; // 分配失敗則傳回 -1

    size_t j = 0;
    for (size_t i = 0; size && i < capacity; i++)
    {
        Entry *e = table + i;
        if (!e->key)
            continue; // 若目前 bucket 為空，則查找下一個 bucket

        while (e)
        {
            ret[j++] = e; // 添加目前的 entry
            size--;
            e = e->next; // 查找鏈結串列節點之 entry
        }
    }

    *entries = ret;
    return 0;
}