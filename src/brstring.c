/*
 * =====================================================================================
 *
 *       Filename:  brstring.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/07/2017 08:32:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "brstring.h"
#include "splitstr.h"
#include <string.h>

//#define DEBUG

int brString_Length_Internal(branch *br, int indent) {
  // note: removed +1's, since null terminators do that job for us
  // note: scratch that
  return (indent + strlen(br->txt) + strlen(br->b1) + strlen(br->b2) + 3);
}

// super secret calculation formula dont tell anyone
int brString_Length(branch *br, int indent) {
  int baseLength = brString_Length_Internal(br,indent);
  if (brHasBranch1(br))
    baseLength = baseLength + brString_Length(br->branch1,indent + 1);
  if (brHasBranch2(br))
    baseLength = baseLength + brString_Length(br->branch2,indent + 1);
  return baseLength;
}

char *without_newline_or_terminator(char *from) {
  int currentLength = strlen(from);
  unsigned int newlines_and_terminators = 0;
  while (*from) {
    if (*from == '\n' || *from == '\0')
      newlines_and_terminators++;
    from++;
  }

  char new_string[currentLength - newlines_and_terminators];
  int current_pos = 0;
  from -= currentLength;
  
  while (*from) {
    if (*from != '\n' || *from != '\0')
    {
      new_string[current_pos] = *from;
      current_pos++;
    }
    from++;
  }
 
  return new_string;
}

void append_to_string(char *to, char *from, int toLength, int fromLength, int position) {
#ifdef DEBUG
  printf("Position is %i\n",position);
  printf("FromLength is %i\n",fromLength);
  printf("ToLength is %i\n",toLength);
  printf("Position + FromLength is %i\n",position + fromLength);
#endif
/*   if (position + fromLength > toLength) {
    fprintf (stderr, "error: insufficient space to append to\n");
    return;
  }

  for (to += position; *from; to++, from++)
    *to = *from;
  *to = *from;
*/
  int somenumber = fromLength,
  lento = toLength,
  end = position + somenumber;

  if (end > lento) {
    fprintf (stderr, "error: insufficient space in append process\n");
    return;
  }

  for (int i = position; i < end; i++)
    to[i] = from[i - position];
}

char *brToString_Internal(branch *br, int indent) {
  // this one's gonna be a doozy, so I'm gonna comment it just in case I forget
  //
  // intended format:
  //
  // txt/b1/b2
  //  b1->txt/b1->b1/b1->b2
  //   b1->b1->txt/b1->b1->b1/b1->b1->b2
  //  b2->txt/b2->b1/b2->b2
  //
  //  and so on
  //
  //  first, we have to initialize a string
  //  the brString_Length function prints out the approximate length of a stringified branch
  int the_string_L = brString_Length(br,indent);
#ifdef DEBUG
  puts("--- Entering brToString_Internal ---");
  printf("the_string_L is %i\n",the_string_L);
#endif
  char the_string[the_string_L];
#ifdef DEBUG
  puts("--- Adding indentation ---");
#endif
  for (int i = 0; i < indent; i++) {
    the_string[i] = ' ';
  }
  the_string[indent] = '\0';

#ifdef DEBUG
  printf("the_string is \"%s\"\n",the_string);
#endif

  // this current_pos variable represents where we need to append the string
  unsigned int current_pos = indent;

  // now we append txt to the string
  // note: since the start of an array is zero, indent will equal the position where we have to start. Why? If we have no indent:
  // [' '] [' '] [' '] <- array
  //  [0]   [1]   [2]  <- positions
  //  since we have 0 indent, we should start at the beginning, and indent already equals 0, so why not use that?
  //  if we have 1 indent, we need to start at space 1, so there's that
  //
  //  an experienced programmer might look at this and see the crutch functions I'm using to access the properties of the branch struct. one might ask "why"?
  //  it's mostly so I don't mix things up, and so it's easier to read
#ifdef DEBUG
  puts("--- Appending br->txt ---");
#endif  
  unsigned int br_txt_L = strlen(brGetText(br));
#ifdef DEBUG
  printf("br_txt is \"%s\"\n",brGetText(br));
  printf("br_txt_L is %i\n",br_txt_L);
#endif
  strcat(the_string,brGetText(br));

#ifdef DEBUG
  printf("the_string is \"%s\"\n",the_string);
#endif
  // now we add the length of the text to current_pos
  // I am doing -1 to filter out the null terminator
  current_pos += br_txt_L;
#ifdef DEBUG
  printf("Current_pos is %i\n",current_pos);
#endif

  // here we add the / character to the string
#ifdef DEBUG
  puts("--- Adding a / ---");
#endif
  strcat(the_string,"/");
  current_pos += 1;
#ifdef DEBUG
  printf("the_string is \"%s\"\n",the_string);
#endif

#ifdef DEBUG
  puts("--- Appending br->b1 ---");
#endif
  // now we add the text for Option 1
  unsigned int br_b1_L = strlen(brGetBranch1Text(br));
#ifdef DEBUG
  printf("br_b1_L is %i\n",br_b1_L);
  printf("br_b1 is \"%s\"\n",brGetBranch1Text(br));
#endif
  strcat(the_string,brGetBranch1Text(br));
  current_pos += br_b1_L;

#ifdef DEBUG
  printf("the_string is \"%s\"\n",the_string);
#endif

  // append the / again
#ifdef DEBUG
  puts("--- Adding a / ---");
#endif
  strcat(the_string,"/");
  current_pos += 1;
#ifdef DEBUG
  printf("the_string is \"%s\"\n",the_string);
#endif

  // now we add the text for Option 2
#ifdef DEBUG
  puts("Adding br->b2");
#endif
  unsigned int br_b2_L = strlen(brGetBranch2Text(br));
#ifdef DEBUG
  printf("br_b2_L is %i\n",br_b2_L);
  printf("br_b2 is \"%s\"\n",brGetBranch2Text(br));
#endif
  strcat(the_string,brGetBranch2Text(br));
  current_pos += br_b2_L;
#ifdef DEBUG
  printf("the_string is \"%s\"\n",the_string);
#endif


  // append a newline, since one of two scenarios might happen:
  // 1. this branch is not the end, if so, it needs to go on
  // 2. this branch is the end, if so, the terminator is easily appended
  strcat(the_string,"\n");
  current_pos += 1;

#ifdef DEBUG
  puts("--- Final Substring ---");
  printf("\"%s\"\n",the_string);
#endif

  // if this branch is a dead end (i.e. no branch1 or branch2) then we are done here
  if (!brHasBranch1(br) && !brHasBranch2(br)) {
#ifdef DEBUG
    puts("Detected dead-end, returning as normal");
#endif
    return strdup(the_string);
  }

  // otherwise, we must append the other branches
  int targetIndent = indent + 1;
#ifdef DEBUG
  puts("--- Appending Branch One ---");
#endif
  if (brHasBranch1(br)) {
    // make the new string for branch1 with one extra indent
    // we append it in the same statement
    unsigned int b1_L = brString_Length(brGetBranch1(br),targetIndent);
    strcat(the_string,brToString_Internal(brGetBranch1(br),targetIndent));
    current_pos += b1_L;
#ifdef DEBUG
    printf("the_string is \"%s\"\n",the_string);
#endif
  }
#ifdef DEBUG
  else {
    puts("Branch 1 not found");
  }
#endif
  
  // now we do branch 2
#ifdef DEBUG
  puts("--- Appending Branch Two ---");
#endif
  if (brHasBranch2(br)) {
    unsigned int b2_L = brString_Length(brGetBranch2(br),targetIndent);
    strcat(the_string,brToString_Internal(brGetBranch2(br),targetIndent));
    current_pos += b2_L; // doing this just in case I need to add anything on
#ifdef DEBUG
    printf("the_string is \"%s\"\n",the_string);
#endif
  }
#ifdef DEBUG
  else {
    puts("Branch 2 not found");
  }
#endif
  
  // unless the format changes, this should be it
  //
  // format changed, we need a newline
  strcat(the_string,"\n");
#ifdef DEBUG
  puts("--- Final String is as follows: ---");
  printf("%s\n",the_string);
  puts("--- Exiting brToString_Internal ---");
#endif
  return strdup(the_string);
}

char *brToString(branch *br) {
  return brToString_Internal(br,0);
}

int getLineIndent(char *str) {
  int indent = 0;
  char current = *(str);
  while (current == ' ') {
    indent++;
    current = *(str + indent);
  }
  return indent;
}

branch *brFromString_Internal(char *str, int indent) {
  int readPos = indent;;
  int pos = 0;
  char current = *(str + readPos);

  char txt[256];
  char b1[256];
  char b2[256];

  while (current != '/') {
    txt[pos] = current;
    pos++;
    readPos++;
    current = *(str + readPos);
  }

  pos = 0;
  readPos++;
  while (current != '/') {
    b1[pos] = current;
    pos++;
    readPos++;
    current = *(str + readPos);
  }

  pos = 0;
  readPos++;
  while (current != '\n' && current != '\0') {
    b2[pos] = current;
    pos++;
    readPos++;
    current = *(str + readPos);
  }

  branch *br = brCreate(b1,b2,txt);
  if (current == '\0')
    return br;

  int targetIndent = indent + 1;
  int newlines = 0;
  for(int i=0 ; *(str+1)!='\0' ; i++)
    if((str+i)=='\n')
      newlines++;
  newlines++;
   
  size_t str_num;
  char **split_lines = str_split(str,'\n',&str_num);
  char *b1_l = 0;
  char *b2_l = 0;

  for (int i = 0; i < str_num; i++) {
    if (getLineIndent(*(split_lines + i)) == targetIndent) {
      if (b1_l) {
        b2_l = *(split_lines + i);
        break;
      } 
      else
        b1_l = *(split_lines + i);
    }
  }

  if (!(b1_l) && !(b2_l))
    return br;

  branch *br1 = brFromString_Internal(b1_l,targetIndent);
  branch *br2 = brFromString_Internal(b2_l,targetIndent);

  brSetBranch1(br,br1);
  brSetBranch2(br,br2);

  return br;
}

branch *brFromString(char *str) {
  return brFromString_Internal(str,0);
}
