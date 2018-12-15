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

typedef struct Card
{
  enum card_color color;
  enum card_value value;
} Card;


int readFile(char *filename, struct Card* stack0)
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
        stack0[card_num].color = RED;
      }
      else if(strstr(clean_line, black) != NULL)
      {
        stack0[card_num].color = BLACK;
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
        stack0[card_num].value = V_A;
      }
      else if(strstr(clean_line, v_2) != NULL)
      {
        stack0[card_num].value = V_2;
      }
      else if(strstr(clean_line, v_3) != NULL)
      {
        stack0[card_num].value = V_3;
      }
      else if(strstr(clean_line, v_4) != NULL)
      {
        stack0[card_num].value = V_4;
      }
      else if(strstr(clean_line, v_5) != NULL)
      {
        stack0[card_num].value = V_5;
      }
      else if(strstr(clean_line, v_6) != NULL)
      {
        stack0[card_num].value = V_6;
      }
      else if(strstr(clean_line, v_7) != NULL)
      {
        stack0[card_num].value = V_7;
      }
      else if(strstr(clean_line, v_8) != NULL)
      {
        stack0[card_num].value = V_8;
      }
      else if(strstr(clean_line, v_9) != NULL)
      {
        stack0[card_num].value = V_9;
      }
      else if(strstr(clean_line, v_10) != NULL)
      {
        stack0[card_num].value = V_10;
      }
      else if(strstr(clean_line, v_J) != NULL)
      {
        stack0[card_num].value = V_J;
      }
      else if(strstr(clean_line, v_Q) != NULL)
      {
        stack0[card_num].value = V_Q;
      }
      else if(strstr(clean_line, v_K) != NULL)
      {
        stack0[card_num].value = V_K;
      }
      else
      {
        printf("[ERR] Invalid file!\n");
        free(clean_line);
        fclose(input);
        return 3;
      }
      card_num++;
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

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("[ERR] Usage: ./ass3 [file-name]\n");
  }

  char *filename = argv[1];

  struct Card* stack0 = (struct Card*) malloc(26 * sizeof(struct Card));
  int r = readFile(filename, stack0);
  if (r != 0)
  {
    return r;
  }

  for (int i = 0; i < 26; i++)
  {
    char label[4];
    cardToStr(stack0[i].color, stack0[i].value, &label);
    printf("%s\n", label);
  }

  return 0;
}
