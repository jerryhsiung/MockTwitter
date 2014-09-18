#include "../include/user.h"
// #include "../include/tweet.h"

using namespace std;

User::User(string name)
{
  username = name;
}

User::~User()
{}

string User::name()
{
  return username;
}

set<User*> User::followers()
{
    /**
   * Gets all the followers of this user  
   * 
   * @return set of Users who follow this user
   */
   return _followers;
}

set<User*> User::following()
{
  /**
   * Gets all the users whom this user follows  
   * 
   * @return set of Users whom this user follows
   */
   return _following;
}

vector<Tweet*> User::tweets()
{
  /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */
   return _tweets;
}

// gets all the mention tweets this user has posted 
vector<Tweet*> User::mentionTweets()
{
  return _mentionTweets;
}

void User::addFollower(User* u)
{
  /**
   * Adds a follower to this users set of followers
   * 
   * @param u User to add as a follower
   */
   _followers.insert(u);
}

void User::addFollowing(User* u)
{
  /**
   * Adds another user to the set whom this User follows
   * 
   * @param u User that the user will now follow
   */
   _following.insert(u);
}

void User::addTweet(Tweet* t)
{
  /**
   * Adds the given tweet as a post from this user
   * 
   * @param t new Tweet posted by this user
   */
   _tweets.push_back(t);
}

//adds the given mention tweet as a post from this user
void User::addMentionTweet(Tweet* t)
{
  _mentionTweets.push_back(t);
}

bool compare(Tweet * t1, Tweet * t2) {
    return (t1->time() < t2->time());
}

vector<Tweet*> User::getFeed()
{
  vector<Tweet *> allTweets;
  for (unsigned int i = 0; i < _tweets.size(); i++)
  {
    allTweets.push_back(_tweets[i]); //adds all of user's tweets to vector
  }

  //following's tweets
  for (set<User*>::iterator it = _following.begin(); it != _following.end(); ++it)
  {
    vector<Tweet *> userTweets = (*it)->tweets();
    for (unsigned int i = 0; i < userTweets.size(); i++)
    {
      //string tweettext = userTweets[i]->text();
      //tweettext[0] (see if it is @)
      // filter here
        //create a set that has the following()
        // if the username is in the set, then you add to main feed
      // check if the name is equal to 
      // if @name == username CHECK if (*it) is following user
      //  (*it)->following() (->name())  == username
      for (unsigned int x = 0; x < _mentionTweets.size(); x++)
      {
        // 
        // if (_mentionTweets[x] == userTweets[i] ) //check if mentionTweets contains the current Tweet
        // {
        //   set<User*> curFollowing = (*it)->following();
        //   set<User*>::iterator it1;
        //   it1 = curFollowing.find((*it)->name());
        //   if (it1 != curFollowing.end())
        //   {
        //     allTweets.push_back(userTweets[i]);
        //   }
        // }
      }
     allTweets.push_back(userTweets[i]); //adds all of user's tweets to vector
    }
  }
  
  //insertion sort
  for (vector<Tweet*>::iterator it = allTweets.begin(); it != allTweets.end(); ++it){
     
     //DateTime min = (*it)->time();
      // Tweet * min = (*it);
    vector<Tweet*>::iterator min = it;
     for (vector<Tweet*>::iterator it2 = it+1; it2 != allTweets.end(); ++it2){
     //for (unsigned int j = i; j < allTweets.size(); j++) {
      // Tweet * curTime = (*it2);
        if ((*min)->time() < (*it2)->time())
        {
          min = it2;
        }
    }

     // allTweets.insert(it2, 1, min);
     // iterator erase (iterator position)
    Tweet * minVal = (*min);
      allTweets.erase(min);
     allTweets.insert(it, minVal);
     // iterator insert (iterator position, const value_type& val);
  }
  // return this vector
  return allTweets;
}

vector<Tweet*> User::getMentionFeed()
{
  return _mentionTweets;
}