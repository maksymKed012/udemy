#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct Sentence
{
  struct WordToken
  {
    bool capitalize;
  };

  private:
  std::string sentence_;
  std::vector<std::string> sentence_words_;
  std::vector<WordToken> word_tokens_;

  std::vector<std::string> split_sentence(const std::string& sentence) {
      std::vector<std::string> split_sentence;
      std::istringstream ss(sentence);
      std::string word;
      while(std::getline(ss, word, ' ')) {
          split_sentence.push_back(word);
      }

      return split_sentence;
  }

  public:

  Sentence(const std::string& text) : sentence_(text)
  {
    // todo

    sentence_words_ = split_sentence(sentence_);

    for(const auto& word : sentence_words_) {
        WordToken word_token;
        word_token.capitalize = false;
        word_tokens_.push_back(word_token);
    }
  }

  WordToken& operator[](size_t index)
  {
    // todo
    if(word_tokens_.size() < index) {
        std::cout << "LOLKEK invalid index return some kekel" << std::endl;
        static WordToken kekel;
        return kekel;
    }

    return word_tokens_[index];
  }

  std::string str() const
  {
    std::stringstream ss;
    for (int i = 0; i < sentence_words_.size(); ++i) {
        auto word = sentence_words_[i];
        if(word_tokens_[i].capitalize) {
            std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        }
        ss << word.c_str();
        if(i < sentence_words_.size() - 1) {
            ss << " ";
        }
    }

    return ss.str();
  }
};


int main () {
    return 0;
}