//-----------------------------------------------------------------------------
// ass3.c
//
// <Explanation of the program ...>
// <... May have multiple lines.>
//
// Group: Group 5, study assistant Michael Hancianu
//
// Authors: <Name> <Matriculum Number>
// <Name> <Matriculum Number>
//-----------------------------------------------------------------------------
//

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

const char *card_value_str[] = {"A ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ",
                                "8 ", "9 ", "10", "J ", "Q ", "K "};

typedef struct
{
  enum card_color color;
  enum card_value value;
  struct Card *next; // pointer to next card
  struct Card *prev; // pointer to previous card
} Card;

//-----------------------------------------------------------------------------
///
/// ReadFile
///
/// @param
/// @param
///
///
/// @return
//
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

      // TODO: properly validate lines with regex
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

//-----------------------------------------------------------------------------
///
/// CardToStr
///
/// @param
/// @param
///
///
/// @return
//
void cardToStr(int color, int value, char* label)
{
  label[0] = card_color_str[color];
  label[1] = card_value_str[value][0];
  label[2] = card_value_str[value][1];
  label[3] = '\0';
}

//-----------------------------------------------------------------------------
///
/// StackCardToStr finds card in stack and prints its three character
/// representation.
///
/// @param
/// @param
///
///
/// @return
//
void stackCardToStr(Card* stack, int card_index, char* label, int is_stack0)
{
  if (stack == NULL)
  {
    return;  // stack is empty
  }
  // Find the card in stack at index card_index
  Card* card = stack;  // start with first card (stack always points to first card)
  int card_counter = 0;  // current card counter
  while (card != NULL)  // check if the card exists
  {
    if (card_index == card_counter)  // we reached the target card
    {
      if (is_stack0)
      {
        if ((*card).next != NULL)
        {
          strncpy(label, "X  ", 3);
        }
        else
        {
          cardToStr((*card).color, (*card).value, label);
        }
      }
      else
      {
        cardToStr((*card).color, (*card).value, label);
      }
    }
    card_counter++;
    card = (*card).next;  // point to next card
  }
}

//-----------------------------------------------------------------------------
///
/// PrintField
///
/// @param
/// @param
///
///
/// @return
//
void printField(Card* stack0, Card* stack1, Card* stack2, Card* stack3,
                Card* stack4, Card* stack5, Card* stack6)
{
  printf("0   | 1   | 2   | 3   | 4   | DEP | DEP\n");
  printf("---------------------------------------\n");
  for (int line_counter = 0; line_counter < 16; line_counter++)
  {
    char label0[4] = "   \0";
    char label1[4] = "   \0";
    char label2[4] = "   \0";
    char label3[4] = "   \0";
    char label4[4] = "   \0";
    char label5[4] = "   \0";
    char label6[4] = "   \0";
    stackCardToStr(stack0, line_counter, &label0, 1);
    stackCardToStr(stack1, line_counter, &label1, 0);
    stackCardToStr(stack2, line_counter, &label2, 0);
    stackCardToStr(stack3, line_counter, &label3, 0);
    stackCardToStr(stack4, line_counter, &label4, 0);
    stackCardToStr(stack5, line_counter, &label5, 0);
    stackCardToStr(stack6, line_counter, &label6, 0);

    printf("%s | %s | %s | %s | %s | %s | %s\n", label0, label1, label2,
           label3, label4, label5, label6);
  }
}

//-----------------------------------------------------------------------------
///
/// The main program.
///
/// @param
/// @param
///
///
/// @return
//
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

  int card_reader = readFile(filename, deck);  // read cards from config file
  if (card_reader != 0)
  {
    return card_reader;
  }
  stack0 = deck;

  printField(stack0, stack1, stack2, stack3, stack4, stack5, stack6);

  // TODO: Deal cards to stacks

  while (1)
  {
    printf("esp> ");
    char user_input[256];
    gets(user_input);  // TODO: implement safe user_input with getc
    if (strstr(user_input, "exit") != NULL)
    {
      return 0;
    }
    // TODO: implement invalid command error
    // TODO: implement help command
    // TODO: implement move command: only validation of arguments
  }

  free(deck);
  return 0;
}
