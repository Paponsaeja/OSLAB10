# Operating Systems Laboratory 📖💻

ศูนย์รวมโปรแกรมตัวอย่างและการทดลองสำหรับวิชา Operating Systems ที่ครอบคลุมหัวข้อหลักๆ ของระบบปฏิบัติการ

## 📋 รายการไฟล์และหัวข้อที่เกี่ยวข้อง

### 🔄 CPU Scheduling Algorithms
- **`Non-Preemptive_SJF_Scheduling.cpp`** - การจัดลำดับงานแบบ Non-Preemptive Shortest Job First
- **`Round_Robin_scheduling.cpp`** - การจัดลำดับงานแบบ Round Robin
- **`prezackversion.c++`** - การจัดลำดับงานแบบ Preemptive SJF
- **`priozackversion.c++`** - การจัดลำดับงานตาม Priority

### 💾 Memory Management
- **`paging.cpp`** - ระบบการจัดการหน่วยความจำแบบ Paging
- **`segment.cpp`** - ระบบการจัดการหน่วยความจำแบบ Segmentation

### 📄 Page Replacement Algorithms  
- **`LAB-9.cpp`** - อัลกอริทึมการแทนที่เพจ (FIFO, LRU, Optimal)
- **`pageReplacement.cpp`** - การเปรียบเทียบอัลกอริทึมการแทนที่เพจ

### 🔒 Deadlock Prevention
- **`LAB7_Banker.c++`** - Banker's Algorithm สำหรับป้องกัน Deadlock

### 🖥️ GUI Application
- **`JAVA_GUI_classify`** - แอปพลิเคชัน Java GUI สำหรับจัดการสินค้าตามหมวดหมู่

## 🚀 วิธีการใช้งาน

### สำหรับไฟล์ C++
```bash
# คอมไพล์ไฟล์ C++
g++ filename.cpp -o output_name

# รันโปรแกรม
./output_name
```

### สำหรับไฟล์ Java
```bash
# คอมไพล์
javac Product.java

# รันโปรแกรม
java Product
```

## 📊 รายละเอียดแต่ละหัวข้อ

### CPU Scheduling
โปรแกรมจำลองการทำงานของ CPU Scheduler ต่างๆ:
- **SJF (Shortest Job First)**: จัดลำดับงานตามระยะเวลาสั้นที่สุดก่อน
- **Round Robin**: จัดสรรเวลาให้แต่ละงานเท่าๆ กัน
- **Priority**: จัดลำดับงานตาม Priority

### Memory Management
- **Paging**: การแบ่งหน่วยความจำเป็นหน้าๆ ขนาดเท่ากัน
- **Segmentation**: การแบ่งหน่วยความจำตามลักษณะการใช้งาน

### Page Replacement
อัลกอริทึมการเลือกเพจที่จะถูกแทนที่เมื่อหน่วยความจำเต็ม:
- **FIFO**: First In First Out
- **LRU**: Least Recently Used  
- **Optimal**: เลือกเพจที่จะไม่ถูกใช้ในอนาคตไกลที่สุด

### Deadlock Prevention
- **Banker's Algorithm**: ตรวจสอบและป้องกัน Deadlock ในระบบ

## 🛠️ ความต้องการของระบบ

- **C++ Compiler**: GCC, Clang หรือ Visual Studio
- **Java**: JDK 8 หรือสูงกว่า
- **IDE แนะนำ**: NetBeans, IntelliJ IDEA, หรือ VS Code

## 📝 หมายเหตุ
- โปรแกรมเหล่านี้เป็นตัวอย่างเพื่อการศึกษา
- ไฟล์บางไฟล์มี hardcoded paths ที่อาจต้องปรับแต่งตามระบบของคุณ
- มีคำอธิบายภาษาไทยในโค้ดเพื่อความเข้าใจ

## 🎓 การเรียนรู้
Repository นี้เหมาะสำหรับ:
- นักศึกษาที่เรียนวิชา Operating Systems

---
*สร้างขึ้นเพื่อการศึกษาด้าน Operating Systems* 
