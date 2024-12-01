// Assignment 2 24T1 COMP1511: Crepe Stand
// crepe_stand.c
//
// This program was written by Carlson Perez (z5582492)
// on 2024-03-31
//
// Version 1.0.0: Assignment released.
//
// This program is a digital version of a crepe stand. You can order your own 
// crepes and the possibilites are endless! You can choose from custom 
// crepes or signature crepes. You can customise the size of your crepe with a
// custom crepe and can get the most massive crepe in all of Australia! (Be 
// prepared to get an earful from your wallet later...) You can do literally 
// everything you can think of in this program. Do you need to delete a crepe 
// because you realised you do not want diabetes? Do you want look at how many 
// orders you made on one day? Do you want to see how much profit this crepe 
// stand makes? Do you want to know if this crepe stand is a scam? Well look no 
// further. This program does absolutely all of the above! (and more...) 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crepe_stand.h"

#define SIG_STRAWBERRY 's'
#define SIG_MATCHA 'm'
#define SIG_CHOCOLATE 'c'
#define NO_SIG_SOLD 'n'
#define NO_SIG_MOST_POP 'N'

#define TRUE 1
#define FALSE 0
#define YES 3
#define NO 2
#define RESET 0
#define NONE 0
#define BEGIN_COUNTING 0
#define POSITION_LAST 1
#define POSITION_FIRST 1
#define CUSTOMER_ORDER 0
#define THE_SAME 0
#define MIN_POSITION 1
#define MIN_BATTER 0
#define MAX_BATTER 2
#define MIN_TOPPING 0
#define MAX_TOPPING 3
#define MIN_SIZE 10
#define MAX_SIZE 40
#define SMALL 20 
#define REGULAR 25
#define MEDIUM 30
#define LARGE 40
#define ORIGINAL 0
#define CHOCOLATE 1
#define MATCHA 2
#define BANANA 1
#define STRAWBERRY 2
#define NUTELLA 3
#define ORIGINAL_BATTER_PRICE 8.00
#define CHOCOLATE_BATTER_PRICE 8.00
#define MATCHA_BATTER_PRICE 9.50
#define GLUTEN_FREE_PRICE 0.60
#define BANANA_TOPPING_PRICE 2.00
#define STRAWBERRY_TOPPING_PRICE 2.00
#define NUTELLA_TOPPING_PRICE 3.50
#define NO_ADDITIONAL_CHARGES 0.00
#define MEDIUM_SIZE_PRICE 2.50
#define LARGE_SIZE_PRICE 3.50
#define EARLIER -1
#define LATER 1
#define WEEKEND 1
#define WEEKDAY 0
#define SATURDAY 6
#define SUNDAY 0
#define WEEKEND_RENT 50.00
#define WEEKDAY_RENT 35.00
#define ONLY_DAY 1
#define BREAK_EVEN 0
#define FORWARDS '>'
#define NUMBER_OF_DAYS 7
#define NUMBER_OF_MONTHS 12
#define MARCH 3
#define TABLE_OF_MONTH_OFFSETS { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }
#define JANUARY_THE_FIRST_2024 {2024, 1, 1}

////////////////////////////////////////////////////////////////////////////////

// A single crepe
//      Stores all the information about a single crepe.
//      Forms a linked list of crepes by pointing to the next one (or NULL).
struct crepe {
    // Name of the customer who ordered the crepe
    char customer_name[MAX_STR_LEN];

    // The batter the crepe will be made out of
    // ORIGINAL, CHOCOLATE or MATCHA
    enum batter_type batter;

    // There can be no topping or one topping
    // NO_TOPPING, BANANA, STRAWBERRY, NUTELLA
    enum topping_type topping;

    // Whether or not the crepe is gluten free;
    // Can be 1 or 0
    int is_gluten_free;

    // Size of the crepe in centimeters
    int diameter_cm;

    // A pointer to the next crepe in the orders list
    // Is NULL if this crepe is the tail of the list.
    struct crepe *next;
};

// A particular day's list of orders
struct day {
    // Date of the day as a struct day, with fields year, month, day
    struct date date;

    // A pointer to the start of the list of this day's orders
    struct crepe *orders;

    // The total income for the day
    // i.e. the total summed price of all crepes
    double income;

    // A pointer to the next day's orders
    // Is NULL if this day is the tail of the list.
    struct day *next;
};

// Add any other structs you define here.
struct yearly_profit {
    double data;
    struct date date;
    struct yearly_profit *next;
};
////////////////////////////////////////////////////////////////////////////////

// Stage 1

// Verifies the customer has chosen the correct options for their custom crepe.
int crepe_verifier(int position,
                   enum batter_type batter,
                   enum topping_type topping,
                   int is_gluten_free,
                   int diameter_cm);

// Adds a crepe at the end of the list.
void append_crepe(struct day *current_day,
                  char *customer_name, 
                  enum batter_type batter, 
                  enum topping_type topping, 
                  int is_gluten_free,
                  int diameter_cm);

// Initialises the values of a signature crepe.
void select_signature_crepe(char *crepe_type,
                            enum batter_type *batter,
                            enum topping_type *topping,
                            int *is_gluten_free);

// Creates a new custom crepe
//
// Parameters:
//      customer_name - name of customer ordering
//      batter - batter base of crepe
//      topping - topping for the crepe
//      is_gluten_free - 1 if it is GF, 0 if not
//      diameter_cm - how large crepe is in cm
// Returns:
//      pointer to newly created struct crepe
//
struct crepe *create_crepe(char *customer_name,
                           enum batter_type batter,
                           enum topping_type topping,
                           int is_gluten_free,
                           int diameter_cm);


// Stage 2

// Inserts a crepes to the desired position in the order list.
void insert_crepe(struct day *current_day,
                  int position,
                  char *customer_name, 
                  enum batter_type batter, 
                  enum topping_type topping, 
                  int is_gluten_free,
                  int diameter_cm);

// Counts how many orders were original, chocolate or matcha.
void count_batter(struct stats **todays_stats,
                  struct crepe *current);

// Counts how many times an ordered crepe was gluten_free.
void count_gluten_free(struct stats **todays_stats,
                       struct crepe *current); 

// Counts how many orders had the topping banana, strawberry or nutella.
void count_topping(struct stats **todays_stats,
                   struct crepe *current,
                   int *banana,
                   int *strawberry,
                   int *nutella,
                   int *none); 

// Counts how many smalls, mediums and larges were ordered
void count_size(struct stats **todays_stats,
                struct crepe *current);                

// Determines the most popular topping for the day.
void popular_topping(struct stats **todays_stats,
                     int banana,
                     int strawberry,
                     int nutella,
                     int none);

// Calculates the price of one crepe.
double add (struct crepe *current);
// Stage 3

// Counts how many days there are in the list.
int count_days(struct day *number_of_days);

// Determines which date comes earlier.
int compare_dates(struct date date_one, 
                  struct date date_two);

// Counts the amount of signature crepes that were ordered for the day.
struct stats *count_signature(struct day *current_day, 
                              char *signature);

// Move forwards in the day list.
void cycle_forwards(struct day **day_one, 
                    struct day **current_day);

// Move backwards in the day list.
void cycle_backwards(struct day **day_one, 
                     struct day **current_day);

// If there is only one day in the list it will remove that day and replace it
// with a new one.
void removing_the_only_day(struct day **day_one,
                           struct day ***current_day);

// If the day being deleted is the first day it will remove it.
void deleting_first_day(struct day **current);

// If the day being deleted is not the first day, i.e second, third, fourth,
// etc., it will remove it.
void deleting_day_that_is_not_first(struct day **current,
                                    struct day **prev);

// Stage 4

// Determines whether or not the given date is a weekend or not.
int is_weekend(struct date date);

// Determines whether or not the given years are equivalent.
int is_same_year(int year_one, 
                 int year_two);

// Transfers data about the years profit into a struct called yearly_profit.
void store_yearly_profit_period(struct day *day_one,
                                int year,
                                struct yearly_profit **profit);

// Accesses a struct called yearly_profit and calculates the maximum profit 
// using the data available.
void calculate_max_profit(struct yearly_profit *profit,
                          struct date *start_date,
                          struct date *end_date,
                          double *max_profit
                        );

// Clears all the memory used in yearly_profit.
void clear_yearly_profit(struct yearly_profit *profit);

// Fills the fields needed for struct max_profit.
struct max_profit stats_max_profit(struct yearly_profit *profit);
//////////////////////////////////////////////////////////////////////
//                        Stage 1 Functions                         //
//////////////////////////////////////////////////////////////////////

struct day *create_day(struct date new_date) {
    struct day *new_day = calloc(1, sizeof(struct day));
    new_day->date.year = new_date.year;
    new_day->date.month = new_date.month;
    new_day->date.day = new_date.day;

    return new_day;
}

struct crepe *create_crepe(char *customer_name,
                           enum batter_type batter,
                           enum topping_type topping,
                           int is_gluten_free,
                           int diameter_cm) {
    struct crepe *new_crepe = malloc(sizeof(struct crepe));
    strcpy(new_crepe->customer_name, customer_name);
    new_crepe->batter = batter;
    new_crepe->topping = topping;
    new_crepe->is_gluten_free = is_gluten_free;
    new_crepe->diameter_cm = diameter_cm;
    new_crepe->next = NULL;
    
    return new_crepe;
}

int append_crepe_custom(struct day *current_day,
                        char *customer_name,
                        enum batter_type batter,
                        enum topping_type topping,
                        int is_gluten_free,
                        int diameter_cm) {
    int status = crepe_verifier(POSITION_LAST, 
                                batter, 
                                topping, 
                                is_gluten_free, 
                                diameter_cm);
    if (status != VALID_CREPE) {
        return status;
    }

    append_crepe(current_day,
                 customer_name, 
                 batter, 
                 topping, 
                 is_gluten_free,
                 diameter_cm);
    return VALID_CREPE;
}

int append_crepe_signature(struct day *current_day,
                           char *customer_name,
                           char *crepe_type) {
    enum batter_type batter;
    enum topping_type topping;
    int is_gluten_free;

    select_signature_crepe(crepe_type,
                           &batter,
                           &topping,
                           &is_gluten_free);

    append_crepe(current_day,
                 customer_name, 
                 batter, 
                 topping, 
                 is_gluten_free,
                 REGULAR);
    return VALID_CREPE;
}

void print_crepes(struct day *current_day) {
    struct crepe *current = current_day->orders;
    for (int i = 1; i - 1 < count_crepes(current_day); i++) {
        print_single_crepe(current, i);
        if (i < count_crepes(current_day)) {
            print_arrow();
        }
        current = current->next;
    }
    if (count_crepes(current_day) == NONE) {
        print_no_crepes();
    }
}

int count_crepes(struct day *current_day) {
    struct crepe *current = current_day->orders;
    int counter = BEGIN_COUNTING;
    while (current != NULL) {
        current = current->next;
        counter++;
    }
    return counter;
}

// Ensures that the inputs for making a custom crepe is valid.
int crepe_verifier(int position,
                   enum batter_type batter,
                   enum topping_type topping,
                   int is_gluten_free,
                   int diameter_cm) {
    if (position < MIN_POSITION) {
        return INVALID_POSITION;
    } else if (!(MIN_BATTER <= batter && batter <= MAX_BATTER)) {
        return INVALID_BATTER;
    } else if (!(MIN_TOPPING <= topping && topping <= MAX_TOPPING)) {
        return INVALID_TOPPING;
    } else if (is_gluten_free != TRUE && is_gluten_free != FALSE) {
        return INVALID_GFO;
    } else if (diameter_cm < MIN_SIZE || diameter_cm >= MAX_SIZE) {
        return INVALID_SIZE;
    }
    return VALID_CREPE; 
}

// Adds the crepe order to the end of the order list.
void append_crepe(struct day *current_day,
                  char *customer_name, 
                  enum batter_type batter, 
                  enum topping_type topping, 
                  int is_gluten_free,
                  int diameter_cm) {
    struct crepe *new_crepe = create_crepe(customer_name, 
                                           batter, 
                                           topping, 
                                           is_gluten_free,
                                           diameter_cm);
    if (current_day->orders == NULL) {
        current_day->orders = new_crepe;
    } else {
        struct crepe *current = current_day->orders;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_crepe;
    }
}

// Initialises the values of batter, topping and gluten_free when the crepe 
// selected is signature.
void select_signature_crepe(char *crepe_type,
                            enum batter_type *batter,
                            enum topping_type *topping,
                            int *is_gluten_free) {

    if (strcmp(crepe_type, "matcha") == CUSTOMER_ORDER) {
        *batter = MATCHA;
        *topping = STRAWBERRY;
        *is_gluten_free = NO;            
    } else if (strcmp(crepe_type, "strawberry") == CUSTOMER_ORDER) {
        *batter = ORIGINAL;
        *topping = STRAWBERRY;
        *is_gluten_free = YES; 
    } else if (strcmp(crepe_type, "chocolate") == CUSTOMER_ORDER) {
        *batter = CHOCOLATE;
        *topping = NUTELLA;
        *is_gluten_free = NO; 
    } 
}

//////////////////////////////////////////////////////////////////////
//                        Stage 2 Functions                         //
//////////////////////////////////////////////////////////////////////

int insert_crepe_custom(struct day *current_day,
                        int position,
                        char *customer_name,
                        enum batter_type batter,
                        enum topping_type topping,
                        int is_gluten_free,
                        int diameter_cm) {
     
    int status = crepe_verifier(position, 
                                batter, 
                                topping, 
                                is_gluten_free, 
                                diameter_cm);
    if (status != VALID_CREPE) {
        return status;
    }

    insert_crepe(current_day,
                 position,
                 customer_name, 
                 batter, 
                 topping, 
                 is_gluten_free,
                 diameter_cm);
    return VALID_CREPE;
}

int insert_crepe_signature(struct day *current_day,
                           int position,
                           char *customer_name,
                           char *crepe_type) {
    enum batter_type batter = NONE;
    enum topping_type topping = NONE;
    int is_gluten_free = NONE;

    int status = crepe_verifier(position, 
                                batter, 
                                topping, 
                                is_gluten_free, 
                                REGULAR);
    if (status != VALID_CREPE) {
        return status;
    }

    select_signature_crepe(crepe_type,
                           &batter,
                           &topping,
                           &is_gluten_free);

    insert_crepe(current_day,
                 position,
                 customer_name, 
                 batter, 
                 topping, 
                 is_gluten_free,
                 REGULAR);
    return VALID_CREPE;
}

struct stats get_stats(struct day *current_day) {
    struct stats *todays_stats = calloc(1, sizeof(struct stats));
    todays_stats->total_crepes = count_crepes(current_day);
    int banana = BEGIN_COUNTING;
    int strawberry = BEGIN_COUNTING;
    int nutella = BEGIN_COUNTING;
    int none = BEGIN_COUNTING;

    struct crepe *current = current_day->orders;
    while (current != NULL) {
        count_batter(&todays_stats, current);
        count_gluten_free(&todays_stats, current);
        count_topping(
            &todays_stats, current, &banana, &strawberry, &nutella, &none
        );
        count_size(&todays_stats, current);
        current = current->next;
    }
    popular_topping(&todays_stats, banana, strawberry, nutella, none);

    return *todays_stats;
}

double calculate_price(struct day *current_day, 
                       int position) {
    struct crepe *current = current_day->orders;
    if (
        (position < POSITION_FIRST ||
        position > count_crepes(current_day))
    ) {
        return INVALID_POSITION;
    }
    
    for (int i = 1; i < position; i++) {
        current = current->next;
    }

    return add(current);
}

double total_income(struct day *current_day) {
    struct crepe *current = current_day->orders;
    double total = BEGIN_COUNTING;
    for (int i = 1; current != NULL; i++) {
        total += calculate_price(current_day, i);
        current = current->next;
    }
    return total;
}

struct bill customer_bill(struct day *current_day, 
                          char *customer_name) {
    struct crepe *current = current_day->orders;
    struct bill customer;
    customer.total_price = BEGIN_COUNTING;
    customer.crepe_count = BEGIN_COUNTING;
    for (int i = 1; current != NULL; i++) {
        if (strcmp(customer_name, current->customer_name) == THE_SAME) {
            customer.total_price += calculate_price(current_day, i);
            customer.crepe_count += 1;
        }
        current = current->next;
    }
    return customer;
}

// Inserts crepe to the desired position. If the position is greater than the 
// number of crepes on the order list, then the crepe will be inserted at the 
// end of the list.
void insert_crepe(struct day *current_day,
                  int position,
                  char *customer_name, 
                  enum batter_type batter, 
                  enum topping_type topping, 
                  int is_gluten_free,
                  int diameter_cm) {

    struct crepe *new_crepe = create_crepe(
                                        customer_name, 
                                        batter, 
                                        topping, 
                                        is_gluten_free,
                                        diameter_cm);

    struct crepe *insertion = current_day->orders;
    insertion = new_crepe;
    if (position == POSITION_FIRST || current_day->orders == NULL) {
        insertion->next = current_day->orders;
        current_day->orders = insertion;
    } else {
        struct crepe *current = current_day->orders;
        for (int i = 1; current->next != NULL && i < position - 1; i++) {
            current = current->next;
        }
        insertion->next = current->next;
        current->next = insertion;
    }
}

// Categorises the type of batter ordered for the crepe order into original,
// chocolate and matcha. As it categorises the crepe's batter, it will add to
// the number of the selected batter type.
void count_batter(struct stats **todays_stats,
                  struct crepe *current) {
    if (current->batter == ORIGINAL) {
        (*todays_stats)->original += 1;
    } else if (current->batter == CHOCOLATE) {
        (*todays_stats)->chocolate += 1;
    } else if (current->batter == MATCHA) {
        (*todays_stats)->matcha += 1;
    }
}

// Categorises the crepe order into gluten_free or not gluten_free. It will then
// add to the number of gluten_free crepe orders.
void count_gluten_free(struct stats **todays_stats,
                       struct crepe *current) {
    // There are two options for gluten_free so that there is a way to 
    // distinguish between signature crepes from custom crepes.
    if (current->is_gluten_free == TRUE || current->is_gluten_free == YES) {
        (*todays_stats)->gluten_free += 1;
    }
}

// Categorises the type of topping for the crepe order into banana, strawberry 
// and nutella. As it categorises the crepe's topping, it will add to the number
// of selected topping type.
void count_topping(struct stats **todays_stats,
                   struct crepe *current,
                   int *banana,
                   int *strawberry,
                   int *nutella,
                   int *none) {
    if (current->topping == BANANA) {
        (*banana)++;
    } else if (current->topping == STRAWBERRY) {
        (*strawberry)++;
    } else if (current->topping == NUTELLA) {
        (*nutella)++;
    } else {
        (*none)++;
    }
}

// Categorises the size of the crepe into small, medium and large. As it 
// categorises the crepe's size it will add to the number of selected crepe 
// size.
void count_size(struct stats **todays_stats,
                struct crepe *current) {
    if (current->diameter_cm < SMALL) {
        (*todays_stats)->small += 1;
    } else if (current->diameter_cm < MEDIUM) {
        (*todays_stats)->medium += 1;
    } else if (current->diameter_cm < LARGE) {
        (*todays_stats)->large += 1;
    }
}

// Determines which topping was the most popular for the day. 
void popular_topping(struct stats **todays_stats,
                     int banana,
                     int strawberry,
                     int nutella,
                     int none) {
    if (banana > strawberry && banana > nutella && banana > none) {
        (*todays_stats)->popular_topping = BANANA;
    } else if (
        strawberry > banana && strawberry > nutella && strawberry > none
        ) {
        (*todays_stats)->popular_topping = STRAWBERRY;
    } else if (nutella > banana && nutella > strawberry && nutella > none) {
        (*todays_stats)->popular_topping = NUTELLA;
    } else {
        (*todays_stats)->popular_topping = NONE;
    } 
}

// Adds up all the fees for the batter, gluten_free option, topping and size
// selections.
double add(struct crepe *current) {
    double total = NONE;

    if (current->batter == ORIGINAL) {
        total += ORIGINAL_BATTER_PRICE;
    } else if (current->batter == CHOCOLATE) {
        total += CHOCOLATE_BATTER_PRICE;
    } else if (current->batter == MATCHA) {
        total += MATCHA_BATTER_PRICE;
    }

    // There are two options for gluten_free so that there is a way to 
    // distinguish between signature crepes from custom crepes.
    if (current->is_gluten_free == TRUE || current->is_gluten_free == YES) {
        total += GLUTEN_FREE_PRICE;
    }
    
    if (current->topping == BANANA) {
        total += BANANA_TOPPING_PRICE;
    } else if (current->topping == STRAWBERRY) {
        total += STRAWBERRY_TOPPING_PRICE;
    } else if (current->topping == NUTELLA) {
        total += NUTELLA_TOPPING_PRICE;
    }

    if (current->diameter_cm < SMALL) {
        total += NO_ADDITIONAL_CHARGES;
    } else if (current->diameter_cm < MEDIUM) {
        total += MEDIUM_SIZE_PRICE;
    } else if (current->diameter_cm < LARGE) {
        total += LARGE_SIZE_PRICE;
    }

    return total;
}

//////////////////////////////////////////////////////////////////////
//                        Stage 3 Functions                         //
//////////////////////////////////////////////////////////////////////

struct day *new_day(struct day *day_one, 
                    struct date date) {
    struct day *insertion = create_day(date);
    struct day *current = day_one;
    struct day *prev = NULL;

    while (current != NULL) {
        if (compare_dates(date, current->date) == THE_SAME) {
            free(insertion); 
            return NULL; 
        }
        current = current->next;
    }

    current = day_one; 

    // LATER refers to the new date coming later than the current date.
    while (current != NULL && compare_dates(date, current->date) == LATER) {
        prev = current;
        current = current->next;
    }
    if (prev == NULL) {
        insertion->next = day_one;
        return insertion;
    } else {
        prev->next = insertion;
        insertion->next = current;
        return day_one;
    }
}

void display_days(struct day *day_one, 
                  struct day *current_day) {
    struct day *current = day_one;
    int total_days = count_days(day_one);
    char signature;

    for (int i = 1; i <= total_days; i++) {
        int today = BEGIN_COUNTING;
        if (current_day == current) {
            today = TRUE;
        }

        struct stats *todays_stats = count_signature(current, &signature);
    
        print_single_day(
            today, current->date, signature, total_income(current)
        );

        if (i < total_days) {
            print_arrow();
        }

        free(todays_stats);
        current = current->next;
    }
}

struct day *cycle_days(char command,
                       struct day *day_one,
                       struct day *current_day) {
    if (command == FORWARDS) {
        cycle_forwards(&day_one, &current_day);
    } else {
        cycle_backwards(&day_one, &current_day);
    }
    return current_day;
}

int remove_crepe(struct day *current_day, 
                 int position) {
    int total_crepes = count_crepes(current_day);
    if (position < POSITION_FIRST || position > total_crepes) {
        return INVALID_POSITION;
    }
    struct crepe *current = current_day->orders;
    if (position == POSITION_FIRST) {
        current_day->orders = current->next;
        free(current);
    } else {
        for (int i = 1; i < position - 1; i++) {
            current = current->next;
        }
        struct crepe *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    return VALID_CREPE;
}

struct day *remove_day(struct day *day_one,
                       struct day **current_day,
                       struct date date) {
    struct day *current = day_one;
    struct day *prev = NULL;
    while (current != NULL) {
        if (compare_dates(date, current->date) == THE_SAME) {
            if (count_days(day_one) == ONLY_DAY) {
                removing_the_only_day(&day_one, &current_day);
                return *current_day;
            }
            if (
                compare_dates(current->date, (*current_day)->date) == THE_SAME
            ) {
                *current_day = cycle_days(FORWARDS, day_one, *current_day);
            }
            if (prev == NULL) {
                deleting_first_day(&current);
                return current;
            } else {
                deleting_day_that_is_not_first(&current, &prev);
                return day_one;
            }
        }
        prev = current;
        current = current->next;
    }
    return NULL;
    
}

void free_crepe_stand(struct day *day_one) {
    struct day *current = day_one;
    struct day *next_day = NULL;
    while (current != NULL) {
        int total_crepes = count_crepes(current);
        for (int i = 0; i < total_crepes; i++) {
            remove_crepe(current, POSITION_FIRST);
        }
        next_day = current->next;
        free(current);
        current = next_day;
    }
}

// Determines which date comes first. If the first date comes first it will 
// return EARLIER but if the first date comes later it will return LATER. 
// If the dates are the same then it will return THE_SAME
int compare_dates(struct date date_one, 
                  struct date date_two) {
    if (date_one.year < date_two.year)
        return EARLIER;
    else if (date_one.year > date_two.year)
        return LATER;
    
    if (date_one.month < date_two.month)
        return EARLIER;
    else if (date_one.month > date_two.month)
        return LATER;
    
    if (date_one.day < date_two.day)
        return EARLIER;
    else if (date_one.day > date_two.day)
        return LATER;
    
    return THE_SAME;
}

// Counts the total amount of days that have been listed.
int count_days(struct day *number_of_days) {
    struct day *current = number_of_days;
    int counter = BEGIN_COUNTING;
    while (current != NULL) {
        current = current->next;
        counter++;
    }
    return counter;
}

// This is different to the count_batter function as it separates the signature
// crepes from the custom crepes by adding the if statement is_gluten_free ==
// NO or YES which is different to the is_gluten_free == FALSE or TRUE for the 
// custom crepes. This results in the function being able to determine the 
// most popular signature crepe.
struct stats *count_signature(struct day *current_day, 
                              char *signature) {
    struct stats *todays_stats = calloc(1, sizeof(struct stats));
    todays_stats->total_crepes = count_crepes(current_day);
    
    struct crepe *current = current_day->orders;
    int total_signature_crepes = NONE;
    while (current != NULL) {
        if (current->is_gluten_free == NO || current->is_gluten_free == YES) {
            count_batter(&todays_stats, current);
            total_signature_crepes++;
        }
        current = current->next;
    }
    
    if (
        todays_stats->original > todays_stats->chocolate && 
        todays_stats->original > todays_stats->matcha
    ) {
        *signature = SIG_STRAWBERRY;
    } else if (
        todays_stats->matcha > todays_stats->original && 
        todays_stats->matcha > todays_stats->chocolate
    ) {
        *signature = SIG_MATCHA;
    } else if (
        todays_stats->chocolate > todays_stats->original && 
        todays_stats->chocolate > todays_stats->matcha
    ) {
        *signature = SIG_CHOCOLATE;
    } else {
        if (total_signature_crepes == NONE) {
            *signature = NO_SIG_SOLD;
        } else {
            *signature = NO_SIG_MOST_POP;
        }
    }
    return todays_stats;
}

// The current day becomes the next day on the list which is in chronological 
// order. If current day is on the end of the list, the next day becomes the 
// first day on the list.
void cycle_forwards(struct day **day_one, 
                    struct day **current_day) {
    if ((*current_day)->next == NULL) {
        *current_day = *day_one;
    } else {
        *current_day = (*current_day)->next;
    }
}

// The current day becomes the previous day on the list which is in 
// chronological order. If the current day is at the start of the list, the 
// previous day becomes the last day on the list.
void cycle_backwards(struct day **day_one, 
                     struct day **current_day) {
    struct day *prev_day = *day_one;
    if (*current_day == *day_one) {
        while (prev_day->next != NULL) {
            prev_day = prev_day->next;
        }
    } else {
        while (prev_day->next != *current_day) {
            prev_day = prev_day->next;
        }
    }
    *current_day = prev_day;
}

// If there is only one day, the day is removed and replaced by the date 
// 2024/01/01 so that there will always be a day so that crepes can be added.
void removing_the_only_day(struct day **day_one,
                           struct day ***current_day) {
    struct date new_date = JANUARY_THE_FIRST_2024;
    struct day *new_day = create_day(new_date);
    free(*day_one);
    new_day->next = NULL;
    **current_day = new_day;
}

// When the day that is being deleted is the first day. This will shift all the 
// days to the left meaning the second day becomes the new first day, the third
// day becomes the second, etc..
void deleting_first_day(struct day **current) {
    // Freeing all the orders that is inside this day.
    for (int i = 1; i <= count_crepes(*current); i++) {
        remove_crepe(*current, POSITION_FIRST);
    }
    struct day *temp = *current;
    *current = (*current)->next;
    free(temp);
}

// When the day that is being deleted is not the first day. This will shift all
// the days to the right of the deleted day to the left meaning that if the 
// third day was deleted, the fourth day will become the new third day and the 
// fifth day will become the new fourth day etc..
void deleting_day_that_is_not_first(struct day **current,
                                    struct day **prev) {

    for (int i = 1; i <= count_crepes(*current); i++) {
        remove_crepe(*current, POSITION_FIRST);
    }
    struct day *temp = (*prev)->next;
    (*prev)->next = temp->next;
    free(temp);
}

//////////////////////////////////////////////////////////////////////
//                        Stage 4 Functions                         //
//////////////////////////////////////////////////////////////////////

struct profits compare_weekday_end(struct day *day_one) {
    struct day *current = day_one;
    double weekday = BEGIN_COUNTING;
    double weekend = BEGIN_COUNTING;
    while (current != NULL) {
        if (is_weekend(current->date) == TRUE) {
            weekend += total_income(current) - WEEKEND_RENT;
        } else {
            weekday += total_income(current) - WEEKDAY_RENT;
        }
        current = current->next;
    }
    struct profits profit = {
        weekday, 
        weekend
    }; 
    return profit;
}

struct max_profit max_profit_period(struct day *day_one, int year) {
    struct yearly_profit *profit = NULL;
    store_yearly_profit_period(day_one, year, &profit);

    if (profit != NULL) {
        struct max_profit max = stats_max_profit(profit);
        return max;
    } else {
        struct max_profit invalid_year = (struct max_profit) {NONE}; 
        return invalid_year;
    }
}

// Determines whether the given date is a weekday or a weekend. 
int is_weekend(struct date date) {

    int day = date.day;
    int month = date.month;
    int year = date.year;


    // https://www.geeksforgeeks.org/find-day-of-the-week-for-a-given-date/

    // https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#
    // Implementation-dependent_methods_of_Sakamoto.2C_Lachman.2C_Keith_and_
    // Craver

    int table_of_month_offset[NUMBER_OF_MONTHS] = TABLE_OF_MONTH_OFFSETS;
    year -= month < MARCH;

    int day_is = (year + year / 4 - year / 100 + year / 400 + 
                  table_of_month_offset[month - 1] + day) % NUMBER_OF_DAYS;

    if (day_is == SATURDAY || day_is == SUNDAY)
        return WEEKEND; 
    else
        return WEEKDAY; 
}

// Determines whether or not the given dates have the same year or not. Returns
// true if they are equivalent, false if they are not.
int is_same_year(int year_one, int year_two) {
    if (year_one == year_two) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// Stores all the profit in the given year in a seperate data structure to 
// help calculate the max profit in the given year period.
void store_yearly_profit_period(struct day *day_one,
                                int year,
                                struct yearly_profit **profit) {
    struct day *current = day_one;
    struct yearly_profit *sales = NULL;
    while (current != NULL) {
        if (is_same_year(year, current->date.year) == TRUE) {
            struct yearly_profit *new_profit = malloc(
                                                sizeof(struct yearly_profit)
                                            );
            if (*profit == NULL) {
                *profit = new_profit;
                sales = *profit;
            } else {
                sales->next = new_profit;
                sales = sales->next;
            }
            if (is_weekend(current->date) == TRUE) {
                sales->data = total_income(current) - WEEKEND_RENT;
                sales->date = current->date;
            } else {
                sales->data = total_income(current) - WEEKDAY_RENT;
                sales->date = current->date;
            }
            sales->next = NULL; 
        } 
        current = current->next;
    }
}

// Iterates through the entire yearly_profit data to find the maxmimum sale 
// within that year's period. It will return the start date, end date as well as 
// the amount of profit gained during that period.
void calculate_max_profit(struct yearly_profit *profit,
                          struct date *start_date,
                          struct date *end_date,
                          double *max_profit
                        ) {
    struct date new_start_date = profit->date;
    struct yearly_profit *current = profit->next;
    double current_profit = profit->data;
    while (current != NULL) {
        if (current_profit < BREAK_EVEN) {
            current_profit = RESET;
            new_start_date = current->date;
        }
        current_profit += current->data;
        // There are two conditional if statements because it appears 
        // 1511 crepe_stand uses a different algorithm to calculate the max
        // profit when the least loss occurs on two different days or when the 
        // max profit is zero. The first if statement accounts for the least 
        // loss. It will return the LATEST day that has the least loss when
        // max profit is tied with another day. The second if statement accounts
        // for when the max profit is zero but two days share a profit of zero
        // with a day of loss in between. It returns the EARLIER day.
        if (*max_profit < BREAK_EVEN && current_profit >= *max_profit) {
            *max_profit = current_profit;
            *end_date = current->date;
            *start_date = new_start_date;
        } else if (current_profit > *max_profit) {
            *max_profit = current_profit;
            *end_date = current->date;
            *start_date = new_start_date;
        }
        current = current->next;
    }
}

// Clears all the memory used in yearly_profit.
void clear_yearly_profit(struct yearly_profit *profit) {
    while (profit != NULL) {
        struct yearly_profit *temp = profit;
        profit = temp->next;
        free(temp);
    }
}

// Fills the fields needed for struct max_profit.
struct max_profit stats_max_profit(struct yearly_profit *profit) {
    struct date start_date = profit->date;
    struct date end_date = profit->date;
    double max_profit = profit->data;

    // Finds the start date, end date and maximum profit yield during the year.
    calculate_max_profit(profit, &start_date, &end_date, &max_profit);

    // Clears all the memory used in yearly_profit.
    clear_yearly_profit(profit);

    struct max_profit stats;
    stats.start_date = start_date;
    stats.profit = max_profit;
    if (
        compare_dates(start_date, end_date) == THE_SAME || 
        max_profit == BREAK_EVEN
    ) {
        stats.end_date = (struct date) {NONE};
    } else {
        stats.end_date = end_date;
    }
    return stats;
}

//////////////////////////////////////////////////////////////////////
//                         Helper Functions                         //
//////////////////////////////////////////////////////////////////////

void print_single_crepe(struct crepe *crepe, int position) {
    printf("---------------------\n");
    printf("%d. %s's crepe\n", position, crepe->customer_name);

    if (crepe->batter == ORIGINAL) {
        printf("Original flavour\n");
    } else if (crepe->batter == MATCHA) {
        printf("Matcha flavour\n");
    } else {
        printf("Chocolate flavour\n");
    }

    printf("Toppings: ");
    if (crepe->topping == NO_TOPPING) {
        printf("none\n");
    } else if (crepe->topping == BANANA) {
        printf("bananas\n");
    } else if (crepe->topping == STRAWBERRY) {
        printf("strawberries\n");
    } else if (crepe->topping == NUTELLA) {
        printf("nutella\n");
    }

    printf("gluten free? ");
    if (crepe->is_gluten_free == TRUE || crepe->is_gluten_free == YES) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    printf("Size: %dcm\n", crepe->diameter_cm);
    printf("---------------------\n");
}

void print_arrow(void) {
    printf("\t|\n\tv\n");
}

void print_no_crepes(void) {
    printf("No crepes have been ordered yet!\n");
}

void print_single_day(int is_current_day,
                      struct date date,
                      char most_pop,
                      double income) {
    printf("---------------------\n");
    if (is_current_day) {
        printf("!CURRENT DAY!\n");
    }
    printf("Date: %04d-%02d-%02d\n", date.year, date.month, date.day);
    if (most_pop == SIG_STRAWBERRY) {
        printf("Most popular signature crepe: Strawberry Special\n");
    } else if (most_pop == SIG_MATCHA) {
        printf("Most popular signature crepe: Matcha Madness\n");
    } else if (most_pop == SIG_CHOCOLATE) {
        printf("Most popular signature crepe: Chocolate Connoisseur\n");
    } else if (most_pop == NO_SIG_SOLD) {
        printf("There were no signature crepes sold!\n");
    } else if (most_pop == NO_SIG_MOST_POP) {
        printf("No signature crepe was more popular than another!\n");
    } else {
        printf("ERROR: %c, unknown most popular character\n", most_pop);
    }
    printf("Total income: $%.2lf\n", income);
    printf("---------------------\n");
}

