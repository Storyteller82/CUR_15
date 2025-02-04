#include <stdint.h>

struct sensor
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minit;
    int8_t t;
};


float average_month_temperature (struct sensor* info, long n, uint8_t month);

int8_t max_month_temperature (struct sensor* info, long n, uint8_t month);

int8_t min_month_temperature (struct sensor* info, long n, uint8_t month);

float average_annual_temperature (struct sensor* info, long n);

int8_t max_annual_temperature (struct sensor* info, long n);

int8_t min_annual_temperature (struct sensor* info, long n);

long read_txt_file_to_info (char *name_of_file, struct sensor* info);


// ==============================================================================================
// ================================= старые функции =============================================
// ==============================================================================================


unsigned int DateToInt (struct sensor* info); // Преобразовать дату в одно число

void SortByDate (struct sensor* info, long n); // Сортировка по дате

void AddRecord (struct sensor* info, long number, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minit, int8_t t);

void print (struct sensor* info, long number);

void load_bin (struct sensor* info, long number);

void save_bin (struct sensor* info, long number);

void changeIJ (struct sensor* info, long i, long j); // Обмен местами

void SortByT (struct sensor* info, long n); // Упорядочить по возрастанию температуры

int AddInfo (struct sensor* info);