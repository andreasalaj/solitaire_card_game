//-----------------------------------------------------------------------------
// ass3.c
//
// ESP Assignment 3 WS18
// Simplified solitaire card game
//
// Group: Group 5, study assistant Michael Hancianu
//
// Authors: Andrea Salaj 01624588
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

enum card_color stringToColor(char* string)
{
  if (strcasecmp(string, "red") == 0)
  {
    return RED;
  }
  else if (strcasecmp(string, "black") == 0)
  {
    return BLACK;
  }
}

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

enum card_value stringToValue(char* string)
{
  if (strcasecmp(string, "A") == 0)
  {
    return V_A;
  }
  else if (strcasecmp(string, "2") == 0)
  {
    return V_2;
  }
  else if (strcasecmp(string, "3") == 0)
  {
    return V_3;
  }
  else if (strcasecmp(string, "4") == 0)
  {
    return V_4;
  }
  else if (strcasecmp(string, "5") == 0)
  {
    return V_5;
  }
  else if (strcasecmp(string, "6") == 0)
  {
    return V_6;
  }
  else if (strcasecmp(string, "7") == 0)
  {
    return V_7;
  }
  else if (strcasecmp(string, "8") == 0)
  {
    return V_8;
  }
  else if (strcasecmp(string, "9") == 0)
  {
    return V_9;
  }
  else if (strcasecmp(string, "10") == 0)
  {
    return V_10;
  }
  else if (strcasecmp(string, "J") == 0)
  {
    return V_J;
  }
  else if (strcasecmp(string, "Q") == 0)
  {
    return V_Q;
  }
  else if (strcasecmp(string, "K") == 0)
  {
    return V_K;
  }
}

typedef struct
{
  enum card_color color;
  enum card_value value;
  struct Card *next; // pointer to next card
  struct Card *prev; // pointer to previous card
} Card;

//-----------------------------------------------------------------------------
///
/// readFile reads configuration file, checks if any error is detected
///
/// @param card_num number of a card
/// @param MAX_LINE_LEN maximum line length
/// @param input configfile
/// @param line one line in a configfile
/// @param token one word from a line
/// @param token_num number of words in a line
///
///
/// @return three if invalid file is detected
//
int readFile(char *filename, Card* deck)
{
  int card_num = 0;
  int MAX_LINE_LEN = 1000;
  FILE *input = fopen(filename, "r");
  if (input)
  {
    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, input))
    {
      char *token;
      token = strtok(line, " \n");
      int token_num = 0;
      if (token == NULL)
      {
        continue;
      }
      while ( token != NULL )
      {
        if (token_num == 0)
        {
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
/// cardToStr saves card characteristics into label
///
/// @param color card color
/// @param value card value
/// @param label content of a field in certain stack
///
///
/// @return void
//
void cardToStr(int color, int value, char* label)
{
  label[0] = card_color_str[color];
  label[1] = card_value_str[value][0];
  label[2] = card_value_str[value][1];
  label[3] = '\0';
}

void printCard(Card* card)
{
    if (card != NULL)
    {
        char label[4] = "   \0";
        cardToStr(card->color, card->value, label);
        printf("%s\n", label);
    }
    else
    {
        printf("NULLCARD\n");
    }
}
//-----------------------------------------------------------------------------
///
/// stackCardToStr finds card in stack and prints its three character
/// representation.
///
/// @param stack relative stack to file
/// @param card_index index of a card
/// @param label content of a field in certain stack
/// @param is_stack0 checks if card is in stack0
///
///
/// @return void
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
/// printField prints game field after reading the configfile
///
/// @param line_counter couts lines of a game field
/// @param label content of a field in certain stack
///
///
/// @return void
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

//-----------------------------------------------------------------------------
///
/// dealCards
///
/// @param deck Pointer to the beginning of array of all cards in the game
/// @param stacks Array of pointers to the first card of each stack
///
///
/// @return void
//
void dealCards(Card* deck, Card* stacks[])
{
  // Go to last card in deck since we start dealing from the top of deck
  Card* card = deck;
  while ((*card).next != NULL)
  {
    card = (*card).next;
  }

  Card* next_card_to_deal = NULL;
  int start_stack_idx = 1;
  for (int start_stack_idx = 1; start_stack_idx <=4; start_stack_idx++)
  {
    for (int stack_idx = start_stack_idx; stack_idx <=4; stack_idx++)
    {
      next_card_to_deal = (*card).prev;  // remember next card from the top of deck
      // if the stack is empty, assign it the first card
      if (stacks[stack_idx] == NULL)
      {
        stacks[stack_idx] = card;
        card->next = NULL;
        card->prev = NULL;
      }
      else // if stack is not empty, we put the new card on top of last card
      {
        // got to last card of stack
        Card* last_stack_card = stacks[stack_idx];
        while ((*last_stack_card).next != NULL)
        {
          last_stack_card = (*last_stack_card).next;
        }
        // attach new card to the top of stack
        last_stack_card->next = card;
        card->prev = last_stack_card;
       }
      // take the next card we prepared from the top of deck
      card = next_card_to_deal;
      card->next = NULL; // now it is on top since we removed one card
    }
  }
}

//-----------------------------------------------------------------------------
///
/// findCard
///
/// @param
/// @param
///
///
/// @return void
//
void findCard(enum card_color c, enum card_value v, Card** found_card,
              Card* stacks[])
{
  for (int stack_num = 0; stack_num < 7; stack_num++)
  {
    *found_card = stacks[stack_num];
    while (*found_card != NULL)
    {
      if ((*found_card)->color == c && (*found_card)->value == v)
      {
        return;
      }
      *found_card = (*(*found_card)).next;
    };
  }
}

//-----------------------------------------------------------------------------
///
/// findTopCard find top card of the stack if stack is not empty
///
/// @param
/// @param
///
///
/// @return void
//
void findTopCard(Card** found_card, Card* stack)
{

  if (stack == NULL)
  {
    return;
  }
  *found_card = stack;
  while ((*(*found_card)).next != NULL)
  {
    *found_card = (*(*found_card)).next;
  };
}

//-----------------------------------------------------------------------------
///
/// findStack
///
/// @param target_card
/// @param stacks
///
///
/// @return
//
int findStack(Card* target_card, Card* stacks[])
{
  for (int stack_num = 0; stack_num < 7; stack_num++)
  {
    Card* card = stacks[stack_num];
    while (card != NULL)
    {
      if (card->color == target_card->color &&
          card->value == target_card->value)
      {
        return stack_num;
      }
      card = (*card).next;
    };
  }
}

//-----------------------------------------------------------------------------
///
/// The main program
///
/// @param argc Counter of arguments
/// @param argv Array
///
///
/// @return zero if everything is okay
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
    char character;
    int character_counter = 0;

    while((character = getchar()) != '\n')
    {
      user_input[character_counter++] = character;
    }
    user_input[character_counter] = '\0';

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
      if (strcasecmp(move_in, "move") != 0 ||
         (strcasecmp(color_in, "black") != 0
          && strcasecmp(color_in, "red") != 0) ||
         (strcasecmp(value_in, "A") != 0 && strcasecmp(value_in, "2") != 0
          && strcasecmp(value_in, "3") != 0 && strcasecmp(value_in, "4") != 0
          && strcasecmp(value_in, "5") != 0 && strcasecmp(value_in, "6") != 0
          && strcasecmp(value_in, "7") != 0 && strcasecmp(value_in, "8") != 0
          && strcasecmp(value_in, "9") != 0 && strcasecmp(value_in, "10") != 0
          && strcasecmp(value_in, "J") != 0 && strcasecmp(value_in, "Q") != 0
          &&strcasecmp(value_in, "K") != 0) || strcasecmp(to_in, "to") != 0 ||
         (strcasecmp(stack_in, "0") != 0 && strcasecmp(stack_in, "1") != 0
          && strcasecmp(stack_in, "2") != 0 && strcasecmp(stack_in, "3") != 0
          && strcasecmp(stack_in, "4") != 0 && strcasecmp(stack_in, "5") != 0
          && strcasecmp(stack_in, "6") != 0))
      {
        printf("[INFO] Invalid move command!\n");
      }
      else
      {
        // convert input strings to color and value
        enum card_color move_color = stringToColor(color_in);
        enum card_value move_value = stringToValue(value_in);
        // find the card by color and value
        Card* move_card = NULL;
        findCard(move_color, move_value, &move_card, stacks);
        if (move_card == NULL)
        {
          printf("[INFO] Invalid command!\n");
          continue;
        }
        // convert input string to stack index
        int target_stack_i = strtol(stack_in, (char **)NULL, 10);

        if (target_stack_i == 0)
        {
          printf("[INFO] Invalid move command!\n");
          continue;
        }

        Card* top_stack_card = NULL;
        findTopCard(&top_stack_card, stacks[target_stack_i]);
        // if target_stack_i 1 2 3 4, razlicita boja, od najvece do najmanje

        if (target_stack_i == 1 || target_stack_i == 2 || target_stack_i == 3
            || target_stack_i == 4)
        {
          if (move_card->color == top_stack_card->color)
          {
            printf("[INFO] Invalid move command!\n");
            continue;
          }
          else if(top_stack_card->value != move_card->value + 1)
          {
            printf("[INFO] Invalid move command!\n");
            continue;
          }
        }
        else
        {
          if ((top_stack_card == NULL && move_card->value != 0) ||
              (top_stack_card != NULL && move_card->color !=
               top_stack_card->color) ||
              (top_stack_card != NULL && top_stack_card->value !=
               move_card->value - 1))
          {
            printf("[INFO] Invalid move command!\n");
            continue;
          }
        }

        // if card to move is the only one on stack, set the stack to be empty after move
        if (move_card->prev == NULL)
        {
          int old_stack_idx = findStack(move_card, stacks);
          stacks[old_stack_idx] = NULL;

        }
        else  // otherwise make the previous card the top one
        {
          Card* prev_card_of_moved_card = move_card->prev;
          prev_card_of_moved_card->next = NULL;
        }


        // if the target stack is not empty put the card on top
        if (stacks[target_stack_i] != NULL)
        {
          // find the top card of the stack


          // put the card on top of that one
          top_stack_card->next = move_card;
          move_card->prev = top_stack_card;
        }
        else  // otherwise put it as a first card on stack
        {
          stacks[target_stack_i] = move_card;
          move_card->prev = NULL;
        }

        // TODO: if valid top card check if it's possible to move to target stack and move
        // TODO: if valid substack check the same and move
        // TODO: separate cases if target stacks are 5 or 6 since different sorting applies there
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
