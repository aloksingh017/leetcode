#include <cctype>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class TextProcessor {
public:
  static vector<string> tokenize(const string &text) {
    vector<string> words;
    string currentWord;

    for (unsigned char ch : text) {
      if (isalnum(ch)) {
        currentWord += static_cast<char>(tolower(ch));
      } else {
        if (!currentWord.empty()) {
          words.push_back(currentWord);
          currentWord.clear();
        }
      }
    }

    if (!currentWord.empty()) {
      words.push_back(currentWord);
    }

    return words;
  }

  static string normalizeWord(const string &word) {
    vector<string> tokens = tokenize(word);

    if (tokens.empty()) {
      return "";
    }

    return tokens[0];
  }
};

class Book {
private:
  string id;
  string title;
  string author;
  unordered_map<string, int> wordFrequency;

  void buildWordFrequency(const string &content) {
    vector<string> words = TextProcessor::tokenize(content);

    for (const string &word : words) {
      wordFrequency[word]++;
    }
  }

public:
  Book(const string &id, const string &title, const string &author,
       const string &content)
      : id(id), title(title), author(author) {
    buildWordFrequency(content);
  }

  string getId() const { return id; }

  string getTitle() const { return title; }

  string getAuthor() const { return author; }

  int getWordCount(const string &word) const {
    string normalizedWord = TextProcessor::normalizeWord(word);

    if (normalizedWord.empty()) {
      return 0;
    }

    auto it = wordFrequency.find(normalizedWord);

    if (it == wordFrequency.end()) {
      return 0;
    }

    return it->second;
  }
};

class BookStore {
private:
  unordered_map<string, Book> books;

public:
  bool addBook(const string &id, const string &title, const string &author,
               const string &content) {
    if (books.find(id) != books.end()) {
      return false;
    }

    Book book(id, title, author, content);
    books.emplace(id, book);

    return true;
  }

  bool hasBook(const string &bookId) const {
    return books.find(bookId) != books.end();
  }

  bool removeBook(const string &bookId) { return books.erase(bookId) > 0; }

  optional<int> getWordCountInBook(const string &bookId,
                                   const string &word) const {
    auto it = books.find(bookId);

    if (it == books.end()) {
      return nullopt;
    }

    return it->second.getWordCount(word);
  }
};

int main() {
  BookStore store;

  store.addBook("B1", "Harry Potter and the Philosopher's Stone",
                "J.K. Rowling",
                "Harry was a wizard. Harry lived with the Dursleys. "
                "Ron and Hermione became Harry's friends.");

  store.addBook("B2", "The Lord of the Rings", "J.R.R. Tolkien",
                "Frodo carried the ring. Sam helped Frodo. "
                "Gandalf guided Frodo and Sam.");

  string bookId = "B1";
  string word = "Harry";

  optional<int> count = store.getWordCountInBook(bookId, word);

  if (count.has_value()) {
    cout << "The word \"" << word << "\" appears " << count.value()
         << " times in book " << bookId << "." << endl;
  } else {
    cout << "Book not found." << endl;
  }

  return 0;
}