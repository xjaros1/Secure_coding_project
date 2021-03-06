#ifndef JPARSER_H
#define JPARSER_H

#include <istream>
#include "jvalue.h"

class JParser;


std::istream& operator>>(std::istream& in, JParser& where);

class JParser
{
   friend std::istream& operator>> (std::istream&, JParser&);
   enum Statuses {
       NEW_DOCUMENT,
       START_OBJECT,
       END_OBJECT,
       START_ARRAY,
       END_ARRAY,
       NEXT_ITEM,
       READING_STRING,
       END_STRING,
       PAIR_DELIM,
       READING_NUMBER,
       NUMBER_READ,
       ROOT_ELEMENT_FOUND,
       ESCAPED,
   };

   void addChar(int c);
   void newDocState(int c);
   void endObjectState(int c);
   void nextItemState(int c);
   void startArrayState(int c);
   void endArrayState(int c);
   void readingStringState(int c);
   void endStringState(int c);
   void pairDelimState(int c);
   void readindNumberState(int c);
   void numberReadState(int c);
   void escapedState(int c);

   void createObject(char c, char expected, DataTypes type, Statuses status);

   void destroyStack();
public:
    JParser();

    ~JParser()
    { }

    JValue* getParsed();

    bool isParsed() {
        return parsed != 0;
    }

private:

   std::vector<JValue*> stack;
   JValue *parsed;
   std::string currentVal;
   std::pair<std::string, JValue*> currPair;
   Statuses status;

};

#endif // JPARSER_H
