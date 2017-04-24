/*
 * =====================================================================================
 *
 *       Filename:  saves.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/05/2017 09:39:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.T. Nunley (JaydomStudios), jtnunley01@gmail.com
 *   Organization:  JaydomStudios
 *
 * =====================================================================================
 */

#include "saves.h"
#include "brstring.h"

#include <stdio.h>

int brSaveToFile(branch *br, char *filename) {
  char *pos;
  if ((pos = strchr(filename,'\n')) != NULL)
    *pos = '\0';
  FILE *output = fopen(filename,"w");
  fprintf(output,brToString(br));
  fclose(output);
  return 0;
}

int getLineIndent(char *line) {
  int indent = 0;
  while (line && line == ' ')
  {
    indent++;
    line++;
  }
  return indent;
}

int countLinesInFile(char *filename) {
  int newlines = 0;
  FILE *input = fopen(filename,"r");

  char buffer[256*4];
  while ((fgets(buffer,256*4,input)) != EOF) {
    if (buffer == '\n')
      continue;
    newlines++;
  }

  fclose(input);
  return newlines;
}

branch *frmString(char str[],int indent) {
  int readPos = indent;
  char current = ' ';

  int currentPos = 0;
  char txtBuffer[256];
  while (current && current != '/')
  {
    current = str[readPos];
    if (current != '/')
      txtBuffer[currentPos] = current;
    readPos++;
    currentPos++;
  }
  txtBuffer[currentPos + 1] = '\0';

  currentPos = 0;
  char b1Buffer[256];
  while (current && current != '/') {
    current = str[readPos];
    if (current != '/')
      b1Buffer[currentPos] = current;
    readPos++;
    currentPos++;
  }
  b1Buffer[currentPos + 1] = '\0';

  currentPos = 0;
  char b2Buffer[256];
  while (current && (current != '\n' || current != '\0')) {
    current = str[readPos];
    if (current != '\n' && current != '\0')
      b2Buffer[currentPos] = current;
    readPos++;
    currentPos++;
  }
  b2Buffer[currentPos + 1] = '\0';

    return brCreate(b1Buffer,b2Buffer,txtBuffer);

   
}

branch **cutArray(branch **array, int bound1, int bound2) {
  int range = bound2 - bound1;
  branch **newArray = malloc(sizeof(branch) * range);
  
  int j = 0;
  for (int i = bound1; i < bound2; i++) {
    j++;
    *(newArray + j) = *(array + i);
  }

  return newArray;
}

int *cutIntArray(int *indent_count, int bound1, int bound2) {
  int range = bound2 - bound1;
  int newArray[range];
  
  int j = 0;
  for (int i = bound1; i < bound2; i++) {
    j++;
    newArray[j] = *(indent_count+i);
  }

  return newArray;
}

branch *constructTree(branch **br_array, int *indent_count, int currentIndent, int count) {
  branch *target = *(br_array);
  int targetIndent = currentIndent + 1;

  if (count <= 1)
    return brDup(target);

  int index_b1 = -1;
  int index_b2 = -1;

  for (int i = 0; i < count; i++) {
    if (*(indent_count+i) == targetIndent) {
      if (index_b1 == -1)
        index_b1 = i;
      else if (index_b2 == -1)
        index_b2 = i;
    }
  }

  if (index_b2 == -1)
    index_b2 = count - 1;

  int range1 = (index_b2 - 1) - index_b1;
  int range2 = (count - 1) - index_b2;
  branch **target1 = cutArray(br_array,index_b1,index_b2 - 1);
  branch **target2 = cutArray(br_array,index_b2,count - 1);
  int *indent1 = cutIntArray(indent_count,index_b1,index_b2 - 1);
  int *indent2 = cutIntArray(indent_count,index_b2,count - 1);
 
  branch *br1 = constructTree(target1,indent1,targetIndent,range1);
  branch *br2 = constructTree(target2,indent2,targetIndent,range2);

  branch *clonedTarget = brDup(target);
  brSetBranch1(clonedTarget,br1);
  brSetBranch2(clonedTarget,br2);

  return clonedTarget;
}

branch *brLoadFromFile(char *filename) {
  char txt[256];
  char b1[256];
  char b2[256];

  int readPos = 0;
  int newlines = countLinesInFile(filename);

  branch *br = 0;
  branch **br_array = malloc(sizeof(branch) * newlines);
  int indent_count[newlines];
  FILE *input = fopen(filename,"r");

  //char fileText[((256 * 4) * newlines * sizeof(char))];

  char buffer[256 * 4];
  while ((fgets(buffer,256 * 4,input)) != EOF) {
    if (buffer == "\n")
      continue;
        
    //int bufferLength = strlen(buffer);
    //for (int i = 0; i < bufferLength; i++)
    //  fileText[i + readPos] = buffer[i];
    
    //readPos += bufferLength;
    //fileText[readPos] = '\n';
    //readPos++;
    
    int indent = getLineIndent(buffer);
    indent_count[readPos] = indent;
    br = frmString(buffer,indent);
    *(br_array + readPos) = brDup(br);
  }
  
  fclose(input);

  br = *(br_array);
  br = constructTree(br_array,indent_count,0,newlines);
  return br;
}
