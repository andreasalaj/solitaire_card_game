#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum card_color
{
  RED,
  BLACK
};

const char card_color_str[] = {'R', 'B'};

enum card_value
{
  V_A,
  V_2,
  V_3,
  V_4,
  V_5,
  V_6,
  V_7,
  V_8,
  V_9,
  V_10,
  V_J,
  V_Q,
  V_K
};

const char *card_value_str[] = {"A ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10", "J ", "Q ", "K "};

typedef struct
{
  enum card_color color;
  enum card_value value;
  struct Card *next; // pointer to next card
  struct Card *prev; // pointer to previous card
} Card;

int readFile(char *filename, Card* deck)
{
  char *red = "RED";
  char *black = "BLACK";
  char *v_a = "A";
  char *v_2 = "2";
  char *v_3 = "3";
  char *v_4 = "4";
  char *v_5 = "5";
  char *v_6 = "6";
  char *v_7 = "7";
  char *v_8 = "8";
  char *v_9 = "9";
  char *v_10 = "10";
  char *v_J = "J";
  char *v_Q = "Q";
  char *v_K = "K";

  int card_num = 0;
  int MAX_LINE_LEN = 1000;
  FILE *input = fopen(filename, "r");
  if (input)
  {
    char temp[MAX_LINE_LEN];
    while (fgets(temp, MAX_LINE_LEN, input))
    {
      char *clean_line = malloc(strlen(temp) + 1);
      char *clp = clean_line;
      char *tmp = temp;
      do
      {
        if (*tmp != ' ')
        {
          *clp = *tmp;
          *clp++;
        }
      } while(*tmp++);

      if (clean_line[0] == '\n')
      {
        continue;
      }

      if(strstr(clean_line, red) != NULL)
      {
        deck[card_num].color = RED;
        char* p = strstr(clean_line, red);
        strncpy(p, "___", 3);
      }
      else if(strstr(clean_line, black) != NULL)
      {
        deck[card_num].color = BLACK;
        char* p = strstr(clean_line, black);
        strncpy(p, "_____", 5);
      }
      else
      {
        printf("[ERR] Invalid file!\n");
        free(clean_line);
        fclose(input);
        return 3;
      }

      if(strstr(clean_line, v_a) != NULL)
      {
        deck[card_num].value = V_A;
      }
      else if(strstr(clean_line, v_2) != NULL)
      {
        deck[card_num].value = V_2;
      }
      else if(strstr(clean_line, v_3) != NULL)
      {
        deck[card_num].value = V_3;
      }
      else if(strstr(clean_line, v_4) != NULL)
      {
        deck[card_num].value = V_4;
      }
      else if(strstr(clean_line, v_5) != NULL)
      {
        deck[card_num].value = V_5;
      }
      else if(strstr(clean_line, v_6) != NULL)
      {
        deck[card_num].value = V_6;
      }
      else if(strstr(clean_line, v_7) != NULL)
      {
        deck[card_num].value = V_7;
      }
      else if(strstr(clean_line, v_8) != NULL)
      {
        deck[card_num].value = V_8;
      }
      else if(strstr(clean_line, v_9) != NULL)
      {
        deck[card_num].value = V_9;
      }
      else if(strstr(clean_line, v_10) != NULL)
      {
        deck[card_num].value = V_10;
      }
      else if(strstr(clean_line, v_J) != NULL)
      {
        deck[card_num].value = V_J;
      }
      else if(strstr(clean_line, v_Q) != NULL)
      {
        deck[card_num].value = V_Q;
      }
      else if(strstr(clean_line, v_K) != NULL)
      {
        deck[card_num].value = V_K;
      }
      else
      {
        printf("[ERR] Invalid file!\n");
        free(clean_line);
        fclose(input);
        return 3;
      }
      if (card_num == 0) {
        deck[card_num].prev = NULL;
      }
      else
      {
        deck[card_num].prev = &deck[card_num-1];
      }
      card_num++;
    }
    card_num--;  // back to the last card
    deck[card_num].next = NULL;  // last card has no subsequent card
    card_num--;  // back to forlast card
    while (card_num > -1) {
      deck[card_num].next = &deck[card_num+1];  // set next for rest of cards
      card_num--;
    }
    fclose(input);
    return 0;
  }
  else
  {
    printf("[ERR] Invalid file!\n");
    return 3;
  }
}

void cardToStr(int color, int value, char* label)
{
  label[0] = card_color_str[color];
  label[1] = card_value_str[value][0];
  label[2] = card_value_str[value][1];
  label[3] = '\0';
}

// find card in stack and print its 3 char representation
void stackCardToStr(Card* stack, int card_i, char* label, int is_stack0)
{
  if (stack == NULL)
  {
    return;  // stack is empty
  }
  // Find the card in stack at index card_i
  Card* c = stack;  // start with first card (stack always points to first card)
  int i = 0;  // current card counter
  while (c != NULL)  // check if the card exists
  {
    if (card_i == i)  // we reached the target card
    {
      if (is_stack0)
      {
        if ((*c).next != NULL)
        {
          strncpy(label, "X  ", 3);
        }
        else
        {
          cardToStr((*c).color, (*c).value, label);
        }
      }
      else
      {
        cardToStr((*c).color, (*c).value, label);
      }
    }
    i++;
    c = (*c).next;  // point to next card
  }
}

void printField(Card* stack0, Card* stack1, Card* stack2, Card* stack3, Card* stack4, Card* stack5, Card* stack6)
{
  printf("0   | 1   | 2   | 3   | 4   | DEP | DEP\n");
  printf("---------------------------------------\n");
  for (int i = 0; i < 16; i++)
  {
    char label0[4] = "   \0";
    char label1[4] = "   \0";
    char label2[4] = "   \0";
    char label3[4] = "   \0";
    char label4[4] = "   \0";
    char label5[4] = "   \0";
    char label6[4] = "   \0";
    stackCardToStr(stack0, i, &label0, 1);
    stackCardToStr(stack1, i, &label1, 0);
    stackCardToStr(stack2, i, &label2, 0);
    stackCardToStr(stack3, i, &label3, 0);
    stackCardToStr(stack4, i, &label4, 0);
    stackCardToStr(stack5, i, &label5, 0);
    stackCardToStr(stack6, i, &label6, 0);

    printf("%s | %s | %s | %s | %s | %s | %s\n", label0, label1, label2, label3, label4, label5, label6);
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("[ERR] Usage: ./ass3 [file-name]\n");
  }

  char *filename = argv[1];

  Card* deck = (Card*) malloc(27 * sizeof(Card));
  Card *stack0 = NULL;
  Card *stack1 = NULL;
  Card *stack2 = NULL;
  Card *stack3 = NULL;
  Card *stack4 = NULL;
  Card *stack5 = NULL;
  Card *stack6 = NULL;

  int r = readFile(filename, deck);
  if (r != 0)
  {
    return r;
  }
  stack0 = deck;

  // for (int i = 0; i < 26; i++)
  // {
  //   char label[4];
  //   cardToStr(stack0[i].color, stack0[i].value, &label);
  //   printf("%s\n", label);
  // }



  printField(stack0, stack1, stack2, stack3, stack4, stack5, stack6);
  free(deck);
  return 0;
}
