#include <stdio.h>
#include <math.h>

struct RawDevice {
    char flag1;
    float voltage;
    char flag2;
    float current;
    int deviceID;
    float power_watt;
    int status;
    int active_minutes;
};

struct OptimizedDevice {
    int deviceID;
    int status;
    int active_minutes;
    float voltage;
    float current;
    float power_watt;
};

int main() {
    struct OptimizedDevice dev;
    float p_calc = 0.0f;
    float diff = 0.0f;
    float kwh = 0.0f;

    printf("=== DANG KY BO NHO STRUCT ===\n");
    printf("Kich thuoc Struct goc (Chua toi uu): %lu bytes\n", (unsigned long)sizeof(struct RawDevice));
    printf("Kich thuoc Struct moi (Da toi uu)  : %lu bytes\n", (unsigned long)sizeof(struct OptimizedDevice));
    printf("Bo nho tiet kiem duoc              : %lu bytes\n\n", (unsigned long)(sizeof(struct RawDevice) - sizeof(struct OptimizedDevice)));

    printf("=== NHAP THONG TIN THIET BI IOT ===\n");
    printf("Nhap Ma thiet bi: ");
    scanf("%d", &dev.deviceID);
    printf("Nhap Trang thai (1 - Bat, 0 - Tat): ");
    scanf("%d", &dev.status);
    printf("Nhap Thoi gian hoat dong (phut): ");
    scanf("%d", &dev.active_minutes);
    printf("Nhap Dien ap U (V): ");
    scanf("%f", &dev.voltage);
    printf("Nhap Dong dien I (A): ");
    scanf("%f", &dev.current);
    printf("Nhap Cong suat do P (W): ");
    scanf("%f", &dev.power_watt);

    if (dev.voltage <= 0.0f || dev.current < 0.0f || dev.active_minutes < 0) {
        printf("\n[LOI CHI SO] Du lieu cam bien khong hop le (U <= 0 hoac I < 0 hoac t < 0). Dung tinh toan!\n");
        return 1;
    }

    if (dev.status != 0 && dev.status != 1) {
        printf("\n[LOI TRANG THAI] Trang thai thiet bi chi nhan gia tri 0 hoac 1. Dung tinh toan!\n");
        return 1;
    }

    printf("\n=== KET QUA PHAN TICH AN TOAN & DIEN NANG ===\n");

    p_calc = dev.voltage * dev.current;
    diff = fabsf(dev.power_watt - p_calc);

    if (p_calc > 0.0f && (diff / p_calc) > 0.05f) {
        printf("[CANH BAO] Cam bien cong suat bao sai lech (Do duoc: %.2f W, Tinh toan U*I: %.2f W)!\n", dev.power_watt, p_calc);
    }

    if (dev.current > 30.0f || dev.power_watt > 6600.0f) {
        printf("[CANH BAO NGUY HIEM] QUA TAI NGUY HIEM (I = %.2f A, P = %.2f W)!\n", dev.current, dev.power_watt);
    }

    if (dev.status == 0 && dev.current > 0.05f) {
        printf("[CANH BAO RO RI] RO RI DIEN HOAC TAI AN (Thiet bi TAT nhung I = %.2f A)!\n", dev.current);
    }

    kwh = (dev.power_watt * (dev.active_minutes / 60.0f)) / 1000.0f;

    printf("\n=== BAO CAO TIEU THU DIEN NANG ===\n");
    printf("Ma thiet bi         : %d\n", dev.deviceID);
    printf("Trang thai          : %s\n", dev.status ? "BAT" : "TAT");
    printf("Thoi gian hoat dong : %d phut (%.2f gio)\n", dev.active_minutes, dev.active_minutes / 60.0f);
    printf("Dien nang tiêu th?  : %.4f kWh\n", kwh);

    return 0;
}

