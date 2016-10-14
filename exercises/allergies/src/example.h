#ifndef _ALLERGIES_H
#define _ALLERGIES_H

#include <stdbool.h>

typedef enum
{
   Allergen_First = 0,
   Allergen_Eggs = Allergen_First,
   Allergen_Peanuts,
   Allergen_Shellfish,
   Allergen_Strawberries,
   Allergen_Tomatoes,
   Allergen_Chocolate,
   Allergen_Pollen,
   Allergen_Cats,
   Allergen_Last = Allergen_Cats
} Allergen_t;

typedef struct
{
   int count;
   Allergen_t *allergens;
} Allergen_List_t;

bool is_allergic_to(Allergen_t allergen, int score);
void get_allergens(int score, Allergen_List_t *list);

#endif
