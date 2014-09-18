#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <QApplication>
#include "../include/user.h"
#include "../include/datetime.h"
#include "../include/tweet.h"
#include "mainwin.h"
#include "trendwin.h"

using namespace std;

int main(int argc, char *argv[])
{
set<string> bobHash;
    string following;
    int num_users;
    map<string, User*> allUsers;
    // map<string, Tweet*> allTimeTrends;
    map<string, vector<Tweet*> > allTimeTrends;
    User* userObject;
    User* followingObject;
    User* userTweetingObject;
    Tweet* tweetObject;
    DateTime dateTimeObject;

    ifstream infile(argv[1]);

    if (infile.is_open())
    {
        string users;
        string username;

        if (infile.good())
        {
            // finds number of users
            getline(infile, users);
            stringstream ss(users);
            ss >> num_users;

            // for loop through num_users to get all users 
            for (int i = 0; i < num_users; i++)
            {
                string line;
                getline(infile, line);
                stringstream ss1(line);
                ss1 >> username;

                //if (!allUsers->contains(username))
                //if (!allUsers->find(username))
                //check if userObject has already been created before 
                map<string, User*>::iterator it;
                it = allUsers.find(username); // SLIDE 15 OF L13_STL
                if (it != allUsers.end())                
                {
                    // userObject = allUsers->find(username); // get User* object from allUsers map
                  userObject = it->second; //get User* object that's already in the allUsers map
                } else
                { 
                    userObject = new User(username); //new userObject created for new username
                    allUsers.insert(pair<string,User*>(username, userObject)); //allUsers map inserts userObject to the username key 
                }

                //gets the following from file
                string dummy; 
                dummy = line.substr(0, line.find_first_of(' '));
                line = line.substr(line.find_first_of(' ') +1);
                stringstream ss2(line);

                while (ss2 >> following)
                {
                    // check if followingObject has already been created before
                    map<string, User*>::iterator it1;
                    it1 = allUsers.find(following);
                    if (it1 != allUsers.end()) 
                    { 
                      followingObject = it1->second;
                      //   followingObject = new User(following);
                        // allUsers->insert(following, followingObject);
                    } else 
                    {
                      followingObject = new User(following);
                      allUsers.insert(pair<string,User*>(following, followingObject));
                        // followingObject = allUsers->get(following);
                    }

                    userObject->addFollowing(followingObject); //adds following to main user objects
                   //  cout << "test: " << userObject->following().size() << endl;
                   // cout << "user added following: " << userObject->name() << endl;
                   // cout << "following being added: " << followingObject->name() << endl;
                    
                    followingObject->addFollower(userObject); //adds main users to following object
                }  
            }
            // map<string, User*>::iterator it3;
            // cout << allUsers->size() << endl;
            // cout << allUsers->find("Mark")->first << endl;
       
          // User* jillUserObject = allUsers->find("Mark")->second;
          // cout << "user: " << jillUserObject->name() << endl;
          // set<User*> jillFollowing = jillUserObject->following();
          // cout << "following size: " << jillFollowing.size() << endl;
          // cout << "followers size: " << jillUserObject->followers().size() << endl;

            // User* cur = *(jillFollowing.first());
            // while (cur != NULL)
            // {
            //  cout << cur->name() << endl;
            //  cur = *(jillFollowing.next());
            // }

          int hour, min, sec, year, month, day;
          char symbols;
          string text;
          string userTweeting;
          string tweet;
          
          while(getline(infile, text))
          {
            stringstream ss3(text);
            ss3 >> year >> symbols >> month >> symbols >> day >> hour >> symbols >> min >> symbols >> sec; //symbol stores unwanted symbols for date/time
            //cout << year << " " << month << " " << day << " " << hour << " " << min << " " << sec << endl;
            dateTimeObject = DateTime(hour, min, sec, year, month, day);

             string dummy1, dummy2; 
            // dummy1 = text.substr(0, text.find_first_of(' ')); //skip over date
            // userTweeting = text.substr(text.find(' ')+10); //skip over time

            // get user of tweet
            stringstream ss4(text);
            ss4 >> dummy1 >> dummy2 >> userTweeting;
            ss4.ignore(256,' '); //ignore whitespace after user of tweets and before tweets
            getline(ss4, tweet);

            map<string, User*>::iterator it2;
            it2 = allUsers.find(userTweeting);
            if (it2 != allUsers.end())
            {
              userTweetingObject = it2->second;
            }
            else
            {
              userTweetingObject = new User(userTweeting);
              allUsers.insert(pair<string,User*>(userTweeting, userTweetingObject));
            }

            tweetObject = new Tweet(userTweetingObject, dateTimeObject, tweet);
            userTweetingObject->addTweet(tweetObject);

            ///////////////////////////////////////@ mentions //////////////////////////////////////
            if (tweet[0] == '@')
            {
              tweet.erase(0,1);
              int pos = tweet.find(' ');
              string firstMention = tweet.substr(0,pos);
              //add to feed? displaying first user?? 
              //cout << firstMention << endl;
            }

            stringstream ss5(tweet);
            string userMention;
            while (ss5 >> userMention)
            {
              if (userMention[0] == '@')
              {
                userMention.erase(0,1);
                //cout << userMention << endl;
              }
            }
          
            ///////////////////////////////////////@ mentions ////////////////////////////////////// 

            /////////////////////////////////////// hashtags ////////////////////////////////////// 
            stringstream ss6(tweet);
            string hashtag;
            while (ss6 >> hashtag)
            {
              if (hashtag[0] == '#')
              {
                hashtag.erase(0,1);
        // map<string, User*>::iterator it2;
        // it2 = allUsers.find(username);
        // if(it2 != allUsers.end())
        // {
        //     userObject = it2->second;
        // }
                vector<Tweet*>curTweets;
                if (allTimeTrends.find(hashtag) != allTimeTrends.end())
                {
                 
                vector<Tweet *> curTweets = allTimeTrends.at(hashtag);
              }
                curTweets.push_back(tweetObject);
                allTimeTrends.insert(pair<string,vector<Tweet*> >(hashtag, curTweets));

                // allTimeTrends.insert(pair<string,Tweet*>(hashtag, tweetObject));
              }
            }
            tweetObject->addHashTags(hashtag);
            /////////////////////////////////////// hashtags ////////////////////////////////////// 
          }
          // Tweet* jillTweetObject = allTimeTrends.find("tbt")->second;
          // cout << "time: " << jillTweetObject->time() << endl;
          // string hash = allTimeTrends.find("tbt")->first;
          // cout << "hashtag: " << hash << endl;
          // set<string> jillHash = jillTweetObject->getHashTags();
          // cout << "size: " << jillHash.size() << endl;
          // for (set<string>::iterator it5 = jillHash.begin(); it5 != jillHash.end(); ++ it5)
          // {
          //   cout << *it5 << endl;
          // }
           // cout << "size of allTimeTrends: " << allTimeTrends.size() << endl;


          //Tweet* jillTweetObject = allUsers.find("Tommy")->second;

          //TESTING TWEETS
          // User* jillUserObject = allUsers.find("Sam")->second;
          // cout << "User: " << jillUserObject->name() << endl;
          // cout << "Begin debugging getFeed" << endl;
          // vector<Tweet*> jillTweets = jillUserObject->getFeed();
          // //cout << "size: " << jillTweets.size() << endl;
          // set <string> jillHash;
          // for (unsigned int i = 0; i < jillTweets.size(); i++)
          // {
          //   jillHash = jillTweets[i]->getHashTags();
          //   // cout << jillTweets[i]->time() << " "
          //   // << jillTweets[i]->user()->name() << " "
          //   // << jillTweets[i]->text() << endl;
          //   //cout << jillTweets[i]->getHashTags() << endl;
          // }
          // cout << "size: " << jillHash.size() << endl;
          // for (set<string>::iterator it5 = jillHash.begin(); it5 != jillHash.end(); ++it5)
          // {
          //   cout << "hashtag; " << *it5 << endl;
          // }
        }
    }

//infile.close();


//debug

//cout << "main: " << allTimeTrends.size() << endl;

QApplication app (argc, argv);

MainWin form(allUsers, allTimeTrends);
TrendWin newForm(allTimeTrends);
form.setWindowTitle("Twitter");
//form.getMap(allUsers);
//form.dispUsers();

form.show();

return app.exec();

return 0;
}