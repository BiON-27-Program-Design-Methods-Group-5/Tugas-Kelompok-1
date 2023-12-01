#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct
{
    char date[20];
    int roomNum;
    double totalMoney; // Ubah tipe data menjadi double
} Payment;

void readPaymentsFromFile(FILE *file, Payment payments[], int *numPayments)
{
    char line[MAX_LINE_LENGTH];
    *numPayments = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        if (line[0] == '#' || line[0] == '\n')
        {
            // Baris komentar atau pemisah
            continue;
        }

        sscanf(line, "Date: %s", payments[*numPayments].date);
        fgets(line, MAX_LINE_LENGTH, file);
        sscanf(line, "RoomNum: %d", &payments[*numPayments].roomNum);
        fgets(line, MAX_LINE_LENGTH, file);
        sscanf(line, "TotalMoney: %lf", &payments[*numPayments].totalMoney); // Ubah tipe data menjadi double

        (*numPayments)++;
    }
}

void processPayments(Payment payments[], int numPayments)
{
    int onTimeRooms[100];  // Daftar kamar yang membayar tepat waktu
    int lateRooms[100];    // Daftar kamar yang membayar tidak tepat waktu
    int warningRooms[100]; // Daftar kamar yang diberi peringatan
    int onTimeCount = 0, lateCount = 0, warningCount = 0;
    double totalMoney = 0.0; // Ubah tipe data menjadi double

    // Proses data pembayaran
    for (int i = 0; i < numPayments; i++)
    {
        // Simulasi: Anggap tanggal batas pembayaran adalah 5 Juni 2020
        if (strcmp(payments[i].date, "5") == 0)
        {
            warningRooms[warningCount++] = payments[i].roomNum;
        }
        else
        {
            if (strcmp(payments[i].date, "5") > 0)
            {
                lateRooms[lateCount++] = payments[i].roomNum;
            }
            else
            {
                onTimeRooms[onTimeCount++] = payments[i].roomNum;
            }
        }

        totalMoney += payments[i].totalMoney;
    }

    // Tampilkan output
    printf("Kamar yang sudah membayar tepat waktu: ");
    for (int i = 0; i < onTimeCount; i++)
    {
        printf("%d", onTimeRooms[i]);
        if (i < onTimeCount - 1)
        {
            printf(",");
        }
    }
    printf("\n");

    printf("Kamar yang sudah membayar tidak tepat waktu: ");
    for (int i = 0; i < lateCount; i++)
    {
        printf("%d", lateRooms[i]);
        if (i < lateCount - 1)
        {
            printf(",");
        }
    }
    printf("\n");

    printf("Kamar yang diberi peringatan: ");
    for (int i = 0; i < warningCount; i++)
    {
        printf("%d", warningRooms[i]);
        if (i < warningCount - 1)
        {
            printf(",");
        }
    }
    printf("\n");

    printf("Jumlah total uang pembayaran: Rp. %.2f,-\n", totalMoney); // Ubah format tampilan menjadi double
}

int main()
{
    FILE *file = fopen("TransactionRecord.txt", "r");
    if (file == NULL)
    {
        printf("Gagal membuka file TransactionRecord.txt\n");
        return 1;
    }

    Payment payments[100];
    int numPayments;
    printf("\n==================================\n");
    printf("PROGRAM PENCATATAN PEMBAYARAN KOST");
    printf("\n==================================\n\n");
    // Panggil fungsi untuk membaca data dari file
    readPaymentsFromFile(file, payments, &numPayments);

    // Panggil fungsi untuk memproses data pembayaran dan menampilkan output
    processPayments(payments, numPayments);

    fclose(file);
    return 0;
}
