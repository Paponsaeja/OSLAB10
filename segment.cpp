#include <stdio.h>

typedef struct {
    int base;
    int length;
    int is_used;
} Segment;

typedef struct {
    int seg_index;
    int offset;
} Logic;

int calculate_physical_address(Segment segment_table[], int segment_index, int offset, int table_size) {
    if (segment_index < 0 || segment_index >= table_size) {
        // ถ้า index ของ segment ไม่ถูกต้อง
        return -1;
    }

    if (segment_table[segment_index].is_used) {
        // ถ้า segment ถูกใช้งานแล้ว
        printf("==> :cannot calculate (%d,%d) because Segment %d is currently in use. Please choose another segment.\n", segment_index,offset,segment_index) ;
        return -2;
    }

    int base_address = segment_table[segment_index].base ;
    int length = segment_table[segment_index].length ;

    if (offset < 0 || offset > length) {
        // ถ้า offset ไม่ถูกต้อง
        return -1; // หรือค่าที่เหมาะสมตามที่คุณต้องการ
    }

    int physical_address = base_address + offset;
    return physical_address;
}

int main() {
    Segment segment_table[] = {
        {219 , 600, 0 },
        {2300, 14 , 0 },
        {90  , 100, 0 },
        {1327, 580, 0 },
        {1952, 96 , 0 }
    };

    Logic logical_address_1[5];

    // รับข้อมูลจากผู้ใช้
    for (int i = 0; i < 5; i++) {
        printf("Enter logical address %d (seg_index offset): ", i);
        scanf("%d %d", &logical_address_1[i].seg_index, &logical_address_1[i].offset);
    }

    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++) {
        int physical_address = calculate_physical_address(segment_table, logical_address_1[i].seg_index,
        logical_address_1[i].offset, sizeof(segment_table) / sizeof(segment_table[0]));
        
        if (physical_address != -2) {
            // ทำเครื่องหมาย segment ที่ถูกใช้งาน
            segment_table[logical_address_1[i].seg_index].is_used = 1;
            printf("Physical Address for Logical Address (%d, %d): %d\n", logical_address_1[i].seg_index,
            logical_address_1[i].offset, physical_address);
        }
    }

    printf("-----------------------------------------------------------------\n");

    // แสดงรายการ segment ที่ยังไม่ถูกใช้งาน
    printf("Available segments that haven't use :\n");
    for (int i = 0; i < sizeof(segment_table) / sizeof(segment_table[0]); i++) {
        if (!segment_table[i].is_used) {
            printf("Segment %d (Base: %d, Length: %d)\n", i, segment_table[i].base, segment_table[i].length);
        }
    }
    return 0;
}
