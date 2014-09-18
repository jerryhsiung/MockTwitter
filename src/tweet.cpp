#include "../include/tweet.h"

using namespace std;

Tweet::Tweet()
{}

Tweet::Tweet(User* user, DateTime& time, std::string& text)
{
  _userObject = user;
  _time = time;
  _text = text;
}

DateTime const & Tweet::time() const
{
  /**
   * Gets the timestamp of this tweet
   *
   * @return timestamp of the tweet
   */
  return _time;
}

string const & Tweet::text() const
{
  /**
   * Gets the actual text of this tweet
   *
   * @return text of the tweet
   */
  return _text;
}

User * & Tweet::user() {
  return _userObject;
}

void Tweet::addHashTags(string h)
{
  _hashtags.insert(h);
}

/**
 * Returns all the strings in the tweet starting with a '#' (removing the # from the word)
 * 
 * @return unique words starting with a '#' symbol
 */
set<string> Tweet::getHashTags()
{
  return _hashtags;
}

ostream& operator<<(ostream& os, const Tweet& t)
{
  os << t._time << " " << t._userObject << " " << t._text;
  return os;
  /**
   * Outputs the tweet to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS username tweet_text
   *
   * @return the ostream passed in as an argument
   */
}