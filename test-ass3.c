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
  int card_num = 0;
  int MAX_LINE_LEN = 1000;
  FILE *input = fopen(filename, "r");
  if (input)
  {
    char temp[MAX_LINE_LEN];
    while (fgets(temp, MAX_LINE_LEN, input))
    {
      //printf("---- %s", temp);
      char *token;
      token = strtok(temp, " \n");
      int token_num = 0;
      if (token == NULL)
      {
        continue;
      }
      while ( token != NULL )
      {
        if (token_num == 0)
        {
          //printf("T0 -> %s\n", token);
          if(strstr(token, "RED") != NULL && strlen(token) == strlen("RED"))
          {
            deck[card_num].color = RED;
          }
          else if(strstr(token, "BLACK") != NULL && strlen(token) == strlen("BLACK"))
          {
            deck[card_num].color = BLACK;
          }
          else
          {
            printf("[ERR] Invalid file!\n");
            fclose(input);
            return 3;
          }
        }
        if (token_num == 1)
        {
          //printf("T1 -> %s (%d)\n", token, strlen(token));
          if(strstr(token, "A") != NULL && strlen(token) == strlen("A"))
          {
            deck[card_num].value = V_A;
          }
          else if(strstr(token, "2") != NULL && strlen(token) == strlen("2"))
          {
            deck[card_num].value = V_2;
          }
          else if(strstr(token, "3") != NULL && strlen(token) == strlen("3"))
          {
            deck[card_num].value = V_3;
          }
          else if(strstr(token, "4") != NULL && strlen(token) == strlen("4"))
          {
            deck[card_num].value = V_4;
          }
          else if(strstr(token, "5") != NULL && strlen(token) == strlen("5"))
          {
            deck[card_num].value = V_5;
          }
          else if(strstr(token, "6") != NULL && strlen(token) == strlen("6"))
          {
            deck[card_num].value = V_6;
          }
          else if(strstr(token, "7") != NULL && strlen(token) == strlen("7"))
          {
            deck[card_num].value = V_7;
          }
          else if(strstr(token, "8") != NULL && strlen(token) == strlen("8"))
          {
            deck[card_num].value = V_8;
          }
          else if(strstr(token, "9") != NULL && strlen(token) == strlen("9"))
          {
            deck[card_num].value = V_9;
          }
          else if(strstr(token, "10") != NULL && strlen(token) == strlen("10"))
          {
            deck[card_num].value = V_10;
          }
          else if(strstr(token, "J") != NULL && strlen(token) == strlen("J"))
          {
            deck[card_num].value = V_J;
          }
          else if(strstr(token, "Q") != NULL && strlen(token) == strlen("Q"))
          {
            deck[card_num].value = V_Q;
          }
          else if(strstr(token, "K") != NULL && strlen(token) == strlen("K"))
          {
            deck[card_num].value = V_K;
          }
          else
          {
            printf("[ERR] Invalid file!\n");
            fclose(input);
            return 3;
          }
        }
        if (token_num > 1)
        {
            printf("[ERR] Invalid file!\n");
            fclose(input);
            return 3;
        }
        token = strtok(NULL," \n");
        token_num++;
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
void printField(Card* stacks[])
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
    stackCardToStr(stacks[0], line_counter, &label0, 1);
    stackCardToStr(stacks[1], line_counter, &label1, 0);
    stackCardToStr(stacks[2], line_counter, &label2, 0);
    stackCardToStr(stacks[3], line_counter, &label3, 0);
    stackCardToStr(stacks[4], line_counter, &label4, 0);
    stackCardToStr(stacks[5], line_counter, &label5, 0);
    stackCardToStr(stacks[6], line_counter, &label6, 0);

    printf("%s | %s | %s | %s | %s | %s | %s\n", label0, label1, label2,
           label3, label4, label5, label6);
  }
}

void dealCards(Card* deck, Card* stacks[])
{
  char label[4] = "   \0";
  // Go to last card in deck
  Card* card = deck;
  while ((*card).next != NULL) {
    card = (*card).next;
  }

  Card* next_card_to_deal = NULL;
  int start_stack_idx = 1;
  for (int start_stack_idx = 1; start_stack_idx <=4; start_stack_idx++)
  {
    for (int stack_idx = start_stack_idx; stack_idx <=4; stack_idx++)
    {
      next_card_to_deal = (*card).prev;
      if (stacks[stack_idx] == NULL)
      {
        stacks[stack_idx] = card;
        card->next = NULL;
        card->prev = NULL;
      }
      else
      {
        // got to last card of stack
        Card* last_stack_card = stacks[stack_idx];
        while ((*last_stack_card).next != NULL) {
          last_stack_card = (*last_stack_card).next;
        }
        // attach card to the end of stack
        last_stack_card->next = card;
        card->prev = last_stack_card;
      }
      card = next_card_to_deal;
      card->next = NULL;
    }
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
  Card* stacks[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};


  int card_reader = readFile(filename, deck);  // read cards from config file
  if (card_reader != 0)
  {
    return card_reader;
  }
  stacks[0] = deck;

  // Deal cards to stacks
  dealCards(deck, stacks);
  printField(stacks);

  while (1)
  {
    printf("esp> ");
    char user_input[256];
    gets(user_input);  // TODO: implement safe user_input with getc

    char tmp_input_for_counting[256];
    strcpy(tmp_input_for_counting, user_input);

    char *token;
    token = strtok(tmp_input_for_counting, " \n");
    int token_num = 0;
    if (token == NULL)
    {
      continue;
    }
    while (token != NULL)
    {
      token = strtok(NULL," \n");
      token_num++;
    }

    if (token_num == 1)  // exit or help command
    {
      token = strtok(user_input, " \n");
      if (strcasecmp(token, "exit") == 0)
      {
        free(deck);
        return 0;
      }
      else if (strcasecmp(token, "help") == 0)
      {
        printf("possible command:\n");
        printf(" - move <color> <value> to <stacknumber>\n");
        printf(" - help\n");
        printf(" - exit\n");
      }
      else
      {
        printf("[ERR] Invalid command!\n");
      }
    }
    else if (token_num == 5)  // move command
    {
      char tmp_input_for_tokenization[256];
      strcpy(tmp_input_for_tokenization, user_input);

      char *move_in = strtok(tmp_input_for_tokenization, " \n");
      char *color_in = strtok(NULL," \n");
      char *value_in = strtok(NULL," \n");
      char *to_in = strtok(NULL," \n");
      char *stack_in = strtok(NULL," \n");

      // validate move command
      if (strcasecmp(move_in, "move") != 0 || (strcasecmp(color_in, "black") != 0 && strcasecmp(color_in, "red") != 0)
          || (strcasecmp(value_in, "A") != 0 && strcasecmp(value_in, "2") != 0 && strcasecmp(value_in, "3") != 0 &&
              strcasecmp(value_in, "4") != 0 && strcasecmp(value_in, "5") != 0 && strcasecmp(value_in, "6") != 0 &&
              strcasecmp(value_in, "7") != 0 && strcasecmp(value_in, "8") != 0 && strcasecmp(value_in, "9") != 0 &&
              strcasecmp(value_in, "10") != 0 && strcasecmp(value_in, "J") != 0 && strcasecmp(value_in, "Q") != 0 &&
              strcasecmp(value_in, "K") != 0)
          || strcasecmp(to_in, "to") != 0
          || (strcasecmp(stack_in, "0") != 0 && strcasecmp(stack_in, "1") != 0 && strcasecmp(stack_in, "2") != 0 &&
              strcasecmp(stack_in, "3") != 0 && strcasecmp(stack_in, "4") != 0 && strcasecmp(stack_in, "5") != 0 &&
              strcasecmp(stack_in, "6") != 0))
      {
        printf("[ERR] Invalid command!\n");
      }
      else
      {
        // TODO: the hard part: check if the move is valid according to game rules (colors, value order, sorting)
        printf("Not implemented yet...\n");
        printField(stacks);
      }
    }
    else
    {
      printf("[ERR] Invalid command!\n");
    }
  }
}
