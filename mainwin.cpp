#include <string>
#include <sstream>
#include "mainwin.h"
#include <QObject>
#include "../include/user.h"
#include "../include/datetime.h"
#include "../include/tweet.h"
#include <iostream>
#include <vector>

using namespace std;

MainWin::MainWin(map<string, User*>& au, map<string, vector<Tweet*> >& allTrends) : allUsers(au), allTimeTrends(allTrends)
{
	btnTweet = new QPushButton("&Tweet");
	btnSave = new QPushButton("&Save");
    btnTrends = new QPushButton("&Trends");

	userLabel = new QLabel("User:");
	userItem = new QComboBox();
    for(map<string, User*>::iterator it = allUsers.begin(); it != allUsers.end(); ++it)
    {
    	QString username = QString::fromStdString(it->first);
    	userItem->addItem(username);
    }

	followLabel = new QLabel("Follow:");

	followItem = new QComboBox();
    for(map<string, User*>::iterator it = allUsers.begin(); it != allUsers.end(); ++it)
    {
    	QString username = QString::fromStdString(it->first);
    	followItem->addItem(username);
    }

	topRow = new QHBoxLayout;
	topRow->addWidget(userLabel);
	topRow->addWidget(userItem);
	topRow->addWidget(followLabel);
	topRow->addWidget(followItem);

	userFeedLabel = new QLabel("User Feed:");
	userFeed = new QListWidget();

	mentionFeedLabel = new QLabel("Mention Feed:");
	mentionFeed = new QListWidget();

	newTweet = new QLineEdit();
	newTweet->setPlaceholderText("Compose new Tweet...");

	filename = new QLineEdit();
	filename->setPlaceholderText("Save filename as...");

	tweetRow = new QHBoxLayout;
	tweetRow->addWidget(newTweet);
	tweetRow->addWidget(btnTweet);
    tweetRow->addWidget(btnTrends);

	saveRow = new QHBoxLayout;
	saveRow->addWidget(filename);
	saveRow->addWidget(btnSave);

	mainLayout = new QVBoxLayout;
  	mainLayout->addLayout(topRow);
 	mainLayout->addWidget(userFeedLabel);
 	mainLayout->addWidget(userFeed);
 	mainLayout->addWidget(mentionFeedLabel);
 	mainLayout->addWidget(mentionFeed);
 	mainLayout->addLayout(tweetRow);
 	mainLayout->addLayout(saveRow);

    connect(userItem, SIGNAL(activated(QString)),  this, SLOT(doSelect()));
    connect(followItem, SIGNAL(activated(QString)),  this, SLOT(doFollow()));
  	connect(btnTweet,	SIGNAL(clicked()),	this, SLOT(doTweet())); 
    connect(btnTrends,  SIGNAL(clicked()),  this, SLOT(openTrends()));

 	setLayout(mainLayout);
}
MainWin::~MainWin()
{}

void MainWin::closeEvent(QCloseEvent *event)
{
	if (true)
	{
		// save data
		event->accept();
	}
	else
	{
		event->ignore();
	}
}
	void MainWin::doSelect()
	{
		userFeed->clear();
		string username;

		QString u = userItem->currentText();
		username =  u.toStdString();
        User* userObject = allUsers.find(username)->second;

        vector<Tweet*> feed = userObject->getFeed();
        for (unsigned int i = 0; i < feed.size(); i++)
        {
        	string text1 = feed[i]->text();
        	QString text = QString::fromStdString(text1);

        	string user1 = feed[i]->user()->name();
        	QString user = QString::fromStdString(user1);

            QString userText = user + " " + text;

        	userFeed->addItem(userText);
            userFeed->setMinimumWidth(userFeed->sizeHintForColumn(0));
        }	

        string mentionName;

        QString m = userItem->currentText();
        mentionName = m.toStdString();
        User* mentionObject = allUsers.find(mentionName)->second;

        vector<Tweet*> mention = mentionObject->getMentionFeed();
        for (unsigned int i = 0; i < mention.size(); i++)
        {
        	string text2 = mention[i]->text();
        	QString text3 = QString::fromStdString(text2);

        	string user2 = mention[i]->user()->name();
        	QString user3 = QString::fromStdString(user2);

        	mentionFeed->addItem("Hi");
        	mentionFeed->addItem(user3);
        	mentionFeed->addItem(text3);
        }
    }

    void MainWin::doFollow()
    {
    	userFeed->clear();
    	string following;
    	string username;
        User* followingObject;
        User* userObject;

    	QString f = followItem->currentText();
    	following = f.toStdString();

        QString u = userItem->currentText();
        username = u.toStdString();

        map<string, User*>::iterator it2;
        it2 = allUsers.find(username);
        if(it2 != allUsers.end())
        {
            userObject = it2->second;
        }
        else
        {
            userObject = new User(username);
            allUsers.insert(pair<string,User*>(username, userObject));
        }

        map<string, User*>::iterator it1;
        it1 = allUsers.find(following);
        if (it1 != allUsers.end())
        {
            followingObject = it1->second;
        }
        else
        {
            followingObject = new User(following);
            allUsers.insert(pair<string,User*>(following, followingObject));
        }

    	userObject->addFollowing(followingObject);
    	followingObject->addFollower(userObject);

    	vector<Tweet*> feed = userObject->getFeed();
        for (unsigned int i = 0; i < feed.size(); i++)
        {

        	string text1 = feed[i]->text();
        	QString text = QString::fromStdString(text1);

        	string user1 = feed[i]->user()->name();
        	QString user = QString::fromStdString(user1);

            QString userText = user + " " + text;
        	userFeed->addItem(userText);
            userFeed->setMinimumWidth(userFeed->sizeHintForColumn(0));
        }	
    }

    void MainWin::doTweet()
    {
        QDateTime dateTime = dateTime.currentDateTime();
        QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss");

        int hour, min, sec, year, month, day;
        char symbols;
        DateTime dateTimeObject;
        string dateTimestr = dateTimeString.toStdString();
        stringstream ss(dateTimestr);
        ss >> year >> symbols >> month >> symbols >> day >> hour >> symbols >> min >> symbols >> sec;
        cout << year << " " << month << " " << day << " " << hour << " " << min << " " << sec << endl;
        dateTimeObject = DateTime(hour, min, sec, year, month, day);

    	QString username = userItem->currentText();
        string u = username.toStdString();

    	QString tweet = newTweet->text();
    	string t = tweet.toStdString();

        QString newPost = dateTimeString + " " + username + " " + tweet;
        mentionFeed->addItem(newPost);

        newTweet->clear();

    	User* userTweetingObject = allUsers.find(u)->second;
    	Tweet* tweetObject = new Tweet(userTweetingObject, dateTimeObject, t);
    	userTweetingObject->addTweet(tweetObject);
        doSelect();
    }

    void MainWin::openTrends()
    {
        newTrendWindow = new TrendWin(allTimeTrends);
        newTrendWindow->setWindowTitle("Trends");
        newTrendWindow->show();
    }