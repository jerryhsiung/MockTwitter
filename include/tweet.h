#ifndef TWEET_H
#define TWEET_H
#include <iostream>
#include <string>
#include "set.h"
#include "datetime.h"

class User;

/**
 * Models a tweet and provide comparison and output operators
 */
class Tweet
{
 public:
  Tweet();

  Tweet(User* user, DateTime& time, std::string& text);

  /**
   * Gets the timestamp of this tweet
   *
   * @return timestamp of the tweet
   */
  DateTime const & time() const;

  /**
   * Gets the actual text of this tweet
   *
   * @return text of the tweet
   */
  std::string const & text() const;

  User * & user(); 

  void addHashTags(std::string h);
  
  /**
   * Returns all the strings in the tweet starting with a '#' (removing the # from the word)
   * 
   * @return unique words starting with a '#' symbol
   */
  std::set<std::string> getHashTags();

  /**
   * Return true if this Tweet's timestamp is less-than other's
   *
   * @return result of less-than comparison of tweet's timestamp
   */
  bool operator<(const Tweet& other) {
    return _time < other._time;
  }

  /**
   * Return true if this Tweet's timestamp is greater-than other's
   *
   * @return result of greater-than comparison of tweet's timestamp
   */
  bool operator>(const Tweet& other) {
    return _time > other._time;
  }

  /**
   * Outputs the tweet to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS username tweet_text
   *
   * @return the ostream passed in as an argument
   */
  friend std::ostream& operator<<(std::ostream& os, const Tweet& t);

 private:
  DateTime _time;
  std::string _text;
  User* _userObject;
  std::set<std::string> _hashtags;

};
struct TweetComp
{
  bool operator()(Tweet* t1, Tweet* t2)
  {
    return (*t1 > *t2);
  }
};
#endif