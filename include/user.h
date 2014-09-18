#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <map>
// #include <stdlib.h>
#include <vector>
#include "set.h"
#include "tweet.h"
#include <algorithm>


class User {
 public:
  User(std::string name);

  ~User();

  /**
   * Gets the name of the user 
   * 
   * @return name of the user 
   */
  std::string name();

  /**
   * Gets all the followers of this user  
   * 
   * @return Set of Users who follow this user
   */
  std::set<User*> followers();

  /**
   * Gets all the users whom this user follows  
   * 
   * @return set of Users whom this user follows
   */
  std::set<User*> following();

  /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */
  std::vector<Tweet*> tweets();

  std::vector<Tweet*> mentionTweets();

  /**
   * Adds a follower to this users set of followers
   * 
   * @param u User to add as a follower
   */
  void addFollower(User* u);

  /**
   * Adds another user to the set whom this User follows
   * 
   * @param u User that the user will now follow
   */
  void addFollowing(User* u);

  /**
   * Adds the given tweet as a post from this user
   * 
   * @param t new Tweet posted by this user
   */
  void addTweet(Tweet* t);

  void addMentionTweet(Tweet* t);

  /**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It contains in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *  and those they follow in timestamp order
   */
  std::vector<Tweet*> getFeed();
  
  std::vector<Tweet*> getMentionFeed();

  bool compare(Tweet * t1, Tweet * t2);

 private:
  std::string username; 
  std::set<User*> _followers;
  std::set<User*> _following;
  std::vector<Tweet*> _tweets;
  std::vector<Tweet*> _mentionTweets;
};

#endif //USER_H