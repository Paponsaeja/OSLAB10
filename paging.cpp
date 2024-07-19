#include <stdio.h>

// ขนาดของหน้า (หน่วยของหน่วยความจำที่ถูกโหลดมาในหน่วยความจำหลัก)
#define FRAME_SIZE 256

// ฟังก์ชันสำหรับคำนวณ Physical Address จาก Logical Address
int calculatePhysicalAddress(int logicalAddress, int frameNumber) {
    int offset = logicalAddress % FRAME_SIZE; // หา Offset
    int physicalAddress = frameNumber * FRAME_SIZE + offset; // คำนวณ Physical Address
    return physicalAddress;
}

int main() {
    // Logical Addresses ที่กำหนด
    int logicalAddresses[] = {0x0125, 0x0243, 0x037A, 0x0550};

    // Process Page Table ที่กำหนด
    int pageTable[] = {0b000010100101001, 0b000010100100011, 0b000000100100100, 
                       0b000110101101011, 0b000011101101100, 0b000111101100111};

    // ประกาศตัวแปรสำหรับจัดเก็บ Physical Addresses
    int physicalAddresses[4];

    // ทำการคำนวณ Physical Addresses สำหรับแต่ละ Logical Address
    for (int i = 0; i < 4; i++) {
        // แปลง Logical Address เป็นเลขฐาน 10
        int logicalAddress = logicalAddresses[i];
        // หา Logical Page Number (LPN) 
        int LPN = (logicalAddress >> 8) & 0xFF;  // เลื่อนไปทางขวา shift bite 8 ครั้ง จาก 0000 0001 0010 0101 -> 0000 0000 0000 0001  
        //ทำการ and กับ 8 บิต 0*FF = 1111 1111    เพื่อเลือกเอาเฉพาะ 8 บิตแรกเท่านั้นคือ 0000 0001
        // หา Frame Number (PFN) จาก Process Page Table
        int PFN = pageTable[LPN];
        // คำนวณ Physical Address
        int physicalAddress = calculatePhysicalAddress(logicalAddress, PFN);
        // เก็บ Physical Address ในอาร์เรย์
        physicalAddresses[i] = physicalAddress;
    }

    // แสดงผล Physical Addresses
    for (int i = 0; i < 4; i++) {
        printf("Logical Address: 0x%04X, Physical Address: %d\n", logicalAddresses[i], physicalAddresses[i]);
    }

    return 0;
}
