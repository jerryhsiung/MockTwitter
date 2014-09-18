#include "trendwin.h"
#include <string>
#include <iostream>
#include <QObject>
#include "../include/user.h"
#include "../include/datetime.h"
#include "../include/tweet.h"

using namespace std;

TrendWin::TrendWin(map<string, vector<Tweet*> >& atrend)  : allTimeTrends(atrend)
{
	btnClose = new QPushButton("&Close");
	btnRefresh = new QPushButton("&Refresh");

	btnAllTime = new QRadioButton("&All-Time");
	btnLastDay = new QRadioButton("&Last Day");

	trendLabel = new QLabel("Trending Selection:");
	matchingLabel = new QLabel("Matching Tweets:");

	trendFeed = new QListWidget();
	matchingFeed = new QListWidget();

	topRow = new QHBoxLayout;
	topRow->addWidget(btnAllTime);
	topRow->addWidget(btnLastDay);
	topRow->addWidget(btnRefresh);

	trendLayout = new QVBoxLayout();
	trendLayout->addWidget(trendLabel);
	trendLayout->addLayout(topRow);
	trendLayout->addWidget(trendFeed);
	trendLayout->addWidget(matchingLabel);
	trendLayout->addWidget(matchingFeed);
	trendLayout->addWidget(btnClose);

    connect(btnClose, SIGNAL(clicked()),  this, SLOT(closeWindow()));
    //connect(btnAllTime, SIGNAL(clicked()),  this, SLOT(allTimeHelper()));
    connect(btnAllTime, SIGNAL(clicked()),  this, SLOT(allTime()));
    connect(btnLastDay, SIGNAL(clicked()),  this, SLOT(lastDay()));

	setLayout(trendLayout);
}

TrendWin::~TrendWin()
{}

void TrendWin::closeWindow()
{
	hide();
}

// void TrendWin::allTime(map<string, Tweet*> allTimeTrends)
void TrendWin::allTime()
{
	trendFeed->clear();
	ValVecComp comp;
	vector<string> aTTrends;
	map<string, vector<Tweet*> >::iterator it;

	//inserting unique hashtag strings into vector
	for (it = allTimeTrends.begin(); it != allTimeTrends.end(); ++it)
	{
		aTTrends.push_back(it->first);
	}
	//applying mergeSort
	mergeSort(aTTrends, comp);

	for (int i = aTTrends.size()-1; i >= 0; i--)
	{
		string trendWord = aTTrends.at(i);
		QString qTrendWord = QString::fromStdString(trendWord);
		trendFeed->addItem(qTrendWord);
	}

	connect(trendFeed, SIGNAL(itemClicked(QListWidgetItem*)),  this, SLOT(matching(QListWidgetItem*)));
}

void TrendWin::lastDay()
{
	trendFeed->clear();
}

void TrendWin::matching(QListWidgetItem *item)
{
	matchingFeed->clear();
	QString hash = item->text();
	string hash1 = hash.toStdString();
	vector<Tweet*> tweetObject = allTimeTrends.find(hash1)->second;

	for(unsigned int i = 0; i < tweetObject.size(); i++)
	{
		string tweetText = tweetObject.at(i)->text();
	QString tweetText1 = QString::fromStdString(tweetText);
matchingFeed->addItem(tweetText1);
	}
	
}