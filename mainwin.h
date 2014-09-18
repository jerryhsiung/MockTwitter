#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QMainWindow>
#include <QGridLayout>
#include <QComboBox>
#include <QListWidget>
#include <QLineEdit>
#include <QCloseEvent>
#include <QLabel>
#include <QString>
#include <QListView>
#include <map>
#include <QDateTime>
#include <sstream>
#include "user.h"
#include "trendwin.h"
#include <vector>

class MainWin : public QWidget 
{
	Q_OBJECT

	public:
		MainWin(QWidget *parent = NULL);
		MainWin(std::map<std::string, User*>&, std::map<std::string, std::vector<Tweet*> >&);
		~MainWin();

	protected:
		void closeEvent(QCloseEvent *event);

	private slots:
		void doSelect();
		void doFollow();
		void doTweet();
		void openTrends();

	private:
		QPushButton * btnTweet;
		QPushButton * btnSave;
		QPushButton * btnTrends;
		QLabel * userLabel;
		QLabel * followLabel;
		QLabel * userFeedLabel;
		QLabel * mentionFeedLabel;
		QComboBox * userItem;
		QComboBox * followItem;
		QListWidget * userFeed;
		QListWidget * mentionFeed;
		QLineEdit * newTweet;
		QLineEdit * filename;
		QHBoxLayout* topRow;
		QHBoxLayout* tweetRow;
		QHBoxLayout* saveRow;
		QVBoxLayout* mainLayout; 
    	std::map<std::string, User*> allUsers;
    	std::map<std::string, vector<Tweet*> > allTimeTrends;
    	std::string username;
    	TrendWin *newTrendWindow;
};

#endif