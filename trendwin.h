#ifndef TrendWin_H
#define TrendWin_H

#include <QWidget>
#include <QMainWindow>
#include <QString>
#include <string>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QGridLayout>
#include <QWidget>
#include <QObject>
#include <QDateTime>
#include "tweet.h"
#include "msort.h"
#include <vector>

class TrendWin : public QWidget
{
	Q_OBJECT

public:
	TrendWin(QWidget *parent = NULL);
	TrendWin(std::map<std::string, std::vector<Tweet*> >&);
	~TrendWin();
	

protected:
	//void closeEvent(QCloseEvent *event);
	// void clearUserFeed();

public slots:
	void closeWindow();
	void allTime();
	void lastDay();
	void matching(QListWidgetItem* item);


private:
	QPushButton *btnClose;
	QPushButton *btnRefresh;
	QLabel *trendLabel;
	QLabel *matchingLabel;
	QRadioButton *btnAllTime;
	QRadioButton *btnLastDay;
	QListWidget *trendFeed;
	QListWidget *matchingFeed;
	QHBoxLayout* topRow;
	QListWidgetItem* item;
	QVBoxLayout* trendLayout;
	QWidget *centralWidget;
	std::map<std::string, vector<Tweet*> > allTimeTrends;
};

#endif