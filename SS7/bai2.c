#include <stdio.h>

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;
    float ratedPowerKW;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main() {
    struct SmartDevice dev;
    struct EnergySensor sen;
    float operatingHours;

    float totalKWh = 0.0f;
    float totalCost = 0.0f;
    float remainingKWh = 0.0f;

    printf("=== NHAP THONG TIN THIET BI ===\n");
    printf("Nhap Ma thiet bi: ");
    scanf("%d", &dev.deviceID);
    printf("Nhap Ten thiet bi: ");
    scanf(" %[^\n]", dev.deviceName);
    printf("Nhap Trang thai (1 - Bat, 0 - Tat): ");
    scanf("%d", &dev.status);
    printf("Nhap Cong suat dinh muc (kW): ");
    scanf("%f", &dev.ratedPowerKW);

    printf("\n=== NHAP THONG TIN CAM BIEN ===\n");
    printf("Nhap Dien ap do duoc (V): ");
    scanf("%f", &sen.voltageVolts);
    printf("Nhap Dong dien do duoc (A): ");
    scanf("%f", &sen.currentAmperes);
    printf("Nhap Thoi gian vang nguoi (phut): ");
    scanf("%d", &sen.unoccupancyMinutes);

    printf("\nNhap so gio van hanh trong thang (h): ");
    scanf("%f", &operatingHours);

    if (sen.voltageVolts < 0.0f || sen.currentAmperes < 0.0f || sen.unoccupancyMinutes < 0) {
        printf("\n[LOI PHAN CUNG] Thong so cam bien khong hop le (phat hien chi so am). Huy thao tac!\n");
        return 1;
    }

    if (operatingHours <= 0.0f || operatingHours > 744.0f) {
        printf("\n[LOI DU LIEU] Thoi gian van hanh khong hop le (phai > 0 va <= 744 gio). Tu choi tinh toan!\n");
        return 1;
    }

    printf("\n=== KET QUA XU LY HE THONG ===\n");
    
    if (sen.currentAmperes > 30.0f) {
        dev.status = 0;
        printf("[CANH BAO NGUY HIEM] Dong dien vuot ngung an toan (%.2fA > 30.0A)! Kich hoat ngat dien khan cap chong chay no.\n", sen.currentAmperes);
    } 
    else if (dev.status == 1 && sen.unoccupancyMinutes >= 15) {
        dev.status = 0;
        printf("[THONG BAO TIET KIEM] Phong vang nguoi %d phut. He thong tu dong tat thiet bi %s.\n", sen.unoccupancyMinutes, dev.deviceName);
    } else {
        printf("[TRANG THAI] Thiet bi hoat dong trong nguong an toan va phu hop.\n");
    }

    totalKWh = dev.ratedPowerKW * operatingHours;
    remainingKWh = totalKWh;

    if (remainingKWh > 50.0f) {
        totalCost += 50.0f * 1806.0f;
        remainingKWh -= 50.0f;
    } else {
        totalCost += remainingKWh * 1806.0f;
        remainingKWh = 0.0f;
    }

    if (remainingKWh > 0.0f) {
        if (remainingKWh > 50.0f) {
            totalCost += 50.0f * 1866.0f;
            remainingKWh -= 50.0f;
        } else {
            totalCost += remainingKWh * 1866.0f;
            remainingKWh = 0.0f;
        }
    }

    if (remainingKWh > 0.0f) {
        if (remainingKWh > 100.0f) {
            totalCost += 100.0f * 2167.0f;
            remainingKWh -= 100.0f;
        } else {
            totalCost += remainingKWh * 2167.0f;
            remainingKWh = 0.0f;
        }
    }

    if (remainingKWh > 0.0f) {
        totalCost += remainingKWh * 2729.0f;
        remainingKWh = 0.0f;
    }

    printf("\n=== BAO CAO TIEU THU DIEN NANG & HOA DON EVN ===\n");
    printf("Ma thiet bi        : %d\n", dev.deviceID);
    printf("Ten thiet bi       : %s\n", dev.deviceName);
    printf("Trang thai hien tai: %s\n", dev.status ? "BAT" : "TAT");
    printf("So gio van hanh    : %.2f gio\n", operatingHours);
    printf("Tong dien nang     : %.2f kWh\n", totalKWh);
    printf("Tong tien dien     : %.0f VNÐ (chua bao gom VAT)\n", totalCost);

    return 0;
}
