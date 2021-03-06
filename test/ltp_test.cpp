// Defines the entry point for the console application.
//

#include <stdlib.h>
#include <iostream>

#include "Xml4nlp.h"
#include "Ltp.h"

using namespace std;

int main(int argc, char *argv[]) {
  const char* usage = "Usage: ./ltp_test <config_file> <type> <test_file>";
  if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
    cerr << usage << endl;
    return 0;
  } else if (argc != 4) {
    cerr << usage << endl;
    return 1;
  }

  string sentence;
  // ofstream log_file("test.log");

  LTP ltp(argv[1]);

  if (!ltp.loaded()) {
    std::cerr << "Failed to load LTP" << std::endl;
    return 1;
  }

  string type(argv[2]);
  ifstream in(argv[3]);

  if (!in.is_open()) {
    cerr << "Cann't open file!" << endl;
    exit(1);
  }

  while(std::getline(in, sentence)){
    int len = sentence.size();
    while ( sentence[len-1]=='\n' || sentence[len-1]=='\r' ) {
      -- len;
    }

    if (len == 0) {
      continue;
    }

    sentence = sentence.substr(0, len);
    XML4NLP xml4nlp;
    xml4nlp.CreateDOMFromString(sentence);

    if(type == "ws"){
      ltp.wordseg(xml4nlp);
    } else if(type == "pos"){
      ltp.postag(xml4nlp);
    } else if(type == "ner"){
      ltp.ner(xml4nlp);
    } else if(type == "dp"){
      ltp.parser(xml4nlp);
    } else if(type == "srl"){
      ltp.srl(xml4nlp);
    } else {
      ltp.srl(xml4nlp);
    }

    string result;
    xml4nlp.SaveDOM(result);
    xml4nlp.ClearDOM();
    std::cout << result << std::endl;
  }
  return 0;
}
