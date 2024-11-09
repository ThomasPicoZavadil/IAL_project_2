/*
 * Použití binárních vyhledávacích stromů.
 *
 * S využitím Vámi implementovaného binárního vyhledávacího stromu (soubory ../iter/btree.c a ../rec/btree.c)
 * implementujte triviální funkci letter_count. Všimněte si, že výstupní strom může být značně degradovaný
 * (až na úroveň lineárního seznamu). Jako typ hodnoty v uzlu stromu využijte 'INTEGER'.
 *
 */

#include "../btree.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Vypočítání frekvence výskytů znaků ve vstupním řetězci.
 *
 * Funkce inicilializuje strom a následně zjistí počet výskytů znaků a-z (case insensitive), znaku
 * mezery ' ', a ostatních znaků (ve stromu reprezentováno znakem podtržítka '_'). Výstup je
 * uložen ve stromu (klíč vždy lowercase).
 *
 * Například pro vstupní řetězec: "abBccc_ 123 *" bude strom po běhu funkce obsahovat:
 *
 * key | value
 * 'a'     1
 * 'b'     2
 * 'c'     3
 * ' '     2
 * '_'     5
 *
 * Pro implementaci si můžete v tomto souboru nadefinovat vlastní pomocné funkce.
 */

/* Kontrola, zda je znak písmeno */
int is_alpha(char ch)
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

/* Převod velkého písmena na malé */
char to_lower(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        return ch + ('a' - 'A');
    }
    return ch;
}

void letter_count(bst_node_t **tree, char *input)
{
    // Initialize the tree
    bst_init(tree);

    // Traverse the input string
    for (char *ch = input; *ch != '\0'; ch++)
    {
        char key;

        // Determine the character category
        if (is_alpha(*ch))
        {
            key = to_lower(*ch); // Convert alphabetic characters to lowercase
        }
        else if (*ch == ' ')
        {
            key = ' '; // Space character
        }
        else
        {
            key = '_'; // All other characters
        }

        // Check if the key exists in the tree, and retrieve its current count
        bst_node_content_t *current_count;
        if (bst_search(*tree, key, &current_count))
        {
            // Pokud klíč existuje, zvýšíme stávající hodnotu
            int *value_ptr = (int *)current_count->value;
            (*value_ptr)++; // Zvýšíme hodnotu
        }
        else
        {
            // Pokud klíč neexistuje, vytvoříme nový uzel s hodnotou 1
            bst_node_content_t content;
            int *initial_count = malloc(sizeof(int));
            *initial_count = 1; // Nastavení počáteční hodnoty na 1
            content.value = initial_count;
            content.type = INTEGER;

            bst_insert(tree, key, content); // Vložíme nový uzel
        }
    }
}